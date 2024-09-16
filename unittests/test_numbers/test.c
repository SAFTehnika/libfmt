/*
 * Copyright (c) 2014 Roman Yeryomin <roman@advem.lv>
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libfmt.h>

#define TEST_FILE	"test.json"
#define RESULT_FILE	"result"
#define A(x)		assert((x) >= 0)
#define D		12.1203981214
#define DP		10
#define I		-1348712304324

int main( int argc, char *argv[] )
{
	fmt_t p;
	double dnum;
	long long inum;

	FILE *fp = fopen( RESULT_FILE, "w" );
	assert( fp != NULL );

	if ( fmt_load_file( TEST_FILE, &p, 0 ) != 0 ) {
		printf( "Cannot load file!\n" );
		goto exit;
	}

	fprintf( fp, "integer: " );
	A( fmt_get_integer( &p, NULL, "integer", &inum ) );
	fprintf( fp, "%lli\n", inum );

	fprintf( fp, "negative: " );
	A( fmt_get_integer( &p, NULL, "negative", &inum ) );
	fprintf( fp, "%lli\n", inum );

	fprintf( fp, "float: " );
	A( fmt_get_double( &p, NULL, "float", &dnum ) );
	fprintf( fp, "%.12f\n", dnum );

	fmt_t *d = fmt_double( D, DP );
	fprintf( fp, "generated double: " );
	A( fmt_double_value( d, NULL, &dnum ) );
	if ( dnum == D )
		fprintf( fp, "%.*f\n", (int)DP, dnum );
	else
		fprintf( fp, "FAIL\n" );
	fmt_free( d );

	fmt_t *i = fmt_integer( I );
	fprintf( fp, "generated integer: " );
	A( fmt_integer_value( i, NULL, &inum ) );
	if ( inum == I )
		fprintf( fp, "%lli\n", inum );
	else
		fprintf( fp, "FAIL\n" );
	fmt_free( i );

exit:
	A( fmt_free( &p ) );
	fclose( fp );

	return 0;
}
