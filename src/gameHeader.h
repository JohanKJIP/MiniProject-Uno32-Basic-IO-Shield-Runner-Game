/*  Header file for game functions */

/* Display-related functions from displayUtil.c */
void displayPixel(int x, int y);
void displayHex(int x, int line, int value);
void display_init(void);
void display_update(void);
void sleep(int);

/* Functions from utils.c */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);

/* Functions from Main.c */
void updateRunning(int);
void updateMainMenu(int);
extern int GAMESTATE;

/* Functions from gameRunning.c */
int getRandomInt(int);

/* Functions from entityHandler */
void entities_update(void);
