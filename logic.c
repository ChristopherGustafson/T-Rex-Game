#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

void initGame(void){
    dino.x = 20;
    dino.y = 0;
    dino.WIDTH = 8;

    cactus.x = 120;
    cactus.y = 0;
    cactus.WIDTH = 5;

    bird.x = 80;
    bird.y = 16;
    bird.WIDTH = 5;

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

  //Jump
  if(BUTTON && !jumping){
    dino.velY = 4;
    dino.y += dino.velY;
    jumping = 1;
  }
  else if(dino.y <= 0){
    jumping = 0;
    dino.y = 0;
    dino.velY = 0;
  }
  else{
    dino.y += dino.velY;
    dino.velY--;
  }

}

void updateObstacles(){

  //Update cactus pos
  if(cactus.x > 0){
    cactus.x--;
  }
  else{
    cactus.x = 120;
  }
  //Update bird pos
  if(bird.x > 0){
    bird.x--;
  }else{
    bird.x = 90;
  }
}

void tick(void){
  updateDino();
  updateObstacles();
  checkCollision();
}
