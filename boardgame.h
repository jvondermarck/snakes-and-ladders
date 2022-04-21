/**
 * @file boardgame.h
 * @author Julien Von Der Marck
 * @brief Function prototypes of the boardgame.c file and include librairies 
 * @version 1.0.25
 * @date 21/04/2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // for srand()
#include <stdbool.h>
#include <time.h>

/**
 * @brief Minimum size of the boardgame
 */
#define MIN_SIZE 36

/**
 * @brief Maximum size of the boardgame
 */
#define MAX_SIZE 64

/**
 * @brief Number of columns of the boardgame to ouput to the user each round
 */
#define COLUMNS 8

/**
 * @brief Snake struct 
 * There is a pointer to a square where is located the head of the snake
 * There is a pointer to a square where is located the foot of the snake
 * There is the length of the snake from the head to the foot (1 square = 1 length)
 * There is a pointer to another snake because the're all linked each other
 */
struct snake {
    struct square *index_head;
    struct square *index_foot;
    int length;
    struct snake *next;
};

/**
 * @brief Ladder struct 
 * There is a pointer to a square where is located the head of the ladder
 * There is a pointer to a square where is located the foot of the ladder
 * There is the length of the ladder from the head to the foot (1 square = 1 length)
 * There is a pointer to another ladder because the're all linked each other
 */
struct ladder {
    struct square *index_head;
    struct square *index_foot;
    int length;
    struct ladder *next;
};

/**
 * @brief Square struct
 * There is the index of the square, the number of the snake (unique)
 * A square know if there is or isn't the player on it
 * Has the information of the presence of a snake / ladder 
 * The name of the square depending if there is a presence of snake/ladder
 * There is a pointer to another square because the're all linked each other
 */
struct square {
    int index;
    bool isPlayer; // false = not here and true = on this square
    struct snake *isSnake;
    struct ladder *isLadder;
    char name[2];
    struct square *next; // if next = null -> we're on the last square
};

/**
 * @brief Boardgame struct
 * The boardgame will know where is located the player by knowing the index number of the square
 * The length of the boardgame
 * A list of square
 * And the cursor square that will be used to seek some squares (linked list)
 */
struct boardgame {
    int index_player; // where is located the player
    int length;
    struct square *square; // because i don't know the size of array, I just use a pointer 
    struct square *head_square;
};

/**
 * @brief Init the first square header
 * 
 * @return struct square* the square allocated in memory
 */
struct square *init_square();

/** 
 * create a boardgame randomly of size 32 to 64 
 */ 
struct boardgame *create_boardgame();

/**
 * @brief Method to print the boardgame to the user
 * The user will see the whole boardgame by seeing each square with the index
 * The presence of snake / ladder head or foot on each square
 * And the location of the player in the boardgame
 * 
 * @param p_boardgame : the main boardgame struct
 */
void print_boardgame(struct boardgame *p_boardgame);

/**
 * @brief Simulate a die roll
 * 
 * @return int the number between 1 and 6 draw at random
 */
int roll_die();

/**
 * @brief Get the random length of a snake/ladder head to foot
 * 
 * @param range the range will be used to avoid draw a random number if the range is less than 10 otherwise we will get an error
 * @return int return a random number between 1 to 10 for the length between the head to the bottom of a snake/tail
 */
int random_length(int range);

/**
 * @brief Get the Random Head of the snake/ladder location on the boardgame 
 * 
 * @param boardgame : the unique boardgame struct that has all the information of the game
 * @param data : void because it will be either a Snake struct or a Ladder struct 
 * @param letter : the array that has two 2 letters in it to know later for the user if the square in question is occuped by a Snake/Ladder head
 * @param random_head : the pointer random head number index square
 * @param isSnake : to know if the square is already used by a snake/ladder
 */
void getRandomHead(struct boardgame *boardgame, void *data, char letter[2], int *random_head, bool isSnake);

/**
 * @brief Get the Random Foot of the snake/ladder location on the boardgame 
 * 
 * @param boardgame : the unique boardgame struct that has all the information of the game
 * @param data : void because it will be either a Snake struct or a Ladder struct 
 * @param letter : (for the foot square) the array that has two 2 letters in it to know later for the user if the square in question is occuped by a Snake/Ladder head
 * @param letterHead : 'for the head square) the array that has two 2 letters in it to know later for the user if the square in question is occuped by a Snake/Ladder foot
 * @param random_head : the pointer random head number index square
 * @param isSnake : to know if the square is already used by a snake/ladder
 * @return int the location of the snake/ladder foot on the boardgame
 */
int getRandomFoot(struct boardgame *boardgame, void *data, char letter[2], char letterHead[2], int *random_head, bool isSnake);

/**
 * @brief Add a new snake to the game
 * 
 * @param head_snake : the snake cursor for the linked list to seek a ladder
 * @param boardgame : the unique boardgame struct that has all the information of the game
 * @return struct snake* 
 */
struct snake *addSnake(struct snake *head_snake, struct boardgame *boardgame);

/**
 * @brief Add a new ladder to the game
 * 
 * @param head_ladder : the ladder cursor for the linked list to seek a ladder
 * @param boardgame : the unique boardgame struct that has all the information of the game
 * @return struct ladder* 
 */
struct ladder *addLadder(struct ladder *head_ladder, struct boardgame *boardgame);

/**
 * @brief Init the snake head for the linked list
 * 
 * @return struct snake* : the snake allocated
 */
struct snake *init_snake();

/**
 * @brief Init the ladder head for the linked list
 * 
 * @return struct ladder* : the ladder allocated
 */
struct ladder *init_ladder();

/**
 * @brief Check if the args written in the command line are correct numbers,
 * Must be around 5 to 30 snakes/ladders.
 * @param argv the arguments passed in the command line
 * @return int number between 1 and 0 : 0 = no error and 1 = error (it will cause an error and stop the execution)
 */
int check_args(char *argv[]);