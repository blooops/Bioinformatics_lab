#include "../libs/util.h"
#include "stdio.h"
#include "stdlib.h"

int question1() {

    int total_natoms = get_number_of_atoms("5un8.pdb");
    Atom* atoms = read_pdb("5un8.pdb", total_natoms);
    

    int i;
    char out_filename[6];

    for(i=0; i<total_natoms; i++) {
        if(atoms[i].chain_id == 'A') {
            strcpy(out_filename, "A.pdb");
        }
        if(atoms[i].chain_id == 'B') {
            strcpy(out_filename, "B.pdb");
        }
        if(atoms[i].chain_id == 'C') {
            strcpy(out_filename, "C.pdb");
        }
        if(atoms[i].chain_id == 'D') {
            strcpy(out_filename, "D.pdb");
        }
        if(atoms[i].chain_id == 'E') {
            strcpy(out_filename, "E.pdb");
        }
        if(atoms[i].chain_id == 'F') {
            strcpy(out_filename, "F.pdb");
        }
        if(atoms[i].chain_id == 'G') {
            strcpy(out_filename, "G.pdb");
        }
        if(atoms[i].chain_id == 'H') {
            strcpy(out_filename, "H.pdb");
        }

        FILE* fout = fopen(out_filename, "a");
        fprintf(fout, "ATOM  %5d  %s %s %c %3d    %8.3f%8.3f%8.3f\n", 
                atoms[i].slno, atoms[i].atom_type,atoms[i].residue_type,
                atoms[i].chain_id, atoms[i].residue_number, atoms[i].x, 
                atoms[i].y, atoms[i].z);        
        fclose(fout);
    }

    free(atoms);
    return total_natoms;
}

typedef struct ASA_Chain {
    int atom_number;
    char atom_name[4];
    char residue_name[4];
    int residue_id;
    char chain_id;
    float sasa;
} ASA_Chain;

ASA_Chain* read_asa(char* filename, int natoms) {

    FILE* fin = fopen(filename, "r");
    char line[100];
    char word[10];
    
    ASA_Chain* atoms = (ASA_Chain*) malloc(natoms * sizeof(ASA_Chain));

    int count = 0;
    while(count < natoms) {

        int i;
        fgets(line, 100, fin);

        for(i=0; i<8; i++) word[i] = line[0+i];
        word[i] = '\0';
        atoms[count].atom_number = atoi(word);

        for(i=0; i<3; i++) word[i] = line[10+i];
        word[i] = '\0';
        strcpy(atoms[count].atom_name, word);

        for(i=0; i<3; i++) word[i] = line[14+i];
        word[i] = '\0';
        strcpy(atoms[count].residue_name, word);

        atoms[count].chain_id = line[18];

        for(i=0; i<3; i++) word[i] = line[23+i];
        word[i] = '\0';
        atoms[count].residue_id = atoi(word);
        
        for(i=0; i<5; i++) word[i] = line[34+i];
        word[i] = '\0';
        atoms[count].sasa = atof(word);

        count++;
    }

    fclose(fin);

    return atoms;
}

void generate_chain_files(char* filename, ASA_Chain* atoms, ASA_Chain* all, int nchain, int nall) {
    int i, j;
    i = j = 0;

    while(atoms[i].atom_number != all[j].atom_number) j++;
    FILE* fout = fopen(filename, "w");

    while(i < nchain) {

        if(atoms[i].atom_number != all[j].atom_number) { printf("OFFSET ERROR\n"); return; }

        if(atoms[i].sasa - all[j].sasa > 0.01f) {
            fprintf(fout, "%7d  %3s   %3s %c  %3d  %5.2f  %5.2f\n", atoms[i].atom_number, atoms[i].atom_name, atoms[i].residue_name, atoms[i].chain_id,
                    atoms[i].residue_id, atoms[i].sasa, atoms[i].sasa - all[j].sasa);
        }
        i++; j++;
    }
    fclose(fout);
}

void question2(int natoms) {

    // Read 5un8.asa data
    ASA_Chain* all = read_asa("5un8.asa", natoms); 
    // Read A.asa data and compare

    int na = 3480;
    int nb = 3495;
    int nc = 3520;
    int nd = 3520; 
    int ne = 56;
    int nf = 63;
    int ng = 67;
    int nh = 63;

    ASA_Chain* a = read_asa("A.asa", na); 
    generate_chain_files("A.interface", a, all, na, natoms); 
    //generate_chain_files("A_interface.asa", a, all,  na, natoms);
    free(a);

    // Read B.asa data and compare
    ASA_Chain* b = read_asa("B.asa", nb); 
    generate_chain_files("B.interface", b, all, nb, natoms); 
    free(b);
    // Read C.asa data and compare
    ASA_Chain* c = read_asa("C.asa", nc); 
    generate_chain_files("C.interface", c, all, nc, natoms); 
    free(c);
    // Read D.asa data and compare
    ASA_Chain* d = read_asa("D.asa", nd); 
    generate_chain_files("D.interface", d, all, nd, natoms); 
    free(d);
    // Read E.asa data and compare
    ASA_Chain* e = read_asa("E.asa", ne); 
    generate_chain_files("E.interface", e, all, ne, natoms); 
    free(e);
    // Read G.asa data and compare
    ASA_Chain* f = read_asa("F.asa", nf); 
    generate_chain_files("F.interface", f, all, nf, natoms); 
    free(f);
    // Read F.asa data and compare
    ASA_Chain* g = read_asa("G.asa", ng); 
    generate_chain_files("G.interface", g, all, ng, natoms); 
    free(g);
    // Read H.asa data and compare
    ASA_Chain* h = read_asa("H.asa", nh); 
    generate_chain_files("H.interface", h, all, nh, natoms); 
    free(h);

    free(all);
}

int main() {
    int natoms = get_number_of_atoms("5un8.pdb");
    question2(natoms);

    // A = 3480 B = 3495 C = 3490 D = 3520 E = 56 F = 63 G = 67  H = 63
    return 0;
}


















