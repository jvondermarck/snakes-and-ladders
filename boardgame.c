#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // for srand()
#include <stdbool.h>

// Constant of the boardgame min and max size
#define MIN_SIZE 32
#define MAX_SIZE 64
#define COLUMNS 8

struct snake {
    int index_head;
    int index_foot;
    int length;
    struct snake *next;
};

struct ladder {
    int index_head;
    int index_foot;
    int length;
    struct ladder *next;
};

struct square {
    int index;
    bool isPlayer; // false = not here and true = on this square
    struct square *next; // if next = null -> we're on the last square
};

struct boardgame {
    int index_player; // where is located the player
    int length;
    struct square *square; // because i don't know the size of array, I just use a pointer 
    struct square *head_square;
};

struct square *init_square() {
    struct square *p_square = malloc(sizeof(struct square));
    p_square->index = 0;
    p_square->isPlayer = false; 
    p_square->next = NULL;
    return p_square;
}

// create a boardgame randomly of size 32 to 64
struct boardgame *create_boardgame(){
    srand(time(NULL));

    int mod = (MAX_SIZE-MIN_SIZE)+1; // to be between 32 and 64 
    int length = rand() % mod + MIN_SIZE; // between 32 and 64 randomly

    struct boardgame *p_boardgame = malloc(sizeof(struct boardgame));
    p_boardgame->length = 36;

    // Taking care of squares now :
    // linked list : creation of the list head of square
    struct square *head_square = init_square();
    p_boardgame->head_square = malloc(sizeof(struct square));
    p_boardgame->head_square = head_square;

    p_boardgame->square = malloc(length * sizeof(struct square));
    for(int i=0; i<p_boardgame->length; i++){
        struct square *p_square = malloc(sizeof(struct square));
        p_boardgame->square[i] = *p_square;

        p_boardgame->square[i].index = i+1;
        if(i==0) p_boardgame->square[i].isPlayer = true;
        else p_boardgame->square[i].isPlayer = false;
        p_boardgame->square[i].next = NULL;
    }

    // We make sure that each square have a next square (expect the last one)
    for(int i=0; i<p_boardgame->length; i++){
        // we move the cursor
        struct square *cursor = p_boardgame->head_square;
        while(cursor->next != NULL){
            cursor = cursor->next;
        }
        cursor->next = &p_boardgame->square[i];
    }
    
    return p_boardgame;
}

void print_boardgame(struct boardgame *p_boardgame){
    bool odd = false;
    int compt = 0;
    for(int i=p_boardgame->length-1; i>=0; i--){
        if(odd){
            for(int j=i-COLUMNS+1; j<=i; j++){
                printf(" %2d ",p_boardgame->square[j].index);
            }
            odd = false;
            printf("\n");
            i -= 7;
        } else {
            compt += 1;
            printf(" %2d ", p_boardgame->square[i].index);
            if(compt == 8) {
                printf("\n");
                odd = true;
                compt = 0;
            }
        }
    }
}

// simulate a die
int roll_die(){
    int result = rand() % 6 + 1; // between 1 and 6 
    return result;
}

struct snake *addSnake(struct snake *head_snake) {
    // create a space in memory for a new p_snake
    struct snake *p_snake = malloc(sizeof(struct snake));

    // esnure the data field of the node points to the data
    p_snake->next = NULL;
    p_snake->index_head = 0;
    p_snake->index_foot = 0;
    p_snake->length = rand() % 10 + 1;

    // we move the cursor
    struct snake *cursor = head_snake;
    while(cursor->next != NULL){
        cursor = cursor->next;
    }
    cursor->next = p_snake;

    // return a pointer to the new node
    return p_snake;
}

struct ladder *addLadder(struct ladder *head_ladder) {
    // create a space in memory for a new p_ladder
    struct ladder *p_ladder = malloc(sizeof(struct ladder));

    // esnure the data field of the node points to the data
    p_ladder->next = NULL;
    p_ladder->index_head = 0;
    p_ladder->index_foot = 0;
    p_ladder->length = rand() % 10 + 1;

    // we move the cursor
    struct ladder *cursor = head_ladder;
    while(cursor->next != NULL){
        cursor = cursor->next;
    }
    cursor->next = p_ladder;

    // return a pointer to the new node
    return p_ladder;
}

struct snake *init_snake(){
    struct snake *p_snake = malloc(sizeof(struct snake));
    p_snake->next = NULL;
    return p_snake;
}

struct ladder *init_ladder(){
    struct ladder *p_ladder = malloc(sizeof(struct ladder));
    p_ladder->next = NULL;
    return p_ladder;
}

// Check if the args written in the command line are correct numbers, must be around 5 to 30 snakes/ladders.
int check_args(char *argv[]) {
    int res = 0; // if 0 = all good OR if 1 = will return an error and stop the application
    if(atoi(argv[1]) < 2 || atoi(argv[1]) > 20){
        printf("Error <number_snakes> : enter a number between 2 and 20.\n");
        res = 1;
    }
    if(atoi(argv[2]) < 2 || atoi(argv[2]) > 20) {
        printf("Error <number_ladders> : enter a number between 2 and 20.\n");
        res = 1;
    }
    return res;
}

int main(int argc, char *argv[]){
    srand(time(NULL)); // to avoid always have the same value with rand()
    if (argc < 2) { // check if user gave two parameters
        printf("Error : %s <number_snakes> <number_ladders>\n", argv[0]);
        printf("--> Don't forget to enter two parameters between 2 to 20 for snakes/ladders amount.\n");  
        return 1; 
    }

    int result = check_args(argv); // check if numbers are alright to play the game
    if(result == 1) return 1; // if number of snakes/ladders not between 2 to 20 ==> exit

    FILE *file;
    file = fopen("report_game.txt","w");

    if(file == NULL)
    {
        printf("Error while creating the file !");   
        exit(1);             
    }

    int number_snakes = atoi(argv[1]); // given by the user
    int number_ladders = atoi(argv[2]); 
    // Write data to the report
    fprintf(file,"- There is %d snakes.\n- There is %d ladders.\n", number_snakes, number_ladders);

    // we create the boardgame
    struct boardgame *game = create_boardgame();
    print_boardgame(game);

    // creation of the array of snake/ladder that will contains all snakes/ladders inputed by the user
    struct snake *snakes_game[number_snakes];
    memset(&snakes_game, 0, sizeof(struct snake)); // Init the two arrays to 0

    struct ladder *ladders_game[number_ladders];
    memset(&ladders_game, 0, sizeof(struct ladder)); 

    // linked list : creation of the lists heads
    struct snake *head_snake = init_snake();
    struct ladder *head_ladder = init_ladder();

    // create each snakes and ladders into the main arrays
    for(int i=0; i<number_snakes; i++) snakes_game[i] = addSnake(head_snake); 
    for(int i=0; i<number_ladders; i++) ladders_game[i] = addLadder(head_ladder); 

    fclose(file);
    // free
}