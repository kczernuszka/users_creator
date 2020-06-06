#include "configParser.h"

cfg_t* initialize_config (char *config_file)
{
        cfg_opt_t options[] =
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
        cfg_t *cfg = cfg_init(options, CFGF_NONE);
        if (cfg_parse(cfg, config_file) != CFG_SUCCESS) {
                return NULL;
        }
        return cfg;
}

struct Config* load_config (cfg_t *cfg)
{
        struct Config *configuration = (struct Config*) malloc(sizeof(struct Config));
        configuration->column_name = (char*) malloc(strlen(cfg_getstr(cfg, "COLUMN_NAME")) * sizeof(char));
        configuration->column_name = cfg_getstr(cfg, "COLUMN_NAME");
        configuration->column_surname = (char*) malloc(strlen(cfg_getstr(cfg, "COLUMN_SURNAME")) * sizeof(char));
        configuration->column_surname = cfg_getstr(cfg, "COLUMN_SURNAME");
        configuration->password_length = cfg_getint(cfg, "PASSWORD_LEN");
        configuration->uidsRange.min_uid = cfg_getint(cfg, "MIN_UID");
        configuration->uidsRange.max_uid = cfg_getint(cfg, "MAX_UID");
        configuration->user.gid = cfg_getint(cfg, "GID");
        configuration->user.home = (char*) malloc(strlen(cfg_getstr(cfg, "HOME")) * sizeof(char));
        configuration->user.home = cfg_getstr(cfg, "HOME");
        configuration->user.change = get_real_time_value(cfg_getint(cfg, "CHANGE"));
        configuration->user.class_group = (char*) malloc(strlen(cfg_getstr(cfg, "CLASS")) * sizeof(char));
        configuration->user.class_group = cfg_getstr(cfg, "CLASS");
        configuration->user.shell = (char*) malloc(strlen(cfg_getstr(cfg, "SHELL")) * sizeof(char));
        configuration->user.shell = cfg_getstr(cfg, "SHELL");
        configuration->user.expire = get_real_time_value(cfg_getint(cfg, "EXPIRE"));
        configuration->quota.limits.dqb_bhardlimit = cfg_getint(cfg, "BLOCKS_HARD_LIMIT");
        configuration->quota.limits.dqb_bsoftlimit = cfg_getint(cfg, "BLOCKS_SOFT_LIMIT");
        configuration->quota.limits.dqb_ihardlimit = cfg_getint(cfg, "INODES_HARD_LIMIT");
        configuration->quota.limits.dqb_isoftlimit = cfg_getint(cfg, "INODES_SOFT_LIMIT");
        configuration->quota.limits.dqb_btime = cfg_getint(cfg, "BLOCKS_TIME");
        configuration->quota.limits.dqb_itime = cfg_getint(cfg, "INODES_TIME");
        configuration->quota.path_quota = (char*) malloc(strlen(cfg_getstr(cfg, "PATH_QUOTA")) * sizeof(char));
        configuration->quota.path_quota = cfg_getstr(cfg, "PATH_QUOTA");

        return configuration;
}

int get_real_time_value (unsigned long seconds)
{
        unsigned long currentTime = time(NULL);

        if(seconds)
                return seconds += (unsigned long) currentTime;
        else
                return 0;
}
