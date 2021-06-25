/*
	Autor:	Ciro Fabian Bermudez Marquez
	Nombre:	Simulador de diseños en VHDL de 64 bits en punto fijo
	Agracecimientos: Dr. Luis Gerardo de la Fraga y Dr. Cuauhtemoc Mancillas López
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* Variables globales */
int _a;						// parte entera
int _b;						// parte fraccionaria
long _power;

/*
	Para un Ryzen 5 3600 en MxLinux
	
	Data type <long> tiene 8 bytes, es decir 64 bits.
	printf("long is %lu bytes.\n",sizeof(long));
	
	Data type <__int128> tiene 16 bytes, es decir 128 bits.
	printf("__int128 is %lu bytes.\n",sizeof(__int128));
	
	Nota1: Se hizo la prueba en una Raspberry pi 4 y no es compatible __int128
	Nota2: De preferencia trabajar con gcc de linux o mac, falta hacer prueba en windows
	
	Para compilar ejecutar:
		gcc -o map1 map1.c
*/

void inicializa( int a, int b ){		
	_a = a;								// A(a,b) representacion en punto fijo, cargamos variables globables 
	_b = b;
	_power = 1L << _b;					// Calculamos el factor para la conversion
}

long setNumber( double v ){				// Convierte a punto fijo con truncamiento 
	return ( (long)(v*_power) );
}

double getNumber( long r ){				// Convierte de vuelta a double
	return ( (double)r/_power);
}

long multTrunc( long x, long y ){		// Multiplicacion con truncamiento
	__int128 r;
	__int128 a=0;
	__int128 b=0;
	a = x;
	b = y;
	r = a*b;
	r = r >> _b;
	return( r );
}

void dec2bin(long dec){
	int a[64],i;    
	long n;
	n = dec;
	for(i=0;n>0;i++){
		a[i]=n%2;    
		n=n/2;    
	}    
	for(i=i-1;i>=0;i--){    
		printf("%d",a[i]);    
	}
	printf("\n");   
}

int main(int argc, char *argv[]){

	// Archivo de texto
  	FILE *fpointer = fopen("salida.txt","w");
  	
	long ai[12];
	long xi, yi, xni, yni, x2i, y2i, xyi;
	double x0;
	double y0;
	int entera;
	int frac;
	int i;
	
	// Parametros de punto fijo
	entera = 3;
	frac = 60; 
	inicializa( entera, frac );
	printf(" Representacion A(a,b) = A(%d,%d)\n a: entera\tb: fraccionaria\n",entera,frac);

	// Valores iniciales
	x0 = 0.1;
	y0 = 0.2;
	printf(" # x0: %f\n", x0 );
	printf(" # y0: %f\n", y0 );
	
	// Conversion a punto fijo
	xi = setNumber( x0 );
	yi = setNumber( y0 );
	printf(" # x0 real: %2.10f\n",getNumber(xi) );
	printf(" # y0 real: %2.10f\n",getNumber(yi) );
	
	// Parametros de mapa 1
	ai[0] = setNumber( -0.6 );
	ai[1] = setNumber( -0.1 );
	ai[2] = setNumber(  1.1 );

	ai[3] = setNumber(  0.2 );
	ai[4] = setNumber( -0.8 );
	ai[5] = setNumber(  0.6 );

	ai[6] = setNumber( -0.7 );
	ai[7] = setNumber(  0.7 );
	ai[8] = setNumber(  0.7 );

	ai[9]  = setNumber( 0.3 );
	ai[10] = setNumber( 0.6 );
	ai[11] = setNumber( 0.9 );
	
	fprintf(fpointer,"%2.20f\t%2.20f\t\t%lx\t\t%lx\n",getNumber( xi ), getNumber( yi ),xi,yi);
	for(i = 0; i<100000; i++){
		x2i =  multTrunc( xi, xi );
		y2i =  multTrunc( yi, yi );
		xyi =  multTrunc( xi, yi );
		xni = ai[0] + multTrunc( ai[1], xi ) + multTrunc( ai[2], x2i ) + multTrunc( ai[3], xyi ) + 
					 multTrunc( ai[4], yi ) + multTrunc( ai[5], y2i );
					 
		yni = ai[6] + multTrunc( ai[7], xi ) + multTrunc( ai[8], x2i ) + multTrunc( ai[9], xyi ) + 
					 multTrunc( ai[10], yi ) + multTrunc( ai[11], y2i );
		
		xi = xni;			 
		yi = yni;
		fprintf(fpointer,"%2.20f\t%2.20f\t\t%lx\t\t%lx\n",getNumber( xi ), getNumber( yi ),xi,yi);
	}
	
	fclose(fpointer);
	return 0;
}
//xxd -b salida	para ver el archivo generado en la terminal
