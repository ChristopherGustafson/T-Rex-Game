/* Declare display-related functions from display_functions.c */
void display();
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);
char * itoaconv( int num );
void display_debug( volatile int * const addr );

#define BUTTON1 (PORTD >> 7)
#define BUTTON2 (PORTD >> 6)
#define BUTTON3 (PORTD >> 5)

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
extern const uint8_t const dinoIm[8];
extern const uint8_t const dinoHead[8];
extern const uint8_t const dinoBody[8];
extern const uint8_t const ground[6];
extern const uint8_t const cactusIm[5];
extern const uint8_t const cactus2[8];

extern const uint8_t const birdIm[5];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

typedef struct gameObject{
  int x;
  int y;
  int velX;
  int velY;
  int WIDTH;
  int HEIGHT;
} gameObject;

/* Game variables */
int running;
int gameOver;
int renderCount;

struct gameObject dino;
struct gameObject cactus;
struct gameObject bird;

int jumping;
 /* Game functions */
void initGame();
void tick();
void render();
