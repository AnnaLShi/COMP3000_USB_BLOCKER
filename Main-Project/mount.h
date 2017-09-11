#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>

int open_file(char *);
int unmount_USB(const char **location);
int check_mounted();
int mount_USB(const char **);
int config_arr();

struct USB_INFO {
	const char *dev_location;
	const char *med_location;
} ;
