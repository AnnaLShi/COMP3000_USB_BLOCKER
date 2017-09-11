#include "mount.h"


struct USB_INFO usb_info[100];

// this is highly restricted at this point in the future replace this with dynamic arrays instead please.
int arr_size = 0;
int is_config = -1;
int version = 0;

int config_arr() {
  	int i;

	for (i = 0; i < 100; i++) {
		usb_info[i].dev_location = calloc(sizeof(char*), 100);
		usb_info[i].med_location = calloc(sizeof(char*), 100);
	}
	
	return 0;

}


int mount_USB(const char **location) {

	if (is_config == -1) {
		config_arr();
	}
	is_config = 0;
	char *test = calloc(sizeof(char*), 150);
	char *usb = calloc(sizeof(char*), 150 );
	char *combine = calloc(sizeof(char*), 150);
	
	char *target = calloc(sizeof(const char*), 150);
	const char *filesystemtype = calloc(sizeof(const char*), 150);
	unsigned long mountfl = 0; 

	// assign
//	strcat(target, *location);



	// call the certain USB, blkid is a bit glitchy with this asspect if we had a bit more time we could have tried a different command or a library.
	// It keeps on sigfaulting during the actual use.
    strcat(test, "sudo blkid ");
	strcat(test, *location);
	strcat(test, " > usb.txt");
	system(test);


	FILE *fl = fopen("usb.txt", "r");
	fscanf(fl, "%[^\n]", usb);
	fclose(fl);
	// get LABEL
	char* found;
	char* tot = calloc(sizeof(char*), 150);
	char *temp = calloc(sizeof(char*), 150);
	int pos = found - usb;
	int total_pos;
    int re_pos = 0;
	char *t = "\"";
	

    found = strstr(usb, "UUID");
	pos = found - usb;
	if (pos > 0) {
	 total_pos = pos + 6;

	 while(usb[total_pos] != t[0]) {
		temp[re_pos] = usb[total_pos];
		re_pos++;
		total_pos++;
		} 
	}
	strcat(combine, "uid=");
	strcat(combine, temp);

   // covert string to char
	char *label =  calloc(sizeof(char*), 150);
	int i = 0;
	found = strstr(usb, "LABEL");
	pos = found - usb;
	if (pos > 0) {
		 total_pos = pos + 7;
		 while(usb[total_pos] != t[0]) {
			label[i] = usb[total_pos]; 
			total_pos++;
			i++;
		}
	
	}
	else {
		strcat(label, "USB");
		strcat(label, temp);
	}
		strcat(target, "/media/");
		strcat(target, label);

	
	char *temp1 = calloc(sizeof(char*), 150);
	re_pos = 0;
	found = strstr(usb, "TYPE");
	pos = found - usb;

	if (pos > 0) {
	  total_pos = pos + 6;
	 while(usb[total_pos] != t[0]) {
		temp1[re_pos] = usb[total_pos];
		re_pos++;
		total_pos++;
		} 
	}
	
// set UUID here and and make a directory. remove write protection
	int mk_dir = mkdir(target, 0777);
	if (mk_dir == -1) {
		// failed trying a different way
	}
	int successful = mount(*location, target, temp1, 0, NULL);
	if (successful == -1) {
	}
	

	strcat(usb_info[arr_size].dev_location, *location);
	strcat(usb_info[arr_size].med_location, target);
	arr_size++; 


	
	return 0;
}

int unmount_USB(const char **location) {
	int i;
	for (i = 0; i < arr_size ; i++) {
		if (strcmp(*location, usb_info[i].dev_location) == 0) {
			umount(usb_info[i].med_location);		
		}
	
	}
	// an new struct might be needed to help with this
	return 0;
}

int open_file(char *usb) {

    // this should only get multiple lines of only USB
	return 0;
}

int check_mounted() {
	return 0;
}

 
