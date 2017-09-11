#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



#include <string.h>
#include "block.h"
#include "detection.h"
#include "mount.h"

int diabox_detection();


int main(void)
{
		
		// configuration of block with udev
       int config_block;
    	config_block = block();
        
       if (config_block == -1) {
         printf("\nConfiguration of block unsucess of -1\n");
         printf("Please run sudo, the block can be sucessfully created in udev, next run throughs don't need sudo");
		 return -1;
       } 
       if (config_block == -2) {
          // directory error
		return -2;
       }

/// end 
       struct udev *udev;
       struct udev_device *dev;
       struct udev_monitor *mon;
        udev = udev_new();

       if (!udev) {
                printf("Can't create udev\n");
                exit(1);
        }

        mon = udev_monitor_new_from_netlink(udev, "udev");
	//	udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", "usb_device");
        udev_monitor_filter_add_match_subsystem_devtype(mon, "block", "partition");
        udev_monitor_enable_receiving(mon);



	//	int usb_count = 0;


//		int fd = udev_monitor_get_fd(mon);
		while (1) {
            dev = udev_monitor_receive_device(mon);
			 if (dev) {
				   printf("\n   Action: %s\n",udev_device_get_action(dev)); 
                    printf("   Node: %s\n", udev_device_get_devnode(dev));

                    printf("   Subsystem: %s\n", udev_device_get_subsystem(dev));

                    printf("   Devtype: %s\n", udev_device_get_devtype(dev)); 
				const char *test = udev_device_get_devnode(dev);
				if (strcmp(udev_device_get_action(dev), "add") == 0) {
					int choice = diabox_detection();		
					if (choice  == 0) {		
						mount_USB(&test);
					}
					else {

						// nothing happens except for the issues
					}
						
					}
				if (strcmp(udev_device_get_action(dev), "remove") == 0) {
					unmount_USB(&test);
					system(" notify-send 'USB Removed' ");
				}
			 	udev_device_unref(dev);
				}

}
        return 0;
}

int diabox_detection() {
	
	char *locate = calloc(sizeof(char*), 1000);
	FILE *fl = popen("./dia_box.sh", "r");
	fscanf(fl, "%[^\n]", locate);
	pclose(fl);
	
	if (strcmp(locate, "0") == 0) {
		return 0;
	}
 	else if (strcmp(locate, "-1") == 0) {
		return -1;
	} 

	return -1;

}
