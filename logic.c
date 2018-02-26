#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

void checkButtons(){

}

void initGame(void){
    dino.x = 20;
    dino.y = 0;
    dino.WIDTH = 8;

    cactus.x = 120;
    cactus.y = 0;
    cactus.WIDTH = 5;

    running = 1;
}

void checkCollision(void){

  if(dino.y == cactus.y){
		int cactusMid = cactus.x + cactus.WIDTH/2;
		if(cactusMid < dino.x+dino.WIDTH && cactusMid > dino.x){
      running = 0;
      gameOver = 1;
		}
	}

}

void updateDino(){

    



  dino.y += dino.velY;


}

void updateObstacles(){
  if(cactus.x > 0){
    cactus.x--;
  }
  else
    cactus.x = 120;

}

void tick(void){
  checkButtons();
  updateDino();
  updateObstacles();
  checkCollision();
}
