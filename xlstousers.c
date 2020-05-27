#include "argumentsParser.h"
#include "configParser.h"
#include "sheetLoader.h"
#include "userCreator.h"

int main(int argc, char *argv[]) {
        struct Settings settings;
        struct Config configuration;
        struct Worksheet dimensions;
        struct Users users;
        cfg_t cfg;
        int status;
        int numberOfSheet;
        int sheetCounter;
        const char *sheetName = NULL;
        unsigned int rows;
        unsigned short columns;
        int numberOfUsers;
        const char ***namesList;

        status = parse_arguments(&settings, argc, argv);
        if(status != 0) {
                if (status == 1)
                        printf("Option -%c requires an argument\n", settings.wrongParameter);
                if (status == 2)
                        printf("Unknown option `-%c\n", settings.wrongParameter);
                if (status == 3)
                        printf("Unknown option character `\\x%x'\n", settings.wrongParameter);
                if (status == 4)
                        printf("usage: xlstousers [-q] [-i] [-t] [-c configFile] xlsFile\n");
                return -1;
        }

        if(settings.config_file == NULL)
                settings.config_file = DEFAULT_CONFIG_FILE_PATH;
        if(initialize_config(&cfg, settings.config_file) != 0) {
                printf("Can not load configure file\n");
                return -1;
        }
        if(settings.passwd_file == NULL) {
                settings.passwd_file = (char*) malloc(25*sizeof(char));
                settings.passwd_file = "/etc/passwd";
        }
        load_config(&configuration, cfg);

        users.name.text = configuration.column_name;
        users.surname.text = configuration.column_surname;

        numberOfSheet = load_file(argv[0]);
        if (numberOfSheet == -1) {
                printf("%s: File can not be loaded\n", argv[0]);
                return -1;
        }

        for (sheetCounter = 0; sheetCounter < numberOfSheet; ++sheetCounter) {
                sheetName = select_worksheet(&dimensions, sheetCounter);
                if (sheetName != NULL) {
                        if (set_columns_heads_location(&users, dimensions) != -1) {
                                if (numberOfUsers = get_number_of_users(users, dimensions.numberOfRows) != 0)
                                        namesList = get_users_list(users, numberOfUsers);
                                else
                                        printf("Not found values in columns %s and %s\n",
                                                users.name.text, users.surname.text);
                        }
                        else {
                                printf("Not found columns %s and %s", users.name.text, users.surname.text);
                        }
                }
                else {
                        printf("Sheet number %d can not be loaded\n", sheetCounter);
                }
        }

}