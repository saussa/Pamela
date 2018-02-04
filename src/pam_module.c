#define PAM_SM_AUTH
#define BUFF 2048


#include "pam_module.h"

PAM_EXTERN int	pam_sm_authenticate(pam_handle_t *pamh, int flags, int ac, const char **av)
{
  int		ret;
  char		*pwd;
  const char	*usr;
  
  (void) ac;
  (void) av;
  (void) flags;

  ret = pam_get_user(pamh, &usr, "Username: ");
  
  if (ret != PAM_SUCCESS)
    return (ret);

  pam_get_item(pamh, PAM_AUTHTOK, (const void **)&pwd);

  pam_set_data(pamh, "pam_module_pass", strdup(pwd), &my_cleanup);
  
  printf("[Pamela]: enter your Password\n");
  return (PAM_SUCCESS);
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int ac, char **av)
{
  int ret = 0;
  const char *usr;
  const char *pwd;


  (void) flags;
  (void) ac;
  (void) av;

  if ((ret != pam_get_user(pamh, &usr, "Username: ")) != PAM_SUCCESS)
    return (ret);
  if ((ret != pam_get_data(pamh, "pam_user_pass", (const void **)&pwd)) != PAM_SUCCESS)
    return (ret);
  open_container(usr, pwd);

  return (PAM_SUCCESS);
}
  
PAM_EXTERN int  pam_sm_close_session(pam_handle_t *pamh, int flags, int ac, const char **av)
{
  char  *usr;
  int ret = 0;

  (void) flags;
  (void) ac;
  (void) av;

  if ((ret = pam_get_user(pamh, (const char **)&usr, "Username: ")) != PAM_SUCCESS)
    return (ret);

 close_container(usr);

  return (PAM_SUCCESS);
}