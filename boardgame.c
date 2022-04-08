#include "boardgame.h"

FILE *file;

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
        p_boardgame->square[i].name[0] = '\0';
        p_boardgame->square[i].name[1] = '\0';
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
            printf("-----------------------------------------\n| "); fprintf(file,"-----------------------------------------\n| ");
            for(int j=i-COLUMNS+1; j<=i; j++){
                if(j >= 0) {
                    printf("%02d | ",p_boardgame->square[j].index);
                    fprintf(file,"%02d | ", p_boardgame->square[j].index);
                } else {
                    printf("-- | "); fprintf(file,"-- | ");
                }
            }
            odd = false;
            printf("\n| "); fprintf(file,"\n| ");

            // we display if the square is a snake/ladder head/foot
            for(int j=i-COLUMNS+1; j<=i; j++){
                if(j >= 0) {
                    if(p_boardgame->square[j].name[0] == '\0') {
                        printf("   | "); fprintf(file,"   | ");
                    } else {
                        printf("%c%c | ", p_boardgame->square[j].name[0], p_boardgame->square[j].name[1]);
                        fprintf(file,"%c%c | ", p_boardgame->square[j].name[0], p_boardgame->square[j].name[1]);
                    }      
                }
                else {
                    printf("-- | ");
                    fprintf(file,"-- | ");
                }
            }
            printf("\n| "); fprintf(file,"\n| ");

            // We display the player location : 
            for(int j=i-COLUMNS+1; j<=i; j++){
                if(j >= 0) {
                    if(p_boardgame->square[j].isPlayer) { printf("\033[0;34mXX\033[0m | "); fprintf(file,"XX | ");}
                    else {printf("   | "); fprintf(file,"   | ");}
                }
                else {
                    printf("   | ");
                    fprintf(file,"   | ");
                }
            }
            printf("\n"); fprintf(file,"\n");
        } else {
            int temp = i;
            printf("-----------------------------------------\n| "); fprintf(file,"-----------------------------------------\n| ");
            for(int j=i; j>temp-8; j--){
                if(j >= 0) {
                    printf("%02d | ", p_boardgame->square[j].index);
                    fprintf(file,"%02d | ", p_boardgame->square[j].index);
                } else {
                    printf("-- | "); fprintf(file,"-- | ");
                }
            }
            printf("\n| "); fprintf(file,"\n| ");

            // we display if the square is a snake/ladder head/foot
            for(int j=i; j>temp-8; j--){
                if(j >= 0) {
                    if(p_boardgame->square[j].name[0] == '\0') {
                        printf("   | "); fprintf(file,"   | ");
                    } else {
                        printf("%c%c | ", p_boardgame->square[j].name[0], p_boardgame->square[j].name[1]);
                        fprintf(file,"%c%c | ", p_boardgame->square[j].name[0], p_boardgame->square[j].name[1]);
                    }      
                }
                else {
                    printf("-- | "); fprintf(file,"-- | ");
                }
            }
            printf("\n| "); fprintf(file,"\n| ");

            // We display the player location : 
            for(int j=i; j>temp-8; j--){
                if(j >= 0) {
                    if(p_boardgame->square[j].isPlayer) { printf("\033[0;34mXX\033[0m | ");  fprintf(file,"XX | ");}
                    else {printf("   | "); fprintf(file,"   | ");}
                }
                else {
                    printf("   | "); fprintf(file,"   | ");
                }
            }
            printf("\n"); fprintf(file,"\n");
            odd = true;
        }
        i -= 8;
    }
    printf("-----------------------------------------\n"); fprintf(file,"-----------------------------------------\n\n");
}

// simulate a die
int roll_die(){
    int result = rand() % 6 + 1; // between 1 and 6 
    return result;
}

// return a random number between a specific range when we're 6 squares close to the end of gameboard
int random_length(int range){
    int result = rand() % range + 1; // between 10 and 1
    return result;
}

void getRandomHead(struct boardgame *boardgame, void *data, char letter[2], int *random_head, bool isSnake){
    int temp = 0;
    while(1) {
        // we need to change the position of the head if no place available
        if(temp>=8) { 
            getRandomHead(boardgame, data, letter, random_head, isSnake);
            temp = 0;
        } 

        struct square *cursor_square = boardgame->head_square;
        *random_head = rand() % (boardgame->length-2) + 2; // from square 2 to n-1
        while(cursor_square->index != *random_head){ // Seek the index of the random number in our array of square
            cursor_square = cursor_square->next;
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

        temp += 1;
    }
}

// when we change the head index, we need to update the index of the head to NULL in his square
void resetHeadIndex(struct boardgame *boardgame, int *random_head, bool isSnake){
    struct square *cursor_square = boardgame->head_square;
    while(cursor_square->index != *random_head){ // Seek the index of the random number in our array of square
        cursor_square = cursor_square->next;
    }
    if(isSnake) { // if true = means that we take care of snakes 
        cursor_square->isSnake = NULL; // we point to our snake
        cursor_square->isSnake->index_head = NULL;
    } else { // if false = means that we take care of ladder 
        cursor_square->isLadder = NULL; // we point to our snake
        cursor_square->isLadder->index_head = NULL;
    }
}

int getRandomFoot(struct boardgame *boardgame, void *data, char letter[2], char letterHead[2], int *random_head, bool isSnake){
    int temp = 0;
    int tempTen = 0;
    int random_foot;
    while(1) {
        if(tempTen==(*random_head-2) || temp>=8) { // we need to change the position of the head if no place available
            resetHeadIndex(boardgame, random_head, isSnake);
            getRandomHead(boardgame, data, letterHead, random_head, isSnake);
            tempTen = 0; temp = 0;
        }

        struct square *cursor_square = boardgame->head_square; // we re-init our variable
        if(*random_head<=10) {
            random_foot = 2 + rand() % (*random_head-2); // from square 2 to random_head-1
            tempTen += 1;
        } else {
            random_foot = (*random_head-10) + rand() % 10; // from square head-1 to -10
        }

        while(cursor_square->index != random_foot){ // Seek the index of the random number in our array of square
            cursor_square = cursor_square->next;
        }

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

        temp+=1;
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

struct square *getSquare(struct boardgame *boardgame, int index){
    // we seek the square thanks to the index
    struct square *cursor_square = boardgame->head_square; 
    while(cursor_square->index != index){ // Seek the index of the random number in our array of square
        if(cursor_square->next == NULL) { break;}
        cursor_square = cursor_square->next;
    }
    return cursor_square;
}

void launch_game(struct boardgame *boardgame) {
    print_boardgame(boardgame);
    int round = 1;
    // we seek the square where is located the player now
    struct square *actual_square = boardgame->head_square;
    while(!actual_square->isPlayer){ // While we're not in the square where the player is located we move on
        actual_square = actual_square->next;
    }
    struct square *new_square = actual_square;

    // while the player is not in the last square, we continue the game
    while(new_square->next != NULL) {
        actual_square = new_square;
        actual_square->isPlayer = false; // we remove the player from the square

        // wait user to roll a die: 
        printf("--> Press enter to roll the die... ");
        char enter = 0;
        while (enter != '\r' && enter != '\n') { enter = getchar(); }
        system("@cls||clear"); // clear terminal
        printf("-----------------ROUND %02d----------------\n\n", round); fprintf(file,"-----------------ROUND %02d----------------\n\n", round);

        // roll the die (check if we're 6 squares close to the end)
        int range = boardgame->length-actual_square->index;
        int index_player = 0;
        if(range < 6) {  index_player = random_length(range); } 
        else { index_player = roll_die(range); }
        
        printf("--> Result of the die rolled : %d\n", index_player);
        fprintf(file,"--> Result of the die rolled : %d\n", index_player);

        index_player += actual_square->index;

        printf("--> You're moving to the square %d ...\n", index_player);
        fprintf(file,"--> You're moving to the square %d ...\n", index_player);

        // we seek the new square where the player will be
        new_square = getSquare(boardgame, index_player);

        if(new_square->isSnake != NULL) {
            if(new_square->isSnake->index_head != NULL && new_square->isSnake->index_head->index == index_player) {
                // we get the length to move backwards
                int decrease_length = new_square->isSnake->length; 
                printf("--> Oh no... You landed on the head of a snake. You're going to move backwards to the square %d.\n", index_player-decrease_length);
                fprintf(file,"--> Oh no... You ended on the head of a snake. You're going to move backwards to the square %d.\n", index_player-decrease_length);
                new_square = getSquare(boardgame, index_player-decrease_length);
            }
        } else if (new_square->isLadder != NULL && new_square->isLadder->index_foot->index == index_player) {
            if(new_square->isLadder->index_foot != NULL) {
                // we get the length to move forwards
                int increase_length = new_square->isLadder->length; 
                printf("--> Oh yes ! You landed on the foot of a ladder. You're going to move forwards to the square %d.\n", index_player+increase_length);
                fprintf(file,"--> Oh yes ! You landed on the foot of a ladder. You're going to move forwards to the square %d.\n", index_player+increase_length);
                new_square = getSquare(boardgame, index_player+increase_length);
            }
        }

        // change text when we move the player
        new_square->isPlayer = true;
        print_boardgame(boardgame);
        round++;
    }

    printf("Congrats, you finished the game in %d rounds ! ", round);
    fprintf(file,"Congrats, you finished the game in %d rounds ! ", round);
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
    system("@cls||clear"); // clear terminal
    if (argc < 2) { // check if user gave two parameters
        printf("Error : %s <number_snakes> <number_ladders>\n", argv[0]);
        printf("--> Don't forget to enter two parameters between 2 to 6 for snakes/ladders amount.\n");  
        return 1; 
    }

    int result = check_args(argv); // check if numbers are alright to play the game
    if(result == 1) return 1; // if number of snakes/ladders not between 2 to 20 ==> exit

    file = fopen("report_game.txt","w");

    if(file == NULL)
    {
        printf("Error while creating the file !");   
        exit(1);             
    }

    int number_snakes = atoi(argv[1]); // given by the user
    int number_ladders = atoi(argv[2]); 

    // Write data to the report
    printf("WELCOME TO THE SNAKES AND LADDERS GAME !\n\n --> Some details below :\n");
    fprintf(file, "WELCOME TO THE SNAKES AND LADDERS GAME !\n\n --> Some details below :\n");
    printf("\t - You choose %d snakes and %d ladders.\n", number_snakes, number_ladders);
    fprintf(file,"\t - You choose %d snakes and %d ladders.\n", number_snakes, number_ladders);
    printf("\t - Meaning of the gameboard :\n\t   - SH: Sneak Head and SF = Snake Foot\n\t   - LH: Ladder Head and LF: Ladder Foot\n\t   - XX: Location of the player\n\n");
    fprintf(file, "\t - Meaning of the gameboard :\n\t   - SH: Sneak Head and SF = Snake Foot\n\t   - LH: Ladder Head and LF: Ladder Foot\n\t   - XX: Location of the player\n\n");
    time_t now = time(NULL);
    printf("\t - Game played at : %s \n", ctime(&now));
    fprintf(file, "\t - Game played at : %s \n", ctime(&now));

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

    launch_game(game);

    fclose(file);
    for(int i=0; i<number_snakes; i++){
        free(snakes_game[i]);
    }
    for(int i=0; i<number_ladders; i++){
        free(ladders_game[i]);
    }
    free(head_snake);
    free(head_ladder);
    free(game);
}