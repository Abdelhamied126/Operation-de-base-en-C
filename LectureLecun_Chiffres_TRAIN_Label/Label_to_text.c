
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fio, *fout;

int main() {
    unsigned char chi;

    int *io;
    int i, j, b = 0;
    long int dimx = 28, dimy = 2142, taille;

    char sortie[35];

    printf("Donnez le nom du fichier de sortie sans extension : ");
    scanf("%s", sortie);
    strcat(sortie, ".txt");

    fout = fopen(sortie, "w");
    fio = fopen("train-labels.idx1-ubyte", "rb");

    if (fio != NULL)
        printf("Ouverture du fichier d'entr�e r�ussie.\n");

    io = (int *)malloc(dimx * dimy * sizeof(int));

    taille = dimx * dimy;
    printf("Taille des donn�es : %ld\n", taille);

    // Ignorer les premiers octets, si n�cessaire
    for (b = 0; b < 8; b++)
        chi = (unsigned char)fgetc(fio);

    // Lecture des pixels
    for (i = 0; i < dimx; i++) {
        for (j = 0; j < dimy; j++) {
            chi = (unsigned char)fgetc(fio);
            io[i * dimx + j] = (int)chi;
            fprintf(fout, "%d ", (int)chi); // �criture dans le fichier texte
            b++;
        }
        fprintf(fout, "\n"); // Nouvelle ligne pour chaque ligne d'images
    }

    // Fermeture des fichiers
    fclose(fout);
    fclose(fio);
    free(io);

    return 0;
}

