#include <stdio.h>
#include <stdlib.h>
#include <time.h>
char *board;
int size;
void clearScreen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}
void showBoard() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int n = i * size + j;
          if (board[n] == '.')
                printf("%3d", n + 1);
            else
                printf("%3c", board[n]);
          if (j < size - 1)
                printf(" |");
        }
      printf("\n");
      if (i < size - 1) {
            for (int j = 0; j < size; j++) {
                printf("----");
                if (j < size - 1)
                    printf("+");
            }
            printf("\n");
        }
    }
}
int checkWin(char symbol) {
    for (int i = 0; i < size; i++) {
        int row = 1;
        int col = 1;
      for (int j = 0; j < size; j++) {
            if (board[i * size + j] != symbol)
                row = 0;
        if (board[j * size + i] != symbol)
                col = 0;
        }
      if (row || col)
            return 1;
    }
  int d1 = 1;
    int d2 = 1;
  for (int i = 0; i < size; i++) {
        if (board[i * size + i] != symbol)
            d1 = 0;
    if (board[i * size + size - 1 - i] != symbol)
            d2 = 0;
    }
  return d1 || d2;
}
int main() {
    int mode, choice, move;
    char player, bot, current;
  srand(time(NULL));
  printf("Field size: ");
    if (scanf("%d", &size) != 1 || size < 3)
        return 1;
  board = malloc((size_t)size * size);
  if (board == NULL)
        return 1;
  printf("1 Bot\n2 Player\n");
    scanf("%d", &mode);
  printf("1 X\n2 O\n");
    scanf("%d", &choice);
  player = choice == 1 ? 'X' : 'O';
    bot = player == 'X' ? 'O' : 'X';
  int cells = size * size;
  for (int i = 0; i < cells; i++)
        board[i] = '.';
  current = 'X';
  while (1) {
        clearScreen();
        showBoard();
    if (mode == 1 && current == bot) {
            do {
                move = rand() % cells;
            } while (board[move] != '.');
      board[move] = bot;
    } else {
            printf("%c: ", current);
      if (scanf("%d", &move) != 1) {
                free(board);
                return 1;
            }
      if (move < 1 || move > cells ||
                board[move - 1] != '.')
                continue;
      board[move - 1] = current;
        }
    if (checkWin(current)) {
            clearScreen();
            showBoard();
            printf("%c wins\n", current);
            break;
        }
    int full = 1;
    for (int i = 0; i < cells; i++) {
            if (board[i] == '.') {
                full = 0;
                break;
            }
        }
    if (full) {
            clearScreen();
            showBoard();
            printf("Draw\n");
            break;
        }
current = current == 'X' ? 'O' : 'X';
    }
free(board);
  return 0;
}
