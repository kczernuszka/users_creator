#include <stddef.h>

#include "freexl.h"

const void *xls_handler;

struct Worksheet {
  unsigned int numberOfRows;
  short unsigned int numberOfColumns;
};


int load_file (const char *file)
{
        unsigned int worksheetCount;

        if (freexl_open(file, &xls_handler) != FREEXL_OK)
                return -1;

        if (freexl_get_info(xls_handler, FREEXL_BIFF_SHEET_COUNT, &worksheetCount) != FREEXL_OK)
                return -1;

        return worksheetCount;
}


const char* select_worksheet (struct Worksheet dimensions, unsigned int idx)
{
        const char* worksheetName;

        if (freexl_select_active_worksheet(xls_handler, idx) != FREEXL_OK)
                return NULL;

        if (freexl_worksheet_dimensions(xls_handler, &dimensions.numberOfRows, &dimensions.numberOfColumns) !=
            FREEXL_OK)
                return NULL;

        if (freexl_get_worksheet_name(xls_handler, idx, &worksheetName) != FREEXL_OK)
                return NULL;

        return worksheetName;
}
