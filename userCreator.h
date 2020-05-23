#ifndef USERCREATOR_H_
#define USERCREATOR_H_

#include <stdlib.h>
#include <string.h>

#include "sheetLoader.h"
#include "freexl.h"

struct ColumnHead {
        char *text;
        unsigned int row;
        unsigned short column;
};

struct Users {
        struct ColumnHead name;
        struct ColumnHead surname;
};

int set_columns_heads_location(struct Users *usersColumns, struct Worksheet dimensions);
int value_is_text(unsigned char type);
int is_column_head(char *columnHead, char *stringInCell);
int set_head_location(struct ColumnHead *head, unsigned int row, unsigned int column);
int get_number_of_users(struct Users usersColumns, unsigned int number_of_rows_in_sheet);
char*** get_users_list (struct Users usersColumns, unsigned int number_of_users);
int chars_are_allowed(char *text);

#endif // SHEETLOADER_H_