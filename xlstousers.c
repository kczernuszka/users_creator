#include<unistd.h>

#include "argumentsParser.h"
#include "configParser.h"
#include "passwdUpdater.h"
#include "sheetLoader.h"
#include "userCreator.h"

int main(int argc, char *argv[]) {
        struct Settings settings;
        struct Config *configuration;
        struct Worksheet dimensions;
        struct Headers headers;
        struct User user;
        struct User **users_list;
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
        unsigned int current_uid;


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

        uid_t uuid=getuid(), euid=geteuid();
        if (uuid > 0 && uuid==euid) {
                printf("sorry, you are not root\n");
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

        strcpy(headers.name.text, configuration->column_name);
        strcpy(headers.surname.text, configuration->column_surname);

        if ((numberOfSheet = load_file(argv[optind], &xls_handler)) == -1) {
                printf("%s: File can not be loaded\n", argv[0]);
                return -1;
        }

        for (sheetCounter = 0; sheetCounter < numberOfSheet; ++sheetCounter) {
                sheetName = select_worksheet(&dimensions, sheetCounter, xls_handler);
                if (sheetName != NULL) {
                        if (set_columns_heads_location(&headers, dimensions, xls_handler) == 1) {
                                if ((numberOfUsers = get_number_of_users(headers, dimensions.numberOfRows,
                                     xls_handler)) != 0) {
                                        namesList = (const char***) get_users_list(headers, numberOfUsers, xls_handler);
                                        break;
                                }
                                else {
                                        printf("Not found values in columns %s and %s\n",
                                                headers.name.text, headers.surname.text);
                                        return -1;
                                }
                        }
                        else {
                                printf("Not found columns %s and %s", headers.name.text, headers.surname.text);
                                return -1;
                        }
                }
                else {
                        printf("Sheet number %d can not be loaded\n", sheetCounter);
                        return -1;
                }
        }

        users_list = (struct User**) malloc(sizeof(struct User) * numberOfUsers);
        current_uid = configuration->uidsRange.min_uid;
        for (userCounter = 0; userCounter < numberOfUsers; ++userCounter) {
                users_list[userCounter] = (struct User*) malloc(sizeof(struct User));
                user.uid = get_free_uid(current_uid, configuration->uidsRange.max_uid);
                strcpy(user.login, create_user_login(namesList[0][userCounter], namesList[1][userCounter]));
                if(user.uid != -1 && user.login != NULL) {
                        strcpy(user.home, create_home_directory(configuration->user.home, user.login));
                        strcpy(user.class_name, configuration->user.class_name);
                        strcpy(user.shell, configuration->user.shell_name);
                        user.gid = configuration->user.gid;
                        *users_list[userCounter] = user;
                        printf("login: %s  home: %s\n", user.login, user.home);
                }
                else {
                        printf("No free uid in range");
                        return -1;
                }
        }
}