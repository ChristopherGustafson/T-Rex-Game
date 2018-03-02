#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

int jumpCount;
volatile int* LEDwrite = (volatile int*) 0xbf886110;

void initGame(void){
    running = 1;
    score = 0;

    dino.x = 20;
    dino.y = 0;
    dino.WIDTH = 8;
    dino.HEIGHT = 12;

    cactus.x = 60;
    cactus.y = 0;
    cactus.WIDTH = 5;
    cactus.HEIGHT = 8;

    bird.x = 120;
    bird.y = 20;
    bird.WIDTH = 5;
    bird.HEIGHT = 4;

    jumping = 0;
    ducking = 0;
    jumpCount = 0;

    *LEDwrite = 0;
}

void checkCollision(void){

  //Check collision with cactus
  if(dino.y < (cactus.y + cactus.HEIGHT)){
		int cactusMid = cactus.x + cactus.WIDTH/2;
		if(cactusMid < dino.x+dino.WIDTH && cactusMid > dino.x){
      running = 0;
      gameOver = 1;
		}
	}

  //Check collision with bird
  if((bird.y) <= (dino.y+dino.HEIGHT) && (bird.y) >= dino.y){
    if(bird.x > dino.x && bird.x < dino.x+dino.WIDTH |
      (bird.x+bird.WIDTH > dino.x && bird.x+bird.WIDTH < dino.x+dino.WIDTH)){
      running = 0;
      gameOver = 1;
    }
  }
}

void updateDino(){
  //Jump
  if(BUTTON1 && !jumping && !ducking){
    jumping = 1;
    dino.velY = 4;
    dino.y += dino.velY;
  }
  else if(jumping){
    if(jumpCount){
      dino.y += dino.velY;
      dino.velY--;
      jumpCount = 0;
    }
    else{
      jumpCount = 1;
    }

    if(dino.y <= 0){
      jumping = 0;
      dino.y = 0;
      dino.velY = 0;
    }
  }


  if(BUTTON2 && !ducking && dino.y == 0){
    ducking = 1;
    dino.HEIGHT = 8;
    dino.WIDTH = 12;
  }
  else if(!BUTTON2 && ducking && dino.y == 0){
    ducking = 0;
    dino.HEIGHT = 12;
    dino.WIDTH = 8;
  }

}

void updateObstacles(){

  //Update cactus pos
  if(cactus.x > 0){
    cactus.x--;
  }
  else{
    cactus.x = 122;
  }
  //Update bird pos
  if(bird.x > 0){
    bird.x--;
  }else{
    bird.x = 122;

    switch(rand()%3){
      case 0:
        bird.y = 20;
        break;
      case 1:
        bird.y = 12;
        break;
      case 2:
        bird.y = 4;
        break;
      }
    }

}

void scoreToArray(int a){

  int n, i;
  if(a < 10){
    n = 1;
  }
  else if(a < 100){
    n = 2;
  }
  else{
    n = 3;
  }

  int ret[3];

  for(i = 0; i < n; i++){
    ret[i] = a % 10;
    a /= 10;
  }

  *highscore = *ret;
}

void tick(void){
  updateDino();
  updateObstacles();
  checkCollision();


  if(cactus.x == dino.x){
    score++;
    *LEDwrite += 1;
  }

}
