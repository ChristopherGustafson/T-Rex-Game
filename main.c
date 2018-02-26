#include <stdint.h>
#include <stdlib.h>
#include <pic32mx.h>
#include "game.h"

void delay(int a){
	int i;
	for(i = 0; i < a; i++){
	}
}

struct gameObject dino = {0, 0, 8, 8};
struct gameObject cactus = {0, 0, 5, 8};

int running;
int collision;
int renderCount;
int gameSpeed;

int count;
uint8_t mini[] = {0x08, 0x30, 0x20, 0xf0, 0xb8, 0x1c, 0x0f, 0x13 };
uint8_t ground[] = {0x05, 0x05, 0x09, 0x01, 0x09, 0x05};
uint8_t cactusIm[] = {0x1c, 0x10, 0xfc, 0x10, 0x1c};

void initGame(void){
	gameSpeed = 1;
	running = 1;
	renderCount = 127;
	dino.x = 20;
	dino.y = 0;

	cactus.x = 120;

	count = 0;
}

void tick(void){

		//update cactus
		if(cactus.x > 0){
			cactus.x -= 2;

		}
		else{
			cactus.x = 120;
		}



	//Collision detection
	if(dino.y == cactus.y){
		int cactusMid = cactus.x + cactus.WIDTH/2;

		if(cactusMid < dino.x+dino.WIDTH && cactusMid > dino.x){
			collision = 1;
		}
	}

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
			//Draw cactus
			else if(page == 2 && col == cactus.x){
				for(t = 0; t < 5; t++){
					spi_send_recv(cactusIm[t]);
				}
				col += 4;
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
			else if(page == 0 && col > 124 && collision){

				spi_send_recv(0x0f);
			}
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
	T2CON |= (0x7 << 4);
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

					tick();
					render();

			}
		}
	}

}
