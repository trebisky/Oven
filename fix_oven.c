/* 
 * fix_oven.c
 *
 * Fix endian issues in packets sent over the network.
 *
 * T. Trebisky 10-18-2018
 */

#include "oven.h"

// void swap4 ( char * );

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

/* float and temp */
#define Fswap(f)	swap4 ( (char *) &f )
#define Tswap(f)	swap4 ( (char *) &f )

/* int, BOOL, power, ... */
#define Iswap(i)	swap4 ( (char *) &i )
#define Bswap(f)	swap4 ( (char *) &f )

#define LOOP(x,lim)	for ( x=0; x < lim; x++ )

void
fix_data ( d_database *db )
{
	int i, j, k, l;

	// adc array
	LOOP ( i, N_COMP ) {
	    Iswap ( db->adc[i].timestamp );
	    Fswap ( db->adc[i].voltage );
	    LOOP ( j, N_PANEL/N_COMP ) {
		Fswap ( db->adc[i].panel[j].current );
		LOOP ( k, N_FASE ) {
		    Fswap ( db->adc[i].panel[j].fase[k].current );
		    Fswap ( db->adc[i].panel[j].fase[k].voltage );
		}
	    }
	    LOOP ( j, N_ROT ) {
		Fswap ( db->adc[i].r[j] );
	    }
	    Fswap ( db->adc[i].rztmp );
	}

	// dcu array
	LOOP ( i, N_DCU ) {
	    Iswap ( db->dcu[i].timestamp );
	    LOOP ( j, N_COUNTER ) {
		LOOP ( k, N_TIC ) {
		    Tswap ( db->dcu[i].counter[j].tic[k].jtmp );
		    LOOP ( l, N_TTMP ) {
			Tswap ( db->dcu[i].counter[j].tic[k].tc[l].ttmp );
		    }
		}
	    }
	}

	// panel array
	LOOP ( i, N_PANEL ) {
	    LOOP ( j, N_FASE ) {
		Fswap ( db->panel[i].fase[j].calc_load );
		LOOP ( k, N_ELEMENT ) {
		    LOOP ( l, N_NNEIGHBOR ) {
			Bswap ( db->panel[i].fase[j].element[k].ndeviant[l] );
		    }
		    LOOP ( l, N_FNEIGHBOR ) {
			Bswap ( db->panel[i].fase[j].element[k].fdeviant[l] );
		    }
		    Tswap ( db->panel[i].fase[j].element[k].htmp );
		    Tswap ( db->panel[i].fase[j].element[k].p_error );
		    Tswap ( db->panel[i].fase[j].element[k].i_error );
		    Tswap ( db->panel[i].fase[j].element[k].d_error );
		    Tswap ( db->panel[i].fase[j].element[k].l_error );
		    Fswap ( db->panel[i].fase[j].element[k].p_product );
		    Fswap ( db->panel[i].fase[j].element[k].i_product );
		    Fswap ( db->panel[i].fase[j].element[k].d_product );
		    Iswap ( db->panel[i].fase[j].element[k].heat );
		}
	    }
	}

	// zone array
	LOOP ( i, N_ZONE ) {
	    Iswap ( db->zone[i].togo );
	    Fswap ( db->zone[i].delta );
	    Iswap ( db->zone[i].c_node );
	    Tswap ( db->zone[i].zdiff );
	    Iswap ( db->zone[i].zpower );
	    Tswap ( db->zone[i].etmp );
	    Tswap ( db->zone[i].ztmp );
	    Tswap ( db->zone[i].zsct );
	}

	// misc
	Iswap ( db->misc.uclock );
	Iswap ( db->misc.iclock );
}

void
fix_param ( p_database *db )
{
	int i, j, k, l;

	// adc
	LOOP ( i, N_COMP ) {
	    Iswap ( db->adc[i].voltage.lower );
	    Iswap ( db->adc[i].voltage.upper );
	    LOOP ( j, N_PANEL/N_COMP ) {
		Fswap ( db->adc[i].panel[j].current.lower );
		Fswap ( db->adc[i].panel[j].current.upper );
		LOOP ( k, N_FASE) {
		    Fswap ( db->adc[i].panel[j].fase[k].current.lower );
		    Fswap ( db->adc[i].panel[j].fase[k].current.upper );
		    Fswap ( db->adc[i].panel[j].fase[k].voltage.lower );
		    Fswap ( db->adc[i].panel[j].fase[k].voltage.upper );
		}
	    }
	}

	LOOP ( i, N_DCU ) {
	    Bswap ( db->dcu[i].down );
	    Iswap ( db->dcu[i].connect );
	    Iswap ( db->dcu[i].port );
	    LOOP ( j, N_COUNTER) {
		LOOP ( k, N_TIC) {
		    Bswap ( db->dcu[i].counter[j].tic[k].down );
		    Iswap ( db->dcu[i].counter[j].tic[k].ijblock );
		    Iswap ( db->dcu[i].counter[j].tic[k].serial );
		    Iswap ( db->dcu[i].counter[j].tic[k].select );
		    Iswap ( db->dcu[i].counter[j].tic[k].tctype );
		    Fswap ( db->dcu[i].counter[j].tic[k].reference );
		    LOOP ( l, N_TTMP) {
			Bswap ( db->dcu[i].counter[j].tic[k].tc[l].down );
			Bswap ( db->dcu[i].counter[j].tic[k].tc[l].ignore );
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].tctype );
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].serial );
			Tswap ( db->dcu[i].counter[j].tic[k].tc[l].offset );
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].loc.r );	/* LOC */
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].loc.t );	/* LOC */
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].loc.z );	/* LOC */
			Fswap ( db->dcu[i].counter[j].tic[k].tc[l].loc.x );	/* LOC */
			Fswap ( db->dcu[i].counter[j].tic[k].tc[l].loc.y );	/* LOC */
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].loc.r1 );	/* LOC */
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].loc.r2 );	/* LOC */
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].loc.t1 );	/* LOC */
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].loc.t2 );	/* LOC */
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].loc.z1 );	/* LOC */
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].loc.z2 );	/* LOC */
		    }
		}
	    }
	    LOOP ( j, N_SELECT) {
		LOOP ( k, N_BUSS) {
		    Iswap ( db->dcu[i].select[j].buss[k].down );
		}
	    }
	}

	LOOP ( i, N_PANEL ) {
	    Bswap ( db->panel[i].ss_down );
	    Iswap ( db->panel[i].connect );
	    Iswap ( db->panel[i].port );
	    LOOP ( j, N_FASE ) {
		Iswap ( db->panel[i].fase[j].max_load );
		Iswap ( db->panel[i].fase[j].epsilon );
		LOOP ( k, N_ELEMENT ) {
		    Bswap ( db->panel[i].fase[j].element[k].he_down );
		    Bswap ( db->panel[i].fase[j].element[k].cs_down );
		    Bswap ( db->panel[i].fase[j].element[k].rs_down );
		    Bswap ( db->panel[i].fase[j].element[k].vs_down );
		    Bswap ( db->panel[i].fase[j].element[k].ignore );
		    Iswap ( db->panel[i].fase[j].element[k].zone );
		    Iswap ( db->panel[i].fase[j].element[k].beam );
		    Iswap ( db->panel[i].fase[j].element[k].twist );
		    Iswap ( db->panel[i].fase[j].element[k].rcs );
		    Iswap ( db->panel[i].fase[j].element[k].n_nneighbor );
		    LOOP ( l, N_NNEIGHBOR ) {
			Iswap ( db->panel[i].fase[j].element[k].nneighbor[l] );
		    }
		    Iswap ( db->panel[i].fase[j].element[k].n_fneighbor );
		    LOOP ( l, N_FNEIGHBOR ) {
			Iswap ( db->panel[i].fase[j].element[k].fneighbor[l] );
		    }
		    Iswap ( db->panel[i].fase[j].element[k].ck_down );
		    Iswap ( db->panel[i].fase[j].element[k].loc.r );	/* LOC */
		    Iswap ( db->panel[i].fase[j].element[k].loc.t );	/* LOC */
		    Iswap ( db->panel[i].fase[j].element[k].loc.z );	/* LOC */
		    Iswap ( db->panel[i].fase[j].element[k].loc.x );	/* LOC */
		    Iswap ( db->panel[i].fase[j].element[k].loc.y );	/* LOC */
		    Iswap ( db->panel[i].fase[j].element[k].loc.r1 );	/* LOC */
		    Iswap ( db->panel[i].fase[j].element[k].loc.r2 );	/* LOC */
		    Iswap ( db->panel[i].fase[j].element[k].loc.t1 );	/* LOC */
		    Iswap ( db->panel[i].fase[j].element[k].loc.t2 );	/* LOC */
		    Iswap ( db->panel[i].fase[j].element[k].loc.z1 );	/* LOC */
		    Iswap ( db->panel[i].fase[j].element[k].loc.z2 );	/* LOC */
		}
	    }
	}

	LOOP ( i, N_TCTYPE ) {
	    LOOP ( j, N_POLYCOEF ) {
		Fswap ( db->tctype[i].mt_polycoef[j] );
	    }
	    LOOP ( j, N_POLYCOEF ) {
		Fswap ( db->tctype[i].cv_polycoef[j] );
	    }
	    LOOP ( j, N_POLYCOEF ) {
		Fswap ( db->tctype[i].jt_polycoef[j] );
	    }
	}

	LOOP ( i, N_ZONE ) {
	    Bswap ( db->zone[i].ck_down );
	    Bswap ( db->zone[i].he_ck_down );
	    Iswap ( db->zone[i].n_node );
	    LOOP ( j, N_NODE ) {
		Iswap ( db->zone[i].node[j].time );
		Tswap ( db->zone[i].node[j].temp );
		Tswap ( db->zone[i].node[j].deviation );
		Tswap ( db->zone[i].node[j].tdeviation );
		Iswap ( db->zone[i].node[j].nlabel );
		Iswap ( db->zone[i].node[j].wflag );
		Iswap ( db->zone[i].node[j].wzone );
		Iswap ( db->zone[i].node[j].wlabel );
		Fswap ( db->zone[i].node[j].p_coef );
		Fswap ( db->zone[i].node[j].i_coef );
		Fswap ( db->zone[i].node[j].d_coef );
		Iswap ( db->zone[i].node[j].i_depth );
		Iswap ( db->zone[i].node[j].limit );
	    }
	}

	// misc
	Iswap ( db->misc.timestamp );
	Iswap ( db->misc.vnumber );

	LOOP ( i, N_COMP) {
	    Bswap ( db->misc.vup[i] );
	}

	Bswap ( db->misc.config );
	Bswap ( db->misc.logrotv );
	Bswap ( db->misc.xadc );
	Bswap ( db->misc.xjtmp );
	Tswap ( db->misc.djtmp );

	LOOP ( i, N_COMP) {
	    Iswap ( db->misc.rport[i] );
	}

	LOOP ( i, N_LVDT) {
	    Tswap ( db->misc.lvdt[i] );
	}

}

/* Just a little bitty thing */
void
fix_biparam ( b_database *db )
{
	int i;

	LOOP ( i, N_ZONE ) {
	    Iswap ( db->zone[i].time );
	    Iswap ( db->zone[i].clock );
	}
	Iswap ( db->misc.info );
}

void
fix_errors ( e_database *db )
{
	int i, j, k, l;

	Iswap ( db->unseen );

	// adc
	LOOP ( i, N_COMP ) {
	    Iswap ( db->adc[i].voltage.lower );
	    Iswap ( db->adc[i].voltage.upper );
	    Iswap ( db->adc[i].voltage.indef );
	    LOOP ( j, N_PANEL/N_COMP ) {
		Iswap ( db->adc[i].panel[j].current.lower );
		Iswap ( db->adc[i].panel[j].current.upper );
		Iswap ( db->adc[i].panel[j].current.indef );
		LOOP ( k, N_FASE ) {
		    Iswap ( db->adc[i].panel[j].fase[k].current.lower );
		    Iswap ( db->adc[i].panel[j].fase[k].current.upper );
		    Iswap ( db->adc[i].panel[j].fase[k].current.indef );
		    Iswap ( db->adc[i].panel[j].fase[k].voltage.lower );
		    Iswap ( db->adc[i].panel[j].fase[k].voltage.upper );
		    Iswap ( db->adc[i].panel[j].fase[k].voltage.indef );
		}
	    }
	}

	LOOP ( i, N_DCU ) {
	    Iswap ( db->dcu[i].ton );
	    Iswap ( db->dcu[i].tof );
	    Iswap ( db->dcu[i].dst );
	    LOOP ( j, N_COUNTER ) {
		LOOP ( k, N_TIC ) {
		    Iswap ( db->dcu[i].counter[j].tic[k].ijt );
		    Iswap ( db->dcu[i].counter[j].tic[k].jtl );
		    LOOP ( l, N_TC ) {
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].fpe );
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].back );
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].shrt );
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].melt );
			Iswap ( db->dcu[i].counter[j].tic[k].tc[l].open );
		    }
		}
	    }
	    LOOP ( j, N_SELECT ) {
		LOOP ( k, N_BUSS ) {
		    Iswap ( db->dcu[i].select[j].buss[k].mer );
		}
	    }
	}

	LOOP ( i, N_PANEL ) {
	    Iswap ( db->panel[i].ppe );
	    Iswap ( db->panel[i].pkp );
	    LOOP ( j, N_FASE ) {
		LOOP ( k, N_ELEMENT ) {
		    Iswap ( db->panel[i].fase[j].element[k].con );
		    Iswap ( db->panel[i].fase[j].element[k].von );
		    Iswap ( db->panel[i].fase[j].element[k].hon );
		    Iswap ( db->panel[i].fase[j].element[k].hof );
		    Iswap ( db->panel[i].fase[j].element[k].vof );
		    Iswap ( db->panel[i].fase[j].element[k].cof );
		    Iswap ( db->panel[i].fase[j].element[k].rof );
		    Iswap ( db->panel[i].fase[j].element[k].ron );
		    Iswap ( db->panel[i].fase[j].element[k].ooii );
		    Iswap ( db->panel[i].fase[j].element[k].oioi );
		    Iswap ( db->panel[i].fase[j].element[k].oiio );
		    Iswap ( db->panel[i].fase[j].element[k].iooi );
		    Iswap ( db->panel[i].fase[j].element[k].ioio );
		    Iswap ( db->panel[i].fase[j].element[k].iioo );
		    Iswap ( db->panel[i].fase[j].element[k].her );
		    Iswap ( db->panel[i].fase[j].element[k].hsc );
		}
	    }
	}

	LOOP ( i, N_ZONE ) {
	    Iswap ( db->zone[i].zsc );
	}

	Iswap ( db->misc.texc );

}

int
fix_gong ( int *buf )
{
	Iswap ( buf[0] );
	return buf[0];
}

void
fix_rspeed ( int *buf )
{
	Iswap ( buf[0] );
	Iswap ( buf[1] );
}

/* THE END */
