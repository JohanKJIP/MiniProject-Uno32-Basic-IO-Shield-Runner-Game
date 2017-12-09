/* gameHighScores.c
   Written by johvh & davidjo2.
*/

#include <stdint.h>
#include "gameHeader.h"

int HIGH_SCORE_1 = 0;
int HIGH_SCORE_2 = 0;
int HIGH_SCORE_3 = 0;

/* evaluate whether score is new high score */
void evalueteScore(void){
    switch(DIFFICULTY){
        case 4:
            if(SCORE > HIGH_SCORE_1) HIGH_SCORE_1 = SCORE;
            break;
        case 8:
            if(SCORE > HIGH_SCORE_2) HIGH_SCORE_2 = SCORE;
            break;
        case 16:
            if(SCORE > HIGH_SCORE_3) HIGH_SCORE_3 = SCORE;
            break;
    }
}

/* Display content of high score screen */
void highScoresScreen(){
    /* Display high scores */
    displayString(30, 1, "High Scores");  //Preliminary values
	displayString(20, 2, "1: ");
	displayDigit(36, 2, HIGH_SCORE_1);
    displayString(52, 2, "2: ");
    displayDigit(68, 2, HIGH_SCORE_2);
    displayString(84, 2, "3: ");
    displayDigit(100, 2, HIGH_SCORE_3);

    //TODO create additional monster animation
}

/* Update the high score screen */
void updateHighScores(){
    highScoresScreen();
    display_update();
    if(getbtns() != 0 && getbtns() != 8){
        GAMESTATE = 1;
    }
}
