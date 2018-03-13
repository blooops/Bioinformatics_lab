// Program to calculate the center of mass (geometric center) of a protein using it's coords in PDB
#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ALA 0
#define ARG 1
#define ASN 2
#define ASX 3
#define CYS 4
#define GLN 5
#define GLU 6
#define GLX 7
#define GLY 8
#define HIS 9
#define ILE 10
#define LEU 11
#define LYS 12
#define MET 13
#define PHE 14 
#define PRO 15
#define SER 16
#define THR 17
#define TRP 18
#define TYR 19
#define UNK 20
#define VAL 21


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

int get_length_of_chain(char* filename);

#endif
