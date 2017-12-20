#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <sys/syscall.h>

#define BLUE        "\x1b[34m"
//#define YELLOW      "\x1b[33m"
#define BOLD        "\x1b[1m"
#define RESET       "\x1b[0m"


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

void ls(char *path){
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

int main (int argc, char *argv[]){

//ls(argv[1]);

}
