#ifndef MOLECULE_H
#define MOLECULE_H

typedef struct Molecule *Molecule;

Molecule molecule_parseXYZ(char* xyzFilePath);

Molecule molecule_parsePDB(char* pdbFilePath);

void molecule_destroy(Molecule molecule);

#endif
