/*  ECAM 2017
    STENHOUSE Quentin
    MyFunc is a simple implementation of a function using Mycp, Myls and Myrm in C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <time.h>
#include <fcntl.h>
#include <sys/syscall.h>

#define BLUE        "\x1b[34m"
#define BOLD        "\x1b[1m"
#define RESET       "\x1b[0m"


void ls(char *path){
    struct linux_dirent {
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

    int fd, n;
    struct linux_dirent *namelist;
    char buf[1024];
    char *file_path;
    char d_type;
    char file_name[255];

    file_path = path;
    if(file_path == NULL){
        file_path = ".";
    }
    // open file_path file or directory and get the file descriptor
    fd = open(file_path, O_RDONLY);
    if(fd == -1){
        printf("myls: cannot access'%s': No such file or directory\n", file_path);
    }
   /* else if(is_regular_file(file_path)){
        // print file name when the file is a regular file
        printf("%s\n", file_path);
    }*/
    else {
        do{
            /* reads several linux_dirent structures from the directory referred to
                by the open file descriptor fd into the buffer pointed to by buf. */
            n = syscall(SYS_getdents, fd, buf, 1024);
            for(int i = 0; i < n;) {
                namelist = (struct linux_dirent *) (buf + i);
                // store file type in d_type
                d_type = *(buf + i + namelist->d_reclen - 1);
                strncpy(file_name, namelist->d_name, 254);
                // ignore entries starting by "."
                if(file_name[0] !=  '.'){
                // print directory entries in blue
                    if(d_type == 4){
                        printf(BLUE BOLD "%s " RESET, namelist->d_name);
                    }
                    // print file entries
                    else {
                        printf("%s ", namelist->d_name);
                    }
                    }
                i += namelist->d_reclen;
                }
        }while(n > 0);
        printf("\n");
    }
}

int unlk;

int is_regular_file(char *path){
    struct stat path_stat;
    // stats the file pointed to by path and fills in path_stat
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

void rm(char *rm_value){
    if(rm_value != NULL){
        if (is_regular_file(rm_value)){
            // deletes the file given its pathname
            unlk = unlink(rm_value);
            if(unlk == 0){
                // keep going
            }
            else {
                printf("Myrm: cannot remove '%s': No such file", rm_value);
            }
        }
        else {
            printf("Myrm: cannot remove '%s': No such file or Is not a regular file\n", rm_value);
        }
    }
    else {
        printf("Myrm: missing operand\n");
    }
}

/*
This procedure is the basic procedure of the mycp command.
It will open a file in reading and the other in writing and will write what's
in the reading file in the writing file.
*/
void copy (char * fil, char * wit)
{
	FILE *file;
	FILE *write;
	char line [256];
	char linec [256];
	file = fopen(fil,"r");
	write = fopen(wit,"w");
	if(file != NULL)
		{
		while (fgets (line, sizeof line, file)!= NULL) //While boucle reads and writes all the lines from file to write.
			{
			fputs (line, write);
			strcpy (line, linec);
			}
		fclose(file);
		fclose(write);
		}
	else
		{
		printf("Error in the directories \n"); //Error appends if no argument are input.
		}
}

int c;
int flag_multiple = 0;
int flag_path = 0;
char * MyPath = "/home/debian/OS_Project/MyValidDatas/";
char * MyPath2 = "/home/debian/OS_Project/datas/";

struct option longopts[] = {
	{"path", no_argument, NULL, 'p'},
	{"multiple", no_argument, NULL, 'm'},
	{0, 0, 0, 0}
};

int main (int argc, char * argv[], char * envp[])
{
while((c = getopt_long(argc, argv,"pm", longopts, NULL)) != -1) // Put the getopt_long in motion
{
	switch (c)
	{
		case 'p':
			flag_path = 1;
		break;

		case 'm':
			flag_multiple = 1;
		break;

		default:
			printf("Option is invalid: ignored \n");
		break;
	}
}

if (flag_path == 1){
	char * MyPath1 = argv[3];
	char * MyFileName1 = argv[2];
    char * str1 = (char *) malloc(1 + strlen(MyPath1)+ strlen(MyFileName1));
    strcpy(str1, MyPath1);
    strcat(str1, MyFileName1);
    char * str2 = (char *) malloc(1 + strlen(MyPath2)+ strlen(MyFileName1));
    strcpy(str2, MyPath2);
    strcat(str2, MyFileName1);
	copy(str2, str1);
	rm(str2);
	ls(argv[3]);
}
else if (flag_multiple == 1){
	struct linux_dirent {
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};

    int fd, n;
    struct linux_dirent *namelist;
    char buf[1024];
    char *file_path;
    char d_type;
    char file_name[255];

    file_path = argv[2];
    if(file_path == NULL){
        file_path = ".";
    }
    // open file_path file or directory and get the file descriptor
    fd = open(file_path, O_RDONLY);
    if(fd == -1){
        printf("Cannot access'%s': No such file or directory\n", file_path);
    }
    else {
        do{
            /* reads several linux_dirent structures from the directory referred to
                by the open file descriptor fd into the buffer pointed to by buf. */
            n = syscall(SYS_getdents, fd, buf, 1024);
            for(int i = 0; i < n;) {
                namelist = (struct linux_dirent *) (buf + i);
                strncpy(file_name, namelist->d_name, 254);
                // ignore entries starting by "."
                if(file_name[0] !=  '.'){
                    char * MyPathf = argv[3];
                    char * strf = (char *) malloc(1 + strlen(MyPathf)+ strlen(namelist->d_name));
                    strcpy(strf, MyPathf);
                    strcat(strf, namelist->d_name);
                    char * strb = (char *) malloc(1 + strlen(file_path)+ strlen(file_name));
                    strcpy(strb, file_path);
                    strcat(strb, file_name);
                    copy(strb, strf);
                    rm(strb);
                    }
                i += namelist->d_reclen;
            }
        }while(n > 0);
        printf("\n");
    }
}
else if (flag_path == 0 && flag_multiple == 0){
    //Combine the name of the file and the path where we want to put it
	char * MyFileName2 = argv[1];
	char * str3 = (char *) malloc(1 + strlen(MyPath)+ strlen(MyFileName2));
	strcpy(str3, MyPath);
	strcat(str3, MyFileName2);
    //Use the folder where the data are stored and takes the data that we want to move
	char * str4 = (char *) malloc(1 + strlen(MyPath2)+ strlen(MyFileName2));
	strcpy(str4, MyPath2);
	strcat(str4, MyFileName2);
	copy(str4, str3);
	rm(str4);
	ls(MyPath);
}
}
