#ifndef ATOM_H
#define ATOM_H

typedef struct Atom *Atom;

void atom_print(Atom atom);

Atom atom_parseXYZ(char* xyzAtomLine);

Atom atom_parsePDB(char* pdbAtomLine);

void atom_destroy(Atom atom);

#endif
