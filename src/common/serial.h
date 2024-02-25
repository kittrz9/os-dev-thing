#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

#define COM1 0x3F8
#define COM2 0x2F8

#define COM1DATA        (COM1 + 0)
#define COM1INT         (COM1 + 1)
#define COM1FIFO        (COM1 + 2)
#define COM1LINECONTROL (COM1 + 3)
#define COM1MODEM       (COM1 + 4)
#define COM1LINESTATUS  (COM1 + 5)
#define COM1MODEMSTATUS (COM1 + 6)
#define COM1SCRATCH     (COM1 + 7)
#define COM1BAUDLSB     COM1DATA
#define COM1BAUDMSB     COM1INT

void initSerial(void);

void serialWriteChar(char c);
void serialWriteStr(char* str);
void serialWriteHex32(uint32_t n);

// should really be moved somewhere else but this works for now
char* hex32Str(uint32_t n); 


#endif
