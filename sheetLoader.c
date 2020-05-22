#include "freexl.h"

const void *handle;

int load_file (const char *file)
{
  unsigned int worksheetCount;

  if (freexl_open(file, &handle) != FREEXL_OK) {
    return -1;
  }

  if (freexl_get_info(handle, FREEXL_BIFF_SHEET_COUNT, &worksheetCount) != FREEXL_OK) {
    return -1;
  }

  return worksheetCount;
}