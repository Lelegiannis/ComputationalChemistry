#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Atom.h"

#define COV_RAD_CONST 1.2F

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

float atom_bondLength(Atom atom1,Atom atom2){
	float xdiff = atom1->x - atom2->x;
	float ydiff = atom1->y - atom2->y;
	float zdiff = atom1->z - atom2->z;

	float lengthSquared = xdiff*xdiff + ydiff*ydiff + zdiff*zdiff;

	return sqrtf(lengthSquared);
}

void atom_destroy(Atom atom){
	if(atom != NULL){
		free(atom);
	}
}

float atom_covalentRadius(Atom atom){
	if(atom->type[0] == 'H' && atom->type[1] == '\0'){
		return 0.37F;
	}else if(atom->type[0] == 'O' && atom->type[1] == '\0'){
		return 0.73F;
	}else if(atom->type[0] == 'C' && atom->type[1] == '\0'){
		return 0.77F;
	}else if(atom->type[0] == 'N' && atom->type[1] == '\0'){
		return 0.75F;
	}else{
		return 0.0F;
	}
}

void atom_printBondGraph(Atom* atoms,int n){
	int i,j;
	for(i = 0; i < n; i++){
		printf("%c%c:",atoms[i]->type[0],atoms[i]->type[1]);
		for(j = 0; j < n; j++){
			float i_covalentRadius = atom_covalentRadius(atoms[i]);
			float j_covalentRadius = atom_covalentRadius(atoms[j]);
			float distance = atom_bondLength(atoms[i],atoms[j]);
			if(distance == 0.0F){
				continue;
			}

			if(distance <= COV_RAD_CONST*(i_covalentRadius + j_covalentRadius)){
				printf(" %d",j);
			}
		}
		printf("\n");
	}
}
