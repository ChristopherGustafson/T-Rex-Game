/* Declare display-related functions from display_functions.c */
void display();
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);
char * itoaconv( int num );
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

extern const uint8_t const dark[128];
//extern const uint8_t const dino[128];
extern const uint8_t const dot[1];

typedef struct gameObject{
  int x;
  int y;
  const int WIDTH;
  const int HEIGHT;
  const uint8_t image[];
} gameObject;
