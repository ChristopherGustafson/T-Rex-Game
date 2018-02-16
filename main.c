#include <stdint.h>
#include <pic32mx.h>



int main(void) {
<<<<<<< HEAD

=======
	
	int running = 0;
	
>>>>>>> 4592b5f5cafd060301cd6b62d7d64cd9f1ac1ce2
	/* Set up peripheral bus clock */
	/* Sätter klockan till 80 Mhz*/
	OSCCON &= ~0x180000;
	OSCCON |= 0x080000;

	/* Set button 2-4 to input */
	TRISD |= (3 << 5);

	/* Set LEDS to output */
	TRISE &= ~0xFF;
<<<<<<< HEAD


=======
	
	/* Pointless comment */
	
	
	
	initGame();
	running = 1;
	
	
	
>>>>>>> 4592b5f5cafd060301cd6b62d7d64cd9f1ac1ce2
}
