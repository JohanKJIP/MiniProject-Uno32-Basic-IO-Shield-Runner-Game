/*  Header file for game functions */

/* Display-related functions from displayUtil.c */
void displayPixel(int, int);
void displayHex(int,int,int);
void display_init(void);
void display_update(void);
void displayString(int,int,char*);
void displayDigit(int,int,int);
void sleep(int);
uint8_t dataArray[512];

/* Functions from utils.c */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);

/* Functions from Main.c */
void updateRunning();
void updateMainMenu();
void updateGameOver();
extern int GAMESTATE;
extern int DIFFICULTY;
extern int SCORE;

/* Functions from gameRunning.c */
int getRandomInt(int);

/* Functions from entityHandler */
void entities_update(void);
