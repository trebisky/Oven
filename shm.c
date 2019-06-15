#include <stdio.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include "oven.h"

/* shm.c
 * Standalone utility to work with oven shared memory.
 *
 * The "ipcs" command line tool will show shm segments
 * The "ipcrm" command line tool will remove them
 *
 * Tom Trebisky 5-24-2019
 */

char    *
shmalloc (nbytes, noven, ncomp, readonly)
int     nbytes;
int     noven;
int     ncomp;
int     readonly;
{
        key_t   key = 256 + noven%16*16 + ncomp%4;
        int     shmflg1 = (readonly) ? 0444 : 0644 | IPC_CREAT;
        int     shmflg2 = (readonly) ? SHM_RDONLY : 0;
        int     shmid;
        char    *shmptr;

	printf ( "Try shmget with %d %d %08x\n", key, nbytes, shmflg1 );
        if ((shmid = shmget (key, nbytes, shmflg1)) == -1) {
            // if (!readonly)
            //    perror ("shmget");
	    printf ( "shmget fails\n" );
            return ((char *)0);
        }

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
	printf ( "Sizeof datbase: %d\n", nb );

	// always fails readonly
	// dbp = shmalloc ( nb, 0, 0, 1 );
	dbp = shmalloc ( nb, 0, 0, readonly );

	// works fine
	// dbp = shmalloc ( DB_SIZE, 0, 0, 0 );
	printf ( "Got %016lx\n", dbp );
}

int
main ( int argc, char **argv )
{
	// show_sizes ();
	create_db ();
}

/* THE END */
