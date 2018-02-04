NAME 	= pam_module.so

CFLAGS 	= -fPIC -fno-stack-protector -W -Wall -Wextra

SRC 	=	src/pam_module.c 	\
			src/utils.c 		\
			src/container.c

OBJ 	= $(SRC:.c=.o)

CP 		= cp

RM 		=	rm -rf

all: $(NAME)

$(NAME):$(OBJ)
	gcc $(OBJ) -shared -rdynamic -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

check:
ifeq ("$(wildcard /lib/security)", "")
	@echo "\npam_module is not installed\n"
else
	@echo "\npam_module is actually installed\n"
endif

test: 
	@echo "\nLOL ON A PAS DE TEST\n"

install:
ifneq ("$(wildcard /lib/security)", "")
	@echo "\npam_module is actually installed\n"
else
	apt-get install -y cryptsetup gcc libcryptsetup-dev libpam0g-dev
	make
	@mkdir /lib/security
	@$(CP) $(NAME) /lib/security/$(NAME)
	@echo "auth optional pamela.so" >> /etc/pam.d/common-auth
	@echo "session optional pamela.so" >> /etc/pam.d/common-session
	@echo "account optional pamela.so" >> /etc/pam.d/common-account
	@echo "password optional pamela.so" >> /etc/pam.d/common-password
	@echo "\nYour pam_module was successfully installed\n"
endif

uninstall:
ifeq ("$(wildcard /lib/security)", "")
	@echo "\npam_module is not installed\n"
else
	make clean
	@$(RM) /lib/security
	@head -n -1 /etc/pam.d/common-auth > /tmp/common-auth && mv /tmp/common-auth /etc/pam.d/common-auth
	@head -n -1 /etc/pam.d/common-session > /tmp/common-session && mv /tmp/common-session /etc/pam.d/common-session
	@head -n -1 /etc/pam.d/common-account > /tmp/common-account && mv /tmp/common-account /etc/pam.d/common-account
	@head -n -1 /etc/pam.d/common-password > /tmp/common-password && mv /tmp/common-password /etc/pam.d/common-password
	@echo "\nYour pam_module was successfully uninstalled\n"
endif