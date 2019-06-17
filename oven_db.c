/* oven_db.c
 * Create (if necessary) the shared memory segment for the
 *  oven software.  Load the on-disk database file into it
 *  by default.
 *
 * The "ipcs" command line tool will show shm segments
 * The "ipcrm" command line tool will remove them
 *  (Use something like: ipcrm shm 3702796)
 *
 *  From shm.c 6-17-2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include "oven.h"

#define DB_FILE	"database"

#define DEFAULT_OVEN	0
#define DEFAULT_COMP	0

/* TODO - 
 * add options
 * -M for meter cubed defaults
 * -b to bypass loading database
 * -l for force loading database
 * -oO:C to specify oven:comp
 */

database *
db_find ( int noven, int ncomp )
{
        key_t   key = 256 + noven%16*16 + ncomp%4;
	int shmid;
	database *p;

        shmid = shmget ( key, 0, 0);
	if ( shmid == -1 ) {
	    printf ( "Probe failed to find shm\n" );
            return ((database *)0);
	}
	printf ( "Found existing shm at ID: %d\n", shmid );

        p = (database *) shmat (shmid, (char *) 0, SHM_RDONLY );
	if ( p == (database *) -1 ) {
	    printf ( "Find failed to attach shm\n" );
            return ((database *)0);
        }
        return p;
}

void
load_database ( database *db )
{
	struct stat sbuf;
	int expect;
	int fd;

	expect = sizeof(b_database) + sizeof(p_database);

	if ( stat ( DB_FILE, &sbuf ) < 0 ) {
	    printf ( "No database file found\n" );
	    return;
	}

	if ( sbuf.st_size != expect ) {
	    printf ( "Database file wrong size (loading skipped)\n" );
	    printf ( "Database file has %d bytes\n", sbuf.st_size );
	    printf ( "Expect %d bytes\n", expect );
	    return;
	}

	printf ( "Found database file on disk\n" );
	printf ( "Loading %d bytes (B+P) to shm database from disk\n", sbuf.st_size );

	fd = open ( DB_FILE, O_RDONLY );
	if ( fd < 0 ) {
	    printf ( "Unable to open database file\n" );
	    return;
	}
	read ( fd, &db->biparameter, sizeof(b_database) );
	read ( fd, &db->parameter, sizeof(p_database) );
	close ( fd );
}

/* We only call this if we have discovered that the SHM segment
 * does not exist, so we must be able to write to it,
 * i.e. readonly access makes no sense here.
 */
database *
db_create ( int noven, int ncomp )
{
        key_t   key;
	int shmid;
	database *dp;

	key = 256 + noven%16*16 + ncomp%4;
        shmid = shmget ( key, sizeof(database), 0644 | IPC_CREAT );
	if ( shmid == -1 ) {
	    printf ( "db_creat: shmget fails\n" );
            return ((database *)0);
	}

	// printf ( "shmget returned id = %d\n", shmid );

        dp = (database *) shmat (shmid, (char *)0, 0);
	if ( dp == (database *) -1 ) {
	    printf ( "db_create: shmat fails\n" );
            return ((database *)0);
        }

	printf ( "Created shm at ID: %d\n", shmid );

	/* Fill with zeros */
	memset ( (char *) dp, 0, sizeof(database) );

	/* Load database from binary file on disk */
	load_database ( dp );

	printf ( "Shared memory database created and initialized\n" );

        return dp;
}

int
main ( int argc, char **argv )
{
	database *dp;

	// printf ( "Sizeof datbase: %d\n", sizeof(database) );

	dp = db_find ( DEFAULT_OVEN, DEFAULT_COMP );
	if ( ! dp ) {
	    dp = db_create ( DEFAULT_OVEN, DEFAULT_COMP );
	}

	exit ( 0 );
}

/* ------------------------------------------------ */

#ifdef notdef
#define DB_SIZE 263748
// #define DB_SIZE 100000
// #define DB_SIZE 50000
// #define DB_SIZE 10000
// #define DB_SIZE 4096
// #define DB_SIZE 1024

void
show_sizes ( void )
{
	printf ( "B database: %9d bytes\n", sizeof(b_database) );
	printf ( "P database: %9d bytes\n", sizeof(p_database) );
	printf ( "I database: %9d bytes\n", sizeof(i_database) );
	printf ( "D database: %9d bytes\n", sizeof(d_database) );
	printf ( "E database: %9d bytes\n", sizeof(e_database) );
	printf ( "total database: %9d bytes\n", sizeof(database) );
}

#endif


/* THE END */
