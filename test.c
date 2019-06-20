// test.c

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int num_dirs = 0;

int main(){
	
	/*
	FILE *fp;
  	char path[1035];

  	//Open the command for reading.
 	 fp = popen("/bin/ls", "r");
 	 if (fp == NULL) {
 	   printf("Failed to run command\n" );
 	   exit(1);
 	 }

  	// Read the output a line at a time - output it.
  	while (fgets(path, sizeof(path)-1, fp) != NULL) {
  	  printf("%s", path);
  	}

  	// close
  	pclose(fp);
  	*/

  	FILE *file1;
    char dirs1[1035];
    int MAX = sizeof(dirs1);
    file1 = popen("/bin/ls", "r");
    while(fgets(dirs1, MAX-1, file1) != NULL) num_dirs++;
    pclose(file1);

    FILE *file2;
    char dirs2[1035];
    file2 = popen("/bin/ls", "r");
    char dir_names[num_dirs][1035];
    int idx = 0;
    while(fgets(dirs2, MAX-1, file2) != NULL){
        strcpy(dir_names[idx], dirs2);
        idx++;
    }
    pclose(file2);

    printf("num dirs: %d\n", num_dirs);

    for(int i = 0; i < num_dirs; i++) printf("%s", dir_names[i]);

    return 0;
}