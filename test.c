#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // for srand()
#include <stdbool.h>

int main(int argc, char *argv[]){
    srand(time(NULL));
    while(1){
        // int nbr = 20 + rand() % 10; // for [20, 30]
        //int nbr = 2 + rand() % (5-2); // for [1, 10]
        int nbr = rand() % 3 + 1;
        // int nbr = rand() % (6-2) + 2;
        printf(" %d \n", nbr);
    }
}