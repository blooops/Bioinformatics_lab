#include "util.h"
#define NUMBER_OF_ATOMS 12000 
#define SQ(x) ((x) * (x))

void print_interaction(Atom p, Atom r) {
    float distance = SQ(p.x-r.x) + SQ(p.y-r.y) + SQ(p.z-r.z); 
    if(distance < 16.0)
        printf("%4s%6d%4s%6d - %4s%6d%4s%6d %8.3f\n", p.atom_type, p.slno, p.residue_type, p.residue_number, r.atom_type, r.slno, r.residue_type, r.residue_number, sqrt(distance));
}


int main() {
    int N = get_number_of_atoms("1asy.pdb");
    Atom* atoms = read_pdb("1asy.pdb", N);

    int protein_starting_id;
    int rna_starting_id;
    rna_starting_id = 0;
    int i;
    for( i=0; i<N; i++) {
        if(atoms[i].chain_id == 'A') {
            protein_starting_id = i;
            break;
        }
    }
    int j;
    for(i=protein_starting_id; i<N; i++) {
        j = rna_starting_id;
        for(; j<protein_starting_id; j++) {
            print_interaction(atoms[i], atoms[j]);
        }
    }

    free(atoms);
    return 0;
}

