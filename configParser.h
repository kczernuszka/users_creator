#ifndef CONFIGPARSER_H_
#define CONFIGPARSER_H_

#include <confuse.h>
#include <time.h>

#include "userCreator.h"

#define DEFAULT_CONFIG_FILE_PATH "/etc/xlstousers/xlstousers.conf"

#define HEADER_LENGTH 29
#define HOME_PATH_LENGTH 64
#define CLASS_NAME_LENGTH 32
#define SHELL_NAME_LENGTH 20

struct QuotaSettings {
        struct dqblk limits;
        char *path_quota;
};

struct UidsRange {
        unsigned int min_uid;
        unsigned int max_uid;
};

struct UserSettings {
        unsigned int gid;
        char home[HOME_PATH_LENGTH];
        unsigned long change;
        char class_name[CLASS_NAME_LENGTH];
        char shell_name[SHELL_NAME_LENGTH];
        unsigned long expire;
};

struct Config {
        char column_name[HEADER_LENGTH];
        char column_surname[HEADER_LENGTH];
        unsigned int password_length;
        struct UidsRange uidsRange;
        struct UserSettings user;
        struct QuotaSettings quota;
};

cfg_t* initialize_config (char *config_file);
struct Config* load_config (cfg_t *cfg);
int get_real_time_value (unsigned long seconds);

#endif // CONFIGPARSER_H_