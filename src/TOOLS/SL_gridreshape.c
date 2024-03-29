#include <R.h>	//WCC:add

//WCC:add
#include "../BLACS/Bdef.h"
#include "../BLACS/Bdef_wcc.h"

#include <stdlib.h>
#include <stdio.h>

int SL_Cgridreshape(int ctxt, int pstart, int row_major_in, int row_major_out, int P, int Q)
//WCC int ctxt, pstart, row_major_in, row_major_out, P, Q;
{
   int Cblacs_pnum(int, int, int);
   int nctxt, P0, Q0, Np, i, *g;

   Cblacs_gridinfo(ctxt, &P0, &Q0, &i, &Np);
   Np = P * Q;
   if (Np+pstart > P0*Q0)
   {
/*WCC      fprintf(stderr, "Illegal reshape command in %s\n",__FILE__); */
      REprintf("Illegal reshape command in %s\n",__FILE__);
      Cblacs_abort(ctxt, -22);
   }
   g = (int *) malloc(Np * sizeof(int));
   if (!g)
   {
/*WCC      fprintf(stderr, "Cannot allocate memory in %s\n",__FILE__); */
      REprintf("Cannot allocate memory in %s\n",__FILE__);
      Cblacs_abort(ctxt, -23);
   }
   if (row_major_in)  /* Read in in row-major order */
   {
      if (row_major_out)
	 for (i=0; i != Np; i++)
            g[(i%Q)*P+i/Q] = Cblacs_pnum(ctxt, (pstart+i)/Q0, (pstart+i)%Q0);
      else
	 for (i=0; i != Np; i++)
            g[i] = Cblacs_pnum(ctxt, (pstart+i)/Q0, (pstart+i)%Q0);
   }
   else /* read in in column-major order */
   {
      if (row_major_out)
	 for (i=0; i != Np; i++)
            g[(i%Q)*P+i/Q] = Cblacs_pnum(ctxt, (pstart+i)%P0, (pstart+i)/P0);
      else
	 for (i=0; i != Np; i++)
            g[i] = Cblacs_pnum(ctxt, (pstart+i)%P0, (pstart+i)/P0);
   }
   Cblacs_get(ctxt, 10, &nctxt);
   Cblacs_gridmap(&nctxt, g, P, P, Q);
   free(g);

   return(nctxt);
}

int sl_gridreshape_(int *ctxt, int *pstart, int *row_major_in, int *row_major_out, int *P, int *Q)
//WCC int *ctxt, *pstart, *row_major_in, *row_major_out, *P, *Q;
{
   return( SL_Cgridreshape(*ctxt, *pstart, *row_major_in, *row_major_out,
                           *P, *Q) );
}

int SL_GRIDRESHAPE(int *ctxt, int *pstart, int *row_major_in, int *row_major_out, int *P, int *Q)
//WCC int *ctxt, *pstart, *row_major_in, *row_major_out, *P, *Q;
{
   return( SL_Cgridreshape(*ctxt, *pstart, *row_major_in, *row_major_out,
                           *P, *Q) );
}

int sl_gridreshape__(int *ctxt, int *pstart, int *row_major_in, int *row_major_out, int *P, int *Q)
//WCC int *ctxt, *pstart, *row_major_in, *row_major_out, *P, *Q;
{
   return( SL_Cgridreshape(*ctxt, *pstart, *row_major_in, *row_major_out,
                           *P, *Q) );
}

int sl_gridreshape(int *ctxt, int *pstart, int *row_major_in, int *row_major_out, int *P, int *Q)
//WCC int *ctxt, *pstart, *row_major_in, *row_major_out, *P, *Q;
{
   return( SL_Cgridreshape(*ctxt, *pstart, *row_major_in, *row_major_out,
                           *P, *Q) );
}
