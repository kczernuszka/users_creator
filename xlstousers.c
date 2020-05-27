#include "argumentsParser.h"
#include "configParser.h"

int main(int argc, char *argv[]) {
        struct Settings settings;
        struct Config configuration;
        cfg_t cfg;
        int status;

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
        }
        if(settings.passwd_file == NULL) {
                settings.passwd_file = (char*) malloc(25*sizeof(char));
                settings.passwd_file = "/etc/passwd";
        }
        load_config(&configuration, cfg);
}