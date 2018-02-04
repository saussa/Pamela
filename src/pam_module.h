#ifndef PAM_MODULE_H
# define PAM_MODULE_H

#define PAM_SM_AUTH
#define BUFF 2048

#include <security/pam_modules.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

char	*firstInCapital(const char *str);
void my_cleanup(pam_handle_t *pamh, void *data, int err);
void close_container(const char *user);
void open_container(const char *usr, const char *pwd);

#endif /* PAM_MODULE_H */