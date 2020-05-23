#ifndef PASSWDUPDATER_H_
#define PASSWDUPDATER_H_

#include<pwd.h>
#include<stdio.h>
#include<stdlib.h>

#define _S(x)	x ?: ""

struct User {
    char* login;
    char* password;
    unsigned int uid;
    unsigned int gid;
    char *name;
    char *home;
    char *shell;
};

int putpwent (const struct passwd *passwd, FILE *stream);
int passwd_update (struct User user, FILE *passwd_file, FILE *master_file);

#endif // PASSWDUPDATER_H_