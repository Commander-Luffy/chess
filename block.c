/*
 * BLOCK-CELL — 4-quadrant divergent chess on 16×16
 * Each quadrant = 1 GoL cell. Nash = alive. Else = reset.
 * 2 human generals (Q1, Q3) + 2 Flint nobles (Q2, Q4)
 * Unicode pieces, fog of war, sphere of influence
 *
 * v0.1: get the board rendering + 4-player turns + basic movement working
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SZ 16
#define SAVE_FILE "block.sav"

/* Piece encoding:
 * White (Q1): uppercase  A-Z
 * Black (Q3): lowercase  a-z
 * Noble1 (Q2): '1'..'9' (uppercase pieces with flag)
 * Noble2 (Q4): '!'..'(' (lowercase pieces with flag)
 * '.' = empty
 *
 * Simplified: 4 colors using high nibble
 * Player 0 = Q1 (White general)   → uppercase
 * Player 1 = Q2 (Noble Flint 1)   → uppercase + underline in display
 * Player 2 = Q3 (Black general)   → lowercase
 * Player 3 = Q4 (Noble Flint 2)   → lowercase + underline in display
 */

typedef struct {
    char board[SZ][SZ];    /* piece char */
    int  owner[SZ][SZ];    /* 0-3 = player, -1 = empty */
    int  revealed[SZ][SZ]; /* 1 = identity known, 0 = fog (looks like pawn) */
    int  turn;             /* 0-3 */
    int  moveCount;
    int  alive[4];         /* 1 = quadrant alive, 0 = dead/reset */
    int  nashReached[4];   /* 1 = this quadrant reached equilibrium */
    int  budget[4];        /* sphere budget per player */
    int  sphere[SZ][SZ];   /* sphere radius of piece at this position (0 = none) */
    int  gameOver;
    int  golTick;          /* which GoL generation we're on */
    char lastMove[32];
} Block;

/* ---- Piece glyphs ---- */

const char *glyph(char p, int owner, int revealed, int viewerOwner) {
    /* Fog: if not revealed and not own piece, show as pawn */
    if (!revealed && owner != viewerOwner && owner >= 0) {
        return (owner < 2) ? "\u2659" : "\u265F"; /* ♙ or ♟ */
    }
    switch (p) {
        case 'K': return "\u2654"; case 'Q': return "\u2655";
        case 'R': return "\u2656"; case 'B': return "\u2657";
        case 'N': return "\u2658"; case 'P': return "\u2659";
        case 'k': return "\u265A"; case 'q': return "\u265B";
        case 'r': return "\u265C"; case 'b': return "\u265D";
        case 'n': return "\u265E"; case 'p': return "\u265F";
        default:  return " ";
    }
}

/* Player color labels */
const char *playerName(int p) {
    switch (p) {
        case 0: return "Q1 General ♔";
        case 1: return "Q2 Noble ♘";
        case 2: return "Q3 General ♚";
        case 3: return "Q4 Noble ♞";
        default: return "???";
    }
}

/* Which quadrant does (r,c) belong to? */
int quadrant(int r, int c) {
    if (r < SZ/2 && c < SZ/2) return 1;  /* top-left = Q2 noble */
    if (r < SZ/2 && c >= SZ/2) return 0;  /* top-right = Q1 general */
    if (r >= SZ/2 && c < SZ/2) return 2;  /* bottom-left = Q3 general */
    return 3;                               /* bottom-right = Q4 noble */
}

/* ---- Init ---- */

void placeArmy(Block *b, int player, int startRow, int startCol, int dir) {
    /* Place a standard army in a quadrant corner
     * dir: 1 = facing down (top), -1 = facing up (bottom) */
    int backRow = startRow;
    int pawnRow = startRow + dir;
    char pieces[] = "RNBQKBNR";

    for (int i = 0; i < 8; i++) {
        int c = startCol + i;
        if (c >= SZ) break;
        char p = pieces[i];
        if (player >= 2) p = tolower(p);
        b->board[backRow][c] = p;
        b->owner[backRow][c] = player;
        b->revealed[backRow][c] = 0; /* fog by default */

        /* Pawns */
        char pawn = (player < 2) ? 'P' : 'p';
        b->board[pawnRow][c] = pawn;
        b->owner[pawnRow][c] = player;
        b->revealed[pawnRow][c] = 0;
    }
}

void initBlock(Block *b) {
    memset(b, 0, sizeof(Block));
    for (int r = 0; r < SZ; r++)
        for (int c = 0; c < SZ; c++) {
            b->board[r][c] = '.';
            b->owner[r][c] = -1;
        }

    /* Q1 General (White) — top-right, rows 0-1, cols 8-15 */
    placeArmy(b, 0, 0, 8, 1);

    /* Q2 Noble Flint 1 — top-left, rows 0-1, cols 0-7 */
    placeArmy(b, 1, 0, 0, 1);

    /* Q3 General (Black) — bottom-left, rows 14-15, cols 0-7 */
    placeArmy(b, 2, 15, 0, -1);

    /* Q4 Noble Flint 2 — bottom-right, rows 14-15, cols 8-15 */
    placeArmy(b, 3, 15, 8, -1);

    b->turn = 0;
    b->moveCount = 0;
    for (int i = 0; i < 4; i++) {
        b->alive[i] = 1;
        b->nashReached[i] = 0;
        b->budget[i] = 5;
    }
    b->gameOver = 0;
    b->golTick = 0;
    strcpy(b->lastMove, "----");

    /* Own pieces always revealed to self */
    for (int r = 0; r < SZ; r++)
        for (int c = 0; c < SZ; c++)
            if (b->owner[r][c] >= 0)
                b->revealed[r][c] = 0; /* stays fog for others */
}

/* ---- Display ---- */

void printBlock(Block *b) {
    int viewer = b->turn;

    printf("\n      ");
    for (int c = 0; c < SZ; c++) printf(" %c  ", 'a' + c);
    printf("\n    +");
    for (int c = 0; c < SZ; c++) printf("---+");
    printf("\n");

    for (int r = 0; r < SZ; r++) {
        printf(" %2d |", SZ - r);
        for (int c = 0; c < SZ; c++) {
            char p = b->board[r][c];
            int own = b->owner[r][c];
            int dark = (r + c) % 2;

            /* Quadrant border markers */
            int onBorder = (r == SZ/2 - 1 || r == SZ/2) && (c == SZ/2 - 1 || c == SZ/2);

            if (p == '.') {
                if (onBorder)
                    printf(" + |");
                else
                    printf(" %s |", dark ? "::" : "  ");
            } else {
                /* Reveal: own pieces always visible, others need sphere/proximity */
                int vis = (own == viewer) ||
                          b->revealed[r][c] ||
                          b->sphere[r][c] > 0;
                printf(" %s |", glyph(p, own, vis, viewer));
            }
        }
        printf(" %2d", SZ - r);

        /* Quadrant labels */
        if (r == 2)  printf("   Q2 Noble");
        if (r == 3)  printf("   Q1 General");
        if (r == 12) printf("   Q3 General");
        if (r == 13) printf("   Q4 Noble");
        printf("\n");

        printf("    +");
        for (int c = 0; c < SZ; c++) printf("---+");
        printf("\n");
    }

    printf("      ");
    for (int c = 0; c < SZ; c++) printf(" %c  ", 'a' + c);
    printf("\n");

    /* Status */
    printf("\n  Move %d | %s | Budget: %d",
           b->moveCount + 1, playerName(b->turn), b->budget[b->turn]);
    printf(" | Alive: ");
    for (int i = 0; i < 4; i++)
        printf("%s%s", b->alive[i] ? "O" : "X", i < 3 ? "-" : "");
    printf(" | GoL tick: %d", b->golTick);
    printf("\n  Last: %s\n", b->lastMove);
}

/* ---- Helpers ---- */

int inBounds(int r, int c) { return r >= 0 && r < SZ && c >= 0 && c < SZ; }

int isOwn(Block *b, int r, int c) {
    return b->owner[r][c] == b->turn;
}

int isEnemy(Block *b, int r, int c) {
    int o = b->owner[r][c];
    return o >= 0 && o != b->turn;
}

int isAlly(Block *b, int r, int c) {
    /* Allies: same general/noble pair (0+1, 2+3) */
    int o = b->owner[r][c];
    if (o < 0) return 0;
    int myTeam = b->turn / 2;
    int theirTeam = o / 2;
    return myTeam == theirTeam;
}

int pathClear(Block *b, int r1, int c1, int r2, int c2) {
    int dr = 0, dc = 0;
    if (r2 > r1) dr = 1; else if (r2 < r1) dr = -1;
    if (c2 > c1) dc = 1; else if (c2 < c1) dc = -1;
    int r = r1 + dr, c = c1 + dc;
    while (r != r2 || c != c2) {
        if (b->board[r][c] != '.') return 0;
        r += dr; c += dc;
    }
    return 1;
}

/* ---- Move validation (classical + Flint-pawn omni-move) ---- */

int isLegal(Block *b, int r1, int c1, int r2, int c2) {
    if (!inBounds(r1, c1) || !inBounds(r2, c2)) return 0;
    if (r1 == r2 && c1 == c2) return 0;
    if (!isOwn(b, r1, c1)) return 0;

    /* Can't capture own or allied pieces */
    if (isOwn(b, r2, c2) || isAlly(b, r2, c2)) return 0;

    char piece = b->board[r1][c1];
    int dr = r2 - r1, dc = c2 - c1;
    int adr = abs(dr), adc = abs(dc);
    char lower = tolower(piece);

    switch (lower) {
        case 'p': /* Flint-Pawn: omni-directional 1 square, all diagonal captures */
            if (adr <= 1 && adc <= 1 && (adr + adc) > 0) {
                /* Can't cross behind own 2nd rank */
                int homeBack = (b->turn < 2) ? 0 : SZ - 1;
                if (r2 == homeBack) return 0;
                /* Diagonal = must capture or empty */
                if (adr == 1 && adc == 1) return 1; /* diagonal: capture or move */
                /* Cardinal: only if empty (no frontal capture for pawns) */
                if (b->board[r2][c2] == '.') return 1;
                return 0;
            }
            /* Pawn double jump from 2nd rank */
            {
                int homeRow2 = (b->turn < 2) ? 1 : SZ - 2;
                int fwd = (b->turn < 2) ? 1 : -1;
                if (r1 == homeRow2 && dc == 0 && dr == 2 * fwd &&
                    b->board[r1 + fwd][c1] == '.' && b->board[r2][c2] == '.')
                    return 1;
            }
            return 0;

        case 'r':
            if (dr != 0 && dc != 0) return 0;
            return pathClear(b, r1, c1, r2, c2);

        case 'n':
            return (adr == 2 && adc == 1) || (adr == 1 && adc == 2);

        case 'b':
            if (adr != adc) return 0;
            return pathClear(b, r1, c1, r2, c2);

        case 'q':
            if (dr == 0 || dc == 0) return pathClear(b, r1, c1, r2, c2);
            if (adr == adc) return pathClear(b, r1, c1, r2, c2);
            return 0;

        case 'k':
            return adr <= 1 && adc <= 1;
    }
    return 0;
}

/* ---- Sphere drag check ---- */

int canMoveSphere(Block *b, int r1, int c1, int r2, int c2) {
    int sp = b->sphere[r1][c1];
    if (sp <= 0) return 1; /* no sphere, no drag */

    int dr = 0, dc = 0;
    if (r2 > r1) dr = 1; else if (r2 < r1) dr = -1;
    if (c2 > c1) dc = 1; else if (c2 < c1) dc = -1;

    /* Check every piece in sphere: can they all shift 1 in (dr,dc)? */
    for (int sr = r1 - sp; sr <= r1 + sp; sr++) {
        for (int sc = c1 - sp; sc <= c1 + sp; sc++) {
            if (!inBounds(sr, sc)) continue;
            if (sr == r1 && sc == c1) continue; /* the moving piece itself */
            if (b->board[sr][sc] == '.') continue;
            if (b->owner[sr][sc] != b->turn && !isAlly(b, sr, sc)) continue; /* only drag own/allied */

            int nr = sr + dr, nc = sc + dc;
            if (!inBounds(nr, nc)) return 0; /* would go off board */
            if (b->board[nr][nc] != '.' && !(nr == r1 && nc == c1)) {
                /* Collision with non-empty square that isn't the departing piece */
                if (b->owner[nr][nc] != b->turn && !isAlly(b, nr, nc))
                    return 0; /* collision with non-allied piece */
            }
        }
    }
    return 1;
}

/* Execute sphere drag */
void executeDrag(Block *b, int r1, int c1, int dr, int dc) {
    int sp = b->sphere[r1][c1];
    if (sp <= 0) return;

    /* Collect pieces to drag (can't modify board while iterating) */
    int dragR[256], dragC[256], dragN = 0;
    for (int sr = r1 - sp; sr <= r1 + sp; sr++) {
        for (int sc = c1 - sp; sc <= c1 + sp; sc++) {
            if (!inBounds(sr, sc)) continue;
            if (sr == r1 && sc == c1) continue;
            if (b->board[sr][sc] == '.') continue;
            if (b->owner[sr][sc] == b->turn || isAlly(b, sr, sc)) {
                dragR[dragN] = sr;
                dragC[dragN] = sc;
                dragN++;
            }
        }
    }

    /* Move dragged pieces (clear first, then place) */
    char saved[256]; int savedOwn[256];
    for (int i = 0; i < dragN; i++) {
        saved[i] = b->board[dragR[i]][dragC[i]];
        savedOwn[i] = b->owner[dragR[i]][dragC[i]];
        b->board[dragR[i]][dragC[i]] = '.';
        b->owner[dragR[i]][dragC[i]] = -1;
    }
    for (int i = 0; i < dragN; i++) {
        int nr = dragR[i] + dr, nc = dragC[i] + dc;
        b->board[nr][nc] = saved[i];
        b->owner[nr][nc] = savedOwn[i];
    }
}

/* ---- Make move ---- */

int makeMove(Block *b, int r1, int c1, int r2, int c2) {
    if (!isLegal(b, r1, c1, r2, c2)) return 0;

    char piece = b->board[r1][c1];
    int isHighPiece = (tolower(piece) != 'p');

    /* Sphere drag check for high pieces */
    if (isHighPiece && !canMoveSphere(b, r1, c1, r2, c2)) {
        printf("  Sphere collision! Can't drag pieces in that direction.\n");
        return 0;
    }

    /* Execute sphere drag BEFORE moving the piece */
    if (isHighPiece) {
        int dr = 0, dc = 0;
        if (r2 > r1) dr = 1; else if (r2 < r1) dr = -1;
        if (c2 > c1) dc = 1; else if (c2 < c1) dc = -1;
        executeDrag(b, r1, c1, dr, dc);
    }

    /* Capture */
    char captured = b->board[r2][c2];

    /* Execute move */
    b->board[r2][c2] = piece;
    b->owner[r2][c2] = b->turn;
    b->board[r1][c1] = '.';
    b->owner[r1][c1] = -1;

    /* Reveal piece to capturer's team on capture */
    if (captured != '.') {
        b->revealed[r2][c2] = 1;
        printf("  Captured! Piece revealed.\n");
    }

    /* Reveal: entering enemy sphere reveals you */
    for (int dr = -3; dr <= 3; dr++)
        for (int dc = -3; dc <= 3; dc++) {
            int er = r2 + dr, ec = c2 + dc;
            if (!inBounds(er, ec)) continue;
            if (b->sphere[er][ec] > 0 && isEnemy(b, er, ec)) {
                int dist = abs(dr) > abs(dc) ? abs(dr) : abs(dc);
                if (dist <= b->sphere[er][ec])
                    b->revealed[r2][c2] = 1;
            }
        }

    /* Record */
    sprintf(b->lastMove, "%c%d%c%d",
            'a' + c1, SZ - r1, 'a' + c2, SZ - r2);
    b->moveCount++;

    /* Advance turn (skip dead players) */
    do {
        b->turn = (b->turn + 1) % 4;
    } while (!b->alive[b->turn] && b->turn != (b->moveCount % 4));

    return 1;
}

/* ---- Budget command: assign sphere ---- */

int assignSphere(Block *b, int r, int c, int radius) {
    if (!inBounds(r, c) || !isOwn(b, r, c)) {
        printf("  Not your piece.\n");
        return 0;
    }
    int cost = radius * (radius + 1) / 2; /* triangular: 1, 3, 6 */
    int oldCost = b->sphere[r][c] * (b->sphere[r][c] + 1) / 2;
    int netCost = cost - oldCost;
    if (netCost > b->budget[b->turn]) {
        printf("  Not enough budget. Need %d, have %d.\n", netCost, b->budget[b->turn]);
        return 0;
    }
    b->budget[b->turn] -= netCost;
    b->sphere[r][c] = radius;
    printf("  Sphere radius %d assigned. Budget remaining: %d\n", radius, b->budget[b->turn]);
    return 1;
}

/* ---- Nash / Draw offer ---- */

void offerNash(Block *b) {
     /* doesn't matter, we check per player */
    b->nashReached[b->turn] = 1;
    printf("  %s offers Nash equilibrium (draw).\n", playerName(b->turn));

    /* Check if all alive players agree */
    int allNash = 1;
    for (int i = 0; i < 4; i++)
        if (b->alive[i] && !b->nashReached[i]) allNash = 0;

    /* Advance turn — Nash counts as your move */
    do {
        b->turn = (b->turn + 1) % 4;
    } while (!b->alive[b->turn]);
    b->moveCount++;

    if (allNash) {
        printf("\n  ╔════════════════════════════╗\n");
        printf("  ║  NASH EQUILIBRIUM REACHED  ║\n");
        printf("  ║  All quadrants ALIVE       ║\n");
        printf("  ║  GoL tick advances         ║\n");
        printf("  ╚════════════════════════════╝\n\n");
        b->golTick++;
        /* Reset Nash flags, replenish budgets */
        for (int i = 0; i < 4; i++) {
            b->nashReached[i] = 0;
            b->budget[i] = 5 + b->golTick; /* budget grows with ticks */
        }
    }
}

/* ---- Save / Load ---- */

void saveBlock(Block *b) {
    FILE *f = fopen(SAVE_FILE, "wb");
    if (!f) { printf("  Save failed.\n"); return; }
    fwrite(b, sizeof(Block), 1, f);
    fclose(f);
    printf("  Saved.\n");
}

int loadBlock(Block *b) {
    FILE *f = fopen(SAVE_FILE, "rb");
    if (!f) { printf("  No save found.\n"); return 0; }
    if (fread(b, sizeof(Block), 1, f) != 1) { fclose(f); return 0; }
    fclose(f);
    printf("  Loaded.\n");
    return 1;
}

/* ---- Parse ---- */

int parseMove(const char *input, int *r1, int *c1, int *r2, int *c2) {
    if (strlen(input) < 4) return 0;
    *c1 = input[0] - 'a';
    *r1 = SZ - atoi(input + 1);
    /* Find second coordinate */
    int i = 1;
    while (input[i] && (input[i] >= '0' && input[i] <= '9')) i++;
    *c2 = input[i] - 'a';
    *r2 = SZ - atoi(input + i + 1);
    return inBounds(*r1, *c1) && inBounds(*r2, *c2);
}

/* ---- Main ---- */

int main(void) {
    Block block;
    char input[64];

    printf("\n  ╔═══════════════════════════════╗\n");
    printf("  ║   BLOCK-CELL — 4-way chess    ║\n");
    printf("  ║   16×16 · Fog · Spheres       ║\n");
    printf("  ╠═══════════════════════════════╣\n");
    printf("  ║  [1] New Block                ║\n");
    printf("  ║  [2] Load Block               ║\n");
    printf("  ║  [3] Quit                     ║\n");
    printf("  ╚═══════════════════════════════╝\n  > ");
    fflush(stdout);

    if (!fgets(input, sizeof(input), stdin)) return 0;
    input[strcspn(input, "\n")] = 0;

    if (input[0] == '3' || input[0] == 'q') return 0;
    if (input[0] == '2') { if (!loadBlock(&block)) { initBlock(&block); } }
    else initBlock(&block);

    printf("\n  Commands:\n");
    printf("    a2a4       Move piece (coordinates)\n");
    printf("    sphere c3 2  Assign sphere radius 2 to piece at c3\n");
    printf("    nash       Offer Nash equilibrium (draw)\n");
    printf("    save/load  Save or load game\n");
    printf("    board      Reprint board\n");
    printf("    help       Show commands\n");
    printf("    quit       Exit\n\n");

    while (!block.gameOver) {
        printBlock(&block);
        printf("  > ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "quit") == 0 || strcmp(input, "q") == 0) break;
        if (strcmp(input, "board") == 0) continue;
        if (strcmp(input, "save") == 0) { saveBlock(&block); continue; }
        if (strcmp(input, "load") == 0) { loadBlock(&block); continue; }
        if (strcmp(input, "nash") == 0) { offerNash(&block); continue; }
        if (strcmp(input, "help") == 0) {
            printf("  a2a4=move  sphere c3 2=assign  nash=offer draw  save/load/board/quit\n");
            continue;
        }

        /* Sphere command: sphere <pos> <radius> */
        if (strncmp(input, "sphere ", 7) == 0) {
            int sc = input[7] - 'a';
            int sr = SZ - atoi(input + 8);
            int radius = 0;
            char *space = strchr(input + 8, ' ');
            if (space) radius = atoi(space + 1);
            assignSphere(&block, sr, sc, radius);
            continue;
        }

        int r1, c1, r2, c2;
        if (!parseMove(input, &r1, &c1, &r2, &c2)) {
            printf("  Bad input. Use: a2a4 or sphere c3 2\n");
            continue;
        }

        if (!makeMove(&block, r1, c1, r2, c2)) {
            printf("  Illegal move.\n");
        }
    }

    printf("\n  Block session ended. GoL tick: %d\n", block.golTick);
    return 0;
}
