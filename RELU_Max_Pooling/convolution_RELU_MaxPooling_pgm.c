
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *fio,*fir;

int main() 
{
unsigned char chi;
int *io,*ir,*ir1;
int nbg;
int conv[3][3]={{-1,0,1},
				{-2,0,2},
				{-1,0,1}};
register long int i,j,k,l,som,mmax;
long int dimx,dimy,taille;
char entree[35],sortie[35],chaine[10];

printf("donner fichier entree sans .pgm\n");
scanf("%s",entree);
strcat(entree,".pgm");

printf("donner fichier sortie sans .pgm\n");
scanf("%s",sortie);
strcat(sortie,".pgm");

fio=fopen(entree,"rb");
fir=fopen(sortie,"wb+");

if(fio !=NULL) printf("ouverture du fichier in\n");
if(fir !=NULL) printf("ouverture du fichier out\n");

//lecture entete pgm
fscanf(fio,"%s\n",chaine);
fprintf(fir,"%s\n",chaine);

i=0;
while(i<1) 
{
	chi=fgetc(fio);
	fputc(chi,fir);
	if(chi=='\n') i++;
}

fscanf(fio,"%ld %ld\n",&dimx,&dimy);
fprintf(fir,"%ld %ld\n",dimx/2,dimy/2);

fscanf(fio,"%d\n",&nbg);
fprintf(fir,"%d\n",nbg);

printf("dimx=%d dimy=%d nbg=%d\n",dimx,dimy,nbg);

//allocation dynamique de m moire des images io et ir
io=(int *)malloc(dimx*dimy*sizeof(int));
ir=(int *)malloc(dimx*dimy*sizeof(int));
ir1=(int *)malloc((dimx/2)*(dimy/2)*sizeof(int));
if(ir1==NULL) printf("allocation ir impossible\n");

taille=dimx*dimy;
printf("taille=%ld\n",taille);

//lecture des pixels
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++) 
	{
		chi=(unsigned char)fgetc(fio);
		io[i*dimx+j]=(int)chi;
		ir[i*dimx+j]=io[i*dimx+j];
	}


///////////////////////////////////////////////////////////////////
//TRAITEMENT
//Convolution
for(i=1;i<dimy-1;i++)
	for(j=1;j<dimx-1;j++)
	{
		som=0;
		for(l=-1;l<2;l++)
		 for(k=-1;k<2;k++)
		   som +=conv[l+1][k+1]*io[(i+l)*dimx+j+k];
		ir[i*dimx+j]=som;
	}
//Relu
for(i=1;i<dimy-1;i++)
	for(j=1;j<dimx-1;j++)
	 if(ir[i*dimx+j]<0) ir[i*dimx+j]=0;
//Max Pooling
for(i=0;i<dimy;i+=2)
	for(j=0;j<dimx;j+=2)
	{
	 mmax=ir[i*dimx+j];
	 for(l=0;l<2;l++)
	  for(k=0;k<2;k++)
	  if(ir[(i+l)*dimx+j+k]>mmax) mmax=ir[(i+l)*dimx+j+k];
	 ir1[(i/2)*(dimx/2)+(j/2)]=mmax;	
	}
		
//FIN TRAITEMENT
///////////////////////////////////////////////////////////////////
 
//Sauvegarde de l image r sultat dans le fichier fir
for(i=0;i<dimy/2;i++)
	for(j=0;j<dimx/2;j++)
		fputc((unsigned char)ir1[i*(dimx/2)+j],fir);

//libération de de la mémoire des tableaux io et ir et fermeture des 2 fichiers fio et fir
free(io); free(ir);free(ir1);
fclose(fio); fclose(fir);
return 0;
}
