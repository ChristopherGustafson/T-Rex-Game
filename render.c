#include <stdint.h>
#include <pic32mx.h>
#include "game.h"


void render(void){

	int page, col, t;

	for(page = 0; page < 4; page++){
		for(col = 0; col < 128; col++){

			//Draw dino
			if(page == 2 && col == dino.x){
				for(t = 0; t < 8; t++){
					spi_send_recv(dinoIm[t]);
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

      /*
			// Draw ground
			else if(page == 3){
				if(col < renderCount+5 && col > renderCount-5)
					spi_send_recv(0x25);
				else if(col < renderCount+40 && col > renderCount+35)
					spi_send_recv(0x19);
				else
					spi_send_recv(0x01);
			}
      */
      else if(page == 3)
        spi_send_recv(0x01);

			// If nothing is drawn, draw black
			else{
				spi_send_recv(0x00);
			}
		}
	}
}
