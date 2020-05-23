#ifndef PASSWDUPDATER_H_
#define PASSWDUPDATER_H_

#include<pwd.h>
#include<stdio.h>
#include<stdlib.h>

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
void create_random_string(char *random_string, size_t length);

#endif // PASSWDUPDATER_H_