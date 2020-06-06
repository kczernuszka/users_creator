#ifndef USERCREATOR_H_
#define USERCREATOR_H_

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/quota.h>

#include "freexl.h"
#include "polishToLatin.h"
#include "sheetLoader.h"
#include "configParser.h"

struct ColumnHead {
        char text[29];
        unsigned int row;
        unsigned short column;
};

struct Headers {
        struct ColumnHead name;
        struct ColumnHead surname;
};

int set_columns_heads_location(struct Headers *usersColumns, struct Worksheet dimensions, const void *xls_handler);
int value_is_text(unsigned char type);
int is_column_head(char *columnHead, char *stringInCell);
int set_head_location(struct ColumnHead *head, unsigned int row, unsigned int column);
int get_number_of_users(struct Headers usersColumns, unsigned int number_of_rows_in_sheet, const void *xls_handler);
char*** get_users_list (struct Headers usersColumns, unsigned int number_of_users, const void *xls_handler);
int chars_are_allowed(const char *text);
void create_quota(struct dqblk *limits, int gid, char *path_quota);

#endif // SHEETLOADER_H_