//Victor Tran 10/3/22
//CIS2017 Lab7: Race
//The purpose of this program is to simulate and display the race between the tortoise and the hare using a random number
//generator and preset move types. The animal positions are accessed and modified using pointers, and the display is
//controlled using the sleep() function. Sometimes it takes a while due to slippage.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define INT_MIN 1
#define INT_MAX 10

//Function prototypes.
int randomNumberGenerator();
void tortMove(int *tPtr);
void hareMove(int *hPtr);
void printRace(int hPos,int tPos);
int min(int hMin, int tMin);

int main(){
    srand((unsigned)time(NULL));

    int hPos = 1;						//hare start position is 1, cannot slip past 1
    int tPos = 1;						//tortoise start position is 1, cannot slip past 1

    puts("\tON YOUR MARK, GET SET");
    puts("\tBANG               !!!!");	//the spacing is modeled after the sample
    puts("\tAND THEY'RE OFF    !!!!");	//the spacing is modeled after the sample

    //Simulates the race.
    while(hPos < 70 && tPos < 70){
        sleep(1);						//slows down the race
        hareMove(&hPos);
        tortMove(&tPos);
        printRace(hPos,tPos);
        puts("");
    }

    //Print out the result of the race.
    if(hPos == 70 && tPos == 70) {
        printf("\tIt's a tie.\n");
    }
    else if(hPos == 70) {
        printf("\tHare wins. Yuch.\n");
    }
    else if(tPos == 70) {
        printf("\tTORTOISE WINS!!! YAY!!!\n");
    }
}

//Prints the position of the H and T
void printRace(int hPos,int tPos){
    printf("\t");
    //This array represents the 70 positions along the race track.
    char race[70];
    for(size_t i = 0; i < 70; i++) {
        race[i] = ' ';
    }

    //For the case where the tortoise and hare are at the same position
    if(hPos == tPos) {
        //Puts "OUCH!!!" starting at the position where the tortoise and the hare meet.
        char *ouch = "OUCH!!!";
        int i = hPos - 1;
        while(*ouch != '\0') {
            race[i] = *ouch;
            *ouch++;
            i++;
        }

        for(size_t i = 0; i < 70; i++) {
            printf("%c", race[i]);
        }
    }
    //For the case where the tortoise and the hare are not at the same position
    else {
        race[hPos-1] = 'H';
        race[tPos-1] = 'T';

        for(size_t i = 0; i < 70; i++) {
            printf("%c", race[i]);
        }
    }
}

//Controls the tortoise movement
void tortMove(int *tPtr){
    //Generates the random number to determine the movement of the tortoise.
    int determineMove = randomNumberGenerator();

    //Tortoise does a fast plod 50% of the time.
    if(determineMove >= 1 && determineMove <= 5) {
        if(*tPtr + 3 > 70) {
            *tPtr = 70;
        }
        else {
            *tPtr += 3;
        }
    }
    //Tortoise has a slip 20% of the time.
    else if(determineMove == 6 || determineMove == 7) {
        if(*tPtr - 6 < 1) {
            *tPtr = 1;
        }
        else {
            *tPtr -= 6;
        }
    }
    //Tortoise does a slow plod 30% of the time.
    else if(determineMove >= 8 && determineMove <= 10){
        *tPtr += 1;
    }
}

//Controls the hare movement
void hareMove(int *hPtr){
    //Generates the random number to determine the movement of the hare.
    int determineMove = randomNumberGenerator();

    //Hare sleeps 20% of the time. If determineMove = 1 or 2, no need to do anything.
    //Hare takes a big hop 20% of the time.
    if(determineMove == 3 || determineMove == 4) {
        if(*hPtr + 9 > 70) {
            *hPtr = 70;
        }
        else {
            *hPtr += 9;
        }
    }
    //Hare has a big slip 10% of the time.
    else if(determineMove == 5){
        if(*hPtr - 12 < 1) {
            *hPtr = 1;
        }
        else {
            *hPtr -= 12;
        }
    }
    //Hare takes a small hop 30% of the time.
    else if(determineMove >= 6 || determineMove <= 8) {
        *hPtr += 1;
    }
    //Hare has a small slip 20% of the time.
    else if(determineMove == 9 || determineMove == 10){
        if(*hPtr - 2 < 1) {
            *hPtr = 1;
        }
        else {
            *hPtr -= 2;
        }
    }
}

//Generates random number from 1-10
int randomNumberGenerator(){
    return rand() % (INT_MAX) + INT_MIN;
}
