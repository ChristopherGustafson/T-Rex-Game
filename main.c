#include <stdint.h>
#include <pic32mx.h>



int main(void) {

	int running = 0;

	//TAGET FRÅN LAB 3 mipslabmain.c
	/* Set up peripheral bus clock */
	/* Sätter klockan till 80 Mhz*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */

	/* Set button 2-4 to input */
	TRISD |= (2 << 5);

	/* Set LEDS to output */
	TRISE &= ~0xFF;



	/* Pointless comment */



	initGame();
	running = 1;

}
