#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *fio, *fir;

int main() 
{
    unsigned char chi;
    int *io, *ir, LUT[256];
    int nbg, d, som, d2;
    register long int i, j, l, k;
    long int dimx, dimy, taille;
    char entree[35], sortie[35], chaine[10];

    printf("donner fichier entree sans .pgm\n");
    scanf("%s", entree);
    strcat(entree, ".pgm");

    printf("donner fichier sortie sans .pgm\n");
    scanf("%s", sortie);
    strcat(sortie, ".pgm");

    fio = fopen(entree, "rb");
    fir = fopen(sortie, "wb+");

    if (fio != NULL) printf("ouverture du fichier in\n");
    if (fir != NULL) printf("ouverture du fichier out\n");

    // Lecture de l'en-tête pgm
    fscanf(fio, "%s\n", chaine);
    fprintf(fir, "%s\n", chaine);

    i = 0;
    while (i < 1) 
    {
        chi = fgetc(fio);
        fputc(chi, fir);
        if (chi == '\n') i++;
    }

    fscanf(fio, "%ld %ld\n", &dimx, &dimy);
    fprintf(fir, "%ld %ld\n", dimx, dimy);

    fscanf(fio, "%d\n", &nbg);
    fprintf(fir, "%d\n", nbg);

    printf("dimx=%d dimy=%d nbg=%d\n", dimx, dimy, nbg);

    // Allocation dynamique de mémoire des images io et ir
    io = (int *)malloc(dimx * dimy * sizeof(int));
    ir = (int *)malloc(dimx * dimy * sizeof(int));
    if (ir == NULL) 
    {
        printf("allocation ir impossible\n");
        return 1;  // Quitter le programme en cas d'échec d'allocation mémoire
    }

    taille = dimx * dimy;
    printf("taille=%ld\n", taille);

    // Lecture des pixels
    for (i = 0; i < dimy; i++)
        for (j = 0; j < dimx; j++) 
        {
            chi = (unsigned char)fgetc(fio);
            io[i * dimx + j] = (int)chi;
            ir[i * dimx + j] = io[i * dimx + j];
        }

    // Matrice de Sobel
    int sobel[3][3] = {{-1, 0, 1},
					   {-2, 0, 2}, 
					   {-1, 0, 1}};

    // Traitement : Convolution avec la matrice de Sobel
    for (i = 1; i < dimy - 1; i++)
        for (j = 1; j < dimx - 1; j++) 
        {
            int sum = 0;
            for (l = -1; l <= 1; l++)
                for (k = -1; k <= 1; k++)
                    sum += io[(i + l) * dimx + (j + k)] * sobel[l + 1][k + 1];
            ir[i * dimx + j] = abs(sum);
        }

    // Sauvegarde de l'image résultat dxans le fichier fir
    for (i = 0; i < dimy; i++)
        for (j = 0; j < dimx; j++)
            fputc((unsigned char)ir[i * dimx + j], fir);

    // Libération de la mémoire des tableaux io et ir et fermeture des fichiers fio et fir
    free(io); 
    free(ir);
    fclose(fio); 
    fclose(fir);
    
    return 0;
}

