#include "configParser.h"

extern cfg_opt_t opts[];

int initialize_config (cfg_t *cfg, char *config_file)
{
        cfg = cfg_init(opts, CFGF_NONE);
        if (cfg_parse(cfg, config_file) == CFG_PARSE_ERROR) {
                return -1;
        }
        return 0;
}

void load_config (struct Config *configuration, cfg_t cfg)
{
        configuration->column_name = cfg_getstr(cfg, "COLUMN_NAME");
        configuration->column_surname = cfg_getstr(cfg, "COLUMN_SURNAME");
        configuration->password_length = cfg_getint(cfg, "PASSWORD_LEN");
        configuration->uidsRange->min_uid = cfg_getint(cfg, "MIN_UID");
        configuration->uidsRange->max_uid = cfg_getint(cfg, "MAX_UID");
        configuration->user->gid = cfg_getint(cfg, "GID");
        configuration->user->home = cfg_getstr(cfg, "HOME");
        configuration->user->change = get_real_time_value(cfg_getint(cfg, "CHANGE"));
        configuration->user->class_group = cfg_getstr(cfg, "CLASS");
        configuration->user->shell = cfg_getstr(cfg, "SHELL");
        configuration->user->expire = get_real_time_value(cfg_getint(cfg, "EXPIRE"));
        configuration->quota->limits->dqb_bhardlimit = cfg_getint(cfg, "BLOCKS_HARD_LIMIT");
        configuration->quota->limits->dqb_bsoftlimit = cfg_getint(cfg, "BLOCKS_SOFT_LIMIT");
        configuration->quota->limits->dqb_ihardlimit = cfg_getint(cfg, "INODES_HARD_LIMIT");
        configuration->quota->limits->dqb_isoftlimit = cfg_getint(cfg, "INODES_SOFT_LIMIT");
        configuration->quota->limits->dqb_btime = cfg_getint(cfg, "BLOCKS_TIME");
        configuration->quota->limits->dqb_itime = cfg_getint(cfg, "INODES_TIME");
        configuration->quota->path_quota = cfg_getstr(cfg, "PATH_QUOTA");
}

int get_real_time_value (unsigned long seconds)
{
        time_t currentTime;
        time(&currentTime);

        if(seconds)
                return seconds += (unsigned long) currentTime;
        else
                return 0;
}
