#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

//int main (int argc, char *argv[]){

int c, unlk;
//char *rm_value;
//*rm_value = argv[1];

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
                printf("myrm: cannot remove '%s': No such file", rm_value);
            }
        }
        else {
            printf("myrm: cannot remove '%s': No such file or Is not a regular file\n", rm_value);
        }
    }
    else {
        printf("myrm: missing operand\n");
    }
}
//rm_value = argv[1];
//rm(argv[1]);

//}
