/* ['./imageToData.py', 'font.png'] */
#include <stdint.h>
uint16_t fontW = 8;
uint16_t fontH = 1504;
static const uint8_t font[] = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,0,0,255,0,0,
	0,0,255,0,0,255,0,0,
	0,0,255,0,0,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,0,0,255,0,0,
	0,0,255,0,0,255,0,0,
	0,0,255,0,0,255,0,0,
	0,255,255,255,255,255,255,0,
	0,0,255,0,0,255,0,0,
	0,0,255,0,0,255,0,0,
	0,255,255,255,255,255,255,0,
	0,0,255,0,0,255,0,0,
	0,0,255,0,0,255,0,0,
	0,0,255,0,0,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,255,255,255,255,255,0,0,
	255,0,0,255,0,0,255,0,
	255,0,0,255,0,0,0,0,
	255,0,0,255,0,0,0,0,
	0,255,255,255,255,255,0,0,
	0,0,0,255,0,0,255,0,
	0,0,0,255,0,0,255,0,
	255,0,0,255,0,0,255,0,
	0,255,255,255,255,255,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,0,0,255,0,0,
	255,0,0,255,0,255,0,0,
	0,255,255,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,255,255,0,0,
	0,255,0,255,0,0,255,0,
	0,255,0,0,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,255,0,0,0,
	0,0,255,0,0,255,0,0,
	0,0,255,0,0,255,0,0,
	0,0,0,255,255,0,0,0,
	0,0,255,255,0,0,0,0,
	0,255,0,0,255,0,255,0,
	0,255,0,0,0,255,0,0,
	0,255,0,0,0,255,0,0,
	0,255,0,0,0,255,0,0,
	0,0,255,255,255,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,0,0,255,0,0,
	0,0,0,255,255,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,255,255,0,0,0,
	0,0,255,0,0,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,255,255,255,255,255,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,255,255,0,
	0,255,0,0,255,0,255,0,
	0,255,0,255,0,0,255,0,
	0,255,255,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,255,255,0,0,0,
	0,0,255,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,255,255,255,0,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,255,255,0,
	0,0,0,0,255,0,255,0,
	0,0,0,255,0,0,255,0,
	0,0,255,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,255,255,255,255,0,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,255,255,0,0,
	0,0,255,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,255,0,0,
	0,0,255,255,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,0,0,
	255,0,0,0,0,0,255,0,
	255,0,0,255,255,255,255,0,
	255,0,255,0,0,0,255,0,
	255,0,255,0,0,0,255,0,
	255,0,255,0,0,0,255,0,
	255,0,255,0,0,255,255,0,
	255,0,0,255,255,0,255,0,
	255,0,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,255,255,255,255,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,0,0,0,
	0,255,0,0,0,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,255,0,0,
	0,255,255,255,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,255,255,255,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,255,255,255,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,255,255,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,255,255,255,255,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,255,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,255,255,255,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,255,0,0,0,255,0,0,
	0,255,0,0,0,255,0,0,
	0,0,255,255,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,255,0,0,
	0,255,0,0,255,0,0,0,
	0,255,0,255,0,0,0,0,
	0,255,255,0,0,0,0,0,
	0,255,255,0,0,0,0,0,
	0,255,0,255,0,0,0,0,
	0,255,0,0,255,0,0,0,
	0,255,0,0,0,255,0,0,
	0,255,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	255,0,0,0,0,0,255,0,
	255,255,0,0,0,255,255,0,
	255,0,255,0,255,0,255,0,
	255,0,0,255,0,0,255,0,
	255,0,0,255,0,0,255,0,
	255,0,0,0,0,0,255,0,
	255,0,0,0,0,0,255,0,
	255,0,0,0,0,0,255,0,
	255,0,0,0,0,0,255,0,
	255,0,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,255,0,0,0,255,0,
	0,255,0,255,0,0,255,0,
	0,255,0,0,255,0,255,0,
	0,255,0,0,0,255,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,255,255,255,255,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,255,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,255,255,255,255,0,0,
	0,255,0,255,0,0,0,0,
	0,255,0,0,255,0,0,0,
	0,255,0,0,0,255,0,0,
	0,255,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	255,255,255,255,255,255,255,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,0,0,255,0,0,
	0,0,255,0,0,255,0,0,
	0,0,255,0,0,255,0,0,
	0,0,0,255,255,0,0,0,
	0,0,0,255,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	255,0,0,0,0,0,255,0,
	255,0,0,0,0,0,255,0,
	255,0,0,0,0,0,255,0,
	255,0,0,0,0,0,255,0,
	255,0,0,0,0,0,255,0,
	255,0,0,255,0,0,255,0,
	255,0,0,255,0,0,255,0,
	255,0,255,0,255,0,255,0,
	255,255,0,0,0,255,255,0,
	255,0,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,0,0,255,0,0,
	0,0,255,0,0,255,0,0,
	0,0,0,255,255,0,0,0,
	0,0,0,255,255,0,0,0,
	0,0,255,0,0,255,0,0,
	0,0,255,0,0,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	255,0,0,0,0,0,255,0,
	255,0,0,0,0,0,255,0,
	0,255,0,0,0,255,0,0,
	0,255,0,0,0,255,0,0,
	0,0,255,0,255,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,255,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,255,255,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,0,255,0,0,0,
	0,255,0,0,0,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,255,0,
	0,0,255,255,255,255,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,255,255,255,255,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,255,255,255,255,255,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,255,255,255,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,255,255,255,255,255,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,255,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,255,255,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,0,255,0,0,
	0,255,0,0,0,255,0,0,
	0,255,0,0,0,255,0,0,
	0,0,255,255,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,255,0,0,
	0,255,0,0,255,0,0,0,
	0,255,255,255,0,0,0,0,
	0,255,0,0,255,0,0,0,
	0,255,0,0,0,255,0,0,
	0,255,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,255,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	255,255,255,255,255,255,0,0,
	255,0,0,255,0,0,255,0,
	255,0,0,255,0,0,255,0,
	255,0,0,255,0,0,255,0,
	255,0,0,255,0,0,255,0,
	255,0,0,255,0,0,255,0,
	255,0,0,255,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,255,255,255,255,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,255,255,255,255,0,
	0,255,255,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,255,255,255,0,
	0,255,0,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,255,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,255,255,255,255,255,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,0,0,255,0,0,
	0,0,255,0,0,255,0,0,
	0,0,0,255,255,0,0,0,
	0,0,0,255,255,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	255,0,0,0,0,0,255,0,
	255,0,0,0,0,0,255,0,
	255,0,0,255,0,0,255,0,
	255,0,0,255,0,0,255,0,
	255,0,0,255,0,0,255,0,
	255,0,0,255,0,0,255,0,
	0,255,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,0,0,255,0,0,
	0,0,0,255,255,0,0,0,
	0,0,255,0,0,255,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,255,0,0,0,0,255,0,
	0,0,255,255,255,255,255,0,
	0,0,0,0,0,0,255,0,
	0,0,0,0,0,0,255,0,
	0,0,255,255,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,255,0,0,0,0,0,0,
	0,255,255,255,255,255,255,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,255,255,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,255,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,255,255,0,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,0,255,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,0,0,255,0,0,0,
	0,0,255,255,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,255,255,0,0,0,255,0,
	255,0,0,255,0,0,255,0,
	255,0,0,0,255,255,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
};