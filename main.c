/*
 * Chess — from scratch in C
 * ASCII board, coordinate moves (e2e4), no libraries, no borrowed art
 * The board IS the graph. Pieces are nodes. Moves are edges.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Piece encoding: uppercase=white, lowercase=black, '.'=empty */
typedef struct {
    char board[8][8];
    int turn; /* 0=white, 1=black */
    int moveCount;
    int gameOver;
    char lastMove[32];
} Game;

void initBoard(Game *g) {
    char back[] = "rnbqkbnr";
    for (int i = 0; i < 8; i++) {
        g->board[0][i] = back[i];        /* black back rank */
        g->board[1][i] = 'p';            /* black pawns */
        g->board[6][i] = 'P';            /* white pawns */
        g->board[7][i] = toupper(back[i]); /* white back rank */
        for (int r = 2; r < 6; r++)
            g->board[r][i] = '.';
    }
    g->turn = 0;
    g->moveCount = 0;
    g->gameOver = 0;
    strcpy(g->lastMove, "----");
}

/* Unicode chess pieces — actual symbols */
const char *pieceGlyph(char p) {
    switch (p) {
        case 'K': return "\u2654"; /* ♔ */
        case 'Q': return "\u2655"; /* ♕ */
        case 'R': return "\u2656"; /* ♖ */
        case 'B': return "\u2657"; /* ♗ */
        case 'N': return "\u2658"; /* ♘ */
        case 'P': return "\u2659"; /* ♙ */
        case 'k': return "\u265A"; /* ♚ */
        case 'q': return "\u265B"; /* ♛ */
        case 'r': return "\u265C"; /* ♜ */
        case 'b': return "\u265D"; /* ♝ */
        case 'n': return "\u265E"; /* ♞ */
        case 'p': return "\u265F"; /* ♟ */
        default:  return " ";
    }
}

void printBoard(Game *g) {
    int dark;
    printf("\n");
    printf("     a    b    c    d    e    f    g    h\n");
    printf("  +----+----+----+----+----+----+----+----+\n");
    for (int r = 0; r < 8; r++) {
        printf("%d |", 8 - r);
        for (int c = 0; c < 8; c++) {
            char p = g->board[r][c];
            dark = (r + c) % 2;
            if (p == '.') {
                printf(" %s  |", dark ? "::" : "  ");
            } else {
                printf(" %s  |", pieceGlyph(p));
            }
        }
        printf(" %d\n", 8 - r);
        printf("  +----+----+----+----+----+----+----+----+\n");
    }
    printf("     a    b    c    d    e    f    g    h\n");
    printf("\n  Move %d | %s to play | Last: %s\n",
           g->moveCount + 1,
           g->turn == 0 ? "White" : "Black",
           g->lastMove);
}

/* Check if a piece belongs to current player */
int isOwn(Game *g, char piece) {
    if (piece == '.') return 0;
    if (g->turn == 0) return isupper(piece);
    return islower(piece);
}

int isEnemy(Game *g, char piece) {
    if (piece == '.') return 0;
    if (g->turn == 0) return islower(piece);
    return isupper(piece);
}

/* Check if square (r,c) is on the board */
int inBounds(int r, int c) {
    return r >= 0 && r < 8 && c >= 0 && c < 8;
}

/* Check if path is clear between two squares (for sliding pieces) */
int pathClear(Game *g, int r1, int c1, int r2, int c2) {
    int dr = 0, dc = 0;
    if (r2 > r1) dr = 1; else if (r2 < r1) dr = -1;
    if (c2 > c1) dc = 1; else if (c2 < c1) dc = -1;

    int r = r1 + dr, c = c1 + dc;
    while (r != r2 || c != c2) {
        if (g->board[r][c] != '.') return 0;
        r += dr;
        c += dc;
    }
    return 1;
}

/* Validate a move — returns 1 if legal, 0 if not */
int isLegal(Game *g, int r1, int c1, int r2, int c2) {
    if (!inBounds(r1, c1) || !inBounds(r2, c2)) return 0;
    if (r1 == r2 && c1 == c2) return 0;

    char piece = g->board[r1][c1];
    char target = g->board[r2][c2];

    if (!isOwn(g, piece)) return 0;
    if (isOwn(g, target)) return 0; /* can't capture own piece */

    int dr = r2 - r1;
    int dc = c2 - c1;
    int adr = abs(dr);
    int adc = abs(dc);
    char lower = tolower(piece);

    switch (lower) {
        case 'p': { /* pawn */
            int dir = isupper(piece) ? -1 : 1; /* white moves up (-r), black down (+r) */
            int startRow = isupper(piece) ? 6 : 1;
            /* Forward 1 */
            if (dc == 0 && dr == dir && target == '.') return 1;
            /* Forward 2 from start */
            if (dc == 0 && dr == 2 * dir && r1 == startRow && target == '.' &&
                g->board[r1 + dir][c1] == '.') return 1;
            /* Capture diagonally */
            if (adc == 1 && dr == dir && isEnemy(g, target)) return 1;
            return 0;
        }
        case 'r': /* rook */
            if (dr != 0 && dc != 0) return 0;
            return pathClear(g, r1, c1, r2, c2);

        case 'n': /* knight */
            return (adr == 2 && adc == 1) || (adr == 1 && adc == 2);

        case 'b': /* bishop */
            if (adr != adc) return 0;
            return pathClear(g, r1, c1, r2, c2);

        case 'q': /* queen = rook + bishop */
            if (dr == 0 || dc == 0) return pathClear(g, r1, c1, r2, c2);
            if (adr == adc) return pathClear(g, r1, c1, r2, c2);
            return 0;

        case 'k': /* king */
            return adr <= 1 && adc <= 1;
    }
    return 0;
}

/* Find the king position for current player */
void findKing(Game *g, int *kr, int *kc) {
    char king = g->turn == 0 ? 'K' : 'k';
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (g->board[r][c] == king) { *kr = r; *kc = c; return; }
    *kr = -1; *kc = -1;
}

/* Check if current player's king is in check */
int inCheck(Game *g) {
    int kr, kc;
    findKing(g, &kr, &kc);
    if (kr < 0) return 1; /* king missing = mated */

    /* Temporarily flip turn to check if opponent can capture king */
    g->turn ^= 1;
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (isOwn(g, g->board[r][c]) && isLegal(g, r, c, kr, kc)) {
                g->turn ^= 1;
                return 1;
            }
    g->turn ^= 1;
    return 0;
}

/* Make a move — returns 1 on success */
int makeMove(Game *g, int r1, int c1, int r2, int c2) {
    if (!isLegal(g, r1, c1, r2, c2)) return 0;

    char piece = g->board[r1][c1];
    char captured = g->board[r2][c2];

    /* Make the move */
    g->board[r2][c2] = piece;
    g->board[r1][c1] = '.';

    /* Pawn promotion (auto-queen) */
    if (tolower(piece) == 'p' && (r2 == 0 || r2 == 7)) {
        g->board[r2][c2] = isupper(piece) ? 'Q' : 'q';
    }

    /* Check if this move leaves own king in check — illegal */
    if (inCheck(g)) {
        /* Undo */
        g->board[r1][c1] = piece;
        g->board[r2][c2] = captured;
        return 0;
    }

    /* Record */
    sprintf(g->lastMove, "%c%d%c%d",
            'a' + c1, 8 - r1, 'a' + c2, 8 - r2);
    g->turn ^= 1;
    g->moveCount++;

    /* Check if opponent is now in checkmate (no legal moves) */
    int hasLegal = 0;
    for (int r = 0; r < 8 && !hasLegal; r++)
        for (int c = 0; c < 8 && !hasLegal; c++)
            if (isOwn(g, g->board[r][c]))
                for (int tr = 0; tr < 8 && !hasLegal; tr++)
                    for (int tc = 0; tc < 8 && !hasLegal; tc++)
                        if (isLegal(g, r, c, tr, tc)) {
                            /* Try it */
                            char p = g->board[r][c];
                            char t = g->board[tr][tc];
                            g->board[tr][tc] = p;
                            g->board[r][c] = '.';
                            if (!inCheck(g)) hasLegal = 1;
                            g->board[r][c] = p;
                            g->board[tr][tc] = t;
                        }

    if (!hasLegal) {
        if (inCheck(g))
            printf("\n  CHECKMATE! %s wins!\n", g->turn == 0 ? "Black" : "White");
        else
            printf("\n  STALEMATE! Draw.\n");
        g->gameOver = 1;
    } else if (inCheck(g)) {
        printf("\n  CHECK!\n");
    }

    /* Check if king was captured (shouldn't happen with check validation, but safety) */
    if (tolower(captured) == 'k') {
        printf("\n  KING CAPTURED! %s wins!\n", g->turn == 1 ? "White" : "Black");
        g->gameOver = 1;
    }

    return 1;
}

/* Parse input like "e2e4" → row/col */
int parseMove(const char *input, int *r1, int *c1, int *r2, int *c2) {
    if (strlen(input) < 4) return 0;
    *c1 = input[0] - 'a';
    *r1 = 8 - (input[1] - '0');
    *c2 = input[2] - 'a';
    *r2 = 8 - (input[3] - '0');
    return inBounds(*r1, *c1) && inBounds(*r2, *c2);
}

int main(void) {
    Game game;
    initBoard(&game);

    char input[64];

    printf("\n  ====== CHESS ======\n");
    printf("  From scratch. No libraries. No borrowed art.\n");
    printf("  Moves: e2e4 (from-square to-square)\n");
    printf("  Commands: quit, reset, board\n\n");

    while (!game.gameOver) {
        printBoard(&game);
        printf("  > ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin)) break;

        /* Strip newline */
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "quit") == 0 || strcmp(input, "q") == 0) break;
        if (strcmp(input, "reset") == 0) { initBoard(&game); continue; }
        if (strcmp(input, "board") == 0) continue; /* just reprint */

        int r1, c1, r2, c2;
        if (!parseMove(input, &r1, &c1, &r2, &c2)) {
            printf("  Bad input. Use format: e2e4\n");
            continue;
        }

        if (!makeMove(&game, r1, c1, r2, c2)) {
            printf("  Illegal move.\n");
        }
    }

    printf("\n  Game over. %d moves played.\n", game.moveCount);
    return 0;
}
