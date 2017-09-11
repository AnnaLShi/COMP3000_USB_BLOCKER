#include "block.h"
 
// replace main with something else
// must run as sudo 
int block () {
   DIR* dir = opendir("/etc/udev/rules.d");
   FILE *fp = fopen("/etc/udev/rules.d/10-no-automount.rules", "r");
   if (!dir) {
	errno = ENOENT;
    printf("*** %s\n and udev maybe not installed on this system", strerror(errno));
    return -2;
   }
   if (fp) {
	return 0;
   }


   // check every status and if the commands has been success delivered, if not it would return -1
   // do error checking to make sure that it is written in the correct place or it maybe unhappy.	write a file but the file empty
	
   printf("File did not exist, setting one up right now...");
   int status;
   status = system("sudo touch /etc/udev/rules.d/10-no-automount.rules");
    
   if (WSTOPSIG(status)) {
       return -1;
    }
   system("sudo echo 'SUBSYSTEMS== \"usb\", ENV{UDISKS_AUTO} = \"0\", ENV{UDISKS_IGNORE}= \"1\" nnnnnnnnnnnnnn' >> /etc/udev/rules.d/10-no-automount.rules" );

    if (WSTOPSIG(status)) {
		printf("I am a little teapot");
       return -1;
    }
   status =  system("sudo udevadm control --reload-rules");
    if (WSTOPSIG(status)) {
       return -1;
    }
/**
   status = system("sudo gsettings set org.gnome.desktop.media-handling automount false");

   if (WSTOPSIG(status)) {
		// phone blocking kind of works?
		return -3;
	}
   status = system("sudo org.gnome.desktop.media-handling.autorun-never true"); **/
   
   return 0;
}
