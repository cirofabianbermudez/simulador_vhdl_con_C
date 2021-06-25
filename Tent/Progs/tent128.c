#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned char masktable[8] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};

int _a;
int _b;
long _mini;
long _maxi;
__int128 _round;
long _power;

void initializeA( int a, int b )
{
	_a = a;
	_b = b;

	_round = 1L;
	_round = _round << (b-1);
	_power = 1L << b;

	_mini = 1L << (a+b);
    _maxi = _mini - 1L;
    _mini = -_mini;
}

long setNumber( double v )
{
	return ( (long)(v*_power) );
}

double getNumber( long r )
{
	return ( (double)r/_power);
}

long multRound( long x, long y )
{
	long res;
	__int128 r;
	__int128 a=0;
	__int128 b=0;

	a = x;
	b = y;

	r = a*b + _round;
	r = r>>_b;

	res = 0xffffffffffffffff & r;

	return( res );
}

long multTrunc( long x, long y )
{
	__int128 r;
	__int128 a=0;
	__int128 b=0;

	a = x;
	b = y;

	r = a*b;
	r = r>>_b;

	return( r );
}

int main(int argc, char *argv[])
{
	FILE *fp;
	char nombre[81];
	char xbits[81];
	long Xi, Xni;
	long Ui, Uno, Umbral, Val, Mitad;
	int i, j, jj, nbits;
	int bits;
	int cuenta[5], v, l, k;
	double u;
	unsigned char buf[10];

	if( argc != 5 ) {
		fprintf( stderr, "Args: x0 bits bit_a_generar archivo_salida\n" );
		return 1;
	}

	bits =  (int)strtol( argv[2], (char **)NULL, 10);
	if ( bits > 62 ) {
		printf("Bits solo puede ser < 62\n");
		return 1;
	}
	nbits = (int)strtol( argv[3], (char **)NULL, 10);	
	strncpy( nombre, argv[4], 80 );

	if ( (fp=fopen( nombre, "w"))==NULL ) {
		fprintf ( stderr, "ERROR: Can't open output file: %s\n", nombre );
		return 1;
	}
	
	u = 1.995;
	initializeA( 1, bits );

	Xni = setNumber( strtod( argv[1], (char **)NULL) );

	Ui = setNumber( u );
	Uno = setNumber( 1.0 );
	Umbral = setNumber(1.0/u);
	Val = setNumber( u/(u-1.0) );
	Mitad = setNumber( 0.5 );

	
	for(i=0, j=0; i < nbits;){
		

		if( Xni <= Umbral )
			Xi = multTrunc( Ui, Xni );
		else
			Xi = multTrunc( Val, Uno-Xni );

		Xni = Xi;

	   if ( k == 5 ) {
			v = cuenta[0];
			for( l=1; l<5; l++ ) v = v^cuenta[l];
			if ( v == 0 ){
				xbits[j] = 0;
			}
			else {
				xbits[j] = 1;
			}
			i++;
			j++;
			k = 0;
		}
		if( Xni >= Mitad )
			cuenta[k] = 1;
		else
			cuenta[k] = 0;
		k++;

		
		if( j == 80 ) {
			j = 0;
			// xbits[80] = 0;
			memset( buf, 0x00, 10 );
			for ( jj=0; jj<80; jj++ ) {
				if ( xbits[jj] == 1 ){
					buf[ jj>>3 ] |= masktable[ jj & 0x0007 ];
				}
			}
			if ( fwrite ( buf, 1, 10, fp) != 10 ) {
				fprintf ( stderr, "ERROR: writing file: %s\n", nombre );
				return 1;
			}
			// printf("%s\n", xbits );
		} 
	}


	if ( j > 0 ) {
		// xbits[j] = 0;
		// printf("%s\n", xbits );
		memset( buf, 0x00, 10 );
		for ( jj=0; jj<j; jj++ ) {
			if ( xbits[jj] == 1 ){
				buf[ jj>>3 ] |= masktable[ jj & 0x0007 ];
			}
		}
		i = (j+7)/8;
		if ( fwrite ( buf, 1, i, fp) != i ) {
			fprintf ( stderr, "ERROR: writing file: %s\n", nombre );
			return 1;
		}
	}
	fclose( fp );

	return 0;
}
