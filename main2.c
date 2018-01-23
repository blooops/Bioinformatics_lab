#include "util.h"
#define NUMBER_OF_ATOMS 12000 

int main() {
    int N = get_number_of_atoms("1asy.pdb");
    Atom* atoms = read_pdb("1asy.pdb", N);

    int a_starts;
    int b_starts;
    int r_starts;
    int s_starts;
    int i;
    char current_chain_id = '';
    
    for(i=0; i<N; i+=) {
        if(current_chain_id != atoms[i].chain_id) {
            current_chain_id = atoms[i].chain_id;
            if(current_chain_id 
        }
    }

    free(atoms);
    return 0;
}

