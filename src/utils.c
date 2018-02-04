#include "pam_module.h"


void my_cleanup(pam_handle_t *pamh, void *data, int err)
{
	(void) pamh;
	(void) err;

	if(data)
	{
		memset(data, 0, strlen(data));
		free(data);
	}	
}

char	*firstInCapital(const char *str)
{
  char	*ret;

  if (!str || !str[0] || (ret = malloc(strlen(str))) == NULL)
    return (NULL);
  strcpy(ret, str);
  if (ret && ret[0] && ret[0] <= 'z' && ret[0] >= 'a')
    ret[0] += 'A' - 'a';
  return (ret);
}