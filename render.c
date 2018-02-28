#include <stdint.h>
#include <pic32mx.h>
#include "game.h"


void render(void){

	int page, col, t, i;

	for(page = 0; page < 4; page++){
		for(col = 0; col < 128; col++){

			switch(page){

				case 0:

					if(dino.x == col){
						for(t = 0; t < dino.WIDTH; t++){

							//If bird.x = col during dino render, render both
							if(bird.x == col){
								for(i = 0; i < bird.WIDTH; i++){
									if(dino.y >= 8){
										spi_send_recv( (dinoHead[t]>>(dino.y-8)) | (dinoBody[t] << (16-dino.y)) | birdIm[i] );
									}
									else{
										spi_send_recv( dinoHead[t] << (8-dino.y) | birdIm[i]);
									}
									t++;
								}
								col += (bird.WIDTH -1);
							}
							else{
								if(dino.y >= 8){
									spi_send_recv( (dinoHead[t]>>(dino.y-8)) | (dinoBody[t] << (16-dino.y)) );
								}
								else{
									spi_send_recv( dinoHead[t] << (8-dino.y));
								}
							}

							col++;
						}
						col--;
					}

					else if(bird.x == col){
						for(t = 0; t < bird.WIDTH; t++){
							spi_send_recv(birdIm[t]);
						}
						col += bird.WIDTH-1;
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

								/* If cactus.x is reached during render of dino, render cactus
								and dino. */
								if(cactus.x == col){
									for(i = 0; i < cactus.WIDTH; i++){
										spi_send_recv(dinoBody[t]>>dino.y | cactusIm[i]);
										t++;
									}
									col += (cactus.WIDTH -1);
								}
								else{
									spi_send_recv(dinoBody[t]>>dino.y);
								}
								col++;
							}
							col--;


					}



					else if(cactus.x == col){
						for(t = 0; t < cactus.WIDTH; t++){
							spi_send_recv(cactusIm[t]);
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
