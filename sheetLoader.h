#ifndef SHEETLOADER_H_
#define SHEETLOADER_H_

#include <stddef.h>

#include "freexl.h"

struct Worksheet {
        unsigned int numberOfRows;
        short unsigned int numberOfColumns;
};

int load_file (const char *file, const void **xls_handler);
const char* select_worksheet (struct Worksheet *dimensions, unsigned int idx, const void *xls_handler);

#endif // SHEETLOADER_H_