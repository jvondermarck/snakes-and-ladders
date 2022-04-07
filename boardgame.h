#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // for srand()
#include <stdbool.h>
#include <time.h>

// Constant of the boardgame min and max size
#define MIN_SIZE 36
#define MAX_SIZE 64
#define COLUMNS 8

struct snake {
    struct square *index_head;
    struct square *index_foot;
    int length;
    struct snake *next;
};

struct ladder {
    struct square *index_head;
    struct square *index_foot;
    int length;
    struct ladder *next;
};

struct square {
    int index;
    bool isPlayer; // false = not here and true = on this square
    struct snake *isSnake;
    struct ladder *isLadder;
    char name[2];
    struct square *next; // if next = null -> we're on the last square
};

struct boardgame {
    int index_player; // where is located the player
    int length;
    struct square *square; // because i don't know the size of array, I just use a pointer 
    struct square *head_square;
};

struct square *init_square();
// create a boardgame randomly of size 32 to 64
struct boardgame *create_boardgame();
void print_boardgame(struct boardgame *p_boardgame);
// simulate a die
int roll_die();
// return a random number between 1 to 10 for the length between the head to the bottom of a snake/tail
int random_length(int range);
void getRandomHead(struct boardgame *boardgame, void *data, char letter[2], int *random_head, bool isSnake);
int getRandomFoot(struct boardgame *boardgame, void *data, char letter[2], char letterHead[2], int *random_head, bool isSnake);
struct snake *addSnake(struct snake *head_snake, struct boardgame *boardgame);
struct ladder *addLadder(struct ladder *head_ladder, struct boardgame *boardgame);
struct snake *init_snake();
struct ladder *init_ladder();
// Check if the args written in the command line are correct numbers, must be around 5 to 30 snakes/ladders.
int check_args(char *argv[]);