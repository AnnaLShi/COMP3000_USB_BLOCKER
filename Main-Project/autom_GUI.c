/**
This is to develop the pop up of the mount function,
To see how the graphics library.
This part of the program would deal with the GUI
So this would function like a view function.


Note: the main should be removed later in development and header files should be used.

system is used to look at the kitten
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <block.c>

char is_detected[1024];




int main() {
	int selected;
	int is_accepted = system("kdialog --title 'USB detected' --yesno 'This will work and be awesome:' > result.txt");
	char *k = (char*)calloc(sizeof(char*), 3);  
	 
	 
	 // add something here
	 if (is_accepted == 0) {
		 selected = system("kdialog --checklist 'Open with...' 1 'Folder' off \ 2 'test' on >  choice.txt");
		FILE *file = fopen("choice.txt", "r");
		fscanf(file, "%[^\n]", k);
		fclose(file);
	 }
		
		printf("%c", (char)k[1]);
	 if (k[1] == '1') {
		 // it's just going to open something
		 system("nautilus ~/");
	 } 
	 
	return 0;
}
