#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Check if the args written in the command line are correct numbers, must be around 5 to 30 snakes/ladders.
int check_args(char *argv[]) {
    int res = 0; // if 0 = all good OR if 1 = will return an error and stop the application
    if(atoi(argv[1]) < 2 || atoi(argv[1]) >= 20){
        printf("Error <number_snakes> : enter a number between 2 and 20.\n");
        res = 1;
    }
    if(atoi(argv[2]) < 2 || atoi(argv[2]) >= 20) {
        printf("Error <number_ladders> : enter a number between 2 and 20.\n");
        res = 1;
    }
    return res;
}

int main(int argc, char *argv[]){
    if (argc != 2) { // check if user gave two parameters
        printf("Error : %s <number_snakes> <number_ladders>\n", argv[0]);
        printf("--> Don't forget to enter two parameters between 2 to 20 for snakes/ladders amount.\n");  
        return 1; 
    }

    int result = check_args(argv); // check if numbers are alright to play the game
    if(result == 1) return 1; // if number of snakes/ladders not between 2 to 20 ==> exit

    int number_snakes = atoi(argv[1]); // given by the user
    int number_ladders = atoi(argv[2]); 

}