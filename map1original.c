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

	// r = a*b + _round;
	r = a*b;
	r = r>>_b;

	// res = 0xffffffffffffffff & r;
	res = r;

	return( res );
}


int main(int argc, char *argv[])
{
	FILE *fp;
	char nombre[81];
	unsigned char buf[16];
	int i, j, jj, nbits;
	int bits;
	long xi, xni, yi, yni;
	long x2i, y2i, xyi;
	long ai[12];

	if( argc != 6 ) {
		fprintf( stderr, "Args: x0 y0 bits bit_a_generar archivo_salida\n" );
		return 1;
	}
	bits =  (int)strtol( argv[3], (char **)NULL, 10);
	if ( bits > 60 ) {  // 1 + 62 = 63.   4 + 59 = 63 
		printf("Bits solo puede ser menor que 59\n");
		return 1;
	}
	nbits = (int)strtol( argv[4], (char **)NULL, 10);	
	strncpy( nombre, argv[5], 80 );

	if ( (fp=fopen( nombre, "w"))==NULL ) {
		fprintf ( stderr, "ERROR: Can't open output file: %s\n", nombre );
		return 1;
	}
	
	initializeA( 3, bits );

	ai[0] = setNumber( -0.6 );
	ai[1] = setNumber( -0.1 );
	ai[2] = setNumber(  1.1 );

	ai[3] = setNumber(  0.2 );
	ai[4] = setNumber( -0.8 );
	ai[5] = setNumber(  0.6 );

	ai[6] = setNumber( -0.7 );
	ai[7] = setNumber(  0.7 );
	ai[8] = setNumber(  0.7 );

	ai[9] = setNumber(  0.3 );
	ai[10] = setNumber( 0.6 );
	ai[11] = setNumber( 0.9 );
	
	printf("# power: %lx\n", _power );
	printf("# round: %lx\n", _round );

	xi = setNumber( strtod( argv[1], (char **)NULL) );
	printf("# xni: %lx\n", xi );
	yi = setNumber( strtod( argv[2], (char **)NULL) );
	printf("# yni: %lx\n", yi );

	for(i=0, j=0; i < nbits; i+=16){
		x2i = multRound( xi, xi );
		y2i = multRound( yi, yi );
		xyi = multRound( xi, yi );

		xni = ai[0] + multRound(ai[1],xi) + multRound(ai[2],x2i) + multRound(ai[3],xyi) +
		              multRound(ai[4],yi) + multRound(ai[5],y2i);
		yni = ai[6] + multRound(ai[7],xi) + multRound(ai[8],x2i) + multRound(ai[9],xyi) +
		              multRound(ai[10],yi) + multRound(ai[11],y2i);

		xi = xni;
		yi = yni;

		// printf("%lf %lf\n", getNumber( xi ), getNumber( yi ) ); 

		// Eight bits obtained every cycle:
		buf[j] = (unsigned char)( xni & 0x00000000000000ff );
		j++;
		buf[j] = (unsigned char)( yni & 0x00000000000000ff );
		j++;

		
		if( j == 16 ) {
			j = 0;
			if ( fwrite ( buf, 1, 16, fp) != 16 ) {
				fprintf ( stderr, "ERROR: writing file: %s\n", nombre );
				return 1;
			}
		} 
	}

	if ( j > 0 ) {
		if ( fwrite ( buf, 1, j, fp) != j ) {
			fprintf ( stderr, "ERROR: writing file: %s\n", nombre );
			return 1;
		}
	}
	fclose( fp );

	return 0;
}
