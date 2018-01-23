#include "util.h"
#define NUMBER_OF_ATOMS 1029

int main() {
    Atom* atoms = read_pdb("3fe0.pdb", NUMBER_OF_ATOMS);
    if(atoms == NULL)  {
        printf("Error parsing pdb");
        return 0;
    }

    printf("%s\n", atoms[1].atom_type);

    int i;
    int residue_count = 0;
    int current_residue_no = 0;

    int positively_charged = 0;
    int negatively_charged = 0;
    int aromatic = 0;
    int neutral = 0;
    int hydrophobic = 0;

    for(i=0; i<NUMBER_OF_ATOMS; i++) {
        if(atoms[i].residue_number != current_residue_no) {
            current_residue_no = atoms[i].residue_number;
            residue_count++;

            if(strcmp(atoms[i].residue_type, "LYS") == 0) {
                positively_charged++;
            }

            else if(strcmp(atoms[i].residue_type, "PHE") == 0) {
                aromatic++;
            }

            else if(strcmp(atoms[i].residue_type, "VAL") == 0) {
                hydrophobic++;
            }

            else if(strcmp(atoms[i].residue_type, "GLU") == 0)  {
                negatively_charged++;
            }
            
            else if(strcmp(atoms[i].residue_type, "ARG") == 0) {
                positively_charged++;
            }

            else if(strcmp(atoms[i].residue_type, "CYS") == 0) {
                neutral++;
            }

            else if(strcmp(atoms[i].residue_type, "LEU") == 0) {
                hydrophobic++;
            }

            else if(strcmp(atoms[i].residue_type, "THR") == 0) {
                neutral++;
            }

            else if(strcmp(atoms[i].residue_type, "TYR") == 0) {
                aromatic++;
            }

            else if(strcmp(atoms[i].residue_type, "TRP") == 0) {
                aromatic++;
            }

            else if(strcmp(atoms[i].residue_type, "ASP") == 0)  {
                negatively_charged++;
            }

            else if(strcmp(atoms[i].residue_type, "SER") == 0) {
                neutral++;
            }

            else if(strcmp(atoms[i].residue_type, "HIS") == 0) {
                neutral++;
            }

            else if(strcmp(atoms[i].residue_type, "ASN") == 0) {
                neutral++;
            }

            else if(strcmp(atoms[i].residue_type, "GLN") == 0) {
                neutral++;
            }
            
            else if(strcmp(atoms[i].residue_type, "MET") == 0) {
                neutral++;
            }

            else if(strcmp(atoms[i].residue_type, "ILE") == 0) {
                hydrophobic++;
            }

            else if(strcmp(atoms[i].residue_type, "PRO") == 0) {
                hydrophobic++;
            }

            else if(strcmp(atoms[i].residue_type, "ALA") == 0) {
                hydrophobic++;
            }

            else if(strcmp(atoms[i].residue_type, "GLY") == 0) {
                hydrophobic++;
            }

        }

    }
    printf("Number of Residues : %d\n", current_residue_no);
    printf("+ve : %8.3f\n", 100 * positively_charged/(float) current_residue_no);
    printf("-ve : %8.3f\n", 100 * negatively_charged/(float) current_residue_no);
    printf("hydrophobic : %8.3f\n", 100 * hydrophobic/(float) current_residue_no);
    printf("aromatic : %8.3f\n", 100 * aromatic/(float) current_residue_no);
    printf("neutral : %8.3f\n", 100 * neutral/(float) current_residue_no);
    free(atoms);
    return 0;
}
