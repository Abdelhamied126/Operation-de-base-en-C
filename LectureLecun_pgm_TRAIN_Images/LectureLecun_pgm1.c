
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//int dimx,dimy;

FILE *fio,*fir;

int main()
{
unsigned char chi;

int *ir,*io;
int nbg;
int i,j,b=0;
long int dimx =28,dimy=28,taille;


char sortie[35],chaine[10];


printf("donner le fichier sortie sans .pgm\n");
scanf("%s",sortie);
strcat(sortie,".pgm");

fir=fopen(sortie,"wb+");
fio=fopen("TrainImages1.idx3-ubyte","rb");

if(fio !=NULL) printf("ouverture du fichier out\n");



//creation entete pgm

fprintf(fir,"%s\n","P5");

fprintf(fir,"%s\n","#ENSEA\n");

fprintf(fir,"%ld %ld\n",dimx,dimy);

nbg=255;
fprintf(fir,"%d\n",nbg);

printf("dimx=%d dimy=%d nbg=%d\n",dimx,dimy,nbg);

io=(int *)malloc(dimx*dimy*sizeof(int));
ir=(int *)malloc(dimx*dimy*sizeof(int));

if(ir==NULL) printf("allocation ir impossible\n");

taille=dimx*dimy;
printf("taille=%ld\n",taille);

for(b=0;b<12;b++)
	chi=(unsigned char)fgetc(fio);

//lecture des pixels
for(i=0;i<dimx;i++)
 for(j=0;j<dimy;j++)
 {
  chi=(unsigned char)fgetc(fio);
  io[i*dimx+j]=(int)chi;

  printf("%d : %u \n ", b,chi);
  b++;
  
  //printf("Valeur de chi %i : %u\n",i, chi);
 }


//Creation Image
/*
for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
  ir[i*dimx+j]=0;
  
for(i=50;i<150;i++)
 for(j=50;j<150;j++)
  ir[i*dimx+j]=255;  
*/
 
for(i=0;i<dimy;i++)
 for(j=0;j<dimx;j++)
  fputc((unsigned char)io[i*dimx+j],fir);


free(ir);free(io);

fclose(fir);fclose(fio);
return 0;
}
