#ifndef FILES_H
#define FILES_H

// moved out of fs.h so stuff like term.h and font.h wouldn't be in stage2 even though stage2 needs fs.h

void printFile(char* name);

void listFiles(void);

#endif 
