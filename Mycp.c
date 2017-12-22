/*  ECAM 2017
    STENHOUSE Quentin
    Mycp is a simple implementation of a cp in C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

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

int main (int argc, char *argv[]){

copy(argv[1], argv[2]);

}
