/*
 * $Id$
 *
 * Copyright (c) 2009-2012 ADMB foundation
 */
/**
 * \file
 * Contains routines to find eigenvectors and eigenvalues
 * for variable types.
 */

#include <fvar.hpp>

void eigens (const dvar_matrix & m, const dvar_matrix & _evecs,
	     const dvar_vector & _evals);

/**
 * \ingroup eigen
 * Eigenvalues
 * \param m \f$m\f$
 * \return a variable vector containing the
 *         eigenvalues of \f$m\f$.
 */
dvar_vector eigenvalues(const dvar_matrix &m)
{
  if (m.rowsize () != m.colsize ())
    {
      cerr <<
	"error -- non square matrix passed to dvector eigenvalues(const dmatrix& m)\n";
      ad_exit (1);
    }

  int rmin = m.rowmin ();
  int rmax = m.rowmax ();

  dvar_matrix evecs (rmin, rmax, rmin, rmax);
  dvar_vector evals (rmin, rmax);

  eigens (m, evecs, evals);

  return evals;
}

/**
 * \ingroup eigen
 * Eigenvectors
 * \param m \f$m\f$
 * \return a variable matrix with the
 *         eigenvectors of \f$m\f$ stored in its columns.
 */
dvar_matrix eigenvectors(const dvar_matrix &m)
{
  if (m.rowsize () != m.colsize ())
    {
      cerr <<
	"error -- non square matrix passed to dmatrix eigenvectors(const dmatrix& m)\n";
      ad_exit (1);
    }

  int rmin = m.rowmin ();
  int rmax = m.rowmax ();

  dvar_matrix evecs (rmin, rmax, rmin, rmax);
  dvar_vector evals (rmin, rmax);

  eigens (m, evecs, evals);

  return evecs;
}

/**
 * \ingroup eigen
 * Eigenvector and Eigenvalue algorithm
 * \param m \f$m\f$
 * \param _evecs
 * \param _evals
 *
 * \return
 * On return _evecs will be a variable matrix with the
 *  eigenvectors of \f$m\f$ stored in its columns.
 * On return _evals will be a variable vector containing the
 *  eigenvalues of \f$m\f$.
 * 
 * \n\n Cephes Math Library Release 2.1:  December, 1988
 * Copyright 1984, 1987, 1988 by Stephen L. Moshier 
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
void eigens (const dvar_matrix & m, const dvar_matrix & _evecs,
	const dvar_vector & _evals)
{
  ADUNCONST (dvar_matrix, evecs)
    ADUNCONST (dvar_vector, evals) if (m.rowsize () != m.colsize ())
    {
      cerr << "error -- non square matrix passed to "
	<<
	"void (const dmatirx& m, const dmatirx& evecs, const dvector& evals)\n";
      ad_exit (1);
    }
  if ((m.rowsize () != evecs.rowsize ())
      || (m.colsize () != evecs.colsize ()))
    {
      cerr << "error -- eigenvector array not compatible with matrix in "
	<<
	"void (const dmatirx& m, const dmatirx& evecs, const dvector& evals)\n";
      ad_exit (1);
    }
  if (m.rowsize () != evals.size ())
    {
      cerr << "error -- eigenvalue array not compatible with matrix in "
	<<
	"void (const dmatirx& m, const dmatirx& evecs, const dvector& evals)\n";
      ad_exit (1);
    }

  int evecslb = evecs.rowmin();
  int evalslb = evals.indexmin();

  int N = m.colsize ();

  dvar_matrix mat = symmetrize (m);

  //shift m, evecs, and evals so they are compatible with algorithm
  mat.rowshift (0);
  mat.colshift (0);
  evecs.rowshift (0);
  evecs.colshift (0);
  evals.shift (0);


  //mat[ row, column ] = A[ (row*row+row)/2 + column ]
  dvar_vector A (0, N * (N + 1) / 2);

  for (int i = 0; i < N; i++)
    {
      for (int j = 0; j <= i; j++)
	{
	  A ((i * i + i) / 2 + j) = mat (i, j);
	}
    }

  dvar_vector RR (0, N * N - 1);
  dvar_vector E (0, N - 1);

  // run cephes code
  int IND, L, LL, LM, M, MM, MQ, I, J, IA, LQ;
  int IQ, IM, IL, NLI, NMI;
  dvariable ANORM, ANORMX, AIA, THR, ALM, ALL, AMM, X, Y;
  dvariable SINX, SINX2, COSX, COSX2, SINCS, AIL, AIM;
  dvariable RLI, RMI;
  static double RANGE = 1.0e-10;	/*3.0517578e-5; */


  /* Initialize identity matrix in RR[] */
  for (J = 0; J < N * N; J++)
    RR[J] = 0.0;
  MM = 0;
  for (J = 0; J < N; J++)
    {
      RR[MM + J] = 1.0;
      MM += N;
    }

  ANORM = 0.0;
  for (I = 0; I < N; I++)
    {
      for (J = 0; J < N; J++)
	{
	  if (I != J)
	    {
	      IA = I + (J * J + J) / 2;
	      AIA = A[IA];
	      ANORM += AIA * AIA;
	    }
	}
    }
  if (ANORM <= 0.0)
    goto done;
  ANORM = sqrt (ANORM + ANORM);
  ANORMX = ANORM * RANGE / N;
  THR = ANORM;

  while (THR > ANORMX)
    {
      THR = THR / N;

      do
	{			/* while IND != 0 */
	  IND = 0;

	  for (L = 0; L < N - 1; L++)
	    {

	      for (M = L + 1; M < N; M++)
		{
		  MQ = (M * M + M) / 2;
		  LM = L + MQ;
		  ALM = A[LM];
		  if (fabs (ALM) < THR)
		    continue;

		  IND = 1;
		  LQ = (L * L + L) / 2;
		  LL = L + LQ;
		  MM = M + MQ;
		  ALL = A[LL];
		  AMM = A[MM];
		  X = (ALL - AMM) / 2.0;
		  Y = -ALM / sqrt (ALM * ALM + X * X);
		  if (X < 0.0)
		    Y = -Y;
		  SINX = Y / sqrt (2.0 * (1.0 + sqrt (1.0 - Y * Y)));
		  SINX2 = SINX * SINX;
		  COSX = sqrt (1.0 - SINX2);
		  COSX2 = COSX * COSX;
		  SINCS = SINX * COSX;

		  /*     ROTATE L AND M COLUMNS */
		  for (I = 0; I < N; I++)
		    {
		      IQ = (I * I + I) / 2;
		      if ((I != M) && (I != L))
			{
			  if (I > M)
			    IM = M + IQ;
			  else
			    IM = I + MQ;
			  if (I >= L)
			    IL = L + IQ;
			  else
			    IL = I + LQ;
			  AIL = A[IL];
			  AIM = A[IM];
			  X = AIL * COSX - AIM * SINX;
			  A[IM] = AIL * SINX + AIM * COSX;
			  A[IL] = X;
			}
		      NLI = N * L + I;
		      NMI = N * M + I;
		      RLI = RR[NLI];
		      RMI = RR[NMI];
		      RR[NLI] = RLI * COSX - RMI * SINX;
		      RR[NMI] = RLI * SINX + RMI * COSX;
		    }

		  X = 2.0 * ALM * SINCS;
		  A[LL] = ALL * COSX2 + AMM * SINX2 - X;
		  A[MM] = ALL * SINX2 + AMM * COSX2 + X;
		  A[LM] = (ALL - AMM) * SINCS + ALM * (COSX2 - SINX2);
		}		/* for M=L+1 to N-1 */
	    }			/* for L=0 to N-2 */

	}
      while (IND != 0);

    }				/* while THR > ANORMX */

done:;

  /* Extract eigenvalues from the reduced matrix */
  L = 0;
  for (J = 1; J <= N; J++)
    {
      L = L + J;
      E[J - 1] = A[L - 1];
    }

  // end of cephes code


  //put data into evecs and evals
  //EV[ n*i+j ] = evecs[i][j]
  for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
	{
	  evecs (j, i) = RR[N * i + j];
	}
    }

  evals = E;

  //shift evecs and evals back
  evecs.rowshift (evecslb);
  evecs.colshift (evecslb);
  evals.shift (evalslb);

}
