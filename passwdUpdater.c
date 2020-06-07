#include "passwdUpdater.h"

int putpwent (const struct passwd *passwd, FILE *stream)
{
        if (passwd == NULL || stream == NULL) {
                return -1;
        }

        if (fprintf(stream, "%s:%s:%lu:%lu:%s:%s:%s\n",
	        passwd->pw_name, _S (passwd->pw_passwd),
		    (unsigned long int) passwd->pw_uid,
		    (unsigned long int) passwd->pw_gid,
 		    _S (passwd->pw_gecos), _S (passwd->pw_dir), 
		    _S (passwd->pw_shell)) < 0)
                return -1;

        return 0;
}

int passwd_update (struct User user, FILE *passwd_file)
{
        struct passwd *p = (struct passwd*) malloc(sizeof(struct passwd));

        p->pw_name = user.login;
        p->pw_passwd = "x";
        p->pw_uid = user.uid;
        p->pw_gid = user.gid;
        p->pw_gecos = user.class_name;
        p->pw_dir = user.home;
        p->pw_shell = user.shell;

        fseek(passwd_file, 0, SEEK_END);  
        if (putpwent(p, passwd_file) == -1) {
                return -1;
        }

        return 0;
}

char* create_user_login(const char *name, const char *surname)
{
        char *login = (char*) malloc(LOGIN_LENGTH * sizeof(char));
        strncat(login, name, 1);
        strcat(login, ".");
        strcat(login, surname);

        while(getpwnam(login) != NULL) {
                strcat(login, "1");
        }
        
        if(strlen(login) < 32)
                return login;
        else
                return NULL;
}

char* create_home_directory(const char *home, const char *login)
{
        char *home_path = (char*) malloc(HOME_PATH_LENGTH * sizeof(char));
        strcpy(home_path, home);
        strcat(home_path, "/");
        strcat(home_path, login);

        return home_path;
}

void create_random_string(char *random_string, size_t length) 
{
        char charset[] = "0123456789"
                   "abcdefghijklmnopqrstuvwxyz"
                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        while (length-- > 0) {
                size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
                *random_string++ = charset[index];
        }
        *random_string = '\0';
}

int get_free_uid(unsigned int uid, unsigned int max_uid) {
        while(getpwuid(uid) != NULL)
                ++uid;
        if(uid < max_uid)
                return uid;
        else
                return -1;
}
