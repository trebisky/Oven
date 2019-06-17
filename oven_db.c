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

#include <sys/ipc.h>
#include <sys/shm.h>

#include "oven.h"

#define DEFAULT_OVEN	0
#define DEFAULT_COMP	0

void
shm_probe ( int noven, int ncomp )
{
        key_t   key = 256 + noven%16*16 + ncomp%4;
	int shmid;

        shmid = shmget ( key, 0, 0);
	if ( shmid == -1 ) {
	    printf ( "Probe failed to find shm\n" );
	    return;
	}
	printf ( "Probe found shm at %d\n", shmid );
}

char    *
shmalloc ( int nbytes, int noven, int ncomp, int readonly )
{
        key_t   key = 256 + noven%16*16 + ncomp%4;
        int     shmflg1 = (readonly) ? 0444 : 0644 | IPC_CREAT;
        int     shmflg2 = (readonly) ? SHM_RDONLY : 0;
        int     shmid;
        char    *shmptr;

	/* If the segment already exists, this works fine and
	 *  returns the shmid
	 */
	printf ( "Try shmget with %d %d %08x\n", key, nbytes, shmflg1 );
        if ((shmid = shmget (key, nbytes, shmflg1)) == -1) {
            // if (!readonly)
            //    perror ("shmget");
	    printf ( "shmget fails\n" );
            return ((char *)0);
        }

	printf ( "shmget returned id = %d\n", shmid );

        shmptr = (char *) shmat (shmid, (char *)0, shmflg2);
	if ( shmptr == (char *) -1 ) {
            // if (!readonly)
            //    perror ("shmat");
	    printf ( "shmat fails\n" );
            return ((char *)0);
        }
        return (shmptr);
}

#ifdef notdef
#define DB_SIZE 263748
// #define DB_SIZE 100000
// #define DB_SIZE 50000
// #define DB_SIZE 10000
// #define DB_SIZE 4096
// #define DB_SIZE 1024
#endif

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

/* readonly must be zero to create a segment.
 */

void
create_db ( void )
{
	char *dbp;
	int nb = sizeof(database);
	int readonly = 0;

	// printf ( "Sizeof pointer: %d\n", sizeof(dbp) );

	// printf ( "Sizeof datbase: %d\n", nb );

	shm_probe ( DEFAULT_OVEN, DEFAULT_COMP );

	// always fails readonly, as it should if the segment
	// does not already exist.
	dbp = shmalloc ( nb, DEFAULT_OVEN, DEFAULT_COMP, readonly );

	if ( ! dbp ) {
	    printf ( "Failed to allocate shm\n" );
	    exit ( 1 );
	}

	// works fine
	// dbp = shmalloc ( DB_SIZE, 0, 0, 0 );
	printf ( "Got %016lx\n", dbp );
}

int
main ( int argc, char **argv )
{
	// show_sizes ();
	create_db ();
	exit ( 0 );
}

/* THE END */
