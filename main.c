#include <stdint.h>
#include <pic32mx.h>

int main(void) {
	
	/* Set up peripheral bus clock */
	OSCCON &= ~0x180000;
	OSCCON |= 0x080000;
	
	/* Set button 2-4 to input */
	TRISD |= (3 << 5);
	
	/* Set LEDS to output */
	TRISE &= ~0xFF;
	
	
}
