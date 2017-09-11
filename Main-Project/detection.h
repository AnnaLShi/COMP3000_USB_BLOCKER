#ifndef DETECTION_H_
#define DETECTION_H_
#include <libudev.h>
#include <stdio.h>

int config_udev(struct udev**, struct udev_monitor**);
int createUSBdir();
int search_usb(struct udev **udev, struct udev_monitor **moni, struct udev_device * *dev);


#endif 
