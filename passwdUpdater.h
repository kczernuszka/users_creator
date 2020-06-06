#ifndef PASSWDUPDATER_H_
#define PASSWDUPDATER_H_

#include<pwd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "configParser.h"

#define LOGIN_LENGTH 32
#define PASSWORD_LENGTH 8
#define _S(x)	x ?: ""

struct User {
    char* login;
    unsigned int uid;
    unsigned int gid;
    char *name;
    char *home;
    char *shell;
};

int putpwent (const struct passwd *passwd, FILE *stream);
int passwd_update (struct User user, FILE *passwd_file, FILE *master_file);
char* create_user_login(const char *name, const char *surname);
char* create_home_directory(const char *home, const char *login);
void create_random_string(char *random_string, size_t length);

#endif // PASSWDUPDATER_H_