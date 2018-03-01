//#include <stdio.h> Tog bort för att få rand att fungera
#include <stdint.h>
#include <stdlib.h>
#include <pic32mx.h>
#include "game.h"
#include "standard.h"

void delay(int a){
	int i;
	for(i = 0; i < a; i++){
	}
}

/* Global variables */
int running;
int renderCount;
int gameSpeed;
int dinoX;
int dinoY;
int hopp;
int cactusX;
int jump;
int fall;
int col0;
int col1;
int col2;
int cac;
int belowDino;
int dinocac;
int h;
int height;
int btnPressed;
int t;
uint8_t mini[] = {0x08, 0x30, 0x20, 0xf0, 0xb8, 0x1c, 0x0f, 0x13};
uint8_t ground[] = {0x05, 0x05, 0x09, 0x01, 0x09, 0x05};
uint8_t cactus[] = {0x1c, 0x10, 0xfc, 0x10, 0x1c};
void initGame(void){
	t = 0;
	btnPressed = 0;
	height = 15;
	h = 0;
	dinocac = 0;
	belowDino = 0;
	cac = 0;
	col0 = 0;
	col1 = 0;
	col2 = 0;
	fall = 0;
	jump = 0;
	dinoY = 0;
	dinoX = 20;
	gameSpeed = 1;
	running = 1;
	cactusX = 125;
	renderCount = 127;
}

void tick(void)
{

}

void render(void){

	int page, col, t;

	for(page = 0; page < 4; page++){
		for(col = 0; col < 128; col++){


			if(btnPressed == 0)
			{
				t++;
				if(t == 32000)
				{
					t = 0;
				}
			}
			if(btnPressed == 1)
			{
				srand((unsigned) t);
			}


			//Draw dino
			if((page == 2) && (col == dinoX) && (!jump))
			{
				for(t = 0; t < 8; t++)
				{
					/*
					if(((t + cactusX) < (dinoX + 7)) && ((t + cactusX) > dinoX))
					{
							spi_send_recv(cactus[h] | mini[t]);
							h++;
					}
					else
					*/


						spi_send_recv(mini[t]);
				}
				h = 0;
				//Problem... Skips 7 columns when dino and cactus touch which
				//means cactus will not be printed since col jumps over cactusX
				col += 7;
			}

			//Make dino jump
			else if(((PORTD >> 7) || jump) && (page == 0) && (col == dinoX))
			{
				btnPressed = 1;
				delay(1000);
				jump = 1;
				//dino written to page 0
				if(dinoY > 7)
				{
					for(col0 = 0; col0 < 8; col0++)
					{
						spi_send_recv(mini[col0] << (height - dinoY));
					}
				}
				col += 7;
			}

			else if(/*((PORTD >> 7) ||*/ (jump) && (page == 1) && (col == dinoX))
			{
				delay(1000);
				//Stops standard printing of dino
				//jump = 1; //Gammalt

				//Dino written to first page
				if(dinoY > 0 && dinoY < 8)
				for(col1 = 0; col1 < 8; col1++)
				{
					// Skitandet i bitar är fel här
					spi_send_recv(mini[col1] << (height - dinoY - 7));
				}
				col += 7;
			}

			else if(jump && (page == 2) && (col == dinoX))
				{
					delay(1000);
					//Dino written to second page
					for(col2 = 0; col2 < 8; col2++)
					{
						spi_send_recv(mini[col2] >> (1 + dinoY));
					}
					col += 7;
					//Max height reached, tell dino to start falling
					if(dinoY == height)
					{
						fall = 1;
					}
					//If max height has not been reached, dino will keep rising
					if(!fall)
					{
						dinoY++;
					}
					//If max height has been reached, dino will start falling
					if(fall)
					{
						dinoY--;
					}
					//When dinoY is 0 again jump is done
					if(!dinoY)
					{
						jump = 0;
						fall = 0;
					}
				}
			//draw cactus
			/*
			else if((page == 2) && (col == cactusX))
			{
				for(cac = 0; cac < 5; cac++)
				{
					if(((cactusX + cac) > dinoX) || (cactusX + cac) < dinoX)
					spi_send_recv(cactus[cac]);
				}
				col += 4;
			}
			*/

			// Draw ground
			else if(page == 3)
			{
				delay(2000);
				if(col < renderCount+5 && col > renderCount-5)
					spi_send_recv(0x25);
				else if(col < renderCount+40 && col > renderCount+35)
					spi_send_recv(0x19);
				else
					spi_send_recv(0x1);
			}
			else if((PORTD >> 6) & 0x1)
			{
				main();
			}
			// If nothing is drawn, draw black
			else
			{
				spi_send_recv(0x00);
			}

		}
	}
	//cactusX värde
	/*
	if(cactusX == -4)
	{
		cactusX = 125;
	}
	else if(cactusX == dinoX+8)
	{
		belowDino = 1;
	}
	else if(cactusX == dinoX-5)
	{
		belowDino = 0;
	}
		cactusX--;
		*/


		//rendercount värde
	if(renderCount == -40)
	{
		renderCount = 127;
	}
	else
	{
		renderCount--;
	}




}

int main(void) {

	/*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/

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

	/* Initiate timer */
	TMR2 = 0;
	T2CON |= (0x3 << 4);
	PR2 = 31250;
	T2CON |= 0x8000;

	//input


	display_init();

	while(1){

		initGame();

		while(running){

			if(IFS(0)){
				IFS(0) = 0;

					render();
					tick();

			}
		}
	}

}
