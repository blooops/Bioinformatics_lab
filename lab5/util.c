#include "util.h"

Atom* read_pdb(char* pdbfilename, int number_atoms)  {
    FILE* fin = fopen(pdbfilename, "r");
    char line[100];
    char word[5];
    char slno_s[6];
    float x, y, z, xcm, ycm, zcm;
    int i;
    char buffer[9];
    int number_of_atoms = 0;
    xcm = ycm = zcm = 0.0f;

    Atom* atoms = (Atom*) malloc(number_atoms * sizeof(Atom));

    // Check if allocation was correct
    if(atoms == NULL) {
    }
    
    while(fgets(line, 100, fin) != NULL) {
        
        for(i=0; i<4; i++) 
           word[i] = line[i]; 

        word[4] = '\0';
        if(strcmp(word, "ATOM") == 0) {
            for(i=0; i<5; i++) slno_s[i] = line[6+i];
            slno_s[i] = '\0';
            atoms[number_of_atoms].slno = atoi(slno_s);  

            for(i=0; i<3; i++) atoms[number_of_atoms].atom_type[i] = line[13+i];
            atoms[number_of_atoms].atom_type[3] = '\0';

            for(i=0; i<3; i++) atoms[number_of_atoms].residue_type[i] = line[17+i];
            atoms[number_of_atoms].residue_type[3] = '\0';

            atoms[number_of_atoms].chain_id = line[21];

            for(i=0; i<3; i++) buffer[i] = line[23 + i];
            buffer[i] = '\0'; atoms[number_of_atoms].residue_number = atoi(buffer);

            for(i=0; i<8; i++) buffer[i] = line[30 + i];
            buffer[i] = '\0';
            atoms[number_of_atoms].x = atof(buffer);

            for(i=0; i<8; i++) buffer[i] = line[38+i];
            buffer[i] = '\0';
            atoms[number_of_atoms].y = atof(buffer);

            for(i = 0; i<8; i++) buffer[i] = line[46+i];
            buffer[i] = '\0';
            atoms[number_of_atoms].z = atof(buffer); 

            for(i = 0; i<7; i++) buffer[i] = line[60+i];
            buffer[i] = '\0';
            atoms[number_of_atoms].B = atof(buffer);

            


            xcm += atoms[number_of_atoms].x; ycm += atoms[number_of_atoms].y; zcm += atoms[number_of_atoms].z;
            
            number_of_atoms++;
        }
    }
    xcm /= number_of_atoms;
    ycm /= number_of_atoms;
    zcm /= number_of_atoms;
    fclose(fin);
    return atoms;
}

int get_number_of_atoms(char* pdbfilename) {
    int i;
    char line[101];
    FILE* fin = fopen(pdbfilename, "r");
    char word[5];
    int count = 0;
    while(fgets(line, 100, fin) != NULL) {
        for(i=0; i<4; i++) 
           word[i] = line[i]; 

        word[4] = '\0';
        if(strcmp(word, "ATOM") == 0) {
            count++;
        }
    } 
    fclose(fin);
    return count;
}


