/* Oven parameters and definitions
 */
#ifndef	NULL
#define	NULL	0
#endif

#define	YES	1
#define	NO	0

#define	forever		while (YES)

#define	ABS(a)		( ((a) >= 0) ? (a) : -(a) )
#define	MIN(a,b)	( ((a) < (b)) ? (a) : (b) )
#define	MAX(a,b)	( ((a) > (b)) ? (a) : (b) )

#define bzero(a,n)      memset(a,0,n)
#define bcopy(a,b,n)    memmove(b,a,n)

#define	todigit(c)	( (c) - '0' )

#define	PORTRD		5100	/* read  data		*/
#define	PORTWP		5101	/* write   parameters	*/
#define	PORTRP		5102	/* read    parameters	*/
#define	PORTWB		5103	/* write biparameters	*/
#define	PORTRB		5104	/* read  biparameters	*/
#define	PORTER		5105	/* read  errors		*/
#define	PORTGN		5106	/* read  gong		*/
#define	PORTRS		5107	/* read  rspeed		*/

#define	PORTDCU0	5110	/* DCU data		*/
#define	PORTDCU1	5111	/* DCU data		*/
#define	PORTDCU2	5112	/* DCU data		*/
#define	PORTDCU3	5113	/* DCU data		*/
#define	PORTDCU4	5114	/* DCU data		*/
#define	PORTDCU5	5115	/* DCU data		*/

#define	PORTADC0	5120	/* ADC data		*/
#define	PORTADC1	5121	/* ADC data		*/
#define	PORTADC2	5122	/* ADC data		*/

#define	NBIT_CHAR	8	/* # of bits in a char (byte)		*/
#define	SZ_NIB		2	/* # of nibbles in a char (byte)	*/

#define	N_OVEN		10	/* # of ovens				*/
#define	N_COMP		3	/* # of V computers			*/
#define	N_MTMP		5	/* # of tc temps in time median filter	*/
#define	N_TC		8	/* # of channels per TIC		*/
#define	N_TTMP		5	/* # of channels with real TCs		*/
#define	N_TIC		4	/* # of TICs per counter card		*/
#define	N_COUNTER	6	/* # of counter cards per  DCU		*/
#define	N_POS		3	/* # of TICS per select buss		*/
#define	N_BUSS		4	/* # of busses per select card		*/
#define	N_SELECT	2	/* # of select  cards per DCU		*/
#define	N_DCU		6	/* # of DCUs				*/
#define	N_POLYCOEF	6	/* # of coefficients in TC polynomial	*/
#define	N_TCTYPE	8	/* # of types of TC			*/
#define	N_NNEIGHBOR	4	/* # of near neighboring TCs per heater	*/
#define	N_FNEIGHBOR	12	/* # of far  neighboring TCs per heater	*/
#define	N_ELEMENT	10	/* # of heaters per phase		*/
#define	N_FASE		3	/* # of phases  per power panel		*/
#define	N_PANEL		10	/* # of power panels ( + 1 phantom )	*/
#define	N_ZONE		21	/* # of control zones			*/
#define	N_ROT		32	/* # of adc channels on rotation ADC	*/
#define	N_LVDT		16	/* # of lvdt channels on rotation ADC	*/
#define	O_LVDT		16	/* # of first lvdt channel on rot ADC	*/
#define	ROT_ZONE	( N_ZONE-1 )	/* rotation zone #		*/
#define	ALL_ZONE	N_ZONE	/* # to signal all zones		*/
#define	N_NODE		32	/* # of nodes per zone			*/
#define	N_MAP		2	/* # of ssr maps (maybe 3 - timing)	*/
#define	N_PMAP		4	/* # of maps in protocol		*/
#define	LEN_MAP		( (N_ELEMENT*N_FASE + NBIT_CHAR-1)/(NBIT_CHAR) )
#define	LEN_PMAP	( (N_PMAP*LEN_MAP + 1) * SZ_NIB + 1 )

#define	M_HEL	0	/* index of heater elements in output protocol map */
#define	M_ERR	1	/* index of error lamps     in output protocol map */
#define	M_SAV	2	/* index of previous heater in output protocol map */
#define	M_VOL	0	/* index of voltage sensors in input  protocol map */
#define	M_LCS	1 /* index of local  current sensors in input  protocol map */
#define	M_RCS	2 /* index of remote current sensors in input  protocol map */

#define	MAX_POWER	240	/* maximum power request		*/
#define	HEATER_AMPS	27.0	/* number of amps per heater		*/

#define	RADIAN		57.2957795

#define	SCER_REPAINT		(-1)
#define	SCER_OK			0
#define	SCER_SYNTAX		1
#define	SCER_RANGE		2
#define	SCER_INCONSISTENT	3
#define	SCER_NOEDITB		4

#define	GOER_EXECUTED		1
#define	GOER_OK			0
#define	GOER_NOMENU		(-1)
#define	GOER_NOWHERE		(-2)
#define	GOER_INCONSISTENT	(-3)
#define	GOER_NOEDITP		(-4)

#define	TCTYPEN	0		/* N type thermocouple */
#define	TCTYPEK	1		/* K type thermocouple */
#define	TCTYPES	2		/* S type thermocouple */
#define	TCTYPET	3		/* T type thermocouple */
#define	TCTYPER	4		/* R type thermocouple */
#define	TCTYPEJ	5		/* J type thermocouple */
#define	TCTYPEE	6		/* E type thermocouple */
#define	TCTYPEZ	7		/* Z type thermistor   */

#define	WFLAG_T	1		/* tolerance	*/
#define	WFLAG_D	2		/* deviation	*/
#define	WFLAG_W	4		/* wait on node	*/

#define NODELABELS	" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define ANODELABELS	"@abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

typedef	int	BOOL;		/* logical YES/NO			*/
typedef	short	COUNT;		/* raw counts				*/
typedef	int	DSB;		/* select buss address			*/
typedef	int	DNTX;		/* TC address				*/
typedef	int	PFE;		/* heater address			*/
typedef	int 	POWER;		/* 1/240 duty cycle			*/
typedef	long	TIME;		/* seconds				*/
typedef	float	TEMP;		/* degrees C				*/

#define	INDEFT	(1.6e38)	/* indefinite (NO) temperature		*/
#define	IS_INDEFT(x)		( (x) > 1.0e38 )

#define	INDEFA	(1.6e38)	/* indefinite (NO) ADC value		*/
#define	IS_INDEFA(x)		( (x) > 1.0e38 )

/* ADC value conversion routines					*/

#define	H2A(h)	( (IS_INDEFA (h)) ? INDEFA : (h) * HEATER_AMPS )
#define	A2H(a)	( (IS_INDEFA (a)) ? INDEFA : (a) / HEATER_AMPS )
#define	KW(v,a)	( (IS_INDEFA (v) || IS_INDEFA (a)) ? INDEFA : (v)*(a) / 1000.0 )
#define	ADS(s,a) ((IS_INDEFA (s) || IS_INDEFA (a)) ? ((s)=INDEFA): ((s)+=(a)) )

#define	CLOCKRATE	100	/* Use 100 HZ clock - 10ms period	*/

/* twork definitions: */

/* translate the tc measurement phase number into a tc number
 */
#ifdef notdef
/* TJT 5-24-2019 -- odd that this has no type? */
static	tc_tcn[] =	{0, 1, 2, 3, 4, 8, 9, 5, 6, 7};	/* 8,9 not used */
#endif

static	int	tc_tcn[] =	{0, 1, 2, 3, 4, 8, 9, 5, 6, 7};	/* 8,9 not used */

/* translate the logical TC number into a hardware multiplexor address
 */
static	int	mux_tc[] = {1, 2, 3, 4, 6, 7, 5, 0};

#define	PERIODT		500	/* 500 ms integration period		*/

#define	TCN_INIT	N_TTMP		/* initialize			*/
#define	TCN_IDLE	( TCN_INIT+1 )	/* do nothing			*/
#define	TCN_ZERO	( TCN_IDLE+1 )	/* get zero point		*/
#define	TCN_REFV	( TCN_ZERO+1 )	/* get reference; calc scale	*/
#define	TCN_JTMP	( TCN_REFV+1 )	/* calc junction temp		*/
#define	TCN_MAXN	( TCN_JTMP+1 )	/* start over			*/

#define	OFFSET		( itic->count[tc_tcn[TCN_ZERO]] ) /* zero offset*/
#define	RCOUNTS		( itic->count[tc] )	/* the raw counts	*/
#define	COUNTS		( (int)RCOUNTS - (int)OFFSET ) /* the count rate*/

#define	TLIMBACK	(-5.0)		/* limit backwards		*/
#define	TLIMSHRT	0.0		/* limit shorted		*/
#define	TLIMMELT	1400.0		/* limit meltdown		*/
#define	TLIMOPEN	10.0		/* limit open			*/
#define	JTMPLLIM	0.0		/* jtmp lower limit		*/
#define	JTMPULIM	80.0		/* jtmp upper limit		*/

#define	DCU__		(pdcu++, idcu++, ddcu++, dcu++)
#define	COUNTER__	(pcounter++, icounter++, dcounter++, counter++)
#define	TIC__		(ptic++, itic++, dtic++, tic++)
#define	SELECT__	(pselect++, iselect++, select++)
#define	BUSS__		(pbuss++, ibuss++, buss++)

/* cwork definitions: */

#define	PERIODS	60		/* schedule resolution (seconds) {30?}	*/
#define	PERIODC	(PERIODS*1000)	/* control period (milliseconds)	*/

#define	WFLAG_TOLERANCE	1.0	/* degrees C				*/

#define	ZONE__		(bzone++, pzone++, izone++, dzone++, zone++)
#define	NODE__		(pnode++, node++)

#define	NNEIGHBOR_WEIGHT	5
#define	FNEIGHBOR_WEIGHT	1

/* pwork definitions: */

#define	GONG	(dbs->intermediate.misc.gong)
#define	PCLOCK(db,panel) ((db->intermediate.misc.pclock			\
			+ (N_MAP*N_PANEL-1-panel)*MAX_POWER/N_PANEL)	\
			% (N_MAP*MAX_POWER))
#define	MAPCLOCK(db,panel) ((PCLOCK(db,panel)/MAX_POWER+N_MAP-1)%N_MAP	\
			* MAX_POWER)

#define	LSN(x)	( (x) & 0xf )
#define	MSN(x)	( LSN((x) >> 4) )

static	char	*tohex	= "0123456789abcdefABCDEF";

/* define heater/sensor errors
 */
#define	OKF	0	/* OK - all off					*/
#define	CON	1	/* current sensor failed on			*/
#define	VON	2	/* voltage sensor failed on			*/
#define	HON	3	/* heater element failed on			*/
#define	HOF	4	/* heater element failed off			*/
#define	VOF	5	/* voltage sensor failed off			*/
#define	COF	6	/* current sensor failed off			*/
#define	ROF	7	/* remote  sensor failed off			*/
#define	RON	8	/* remote  sensor failed on			*/
#define	OOII	9
#define	OIOI	10
#define	OIIO	11
#define	IOOI	12
#define	IOIO	13
#define	IIOO	14
#define	OKN	0	/* OK - all on					*/

#define	HE	2	/* disabled sensor				*/

/*		     H  V  C  R						*/
/* static int	perr[2][2][2]	= {OKF, CON, VON, HON, HOF, VOF, COF, OKN}; */
/*
static	int	perr[2][2][2][2] = {OKF, RON, CON, OOII, VON, OIOI, OIIO, HON,
				    HOF, IOOI, IOIO, VOF, IIOO, COF, ROF, OKN};
 */
static	int perr[2][3][3][3] = {OKF, RON, OKF, CON, OOII, CON, OKF, RON, OKF,
				VON, OIOI, VON, OIIO, HON, HON, VON, HON, VON,
				OKF, RON, OKF, CON, HON, CON, OKF, RON, OKF,
				HOF, IOOI, HOF, IOIO, VOF, VOF, HOF, VOF, VOF,
				IIOO, COF, COF, ROF, OKN, OKN, ROF, OKN, OKN,
				HOF, COF, COF, ROF, OKN, OKN, ROF, OKN, OKN};

/* the following indicates a power panel buss error
 */
#define	PANEL_SENSOR_STATUS_ERROR ((ipanel->imap[M_VOL].mapbyte[1] & 128) != 0)

static	int mapbyt[N_FASE][N_ELEMENT] = {
	0,  0,  0,  0,  0,  0,  0,  0,
	1,  1,  1,  1,  1,  1,  1,
	2,  2,  2,  2,  2,  2,  2,  2,
	3,  3,  3,  3,  3,  3,  3};
static	unsigned char mapbit[N_FASE][N_ELEMENT] = {
	1,  2,  4,  8, 16, 32, 64, 128,
	1,  2,  4,  8, 16, 32, 64,
	1,  2,  4,  8, 16, 32, 64, 128,
	1,  2,  4,  8, 16, 32, 64};

#define	PANEL__		(ppanel++, ipanel++, dpanel++, panel++)
#define	FASE__		(pfase++, ifase++, dfase++, fase++)
#define	ELEMENT__	(pelement++, ielement++, delement++, element++)

#define	CONNECT(x)	( ((x)-1) == db->parameter.misc.vnumber )
#define	IS_STALE(x)	( (db->data.misc.uclock - (x)) > 10 )
#define	IS_STALEA(x)	( (db->data.misc.uclock - (x)) > 120 )
#define	CONFIG		( db->parameter.misc.config )

static	int configt[N_FASE][N_ELEMENT] = {		/* config time	*/
	   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,
	  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
	  20,  21,  22,  23, 240, 241, 242, 243, 244, 245
	};

#define	ADCFSV	4096.0

static	float	adcfsv[] = {	/* ADC full scale values for each channel */
	400.0, 400.0, 400.0, 400.0, 400.0, 400.0, 400.0, 400.0,
	400.0, 400.0, 400.0, 400.0,   0.0,   0.0,   0.0,   0.0,
	300.0, 300.0, 300.0, 300.0, 300.0, 300.0, 300.0, 300.0,
	300.0, 150.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
	600.0, 600.0, 600.0,  15.0,  15.0,  30.0,  30.0,  80.0,
	 80.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0, 100.0,
	412.0, 412.0, 412.0, 412.0, 412.0, 412.0, 412.0, 412.0,
	1930.0, 1930.0, 1930.0, 1930.0, 50.4, 50.4, 50.4, 50.4
	};

#define	Voltage		voltage
#define	Current		current

/* pointer/counter declarations */

#define	DCL_ZONE	\
	b_zone	*bzone	= db->biparameter.zone;	\
	p_zone	*pzone	= db->parameter.zone;	\
	i_zone	*izone	= db->intermediate.zone;	\
	d_zone	*dzone	= db->data.zone;	\
	int	zone;

#define	DCL_PANEL	\
	p_panel	*ppanel = db->parameter.panel;	\
	i_panel	*ipanel = db->intermediate.panel;	\
	d_panel	*dpanel = db->data.panel;	\
	int	panel;

#define	DCL_FASE	\
	p_fase	*pfase = ppanel->fase;	\
	i_fase	*ifase = ipanel->fase;	\
	d_fase	*dfase = dpanel->fase;	\
	register	int		fase;

#define	DCL_ELEMENT	\
	p_element	*pelement = pfase->element;	\
	register	i_element	*ielement = ifase->element;	\
	d_element	*delement = dfase->element;	\
	register	int		element;

#define	DCL_DCU	\
	p_dcu	*pdcu = db->parameter.dcu;	\
	i_dcu	*idcu = db->intermediate.dcu;	\
	d_dcu	*ddcu = db->data.dcu;	\
	int	dcu;

#define	DCL_COUNTER	\
	p_counter	*pcounter = pdcu->counter;	\
	i_counter	*icounter = idcu->counter;	\
	d_counter	*dcounter = ddcu->counter;	\
	int		counter;

#define	DCL_TIC	\
	p_tic	*ptic = pcounter->tic;	\
	i_tic	*itic = icounter->tic;	\
	d_tic	*dtic = dcounter->tic;	\
	int	tic;

#define	DCL_SELECT	\
	p_select	*pselect = pdcu->select;	\
	i_select	*iselect = idcu->select;	\
	int		select;	\

#define	DCL_BUSS	\
	p_buss	*pbuss = pselect->buss;	\
	i_buss	*ibuss = iselect->buss;	\
	int	buss;

/* error counter definitions */

#define	CERRZSC	db->error.zone[zone].zsc++
#define	CERRHER	db->error.panel[panel].fase[fase].element[element].her++
#define	CERRHSC	db->error.panel[panel].fase[fase].element[element].hsc++
#define	PERRCON	db->error.panel[panel].fase[fase].element[element].con++
#define	PERRVON	db->error.panel[panel].fase[fase].element[element].von++
#define	PERRHON	db->error.panel[panel].fase[fase].element[element].hon++
#define	PERRHOF	db->error.panel[panel].fase[fase].element[element].hof++
#define	PERRVOF	db->error.panel[panel].fase[fase].element[element].vof++
#define	PERRCOF	db->error.panel[panel].fase[fase].element[element].cof++
#define	PERRROF	db->error.panel[panel].fase[fase].element[element].rof++
#define	PERRRON	db->error.panel[panel].fase[fase].element[element].ron++
#define	PERROOII db->error.panel[panel].fase[fase].element[element].ooii++
#define	PERROIOI db->error.panel[panel].fase[fase].element[element].oioi++
#define	PERROIIO db->error.panel[panel].fase[fase].element[element].oiio++
#define	PERRIOOI db->error.panel[panel].fase[fase].element[element].iooi++
#define	PERRIOIO db->error.panel[panel].fase[fase].element[element].ioio++
#define	PERRIIOO db->error.panel[panel].fase[fase].element[element].iioo++
#define	PERRPPE	db->error.panel[panel].ppe++
#define	PERRPKP	db->error.panel[panel].pkp++
#define	TERRFPE	db->error.dcu[dcu].counter[counter].tic[tic].tc[tc].fpe++
#define	TERRBACK db->error.dcu[dcu].counter[counter].tic[tic].tc[tc].back++
#define	TERRSHRT db->error.dcu[dcu].counter[counter].tic[tic].tc[tc].shrt++
#define	TERRMELT db->error.dcu[dcu].counter[counter].tic[tic].tc[tc].melt++
#define	TERROPEN db->error.dcu[dcu].counter[counter].tic[tic].tc[tc].open++
#define	TERRMER	db->error.dcu[dcu].select[select].buss[buss].mer++
#define	TERRTON	db->error.dcu[dcu].ton++
#define	TERRTOF	db->error.dcu[dcu].tof++
#define	TERRDST	db->error.dcu[dcu].dst++
#define	TERRIJT	db->error.dcu[dcu].counter[counter].tic[tic].ijt++
#define	TERRJTL	db->error.dcu[dcu].counter[counter].tic[tic].jtl++
#define	AERRFCL	\
 db->error.adc[panel/N_COMP].panel[panel%N_COMP].fase[fase].current.lower++
#define	AERRFCU	\
 db->error.adc[panel/N_COMP].panel[panel%N_COMP].fase[fase].current.upper++
#define	AERRFCI	\
 db->error.adc[panel/N_COMP].panel[panel%N_COMP].fase[fase].current.indef++
#define	AERRFVL	\
 db->error.adc[panel/N_COMP].panel[panel%N_COMP].fase[fase].voltage.lower++
#define	AERRFVU	\
 db->error.adc[panel/N_COMP].panel[panel%N_COMP].fase[fase].voltage.upper++
#define	AERRFVI	\
 db->error.adc[panel/N_COMP].panel[panel%N_COMP].fase[fase].voltage.indef++
#define	AERRPCL	\
 db->error.adc[panel/N_COMP].panel[panel%N_COMP].current.lower++
#define	AERRPCU	\
 db->error.adc[panel/N_COMP].panel[panel%N_COMP].current.upper++
#define	AERRPCI	\
 db->error.adc[panel/N_COMP].panel[panel%N_COMP].current.indef++
#define	AERRHVL	\
 db->error.adc[panel/N_COMP].voltage.lower++
#define	AERRHVU	\
 db->error.adc[panel/N_COMP].voltage.upper++
#define	AERRHVI	\
 db->error.adc[panel/N_COMP].voltage.indef++

#define	RDADC(n,x)	radcv (n, &ddb->adc[panel/N_COMP].x);

#define	CKADC(x)	\
	if (!pdb->misc.vup[panel/N_COMP]) \
	    ;	\
	else if (pdb->adc[panel/N_COMP].x.upper==0. &&	\
	  pdb->adc[panel/N_COMP].x.lower==0.) \
	    ;	\
	else if (IS_INDEFA (ddb->adc[panel/N_COMP].x))	\
	    db->error.adc[panel/N_COMP].x.indef++;	\
	else if (IS_STALEA (ddb->adc[panel/N_COMP].timestamp))	\
	    db->error.adc[panel/N_COMP].x.indef++;	\
	else if (ddb->adc[panel/N_COMP].x > pdb->adc[panel/N_COMP].x.upper) \
	    db->error.adc[panel/N_COMP].x.upper++;	\
	else if (ddb->adc[panel/N_COMP].x < pdb->adc[panel/N_COMP].x.lower) \
	    db->error.adc[panel/N_COMP].x.lower++;	\
	else	\
	    ;

#define	STALEADC(x)	\
	if (IS_STALEA (ddb->adc[panel/N_COMP].timestamp))	\
	    ddb->adc[panel/N_COMP].x = INDEFA;

/* structure definitions */

typedef	struct	{
	int	r;		/* radius (inches)			*/
	int	t;		/* theta (degrees)			*/
	int	z;		/* height (inches)			*/
	float	x;		/* (r,t) (inches)			*/
	float	y;		/* (r,t) (inches)			*/
	int	r1;		/* limits				*/
	int	r2;
	int	t1;
	int	t2;
	int	z1;
	int	z2;
} LOC;				/* TC or heater location		*/

typedef	struct	{
	BOOL	down;		/* status				*/
	BOOL	ignore;		/* use it ?				*/
	int	tctype;		/* type of TC				*/
	int	serial;		/* TC serial number			*/
	TEMP	offset;		/* zero point				*/
	LOC	loc;		/* location				*/
} p_tc;				/* TC parameters			*/

typedef	struct	{
	BOOL	error;		/* badness				*/
	TEMP	mtmp[N_MTMP];	/* time median filter			*/
	int	last;		/* index of last mtmp			*/
	TEMP	good;		/* value of last good mtmp		*/
} i_tc;				/* TC intermediate values		*/

typedef	struct	{
	TEMP	ttmp;		/* final temperature			*/
} d_tc;				/* TC data				*/

typedef	struct	{
	BOOL	down;		/* status				*/
	int	ijblock;	/* ij block number			*/
	int	serial;		/* TIC serial number			*/
	DSB	select;		/* select buss address of this TIC	*/
	int	tctype;		/* type of ij sensor			*/
	float	reference;	/* reference voltage			*/
	p_tc	tc[N_TTMP];	/* TC parameters			*/
} p_tic;			/* TIC parameters			*/

typedef	struct	{
	BOOL	error;		/* badness				*/
	float	scale;		/* millivolts per count			*/
	COUNT	count[N_TC];	/* raw counts				*/
	i_tc	tc[N_TTMP];	/* TC intermediate values		*/
} i_tic;			/* TIC intermediate values		*/

typedef	struct	{
	TEMP	jtmp;		/* junction temperature			*/
	d_tc	tc[N_TTMP];	/* TC data				*/
} d_tic;			/* TIC data				*/

typedef	struct	{
	p_tic	tic[N_TIC];	/* TIC parameters			*/
} p_counter;			/* counter parameters			*/

typedef	struct	{
	i_tic	tic[N_TIC];	/* TIC intermediate values		*/
} i_counter;			/* counter intermediate values		*/

typedef	struct	{
	d_tic	tic[N_TIC];	/* TIC data				*/
} d_counter;			/* counter data				*/

typedef	struct	{
	BOOL	down;		/* status				*/
} p_buss;			/* buss parameters			*/

typedef	struct	{
	BOOL	error;		/* badness				*/
} i_buss;			/* buss intermediate values		*/

typedef	struct	{
	p_buss	buss[N_BUSS];	/* buss parameters			*/
} p_select;			/* select card parameters		*/

typedef	struct	{
	i_buss	buss[N_BUSS];	/* buss intermediate values		*/
} i_select;			/* select card intermediate values	*/

typedef	struct	{
	BOOL	down;		/* status				*/
	int	connect;	/* physically connected			*/
	int	port;		/* connection port			*/
	p_counter counter[N_COUNTER];	/* counter parameters		*/
	p_select select[N_SELECT];	/* select card parameters	*/
} p_dcu;			/* DCU parameters			*/

typedef	struct	{
	BOOL	error;		/* badness				*/
	i_counter counter[N_COUNTER];	/* counter intermediate values	*/
	i_select select[N_SELECT];	/* select intermediate values	*/
} i_dcu;			/* DCU intermediate values		*/

typedef	struct	{
	long	timestamp;
	d_counter counter[N_COUNTER];	/* counter data			*/
} d_dcu;			/* DCU data				*/

typedef	struct	{
	BOOL	he_down;	/* heater element status		*/
	BOOL	cs_down;	/* current sensor status		*/
	BOOL	rs_down;	/* remote current sensor status		*/
	BOOL	vs_down;	/* voltage sensor status		*/
	BOOL	ignore;		/* use it ?				*/
	int	zone;		/* control zone				*/
	int	beam;		/* beam number				*/
	int	twist;		/* twistlock number			*/
	PFE	rcs;		/* remote current sensor address	*/
	int	n_nneighbor;	/* # of near neighboring TCs		*/
	DNTX	nneighbor[N_NNEIGHBOR];	/* address of near neighbors	*/
	int	n_fneighbor;	/* # of far  neighboring TCs		*/
	DNTX	fneighbor[N_FNEIGHBOR];	/* address of far  neighbors	*/
	BOOL	ck_down;	/* heater error check status		*/
	LOC	loc;		/* location				*/
} p_element;			/* element parameters			*/

typedef	struct	{
	int	error;	/* error code for he, vs, cs failures		*/
	BOOL	state;	/* temporary on-off state for making maps	*/
	POWER	left;	/* temporary heat left when   making maps	*/
} i_element;			/* element intermediate values		*/

typedef	struct	{
	BOOL	ndeviant[N_NNEIGHBOR];	/* badness			*/
	BOOL	fdeviant[N_FNEIGHBOR];	/* badness			*/
	TEMP	htmp;		/* heater temperature			*/
	TEMP	p_error;		/* proportional error		*/
	TEMP	i_error;                /* integral error		*/
	TEMP	d_error;                /* derivative error		*/
	TEMP	l_error;		/* last error			*/
	float	p_product;		/* proportional power		*/
	float	i_product;		/* integral power		*/
	float	d_product;		/* derivative power		*/
	POWER	heat;		/* power request			*/
} d_element;			/* element data				*/

typedef	struct	{
	int	max_load;	/* maximum # of HEs allowed on together	*/
	int	epsilon;	/* duration factor			*/
	p_element element[N_ELEMENT];	/* element parameters		*/
} p_fase;			/* fase parameters			*/

typedef	struct	{
	int	low_load;	/* minimum # of HEs on at the same time	*/
	int	nhigh;		/* # of P ticks at higher load		*/
	i_element element[N_ELEMENT];	/* element intermediate values	*/
} i_fase;			/* fase intermediate values		*/

typedef	struct	{
	float	calc_load;	/* average # of HEs         on together	*/
	d_element element[N_ELEMENT];	/* element data			*/
} d_fase;			/* fase data				*/

typedef	struct	{
	BOOL	ss_down;	/* sensors down				*/
	int	connect;	/* physically connected			*/
	int	port;		/* connection port			*/
	p_fase	fase[N_FASE];	/* fase parameters			*/
} p_panel;			/* panel parameters			*/

typedef	struct	{
	unsigned char	mapbyte[LEN_MAP];	/* ssr maps		*/
} i_map;

typedef	struct	{
	BOOL	ss_error;	/* sensors badness - protocol error	*/
	BOOL	pp_error;	/* sensors badness - buss failure	*/
	i_fase	fase[N_FASE];	/* fase intermediate values		*/
	i_map	ssr[N_MAP*MAX_POWER];		/* ssr maps		*/
	i_map	omap[N_PMAP];	/* output maps				*/
	i_map	imap[N_PMAP];	/* input  maps				*/
} i_panel;			/* panel intermediate values		*/

typedef	struct	{
	d_fase	fase[N_FASE];	/* fase data				*/
} d_panel;			/* panel data				*/

typedef	struct	{
	float	mt_polycoef[N_POLYCOEF]; /* measurement temperature	*/
	float	cv_polycoef[N_POLYCOEF]; /* compensation voltage	*/
	float	jt_polycoef[N_POLYCOEF]; /* junction temperature	*/
} p_tctype;				 /* tctype parameters		*/

typedef	struct	{
	TIME	time;		/* node time				*/
	TEMP	temp;		/* node temp				*/
	TEMP	deviation;	/* deviation limit			*/
	TEMP	tdeviation;	/* TTMP (TC) deviation limit		*/
	int	nlabel;		/* node label				*/
	int	wflag;		/* wait flag				*/
	int	wzone;		/* zone whose node we wait on		*/
	int	wlabel;		/* node label to wait on in zone	*/
	float	p_coef;		/* proportional coefficient		*/
	float	i_coef;		/* integral     coefficient		*/
	float	d_coef;		/* derivative   coefficient		*/
	int	i_depth;	/* depth of integral			*/
	POWER	limit;		/* power limit				*/
} p_node;			/* node parameters			*/

typedef	struct	{
	TIME	time;		/* zone time				*/
	BOOL	clock;		/* clock running ?			*/
} b_zone;			/* zone parameters (bi-directional)	*/

typedef	struct	{
	BOOL	ck_down;	/* zone scatter check status		*/
	BOOL	he_ck_down;	/* heater error check status		*/
	int	n_node;		/* # of nodes in schedule		*/
	p_node	node[N_NODE];	/* node parameters			*/
} p_zone;			/* zone parameters			*/

typedef	struct	{
	int	count;
	TEMP	tmin;
	TEMP	tmax;
	TEMP	tsum;
	float	hsum;
} i_zone;			/* zone intermediate values		*/

typedef	struct	{
	TIME	togo;		/* time to go until next node		*/
	float	delta;		/* current scheduled slope		*/
	int	c_node;		/* current node index			*/
	TEMP	zdiff;		/* zone temperature error		*/
	POWER	zpower;		/* average zone power			*/
	TEMP	etmp;		/* current scheduled temperature	*/
	TEMP	ztmp;		/* average zone temperature		*/
	TEMP	zsct;		/* average zone temperature scatter	*/
} d_zone;			/* zone data				*/

typedef	struct	{
	int	info;
} b_misc;

typedef	struct	{
	long	timestamp;	/* timestamp of last parameter change	*/
	int	vnumber;	/* my computer number 0, 1, 2		*/
	BOOL	vup[N_COMP];	/* V computer communications enabled	*/
	BOOL	config;		/* config mode				*/
	BOOL	logrotv;	/* log rotation data			*/
	BOOL	xadc;		/* check ADC values against limits	*/
	BOOL	xjtmp;		/* check JTMP`s				*/
	TEMP	djtmp;		/* JTMP difference			*/
	int	rport[N_COMP];	/* rotation port			*/
	TEMP	lvdt[N_LVDT];	/* lvdt offsets				*/
} p_misc;

typedef	struct	{
	int	msclock;	/* millisecond clock, range 0-59999	*/
	int	tclock;		/* temperature clock 0-9 500ms units	*/
	int	cclock;		/* control clock 0-9 6000ms units	*/
	int	pclock;		/* power clock 0-239 250ms units	*/
	int	*tsem;		/* t semaphore (really vxWorks SEM_ID)	*/
	int	*csem;		/* c semaphore				*/
	int	*psem;		/* k semaphore (clock sync)		*/
	int	*ksem;		/* p semaphore				*/
	int	*rsem;		/* r semaphore				*/
	int	*dcusem;	/* dcu semaphore			*/
	int	*adcsem;	/* adc semaphore			*/
	BOOL	horn;		/* priority error horn			*/
	int	gong;		/* priority error gong			*/
	int	ncomp;		/* my comp number			*/
} i_misc;

typedef	struct	{
	long	uclock;		/* unix clock time of day		*/
	unsigned long	iclock;	/* ip   clock time of day		*/
} d_misc;

typedef	struct	{
	float	lower;		/* lower limit				*/
	float	upper;		/* upper limit				*/
} ADC;				/* ADC data				*/

typedef	struct	{
	ADC	current;	/* amps					*/
	ADC	voltage;	/* volts				*/
} pa_fase;			/* fase data				*/

typedef	struct	{
	ADC	current;	/* neutral				*/
	pa_fase	fase[N_FASE];	/* fase data				*/
} pa_panel;			/* panel data				*/

typedef	struct	{
	ADC	voltage;	/* housekeeping				*/
	pa_panel	panel[N_PANEL/N_COMP];
} p_adc;			/* ADC data				*/

typedef	struct	{
	float	current;	/* amps					*/
	float	voltage;	/* volts				*/
} da_fase;			/* fase data				*/

typedef	struct	{
	float	current;	/* neutral				*/
	da_fase	fase[N_FASE];	/* fase data				*/
} da_panel;			/* panel data				*/

typedef	struct	{
	long	timestamp;
	float	voltage;	/* housekeeping				*/
	da_panel	panel[N_PANEL/N_COMP];
	float	r[N_ROT];	/* rotation measurements		*/
	float	rztmp;		/* rotation speed          		*/
} d_adc;			/* ADC data				*/

typedef	struct	{
	b_zone		zone[N_ZONE];
	b_misc		misc;
} b_database;			/* parameters database (bi-directional)	*/

typedef	struct	{
	p_adc		adc[N_COMP];
	p_dcu		dcu[N_DCU];
	p_panel		panel[N_PANEL];
	p_tctype	tctype[N_TCTYPE];
	p_zone		zone[N_ZONE];
	p_misc		misc;
} p_database;			/* parameters database			*/

typedef	struct	{
	i_dcu		dcu[N_DCU];
	i_panel		panel[N_PANEL];
	i_zone		zone[N_ZONE];
	i_misc		misc;
} i_database;			/* intermediate values database		*/

typedef	struct	{
	d_adc		adc[N_COMP];
	d_dcu		dcu[N_DCU];
	d_panel		panel[N_PANEL];
	d_zone		zone[N_ZONE];
	d_misc		misc;
} d_database;			/* data database			*/

/* error counters structure
 */
typedef	struct	{
	int	fpe;
	int	back;
	int	shrt;
	int	melt;
	int	open;
} e_tc;				/* TC error       values		*/

typedef	struct	{
	int	ijt;
	int	jtl;
	e_tc	tc[N_TC];	/* TC error       values		*/
} e_tic;			/* TIC error       values		*/

typedef	struct	{
	e_tic	tic[N_TIC];	/* TIC error       values		*/
} e_counter;			/* counter error       values		*/

typedef	struct	{
	int	mer;
} e_buss;			/* buss error       values		*/

typedef	struct	{
	e_buss	buss[N_BUSS];	/* buss error       values		*/
} e_select;			/* select card error       values	*/

typedef	struct	{
	int	ton;
	int	tof;
	int	dst;
	e_counter counter[N_COUNTER];	/* counter error       values	*/
	e_select select[N_SELECT];	/* select error       values	*/
} e_dcu;			/* DCU error       values		*/

typedef	struct	{
	int	con;
	int	von;
	int	hon;
	int	hof;
	int	vof;
	int	cof;
	int	rof;
	int	ron;
	int	ooii;
	int	oioi;
	int	oiio;
	int	iooi;
	int	ioio;
	int	iioo;
	int	her;
	int	hsc;
} e_element;			/* element error       values		*/

typedef	struct	{
	e_element element[N_ELEMENT];	/* element error       values	*/
} e_fase;			/* fase error       values		*/

typedef	struct	{
	int	ppe;
	int	pkp;
	e_fase	fase[N_FASE];	/* fase error       values		*/
} e_panel;			/* panel error       values		*/

typedef	struct	{
	int	zsc;
} e_zone;			/* zone error       values		*/

typedef	struct	{
	int	lower;		/* lower limit error			*/
	int	upper;		/* upper limit error			*/
	int	indef;		/* indefinite  error			*/
} e_ADC;			/* ADC data				*/

typedef	struct	{
	e_ADC	current;	/* amps					*/
	e_ADC	voltage;	/* volts				*/
} ea_fase;			/* fase data				*/

typedef	struct	{
	e_ADC	current;	/* neutral				*/
	ea_fase	fase[N_FASE];	/* fase data				*/
} ea_panel;			/* panel data				*/

typedef	struct	{
	e_ADC	voltage;	/* housekeeping				*/
	ea_panel	panel[N_PANEL/N_COMP];
} e_adc;			/* ADC data				*/

typedef	struct	{
	int	texc;		/* a task was restarted			*/
} e_misc;

typedef	struct	{
	int		unseen;	/* unseen errors			*/
	e_adc		adc[N_COMP];
	e_dcu		dcu[N_DCU];
	e_panel		panel[N_PANEL];
	e_zone		zone[N_ZONE];
	e_misc		misc;
} e_database;			/* error       values database		*/

typedef	struct	{
	b_database	biparameter;
	p_database	parameter;
	i_database	intermediate;
	d_database	data;
	e_database	error;
} database;			/* total database			*/

#ifndef	UTIL
extern	p_buss	*pbuss_dsb();
extern	i_buss	*ibuss_dsb();
extern	p_tc	*ptc_dntx();
extern	i_tc	*itc_dntx();
extern	d_tc	*dtc_dntx();
extern	p_tic	*ptic_dntx();
extern	i_tic	*itic_dntx();
extern	d_tic	*dtic_dntx();
extern	p_dcu	*pdcu_dntx();
extern	i_dcu	*idcu_dntx();
extern	d_dcu	*ddcu_dntx();
extern	p_element	*phe_pfe();
extern	i_element	*ihe_pfe();
extern	d_element	*dhe_pfe();
extern	p_fase	*pfase_pfe();
extern	pa_fase	*pafase_pfe();
extern	i_fase	*ifase_pfe();
extern	d_fase	*dfase_pfe();
extern	da_fase	*dafase_pfe();
extern	p_panel	*ppanel_pfe();
extern	pa_panel *papanel_pfe();
extern	i_panel	*ipanel_pfe();
extern	d_panel	*dpanel_pfe();
extern	da_panel *dapanel_pfe();
extern	int	n_nneigh();
extern	PFE	nneigh();
extern	int	n_fneigh();
extern	PFE	fneigh();
extern	DNTX	adjtic();
extern	TEMP	adjtmp();
extern	DNTX	dntx_dsb();
extern	int	n_dntx_dsb();
#endif

/* The total database is divided into parts according to usage.
 * The parameters are modified only by the control room computers.
 * The onboard computers only read the parameters and never modify them.
 * The control room computer can update the parameters to the onboard,
 * and can read them back for verification.
 *
 * The intermediate values are internal to the onboard computers and
 * never need to be exchanged with the control room.
 *
 * The data values are produced, measured, computed, or derived on the
 * onboard computers.  They may be read back to the control room but
 * never modified by the control room.
 *
 * The bidirectional parameters have aspects of both "parameter" and
 * "data" sections.  The control room may update these parameters to the
 * onboard computers, but the onboard computers may (and usually do)
 * modify these numbers.  Thus the control really should read back these
 * values before modifying and updating them to the onboard computers.
 */
