// Program to calculate the center of mass (geometric center) of a protein using it's coords in PDB
#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct atom {
    int slno;
    char atom_type[4];
    char residue_type[4];
    int residue_number;
    char chain_id;
    float x, y, z;
    float B;
} Atom;

int get_number_of_atoms(char* filename);
Atom* read_pdb(char* pdbfilename, int number_atoms);

#endif
