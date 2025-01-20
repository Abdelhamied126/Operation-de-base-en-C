
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define dim 16

float predict(float x,float w1,float w0)
{
 	  return w1*x+w0;
}

float loss(float x, float y,float w1,float w0)
{
	return (y-predict(x,w1,w0))*(y-predict(x,w1,w0));
}

float gradient_w1(float x, float y,float w1,float w0)
{
 	  return 2*x*(predict(x,w1,w0)-y);	
}

float gradient_w0(float x, float y,float w1,float w0)
{
 	  return 2*(predict(x,w1,w0)-y);	
}

int main()
{
	FILE *f;
	int x[dim],y[dim],cl[dim],i;
	float nouveau_w1,nouveau_w0;
	float alpha=0.0001,w1=1.25,w0=0.75;
	
	f=fopen("Data.txt","rb");
	if(f==NULL) printf("\n ouverture fichier impossible");
	for(i=0;i<dim;i++) fscanf(f,"%d %d %d",&x[i],&y[i],&cl[i]);
	printf("\n\n");
	for(i=0;i<dim;i++) printf("%d %d %d\n",x[i],y[i],cl[i]);
	
	for(i=0;i<dim;i++)
	{
		nouveau_w1=w1-alpha*gradient_w1(x[i],y[i],w1,w0);
		nouveau_w0=w0-alpha*gradient_w0(x[i],y[i],w1,w0);
		printf("Iteration %d : w1 = %f, w0 = %f, f(x) = %f, loss = %f\n", i+1,nouveau_w1,nouveau_w0, predict(x[i],nouveau_w1,nouveau_w0), loss(x[i],nouveau_w1,nouveau_w0,y[i]));
		/*
		if (loss(x,nouveau_w1,nouveau_w0,y)<alpha) 
	    {
            printf("Convergence atteinte apr�s %d iterations.\n", i+1);
            break;
        }
        */
        w1=nouveau_w1;
        w0=nouveau_w0;	
	}
return 0;
	 
}



