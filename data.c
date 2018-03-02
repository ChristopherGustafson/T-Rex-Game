#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"  /* Declatations for these labs */

char textbuffer[4][16];

const uint8_t const dinoHead[] = {0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0x50, 0x70};
const uint8_t const dinoBody[] = {0x0e, 0x18, 0xfc, 0xbf, 0x3f, 0xff, 0x85, 0x00};
const uint8_t const dinoDuck[] = {0x0e, 0x18, 0xf8, 0xbc, 0x3c, 0xfc, 0x9c, 0x3c, 0x18, 0x74, 0x5c, 0x1c};
const uint8_t const cactusIm[] = {0x1c, 0x10, 0xfc, 0x10, 0x1c};
const uint8_t const birdIm[] = {0x0c, 0x2c, 0x38, 0x18, 0x08};
const uint8_t const start[] = {0x1f, 0x11, 0x11, 0x0e, 0x0, 0x11, 0x1f, 0x11, 0x0, 0x1f, 0x02, 0x04, 0x1f
															, 0x0, 0x0e, 0x11, 0x11, 0x0e, 0x0, 0x0, 0x0, 0x1f, 0x05, 0x0d, 0x12, 0x0,
															0x0f, 0x10, 0x10, 0x0f, 0x0, 0x1f, 0x02, 0x04, 0x1f};

const uint8_t const game[] = {0x0e, 0x11, 0x15, 0x0c, 0x0, 0x1e, 0x05, 0x5,
															0x1e, 0x0, 0x1f, 0x02, 0x04, 0x02, 0x1f, 0x0,
															0x1f, 0x15, 0x15, 0x11, 0x0, 0x0, 0x0, 0x0e,
															0x11, 0x11, 0x0e, 0x0, 0x03, 0x0c, 0x10,
															0x0c, 0x03, 0x0, 0x1f, 0x15, 0x15, 0x11, 0x0,
															0x1f, 0x05, 0x0d, 0x12};

const uint8_t const numbers[] = {0x0e, 0x11, 0x11, 0x0e, 0x12, 0x1f, 0x10, 0x0, 0x12, 0x19, 0x15, 0x12,
																0x0a, 0x11, 0x15, 0x0a, 0x0c, 0x0a, 0x1f, 0x8,
																0x17, 0x15, 0x15, 0x09, 0x0e, 0x15, 0x15, 0x8,
																0x1, 0x1, 0x19, 0x6,0x0a, 0x15, 0x15, 0x0a, 0x02,
																0x05, 0x15, 0x0e};

const uint8_t const s[] = {0x12, 0x15, 0x15, 0x09, 0x00, 0x0e, 0x11, 0x11, 0x0a, 0x00,
															0x0e, 0x11, 0x11, 0x0e, 0x00, 0x1f, 0x05, 0x0d, 0x12, 0x00,
															0x1f, 0x15, 0x15, 0x11, 0x00};
