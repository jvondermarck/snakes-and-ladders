#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // for srand()
#include <stdbool.h>

int main(int argc, char *argv[]){
    srand(time(NULL));
    while(1){
        // int nbr = 20 + rand() % 10; // for [20, 30]
        int nbr = 2 + rand() % 9; // for [1, 10]
        printf(" %d \n", nbr);
    }
}