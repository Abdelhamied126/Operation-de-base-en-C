#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
    unsigned char chi;
    int *io, *it, *ir;
    int nbg;
    int i, j, k, l, som, m;
    int sx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};
    long int dimx, dimy, taille;

    char entree[35], sortie[35], chaine[10];

    for (m = 1; m <= 4; m++) {
        printf("donner le fichier entree sans .pgm\n");
        scanf("%s", entree);
        strcat(entree, ".pgm");

        printf("donner le fichier sortie sans .pgm\n");
        scanf("%s", sortie);
        strcat(sortie, ".pgm");

        FILE *fio = fopen(entree, "rb");
        FILE *fir = fopen(sortie, "wb+");
        if (fio != NULL) printf("ouverture du fichier in\n");
        if (fir != NULL) printf("ouverture du fichier out\n");

        fscanf(fio, "%s\n", chaine);
        fprintf(fir, "%s\n", chaine);

        i = 0;
        while (i < 1) {
            chi = fgetc(fio);
            fputc(chi, fir);
            if (chi == '\n') i++;
        }

        fscanf(fio, "%ld %ld\n", &dimx, &dimy);
        fprintf(fir, "%ld %ld\n", dimx / 2, dimy / 2);

        fscanf(fio, "%d\n", &nbg);
        fprintf(fir, "%d\n", nbg);

        printf("dimx=%ld dimy=%ld nbg=%d\n", dimx, dimy, nbg);

        io = (int *)malloc(dimx * dimy * sizeof(int));
        it = (int *)malloc((dimx + 1) * (dimy + 1) * sizeof(int));
        ir = (int *)malloc((dimx / 2) * (dimy / 2) * sizeof(int));

        taille = dimx * dimy;
        printf("taille=%ld\n", taille);

        for (i = 0; i < dimy; i++)
            for (j = 0; j < dimx; j++) {
                chi = (unsigned char)fgetc(fio);
                io[i * dimx + j] = (int)chi;
            }

        for (i = 0; i < dimy + 1; i++)
            for (j = 0; j < dimx + 1; j++)
                it[i * (dimx + 1) + j] = 0;

        for (i = 0; i < dimy; i++)
            for (j = 0; j < dimx; j++)
                it[i * (dimx + 1) + j] = io[i * dimx + j];

        for (i = 1; i < dimy + 1; i += 2)
            for (j = 1; j < dimx + 1; j += 2) {
                som = 0;
                for (l = -1; l < 2; l++)
                    for (k = -1; k < 2; k++)
                        som += sx[l + 1][k + 1] * it[(i + l) * (dimx + 1) + j + k];
                if (som < 0) som = 0;
                ir[(i / 2) * (dimx / 2) + (j / 2)] = som;
            }

        int *resultVector = (int *)malloc((dimx / 2) * (dimy / 2) * sizeof(int));
        int index = 0;
        for (i = 0; i < dimy / 2; i++)
            for (j = 0; j < dimx / 2; j++)
                resultVector[index++] = ir[i * (dimx / 2) + j];

        printf("Result Vector:\n");
        for (i = 0; i < (dimx / 2) * (dimy / 2); i++)
            printf("%d \n", resultVector[i]);
        printf("\n");

        free(io);
        free(ir);
        free(resultVector);

        fclose(fio);
        fclose(fir);
    }
    return 0;
}

