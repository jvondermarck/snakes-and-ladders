#include "boardgame.h"

struct square *init_square() {
    struct square *p_square = malloc(sizeof(struct square));
    p_square->index = 0;
    p_square->isPlayer = false; 
    p_square->next = NULL;
    return p_square;
}

// create a boardgame randomly of size 32 to 64
struct boardgame *create_boardgame(){
    int mod = (MAX_SIZE-MIN_SIZE)+1; // to be between 32 and 64 
    int length = rand() % mod + MIN_SIZE; // between 32 and 64 randomly

    struct boardgame *p_boardgame = malloc(sizeof(struct boardgame));
    p_boardgame->length = length;

    // linked list : creation of the list head of square
    struct square *head_square = init_square();
    p_boardgame->head_square = malloc(sizeof(struct square));
    p_boardgame->head_square = head_square;

    // Creation of N squares depending of the length of the gameboard drawn at random
    p_boardgame->square = malloc(length * sizeof(struct square));
    for(int i=0; i<p_boardgame->length; i++){
        struct square *p_square = malloc(sizeof(struct square));
        p_boardgame->square[i] = *p_square; // Init square
        p_boardgame->square[i].index = i+1; // Number of the square
        p_boardgame->square[i].isSnake = NULL; // Init to NULL because it doesn't have a snake yet
        p_boardgame->square[i].isLadder = NULL;
        memset(p_boardgame->square[i].name, '\0', sizeof(char)*2); 
        p_boardgame->square[i].next = NULL; // Next square as null 
        if(i==0) p_boardgame->square[i].isPlayer = true; // We place the player at the 1st square
        else p_boardgame->square[i].isPlayer = false;
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
    int i = p_boardgame->length-1;
    while(i >= 0) {
        if(odd){
            printf("-----------------------------------------\n| ");

            for(int j=i-COLUMNS+1; j<=i; j++){
                if(j >= 0)
                    printf("%02d | ",p_boardgame->square[j].index);
                else {
                    printf("-- | ");
                }
            }
            odd = false;
            printf("\n| ");
            for(int j=i-COLUMNS+1; j<=i; j++){
                if(j >= 0) {
                    if(p_boardgame->square[j].name[0] == '\0') {
                        printf("   | ");
                    } else {
                        printf("%s | ", p_boardgame->square[j].name);
                    }      
                }
                else {
                    printf("-- | ");
                }
            }
            printf("\n| ");
            for(int j=i-COLUMNS+1; j<=i; j++){
                if(j >= 0) {
                    if(p_boardgame->square[j].isPlayer) { printf("XX | "); }
                    else {printf("   | ");}
                }
                else {
                    printf("   | ");
                }
            }
            printf("\n");
        } else {
            int temp = i;
            printf("-----------------------------------------\n| ");
            for(int j=i; j>temp-8; j--){
                if(j >= 0)
                    printf("%02d | ", p_boardgame->square[j].index);
                else {
                    printf("-- | ");
                }
            }
            printf("\n| ");
            for(int j=i; j>temp-8; j--){
                if(j >= 0) {
                    if(p_boardgame->square[j].name[0] == '\0') {
                        printf("   | ");
                    } else {
                        printf("%s | ", p_boardgame->square[j].name);
                    }      
                }
                else {
                    printf("-- | ");
                }
            }
            printf("\n| ");
            for(int j=i; j>temp-8; j--){
                if(j >= 0) {
                    if(p_boardgame->square[j].isPlayer) { printf("XX | "); }
                    else {printf("   | ");}
                }
                else {
                    printf("   | ");
                }
            }
            printf("\n");
            odd = true;
        }
        i -= 8;
    }
    printf("-----------------------------------------\n");
}

// simulate a die
int roll_die(){
    int result = rand() % 6 + 1; // between 1 and 6 
    return result;
}

// return a random number between 1 to 10 for the length between the head to the bottom of a snake/tail
int random_length(int range){
    int result = rand() % range + 1; // between 10 and 1
    return result;
}

void getRandomHead(struct boardgame *boardgame, void *data, char letter[2], int *random_head, bool isSnake){
    int temp = 1;
    while(1) {
        bool breakLoop = false;
        struct square *cursor_square = boardgame->head_square;
        *random_head = rand() % (boardgame->length-2) + 2; // from square 2 to n-1
        while(cursor_square->index != *random_head){ // Seek the index of the random number in our array of square
            if(cursor_square->next == NULL) {  breakLoop = true; break;}
            cursor_square = cursor_square->next;
        }
        if(breakLoop) break;

        temp += 1;
        if(temp>=10) { // we need to change the position of the head if no place available
            getRandomHead(boardgame, data, letter, random_head, isSnake);
            temp = 0;
        } 
        if(cursor_square->isSnake == NULL && cursor_square->isLadder == NULL){
            if(isSnake) { // if true = means that we take care of snakes 
                cursor_square->isSnake = data;
                cursor_square->isSnake->index_head = cursor_square;
                cursor_square->isSnake->index_head->name[0] = letter[0];
                cursor_square->isSnake->index_head->name[1] = letter[1];
            } else { // if false = means that we take care of ladder 
                cursor_square->isLadder = data;
                cursor_square->isLadder->index_head = cursor_square;
                cursor_square->isLadder->index_head->name[0] = letter[0];
                cursor_square->isLadder->index_head->name[1] = letter[1];
            }
           
           break;
        }
    }
}

int getRandomFoot(struct boardgame *boardgame, void *data, char letter[2], char letterHead[2], int *random_head, bool isSnake){
    int temp = 0;
    int tempTen = 0;
    int random_foot;
    while(1) {
        bool breakLoop = false;
        struct square *cursor_square = boardgame->head_square; // we re-init our variable
        if(*random_head<=10) {
            random_foot = 2 + rand() % (*random_head-1); // from square 2 to random_head-1
            tempTen += 1;
        } else {
            random_foot = (*random_head-10) + rand() % 10; // from square head-1 to -10
        }

        temp+=1;

        if(tempTen==*random_head || temp>=10) { // we need to change the position of the head if no place available
            getRandomHead(boardgame, data, letterHead, random_head, isSnake);
            tempTen = 0; temp = 0;
        }  

        while(cursor_square->index != random_foot){ // Seek the index of the random number in our array of square
             if(cursor_square->next == NULL) {  breakLoop = true; break;}
             cursor_square = cursor_square->next;
        }

        if(breakLoop) { getRandomHead(boardgame, data, letterHead, random_head, isSnake); tempTen = 0; temp = 0;}

        if(cursor_square->isSnake == NULL && cursor_square->isLadder == NULL){
            if(isSnake) { // if true = means that we take care of snakes 
                cursor_square->isSnake = data; // we point to our snake
                cursor_square->isSnake->index_foot = cursor_square;
                cursor_square->isSnake->index_foot->name[0] = letter[0];
                cursor_square->isSnake->index_foot->name[1] = letter[1];
            } else { // if false = means that we take care of ladder 
                cursor_square->isLadder = data; // we point to our snake
                cursor_square->isLadder->index_foot = cursor_square;
                cursor_square->isLadder->index_foot->name[0] = letter[0];
                cursor_square->isLadder->index_foot->name[1] = letter[1];
            }
           
           break;
        }
    }
    return random_foot;
}

struct snake *addSnake(struct snake *head_snake, struct boardgame *boardgame) {
    // create a space in memory for a new p_snake
    struct snake *p_snake = malloc(sizeof(struct snake));

    // Taking care of looking a place to put on a square to put the head of snake
    int random_head, random_foot = 0;
    int *p_random_head = &random_head;
    char letterHead[2] = "SH";
    char letterFoot[2] = "SF";
    getRandomHead(boardgame, p_snake, letterHead, p_random_head, true);

    // Look for a place to put the foot of a snake
    random_foot = getRandomFoot(boardgame, p_snake, letterFoot, letterHead, p_random_head, true);

    printf("Snake : Head = %d and Foot = %d\n", p_snake->index_head->index, p_snake->index_foot->index);
    
    p_snake->length = random_head-random_foot;
    p_snake->next = NULL;

    struct snake *cursor = head_snake; // init cursor to move different each square
    while(cursor->next != NULL){
        cursor = cursor->next;
    }
    cursor->next = p_snake;

    // return a pointer to the new node
    return p_snake;
}

struct ladder *addLadder(struct ladder *head_ladder, struct boardgame *boardgame) {
    // create a space in memory for a new p_ladder
    struct ladder *p_ladder = malloc(sizeof(struct ladder));

    // Taking care of looking a place to put on a square to put the head of snake
    int random_head, random_foot = 0;
    int *p_random_head = &random_head;
    char letterHead[2] = "LH";
    char letterFoot[2] = "LF";

    getRandomHead(boardgame, p_ladder, letterHead, p_random_head, false);
    random_foot = getRandomFoot(boardgame, p_ladder, letterFoot, letterHead, p_random_head, false);

    p_ladder->length = random_head-random_foot;

    printf("Ladder : Head = %d and Foot = %d\n", p_ladder->index_head->index, p_ladder->index_foot->index);

    // we move the cursor
    p_ladder->next = NULL;
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
    p_snake->index_head = NULL;
    p_snake->index_foot = NULL;
    p_snake->next = NULL;
    return p_snake;
}

struct ladder *init_ladder(){
    struct ladder *p_ladder = malloc(sizeof(struct ladder));
    p_ladder->index_head = NULL;
    p_ladder->index_foot = NULL;
    p_ladder->next = NULL;
    return p_ladder;
}

// Check if the args written in the command line are correct numbers, must be around 5 to 30 snakes/ladders.
int check_args(char *argv[]) {
    int res = 0; // if 0 = all good OR if 1 = will return an error and stop the application
    if(atoi(argv[1]) < 2 || atoi(argv[1]) > 7){
        printf("Error <number_snakes> : enter a number between 2 and 7.\n");
        res = 1;
    }
    if(atoi(argv[2]) < 2 || atoi(argv[2]) > 7) {
        printf("Error <number_ladders> : enter a number between 2 and 7.\n");
        res = 1;
    }
    return res;
}

int main(int argc, char *argv[]){
    srand(time(NULL)); // to avoid always have the same value with rand()
    if (argc < 2) { // check if user gave two parameters
        printf("Error : %s <number_snakes> <number_ladders>\n", argv[0]);
        printf("--> Don't forget to enter two parameters between 2 to 7 for snakes/ladders amount.\n");  
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

    // creation of the array of snake/ladder that will contains all snakes/ladders inputed by the user
    struct snake *snakes_game[number_snakes];
    memset(&snakes_game, 0, sizeof(struct snake)); // Init the two arrays to 0

    struct ladder *ladders_game[number_ladders];
    memset(&ladders_game, 0, sizeof(struct ladder)); 

    // linked list : creation of the lists heads
    struct snake *head_snake = init_snake();
    struct ladder *head_ladder = init_ladder();

    // create each snakes and ladders into the main arrays
    for(int i=0; i<number_snakes; i++) snakes_game[i] = addSnake(head_snake, game); 
    for(int i=0; i<number_ladders; i++) ladders_game[i] = addLadder(head_ladder, game); 

    print_boardgame(game);

    fclose(file);
    // free
}