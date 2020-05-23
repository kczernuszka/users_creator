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

int passwd_update (struct User user, FILE *passwd_file, FILE *master_file)
{
        struct passwd *p = (struct passwd*) malloc(sizeof(struct passwd));

        p->pw_name = user.login;
        p->pw_passwd = user.password;
        p->pw_uid = user.uid;
        p->pw_gid = user.gid;
        p->pw_gecos = user.name;
        p->pw_dir = user.home;
        p->pw_shell = user.shell;

        fseek(passwd_file, 0, SEEK_END);  
        if (putpwent(p, passwd_file) == -1) {
                return -1;
        }

        return 0;
}
