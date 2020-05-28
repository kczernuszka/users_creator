#ifndef ARGUMENTSPARSER_H_
#define ARGUMENTSPARSER_H_

#include<ctype.h>
#include<getopt.h>
#include<stddef.h>
#include<stdlib.h>

struct Settings {
        int interactive_mode;
        int test_mode; 
        int quota_on;
        char *config_file;
        char *passwd_file;
        char wrongParameter;
};

int parse_arguments (struct Settings *settings, int argc, char *argv[]);

#endif // ARGUMENTSPARSER_H_