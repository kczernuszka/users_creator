#ifndef CONFIGPARSER_H_
#define CONFIGPARSER_H_

#include <confuse.h>
#include <time.h>

#include "userCreator.h"

#define DEFAULT_CONFIG_FILE_PATH "/etc/xlstousers/xlstousers.conf"

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
        char *home;
        unsigned long change;
        char *class_group;
        char *shell;
        unsigned long expire;
};

struct Config {
        char *column_name;
        char *column_surname;
        unsigned int password_length;
        struct UidsRange uidsRange;
        struct UserSettings user;
        struct QuotaSettings quota;
};

int initialize_config (cfg_t *cfg, char *config_file);
void load_config (struct Config *configuration, cfg_t *cfg);
int get_real_time_value (unsigned long seconds);

#endif // CONFIGPARSER_H_