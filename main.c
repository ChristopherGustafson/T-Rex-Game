#include <stdint.h>
#include <stdlib.h>
#include <pic32mx.h>
#include "game.h"


void delay(int a){
	int i;
	for(i = 0; i < a; i++){
	}
}


int running;
int renderCount;
int gameSpeed;

int dinoX;
int dinoY;


int cactusX;
uint8_t mini[] = {0x08, 0x30, 0x20, 0xf0, 0xb8, 0x1c, 0x0f, 0x13 };
uint8_t ground[] = {0x05, 0x05, 0x09, 0x01, 0x09, 0x05};
uint8_t cactus[] = {0x1c, 0x10, 0xfc, 0x10, 0x1c};

void initGame(void){
	dinoY = 0;
	dinoX = 20;
	gameSpeed = 1;
	running = 1;
	cactusX = 125;
	renderCount = 127;

	gameObject dino = {10, 10};
	dino.x = 10;

}

void tick(void){
}

void render(void){

	int page, col, t;

	for(page = 0; page < 4; page++){
		for(col = 0; col < 128; col++){

			//Draw dino
			if(page == 2 && col == dino.x){
				for(t = 0; t < 8; t++){
					spi_send_recv(mini[t]);
				}
				col += 7;
			}
			// Draw ground
			else if(page == 3){
				if(col < renderCount+5 && col > renderCount-5)
					spi_send_recv(0x25);
				else if(col < renderCount+40 && col > renderCount+35)
					spi_send_recv(0x19);
				else
					spi_send_recv(0x01);
			}
			// If nothing is drawn, draw black
			else{
				spi_send_recv(0x00);
			}
		}
	}

	if(renderCount == -40)
		renderCount = 127;
	else
		renderCount--;

}

void renderStartScreen(void){




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
	T2CON |= (0x3 << 4);
	PR2 = 31250;
	T2CON |= 0x8000;

	display_init();

	while(1){

		initGame();
		while(!running){
			renderStartScreen();
		}

		while(running){

			if(IFS(0)){
				IFS(0) = 0;

					render();
					tick();

			}
		}
	}

}
