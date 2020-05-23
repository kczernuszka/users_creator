#include "userCreator.h"

extern const void *xls_handler;

int set_columns_heads_location (struct Users *usersColumns, struct Worksheet dimensions)
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
        if (nameColumnFound|| surnameColumnFound)
                return -1;
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

int get_number_of_users(struct Users usersColumns, unsigned int number_of_rows_in_sheet)
{
        FreeXL_CellValue nameValue;
        FreeXL_CellValue surnameValue;
        unsigned int nameRow = usersColumns.name.row;
        unsigned short surnameRow = usersColumns.surname.row;
        unsigned int number_of_users = 0;

        while(nameRow < number_of_rows_in_sheet && surnameRow < number_of_rows_in_sheet) {
                ++nameRow;
                ++surnameRow;

        freexl_get_cell_value(xls_handler, nameRow, usersColumns.name.column, &nameValue);
        freexl_get_cell_value(xls_handler, surnameRow, usersColumns.surname.column, &surnameValue);

        if(value_is_text(nameValue.type) && value_is_text(nameValue.type))
                ++number_of_users;
        else
                break;
        }

        return number_of_users;
}
