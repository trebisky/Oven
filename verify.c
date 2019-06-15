/* verify.c
 * Experimen utility to check byte swapping in
 * binary oven database files.
 *
 * This proved that fix_oven.c is unnecessary and that
 * just swapping an array of longs would do the job.
 *
 * Tom Trebisky 6-1-2019
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "oven.h"

void fix_biparam ( b_database * );
void fix_param ( p_database * );
void fix_data ( d_database * );
void fix_errors ( e_database * );

/* We use int rather than long so this can be compiled 64 bit */

/* Anything with 4 distinctive bytes would work */
#define  MAGIC	0x1234abcd

/* This found one problem in fix_oven.c */
void
load1 ( int *lp, int n )
{
	int nl = n / sizeof(int);
	int i;

	for ( i=0; i < nl; i++ ) {
	    *lp++ = MAGIC;
	}
}

/* This will verify if anything gets moved around */
void
load ( int *lp, int n )
{
	int nl = n / sizeof(int);
	int i;

	for ( i=0; i < nl; i++ ) {
	    *lp++ = 0xABCD | i;
	}
}

void
sswap ( int *lp, int n )
{
	int nl = n / sizeof(int);
	int temp;
	int i;

	for ( i=0; i < nl; i++ ) {
	    temp = *lp;
	    *lp++ = htonl ( temp );
	}
}

int
check ( int *p1, int *p2, int n )
{
	int nl = n / sizeof(int);
	int i;
	int rv = 1;

	for ( i=0; i < nl; i++ ) {
	    if ( *p1++ != *p2++ ) {
		printf ( " Trouble at index: %d\n", i );
		rv = 0;
	    }
	}

	return rv;
}

void
ver_b ( void )
{
	b_database v1;
	b_database v2;

	load ( (int *) &v1, sizeof(b_database) );
	v2 = v1;
	sswap ( (int *) &v2, sizeof(b_database) );
	fix_biparam ( &v1 );

	if ( ! check ( (int *) &v1, (int *) &v2, sizeof(b_database) ) )
	    printf ( "ver_b trouble\n" );
	else
	    printf ( "B is OK\n" );
}

void
ver_p ( void )
{
	p_database v1;
	p_database v2;

	load ( (int *) &v1, sizeof(p_database) );
	v2 = v1;
	sswap ( (int *) &v2, sizeof(p_database) );
	fix_param ( &v1 );

	if ( ! check ( (int *) &v1, (int *) &v2, sizeof(p_database) ) )
	    printf ( "ver_p trouble\n" );
	else
	    printf ( "P is OK\n" );
}

void
ver_d ( void )
{
	d_database v1;
	d_database v2;

	load ( (int *) &v1, sizeof(d_database) );
	v2 = v1;
	sswap ( (int *) &v2, sizeof(d_database) );
	fix_data ( &v1 );

	if ( ! check ( (int *) &v1, (int *) &v2, sizeof(d_database) ) )
	    printf ( "ver_d trouble\n" );
	else
	    printf ( "D is OK\n" );
}

void
ver_e ( void )
{
	e_database v1;
	e_database v2;

	load ( (int *) &v1, sizeof(e_database) );
	v2 = v1;
	sswap ( (int *) &v2, sizeof(e_database) );
	fix_errors ( &v1 );

	if ( ! check ( (int *) &v1, (int *) &v2, sizeof(e_database) ) )
	    printf ( "ver_e trouble\n" );
	else
	    printf ( "E is OK\n" );
}

void
show_p ( void )
{
	p_database x;
	int *base;
	int *p;
	int i;

	base = (int *) &x;

	for ( i = 0; i<N_COMP; i++ ) {
	    p = (int *) &x.adc[i];
	    printf ( "ADC %d = %d\n", i, p-base );
	}
}

void
show_sizes ( void )
{
	printf ( "B database: %9d longs\n", sizeof(b_database)/ sizeof(int) );
	printf ( "P database: %9d longs\n", sizeof(p_database)/ sizeof(int) );
	printf ( "I database: %9d longs\n", sizeof(i_database)/ sizeof(int) );
	printf ( "D database: %9d longs\n", sizeof(d_database)/ sizeof(int) );
	printf ( "E database: %9d longs\n", sizeof(e_database)/ sizeof(int) );
	printf ( "total database: %9d longs\n", sizeof(database)/ sizeof(int) );
}

int
main ( int argc, char **argv )
{
	ver_b ();
	ver_d ();
	ver_e ();
	ver_p ();
	// show_p ();
	show_sizes ();
}

/* THE END */
