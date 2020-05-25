#include "argumentsParser.h"
#include "configParser.h"

main(int argc, char *argv[]) {
        struct Settings settings;

        if(parse_arguments(settings, argc, argv) != 0) {
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
}