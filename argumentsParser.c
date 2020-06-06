#include "argumentsParser.h"

int parse_arguments (struct Settings *settings, int argc, char *argv[])
{
        int c, ctargc = 2;
        settings->interactive_mode = 0;
        settings->test_mode = 0;
        settings->quota_on = 0;
        settings->config_file = NULL;
        settings->passwd_file = NULL;

        while ((c = getopt(argc, argv, "itqc:")) != -1) {
                ++ctargc;
                switch (c) {
                        case 'i':
	                            settings->interactive_mode = 1;
	                            break;
                        case 'c':
	                            settings->config_file = optarg;
	                            ++ctargc;
	                            break;
                        case 't':
	                            settings->passwd_file = (char*) malloc(7*sizeof(char));
	                            settings->passwd_file = "passwd";
	                            settings->test_mode = 1;
	                            break;
                        case 'q':
                                settings->quota_on = 1;
                                break;
                        case '?':
                                settings->wrongParameter = optopt;
                                if(optopt == 'c')
                                        return 1;
                                else if(isprint(optopt))
                                        return 2;
                                else
                                        return 3;
                                break;
                        default:
                                abort();
                }
        }
        if(ctargc != argc)
                return 4;
        if(argc == 1)
                return 4;
        return 0;
}