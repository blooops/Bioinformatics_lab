#include "util.h"
#include "stdio.h"
#include "stdlib.h" 
int question1() {
int total_natoms = get_number_of_atoms("5un8.pdb");
    Atom* atoms = read_pdb("5un8.pdb", total_natoms);
    

    int i;
    char out_filename[6];

    for(i=0; i<total_natoms; i++) {
        if(atoms[i].chain_id == 'A') { strcpy(out_filename, "A.pdb");
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
            fprintf(fout, "    %4d     %3s    %3s %c      %3d           %5.2f  %5.2f\n", atoms[i].atom_number, atoms[i].atom_name, atoms[i].residue_name, atoms[i].chain_id,
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
    int natoms = 2748;//get_number_of_atoms("5un8.pdb");
    question2(natoms);
    printf("DEBUG\n");
    ASA_Chain* atoms = read_asa("B.interface", natoms);
    printf("DEBUG!\n");
    int* frequencies = (int*) malloc(sizeof(int) * 22);
    int i;

    for(i=0; i<natoms; i++)
        frequencies[i] = 0;

    int old_residue_id = -1;

    for(i =0; i < natoms; i++) {
                old_residue_id = atoms[i].residue_id;
                int n = 0; float csasa=0.0f;
                while(atoms[i].residue_id == old_residue_id) {
                    csasa += atoms[i].sasa;
                    n += 1;
                    i++;
                }

                if(csasa/n > 2.0f)
                    continue;
                if(strcmp(atoms[i].residue_name, "ALA") == 0)
                    frequencies[ALA] += 1;
                else if(strcmp(atoms[i].residue_name, "ARG") == 0)
                    frequencies[ARG] += 1;
                else if(strcmp(atoms[i].residue_name, "ASN") == 0)
                    frequencies[ASN] += 1;
                else if(strcmp(atoms[i].residue_name, "ASX") == 0)
                    frequencies[ASX] += 1;
                else if(strcmp(atoms[i].residue_name, "CYS") == 0)
                    frequencies[CYS] += 1;
                else if(strcmp(atoms[i].residue_name, "GLN") == 0)
                    frequencies[GLN] += 1;
                else if(strcmp(atoms[i].residue_name, "GLU") == 0)
                    frequencies[GLU] += 1;
                else if(strcmp(atoms[i].residue_name, "GLX") == 0)
                    frequencies[GLX] += 1;
                else if(strcmp(atoms[i].residue_name, "GLY") == 0)
                    frequencies[GLY] += 1;
                else if(strcmp(atoms[i].residue_name, "HIS") == 0)
                    frequencies[HIS] += 1;
                else if(strcmp(atoms[i].residue_name, "ILE") == 0)
                    frequencies[ILE] += 1;
                else if(strcmp(atoms[i].residue_name, "LEU") == 0)
                    frequencies[LEU] += 1;
                else if(strcmp(atoms[i].residue_name, "LYS") == 0)
                    frequencies[LYS] += 1;
                else if(strcmp(atoms[i].residue_name, "MET") == 0)
                    frequencies[MET] += 1;
                else if(strcmp(atoms[i].residue_name, "PHE") == 0)
                    frequencies[PHE] += 1;
                else if(strcmp(atoms[i].residue_name, "PRO") == 0)
                    frequencies[PRO] += 1;
                else if(strcmp(atoms[i].residue_name, "SER") == 0)
                    frequencies[SER] += 1;
                else if(strcmp(atoms[i].residue_name, "THR") == 0)
                    frequencies[THR] += 1;
                else if(strcmp(atoms[i].residue_name, "TRP") == 0)
                    frequencies[TRP] += 1;
                else if(strcmp(atoms[i].residue_name, "TYR") == 0)
                    frequencies[TYR] += 1;
                else if(strcmp(atoms[i].residue_name, "UNK") == 0)
                    frequencies[UNK] += 1;
                else if(strcmp(atoms[i].residue_name, "VAL") == 0)
                    frequencies[VAL] += 1;
            

    }


        printf("TOTAL SURFACE COMPOSITION : \n");
        printf("%8s    %8s\n", "RESID", "RESFREQ");
        printf("%8s    %8d\n", "ALA", frequencies[0]);
        printf("%8s    %8d\n", "ARG", frequencies[1]);
        printf("%8s    %8d\n", "ASN", frequencies[2]);
        printf("%8s    %8d\n", "ASX", frequencies[3]);
        printf("%8s    %8d\n", "CYS", frequencies[4]);
        printf("%8s    %8d\n", "GLN", frequencies[5]);
        printf("%8s    %8d\n", "GLU", frequencies[6]);
        printf("%8s    %8d\n", "GLX", frequencies[7]);
        printf("%8s    %8d\n", "GLY", frequencies[8]);
        printf("%8s    %8d\n", "HIS", frequencies[8]);
        printf("%8s    %8d\n", "ILE", frequencies[10]);
        printf("%8s    %8d\n", "LEU", frequencies[11]);
        printf("%8s    %8d\n", "LYS", frequencies[12]);
        printf("%8s    %8d\n", "MET", frequencies[13]);
        printf("%8s    %8d\n", "PHE", frequencies[14]);
        printf("%8s    %8d\n", "PRO", frequencies[15]);
        printf("%8s    %8d\n", "SER", frequencies[16]);
        printf("%8s    %8d\n", "THR", frequencies[17]);
        printf("%8s    %8d\n", "TRP", frequencies[18]);
        printf("%8s    %8d\n", "TYR", frequencies[19]);
        printf("%8s    %8d\n", "UNK", frequencies[20]);
        printf("%8s    %8d\n", "VAL", frequencies[21]);

    return 0;
}
