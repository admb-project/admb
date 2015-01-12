/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * This file can probably be removed.
 */
//#define USE_DD_STUFF
//#define USE_DD
#  include <admodel.h>
//# include <hs.h>
/*
dvector solve(const dmatrix & _st,const dmatrix & Hess,
  const dvector& grad)
{
  ADUNCONST(dmatrix,st)
  int nz=st.indexmax();
  int n=Hess.indexmax();
  // fill up compressed triplet with nonzero entries of the Hessian
  for (int i=1;i<=nz;i++)
  {
    st(i,3)=Hess(st(i,1),st(i,2));
  }

  hs_smatrix HS(n,st);  // Convert triplet to working format

  hs_symbolic S(n,st,1);         // Fill reducing row-col permutation                 
  hs_smatrix L(S);              // Allocates cholesky factor

  chol(HS,S,L);                  // Does numeric factorization

  dvector x(0,n-1);
  grad.shift(0);
  x = cs_ipvec(S.pinv, grad);
  grad.shift(1);
  x = cs_lsolve(L,x);
  x = cs_ltsolve(L,x);
  x = cs_pvec(S.pinv,x);
  x.shift(1);
  return x;
}
*/

