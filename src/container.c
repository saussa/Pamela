#include "pam_module.h"

void open_container(const char *usr, const char *pwd)
{
	char *capUser = firstInCapital(usr);
	char cmd[BUFF];

	sprintf(cmd, "echo \"%s\" | sudo cryptsetup luksOpen /home/%s/cipher%s cipher%s && sudo mount /dev/mapper/cipher%s /home/%s/cipher ; echo \"%s\" | sudo cryptsetup luksOpen /home/shared/cipherShared cipherShared && sudo mount /dev/mapper/cipherShared /home/shared/cipher", pwd, usr, capUser, capUser, capUser, usr, pwd);
}

void close_container(const char *usr)
{
  char *capUser = firstInCapital(usr);
  char cmd[BUFF];

  sprintf(cmd, "sudo umount /home/%s/cipher ; sudo cryptsetup luksClose cipher%s ; sudo umount /home/shared/cipher ; sudo cryptsetup luksClose cipherShared", usr, capUser);
  system(cmd);
}
