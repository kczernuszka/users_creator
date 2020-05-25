#ifndef CONFIGPARSER_H_
#define CONFIGPARSER_H_

#include <confuse.h>

#include "userCreator.h"

#define DEFAULT_CONFIG_FILE_PATH "/etc/xlstousers/xlstousers.conf"

cfg_opt_t opts[] =
{
        CFG_STR("COLUMN_NAME", "Imie", CFGF_NONE),
        CFG_STR("COLUMN_SURNAME", "Nazwisko", CFGF_NONE),
        CFG_INT("PASSWORD_LEN", 8, CFGF_NONE),
        CFG_INT("MIN_UID", 1001, CFGF_NONE),
        CFG_INT("MAX_UID", 10000, CFGF_NONE),
        CFG_INT("GID", 10, CFGF_NONE),
        CFG_STR("HOME", "/home/", CFGF_NONE),
        CFG_INT("CHANGE", 0, CFGF_NONE),
        CFG_STR("CLASS", "staff", CFGF_NONE),
        CFG_STR("SHELL", "/bin/ksh", CFGF_NONE),
        CFG_INT("EXPIRE", 0, CFGF_NONE),
        CFG_INT("BLOCKS_HARD_LIMIT", 0, CFGF_NONE),
        CFG_INT("BLOCKS_SOFT_LIMIT", 0, CFGF_NONE),
        CFG_INT("INODES_HARD_LIMIT", 0, CFGF_NONE),
        CFG_INT("INODES_SOFT_LIMIT", 0, CFGF_NONE),
        CFG_INT("BLOCKS_TIME", 0, CFGF_NONE),
        CFG_INT("INODES_TIME", 0, CFGF_NONE),
        CFG_STR("PATH_QUOTA", "/home/", CFGF_NONE),
        CFG_END()
};

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
        char *password_length;
        struct UidsRange uidsRange;
        struct UserSettings user;
        struct QuotaSettings quota;
};

int initialize_config (cfg_t *cfg, char *config_file);
void load_config (struct Config *configuration, cfg_t cfg);
int get_real_time_value (unsigned long seconds);

#endif // CONFIGPARSER_H_