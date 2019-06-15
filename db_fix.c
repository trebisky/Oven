/* db_fix.c
 * Standalone utility to fix byte swapping in
 * binary oven database files.
 *
 * Tom Trebisky 5-25-2019
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "oven.h"

void fix_biparam ( b_database * );
void fix_param ( p_database * );

struct bp_database {
	b_database      biparameter;
        p_database      parameter;
};

struct bp_database buf;
struct stat sbuf;

#ifdef notdef
/* POSIX has this these days */
void
my_rename ( char *cur_name, char *bak_name )
{
	/* If there is anything already there, away it goes ! */
	unlink ( bak_name );

	/* two names briefly */
        link ( cur_name, bak_name);

	/* abandon the original name */
	unlink ( cur_name );
}
#endif

void
fixer ( char *file, char *bak_file )
{
	int nw = sizeof ( buf );
	int nr;
	int fd;

	// printf ( "Size of BP is %d bytes\n", nw );
	// Size of BP is 133548 bytes (correct)

	fd = open ( file, O_RDONLY );
	if ( fd < 0 ) {
	    fprintf ( stderr, "Cannot open input file\n" );
	    exit ( 1 );
	}

	(void) fstat ( fd, &sbuf );
	if ( sbuf.st_size != nw ) {
	    fprintf ( stderr, "Wrong file size: %d bytes\n", sbuf.st_size );
	    exit ( 1 );
	}

	nr = read ( fd, (void *) &buf, nw );
	if ( nr != nw ) {
	    fprintf ( stderr, "Bad file read: %d bytes\n", nr );
	    exit ( 1 );
	}
	(void) close ( fd );

	rename ( file, bak_file );

#ifdef notdef
	/* It would be nice to recognize what endianism the file
	 * is automatically, and it is probably possible to do so.
	 * A magic number would make it easy.
	 */
	printf ( "Z0 clock: %08x\n", buf.biparameter.zone[0].clock );
	printf ( "Timestamp: %08x\n", buf.parameter.misc.timestamp );
#endif
	printf ( "Z0 clock: %08x\n", buf.biparameter.zone[0].clock );
	printf ( "Timestamp: %08x\n", buf.parameter.misc.timestamp );

	fix_param ( &buf.parameter );
	fix_biparam ( &buf.biparameter );

	fd = open ( file, O_WRONLY|O_CREAT, 0644 );
	if ( fd < 0 ) {
	    fprintf ( stderr, "Cannot create output file\n" );
	    exit ( 1 );
	}
	(void) write ( fd, (void *) &buf, nw );
	(void) close ( fd );

	exit ( 0 );

}

/* This needs command line arguments.
 * If there is just one argument, discard the original file.
 * If there are two, the second is the backup name.
 */
int
main ( int argc, char **argv )
{
	fixer ( "database", "database.OLD" );
}

/* THE END */
