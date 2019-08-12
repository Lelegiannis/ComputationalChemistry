#include <stdio.h>
#include <stdlib.h>
#include "Atom.h"
#include "Tools.h"
#include "globalDefs.h"

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

	/*Read Number of atoms in xyz file*/
	char* line = readLine(xyzFP);
	if(line == NULL){
		perror("Failed to read first line from xyz file.\n");
		fclose(xyzFP);
		return -1;
	}
	int numOfAtoms = atoi(line);
	/*Check if first line was indeed an integer*/

	/*Read comments*/
	line = readLine(xyzFP);

	Atom* allAtoms = malloc(numOfAtoms*sizeof(Atom));
	if(allAtoms == NULL){
		perror("Could not create atom array");
		fclose(xyzFP);
		return -1;
	}

	int atomCount;
	for(atomCount = 0; atomCount < numOfAtoms; atomCount++){
		line = readLine(xyzFP);
		if(line == NULL){
			perror("Failed to read line from file.\n");
			fclose(xyzFP);
			return -1;
		}

		allAtoms[atomCount] = atom_parseXYZ(line);
		printf("Atom %d\n",atomCount+1);
		atom_print(allAtoms[atomCount]);
		printf("Distance from first: %f\n",atom_bondLength(allAtoms[0],allAtoms[atomCount]));
		printf("-----------------\n");
	}

	atom_printBondGraph(allAtoms,numOfAtoms);

	for(atomCount = 0; atomCount < numOfAtoms; atomCount++){
		atom_destroy(allAtoms[atomCount]);
	}
	free(allAtoms);
	return 0;
}
