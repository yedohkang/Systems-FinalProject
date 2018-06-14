#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>

//long messages
#define WELCOME_MSG "\n\n\nHello, and welcome to Battleship! \n\nFirst, we will begin with a setup phase (where you will be asked to place your ships), then we will continue to the playing phase (where\nyou compete with your opponent). \n\nAll standard Battleship rules apply, but we will explain the syntax of our terminal game. \n\nPress enter to continue.\n"

#define SETUP_INSTRUCTIONS "\nSETUP PHASE: \n\nYou will be asked to input the ship, the starting coordinates of the\nlocation, and the direction in which it extends.\n1. the available ships \n\tA: aircraft, size 5 \n\tB: battleship, size 4 \n\tC: cruiser, size 3 \n\tS: submarine, size 3 \n\tD: destroyer, size 2 \n2. the letter and digit corresponding to the column and the row \n3. the letter representing the direction \n\tL: left \n\tR: right \n\tU: up \n\tD: down \nFor example: S A0 D will place a submarine occupying A0, A1, and A2\n\nPress enter to continue.\n"

#define PLAYING_INSTRUCTIONS "\nPLAYING PHASE: \n\nYou will be asked to input the coordinates of the location you would\nlike to send a missile to. \n\tFor example: A0 \n\nHere is what the board display means: \n\t. (empty slot) \n\t* (missed ship) \n\tH (hit ship)\n\nPress enter to continue.\n"

//ship structs
struct aircraft {
  char name;
  int length;
  char coor[256];
};
struct battleship {
  char name;
  int length;
  char coor[256];
};
struct cruiser {
  char name;
  int length;
  char coor[256];
};
struct submarine {
  char name;
  int length;
  char coor[256];
};
struct destroyer {
  char name;
  int length;
  char coor[256];
};
struct board {
  int rows;
  int cols;
  char **board_;
};

struct aircraft *create_aircraft (char name, int size) {
  struct aircraft *A = (struct aircraft *)malloc(sizeof(struct aircraft));
  A->name = name;
  A->length = size;
  return A;
}
struct battleship *create_battleship (char name, int size) {
  struct battleship *B = (struct battleship *)malloc(sizeof(struct battleship));
  B->name = name;
  B->length = size;
  return B;
}
struct cruiser *create_cruiser (char name, int size) {
  struct cruiser *C = (struct cruiser *)malloc(sizeof(struct cruiser));
  C->name = name;
  C->length = size;
  return C;
}
struct submarine *create_submarine (char name, int size) {
  struct submarine *S = (struct submarine *)malloc(sizeof(struct submarine));
  S->name = name;
  S->length = size;
  return S;
}
struct destroyer *create_destroyer (char name, int size) {
  struct destroyer *D = (struct destroyer *)malloc(sizeof(struct destroyer));
  D->name = name;
  D->length = size;
  return D;
}
struct board *create_board (int rows, int cols) {
  struct board *b = (struct board *)malloc(sizeof(struct board));
  b->rows = rows;
  b->cols = cols;

  char ** board_ = (char **)malloc(sizeof(char*) * rows);
  int i;
  for (i = 0; i < rows; i++) {
    board_[i] = (char *)malloc(sizeof(char) * cols);
  }
  b->board_ = board_;

  return b;
}

//colors
#define WATER	"\e[38;2;200;200;200m\e[48;2;0;0;255m"
#define HIT	"\e[38;2;200;200;200m\e[48;2;255;0;0m"
#define MISS	"\e[38;2;100;100;100m\e[48;2;255;255;255m"
#define SHIP	"\e[38;2;255;255;255m\e[48;2;0;200;0m"
#define RESET	"\e[0m"

//function headers
static void sighandler (int signo);
void initialize_board (struct board * home);

void pretty_spacing (int x);
void print_board (struct board * home, struct board * opp, int row);
void display (struct board * home, struct board * opp);

int placement_valid (char ship, char col, char row, char dir, struct board * home, struct board * opp, char shipP[6][13]);
int parse_ship (char * ship_p, char * col_p, char * row_p, char * dir_p, struct board * home, struct board * opp, char shipP[6][13]);
void place_ship (char ship, char col, char row, char dir, struct board * home, char shipP[6][13]);

int missile_valid (char col, char row, struct board * home, struct board * opp);
int parse_missile (char * col_p, char * row_p, struct board * home, struct board * opp);
void place_missile (char col, char row, struct board * opp, int attacking, char * string);

int player_loss (struct board * home);
int game_over (struct board * home, struct board * opp);

