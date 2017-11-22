//-----------------------------
// Written by johvh & davidjo2.
//-----------------------------

#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

/**
 * Function to sleep X cycles.
 * @param cycles
 */
void sleep(int cycles) {
	int i;
	for(i = cycles; i > 0; i--);
}

/**
 * Send data to display buffer.
 * @param data
 */
void sendSPI(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

/**
 * Initialise display
 */
void display_init(void) {
    DISPLAY_CHANGE_TO_COMMAND_MODE;
    sleep(10);
	DISPLAY_ACTIVATE_VDD;
    sleep(1000000);

    sendSPI(0xAE);
	DISPLAY_ACTIVATE_RESET;
    sleep(10);
	DISPLAY_DO_NOT_RESET;
    sleep(10);

    sendSPI(0x8D);
    sendSPI(0x14);

    sendSPI(0xD9);
    sendSPI(0xF1);

	DISPLAY_ACTIVATE_VBAT;
    sleep(10000000);

    sendSPI(0xA1);
    sendSPI(0xC8);

    sendSPI(0xDA);
    sendSPI(0x20);

    sendSPI(0xAF);
}

void displayPixel(int x, int y) {
    sendSPI(x+y*8);
}

void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;

	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}

void display_image(int x, const uint8_t *data) {
	int i, j;

	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;

        sendSPI(0x22);
        sendSPI(i);

        sendSPI(x & 0xF);
        sendSPI(0x10 | ((x >> 4) & 0xF));

		DISPLAY_CHANGE_TO_DATA_MODE;

		for(j = 0; j < 32; j++)
            sendSPI(~data[i*32 + j]);
	}
}

void display_update(void) {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
        sendSPI(0x22);
        sendSPI(i);

        sendSPI(0x0);
        sendSPI(0x10);

		DISPLAY_CHANGE_TO_DATA_MODE;

		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;

			for(k = 0; k < 8; k++)
                sendSPI(font[c*8 + k]);
		}
	}
}
