#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Atom.h"

struct Atom{
	char type[2];
	float x;
	float y;
	float z;
};

void atom_print(Atom atom){
	printf("Type: %c%c\n",atom->type[0],atom->type[1]);
	printf("Coordinates: %f %f %f\n",atom->x,atom->y,atom->z);
}

Atom atom_parseXYZ(char* xyzAtomLine){
	Atom atom = malloc(sizeof(struct Atom));
	if(atom == NULL){
		return NULL;
	}

	char* xyzType = strtok(xyzAtomLine,"\t ");
	if(xyzType == NULL){
		fprintf(stderr,"File provided does not follow the xyz format.\n");
		exit(-1);
	}
	if(strlen(xyzType) != 1 && strlen(xyzType) != 2){
		fprintf(stderr,"File provided does not follow the xyz format.\n");
		exit(-1);
	}
	atom->type[0] = xyzType[0];
	atom->type[1] = xyzType[1];

	char* xyz_x = strtok(NULL,"\t ");
	if(xyz_x == NULL){
		fprintf(stderr,"File provided does not follow the xyz format.\n");
		exit(-1);
	}
	atom->x = strtof(xyz_x,NULL);
	/*somehow check if xyz_x represented a valid float number and the convertion was properly done*/

	char* xyz_y = strtok(NULL,"\t ");
	if(xyz_y == NULL){
		fprintf(stderr,"File provided does not follow the xyz format.\n");
		exit(-1);
	}
	atom->y = strtof(xyz_y,NULL);
	/*check if convertion was done properly*/

char* xyz_z = strtok(NULL,"\t ");
	if(xyz_z == NULL){
		fprintf(stderr,"File provided does not follow the xyz format.\n");
		exit(-1);
	}
	atom->z = strtof(xyz_z,NULL);
	/*check if convertion was done properly*/

	return atom;
}

Atom atom_parsePDB(char* pdbAtomLine){
	/*Under construction*/
	return NULL;
}

void atom_destroy(Atom atom){
	if(atom != NULL){
		free(atom);
	}
}
