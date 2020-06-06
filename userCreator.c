#include "userCreator.h"

extern const void *xls_handler;

int set_columns_heads_location (struct Headers *usersColumns, struct Worksheet dimensions, const void *xls_handler)
{
        FreeXL_CellValue cellValue;
        char *stringInCell;
        unsigned short nameColumnFound = 0;
        unsigned short surnameColumnFound = 0;
        int row;
        int column;

        for (row = 0; row < dimensions.numberOfRows; ++row) {
                for (column = 0; column < dimensions.numberOfColumns; ++column) {

                        freexl_get_cell_value(xls_handler, row, column, &cellValue);
                        stringInCell = (char*)cellValue.value.text_value;
                        stringInCell = polish_letters_to_latin(stringInCell);

                        if (value_is_text(cellValue.type)) {
                                if (is_column_head(usersColumns->name.text, stringInCell)) {
                                        set_head_location(&usersColumns->name, row, column);
                                        nameColumnFound = 1;
                                }
                                else if (is_column_head(usersColumns->surname.text, stringInCell)) {
                                        set_head_location(&usersColumns->surname, row, column);
                                        surnameColumnFound = 1;
                                }
                        }
                }
        }
        if (nameColumnFound && surnameColumnFound)
                return 1;
        else
                return 0;
}

int value_is_text (unsigned char type) 
{
        if (type == FREEXL_CELL_SST_TEXT || type == FREEXL_CELL_TEXT)
                return 1;
        else
                return 0;
}

int is_column_head(char *columnHead, char *stringInCell)
{
        if(strcmp(columnHead, stringInCell))
                return 0;
        else
                return 1;
}

int set_head_location(struct ColumnHead *head, unsigned int row, unsigned int column)
{
        head->row = row;
        head->column = column;
}

int get_number_of_users(struct Headers usersColumns, unsigned int number_of_rows_in_sheet, const void *xls_handler)
{
        FreeXL_CellValue nameValue;
        FreeXL_CellValue surnameValue;
        unsigned int nameRow = usersColumns.name.row;
        unsigned short surnameRow = usersColumns.surname.row;
        unsigned int number_of_users = 0;

        while(++nameRow < number_of_rows_in_sheet && ++surnameRow < number_of_rows_in_sheet) {

        freexl_get_cell_value(xls_handler, nameRow, usersColumns.name.column, &nameValue);
        freexl_get_cell_value(xls_handler, surnameRow, usersColumns.surname.column, &surnameValue);

        if(value_is_text(nameValue.type) && value_is_text(nameValue.type))
                ++number_of_users;
        else
                break;
        }

        return number_of_users;
}

char*** get_users_list (struct Headers usersColumns, unsigned int number_of_users, const void *xls_handler)
{
        FreeXL_CellValue nameValue, surnameValue;
        unsigned int nameRow = usersColumns.name.row;
        unsigned short surnameRow = usersColumns.surname.row;
        char ***namesList;
        char *name, *surname;
        int i, counter = 1;
        namesList = (char***) malloc(2*sizeof(char**));
        namesList[0] = (char**) malloc(HEADER_LENGTH * number_of_users * sizeof(char*));
        namesList[1] = (char**) malloc(HEADER_LENGTH * number_of_users * sizeof(char*));

        for (i = 0; i < number_of_users; ++i) {
                ++nameRow;
                ++surnameRow;
		namesList[0][i] = (char*) malloc(HEADER_LENGTH * sizeof(char));
                namesList[1][i] = (char*) malloc(HEADER_LENGTH * sizeof(char));

                freexl_get_cell_value(xls_handler, nameRow, usersColumns.name.column, &nameValue);
                freexl_get_cell_value(xls_handler, surnameRow, usersColumns.surname.column, &surnameValue);

                if (strlen((char*) nameValue.value.text_value) < HEADER_LENGTH && 
                    strlen((char*) surnameValue.value.text_value) < HEADER_LENGTH && 
                     chars_are_allowed(nameValue.value.text_value) &&
                      chars_are_allowed(surnameValue.value.text_value)) {
                        
                        strcpy(namesList[0][i], polish_letters_to_latin(nameValue.value.text_value));
                        strcpy(namesList[1][i], polish_letters_to_latin(surnameValue.value.text_value));
                }
                ++counter;
        }
        return namesList;
}

int chars_are_allowed(const char *text)
{
        const char *pointer = text;
        while (*pointer != '\0') {
                if (!isalpha(*pointer)){
                        return 0;
                }
                pointer++;
        }
        return 1;
}

void create_quota(struct dqblk *limits, int gid, char *path_quota)
{
    quotactl(QCMD(Q_SETQUOTA, GRPQUOTA), path_quota, gid, (char*)&limits);
}