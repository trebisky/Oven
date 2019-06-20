/* 
 * roven.c
 * previously rcell.c
 *
 * This program talks to the appropriate sockets to get info
 * from the SOML mirror oven VxWorks computers
 *
 * This is a unix program.
 *
 * T. Trebisky 10-18-2018
 * T. Trebisky  10-9-92, 12-10-96
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>

#include "oven.h"

int net_setup ( int );

int netwrite ( int, char *, int );
int netread ( int, char *, int );
int readline ( int, char *, int );
void error( char * );

void do_data ( void );
void do_biparam ( void );
void do_param ( void );
void do_errors ( void );

void do_gong ( void );
void do_rspeed ( void );

#define MAXLINE		256

char *mname;
// char *cname = "localhost";
char *cname = "oven1v0";

int option = 'd';	/* DATA */

/* Oven stuff */

void
quit(int sig)
{
	exit(0);
}

void
sigconnect(int sig, void (*func)())
{
	struct sigaction sa;

	sa.sa_handler   = func;
	sa.sa_flags     = 0;
	sigemptyset ( &sa.sa_mask );
	if ( sigaction ( sig, &sa, NULL ) < 0 )
	    error("Trouble installing signal");
}

int global_argc;
char **global_argv;

int
main ( int argc, char **argv )
{
	register char *p;

	sigconnect(SIGINT,quit);

	/*
	printf ( "long is %d bytes\n", sizeof(long) );
	printf ( "float is %d bytes\n", sizeof(float) );
	*/

#ifdef notdef
	mname = dname;
	if ( gethostname(hname,MAXLINE) )
	    error("Cannot get host name");

	if ( strcmp(hname,"dorado") == 0 )
	    mname = cname;
	if ( strcmp(hname,"castor") == 0 )
	    mname = cname;
#endif

	mname = cname;

	++argv;
	--argc;

	while ( argc ) {
	    if ( argv[0][0] != '-' )
		break;
	    --argc;
	    p = *argv++ + 1;
	    if ( *p == 'M' ) {
		if ( argc-- < 1 )
		    error ("no machine name");
		mname = *argv++;
	    } else {
		option = *p;
		break;
	    }
	}

#ifdef notdef
	printf("host machine: %s\n",hname);
	printf("will contact machine: %s\n",mname);
#endif

#ifdef notdef
	printf("will run option: %c\n",option);
#endif

	global_argc = argc;
	global_argv = argv;

	if ( option == 'i' ) {		/* info (default) */
	    // do_info(1);
	    // do_time();
	}
	else if ( option == 'd' )	/* get data (oven) */
	    do_data ();
	else if ( option == 'b' )	/* get bip (oven) */
	    do_biparam ();
	else if ( option == 'p' )	/* get param (oven) */
	    do_param ();
	else if ( option == 'e' )	/* get errors (oven) */
	    do_errors ();
	else if ( option == 'g' )	/* get gong (oven) */
	    do_gong ();
	else if ( option == 'r' )	/* get rspeed (oven) */
	    do_rspeed ();
#ifdef MMTCELL
	else if ( option == 'R' )	/* [park mirror] and reboot */
	    do_reboot();
	else if ( option == 't' )	/* get boot and current time */
	    do_time();
#endif
	else
	    printf("unknown option\n");

	exit(0);
}

/* Biggest item is param at 133,376 bytes */
#define DATA_MAX	140*1024
char data_buf[DATA_MAX];

/* ---------- */

void fix_data ( d_database * );
void show_data ( d_database * );

void
do_data ( void )
{
	int sn;
	int nio;
	int port = PORTRD;

	printf ( "Size of data structure is %d bytes\n", sizeof(d_database) );
	printf ( "Ask for %d bytes\n", DATA_MAX );

	if ( (sn=net_setup ( port ) ) < 0 ) {
	    fprintf(stderr,"Cannot contact port %d on host: %s\n",port, mname);
	    exit(1);
	}

	nio = netread( sn, data_buf, DATA_MAX );
	close(sn);

	printf ( "Read %d bytes of data\n", nio );

	fix_data ( (d_database *) data_buf );
	show_data ( (d_database *) data_buf );
}

void fix_biparam ( b_database * );
void show_biparam ( b_database * );

void
do_biparam ( void )
{
	int sn;
	int nio;
	int port = PORTRB;

	printf ( "Size of data structure is %d bytes\n", sizeof(b_database) );
	printf ( "Ask for %d bytes\n", DATA_MAX );

	if ( (sn=net_setup ( port ) ) < 0 ) {
	    fprintf(stderr,"Cannot contact port %d on host: %s\n",port, mname);
	    exit(1);
	}

	nio = netread( sn, data_buf, DATA_MAX );
	close(sn);

	printf ( "Read %d bytes of data\n", nio );

	fix_biparam ( (b_database *) data_buf );
	show_biparam ( (b_database *) data_buf );
}

void fix_param ( p_database * );
void show_param ( p_database * );

void
do_param ( void )
{
	int sn;
	int nio;
	int port = PORTRP;

	printf ( "Size of data structure is %d bytes\n", sizeof(p_database) );
	printf ( "Ask for %d bytes\n", DATA_MAX );

	if ( (sn=net_setup ( port ) ) < 0 ) {
	    fprintf(stderr,"Cannot contact port %d on host: %s\n",port, mname);
	    exit(1);
	}

	nio = netread( sn, data_buf, DATA_MAX );
	close(sn);

	printf ( "Read %d bytes of data\n", nio );

	fix_param ( (p_database *) data_buf );
	show_param ( (p_database *) data_buf );
}

void fix_errors ( e_database * );
void show_errors ( e_database * );

void
do_errors ( void )
{
	int sn;
	int nio;
	int port = PORTER;

	printf ( "Size of data structure is %d bytes\n", sizeof(e_database) );
	printf ( "Ask for %d bytes\n", DATA_MAX );

	if ( (sn=net_setup ( port ) ) < 0 ) {
	    fprintf(stderr,"Cannot contact port %d on host: %s\n",port, mname);
	    exit(1);
	}

	nio = netread( sn, data_buf, DATA_MAX );
	close(sn);

	printf ( "Read %d bytes of data\n", nio );

	fix_errors ( (e_database *) data_buf );
	show_errors ( (e_database *) data_buf );
}

void
dump ( unsigned char *buf, int n )
{
	int i;

	for ( i=0; i<n; i++ )
	    printf ( " %02x", buf[i] );
	printf ( "\n" );
}

int fix_gong ( int * );

/* Gong is just a single int */
void
do_gong ( void )
{
	int sn;
	int nio;
	int port = PORTGN;
	char gong_buf[10];
	int gong;

	printf ( "Size of data structure is %d bytes\n", sizeof(int) );
	printf ( "Ask for %d bytes\n", 10 );

	if ( (sn=net_setup ( port ) ) < 0 ) {
	    fprintf(stderr,"Cannot contact port %d on host: %s\n",port, mname);
	    exit(1);
	}

	nio = netread( sn, gong_buf, 10 );
	printf ( "Read %d bytes of data\n", nio );

	dump ( gong_buf, nio );

	gong = fix_gong ( (int *) gong_buf );

	printf ( "Gong: %d\n", gong );

	close(sn);
}

void fix_rspeed ( int * );

/* rspeed is just a pair of 32 bit objects (int) */
void
do_rspeed ( void )
{
	int sn;
	int nio;
	int port = PORTRS;
	char rspeed_buf[10];
	int *rp;

	/* XXX does not work for MCUBE */
	printf ( "Sorry\n" );
	return;

	printf ( "Size of data structure is %d bytes\n", 2*sizeof(int) );
	printf ( "Ask for %d bytes\n", 10 );

	if ( (sn=net_setup ( port ) ) < 0 ) {
	    fprintf(stderr,"Cannot contact port %d on host: %s\n",port, mname);
	    exit(1);
	}

	nio = netread( sn, rspeed_buf, 10 );
	printf ( "Read %d bytes of data\n", nio );

	dump ( rspeed_buf, nio );

	fix_rspeed ( (int *) rspeed_buf );
	rp = (int *) rspeed_buf;

	printf ( "Rspeed  (time): %d\n", rp[0] );
	printf ( "Rspeed (speed): %d\n", rp[1] );

	close(sn);
}

/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */

#ifdef notdef
/* Only counts are stored as shorts,
 * and they only appear in the i_database,
 * which never goes over the network.
 */
void
swap2 ( char *item )
{
	int tmp;

	tmp = item[0];
	item[0] = item[1];
	item[1] = tmp;
}

/* counts */
#define Cswap(s)	swap2 ( (char *) &s )

#endif

void
swap4 ( char *item )
{
	int tmp;

	tmp = item[0];
	item[0] = item[3];
	item[3] = tmp;

	tmp = item[1];
	item[1] = item[2];
	item[2] = tmp;
}

/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */

void
debug_f ( long *a, long *b )
{
	printf ( " --> %08x  %08x\n", *a, *b );
}

char *
encode_f ( char *buf, float val )
{
	if ( val > 1.0e38 )
	    strcpy ( buf, "INDEF" );
	else
	    sprintf ( buf, "%.2f", val );
	return buf;
}

/* Never used */
#define IS_INDEFT(x)            ( (x) > 1.0e38 )

void
show_data_rot ( d_database *db )
{
	int c;

	for ( c=0; c<N_COMP; c++ ) {
	    printf ( "Computer %d, rztmp = %.3f\n", c, db->adc[c].rztmp );
	}
}

void
show_data ( d_database *db )
{
	int i;
	// int nz = N_ZONE;	/* 21 */
	// int nz = 3;
	char buf1[20], buf2[20], buf3[20];

	for ( i=0; i<N_ZONE; i++ ) {
	    printf ( "Zone %d:  %8d  %8d %s %s %s\n",
		i,
		db->zone[i].togo,
		db->zone[i].c_node,
		encode_f ( buf1, db->zone[i].delta ),
		encode_f ( buf2, db->zone[i].etmp ),
		encode_f ( buf3, db->zone[i].ztmp )
		);

	    // debug_f ( (long *) &db->zone[i].delta, (long *) &db->zone[i].ztmp );
	}
	printf ( "Info (misc) =  %d  %u\n", db->misc.uclock, db->misc.iclock );
	show_data_rot ( db );
}

void
show_biparam ( b_database *db )
{
	int i;

	for ( i=0; i<N_ZONE; i++ ) {
	    printf ( "Zone %d:  %8d  %8d\n", i,
		db->zone[i].time, db->zone[i].clock );
	}
	printf ( "Info (misc) =  %d\n", db->misc.info );
}

void
show_param ( p_database *db )
{
}

void
show_errors ( e_database *db )
{
}

/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */

#ifdef MMTCELL
void
do_info ( int flag )
{
	// do_status();
}

do_reboot()
{
	int sn;

	if ( (sn=net_setup(REBOOT_PORT,RB_REBOOT,0)) < 0 ) {
	    fprintf(stderr,"Cannot reboot: %s\n",mname);
	    exit(1);
	}

	/* no data */

	close(sn);
	fprintf(stderr,"Reboot requested.\n");
}

char *
wonk_time(time_t atime)
{
	static char buf[MAXLINE];
	time_t time;
	struct	tm *tp;

	/*
	time_t	t;
	time (&t);
	gmtime_r (&t, &tb);
	localtime_r (&t, &tb);
	tp = &tb;
	*/

#if BYTE_ORDER == LITTLE_ENDIAN
	time = ntohl(atime);
#else
	time = atime;
#endif

	tp = localtime (&time);
	/*
	(void) strftime (buf, MAXLINE, "%H:%M:%S", tp);
	*/
	(void) strftime (buf, MAXLINE, "%m/%d/%y %H:%M:%S", tp);
	return buf;
}


do_time()
{
	int sn;
	time_t btime = 0;
	time_t ctime = 0;

	if ( (sn=net_setup(CELL_PORT,GET_TIME,0)) < 0 )
	    error("net setup fails");

	(void) netread( sn, (char *) &btime, sizeof(time_t));
	(void) netread( sn, (char *) &ctime, sizeof(time_t));
	close (sn);

	printf("boot: %s\n",wonk_time(btime));
	printf("cur:  %s\n",wonk_time(ctime));
}

printval(aval)
float aval;
{
	float val = ntohf(aval);

	if ( val < 1.0 )
	    printf("%10.6f",val);
	else
	    printf("%10.5f",val);
}
#endif	/* MMTCELL */

/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */

/*
extern int errno;
*/

int
net_setup ( int port )
{
	int sn;
	struct sockaddr_in sock;
	struct hostent *hp;
	// struct netreq rbuf;

	if ( (sn=socket ( AF_INET, SOCK_STREAM, 0 )) < 0 )
	    return ( -1 );

	memset((char *)&sock, 0, sizeof(sock));
	sock.sin_family = AF_INET;

	if ( (hp=gethostbyname(mname)) == 0 )
	    return ( -2 );
	memcpy( (char *) &sock.sin_addr,
	    (char *) hp->h_addr, hp->h_length);
	sock.sin_port = htons(port);

	/* Will hang in connect if trying to contact a
	 * non-existing machine (or one not on local net).
	 */
	if ( connect ( sn, (struct sockaddr *) &sock, sizeof(sock) ) < 0 )
	    return ( -3 );

	// rbuf.ne_type = htons(type);
	// rbuf.ne_addr = htons(addr);
	// netwrite ( sn,&rbuf,sizeof(rbuf) );

	return ( sn );
}

int
netread ( int fd, char *buf, int nbuf )
{
	int n, nleft;

	nleft = nbuf;
	while ( nleft ) {
	    if ( (n=read(fd,buf,nleft)) < 0 ) {
		/*
		printf("errno = %d\n",errno);
		*/
		printf("%d %d\n",n,nleft);
		return(-1);	/* error */
	    }
	    else if ( n == 0 )
		break;		/* EOF */
	    nleft -= n;
	    buf += n;
	}
	return (nbuf-nleft);
}

int
netwrite ( int fd, char *buf, int nbuf )
{

	if ( write(fd,buf,nbuf) != nbuf )
	    return(-1);
	return (0);
}

/* simple version of readline, it would be better to do bigger reads and
 * buffer characters, rather than a system call per character read.
 */
int
readline ( int fd, char *buf, int maxlen )
{
	int n, tot;

	for ( tot=0; tot<maxlen-1; ) {
	    if ( (n=read(fd,buf,1)) == 1 ) {
		if ( *buf == '\n' )
		    break;
		++tot;
		++buf;
	    } else if ( n == 0 ) {	/* EOF, the usual case */
		*buf = '\0';
		return ( tot );
	    } else {
		return ( -1 );
	    }
	}

	++tot;
	*++buf = '\0';
	return ( tot );
}

void
error( char *s )
{
	fprintf(stderr,"%s\n",s);
	exit(1);
}

#ifdef notdef
float ntohf(float);
float htonf(float);

float
ntohf(float nval)
{
#if BYTE_ORDER == LITTLE_ENDIAN
	    union {
		long lval;
		float val;
	    } uval;

	uval.val = nval;
	uval.lval = ntohl(uval.lval);
	return ( uval.val );
#else
	return nval;
#endif
}

float
htonf(float hval)
{
#if BYTE_ORDER == LITTLE_ENDIAN
	    union {
		long lval;
		float val;
	    } uval;

	uval.val = hval;
	uval.lval = htonl(uval.lval);
	return ( uval.val );
#else
	return hval;
#endif
}
#endif

/* THE END */
