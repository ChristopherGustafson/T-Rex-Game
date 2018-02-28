#include <stdint.h>
#include <stdlib.h>
#include <pic32mx.h>
#include "game.h"

void delay(int a){
	int i;
	for(i = 0; i < a; i++){
	}
}
/*
struct gameObject dino = {0, 0, 8, 8};
struct gameObject cactus = {0, 0, 5, 8};
*/

void startScreen(void){
	running = 1;
}
void gameOverScreen(void){
	gameOver = 0;
}


int main(void) {

	/* Code from labs */

	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
  SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;

	/* Own written code */

	/* Initiate timer */
	TMR2 = 0;
	T2CON |= (0x6 << 4);
	PR2 = 31250;
	T2CON |= 0x8000;

	display_init();

	while(1){

		while(!running){
			startScreen();
		}

		initGame();

		while(running){
			if(IFS(0)){
				IFS(0) = 0;
					tick();
					render();
			}
		}

		while(gameOver){
			gameOverScreen();
		}

	}

}
