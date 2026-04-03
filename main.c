/*
 * Chess — from scratch in C
 * Unicode pieces, coordinate moves (e2e4)
 * En passant, castling, pawn promotion, check/checkmate/stalemate
 * Save/load, menu system
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SAVE_FILE "chess.sav"

typedef struct {
    char board[8][8];
    int turn;           /* 0=white, 1=black */
    int moveCount;
    int gameOver;
    char lastMove[32];
    /* Castling rights */
    int whiteKingMoved;
    int blackKingMoved;
    int whiteRookAMoved; /* a1 rook */
    int whiteRookHMoved; /* h1 rook */
    int blackRookAMoved; /* a8 rook */
    int blackRookHMoved; /* h8 rook */
    /* En passant: column where a pawn just double-moved (-1 if none) */
    int enPassantCol;
    int enPassantRow;    /* the row the capturing pawn lands on */
} Game;

/* ---- Piece glyphs ---- */

const char *pieceGlyph(char p) {
    switch (p) {
        case 'K': return "\u2654";
        case 'Q': return "\u2655";
        case 'R': return "\u2656";
        case 'B': return "\u2657";
        case 'N': return "\u2658";
        case 'P': return "\u2659";
        case 'k': return "\u265A";
        case 'q': return "\u265B";
        case 'r': return "\u265C";
        case 'b': return "\u265D";
        case 'n': return "\u265E";
        case 'p': return "\u265F";
        default:  return " ";
    }
}

/* ---- Init ---- */

void initBoard(Game *g) {
    char back[] = "rnbqkbnr";
    for (int i = 0; i < 8; i++) {
        g->board[0][i] = back[i];
        g->board[1][i] = 'p';
        g->board[6][i] = 'P';
        g->board[7][i] = toupper(back[i]);
        for (int r = 2; r < 6; r++)
            g->board[r][i] = '.';
    }
    g->turn = 0;
    g->moveCount = 0;
    g->gameOver = 0;
    strcpy(g->lastMove, "----");
    g->whiteKingMoved = g->blackKingMoved = 0;
    g->whiteRookAMoved = g->whiteRookHMoved = 0;
    g->blackRookAMoved = g->blackRookHMoved = 0;
    g->enPassantCol = -1;
    g->enPassantRow = -1;
}

/* ---- Display ---- */

void printBoard(Game *g) {
    printf("\n     a    b    c    d    e    f    g    h\n");
    printf("  +----+----+----+----+----+----+----+----+\n");
    for (int r = 0; r < 8; r++) {
        printf("%d |", 8 - r);
        for (int c = 0; c < 8; c++) {
            char p = g->board[r][c];
            int dark = (r + c) % 2;
            if (p == '.')
                printf(" %s  |", dark ? "::" : "  ");
            else
                printf(" %s  |", pieceGlyph(p));
        }
        printf(" %d\n", 8 - r);
        printf("  +----+----+----+----+----+----+----+----+\n");
    }
    printf("     a    b    c    d    e    f    g    h\n");
    printf("\n  Move %d | %s | Last: %s\n",
           g->moveCount + 1,
           g->turn == 0 ? "White ♔" : "Black ♚",
           g->lastMove);
}

/* ---- Helpers ---- */

int isOwn(Game *g, char p) {
    if (p == '.') return 0;
    return g->turn == 0 ? isupper(p) : islower(p);
}

int isEnemy(Game *g, char p) {
    if (p == '.') return 0;
    return g->turn == 0 ? islower(p) : isupper(p);
}

int inBounds(int r, int c) { return r >= 0 && r < 8 && c >= 0 && c < 8; }

int pathClear(Game *g, int r1, int c1, int r2, int c2) {
    int dr = 0, dc = 0;
    if (r2 > r1) dr = 1; else if (r2 < r1) dr = -1;
    if (c2 > c1) dc = 1; else if (c2 < c1) dc = -1;
    int r = r1 + dr, c = c1 + dc;
    while (r != r2 || c != c2) {
        if (g->board[r][c] != '.') return 0;
        r += dr; c += dc;
    }
    return 1;
}

/* ---- Move validation ---- */

int isLegal(Game *g, int r1, int c1, int r2, int c2) {
    if (!inBounds(r1, c1) || !inBounds(r2, c2)) return 0;
    if (r1 == r2 && c1 == c2) return 0;

    char piece = g->board[r1][c1];
    char target = g->board[r2][c2];
    if (!isOwn(g, piece)) return 0;
    if (isOwn(g, target)) return 0;

    int dr = r2 - r1, dc = c2 - c1;
    int adr = abs(dr), adc = abs(dc);
    char lower = tolower(piece);

    switch (lower) {
        case 'p': {
            int dir = isupper(piece) ? -1 : 1;
            int startRow = isupper(piece) ? 6 : 1;
            /* Forward 1 */
            if (dc == 0 && dr == dir && target == '.') return 1;
            /* Forward 2 from start */
            if (dc == 0 && dr == 2 * dir && r1 == startRow && target == '.' &&
                g->board[r1 + dir][c1] == '.') return 1;
            /* Capture diagonally */
            if (adc == 1 && dr == dir && isEnemy(g, target)) return 1;
            /* En passant */
            if (adc == 1 && dr == dir && target == '.' &&
                c2 == g->enPassantCol && r2 == g->enPassantRow) return 1;
            return 0;
        }
        case 'r':
            if (dr != 0 && dc != 0) return 0;
            return pathClear(g, r1, c1, r2, c2);
        case 'n':
            return (adr == 2 && adc == 1) || (adr == 1 && adc == 2);
        case 'b':
            if (adr != adc) return 0;
            return pathClear(g, r1, c1, r2, c2);
        case 'q':
            if (dr == 0 || dc == 0) return pathClear(g, r1, c1, r2, c2);
            if (adr == adc) return pathClear(g, r1, c1, r2, c2);
            return 0;
        case 'k':
            /* Normal king move */
            if (adr <= 1 && adc <= 1) return 1;
            /* Castling: king moves 2 squares horizontally */
            if (adr == 0 && adc == 2) {
                int homeRow = isupper(piece) ? 7 : 0;
                if (r1 != homeRow || c1 != 4) return 0;
                int kingMoved = isupper(piece) ? g->whiteKingMoved : g->blackKingMoved;
                if (kingMoved) return 0;
                if (dc == 2) { /* kingside */
                    int rookMoved = isupper(piece) ? g->whiteRookHMoved : g->blackRookHMoved;
                    if (rookMoved) return 0;
                    if (g->board[homeRow][7] != (isupper(piece) ? 'R' : 'r')) return 0;
                    if (g->board[homeRow][5] != '.' || g->board[homeRow][6] != '.') return 0;
                    return 1; /* check validation happens in makeMove */
                }
                if (dc == -2) { /* queenside */
                    int rookMoved = isupper(piece) ? g->whiteRookAMoved : g->blackRookAMoved;
                    if (rookMoved) return 0;
                    if (g->board[homeRow][0] != (isupper(piece) ? 'R' : 'r')) return 0;
                    if (g->board[homeRow][1] != '.' || g->board[homeRow][2] != '.' || g->board[homeRow][3] != '.') return 0;
                    return 1;
                }
            }
            return 0;
    }
    return 0;
}

/* ---- Check detection ---- */

void findKing(Game *g, int *kr, int *kc) {
    char king = g->turn == 0 ? 'K' : 'k';
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (g->board[r][c] == king) { *kr = r; *kc = c; return; }
    *kr = -1; *kc = -1;
}

int inCheck(Game *g) {
    int kr, kc;
    findKing(g, &kr, &kc);
    if (kr < 0) return 1;
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

/* Check if square is attacked by opponent */
int isAttacked(Game *g, int r, int c) {
    g->turn ^= 1;
    for (int ar = 0; ar < 8; ar++)
        for (int ac = 0; ac < 8; ac++)
            if (isOwn(g, g->board[ar][ac]) && isLegal(g, ar, ac, r, c)) {
                g->turn ^= 1;
                return 1;
            }
    g->turn ^= 1;
    return 0;
}

/* ---- Make move ---- */

int makeMove(Game *g, int r1, int c1, int r2, int c2) {
    if (!isLegal(g, r1, c1, r2, c2)) return 0;

    char piece = g->board[r1][c1];
    char captured = g->board[r2][c2];
    int isCastle = 0;
    int isEP = 0;

    /* Detect castling */
    if (tolower(piece) == 'k' && abs(c2 - c1) == 2) {
        /* Can't castle out of check */
        if (inCheck(g)) return 0;
        /* Can't castle through check */
        int dir = c2 > c1 ? 1 : -1;
        if (isAttacked(g, r1, c1 + dir)) return 0;
        if (isAttacked(g, r1, c2)) return 0;
        isCastle = 1;
    }

    /* Detect en passant */
    if (tolower(piece) == 'p' && c2 == g->enPassantCol && r2 == g->enPassantRow && captured == '.') {
        isEP = 1;
    }

    /* Execute the move */
    g->board[r2][c2] = piece;
    g->board[r1][c1] = '.';

    /* En passant: remove captured pawn */
    if (isEP) {
        int capturedRow = isupper(piece) ? r2 + 1 : r2 - 1;
        g->board[capturedRow][c2] = '.';
    }

    /* Castling: move the rook too */
    if (isCastle) {
        int homeRow = r1;
        if (c2 == 6) { /* kingside */
            g->board[homeRow][5] = g->board[homeRow][7];
            g->board[homeRow][7] = '.';
        } else { /* queenside */
            g->board[homeRow][3] = g->board[homeRow][0];
            g->board[homeRow][0] = '.';
        }
    }

    /* Pawn promotion — player chooses */
    if (tolower(piece) == 'p' && (r2 == 0 || r2 == 7)) {
        char choice = 0;
        printf("\n  PROMOTION! Choose piece:\n");
        printf("  [Q] ♕ Queen  [R] ♖ Rook  [B] ♗ Bishop  [N] ♘ Knight\n  > ");
        fflush(stdout);
        char buf[16];
        if (fgets(buf, sizeof(buf), stdin)) {
            choice = toupper(buf[0]);
        }
        if (choice != 'Q' && choice != 'R' && choice != 'B' && choice != 'N') choice = 'Q';
        g->board[r2][c2] = isupper(piece) ? choice : tolower(choice);
        printf("  Promoted to %s\n", pieceGlyph(g->board[r2][c2]));
    }

    /* Check if move leaves own king in check — illegal */
    if (inCheck(g)) {
        /* Undo everything */
        g->board[r1][c1] = piece;
        g->board[r2][c2] = captured;
        if (isEP) {
            int capturedRow = isupper(piece) ? r2 + 1 : r2 - 1;
            g->board[capturedRow][c2] = isupper(piece) ? 'p' : 'P';
        }
        if (isCastle) {
            int homeRow = r1;
            if (c2 == 6) { g->board[homeRow][7] = g->board[homeRow][5]; g->board[homeRow][5] = '.'; }
            else { g->board[homeRow][0] = g->board[homeRow][3]; g->board[homeRow][3] = '.'; }
        }
        return 0;
    }

    /* Update castling rights */
    if (piece == 'K') g->whiteKingMoved = 1;
    if (piece == 'k') g->blackKingMoved = 1;
    if (piece == 'R' && r1 == 7 && c1 == 0) g->whiteRookAMoved = 1;
    if (piece == 'R' && r1 == 7 && c1 == 7) g->whiteRookHMoved = 1;
    if (piece == 'r' && r1 == 0 && c1 == 0) g->blackRookAMoved = 1;
    if (piece == 'r' && r1 == 0 && c1 == 7) g->blackRookHMoved = 1;
    /* Rook captured on home square also loses rights */
    if (r2 == 7 && c2 == 0) g->whiteRookAMoved = 1;
    if (r2 == 7 && c2 == 7) g->whiteRookHMoved = 1;
    if (r2 == 0 && c2 == 0) g->blackRookAMoved = 1;
    if (r2 == 0 && c2 == 7) g->blackRookHMoved = 1;

    /* Update en passant state */
    g->enPassantCol = -1;
    g->enPassantRow = -1;
    if (tolower(piece) == 'p' && abs(r2 - r1) == 2) {
        g->enPassantCol = c1;
        g->enPassantRow = (r1 + r2) / 2; /* the square the capturing pawn lands on */
    }

    /* Record */
    sprintf(g->lastMove, "%c%d%c%d%s%s",
            'a' + c1, 8 - r1, 'a' + c2, 8 - r2,
            isCastle ? (c2 == 6 ? " O-O" : " O-O-O") : "",
            isEP ? " e.p." : "");
    g->turn ^= 1;
    g->moveCount++;

    /* Check for checkmate or stalemate */
    int hasLegal = 0;
    for (int r = 0; r < 8 && !hasLegal; r++)
        for (int c = 0; c < 8 && !hasLegal; c++)
            if (isOwn(g, g->board[r][c]))
                for (int tr = 0; tr < 8 && !hasLegal; tr++)
                    for (int tc = 0; tc < 8 && !hasLegal; tc++)
                        if (isLegal(g, r, c, tr, tc)) {
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
            printf("\n  ♚ CHECKMATE! %s wins! ♔\n", g->turn == 0 ? "Black" : "White");
        else
            printf("\n  STALEMATE! Draw.\n");
        g->gameOver = 1;
    } else if (inCheck(g)) {
        printf("\n  ♚ CHECK!\n");
    }

    return 1;
}

/* ---- Save / Load ---- */

int saveGame(Game *g) {
    FILE *f = fopen(SAVE_FILE, "wb");
    if (!f) { printf("  Save failed.\n"); return 0; }
    fwrite(g, sizeof(Game), 1, f);
    fclose(f);
    printf("  Game saved to %s\n", SAVE_FILE);
    return 1;
}

int loadGame(Game *g) {
    FILE *f = fopen(SAVE_FILE, "rb");
    if (!f) { printf("  No save file found.\n"); return 0; }
    if (fread(g, sizeof(Game), 1, f) != 1) {
        fclose(f); printf("  Save file corrupted.\n"); return 0;
    }
    fclose(f);
    printf("  Game loaded from %s\n", SAVE_FILE);
    return 1;
}

/* ---- Parse ---- */

int parseMove(const char *input, int *r1, int *c1, int *r2, int *c2) {
    if (strlen(input) < 4) return 0;
    *c1 = input[0] - 'a';
    *r1 = 8 - (input[1] - '0');
    *c2 = input[2] - 'a';
    *r2 = 8 - (input[3] - '0');
    return inBounds(*r1, *c1) && inBounds(*r2, *c2);
}

/* ---- Menu ---- */

void printMenu(void) {
    printf("\n");
    printf("  ╔══════════════════════════╗\n");
    printf("  ║     ♔  C H E S S  ♚     ║\n");
    printf("  ╠══════════════════════════╣\n");
    printf("  ║  [1] New Game            ║\n");
    printf("  ║  [2] Load Game           ║\n");
    printf("  ║  [3] Quit                ║\n");
    printf("  ╚══════════════════════════╝\n");
    printf("\n  > ");
}

void printHelp(void) {
    printf("\n  Commands:\n");
    printf("    e2e4    Move piece (from-to coordinates)\n");
    printf("    e1g1    Castle kingside (move king 2 squares)\n");
    printf("    e1c1    Castle queenside\n");
    printf("    save    Save game\n");
    printf("    load    Load saved game\n");
    printf("    reset   New game\n");
    printf("    menu    Return to menu\n");
    printf("    help    Show this help\n");
    printf("    quit    Exit\n\n");
}

/* ---- Main ---- */

int main(void) {
    Game game;
    char input[64];

    while (1) {
        printMenu();
        fflush(stdout);
        if (!fgets(input, sizeof(input), stdin)) return 0;
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "3") == 0 || strcmp(input, "quit") == 0 || strcmp(input, "q") == 0)
            return 0;

        if (strcmp(input, "1") == 0) {
            initBoard(&game);
            printf("\n  New game started.\n");
        } else if (strcmp(input, "2") == 0) {
            if (!loadGame(&game)) continue;
        } else {
            continue;
        }

        printHelp();

        while (!game.gameOver) {
            printBoard(&game);
            printf("  > ");
            fflush(stdout);

            if (!fgets(input, sizeof(input), stdin)) break;
            input[strcspn(input, "\n")] = 0;

            if (strcmp(input, "quit") == 0 || strcmp(input, "q") == 0) return 0;
            if (strcmp(input, "menu") == 0) break;
            if (strcmp(input, "save") == 0) { saveGame(&game); continue; }
            if (strcmp(input, "load") == 0) { loadGame(&game); continue; }
            if (strcmp(input, "reset") == 0) { initBoard(&game); printf("  Reset.\n"); continue; }
            if (strcmp(input, "help") == 0) { printHelp(); continue; }
            if (strcmp(input, "board") == 0) continue;

            int r1, c1, r2, c2;
            if (!parseMove(input, &r1, &c1, &r2, &c2)) {
                printf("  Bad input. Use format: e2e4 (type 'help' for commands)\n");
                continue;
            }

            if (!makeMove(&game, r1, c1, r2, c2)) {
                printf("  Illegal move.\n");
            }
        }
    }
    return 0;
}
