#ifndef SHEETLOADER_H_
#define SHEETLOADER_H_

#include <stddef.h>

#include "freexl.h"

struct Worksheet {
        unsigned int numberOfRows;
        short unsigned int numberOfColumns;
};

int load_file (const char *file);
const char* select_worksheet (struct Worksheet dimensions, unsigned int idx);

#endif // SHEETLOADER_H_