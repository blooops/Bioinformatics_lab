#include "util.h"

typedef struct f2 {
    float a,b;
} f2;

f2 get_average_b(Atom* atoms, int start_index, int stop_index) {
    float main_avg_b = 0.0f;
    float side_avg_b = 0.0f;
    int i;
    int count_main =0;
    int count_side=0;
    for(i = start_index; i<=stop_index; i++) {
        if(strcmp(atoms[i].atom_type, "CA ") ==0 || strcmp(atoms[i].atom_type, "N  ") ==0 || strcmp("C  ", atoms[i].atom_type)==0 || strcmp("O  ", atoms[i].atom_type)==0) {
            count_main++;
            main_avg_b += atoms[i].B;
        }
        else {
            count_side++;
            side_avg_b += atoms[i].B;
        }
        // DEBUG
        //printf(" count_main = %d count_side = %d\n", count_main, count_side);
        // DEBUG
    }

    side_avg_b /= count_side;
    main_avg_b /= count_main;
    f2 returns;
    returns.a = main_avg_b;
    returns.b = side_avg_b;
    return returns;

}

void print_residue_bfactor(Atom* atoms, int start, int stop) {
    int max_id, min_id;
    max_id = min_id = -1;
    float max_val, min_val;
    char max_type[10], min_type[10];
    strcpy(max_type, "DEFAULT");
    strcpy(min_type, "DEFAULT");
    max_val = 0.0f;
    min_val = 1000000.0f;
    int current_res_id;
    int i=start;
    while(i<=stop) {
        float res_avg_b=0.0f;
        current_res_id = atoms[i].residue_number;
        int n_res =0;
        while(atoms[i].residue_number == current_res_id) {
            if(!(strcmp(atoms[i].atom_type, "CA ") ==0 || strcmp(atoms[i].atom_type, "N  ") ==0 || strcmp("C  ", atoms[i].atom_type)==0 || strcmp("O  ", atoms[i].atom_type)==0)) {
                res_avg_b += atoms[i].B;
                n_res++;
            }
            i++;
        }
        if(n_res != 0) {
        res_avg_b /= n_res;
        //DEBUG
        //DEBUGprintf("%8.3f %3d STARTS %5d ENDS %5d\n",res_avg_b, n_res, atoms[i-n_res].slno,atoms[i].slno-1 );
        //DEBUG

        if(max_val < res_avg_b) {
            max_val = res_avg_b;
            strcpy(max_type , atoms[i-1].residue_type);
            max_id = current_res_id;
        }
        if(min_val > res_avg_b) {
            min_val = res_avg_b;
            strcpy(min_type,atoms[i-1].residue_type);
            min_id = current_res_id;
        }
        }
    }

    printf("MAXIMUM B-FACTOR RESIDUE : %5s %5d\n", max_type, max_id);

    printf("MINIMUM B-FACTOR RESIDUE : %5s %5d\n", min_type, min_id);
}

int main() {
    int N = get_number_of_atoms("1oj6.pdb");
    Atom* atoms = read_pdb("1oj6.pdb", N);

    int a, b, c, d;
    a = 0;
    int i;
    for(i=0; i<N; i++) {
        if(atoms[i].chain_id == 'B') {
            b = i;
            break;
        }
    }

    for(i=b; i<N; i++) {
        if(atoms[i].chain_id == 'C') {
            c=i;
            break;
        }
    }

    for(i=c; i<N; i++) {
        if(atoms[i].chain_id == 'D') {
            d=i;
            break;
        }
    }

    f2 values;
    
    values = get_average_b(atoms, a, b-1);
    printf("CHAIN A: MAIN=%8.3f SIDE=%8.3f \n", values.a, values.b);
    values = get_average_b(atoms, b, c-1);
    printf("CHAIN B: MAIN=%8.3f SIDE=%8.3f \n", values.a, values.b);
    values = get_average_b(atoms, c, d-1);
    printf("CHAIN C: MAIN=%8.3f SIDE=%8.3f \n", values.a, values.b);
    values = get_average_b(atoms, d, N-1);
    printf("CHAIN D: MAIN=%8.3f SIDE=%8.3f \n", values.a, values.b);

    printf("CHAIN A => \n");
    print_residue_bfactor(atoms, a, b-1);
    
    printf("CHAIN B => \n");
    print_residue_bfactor(atoms, b, c-1);

    printf("CHAIN C => \n");
    print_residue_bfactor(atoms, c, d-1);

    printf("CHAIN D => \n");
    print_residue_bfactor(atoms, d, N-1);
    free(atoms);

}
