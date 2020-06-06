#include "argumentsParser.h"
#include "configParser.h"
#include "passwdUpdater.h"
#include "sheetLoader.h"
#include "userCreator.h"

int main(int argc, char *argv[]) {
        struct Settings settings;
        struct Config *configuration;
        struct Worksheet dimensions;
        struct Users users;
        cfg_t *cfg;
        int status;
        int numberOfSheet;
        int sheetCounter;
        const char *sheetName = NULL;
        unsigned int rows;
        unsigned short columns;
        int numberOfUsers;
        const char ***namesList;
        const void *xls_handler;
        unsigned int userCounter;
        char *login;
        char *home;

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

        if(settings.config_file == NULL) {
                settings.config_file = (char*) malloc(strlen(DEFAULT_CONFIG_FILE_PATH) * sizeof(char));
                settings.config_file = DEFAULT_CONFIG_FILE_PATH;
        }
        if((cfg = initialize_config(settings.config_file)) == NULL) {
                printf("Can not load configure file\n");
                return -1;
        }
        if(settings.passwd_file == NULL) {
                settings.passwd_file = (char*) malloc(strlen("/etc/passwd") * sizeof(char));
                settings.passwd_file = "/etc/passwd";
        }
        configuration = load_config(cfg);

        strcpy(users.name.text, configuration->column_name);
        strcpy(users.surname.text, configuration->column_surname);

        if ((numberOfSheet = load_file(argv[optind], &xls_handler)) == -1) {
                printf("%s: File can not be loaded\n", argv[0]);
                return -1;
        }

        for (sheetCounter = 0; sheetCounter < numberOfSheet; ++sheetCounter) {
                sheetName = select_worksheet(&dimensions, sheetCounter, xls_handler);
                if (sheetName != NULL) {
                        if (set_columns_heads_location(&users, dimensions, xls_handler) != 0) {
                                if ((numberOfUsers = get_number_of_users(users, dimensions.numberOfRows,
                                     xls_handler)) != 0)
                                        namesList = (const char***) get_users_list(users, numberOfUsers, xls_handler);
                                else {
                                        printf("Not found values in columns %s and %s\n",
                                                users.name.text, users.surname.text);
                                        return -1;
                                }
                        }
                        else {
                                printf("Not found columns %s and %s", users.name.text, users.surname.text);
                                return -1;
                        }
                }
                else {
                        printf("Sheet number %d can not be loaded\n", sheetCounter);
                        return -1;
                }
        }

        for (userCounter = 0; userCounter < numberOfUsers; ++userCounter) {
                login = create_user_login(namesList[0][userCounter], namesList[1][userCounter]);
                home = create_home_directory(configuration->user.home, login);
                printf("login: %s  home: %s", login, home);
        }

}