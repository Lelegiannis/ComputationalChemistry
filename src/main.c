#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globalDefs.h"

typedef struct Atom{
	char type[2];
	float x;
	float y;
	float z;
}Atom;

void printAtom(Atom atom){
	printf("Type: %c%c\n",atom.type[0],atom.type[1]);
	printf("Coordinates: %f %f %f\n",atom.x,atom.y,atom.z);
}

Atom parseAtom(char* xyzLine){
	Atom atom;
	
	char* xyzType = strtok(xyzLine,"\t ");
	if(xyzType == NULL){
		fprintf(stderr,"File provided does not follow the xyz format.\n");
		exit(-1);
	}
	if(strlen(xyzType) != 1 && strlen(xyzType) != 2){
		fprintf(stderr,"File provided does not follow the xyz format.\n");
		exit(-1);
	}
	atom.type[0] = xyzType[0];
	atom.type[1] = xyzType[1];

	char* xyz_x = strtok(NULL,"\t ");
	if(xyz_x == NULL){
		fprintf(stderr,"File provided does not follow the xyz format.\n");
		exit(-1);
	}
	atom.x = strtof(xyz_x,NULL);
	/*somehow check if xyz_x represented a valid float number and the convertion was properly done*/

	char* xyz_y = strtok(NULL,"\t ");
	if(xyz_y == NULL){
		fprintf(stderr,"File provided does not follow the xyz format.\n");
		exit(-1);
	}
	atom.y = strtof(xyz_y,NULL);
	/*check if convertion was done properly*/

	char* xyz_z = strtok(NULL,"\t ");
	if(xyz_z == NULL){
		fprintf(stderr,"File provided does not follow the xyz format.\n");
		exit(-1);
	}
	atom.z = strtof(xyz_z,NULL);
	/*check if convertion was done properly*/

	return atom;
}

char* readLine(FILE* file){
	static char* buffer = NULL;

	/*Clean function when file is NULL*/
	if(file == NULL){
		if(buffer != NULL){
			free(buffer);
		}
		buffer = NULL;
		return NULL;
	}

	if(buffer != NULL){
		free(buffer);
		buffer = NULL;
	}

	unsigned int buffer_size = 0;
	unsigned int bytes_read = 0;
	unsigned int i;

	do{
		buffer_size += BLOCK_SIZE;

		buffer = realloc(buffer,buffer_size);
		if(buffer == NULL) return NULL;
		for(i = buffer_size-BLOCK_SIZE;i < buffer_size;i++) buffer[i] = 0;

		fgets(buffer+bytes_read,BLOCK_SIZE,file);
		bytes_read += BLOCK_SIZE-1; /*if we read less chars than that we exit the loop*/
	}while((feof(file) == 0) && (strchr(buffer,'\n') == NULL));

	return buffer;
}

int main(int argc,char* argv[]){
	if(argc <= 1){
		fprintf(stderr,"The name of at least one xyz file must be passed as a parameter for the program to work.\n");
		return -1;
	}

	FILE *xyzFP;
	xyzFP = fopen(argv[1],"r");
	if(xyzFP == NULL){
		perror("Could not open xyz file specified.\n");
		return -1;
	}else{
		printf("Successfully opened file.\n");
	}

	char* line;
	line = readLine(xyzFP); /*Number of atoms*/
	line = readLine(xyzFP); /*Comments*/
	unsigned int atomCount = 0;
	while(!feof(xyzFP)){
		line = readLine(xyzFP);
		if(line == NULL){
			perror("Failed to read line from file.\n");
			fclose(xyzFP);
			return -1;
		}
		if(line[0] == '\0') break;

		Atom atom = parseAtom(line);
		printf("Atom %d\n",++atomCount);
		printAtom(atom);
		printf("\n");
	}

	return 0;
}
