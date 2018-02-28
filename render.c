#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

/*
void render(void){

	int page, col, t;

	for(page = 0; page < 4; page++){
		for(col = 0; col < 128; col++){


			//Draw dino
			if(page == 2 && col == dino.x && dino.y == 0){
				for(t = 0; t < 8; t++){
					spi_send_recv(dinoBody[t]);
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

			//Draw bird
			else if(page == 0 && col == bird.x){
				for(t = 0; t < bird.WIDTH; t++){
					spi_send_recv(birdIm[t]);
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


      else if(page == 3)
        spi_send_recv(0x01);

			// If nothing is drawn, draw black
			else{
				spi_send_recv(0x00);
			}
		}
	}
}
*/
void render(void){

	int page, col, t;

	for(page = 0; page < 4; page++){
		for(col = 0; col < 128; col++){

			switch(page){

				case 0:

					if(dino.x == col){
						for(t = 0; t < dino.WIDTH; t++){
							if(dino.y >= 8){
								spi_send_recv( (dinoHead[t]>>(dino.y-8)) | (dinoBody[t] << (16-dino.y)) );
							}
							else{
								spi_send_recv( dinoHead[t] << (8-dino.y));
							}
						}
						col += (dino.WIDTH-1);
					}
					else{
						spi_send_recv(0x00);
					}
					break;

				case 1:

					if(dino.x == col){
						for(t = 0; t < dino.WIDTH; t++){
							if(dino.y <= 8){
								spi_send_recv( (dinoHead[t]>>dino.y) | (dinoBody[t] << (8-dino.y)) );
							}
							else{
								spi_send_recv( dinoBody[t] >> (dino.y-8));
							}
						}
						col += (dino.WIDTH-1);
					}
					else{
						spi_send_recv(0x00);
					}
					break;

				case 2:

					if(dino.x == col){
							for(t = 0; t < dino.WIDTH; t++){
								spi_send_recv(dinoBody[t]>>dino.y);
							}
						}
						col += (dino.WIDTH-1);
					}



					else if(cactus.x == col){
						for(t = 0; t < cactus.WIDTH; t++){
							spi_send_recv(cactus2[t]);
						}
						col += cactus.WIDTH-1;
					}
					else{
						spi_send_recv(0x00);
					}
					break;

				case 3:

					spi_send_recv(0x01);
					break;


			}

		}
	}
}
