#include <stdlib.h>
#include "Molecule.h"
#include "Atom.h"
#include "Tools.h"

struct Molecule{
	Atom* atoms;
	int numOfAtoms;
};

Molecule molecule_parseXYZ(char* xyzFilePath){
	FILE *xyzFP;
	xyzFP = fopen(xyzFilePath);
	if(xyzFP == NULL){
		perror("Could not open xyz file specified.\n");
		exit(1);
	}

	/*Read number of atoms in xyz file*/
	char* line = readLine(xyzFP);
	if(line == NULL){
		perror("Failed to read first line of xyz file.\n");
		fclose(xyzFP);
		exit(1);
	}
	//Skip comments (what is the comment syntax on xyz files?)
	int numOfAtoms = atoi(line);

	/*Create Molecule Atom array*/
	Molecule molecule = malloc(sizeof(struct Molecule));
	if(molecule == NULL){
		perror("Could not allocate memory for new molecule object.\n");
		fclose(xyzFile);
		exit(1);
	}
	molecule->atoms = malloc(numOfAtoms*sizeof(struct Atom));
	if(molecule->atoms == NULL){
		perror("Could not allocate memory for new molecule atom array.\n");
		fclose(xyzFile);
		exit(1);
	}
	molecule->numOfAtoms = numOfAtoms;

	int atomCount;
	for(atomCount = 0; atomCount < numOfAtoms; atomCount++){
		line = readLine(xyzFP);
		if(line == NULL){
			fprintf(stderr,"Failed to read atom %d from xyz file.\n",atomCount);
			fclose(xyzFile);
			exit(1);
		}
		//Skip comments

		molecule->atoms[atomCount] = atom_parseXYZ(line);
	}

	return molecule;
}

Molecule molecule_parsePDB(char* pdbFilePath){
	fprintf(stderr,"PDB file format is not yet supported.\n");
	exit(1);
}

void molecule_destroy(Molecule molecule){
	int i;
	for(i = 0; i < molecule->numOfAtoms; i++){
		atom_destroy(molecule->atoms[i]);
	}
	free(molecule->atoms);
	free(molecule);
	molecule = NULL;
}
