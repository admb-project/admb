/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2009-2012 ADMB foundation
 *
 * This code is inspired by the CSparse package written by Timothy A. Davis.
 * It has been extensively modified for compliance with ADMB.
 *
 * License: LGPL
 */

#include <fvar.hpp>
//#include <admodel.h>
//#include <df1b2fun.h>
//#include <adrndeff.h>
#define XCONST const
#include "hs.h"
//pthread_mutex_t mutex_dfpool = PTHREAD_MUTEX_INITIALIZER;

#define USE_ADJOINT_CODE
void report_derivatives(const dvar_vector& x);

static void xxx(int i){;}
static void xxx(ivector& i){;}
static void xxxv(ivector& x)
{
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    switch (x(i))
    {
      case 0:
        cout << "not used" << endl;
        break;
      case 1:
        xxx(x);
        break;
      default:
        xxx(x);
        break;
    }
  }
}
//int varchol(XCONST dvar_hs_smatrix &A, XCONST hs_symbolic &S,
//dvar_hs_smatrix &L, laplace_approximation_calculator * );
int varchol(XCONST dvar_hs_smatrix &A, XCONST hs_symbolic &S,
  dvar_hs_smatrix &L, dcompressed_triplet & sparse_triplet2);

int tmpxchol(XCONST hs_smatrix &A, XCONST hs_symbolic &S, hs_smatrix &L,
  ivector & xcount);

hs_smatrix cs_multiply(const hs_smatrix &A, const hs_smatrix  &B);
int cholnew(XCONST hs_smatrix &A, XCONST hs_symbolic &S, hs_smatrix &L);

// Utility function: p [0..n] = cumulative sum of c [0..n-1],
// and then copy p [0..n-1] into c
 double cs_cumsum (ivector &p, ivector &c, int n)
{
   int i, nz = 0 ;
    double nz2 = 0 ;
    for (i = 0 ; i < n ; i++)
    {
        p [i] = nz ;
        nz += c [i] ;
        nz2 += c [i] ;// also in double to avoid int overflow
        c [i] = p [i] ;// also copy p[0..n-1] back into c[0..n-1]
    }
    p [n] = nz ;
    return (nz2) ;                    // return sum (c [0..n-1])
}

// clear w
 int cs_wclear (int mark, int lemax, ivector &w, int n)
{
    int k ;
    if (mark < 2 || (mark + lemax < 0))
    {
        for (k = 0 ; k < n ; k++) if (w [k] != 0) w [k] = 1 ;
        mark = 2 ;
    }
    return (mark) ;        // at this point, w [0..n-1] < mark holds
}

// Find C = A'
 void cs_transpose (XCONST hs_smatrix &_A, int values, hs_smatrix &C)
{
    ADUNCONST(hs_smatrix,A)
    int p, q, j;

    int n = A.n ;
    int m = n;
    ivector & Ap=A.p;
    ivector & Ai=A.i;
    dvector & Ax=A.x;

    ivector & Cp=C.p;
    ivector & Ci=C.i;
    dvector & Cx=C.x;

    ivector w(0,n-1);                                      // workspace
    w.initialize();

    for (p = 0 ; p < Ap [n] ; p++)
      w [Ai [p]]++ ;                                          // row counts
    cs_cumsum (Cp, w, m) ;                              // row pointers
    for (j = 0 ; j < n ; j++)
    {
        for (p = Ap [j] ; p < Ap [j+1] ; p++)
        {
          Ci [q = w [Ai [p]]++] = j ; // place A(i,j) as entry C(j,i)
          Cx [q] = Ax [p] ;
        }
    }
    return;
}

 void cs_transpose (XCONST dvar_hs_smatrix &_A, int values, dvar_hs_smatrix &C)
{
    ADUNCONST(dvar_hs_smatrix,A)
    int p, q, j;

    int n = A.n ;
    int m = n;
    ivector & Ap=A.p;
    ivector & Ai=A.i;
    dvar_vector & Ax=A.x;

    ivector & Cp=C.p;
    ivector & Ci=C.i;
    dvar_vector & Cx=C.x;

    ivector w(0,n-1);                                      // workspace
    w.initialize();

    for (p = 0 ; p < Ap [n] ; p++)
      w [Ai [p]]++ ;                                          // row counts
    cs_cumsum (Cp, w, m) ;                              // row pointers
    for (j = 0 ; j < n ; j++)
    {
        for (p = Ap [j] ; p < Ap [j+1] ; p++)
        {
          Ci [q = w [Ai [p]]++] = j ; // place A(i,j) as entry C(j,i)
          Cx [q] = Ax [p] ;
        }
    }
    return;
}


//Sparse matrix XCONSTructor (compressed format) from dmatrix in triplet format
dmatrix make_dmatrix(dcompressed_triplet& M,int n,int m)
{
  dmatrix tmp(1,n,1,m);
  tmp.initialize();
  int nz = M.indexmax()- M.indexmin() + 1;
  for (int i=1;i<=nz;i++)
  {
    tmp(M(1,i),M(2,i))=M(i);
    if (M(1,i) != M(2,i))
    {
      tmp(M(2,i),M(1,i))=M(i);
    }
  }
  return tmp;
}

dvar_matrix make_sdvar_matrix(dvar_compressed_triplet& M)
{
  int n=M.get_n();
  int m=M.get_m();
  dvar_matrix tmp(1,n,1,m);
  tmp.initialize();
  int nz = M.indexmax()- M.indexmin() + 1;
  for (int i=1;i<=nz;i++)
  {
    tmp(M(1,i),M(2,i))=M(i);
    if (M(1,i) != M(2,i))
    {
      tmp(M(2,i),M(1,i))=M(i);
    }
  }
  return tmp;
}

dvar_matrix make_dvar_matrix(dvar_compressed_triplet& M)
{
  int n=M.get_n();
  int m=M.get_m();
  dvar_matrix tmp(1,n,1,m);
  tmp.initialize();
  int nz = M.indexmax()- M.indexmin() + 1;
  for (int i=1;i<=nz;i++)
  {
    tmp(M(1,i),M(2,i))=M(i);
  }
  return tmp;
}


dmatrix make_dmatrix(dcompressed_triplet& M)
{
  int n=M.get_n();
  int m=M.get_m();
  dmatrix tmp(1,n,1,m);
  tmp.initialize();
  int nz = M.indexmax()- M.indexmin() + 1;
  for (int i=1;i<=nz;i++)
  {
    tmp(M(1,i),M(2,i))=M(i);
  }
  return tmp;
}

dmatrix make_sdmatrix(dcompressed_triplet& M)
{
  int n=M.get_n();
  int m=M.get_m();
  dmatrix tmp(1,n,1,m);
  tmp.initialize();
  int nz = M.indexmax()- M.indexmin() + 1;
  for (int i=1;i<=nz;i++)
  {
    tmp(M(1,i),M(2,i))=M(i);
    if (M(1,i) != M(2,i))
    {
      tmp(M(2,i),M(1,i))=M(i);
    }
  }
  return tmp;
}

dvar_matrix make_dvar_matrix(dvar_compressed_triplet& M,int n,int m)
{
  dvar_matrix tmp(1,n,1,m);
  int nz = M.indexmax()- M.indexmin() + 1;
  for (int i=1;i<=nz;i++)
  {
    tmp(M(1,i),M(2,i))=M(i);
    if (M(1,i) != M(2,i))
    {
      tmp(M(2,i),M(1,i))=M(i);
    }
  }
  return tmp;
}


hs_smatrix::hs_smatrix(int _n, XCONST dcompressed_triplet &_M)
{
    ADUNCONST(dcompressed_triplet,M)

    n = _n;
    m = n;                // May remove m from code; only square matrices needed

    int nz = M.indexmax()- M.indexmin() + 1;
    nzmax = nz;

    int k;

    // Matrix in triplet format
    ivector Ti(1,nz);
    ivector tmp=(M.get_coords())(1);
    Ti=tmp-1;
    Ti.shift(0);


    ivector Tj(1,nz);
    ivector tmp1=(M.get_coords())(2);
    Tj=tmp1-1;
    Tj.shift(0);

    dvector Tx(1,nz);
    Tx = M.get_x();
    Tx.shift(0);

    if( min(Ti)<0 || max(Ti)>(n-1) || max(Tj)>(n-1) || min(Tj)<0)
      cout << "Error #2 in hs_smatrix::hs_smatrix" << endl;

    int lower_tri=0;
    for (k = 0 ; k < nz ; k++)
      lower_tri += Ti[k]>Tj[k];
    if(lower_tri)
      cout << "hs_smatrix::hs_smatrix: M must be upper triangular" << endl;

    // Matrix in compressed format
    p.allocate(0,n);
    p = 0;
    i.allocate(0,nzmax-1);
    x.allocate(0,nzmax-1);
    ivector & Cp=p;
    ivector & Ci=i;
    dvector & Cx=x;

    ivector w(0,n-1);                                        // get workspace
    w.initialize();

    // Does the compression
    int P;                                                // Originally p
    for (k = 0 ; k < nz ; k++) w [Tj [k]]++ ;                // column counts
    cs_cumsum(Cp, w, n) ;                                // column pointers
    for (k = 0 ; k < nz ; k++)
    {
        P = w [Tj [k]]++;
        Ci [P] = Ti [k] ;
        Cx [P] = Tx [k] ;
    }
}

hs_smatrix::hs_smatrix(const dcompressed_triplet &_M)
{
    ADUNCONST(dcompressed_triplet,M)

    m = M.get_n();
    n = M.get_m();

    int nz = M.indexmax()- M.indexmin() + 1;
    nzmax = nz;

    int k;

    // Matrix in triplet format
    ivector Ti(1,nz);
    ivector tmp=(M.get_coords())(1);
    Ti=tmp-1;
    Ti.shift(0);


    ivector Tj(1,nz);
    ivector tmp1=(M.get_coords())(2);
    Tj=tmp1-1;
    Tj.shift(0);

    dvector Tx(1,nz);
    Tx = M.get_x();
    Tx.shift(0);

    if( min(Ti)<0 || max(Ti)>(n-1) || max(Tj)>(m-1) || min(Tj)<0)
      cout << "Error #2 in hs_smatrix::hs_smatrix" << endl;

    int lower_tri=0;
    for (k = 0 ; k < nz ; k++)
      lower_tri += Ti[k]>Tj[k];
    if(lower_tri)
      cout << "hs_smatrix::hs_smatrix: M must be upper triangular" << endl;

    // Matrix in compressed format
    p.allocate(0,n);
    p = 0;
    i.allocate(0,nzmax-1);
    x.allocate(0,nzmax-1);
    ivector & Cp=p;
    ivector & Ci=i;
    dvector & Cx=x;

    ivector w(0,m-1);                                        // get workspace
    w.initialize();

    // Does the compression
    int P;                                                // Originally p
    for (k = 0 ; k < nz ; k++) w [Tj [k]]++ ;                // column counts
    cs_cumsum(Cp, w, n) ;                                // column pointers
    for (k = 0 ; k < nz ; k++)
    {
        P = w [Tj [k]]++;
        Ci [P] = Ti [k];
        Cx [P] = Tx [k] ;
    }
}

dvar_hs_smatrix::dvar_hs_smatrix(int _n, XCONST dvar_compressed_triplet &_M)
{
    ADUNCONST(dvar_compressed_triplet,M)
    n = _n;
    m = n;                // May remove m from code; only square matrices needed

    int nz = M.indexmax()- M.indexmin() + 1;
    nzmax = nz;

    int k;

    // Matrix in triplet format
    ivector Ti(1,nz);
    ivector tmp=(M.get_coords())(1);
    Ti=tmp-1;
    Ti.shift(0);


    ivector Tj(1,nz);
    ivector tmp1=(M.get_coords())(2);
    Tj=tmp1-1;
    Tj.shift(0);

    dvar_vector Tx(1,nz);
    Tx = M.get_x();
    Tx.shift(0);

    if( min(Ti)<0 || max(Ti)>(n-1) || max(Tj)>(n-1) || min(Tj)<0)
      cout << "Error #2 in dvar_hs_smatrix::dvar_hs_smatrix" << endl;

    int lower_tri=0;
    for (k = 0 ; k < nz ; k++)
      lower_tri += Ti[k]>Tj[k];
    if(lower_tri)
      cout << "dvar_hs_smatrix::dvar_hs_smatrix: M must be upper triangular"
           << endl;

    // Matrix in compressed format
    p.allocate(0,n);
    p = 0;
    i.allocate(0,nzmax-1);
    x.allocate(0,nzmax-1);
    ivector & Cp=p;
    ivector & Ci=i;
    dvar_vector & Cx=x;

    ivector w(0,n-1);                                        // get workspace
    w.initialize();

    // Does the compression
    int P;                                                // Originally p
    for (k = 0 ; k < nz ; k++) w [Tj [k]]++ ;                // column counts
    cs_cumsum(Cp, w, n) ;                                // column pointers
    for (k = 0 ; k < nz ; k++)
    {
        P = w [Tj [k]]++;
        Ci [P] = Ti [k];
        Cx [P] = Tx [k] ;
    }
}

hs_smatrix::hs_smatrix(int _n, int _nzmax)
{
    nzmax = _nzmax;
    n = _n;
    m = _n;               // May get rid of m later; only square matrices needed

    p.allocate(0,n);
    p = 0;
    i.allocate(0,nzmax-1);
    i = 0;
    x.allocate(0,nzmax-1);
    x = 0.0;
}

dvar_hs_smatrix::dvar_hs_smatrix(int _n, int _nzmax)
{
    nzmax = _nzmax;
    n = _n;
    m = _n;               // May get rid of m later; only square matrices needed

    p.allocate(0,n);
    p = 0;
    i.allocate(0,nzmax-1);
    i = 0;
    x.allocate(0,nzmax-1);
    x = 0.0;
}

// Convert cs to hs_smatrix
hs_smatrix::hs_smatrix(XCONST cs *A)
{
  int j;
    nzmax = A->nzmax;
    n = A->n;
    m = n;

    p.allocate(0,n);
    for (j = 0 ; j <= n ; j++)
      p[j] = A->p[j];

    i.allocate(0,nzmax-1);
    for (j = 0 ; j < nzmax ; j++)
      i[j] = A->i[j];

    x.allocate(0,nzmax-1);
    for (j = 0 ; j < nzmax ; j++)
      x[j] = A->x[j];
}

// Extends nzmax; new entries initialized to zero
void hs_smatrix::reallocate(int _nzmax)
{
    ivector tmp(0,nzmax-1);
    tmp=i;
    i.deallocate();
    i.allocate(0,_nzmax-1);
    i(nzmax,_nzmax-1) = 0;
    i(0,nzmax-1) = tmp;

    dvector tmpx(0,nzmax-1);
    tmpx=x;
    x.deallocate();
    x.allocate(0,_nzmax-1);
    x(nzmax,_nzmax-1) = 0.0;
    x(0,nzmax-1) = tmpx;

    nzmax = _nzmax;
}

void dvar_hs_smatrix::reallocate(int _nzmax)
{
    ivector tmp(0,nzmax-1);
    tmp=i;
    i.deallocate();
    i.allocate(0,_nzmax-1);
    i(nzmax,_nzmax-1) = 0;
    i(0,nzmax-1) = tmp;

    dvar_vector tmpx(0,nzmax-1);
    tmpx=x;
    x.deallocate();
    x.allocate(0,_nzmax-1);
    x(nzmax,_nzmax-1) = 0.0;
    x(0,nzmax-1) = tmpx;

    nzmax = _nzmax;
}

dvar_hs_smatrix::dvar_hs_smatrix(XCONST dvar_hs_smatrix &A)
{
    nzmax = A.nzmax;
    n = A.n;
    m = n;                // May get rid of m later; only square matrices needed

    p.allocate(0,n);
    i.allocate(0,nzmax-1);
    x.allocate(0,nzmax-1);
    p = A.p;
    i = A.i;
    x = A.x;
}

hs_smatrix::hs_smatrix(XCONST hs_smatrix &A)
{
    nzmax = A.nzmax;
    n = A.n;
    m = n;                // May get rid of m later; only square matrices needed

    p.allocate(0,n);
    i.allocate(0,nzmax-1);
    x.allocate(0,nzmax-1);
    p = A.p;
    i = A.i;
    x = A.x;
}

hs_smatrix& hs_smatrix::operator=(XCONST hs_smatrix &A)
{
    if((n != A.n)||(nzmax != A.nzmax))
      cout << "hs_smatrix&: lhs and rhs dimensions differ" << endl;
    else
    {
      p = A.p;
      i = A.i;
      x = A.x;
    }

    return *this;
}

dvar_hs_smatrix& dvar_hs_smatrix::operator=(XCONST dvar_hs_smatrix &A)
{
    if((n != A.n)||(nzmax != A.nzmax))
      cout << "dvar_hs_smatrix&: lhs and rhs dimensions differ" << endl;
    else
    {
      p = A.p;
      i = A.i;
      x = A.x;
    }

    return *this;
}

// Allocate Cholesky factor
hs_smatrix::hs_smatrix(XCONST hs_symbolic &S)
{
    nzmax = S.cp[S.n];
    n = S.n;
    m = n;

    p.allocate(0,n);
    i.allocate(0,nzmax-1);
    x.allocate(0,nzmax-1);
}

dvar_hs_smatrix::dvar_hs_smatrix(XCONST hs_symbolic &S)
{
    nzmax = S.cp[S.n];
    n = S.n;
    m = n;

    p.allocate(0,n);
    i.allocate(0,nzmax-1);
    x.allocate(0,nzmax-1);
}

// For determinant calculations: sum(log(diag(L)).
double hs_smatrix::trace_log(int & sgn)
{
  sgn=0;
  double ret = 0.0;
  for (int j = 0 ; j < n ; j++)
  {
    for (int k = p [j] ; k < p [j+1] ; k++)
    {
      if(j==i[k])
      {
        //cout << " k = "  << k << "  x[k] = " << x[k] << endl;
        if(x[k]>0.0)
          ret += log(x[k]);
        else if (x[k]<0.0)
        {
          ret += log(-x[k]);
          sgn++;
        }
          else
        {
              cerr << "!!!! trace_log: zero diagonal element " << endl;
          sgn=-1;
          break;
        }
      }
      if (sgn==-1) break;
    }
    if (sgn==-1) break;
  }
  sgn=sgn%2;
  return(ret);
}

dvariable dvar_hs_smatrix::trace_log(int & sgn)
{
  sgn=0;
  dvariable ret = 0.0;
  for (int j = 0 ; j < n ; j++)
  {
    for (int k = p [j] ; k < p [j+1] ; k++)
    {
      if(j==i[k])
      {
        //cout << " k = "  << k << "  x[k] = " << x[k] << endl;
        if(x[k]>0.0)
          ret += log(x[k]);
        else if (x[k]<0.0)
        {
          ret += log(-x[k]);
          sgn++;
        }
          else
        {
              cerr << "!!!! trace_log: zero diagonal element " << endl;
          sgn=-1;
          break;
        }
      }
      if (sgn==-1) break;
    }
    if (sgn==-1) break;
  }
  sgn=sgn%2;
  return(ret);
}
dvariable ln_det(XCONST dvar_hs_smatrix& M)
{
  int sgn;
  return ln_det(M,sgn);
}


dvariable ln_det(XCONST dvar_hs_smatrix& _M,int & sgn)
{
  ADUNCONST(dvar_hs_smatrix,M)
  return M.trace_log(sgn);
}

double ln_det(XCONST hs_smatrix& _M)
{
  ADUNCONST(hs_smatrix,M)
  int sgn;
  return M.trace_log(sgn);
}
double ln_det(XCONST hs_smatrix& _M,int & sgn)
{
  ADUNCONST(hs_smatrix,M)
  return M.trace_log(sgn);
}

int hs_smatrix::print()
{
    cout << "Sparse matrix in compressed form (i,x):" << endl;
    for (int j = 0 ; j < n ; j++)
    {
      cout << "    col " << j << " : locations " << p[j] << " to " << p[j+1]-1
           <<  endl;
      for (int P = p [j] ; P < p [j+1] ; P++)
        cout << i [P] << " " << x [P] << endl;
    }
    return(0);
}

int hs_smatrix::print_pattern()
{
    cout << "Sparseness pattern:" << endl;
    for (int j = 0 ; j < n ; j++)
    {
      for (int k = 0 ; k < n ; k++)
      {
        int tmp=0;
        for (int kk = p[k] ; kk < p[k+1] ; kk++)
          tmp += (i[kk]==j);
        if(tmp)
          cout << "x";
        else
          cout << " ";
      }
      cout << endl;
    }
    return(0);
}

// Print matrix transpose with zeros
int hs_smatrix::print_trans_zeros()
{
    for(int k = 0 ; k < n ; k++)        // cols
    {
      int kk = p[k];
      for(int j = 0 ; j < n ; j++)        // rows
        if(i[kk]==j)
        {
          cout << x[kk] << "\t";
          kk++;
        }
        else
          cout << "0\t";
      cout << endl;
    }
    return(0);
}

// Find nonzero pattern of Cholesky L(k,1:k-1) using etree and triu(A(:,k))
int cs_ereach (XCONST hs_smatrix &_A, int k, XCONST ivector &parent, ivector &s,
  ivector &w)
{
    ADUNCONST(hs_smatrix,A)
    int i, p, n, len, top;

    n = A.n;
    top = n;

    ivector & Ap=A.p;
    ivector & Ai=A.i;

    CS_MARK (w, k) ;                    /* mark node k as visited */
    for (p = Ap [k] ; p < Ap [k+1] ; p++)
    {
        i = Ai [p] ;                    /* A(i,k) is nonzero */
        if (i > k) continue ;          /* only use upper triangular part of A */
        for (len = 0 ; !CS_MARKED (w,i) ; i = parent [i]) /* traverse up etree*/
        {
            s [len++] = i ;            /* L(k,i) is nonzero */
            CS_MARK (w, i) ;            /* mark i as visited */
        }
        while (len > 0) s [--top] = s [--len] ; /* push path onto stack */
    }
    for (p = top ; p < n ; p++) CS_MARK (w, s [p]) ;      /* unmark all nodes */
    CS_MARK (w, k) ;                    /* unmark node k */
    return (top) ;                  /* s [top..n-1] contains pattern of L(k,:)*/
}

int cs_ereach (XCONST dvar_hs_smatrix &_A, int k, XCONST ivector &parent,
  ivector &s, ivector &w)
{
    ADUNCONST(dvar_hs_smatrix,A)
    int i, p, n, len, top;

    n = A.n;
    top = n;

    ivector & Ap=A.p;
    ivector & Ai=A.i;

    CS_MARK (w, k) ;                    /* mark node k as visited */
    for (p = Ap [k] ; p < Ap [k+1] ; p++)
    {
        i = Ai [p] ;                    /* A(i,k) is nonzero */
        if (i > k) continue ;          /* only use upper triangular part of A */
        for (len = 0 ; !CS_MARKED (w,i) ; i = parent [i]) /* traverse up etree*/
        {
            s [len++] = i ;            /* L(k,i) is nonzero */
            CS_MARK (w, i) ;            /* mark i as visited */
        }
        while (len > 0) s [--top] = s [--len] ; /* push path onto stack */
    }
    for (p = top ; p < n ; p++) CS_MARK (w, s [p]) ;      /* unmark all nodes */
    CS_MARK (w, k) ;                    /* unmark node k */
    return (top) ;                  /* s [top..n-1] contains pattern of L(k,:)*/
}

/* C = A(p,p) where A and C are symmetric the upper part stored; pinv not p */
void hs_symperm(XCONST hs_smatrix &_A, XCONST ivector &pinv, hs_smatrix &C)
{
    ADUNCONST(hs_smatrix,A)
    int i, j, p, q, i2, j2;

    int n = A.n ;
    ivector & Ap=A.p;
    ivector & Ai=A.i;
    dvector & Ax=A.x;
    ivector w(0,n-1);                        /* get workspace */
    w.initialize();
    ivector & Cp=C.p;
    ivector & Ci=C.i;
    dvector & Cx=C.x;

    for (j = 0 ; j < n ; j++)            /* count entries in each column of C */
    {
        j2 = (pinv[0]!=-1) ? pinv [j] : j ;/* column j of A is column j2 of C */
        for (p = Ap [j] ; p < Ap [j+1] ; p++)
        {
            i = Ai [p] ;
            if (i > j) continue ;        /* skip lower triangular part of A */
            i2 = (pinv[0]!=-1) ? pinv [i] : i ;  /* row i of A is row i2 of C */
            w [CS_MAX (i2, j2)]++ ;        /* column count of C */
        }
    }
    cs_cumsum (Cp, w, n) ;                /* compute column pointers of C */
    for (j = 0 ; j < n ; j++)
    {
        j2 = (pinv[0]!=-1) ? pinv [j] : j ;/* column j of A is column j2 of C */
        for (p = Ap [j] ; p < Ap [j+1] ; p++)
        {
            i = Ai [p] ;
            if (i > j) continue ;        /* skip lower triangular part of A*/
            i2 = (pinv[0]!=-1) ? pinv [i] : i ;  /* row i of A is row i2 of C */

            q = w [CS_MAX (i2, j2)]++;
            Ci [q] = CS_MIN (i2, j2) ;
            Cx [q] = Ax [p] ;
        }
    }
}
void hs_symperm(XCONST dvar_hs_smatrix &_A, XCONST ivector &pinv,
  dvar_hs_smatrix &C)
{
    ADUNCONST(dvar_hs_smatrix,A)
    int i, j, p, q, i2, j2;

    int n = A.n ;
    ivector & Ap=A.p;
    ivector & Ai=A.i;
    dvar_vector & Ax=A.x;
    ivector w(0,n-1);                        /* get workspace */
    w.initialize();
    ivector & Cp=C.p;
    ivector & Ci=C.i;
    dvar_vector & Cx=C.x;

    for (j = 0 ; j < n ; j++)            /* count entries in each column of C */
    {
        j2 = (pinv[0]!=-1) ? pinv [j] : j ;/* column j of A is column j2 of C */
        for (p = Ap [j] ; p < Ap [j+1] ; p++)
        {
            i = Ai [p] ;
            if (i > j) continue ;        /* skip lower triangular part of A */
            i2 = (pinv[0]!=-1) ? pinv [i] : i ;  /* row i of A is row i2 of C */
            w [CS_MAX (i2, j2)]++ ;        /* column count of C */
        }
    }
    cs_cumsum (Cp, w, n) ;                /* compute column pointers of C */
    for (j = 0 ; j < n ; j++)
    {
        j2 = (pinv[0]!=-1) ? pinv [j] : j ;/* column j of A is column j2 of C */
        for (p = Ap [j] ; p < Ap [j+1] ; p++)
        {
            i = Ai [p] ;
            if (i > j) continue ;        /* skip lower triangular part of A*/
            i2 = (pinv[0]!=-1) ? pinv [i] : i ;  /* row i of A is row i2 of C */

            q = w [CS_MAX (i2, j2)]++;
            Ci [q] = CS_MIN (i2, j2) ;
            Cx [q] = Ax [p] ;
        }
    }
}

void myacc(int & p,int Lpi1,int ci,const ivector & Li,
  dvector & x,const dvector & Lx,const double & lki)
{
  for (p = Lpi1 ; p < ci ; p++)
  {
      x[Li[p]] -= Lx[p]*lki ;
  }
}

// Numeric Cholesky factorization (L is factor). Return 1 on success 0 otherwise
int chol(XCONST hs_smatrix& A,
         XCONST hs_symbolic& T,
         hs_smatrix& L)
{
    //ADUNCONST(hs_symbolic,S)
    hs_symbolic& S = (hs_symbolic&)T;
    double d, lki;
    int top, i, p, k, n;

    n = A.n ;

    ivector c(0,n-1);                              // int workspace
    ivector s(0,n-1);                                   // int workspace
    dvector x(0,n-1) ;                        // double workspace

    ivector & cp=S.cp;
    ivector & pinv=S.pinv;
    ivector & parent=S.parent;

    hs_smatrix C(A);
    C = A;
    if(S.pinv[0]!=-1)
      hs_symperm(A,pinv,C);

    ivector & Cp=C.p;
    ivector & Ci=C.i;
    dvector & Cx=C.x;

    ivector & Lp=L.p;
    ivector & Li=L.i;
    dvector & Lx=L.x;

    for (k = 0 ; k < n ; k++)
      Lp [k] = c [k] = cp [k] ;

    for (k = 0 ; k < n ; k++)            // compute L(:,k) for L*L' = C
    {
        // --- Nonzero pattern of L(k,:) ------------------------------------
        top = cs_ereach (C, k, parent, s, c) ;         // find pattern of L(k,:)
        x [k] = 0 ;                                    // x (0:k) is now zero
        for (p = Cp [k] ; p < Cp [k+1] ; p++)          // x = full(triu(C(:,k)))
        {
            if (Ci [p] <= k) x [Ci [p]] = Cx [p] ;
        }
        d = x [k] ;                        // d = C(k,k)
        x [k] = 0 ;                        // clear x for k+1st iteration
        // --- Triangular solve ---------------------------------------------
        for ( ; top < n ; top++)    // solve L(0:k-1,0:k-1) * x = C(:,k)
        {
            i = s [top] ;                // s [top..n-1] is pattern of L(k,:)
            lki = x [i] / Lx [Lp [i]] ; // L(k,i) = x (i) / L(i,i)
            x [i] = 0 ;                        // clear x for k+1st iteration


            int Lpi1=Lp[i]+1;
            int ci=c[i];
            for (p = Lpi1; p < ci ; p++)
            {
                x [Li [p]] -= Lx [p] * lki ;
            }

            d -= lki * lki ;                // d = d - L(k,i)*L(k,i)
            p = c [i]++ ;
            Li [p] = k ;                // store L(k,i) in column i
            Lx [p] = lki ;
        }
        // --- Compute L(k,k) -----------------------------------------------
        if (d <= 0) return (0) ; // not pos def
        p = c [k]++ ;
        Li [p] = k ;                    // store L(k,k) = sqrt (d) in column k
        Lx [p] = sqrt (d) ;
    }
    Lp [n] = cp [n] ;                    // finalize L
    return (1);
}
// Numeric Cholesky factorization (L is factor).
// Return 1 on success; 0 otherwise
int tmpxchol1(XCONST hs_smatrix &A, XCONST hs_symbolic& T, hs_smatrix &L,
  ivector & nxcount)
{
    //ADUNCONST(hs_symbolic,S)
    hs_symbolic& S = (hs_symbolic&)T;
    double d, lki;
    int top, i, p, k, n;

    n = A.n ;

    ivector c(0,n-1);                              /* int workspace */
    ivector s(0,n-1);                                   /* int workspace */
    //dvector x(0,n-1) ;                        /* double workspace */
    dmatrix x(0,n-1,1,nxcount) ;                        /* double workspace */

    ivector & cp=S.cp;
    ivector & pinv=S.pinv;
    ivector & parent=S.parent;

    hs_smatrix C(A);
    C = A;
    if(S.pinv[0]!=-1)
      hs_symperm(A,pinv,C);

    ivector & Cp=C.p;
    ivector & Ci=C.i;
    dvector & Cx=C.x;

    ivector & Lp=L.p;
    ivector & Li=L.i;
    dvector & Lx=L.x;

  // counters
    ivector Licount(Li.indexmin(),Li.indexmax());
    Licount.initialize();
    ivector Lxcount(Lx.indexmin(),Lx.indexmax());
    Lxcount.initialize();
    ivector xcount(x.indexmin(),x.indexmax());
    xcount.initialize();

    int dcount=0;
    int pcount=0;
    int icount=0;
    int lkicount=0;

    for (k = 0 ; k < n ; k++)
    {
      Lp [k] = c [k] = cp [k] ;
    }

    for (k = 0 ; k < n ; k++)            /* compute L(:,k) for L*L' = C */
    {
        /* --- Nonzero pattern of L(k,:) ------------------------------------ */
        top = cs_ereach (C, k, parent, s, c) ;      /* find pattern of L(k,:) */
        xcount[k]++;
        x (k,xcount(k)) = 0 ;                          /* x (0:k) is now zero */
        for (p = Cp [k] ; p < Cp [k+1] ; p++)       /* x = full(triu(C(:,k))) */
        {
          if (Ci [p] <= k)
          {
            xcount[Ci[p]]++;
            x(Ci[p],xcount(Ci[p])) = Cx[p] ;
          }
        }
        d = x(k,xcount[k]) ;                        /* d = C(k,k) */
        dcount++;
        xcount[k]++;
        x(k,xcount[k]) = 0 ;                   /* clear x for k+1st iteration */
        /* --- Triangular solve --------------------------------------------- */
        for ( ; top < n ; top++)    /* solve L(0:k-1,0:k-1) * x = C(:,k) */
        {
            i = s [top] ;                /* s [top..n-1] is pattern of L(k,:) */
            icount++;
            lki = x (i,xcount[i]) / Lx [Lp [i]] ; /* L(k,i) = x (i) / L(i,i) */
            lkicount++;
            xcount[i]++;
            x (i,xcount[i]) = 0.0 ;            /* clear x for k+1st iteration */
            for (p = Lp [i] + 1 ; p < c [i] ; p++)
            {
                x [Li [p]] -= Lx [p] * lki ;
            }
            d -= lki * lki ;                /* d = d - L(k,i)*L(k,i) */
            p = c [i]++ ;
            pcount++;
            Li [p] = k ;                /* store L(k,i) in column i */
            Licount[p]++;
            if (Licount(p)>1)
            {
              cerr << "Error unhandled case in chol" << endl;
            }
            Lx [p] = lki ;
            Lxcount[p]++;
            if (Lxcount(p)>1)
            {
              cerr << "Error unhandled case in chol" << endl;
              ad_exit(1);
            }
        }
        /* --- Compute L(k,k) ----------------------------------------------- */
        if (d <= 0) return (0) ; /* not pos def */
        p = c [k]++ ;
        pcount++;
        Li [p] = k ;                   /* store L(k,k) = sqrt (d) in column k */
        Licount[p]++;
        if (Licount(p)>1)
        {
          cerr << "Error unhandled case in chol" << endl;
        }
        Lx [p] = sqrt (d) ;
        Lxcount[p]++;
        if (Lxcount(p)>1)
        {
          cerr << "Error unhandled case in chol" << endl;
          ad_exit(1);
        }
    }
    Lp [n] = cp [n] ;                    /* finalize L */
    xxx(pcount);
    xxx(dcount);
    xxx(icount);
    xxx(lkicount);
    xxxv(Licount);
    xxxv(Lxcount);
    xxxv(xcount);
    return (1);
}

/* x(p) = b, for dense vectors x and b; p=NULL denotes identity */
 dvector cs_ipvec(XCONST ivector &p, XCONST dvector &b)
{
    if(p[0]==-1)                        // No permutation
      return(b);
    else
    {
      int n = p.indexmax()+1;
      dvector x(0,n-1);
      for (int k = 0 ; k < n ; k++)
        x [p [k]] = b [k] ;
      return (x) ;
    }
}

/* x = b(p), for dense vectors x and b; p=NULL denotes identity */
 dvector cs_pvec (XCONST ivector &p, XCONST dvector &b)
{
    if(p[0]==-1)                        // No permutation
      return(b);
    else
    {
      int n = p.indexmax()+1;
      dvector x(0,n-1);
      for (int k = 0 ; k < n ; k++)
        x[k] = b[p[k]];
      return (x) ;
    }
}

 dvar_vector cs_pvec (XCONST ivector &p, XCONST dvar_vector &b)
{
    if(p[0]==-1)                        // No permutation
      return(b);
    else
    {
      int n = p.indexmax()+1;
      dvar_vector x(0,n-1);
      for (int k = 0 ; k < n ; k++)
        x[k] = b[p[k]];
      return (x) ;
    }
}

/* solve Lx=b where x and b are dense.  x=b on input, solution on output. */
 dvector cs_lsolve (XCONST hs_smatrix & LL, XCONST dvector &y)
{
    //ADUNCONST(hs_smatrix,L)
    hs_smatrix& L = (hs_smatrix&)LL;
    int p, j, n;

    n = L.n;
    dvector x(0,n-1);
    x=y;

    ivector & Lp=L.p;
    ivector & Li=L.i;
    dvector & Lx=L.x;

    for (j = 0 ; j < n ; j++)
    {
        x [j] /= Lx [Lp [j]] ;
        for (p = Lp [j]+1 ; p < Lp [j+1] ; p++)
        {
            x [Li [p]] -= Lx [p] * x [j] ;
        }
    }
    return (x) ;
}

 dvar_vector cs_lsolve (XCONST dvar_hs_smatrix & LL, XCONST dvar_vector &y)
{
    //ADUNCONST(dvar_hs_smatrix,L)
    dvar_hs_smatrix& L = (dvar_hs_smatrix&)LL;
    int p, j, n;

    n = L.n;
    dvar_vector x(0,n-1);
    x=y;

    ivector & Lp=L.p;
    ivector & Li=L.i;
    dvar_vector & Lx=L.x;

    for (j = 0 ; j < n ; j++)
    {
        x [j] /= Lx [Lp [j]] ;
        for (p = Lp [j]+1 ; p < Lp [j+1] ; p++)
        {
            x [Li [p]] -= Lx [p] * x [j] ;
        }
    }
    return (x) ;
}

 dvar_vector cs_lsolve (XCONST dvar_hs_smatrix & LL, XCONST dvector &y)
{
    //ADUNCONST(dvar_hs_smatrix,L)
    dvar_hs_smatrix& L = (dvar_hs_smatrix&)LL;
    int p, j, n;

    n = L.n;
    dvar_vector x(0,n-1);
    x=y;

    ivector & Lp=L.p;
    ivector & Li=L.i;
    dvar_vector & Lx=L.x;

    for (j = 0 ; j < n ; j++)
    {
        x [j] /= Lx [Lp [j]] ;
        for (p = Lp [j]+1 ; p < Lp [j+1] ; p++)
        {
            x [Li [p]] -= Lx [p] * x [j] ;
        }
    }
    return (x) ;
}

/* solve L'x=b where x and b are dense.  x=b on input, solution on output. */
 dvector cs_ltsolve (XCONST hs_smatrix &LL, XCONST dvector &y)
{
    //ADUNCONST(hs_smatrix,L)
    hs_smatrix& L = (hs_smatrix&)LL;
    int p, j, n;

    n = L.n;
    dvector x(0,n-1);
    x=y;
    ivector & Lp=L.p;
    ivector & Li=L.i;
    dvector & Lx=L.x;

    for (j = n-1 ; j >= 0 ; j--)
    {
        for (p = Lp [j]+1 ; p < Lp [j+1] ; p++)
        {
            x [j] -= Lx [p] * x [Li [p]] ;
        }
        x [j] /= Lx [Lp [j]] ;
    }
    return (x) ;
}

 dvar_vector cs_ltsolve (XCONST dvar_hs_smatrix &LL, XCONST dvar_vector &y)
{
    //ADUNCONST(dvar_hs_smatrix,L)
    dvar_hs_smatrix& L = (dvar_hs_smatrix&)LL;
    int p, j, n;

    n = L.n;
    dvar_vector x(0,n-1);
    x=y;
    ivector & Lp=L.p;
    ivector & Li=L.i;
    dvar_vector & Lx=L.x;

    for (j = n-1 ; j >= 0 ; j--)
    {
        for (p = Lp [j]+1 ; p < Lp [j+1] ; p++)
        {
            x [j] -= Lx [p] * x [Li [p]] ;
        }
        x [j] /= Lx [Lp [j]] ;
    }
    return (x) ;
}

// keep off-diagonal entries; drop diagonal entries
 int cs_diag(int i, int j, double aij, void *other) { return (i != j) ; }
int cs_diag(int i, int j, const prevariable& aij, void *other)
  { return (i != j) ; }

/* drop entries for which fkeep(A(i,j)) is false; return nz if OK, else -1 */
int cs_fkeep (hs_smatrix &A, int (*fkeep) (int, int, double, void *),
  void *other)
{
    int j, p, nz = 0 ;

    int n = A.n ;
    ivector & Ap=A.p;
    ivector & Ai=A.i;
    dvector & Ax=A.x;

    for (j = 0 ; j < n ; j++)
    {
        p = Ap [j] ;                        /* get current location of col j */
        Ap [j] = nz ;                       /* record new location of col j */
        for ( ; p < Ap [j+1] ; p++)
        {
            if (fkeep (Ai [p], j, Ax [p], other))
            {
                Ax [nz] = Ax [p] ;  /* keep A(i,j) */
                Ai [nz++] = Ai [p] ;
            }
        }
    }
    Ap [n] = nz ;                           /* finalize A */
    return (nz) ;
}

int cs_fkeep (dvar_hs_smatrix &A, int (*fkeep) (int, int, const prevariable&,
  void *), void *other)
{
    int j, p, nz = 0 ;

    int n = A.n ;
    ivector & Ap=A.p;
    ivector & Ai=A.i;
    dvar_vector & Ax=A.x;

    for (j = 0 ; j < n ; j++)
    {
        p = Ap [j] ;                        /* get current location of col j */
        Ap [j] = nz ;                       /* record new location of col j */
        for ( ; p < Ap [j+1] ; p++)
        {
            if (fkeep (Ai [p], j, Ax [p], other))
            {
                Ax [nz] = Ax [p] ;  /* keep A(i,j) */
                Ai [nz++] = Ai [p] ;
            }
        }
    }
    Ap [n] = nz ;                           /* finalize A */
    return (nz) ;
}

/* x = x + beta * A(:,j), where x is a dense vector and A(:,j) is sparse */
int cs_scatter(XCONST hs_smatrix &AA, int j, double beta, ivector &w,
  dvector &x, int mark, hs_smatrix &C, int nz)
{
    //ADUNCONST(hs_smatrix,A)
    hs_smatrix& A = (hs_smatrix&)AA;
    int i, p;
    ivector & Ap=A.p;
    ivector & Ai=A.i;
    dvector & Ax=A.x;
    ivector & Ci=C.i;
    for (p = Ap [j] ; p < Ap [j+1] ; p++)
    {
        i = Ai [p] ;                            /* A(i,j) is nonzero */
        if (w [i] < mark)
        {
            w [i] = mark ;                      /* i is new entry in column j */
            Ci [nz++] = i ;                     /* add i to pattern of C(:,j) */
            x [i] = beta * Ax [p] ;      /* x(i) = beta*A(i,j) */
        }
        else x [i] += beta * Ax [p] ;    /* i exists in C(:,j) already */
    }
    return (nz) ;
}

 //int cs_scatter(XCONST hs_smatrix &A, int j, double beta, ivector &w,
 //  dvector &x, int mark, hs_smatrix &C, int nz)
 //{
 //    int i, p;
 //    ivector & Ap=A.p;
 //    ivector & Ai=A.i;
 //    dvector & Ax=A.x;
 //    ivector & Ci=C.i;
 //    for (p = Ap [j] ; p < Ap [j+1] ; p++)
 //    {
 //        i = Ai [p] ;                            /* A(i,j) is nonzero */
 //        if (w [i] < mark)
 //        {
 //            w [i] = mark ;                   /* i is new entry in column j */
 //            Ci [nz++] = i ;                  /* add i to pattern of C(:,j) */
 //            x [i] = beta * Ax [p] ;      /* x(i) = beta*A(i,j) */
 //        }
 //        else x [i] += beta * Ax [p] ;    /* i exists in C(:,j) already */
 //    }
 //    return (nz) ;
 //}

int cs_scatter(XCONST dvar_hs_smatrix &AA, int j, double beta, ivector &w,
  dvar_vector &x, int mark, dvar_hs_smatrix &C, int nz)
{
    //ADUNCONST(dvar_hs_smatrix,A)
    dvar_hs_smatrix& A = (dvar_hs_smatrix&)AA;
    int i, p;
    ivector & Ap=A.p;
    ivector & Ai=A.i;
    dvar_vector & Ax=A.x;
    ivector & Ci=C.i;
    for (p = Ap [j] ; p < Ap [j+1] ; p++)
    {
        i = Ai [p] ;                            /* A(i,j) is nonzero */
        if (w [i] < mark)
        {
            w [i] = mark ;                      /* i is new entry in column j */
            Ci [nz++] = i ;                     /* add i to pattern of C(:,j) */
            x [i] = beta * Ax [p] ;      /* x(i) = beta*A(i,j) */
        }
        else x [i] += beta * Ax [p] ;    /* i exists in C(:,j) already */
    }
    return (nz) ;
}

/* C = alpha*A + beta*B */
hs_smatrix cs_add(XCONST hs_smatrix &AA, XCONST hs_smatrix &BB, double alpha,
  double beta)
{
    //ADUNCONST(hs_smatrix,A)
    //ADUNCONST(hs_smatrix,B)
    hs_smatrix& A = (hs_smatrix&)AA;
    hs_smatrix& B = (hs_smatrix&)BB;
    int p, j, nz = 0, anz,m, n, bnz;

    if (A.m != B.m || A.n != B.n)
    {
       cout << "!!!! Error in cs_add: A.m != B.m || A.n != B.n" << endl;
       exit(0);
    }

    m = A.m ; anz = A.p [A.n] ;
    n = B.n ;

    ivector & Bp=B.p;
    bnz = Bp [n] ;
    ivector w(0,m-1);                                             // Workspace
    w.initialize();

    // Always assumes values == 1
    dvector x(0,m-1);                                             // Workspace
    x.initialize();

    hs_smatrix C(n,anz + bnz);
    ivector & Cp=C.p;
    ivector & Ci=C.i;
    dvector & Cx=C.x;

    for (j = 0 ; j < n ; j++)
    {
        Cp [j] = nz ;                   /* column j of C starts here */
        nz = cs_scatter (A, j, alpha, w, x, j+1, C, nz) ;   /* alpha*A(:,j)*/
        nz = cs_scatter (B, j, beta, w, x, j+1, C, nz) ;    /* beta*B(:,j) */
        for (p = Cp [j] ; p < nz ; p++)
          Cx [p] = x [Ci [p]] ;
    }
    Cp [n] = nz ;                       /* finalize the last column of C */
    //cs_sprealloc (C, 0) ;               Ignoring this. Must be picked up
    return (C) ;
}

dvar_hs_smatrix cs_add(XCONST dvar_hs_smatrix &AA, XCONST dvar_hs_smatrix &BB,
  double alpha, double beta)
{
    //ADUNCONST(dvar_hs_smatrix,A)
    //ADUNCONST(dvar_hs_smatrix,B)
    dvar_hs_smatrix& A = (dvar_hs_smatrix&)AA;
    dvar_hs_smatrix& B = (dvar_hs_smatrix&)BB;
    int p, j, nz = 0, anz,m, n, bnz;

    if (A.m != B.m || A.n != B.n)
    {
       cout << "!!!! Error in cs_add: A.m != B.m || A.n != B.n" << endl;
       exit(0);
    }

    m = A.m ; anz = A.p [A.n] ;
    n = B.n ;

    ivector & Bp=B.p;
    bnz = Bp [n] ;
    ivector w(0,m-1);                                             // Workspace
    w.initialize();

    // Always assumes values == 1
    dvar_vector x(0,m-1);                                           // Workspace
    x.initialize();

    dvar_hs_smatrix C(n,anz + bnz);
    ivector & Cp=C.p;
    ivector & Ci=C.i;
    dvar_vector & Cx=C.x;

    for (j = 0 ; j < n ; j++)
    {
        Cp [j] = nz ;                   /* column j of C starts here */
        nz = cs_scatter (A, j, alpha, w, x, j+1, C, nz) ;   /* alpha*A(:,j)*/
        nz = cs_scatter (B, j, beta, w, x, j+1, C, nz) ;    /* beta*B(:,j) */
        for (p = Cp [j] ; p < nz ; p++)
          Cx [p] = x [Ci [p]] ;
    }
    Cp [n] = nz ;                       /* finalize the last column of C */
    //cs_sprealloc (C, 0) ;               Ignoring this. Must be picked up
    return (C) ;
}

/* depth-first search and postorder of a tree rooted at node j */
int cs_tdfs (int j, int k, ivector &head, XCONST ivector &next, ivector &post,
  ivector &stack)
{
    int i, p, top = 0 ;
    stack [0] = j ;                 /* place j on the stack */
    while (top >= 0)                /* while (stack is not empty) */
    {
        p = stack [top] ;           /* p = top of stack */
        i = head [p] ;              /* i = youngest child of p */
        if (i == -1)
        {
            top-- ;                 /* p has no unordered children left */
            post [k++] = p ;        /* node p is the kth postordered node */
        }
        else
        {
            head [p] = next [i] ;   /* remove i from children of p */
            stack [++top] = i ;     /* start dfs on child node i */
        }
    }
    return (k) ;
}

/**
p = amd(A+A') if symmetric is true, or amd(A'A) otherwise
\todo Need test case.
*/
ivector cs_amd (XCONST hs_smatrix &A)  /* Implements only order == 1: Chol*/
{
    int d, dk, dext, lemax = 0, e, elenk, eln, i, j, k, k1,
        k2, k3, jlast, ln, dense, nzmax, mindeg = 0, nvi, nvj, nvk, mark, wnvi,
        ok, cnz, nel = 0, p, p1, p2, p3, p4, pj, pk, pk1, pk2, pn, q, t ;
    unsigned int h ;
    /* --- Construct matrix C ----------------------------------------------- */

    int n = A.n ;

    hs_smatrix AT(n,A.nzmax);
    cs_transpose(A,0,AT);

    /* find dense threshold */
    dense = CS_MAX (16, (int)(10.0 * sqrt((double)n)));
    dense = CS_MIN (n-2, dense) ;

    hs_smatrix C = cs_add(A,AT);
    cs_fkeep (C, &cs_diag, NULL);        // drop diagonal entries
    cnz = C.p [n] ;
    ivector P(0,n);

    t = cnz + cnz/5 + 2*n ;                    // add elbow room to C
    C.reallocate(t);
    ivector & Cp=C.p;

    ivector len(0,n);
    len.initialize();
    ivector nv(0,n);
    ivector next(0,n);
    ivector head(0,n);
    head.initialize();
    ivector elen(0,n);
    ivector degree(0,n);
    ivector w(0,n);
    ivector hhead(0,n);
    ivector &last = P ;                        /* use P as workspace for last */

    /* --- Initialize quotient graph ---------------------------------------- */
    for (k = 0 ; k < n ; k++) len [k] = Cp [k+1] - Cp [k] ;
    len [n] = 0 ;
    nzmax = C.nzmax ;
    ivector & Ci=C.i;
    for (i = 0 ; i <= n ; i++)
    {
        head [i] = -1 ;                            /* degree list i is empty */
        last [i] = -1 ;
        next [i] = -1 ;
        hhead [i] = -1 ;                    /* hash list i is empty */
        nv [i] = 1 ;                            /* node i is just one node */
        w [i] = 1 ;                            /* node i is alive */
        elen [i] = 0 ;                            /* Ek of node i is empty */
        degree [i] = len [i] ;                    /* degree of node i */
    }
    mark = cs_wclear (0, 0, w, n) ;            /* clear w */
    elen [n] = -2 ;                            /* n is a dead element */
    Cp [n] = -1 ;                            /* n is a root of assembly tree */
    w [n] = 0 ;                                    /* n is a dead element */
    /* --- Initialize degree lists ------------------------------------------ */
    for (i = 0 ; i < n ; i++)
    {
        d = degree [i] ;
        if (d == 0)                            /* node i is empty */
        {
            elen [i] = -2 ;                    /* element i is dead */
            nel++ ;
            Cp [i] = -1 ;                    /* i is a root of assembly tree */
            w [i] = 0 ;
        }
        else if (d > dense)                    /* node i is dense */
        {
            nv [i] = 0 ;                    /* absorb i into element n */
            elen [i] = -1 ;                    /* node i is dead */
            nel++ ;
            Cp [i] = CS_FLIP (n) ;
            nv [n]++ ;
        }
        else
        {
            if (head [d] != -1) last [head [d]] = i ;
            next [i] = head [d] ;            /* put node i in degree list d */
            head [d] = i ;
        }
    }
    while (nel < n)                            /* while (selecting pivots) do */
    {
        /* --- Select node of minimum approximate degree -------------------- */
        for (k = -1 ; mindeg < n && (k = head [mindeg]) == -1 ; mindeg++) ;
        if (next [k] != -1) last [next [k]] = -1 ;
        head [mindeg] = next [k] ;            /* remove k from degree list */
        elenk = elen [k] ;                    /* elenk = |Ek| */
        nvk = nv [k] ;                            /* # of nodes k represents */
        nel += nvk ;                           /* nv[k] nodes of A eliminated */
        /* --- Garbage collection ------------------------------------------- */
        if (elenk > 0 && cnz + mindeg >= nzmax)
        {
            for (j = 0 ; j < n ; j++)
            {
                if ((p = Cp [j]) >= 0)         /* j is a live node or element */
                {
                    Cp [j] = Ci [p] ;           /* save first entry of object */
                    Ci [p] = CS_FLIP (j) ;  /* first entry is now CS_FLIP(j) */
                }
            }
            for (q = 0, p = 0 ; p < cnz ; ) /* scan all of memory */
            {
                if ((j = CS_FLIP (Ci [p++])) >= 0)  /* found object j */
                {
                    Ci [q] = Cp [j] ;        /* restore first entry of object */
                    Cp [j] = q++ ;            /* new pointer to object j */
                    for (k3 = 0 ; k3 < len [j]-1 ; k3++) Ci [q++] = Ci [p++] ;
                }
            }
            cnz = q ;                          /* Ci [cnz...nzmax-1] now free */
        }
        /* --- Construct new element ---------------------------------------- */
        dk = 0 ;
        nv [k] = -nvk ;                            /* flag k as in Lk */
        p = Cp [k] ;
        pk1 = (elenk == 0) ? p : cnz ;         /* do in place if elen[k] == 0 */
        pk2 = pk1 ;
        for (k1 = 1 ; k1 <= elenk + 1 ; k1++)
        {
            if (k1 > elenk)
            {
                e = k ;                            /* search the nodes in k */
                pj = p ;                    /* list of nodes starts at Ci[pj]*/
                ln = len [k] - elenk ;        /* length of list of nodes in k */
            }
            else
            {
                e = Ci [p++] ;                    /* search the nodes in e */
                pj = Cp [e] ;
                ln = len [e] ;                /* length of list of nodes in e */
            }
            for (k2 = 1 ; k2 <= ln ; k2++)
            {
                i = Ci [pj++] ;
                if ((nvi = nv [i]) <= 0) continue ; /* node i dead, or seen */
                dk += nvi ;                   /* degree[Lk] += size of node i */
                nv [i] = -nvi ;              /* negate nv[i] to denote i in Lk*/
                Ci [pk2++] = i ;            /* place i in Lk */
                if (next [i] != -1) last [next [i]] = last [i] ;
                if (last [i] != -1)            /* remove i from degree list */
                {
                    next [last [i]] = next [i] ;
                }
                else
                {
                    head [degree [i]] = next [i] ;
                }
            }
            if (e != k)
            {
                Cp [e] = CS_FLIP (k) ;            /* absorb e into k */
                w [e] = 0 ;                    /* e is now a dead element */
            }
        }
        if (elenk != 0) cnz = pk2 ;            /* Ci [cnz...nzmax] is free */
        degree [k] = dk ;                    /* external degree of k - |Lk\i| */
        Cp [k] = pk1 ;                      /* element k is in Ci[pk1..pk2-1] */
        len [k] = pk2 - pk1 ;
        elen [k] = -2 ;                            /* k is now an element */
        /* --- Find set differences ----------------------------------------- */
        mark = cs_wclear (mark, lemax, w, n) ;        /* clear w if necessary */
        for (pk = pk1 ; pk < pk2 ; pk++)    /* scan 1: find |Le\Lk| */
        {
            i = Ci [pk] ;
            if ((eln = elen [i]) <= 0) continue ;/* skip if elen[i] empty */
            nvi = -nv [i] ;                         /* nv [i] was negated */
            wnvi = mark - nvi ;
            for (p = Cp [i] ; p <= Cp [i] + eln - 1 ; p++)  /* scan Ei */
            {
                e = Ci [p] ;
                if (w [e] >= mark)
                {
                    w [e] -= nvi ;            /* decrement |Le\Lk| */
                }
                else if (w [e] != 0)            /* ensure e is a live element */
                {
                    w [e] = degree [e] + wnvi ;  /* 1st time e seen in scan 1 */
                }
            }
        }
        /* --- Degree update ------------------------------------------------ */
        for (pk = pk1 ; pk < pk2 ; pk++)    /* scan2: degree update */
        {
            i = Ci [pk] ;                    /* consider node i in Lk */
            p1 = Cp [i] ;
            p2 = p1 + elen [i] - 1 ;
            pn = p1 ;
            for (h = 0, d = 0, p = p1 ; p <= p2 ; p++)    /* scan Ei */
            {
                e = Ci [p] ;
                if (w [e] != 0)                 /* e is an unabsorbed element */
                {
                    dext = w [e] - mark ;   /* dext = |Le\Lk| */
                    if (dext > 0)
                    {
                        d += dext ;            /* sum up the set differences */
                        Ci [pn++] = e ;            /* keep e in Ei */
                        h += e ;            /* compute the hash of node i */
                    }
                    else
                    {
                        Cp [e] = CS_FLIP (k) ;     /* aggressive absorb. e->k */
                        w [e] = 0 ;                /* e is a dead element */
                    }
                }
            }
            elen [i] = pn - p1 + 1 ;            /* elen[i] = |Ei| */
            p3 = pn ;
            p4 = p1 + len [i] ;
            for (p = p2 + 1 ; p < p4 ; p++) /* prune edges in Ai */
            {
                j = Ci [p] ;
                if ((nvj = nv [j]) <= 0) continue ; /* node j dead or in Lk */
                d += nvj ;                    /* degree(i) += |j| */
                Ci [pn++] = j ;                  /* place j in node list of i */
                h += j ;                    /* compute hash for node i */
            }
            if (d == 0)                         /* check for mass elimination */
            {
                Cp [i] = CS_FLIP (k) ;            /* absorb i into k */
                nvi = -nv [i] ;
                dk -= nvi ;                    /* |Lk| -= |i| */
                nvk += nvi ;                    /* |k| += nv[i] */
                nel += nvi ;
                nv [i] = 0 ;
                elen [i] = -1 ;                    /* node i is dead */
            }
            else
            {
                degree [i] = CS_MIN (degree [i], d) ;     /* update degree(i) */
                Ci [pn] = Ci [p3] ;            /* move first node to end */
                Ci [p3] = Ci [p1] ;            /* move 1st el. to end of Ei */
                Ci [p1] = k ;                /* add k as 1st element in of Ei */
                len [i] = pn - p1 + 1 ;     /* new len of adj. list of node i */
                h %= n ;                    /* finalize hash of i */
                next [i] = hhead [h] ;            /* place i in hash bucket */
                hhead [h] = i ;
                last [i] = h ;                   /* save hash of i in last[i] */
            }
        }                                    /* scan2 is done */
        degree [k] = dk ;                    /* finalize |Lk| */
        lemax = CS_MAX (lemax, dk) ;
        mark = cs_wclear (mark+lemax, lemax, w, n) ;        /* clear w */
        /* --- Supernode detection ------------------------------------------ */
        for (pk = pk1 ; pk < pk2 ; pk++)
        {
            i = Ci [pk] ;
            if (nv [i] >= 0) continue ;                /* skip if i is dead */
            h = last [i] ;                      /* scan hash bucket of node i */
            i = hhead [h] ;
            hhead [h] = -1 ;                     /* hash bucket will be empty */
            for ( ; i != -1 && next [i] != -1 ; i = next [i], mark++)
            {
                ln = len [i] ;
                eln = elen [i] ;
                for (p = Cp [i]+1 ; p <= Cp [i] + ln-1 ; p++) w [Ci [p]] = mark;
                jlast = i ;
                for (j = next [i] ; j != -1 ; )       /* compare i with all j */
                {
                    ok = (len [j] == ln) && (elen [j] == eln) ;
                    for (p = Cp [j] + 1 ; ok && p <= Cp [j] + ln - 1 ; p++)
                    {
                        if (w [Ci [p]] != mark) ok = 0 ;    /* compare i and j*/
                    }
                    if (ok)                        /* i and j are identical */
                    {
                        Cp [j] = CS_FLIP (i) ;        /* absorb j into i */
                        nv [i] += nv [j] ;
                        nv [j] = 0 ;
                        elen [j] = -1 ;                /* node j is dead */
                        j = next [j] ;           /* delete j from hash bucket */
                        next [jlast] = j ;
                    }
                    else
                    {
                        jlast = j ;                /* j and i are different */
                        j = next [j] ;
                    }
                }
            }
        }
        /* --- Finalize new element------------------------------------------ */
        for (p = pk1, pk = pk1 ; pk < pk2 ; pk++)   /* finalize Lk */
        {
            i = Ci [pk] ;
            if ((nvi = -nv [i]) <= 0) continue ;/* skip if i is dead */
            nv [i] = nvi ;                        /* restore nv[i] */
            d = degree [i] + dk - nvi ;         /* compute external degree(i) */
            d = CS_MIN (d, n - nel - nvi) ;
            if (head [d] != -1) last [head [d]] = i ;
            next [i] = head [d] ;                /* put i back in degree list */
            last [i] = -1 ;
            head [d] = i ;
            mindeg = CS_MIN (mindeg, d) ;        /* find new minimum degree */
            degree [i] = d ;
            Ci [p++] = i ;                        /* place i in Lk */
        }
        nv [k] = nvk ;                            /* # nodes absorbed into k */
        if ((len [k] = p-pk1) == 0)         /* length of adj list of element k*/
        {
            Cp [k] = -1 ;                    /* k is a root of the tree */
            w [k] = 0 ;                            /* k is now a dead element */
        }
        if (elenk != 0) cnz = p ;            /* free unused space in Lk */
    }
    /* --- Postordering ----------------------------------------------------- */
    for (i = 0 ; i < n ; i++) Cp [i] = CS_FLIP (Cp [i]) ;/* fix assembly tree */
    for (j = 0 ; j <= n ; j++) head [j] = -1 ;
    for (j = n ; j >= 0 ; j--)              /* place unordered nodes in lists */
    {
        if (nv [j] > 0) continue ;            /* skip if j is an element */
        next [j] = head [Cp [j]] ;           /* place j in list of its parent */
        head [Cp [j]] = j ;
    }
    for (e = n ; e >= 0 ; e--)                    /* place elements in lists */
    {
        if (nv [e] <= 0) continue ;            /* skip unless e is an element */
        if (Cp [e] != -1)
        {
            next [e] = head [Cp [e]] ;       /* place e in list of its parent */
            head [Cp [e]] = e ;
        }
    }
    for (k = 0, i = 0 ; i <= n ; i++)          /* postorder the assembly tree */
    {
        if (Cp [i] == -1) k = cs_tdfs (i, k, head, next, P, w) ;
    }
    return (P) ;
}

/**
\todo Need test case.
*/
ivector cs_amd (XCONST dvar_hs_smatrix &A) /* Implements only order == 1: Chol*/
{
    int d, dk, dext, lemax = 0, e, elenk, eln, i, j, k, k1,
        k2, k3, jlast, ln, dense, nzmax, mindeg = 0, nvi, nvj, nvk, mark, wnvi,
        ok, cnz, nel = 0, p, p1, p2, p3, p4, pj, pk, pk1, pk2, pn, q, t ;
    unsigned int h ;
    /* --- Construct matrix C ----------------------------------------------- */

    int n = A.n ;

    dvar_hs_smatrix AT(n,A.nzmax);
    cs_transpose(A,0,AT);
    /* find dense threshold */
    dense = CS_MAX (16, (int)(10.0 * sqrt((double)n)));
    dense = CS_MIN (n-2, dense) ;

    dvar_hs_smatrix C = cs_add(A,AT);
    cs_fkeep (C, &cs_diag, NULL);        // drop diagonal entries
    cnz = C.p [n] ;
    ivector P(0,n);

    t = cnz + cnz/5 + 2*n ;                    // add elbow room to C
    C.reallocate(t);
    ivector & Cp=C.p;

    ivector len(0,n);
    len.initialize();
    ivector nv(0,n);
    ivector next(0,n);
    ivector head(0,n);
    head.initialize();
    ivector elen(0,n);
    ivector degree(0,n);
    ivector w(0,n);
    ivector hhead(0,n);
    ivector &last = P ;                        /* use P as workspace for last */

    /* --- Initialize quotient graph ---------------------------------------- */
    for (k = 0 ; k < n ; k++) len [k] = Cp [k+1] - Cp [k] ;
    len [n] = 0 ;
    nzmax = C.nzmax ;
    ivector & Ci=C.i;
    for (i = 0 ; i <= n ; i++)
    {
        head [i] = -1 ;                            /* degree list i is empty */
        last [i] = -1 ;
        next [i] = -1 ;
        hhead [i] = -1 ;                    /* hash list i is empty */
        nv [i] = 1 ;                            /* node i is just one node */
        w [i] = 1 ;                            /* node i is alive */
        elen [i] = 0 ;                            /* Ek of node i is empty */
        degree [i] = len [i] ;                    /* degree of node i */
    }
    mark = cs_wclear (0, 0, w, n) ;            /* clear w */
    elen [n] = -2 ;                            /* n is a dead element */
    Cp [n] = -1 ;                            /* n is a root of assembly tree */
    w [n] = 0 ;                                    /* n is a dead element */
    /* --- Initialize degree lists ------------------------------------------ */
    for (i = 0 ; i < n ; i++)
    {
        d = degree [i] ;
        if (d == 0)                            /* node i is empty */
        {
            elen [i] = -2 ;                    /* element i is dead */
            nel++ ;
            Cp [i] = -1 ;                    /* i is a root of assembly tree */
            w [i] = 0 ;
        }
        else if (d > dense)                    /* node i is dense */
        {
            nv [i] = 0 ;                    /* absorb i into element n */
            elen [i] = -1 ;                    /* node i is dead */
            nel++ ;
            Cp [i] = CS_FLIP (n) ;
            nv [n]++ ;
        }
        else
        {
            if (head [d] != -1) last [head [d]] = i ;
            next [i] = head [d] ;            /* put node i in degree list d */
            head [d] = i ;
        }
    }
    while (nel < n)                            /* while (selecting pivots) do */
    {
        /* --- Select node of minimum approximate degree -------------------- */
        for (k = -1 ; mindeg < n && (k = head [mindeg]) == -1 ; mindeg++) ;
        if (next [k] != -1) last [next [k]] = -1 ;
        head [mindeg] = next [k] ;            /* remove k from degree list */
        elenk = elen [k] ;                    /* elenk = |Ek| */
        nvk = nv [k] ;                            /* # of nodes k represents */
        nel += nvk ;                           /* nv[k] nodes of A eliminated */
        /* --- Garbage collection ------------------------------------------- */
        if (elenk > 0 && cnz + mindeg >= nzmax)
        {
            for (j = 0 ; j < n ; j++)
            {
                if ((p = Cp [j]) >= 0)         /* j is a live node or element */
                {
                    Cp [j] = Ci [p] ;           /* save first entry of object */
                    Ci [p] = CS_FLIP (j) ;  /* first entry is now CS_FLIP(j) */
                }
            }
            for (q = 0, p = 0 ; p < cnz ; ) /* scan all of memory */
            {
                if ((j = CS_FLIP (Ci [p++])) >= 0)  /* found object j */
                {
                    Ci [q] = Cp [j] ;        /* restore first entry of object */
                    Cp [j] = q++ ;            /* new pointer to object j */
                    for (k3 = 0 ; k3 < len [j]-1 ; k3++) Ci [q++] = Ci [p++] ;
                }
            }
            cnz = q ;                          /* Ci [cnz...nzmax-1] now free */
        }
        /* --- Construct new element ---------------------------------------- */
        dk = 0 ;
        nv [k] = -nvk ;                            /* flag k as in Lk */
        p = Cp [k] ;
        pk1 = (elenk == 0) ? p : cnz ;         /* do in place if elen[k] == 0 */
        pk2 = pk1 ;
        for (k1 = 1 ; k1 <= elenk + 1 ; k1++)
        {
            if (k1 > elenk)
            {
                e = k ;                            /* search the nodes in k */
                pj = p ;                    /* list of nodes starts at Ci[pj]*/
                ln = len [k] - elenk ;        /* length of list of nodes in k */
            }
            else
            {
                e = Ci [p++] ;                    /* search the nodes in e */
                pj = Cp [e] ;
                ln = len [e] ;                /* length of list of nodes in e */
            }
            for (k2 = 1 ; k2 <= ln ; k2++)
            {
                i = Ci [pj++] ;
                if ((nvi = nv [i]) <= 0) continue ; /* node i dead, or seen */
                dk += nvi ;                   /* degree[Lk] += size of node i */
                nv [i] = -nvi ;              /* negate nv[i] to denote i in Lk*/
                Ci [pk2++] = i ;            /* place i in Lk */
                if (next [i] != -1) last [next [i]] = last [i] ;
                if (last [i] != -1)            /* remove i from degree list */
                {
                    next [last [i]] = next [i] ;
                }
                else
                {
                    head [degree [i]] = next [i] ;
                }
            }
            if (e != k)
            {
                Cp [e] = CS_FLIP (k) ;            /* absorb e into k */
                w [e] = 0 ;                    /* e is now a dead element */
            }
        }
        if (elenk != 0) cnz = pk2 ;            /* Ci [cnz...nzmax] is free */
        degree [k] = dk ;                    /* external degree of k - |Lk\i| */
        Cp [k] = pk1 ;                      /* element k is in Ci[pk1..pk2-1] */
        len [k] = pk2 - pk1 ;
        elen [k] = -2 ;                            /* k is now an element */
        /* --- Find set differences ----------------------------------------- */
        mark = cs_wclear (mark, lemax, w, n) ;        /* clear w if necessary */
        for (pk = pk1 ; pk < pk2 ; pk++)    /* scan 1: find |Le\Lk| */
        {
            i = Ci [pk] ;
            if ((eln = elen [i]) <= 0) continue ;/* skip if elen[i] empty */
            nvi = -nv [i] ;                         /* nv [i] was negated */
            wnvi = mark - nvi ;
            for (p = Cp [i] ; p <= Cp [i] + eln - 1 ; p++)  /* scan Ei */
            {
                e = Ci [p] ;
                if (w [e] >= mark)
                {
                    w [e] -= nvi ;            /* decrement |Le\Lk| */
                }
                else if (w [e] != 0)            /* ensure e is a live element */
                {
                    w [e] = degree [e] + wnvi ;  /* 1st time e seen in scan 1 */
                }
            }
        }
        /* --- Degree update ------------------------------------------------ */
        for (pk = pk1 ; pk < pk2 ; pk++)    /* scan2: degree update */
        {
            i = Ci [pk] ;                    /* consider node i in Lk */
            p1 = Cp [i] ;
            p2 = p1 + elen [i] - 1 ;
            pn = p1 ;
            for (h = 0, d = 0, p = p1 ; p <= p2 ; p++)    /* scan Ei */
            {
                e = Ci [p] ;
                if (w [e] != 0)                 /* e is an unabsorbed element */
                {
                    dext = w [e] - mark ;   /* dext = |Le\Lk| */
                    if (dext > 0)
                    {
                        d += dext ;            /* sum up the set differences */
                        Ci [pn++] = e ;            /* keep e in Ei */
                        h += e ;            /* compute the hash of node i */
                    }
                    else
                    {
                        Cp [e] = CS_FLIP (k) ;     /* aggressive absorb. e->k */
                        w [e] = 0 ;                /* e is a dead element */
                    }
                }
            }
            elen [i] = pn - p1 + 1 ;            /* elen[i] = |Ei| */
            p3 = pn ;
            p4 = p1 + len [i] ;
            for (p = p2 + 1 ; p < p4 ; p++) /* prune edges in Ai */
            {
                j = Ci [p] ;
                if ((nvj = nv [j]) <= 0) continue ; /* node j dead or in Lk */
                d += nvj ;                    /* degree(i) += |j| */
                Ci [pn++] = j ;                  /* place j in node list of i */
                h += j ;                    /* compute hash for node i */
            }
            if (d == 0)                         /* check for mass elimination */
            {
                Cp [i] = CS_FLIP (k) ;            /* absorb i into k */
                nvi = -nv [i] ;
                dk -= nvi ;                    /* |Lk| -= |i| */
                nvk += nvi ;                    /* |k| += nv[i] */
                nel += nvi ;
                nv [i] = 0 ;
                elen [i] = -1 ;                    /* node i is dead */
            }
            else
            {
                degree [i] = CS_MIN (degree [i], d) ;     /* update degree(i) */
                Ci [pn] = Ci [p3] ;            /* move first node to end */
                Ci [p3] = Ci [p1] ;            /* move 1st el. to end of Ei */
                Ci [p1] = k ;                /* add k as 1st element in of Ei */
                len [i] = pn - p1 + 1 ;     /* new len of adj. list of node i */
                h %= n ;                    /* finalize hash of i */
                next [i] = hhead [h] ;            /* place i in hash bucket */
                hhead [h] = i ;
                last [i] = h ;                   /* save hash of i in last[i] */
            }
        }                                    /* scan2 is done */
        degree [k] = dk ;                    /* finalize |Lk| */
        lemax = CS_MAX (lemax, dk) ;
        mark = cs_wclear (mark+lemax, lemax, w, n) ;        /* clear w */
        /* --- Supernode detection ------------------------------------------ */
        for (pk = pk1 ; pk < pk2 ; pk++)
        {
            i = Ci [pk] ;
            if (nv [i] >= 0) continue ;                /* skip if i is dead */
            h = last [i] ;                      /* scan hash bucket of node i */
            i = hhead [h] ;
            hhead [h] = -1 ;                     /* hash bucket will be empty */
            for ( ; i != -1 && next [i] != -1 ; i = next [i], mark++)
            {
                ln = len [i] ;
                eln = elen [i] ;
                for (p = Cp [i]+1 ; p <= Cp [i] + ln-1 ; p++) w [Ci [p]] = mark;
                jlast = i ;
                for (j = next [i] ; j != -1 ; )       /* compare i with all j */
                {
                    ok = (len [j] == ln) && (elen [j] == eln) ;
                    for (p = Cp [j] + 1 ; ok && p <= Cp [j] + ln - 1 ; p++)
                    {
                        if (w [Ci [p]] != mark) ok = 0 ;    /* compare i and j*/
                    }
                    if (ok)                        /* i and j are identical */
                    {
                        Cp [j] = CS_FLIP (i) ;        /* absorb j into i */
                        nv [i] += nv [j] ;
                        nv [j] = 0 ;
                        elen [j] = -1 ;                /* node j is dead */
                        j = next [j] ;           /* delete j from hash bucket */
                        next [jlast] = j ;
                    }
                    else
                    {
                        jlast = j ;                /* j and i are different */
                        j = next [j] ;
                    }
                }
            }
        }
        /* --- Finalize new element------------------------------------------ */
        for (p = pk1, pk = pk1 ; pk < pk2 ; pk++)   /* finalize Lk */
        {
            i = Ci [pk] ;
            if ((nvi = -nv [i]) <= 0) continue ;/* skip if i is dead */
            nv [i] = nvi ;                        /* restore nv[i] */
            d = degree [i] + dk - nvi ;         /* compute external degree(i) */
            d = CS_MIN (d, n - nel - nvi) ;
            if (head [d] != -1) last [head [d]] = i ;
            next [i] = head [d] ;                /* put i back in degree list */
            last [i] = -1 ;
            head [d] = i ;
            mindeg = CS_MIN (mindeg, d) ;        /* find new minimum degree */
            degree [i] = d ;
            Ci [p++] = i ;                        /* place i in Lk */
        }
        nv [k] = nvk ;                            /* # nodes absorbed into k */
        if ((len [k] = p-pk1) == 0)         /* length of adj list of element k*/
        {
            Cp [k] = -1 ;                    /* k is a root of the tree */
            w [k] = 0 ;                            /* k is now a dead element */
        }
        if (elenk != 0) cnz = p ;            /* free unused space in Lk */
    }
    /* --- Postordering ----------------------------------------------------- */
    for (i = 0 ; i < n ; i++) Cp [i] = CS_FLIP (Cp [i]) ;/* fix assembly tree */
    for (j = 0 ; j <= n ; j++) head [j] = -1 ;
    for (j = n ; j >= 0 ; j--)              /* place unordered nodes in lists */
    {
        if (nv [j] > 0) continue ;            /* skip if j is an element */
        next [j] = head [Cp [j]] ;           /* place j in list of its parent */
        head [Cp [j]] = j ;
    }
    for (e = n ; e >= 0 ; e--)                    /* place elements in lists */
    {
        if (nv [e] <= 0) continue ;            /* skip unless e is an element */
        if (Cp [e] != -1)
        {
            next [e] = head [Cp [e]] ;       /* place e in list of its parent */
            head [Cp [e]] = e ;
        }
    }
    for (k = 0, i = 0 ; i <= n ; i++)          /* postorder the assembly tree */
    {
        if (Cp [i] == -1) k = cs_tdfs (i, k, head, next, P, w) ;
    }
    return (P) ;
}

/* compute the etree of A (using triu(A), or A'A without forming A'A */
ivector cs_etree (XCONST hs_smatrix &_A)
{
    ADUNCONST(hs_smatrix,A)
    int i, k, p, inext;

    int n = A.n ;
    ivector & Ap=A.p;
    ivector & Ai=A.i;

    ivector parent(0,n-1);
    parent.initialize();
    ivector w(0,n-1);                   /* get workspace */
    w.initialize();
    ivector &ancestor = w ;
    for (k = 0 ; k < n ; k++)
    {
        parent [k] = -1 ;                   /* node k has no parent yet */
        ancestor [k] = -1 ;                 /* nor does k have an ancestor */
        for (p = Ap [k] ; p < Ap [k+1] ; p++)
        {
            i = Ai [p] ;
            for ( ; i != -1 && i < k ; i = inext)   /* traverse from i to k */
            {
                inext = ancestor [i] ;              /* inext = ancestor of i */
                ancestor [i] = k ;                  /* path compression */
                if (inext == -1) parent [i] = k ;   /* no anc., parent is k */
            }
        }
    }
    return (parent) ;
}

ivector cs_etree (XCONST dvar_hs_smatrix &_A)
{
    ADUNCONST(dvar_hs_smatrix,A)
    int i, k, p, inext;

    int n = A.n ;
    ivector & Ap=A.p;
    ivector & Ai=A.i;

    ivector parent(0,n-1);
    parent.initialize();
    ivector w(0,n-1);                   /* get workspace */
    w.initialize();
    ivector &ancestor = w ;
    for (k = 0 ; k < n ; k++)
    {
        parent [k] = -1 ;                   /* node k has no parent yet */
        ancestor [k] = -1 ;                 /* nor does k have an ancestor */
        for (p = Ap [k] ; p < Ap [k+1] ; p++)
        {
            i = Ai [p] ;
            for ( ; i != -1 && i < k ; i = inext)   /* traverse from i to k */
            {
                inext = ancestor [i] ;              /* inext = ancestor of i */
                ancestor [i] = k ;                  /* path compression */
                if (inext == -1) parent [i] = k ;   /* no anc., parent is k */
            }
        }
    }
    return (parent) ;
}

/* post order a forest */
ivector cs_post (XCONST ivector &parent, int n)
{
    int j, k = 0;

    ivector post(0,n-1);
    post.initialize();
    ivector head(0,n-1);
    ivector next(0,n-1);
    next.initialize();
    ivector stack(0,n-1);
    stack.initialize();

    for (j = 0 ; j < n ; j++) head [j] = -1 ;           /* empty linked lists */
    for (j = n-1 ; j >= 0 ; j--)            /* traverse nodes in reverse order*/
    {
        if (parent [j] == -1) continue ;    /* j is a root */
        next [j] = head [parent [j]] ;      /* add j to list of its parent */
        head [parent [j]] = j ;
    }
    for (j = 0 ; j < n ; j++)
    {
        if (parent [j] != -1) continue ;    /* skip j if it is not a root */
        k = cs_tdfs (j, k, head, next, post, stack) ;
    }
    return (post) ;
}


/* consider A(i,j), node j in ith row subtree and return lca(jprev,j) */
int cs_leaf (int i, int j, XCONST ivector &first, ivector &maxfirst,
  ivector &prevleaf, ivector &ancestor, int *jleaf)
{
    int q, s, sparent, jprev ;
    *jleaf = 0 ;
    if (i <= j || first [j] <= maxfirst [i]) return (-1) ;  /* j not a leaf */
    maxfirst [i] = first [j] ;      /* update max first[j] seen so far */
    jprev = prevleaf [i] ;          /* jprev = previous leaf of ith subtree */
    prevleaf [i] = j ;
    *jleaf = (jprev == -1) ? 1: 2 ; /* j is first or subsequent leaf */
    if (*jleaf == 1) return (i) ;   /* if 1st leaf, q = root of ith subtree */
    for (q = jprev ; q != ancestor [q] ; q = ancestor [q]) ;
    for (s = jprev ; s != q ; s = sparent)
    {
        sparent = ancestor [s] ;    /* path compression */
        ancestor [s] = q ;
    }
    return (q) ;                    /* q = least common ancester (jprev,j) */
}

/* column counts of LL'=A or LL'=A'A, given parent & post ordering */
ivector cs_counts (XCONST hs_smatrix &A, XCONST ivector &parent,
  XCONST ivector &post)
{
    int i, j, k, J, p, q, jleaf;

    int n = A.n ;
    ivector delta(0,n-1);
    delta.initialize();
    ivector& colcount = delta;

    hs_smatrix AT(n,A.nzmax);
    cs_transpose (A,0,AT) ;                                /* AT = A' */

    ivector ancestor(0,n-1);
    ancestor = -1;
    ivector maxfirst(0,n-1);
    maxfirst = -1;
    ivector prevleaf(0,n-1);
    prevleaf = -1;
    ivector first(0,n-1);
    first = -1;

    for (k = 0 ; k < n ; k++)                        /* find first [j] */
    {
        j = post [k] ;
        delta [j] = (first [j] == -1) ? 1 : 0 ;  /* delta[j]=1 if j is a leaf */
        for ( ; j != -1 && first [j] == -1 ; j = parent [j]) first [j] = k ;
    }

    ivector & ATp=AT.p;
    ivector & ATi=AT.i;

    for (i = 0 ; i < n ; i++) ancestor [i] = i ; /* each node in its own set */
    for (k = 0 ; k < n ; k++)
    {
        j = post [k] ;              /* j is the kth node in postordered etree */
        if (parent [j] != -1) delta [parent [j]]-- ;       /* j is not a root */
        for (J = j ; J != -1 ; J = -1)        /* J=j for LL'=A case */
        {
            for (p = ATp [J] ; p < ATp [J+1] ; p++)
            {
                i = ATi [p] ;
                q = cs_leaf (i, j, first, maxfirst, prevleaf, ancestor, &jleaf);
                if (jleaf >= 1) delta [j]++ ;   /* A(i,j) is in skeleton */
                if (jleaf == 2) delta [q]-- ;     /* account for overlap in q */
            }
        }
        if (parent [j] != -1) ancestor [j] = parent [j] ;
    }
    for (j = 0 ; j < n ; j++)                /* sum up delta's of each child */
    {
        if (parent [j] != -1) colcount [parent [j]] += colcount [j] ;
    }
    return (colcount) ;
}

ivector cs_counts (XCONST dvar_hs_smatrix &A, XCONST ivector &parent,
  XCONST ivector &post)
{
    int i, j, k, J, p, q, jleaf;

    int n = A.n ;
    ivector delta(0,n-1);
    delta.initialize();
    ivector& colcount = delta;

    dvar_hs_smatrix AT(n,A.nzmax);
    cs_transpose (A,0,AT) ;                                /* AT = A' */

    ivector ancestor(0,n-1);
    ancestor = -1;
    ivector maxfirst(0,n-1);
    maxfirst = -1;
    ivector prevleaf(0,n-1);
    prevleaf = -1;
    ivector first(0,n-1);
    first = -1;

    for (k = 0 ; k < n ; k++)                        /* find first [j] */
    {
        j = post [k] ;
        delta [j] = (first [j] == -1) ? 1 : 0 ;  /* delta[j]=1 if j is a leaf */
        for ( ; j != -1 && first [j] == -1 ; j = parent [j]) first [j] = k ;
    }

    ivector & ATp=AT.p;
    ivector & ATi=AT.i;

    for (i = 0 ; i < n ; i++) ancestor [i] = i ; /* each node in its own set */
    for (k = 0 ; k < n ; k++)
    {
        j = post [k] ;              /* j is the kth node in postordered etree */
        if (parent [j] != -1) delta [parent [j]]-- ;       /* j is not a root */
        for (J = j ; J != -1 ; J = -1)        /* J=j for LL'=A case */
        {
            for (p = ATp [J] ; p < ATp [J+1] ; p++)
            {
                i = ATi [p] ;
                q = cs_leaf (i, j, first, maxfirst, prevleaf, ancestor, &jleaf);
                if (jleaf >= 1) delta [j]++ ;   /* A(i,j) is in skeleton */
                if (jleaf == 2) delta [q]-- ;     /* account for overlap in q */
            }
        }
        if (parent [j] != -1) ancestor [j] = parent [j] ;
    }
    for (j = 0 ; j < n ; j++)                /* sum up delta's of each child */
    {
        if (parent [j] != -1) colcount [parent [j]] += colcount [j] ;
    }
    return (colcount) ;
}

/* pinv = p', or p = pinv' */
ivector cs_pinv (XCONST ivector &p, int n)
{
    int k ;
    ivector pinv(0,n-1);
    pinv.initialize();
    for (k = 0 ; k < n ; k++) pinv [p [k]] = k ;/* invert the permutation */
    return (pinv) ;                             /* return result */
}

/* Constructor that does symbolic Cholesky  */
 //hs_symbolic::hs_symbolic(int _n, XCONST dmatrix &T, int order)
 //{
 //
 //    if (order != 0 && order != 1 )
 //    {
 //        cout << "!!! hs_symbolic: only order = 0,1 allowed" << endl;
 //        exit(0);
 //    }
 //
 //    hs_smatrix A(_n,T);
 //    n = _n;
 //
 //    // Allocate symbolic structure
 //    pinv.allocate(0,n-1);
 //    parent.allocate(0,n-1);
 //    cp.allocate(0,n);
 //    cp = 0;
 //
 //    hs_smatrix C(A);
 //    C = A;
 //
 //    if(order==0)
 //    {
 //      pinv(0) = -1;
 //    }
 //    else
 //    {
 //      ivector P = cs_amd (A) ;          /* P = amd(A+A'), or natural */
 //      pinv = cs_pinv (P, n) ;           /* find inverse permutation */
 //      hs_symperm(A,pinv,C);
 //    }
 //
 //    parent = cs_etree (C) ;                     /* find etree of C */
 //    ivector post = cs_post (parent, n) ;  /* postorder the etree */
 //    /* find column counts of chol(C) */
 //    ivector c = cs_counts (C, parent, post) ;
 //    lnz = cs_cumsum (cp, c, n) ;         /* find column pointers for L */
 //
 //}
 //
hs_symbolic::hs_symbolic(void)
{
    n = 0;

    // Allocate symbolic structure
    pinv.allocate();
    parent.allocate();
    cp.allocate();
}

hs_symbolic::hs_symbolic(XCONST dcompressed_triplet &_T, int order)
{
  ADUNCONST(dcompressed_triplet,T)
  int _n=T.get_n();

    if (order != 0 && order != 1 )
    {
        cout << "!!! hs_symbolic: only order = 0,1 allowed" << endl;
        exit(0);
    }

    hs_smatrix A(_n,T);
    n = _n;

    // Allocate symbolic structure
    pinv.allocate(0,n-1);
    parent.allocate(0,n-1);
    cp.allocate(0,n);
    cp = 0;

    hs_smatrix C(A);
    C = A;

    if(order==0)
    {
      pinv(0) = -1;
    }
    else
    {
      ivector P = cs_amd (A) ;          /* P = amd(A+A'), or natural */
      pinv = cs_pinv (P, n) ;           /* find inverse permutation */
      hs_symperm(A,pinv,C);
    }

    parent = cs_etree (C) ;                     /* find etree of C */
    ivector post = cs_post (parent, n) ;  /* postorder the etree */
   ivector c = cs_counts (C, parent, post) ; /* find column counts of chol(C) */
    lnz = cs_cumsum (cp, c, n) ;         /* find column pointers for L */
}

hs_symbolic::hs_symbolic(XCONST dvar_compressed_triplet &_T, int order)
{
  ADUNCONST(dvar_compressed_triplet,T)
  int _n=T.get_n();

    if (order != 0 && order != 1 )
    {
        cout << "!!! hs_symbolic: only order = 0,1 allowed" << endl;
        exit(0);
    }

    dvar_hs_smatrix A(_n,T);
    n = _n;

    // Allocate symbolic structure
    pinv.allocate(0,n-1);
    parent.allocate(0,n-1);
    cp.allocate(0,n);
    cp = 0;

    dvar_hs_smatrix C(A);
    C = A;

    if(order==0)
    {
      pinv(0) = -1;
    }
    else
    {
      ivector P = cs_amd (A) ;          /* P = amd(A+A'), or natural */
      pinv = cs_pinv (P, n) ;           /* find inverse permutation */
      hs_symperm(A,pinv,C);
    }

    parent = cs_etree (C) ;                     /* find etree of C */
    ivector post = cs_post (parent, n) ;  /* postorder the etree */
   ivector c = cs_counts (C, parent, post) ; /* find column counts of chol(C) */
    lnz = cs_cumsum (cp, c, n) ;         /* find column pointers for L */
}
dvar_compressed_triplet::dvar_compressed_triplet(int mmin,int mmax,int _n,
  int _m)
{
  allocate(mmin,mmax,_n,_m);
}

void dcompressed_triplet::initialize(void)
{
  x.initialize();
}

dcompressed_triplet::dcompressed_triplet(int mmin,int mmax,int _n,int _m)
{
  allocate(mmin,mmax,_n,_m);
}


void dvar_compressed_triplet::allocate(int mmin,int mmax,int _n,int _m)
{
  n=_n;
  m=_m;
  coords.allocate(1,2,mmin,mmax);
  x.allocate(mmin,mmax);
}

void dvar_compressed_triplet::deallocate(void)
{
  n=-1;
  m=-1;
  coords.deallocate();
  x.deallocate();
}

void dcompressed_triplet::allocate(int mmin,int mmax,int _n,int _m)
{
  n=_n;
  m=_m;
  coords.allocate(1,2,mmin,mmax);
  x.allocate(mmin,mmax);
}

void dcompressed_triplet::deallocate(void)
{
  n=-1;
  m=-1;
  coords.deallocate();
  x.deallocate();
}


istream & operator >> (istream & is,dcompressed_triplet & M)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    is >> M(i,1);
    is >> M(i,2);
    is >> M(i);
  }
  return is;
}

istream & operator >> (istream & is,dvar_compressed_triplet & M)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    is >> M(i,1);
    is >> M(i,2);
    is >> M(i);
  }
  return is;
}

hs_smatrix * return_choleski_decomp(dcompressed_triplet & st)
{
  //ADUNCONST(dmatrix,st)
  int n=st.get_n();

  hs_smatrix HS(n,st);  // Convert triplet to working format

  hs_symbolic S(st,1);         // Fill reducing row-col permutation
  hs_smatrix * PL = new hs_smatrix(S);              // Allocates cholesky factor

  chol(HS,S,*PL);                  // Does numeric factorization

  PL->set_symbolic(S);

  return PL;
}

dvar_hs_smatrix * return_choleski_decomp(dvar_compressed_triplet & st)
{
  //ADUNCONST(dmatrix,st)
  int n=st.get_n();

  dvar_hs_smatrix HS(n,st);  // Convert triplet to working format

  hs_symbolic S(st,1);         // Fill reducing row-col permutation
  dvar_hs_smatrix * PL = new dvar_hs_smatrix(S);    // Allocates cholesky factor

  chol(HS,S,*PL);                  // Does numeric factorization

  PL->set_symbolic(S);

  return PL;
}

dvector return_choleski_decomp_solve(dcompressed_triplet & st,dvector& eps)
{
  //ADUNCONST(dmatrix,st)
  int n=st.get_n();

  hs_smatrix HS(n,st);  // Convert triplet to working format

  hs_symbolic S(st,1);         // Fill reducing row-col permutation
  hs_smatrix L(S);              // Allocates cholesky factor

  chol(HS,S,L);                  // Does numeric factorization

  dvector x(0,n-1);
  eps.shift(0);
  x = cs_ipvec(S.pinv, eps);
  eps.shift(1);
  x = cs_lsolve(L,x);
  //x = cs_ltsolve(L,x);
  x = cs_pvec(S.pinv,x);
  x.shift(1);
  return x;
}

dvector return_choleski_factor_solve(hs_smatrix * PL,dvector& eps)
{
  //ADUNCONST(dmatrix,st)
  hs_smatrix& L= *PL;
  int n=L.m;
  hs_symbolic & S = L.sym;
  dvector x(0,n-1);
  eps.shift(0);
  x = cs_ipvec(S.pinv, eps);
  eps.shift(1);
  x = cs_lsolve(L,x);
  //x = cs_ltsolve(L,x);
  x = cs_pvec(S.pinv,x);
  x.shift(1);
  return x;
}

dvar_vector return_choleski_factor_solve(dvar_hs_smatrix * PL,dvector& eps)
{
  //ADUNCONST(dmatrix,st)
  dvar_hs_smatrix& L= *PL;
  int n=L.m;
  hs_symbolic & S = L.sym;
  dvar_vector x(0,n-1);
  eps.shift(0);
  x = cs_ipvec(S.pinv, eps);
  eps.shift(1);
  x = cs_lsolve(L,x);
  //x = cs_ltsolve(L,x);
  x = cs_pvec(S.pinv,x);
  x.shift(1);
  return x;
}


dvector solve(dcompressed_triplet & st,dmatrix & Hess,
  dvector& grad)
{
  //ADUNCONST(dmatrix,st)
  int nz=st.indexmax();
  int n=Hess.indexmax();
  // fill up compressed triplet with nonzero entries of the Hessian
  for (int i=1;i<=nz;i++)
  {
    st(i)=Hess(st(1,i),st(2,i));
  }

  hs_smatrix HS(n,st);  // Convert triplet to working format

  hs_symbolic S(st,1);         // Fill reducing row-col permutation
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

dvector solve(dcompressed_triplet & st,dmatrix & Hess,
  dvector& grad,hs_symbolic& S)
{
  //ADUNCONST(dmatrix,st)
  int nz=st.indexmax();
  int n=Hess.indexmax();
  // fill up compressed triplet with nonzero entries of the Hessian
  for (int i=1;i<=nz;i++)
  {
    st(i)=Hess(st(1,i),st(2,i));
  }

  hs_smatrix HS(n,st);  // Convert triplet to working format

  //hs_symbolic S(st,1);         // Fill reducing row-col permutation
  hs_smatrix L(S);              // Allocates cholesky factor
  //hs_smatrix L1(S);              // Allocates cholesky factor

  //chol(HS,S,L);                  // Does numeric factorization
  ivector nxcount;
  chol(HS,S,L);                  // Does numeric factorization
  //tmpxchol(HS,S,L,nxcount);                  // Does numeric factorization

  //cout << norm2(L.get_x()-L1.get_x()) << endl;
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

dvector solve(const dcompressed_triplet & _st,const dvector& _grad,
  const hs_symbolic& S)
  {
    ADUNCONST(dcompressed_triplet,st)
    ADUNCONST(dvector,grad)
    int n=st.get_n();
    //int n=Hess.indexmax();
    // fill up compressed triplet with nonzero entries of the Hessian

    hs_smatrix HS(n,st);  // Convert triplet to working format

    hs_smatrix L(S);              // Allocates cholesky factor

    ivector nxcount;
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

dvector solve(const dcompressed_triplet & _st,const dvector& _grad,
  const hs_symbolic& S,int& ierr)
  {
    ADUNCONST(dcompressed_triplet,st)
    ADUNCONST(dvector,grad)
    int n=st.get_n();
    //int n=Hess.indexmax();
    // fill up compressed triplet with nonzero entries of the Hessian

    hs_smatrix HS(n,st);  // Convert triplet to working format

    hs_smatrix L(S);              // Allocates cholesky factor

    ivector nxcount;
    ierr=chol(HS,S,L);     // 0 error 1 OK        Does numeric factorization

    dvector x(0,n-1);
  if (ierr)
  {
    grad.shift(0);
    x = cs_ipvec(S.pinv, grad);
    grad.shift(1);
    x = cs_lsolve(L,x);
    x = cs_ltsolve(L,x);
    x = cs_pvec(S.pinv,x);
    x.shift(1);
  }
  else
  {
    x.initialize();
    x.shift(1);
  }
  return x;
}

int allocated(const dcompressed_triplet & _st)
{
  ADUNCONST(dcompressed_triplet,st)
  return allocated(st.get_coords());
}
int allocated(const dvar_compressed_triplet & _st)
{
  ADUNCONST(dvar_compressed_triplet,st)
  return allocated(st.get_coords());
}
dvariable ln_det(dvar_compressed_triplet& VM)
{
  int n=VM.get_n();
  dvar_hs_smatrix H(n,VM);
  hs_symbolic S(VM,1);         // Fill reducing row-col permutation
  dvar_hs_smatrix L(S);              // Allocates cholesky factor
  int ierr=chol(H,S,L);                  // Does numeric factorization
  if (ierr==0)
  {
    cerr << "Error matrix not positrive definite in chol" << endl;
    ad_exit(1);
  }
  return 2.0*ln_det(L);
  //return L.x(0);
}


dvariable ln_det(dvar_compressed_triplet& VM,hs_symbolic& S)
{
  int n=VM.get_n();
  dvar_hs_smatrix H(n,VM);
  //hs_symbolic S(VM,1);         // Fill reducing row-col permutation
  dvar_hs_smatrix L(S);              // Allocates cholesky factor
  int ierr=chol(H,S,L);                  // Does numeric factorization
  if (ierr==0)
  {
    cerr << "Error matrix not positive definite in chol" << endl;
    ad_exit(1);
  }
  return 2.0*ln_det(L);
  //return L.x(0);
}


 int check_flag=0;

dvariable ln_det(dvar_compressed_triplet& VM,hs_symbolic& S,
  dcompressed_triplet& s)
{
  RETURN_ARRAYS_INCREMENT();
  int n=VM.get_n();
  dvar_hs_smatrix H(n,VM);
  //hs_symbolic S(VM,1);         // Fill reducing row-col permutation
  dvar_hs_smatrix L(S);              // Allocates cholesky factor
  int ierr = 0;
  if (check_flag==0)
  {
    ierr=varchol(H,S,L,s);
  }
  else
  {
    ierr=chol(H,S,L);
  }
  if (ierr==0)
  {
    cerr << "Error matrix not positive definite in chol" << endl;
    ad_exit(1);
  }
  //set_gradstack_flag("AAC");
  dvariable tmp= 2.0*ln_det(L);
  RETURN_ARRAYS_DECREMENT();
  return tmp;
  //return L.x(0);
}


double ln_det(const dcompressed_triplet& VVM,
              const hs_symbolic& T)
{
  //ADUNCONST(dcompressed_triplet,VM)
  //ADUNCONST(hs_symbolic,S)
  dcompressed_triplet& VM = (dcompressed_triplet&)VVM;
  hs_symbolic& S = (hs_symbolic&)T;
  int n=VM.get_n();
  hs_smatrix H(n,VM);
  //hs_symbolic S(VM,1);         // Fill reducing row-col permutation
  hs_smatrix L(S);              // Allocates cholesky factor
  int ierr=chol(H,S,L);                  // Does numeric factorization
  if (ierr==0)
  {
    cerr << "Error matrix not positrive definite in chol" << endl;
    ad_exit(1);
  }
  return 2.0*ln_det(L);
  //return L.x(0);
}


double ln_det(const dcompressed_triplet& VVM)
{
  //ADUNCONST(dcompressed_triplet,VM)
  dcompressed_triplet& VM = (dcompressed_triplet&)VVM;
  int n=VM.get_n();
  hs_smatrix H(n,VM);
  hs_symbolic S(VM,1);         // Fill reducing row-col permutation
  hs_smatrix L(S);              // Allocates cholesky factor
  int ierr=chol(H,S,L);                  // Does numeric factorization
  if (ierr==0)
  {
    cerr << "Error matrix not positrive definite in chol" << endl;
    ad_exit(1);
  }
  return 2.0*ln_det(L);
  //return L.x(0);
}


int cholnew(XCONST hs_smatrix &AA, XCONST hs_symbolic &T, hs_smatrix &LL)
{
    //ADUNCONST(hs_symbolic,S)
    //ADUNCONST(hs_smatrix,L)
    //ADUNCONST(hs_smatrix,A)
    hs_symbolic& S = (hs_symbolic&)T;
    hs_smatrix& A = (hs_smatrix&)AA;
    hs_smatrix& L = (hs_smatrix&)LL;
    double d, lki;
    int top, i, p, k, n;

    n = A.n ;

    ivector c(0,n-1);                              /* int workspace */
    ivector s(0,n-1);                                   /* int workspace */
    dvector x(0,n-1) ;                        /* double workspace */
    double xcount=0.0;                        /* double workspace */

    ivector & cp=S.cp;
    ivector & pinv=S.pinv;
    ivector & parent=S.parent;

    hs_smatrix C(A);
    C = A;
    if(S.pinv[0]!=-1)
      hs_symperm(A,pinv,C);

    ivector & Cp=C.p;
    ivector & Ci=C.i;
    dvector & Cx=C.x;

    ivector & Lp=L.p;
    ivector & Li=L.i;
    dvector & Lx=L.x;

    for (k = 0 ; k < n ; k++)
      Lp [k] = c [k] = cp [k] ;

    for (k = 0 ; k < n ; k++)            /* compute L(:,k) for L*L' = C */
    {
        /* --- Nonzero pattern of L(k,:) ------------------------------------ */
        top = cs_ereach (C, k, parent, s, c) ;      /* find pattern of L(k,:) */
        x [k] = 0 ;                                    /* x (0:k) is now zero */
        for (p = Cp [k] ; p < Cp [k+1] ; p++)       /* x = full(triu(C(:,k))) */
        {
            if (Ci [p] <= k) x [Ci [p]] = Cx [p] ;
        }
        d = x [k] ;                        /* d = C(k,k) */
        x [k] = 0 ;                        /* clear x for k+1st iteration */
        /* --- Triangular solve --------------------------------------------- */
        for ( ; top < n ; top++)    /* solve L(0:k-1,0:k-1) * x = C(:,k) */
        {
            i = s [top] ;                /* s [top..n-1] is pattern of L(k,:) */
            lki = x [i] / Lx [Lp [i]] ; /* L(k,i) = x (i) / L(i,i) */
            xcount++;
            x [i] = 0 ;                        /* clear x for k+1st iteration */


            int Lpi1=Lp[i]+1;
            int ci=c[i];
            if (Lpi1<ci)
            {
              myacc(p,Lpi1,ci,Li,x,Lx,lki);
            }
            /*
            for (p = Lp [i] + 1 ; p < c [i] ; p++)
            {
                x [Li [p]] -= Lx [p] * lki ;
            }
            */

            d -= lki * lki ;                /* d = d - L(k,i)*L(k,i) */
            p = c [i]++ ;
            Li [p] = k ;                /* store L(k,i) in column i */
            Lx [p] = lki ;
        }
        /* --- Compute L(k,k) ----------------------------------------------- */
        if (d <= 0) return (0) ; /* not pos def */
        p = c [k]++ ;
        Li [p] = k ;                   /* store L(k,k) = sqrt (d) in column k */
        Lx [p] = sqrt (d) ;
    }
    Lp [n] = cp [n] ;                    /* finalize L */
    return (1) ;
}

static void dfcholeski_sparse(void);

int varchol(XCONST dvar_hs_smatrix &AA, XCONST hs_symbolic &T,
  dvar_hs_smatrix &LL, dcompressed_triplet & sparse_triplet2)
 //laplace_approximation_calculator * lapprox)
{
  RETURN_ARRAYS_INCREMENT(); //Need this statement because the function
  //ADUNCONST(hs_symbolic,S)
  //ADUNCONST(dvar_hs_smatrix,L)
  //ADUNCONST(dvar_hs_smatrix,A)
    hs_symbolic& S = (hs_symbolic&)T;
    dvar_hs_smatrix& A = (dvar_hs_smatrix&)AA;
    dvar_hs_smatrix& L = (dvar_hs_smatrix&)LL;
  int icount=0;
  double lki;
  double d;
  int top, i, p, k, n;
  n = A.n ;
  ivector c(0,n-1);                              /* int workspace */
  ivector s(0,n-1);                                   /* int workspace */
  dvector x(0,n-1) ;                        /* double workspace */

  ivector & cp=S.cp;
  ivector & pinv=S.pinv;
  ivector & parent=S.parent;

  dvar_hs_smatrix C(A);
  C = A;
  if(S.pinv[0]!=-1)
    hs_symperm(A,pinv,C);

  ivector & Cp=C.p;
  ivector & Ci=C.i;
  dvector Cx=value(C.x);

  ivector & Lp=L.p;
  ivector & Li=L.i;
  dvector Lx=value(L.x);
  int txcount=0;
  int lkicount=0;
  int tccount=0;

  for (k = 0 ; k < n ; k++)
  {
    Lp [k] = c [k] = cp [k] ;
  }

  for (k = 0 ; k < n ; k++)
  {
    top = cs_ereach (C, k, parent, s, c) ;
    x [k] = 0 ;
    for (p = Cp [k] ; p < Cp [k+1] ; p++)
    {
      if (Ci[p] <= k) x [Ci[p]] = Cx[p] ;
    }
    d = x[k] ;
    x[k] = 0.0;
    for ( ; top < n ; top++)
    {
      i = s[top] ;
      lki = x[i] / Lx[Lp[i]] ;
      txcount++;
      icount++;   // count the number of times lki is overwritten
      lkicount++;   // count the number of times lki is overwritten
      x [i] = 0 ;
      for (p = Lp [i] + 1 ; p < c [i] ; p++)
      {
        x[Li[p]] -= Lx[p] * lki ;
      }
      d -= lki * lki ;
      p = c [i]++ ;
      tccount++;
      Li [p] = k ;
      Lx [p] = lki ;
    }
    if (d <= 0) return (0) ;
    p = c [k]++ ;
    tccount++;
    Li [p] = k ;
    Lx [p] = sqrt (d) ;
  }
  Lp [n] = cp [n] ;
  xxx(txcount);
  int mmin=Lx.indexmin();
  int mmax=Lx.indexmax();
  for (int ii=mmin;ii<=mmax;ii++)
  {
    value(L.x(ii))=Lx(ii);
  }
  int nxcount=txcount;
  int nccount=tccount;
  int nlkicount=lkicount;
  save_identifier_string("ty");

  save_int_value(nxcount);
  save_int_value(nlkicount);
  save_int_value(nccount);

  save_identifier_string("tu");
  C.x.save_dvar_vector_position();
  save_identifier_string("wy");
  L.x.save_dvar_vector_position();
  save_identifier_string("iy");
  save_ad_pointer(&S);
  save_ad_pointer(&sparse_triplet2);
  save_identifier_string("dg");
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(dfcholeski_sparse);
  RETURN_ARRAYS_DECREMENT(); //Need this statement because the function
  return (1) ;
}

static void dfcholeski_sparse(void)
{
  verify_identifier_string("dg");
  dcompressed_triplet * sparse_triplet2  =
    ( dcompressed_triplet *) restore_ad_pointer();
  hs_symbolic & S  =
    *( hs_symbolic * ) restore_ad_pointer();
  verify_identifier_string("iy");
  dvar_vector_position dpos=restore_dvar_vector_position();
  verify_identifier_string("wy");
  dvar_vector_position cpos=restore_dvar_vector_position();
  verify_identifier_string("tu");

  int nccount=restore_int_value();
  int nlkicount=restore_int_value();
  int nxcount=restore_int_value();

  verify_identifier_string("ty");

    dvector  dfLx=restore_dvar_vector_derivatives(dpos);
    hs_smatrix A(sparse_triplet2->get_n(),
      *(sparse_triplet2) );

    //hs_symbolic& S=*(lapprox->sparse_symbolic2);
    double d;
    double lki=0;
    double dfd=0.0;
    double dflki=0.0;
    int top, i, p, k, n;
    int p2;
    n = A.n ;

    ivector cold(0,n-1);                              /* int workspace */
    ivector c(0,n-1);                              /* int workspace */
    imatrix ssave(0,n-1);                              /* int workspace */
    ivector s(0,n-1);                                   /* int workspace */
    dvector x(0,n-1) ;                        /* double workspace */
    dvector dfx(0,n-1) ;                        /* double workspace */
    dfx.initialize();

    ivector & cp=S.cp;
    ivector & pinv=S.pinv;
    ivector & parent=S.parent;

    hs_smatrix C(A);
    C = A;
    if(S.pinv[0]!=-1)
      hs_symperm(A,pinv,C);

    hs_smatrix L(S);              // Allocates cholesky factor

    ivector & Cp=C.p;
    ivector & Ci=C.i;
    dvector & Cx=C.x;
    dvector dfCx(C.x.indexmin(),Cx.indexmax());
    dfCx.initialize();

    ivector & Lp=L.p;
    ivector & Li=L.i;
    dvector & Lx=L.x;

  // counters
    int tccount=0;
    int txcount=0;
    ivector ccount(c.indexmin(),c.indexmax());
    ccount.initialize();
    ivector Licount(Li.indexmin(),Li.indexmax());
    Licount.initialize();
    ivector Lxcount(Lx.indexmin(),Lx.indexmax());
    Lxcount.initialize();
    ivector xcount(x.indexmin(),x.indexmax());
    xcount.initialize();

    int pcount=0;
    int icount=0;
    int lkicount=0;

    int p1=0;

    dvector xsave(0,nxcount);
    ivector csave(0,nccount);
    dvector lkisave(0,nlkicount);

    tccount=0;
    txcount=0;
    pcount=0;
    ccount.initialize();
    Licount.initialize();
    Lxcount.initialize();
    xcount.initialize();
    lkicount=0;

    // do it again -- this oulod be the frist time in the adjoint code
    for (k = 0 ; k < n ; k++)
    {
      Lp [k] = c [k] = cp [k] ;
      //ccount[k]++;
      //tccount++;
    }
    ivector Top(0,n);

    for (k = 0 ; k < n ; k++)            /* compute L(:,k) for L*L' = C */
    {
        /* --- Nonzero pattern of L(k,:) ------------------------------------ */
        Top(k) = cs_ereach (C, k, parent, s, c) ;

        //ssave(k)=s;
        if (allocated(ssave(k)))
        {
          cerr << "This can't happen" << endl;
          ad_exit(1);
        }
        else
        {
          ssave(k).allocate(Top(k),n-1);
        }
        ssave(k)=s(Top(k),n-1);
        x [k] = 0 ;                                    /* x (0:k) is now zero */
        //xcount[k]++;
        for (p = Cp [k] ; p < Cp [k+1] ; p++)       /* x = full(triu(C(:,k))) */
        {
          if (Ci [p] <= k)
          {
            x[Ci[p]] = Cx[p] ;
            xcount[Ci[p]]++;
          }
        }
        d = x [k] ;                        /* d = C(k,k) */
        //dcount++;
        x [k] = 0 ;                        /* clear x for k+1st iteration */
        //xcount[k]++;
        /* --- Triangular solve --------------------------------------------- */
        top=Top(k);
        for ( ; top < n ; top++)    /* solve L(0:k-1,0:k-1) * x = C(:,k) */
        {
            i = s [top] ;
            icount++;
            lkisave(lkicount++)=lki;
            lki = x [i] / Lx [Lp [i]] ; /* L(k,i) = x (i) / L(i,i) */
            xsave(txcount++)=x(i);
            x [i] = 0 ;                        /* clear x for k+1st iteration */
            for (p1 = Lp [i] + 1 ; p1 < c [i] ; p1++)
            {
               x [Li [p1]] -= Lx [p1] * lki ;
            }
            d -= lki * lki ;                /* d = d - L(k,i)*L(k,i) */
            csave(tccount++)=c[i];
            p2 = c [i] ;
            //ofs << ttc++ << " " << p2 << " 2" << endl;
            c[i]++;
            ccount[i]++;
            Li [p2] = k ;                /* store L(k,i) in column i */
            Licount[p2]++;
            if (Licount(p2)>1)
            {
              cerr << "Error unhandled case in chol" << endl;
            }
            Lx [p2] = lki ;
            Lxcount[p2]++;
            if (Lxcount(p2)>1)
            {
              cerr << "Error unhandled case in chol" << endl;
              ad_exit(1);
            }
        }
        /* --- Compute L(k,k) ----------------------------------------------- */
        if (d <= 0) return ; /* not pos def */
        csave(tccount++)=c[k];
        p = c [k];
        //ofs << ttc++ << " " << p << " 1"<< endl;
        c[k]++;
        //ccount[k]++;
        pcount++;
        Li [p] = k ;                   /* store L(k,k) = sqrt (d) in column k */
        Licount[p]++;
        if (Licount(p)>1)
        {
          cerr << "Error unhandled case in chol" << endl;
        }
        Lx [p] = sqrt (d) ;
        Lxcount[p]++;
        if (Lxcount(p)>1)
        {
          cerr << "Error unhandled case in chol" << endl;
          ad_exit(1);
        }
    }
    Lp [n] = cp [n] ;                    /* finalize L */


    // now the real adjoint code

    for (k = n-1 ; k >=0 ; k--)
    {
      c[k]=csave(--tccount);
      p=c[k];
      s(ssave(k).indexmin(),ssave(k).indexmax())=ssave(k);
      //if (k==3)
       // cout << "HERE2" << endl;
      // Lx [p] = sqrt (d) ;
      //ofs << --ttc << " " << p << " 1" << endl;

      dfd+=dfLx(p)/(2.0*Lx(p));
      dfLx(p)=0.0;

      //c[k]=csave(--tccount);
      //p=c[k];

      for (top=n-1 ; top >=Top[k] ; top--)
      {
        i=s(top);
        //Lx [p] = lki ;
        c[i]=csave(--tccount);
        p2=c[i];
        //ofs << --ttc << " " << p2 << " 2" << endl;
        dflki+=dfLx[p2];
        dfLx[p2]=0.0;
        //d -= lki * lki ;                /* d = d - L(k,i)*L(k,i) */
        dflki-=2.0*dfd*lki;
        for (p1 = Lp [i] + 1 ; p1 < c [i] ; p1++)
        {
          //x [Li [p1]] -= Lx [p1] * lki ;
          dflki-=dfx(Li(p1))*Lx(p1);
          dfLx(p1)-=dfx(Li(p1))*lki;
        }
        dfx[i]=0.0;
        // maybe not here
        x(i)=xsave(--txcount);
        // lki = x[i] / Lx[Lp[i]] ;
        dfx(i)+=dflki/Lx(Lp(i));
        dfLx(Lp(i))-=dflki*x(i)/square(Lx(Lp(i)));
        // but here
        dflki=0.0;
        lki=lkisave(--lkicount);
      }
      // x[k]=0.0;
      dfx[k]=0.0;
      //d = x [k] ;                        /* d = C(k,k) */
      dfx(k)+=dfd;
      dfd=0.0;
      for (p1 = Cp [k+1]-1 ; p1 >= Cp [k] ; p1--)
      {
        if (Ci [p1] <= k)
        {
          //x[Ci[p1]] = Cx[p1] ;
          dfCx[p1]+=dfx[Ci[p1]];
          dfx[Ci[p1]]=0.0;
        }
      }
      //x [k] = 0 ;                        /* clear x for k+1st iteration */
      dfx(k)=0.0;
    }

    dfCx.save_dvector_derivatives(cpos);

    return  ;
}

int chol(XCONST dvar_hs_smatrix &AA, XCONST hs_symbolic &T,
  dvar_hs_smatrix &LL)
{
  //ADUNCONST(hs_symbolic,S)
  //ADUNCONST(dvar_hs_smatrix,L)
  //ADUNCONST(dvar_hs_smatrix,A)
  dvar_hs_smatrix& A = (dvar_hs_smatrix&)AA;
  hs_symbolic& S = (hs_symbolic&)T;
  dvar_hs_smatrix& L = (dvar_hs_smatrix&)LL;
  int icount=0;
  dvariable lki;
  dvariable d;
  int top, i, p, k, n;
  int p1,p2;
  n = A.n ;
  ivector c(0,n-1);                              /* int workspace */
  ivector s(0,n-1);                                   /* int workspace */
  dvar_vector x(0,n-1) ;                        /* double workspace */

  ivector & cp=S.cp;
  ivector & pinv=S.pinv;
  ivector & parent=S.parent;

  dvar_hs_smatrix C(A);
  C = A;
  if(S.pinv[0]!=-1)
    hs_symperm(A,pinv,C);

  //dvar_hs_smatrix & E = C;

  ivector & Cp=C.p;
  ivector & Ci=C.i;
  dvar_vector & Cx=C.x;

  ivector & Lp=L.p;
  ivector & Li=L.i;
  dvar_vector & Lx=L.x;

  for (k = 0 ; k < n ; k++)
  {
    Lp [k] = c [k] = cp [k] ;
  }

  for (k = 0 ; k < n ; k++)
  {
    top = cs_ereach (C, k, parent, s, c) ;
    x [k] = 0 ;
    for (p = Cp [k] ; p < Cp [k+1] ; p++)
    {
      if (Ci[p] <= k) x [Ci[p]] = Cx[p] ;
    }
    d = x[k] ;
    x[k] = 0.0;
    for ( ; top < n ; top++)
    {
      i = s[top] ;
      lki = x[i] / Lx[Lp[i]] ;
      icount++;   // count the number of times lki is overwritten
      x [i] = 0 ;
      for (p1 = Lp [i] + 1 ; p1 < c [i] ; p1++)
      {
        x[Li[p1]] -= Lx[p1] * lki ;
      }
      d -= lki * lki ;
      p2 = c[i]++ ;
      Li [p2] = k ;
      Lx [p2] = lki ;
    }
    if (d <= 0) return (0) ;
    p = c[k]++ ;
    Li [p] = k ;
    Lx [p] = sqrt (d) ;
  }
  Lp [n] = cp [n] ;
  xxx(icount);
  return (1) ;
}
 //class hs_symbolic    // Info for symbolic cholesky
 //{
 //    public:
 //
 //    int n ;     // Dimension of underlying pos. def. matrix
 //    ivector pinv ;     // inverse row perm. for QR, fill red. perm for Chol
 //    ivector parent ;   // elimination tree for Cholesky and QR
 //    ivector cp ;       // column pointers for Cholesky, row counts for QR
 //    double lnz ;    // # entries in L for LU or Cholesky; in V for QR
 //
 //    hs_symbolic(int, XCONST css *);
 //    hs_symbolic(int n, XCONST dmatrix &T, int order);
 //    hs_symbolic(XCONST dcompressed_triplet &T, int order);
 //    hs_symbolic(XCONST dvar_compressed_triplet &T, int order);
 //    int is_null();
 //    int cmp(hs_symbolic &S);
 //    hs_symbolic(void);
 //};

void hs_smatrix::set_symbolic(hs_symbolic& s)
{
  sym.n=s.n;
  sym.pinv.allocate(s.pinv.indexmin(),s.pinv.indexmax());
  sym.pinv=s.pinv;
  sym.parent.allocate(s.parent.indexmin(),s.parent.indexmax());
  sym.parent=s.parent;
  sym.cp.allocate( s.cp.indexmin(),s.cp.indexmax());
  sym.cp=s.cp;
  sym.lnz=s.lnz;
}

void dvar_hs_smatrix::set_symbolic(hs_symbolic& s)
{
  sym.n=s.n;
  sym.pinv.allocate(s.pinv.indexmin(),s.pinv.indexmax());
  sym.pinv=s.pinv;
  sym.parent.allocate(s.parent.indexmin(),s.parent.indexmax());
  sym.parent=s.parent;
  sym.cp.allocate( s.cp.indexmin(),s.cp.indexmax());
  sym.cp=s.cp;
  sym.lnz=s.lnz;
}

void report_dvar_vector_derivatives(void)
{
  verify_identifier_string("jr");
  /*dvar_vector_position dpos=*/restore_dvar_vector_position();
  //dvector  dfLx=restore_dvar_vector_derivatives(dpos);
  verify_identifier_string("jx");
}


void report_derivatives(const dvar_vector& x)
{
  save_identifier_string("jx");
  x.save_dvar_vector_position();
  gradient_structure::GRAD_STACK1->
      set_gradient_stack(report_dvar_vector_derivatives);
  save_identifier_string("jr");
}

void get_inverse_sparse_hessian(dcompressed_triplet & st, hs_symbolic& S,
  uostream& ofs1,ofstream& ofs,int usize,int xsize,dvector& u)
{
  int n=st.get_n();
  hs_smatrix HS(n,st);
  hs_smatrix L(S);
  chol(HS,S,L);
  dvector gr(0,n-1);
  dvector x(0,n-1);
  gr.initialize();
  ofs1 << usize << xsize;
  int i;
  for (i=1;i<=n;i++)
  {
    gr(i-1)=1.0;
    x = cs_ipvec(S.pinv, gr);
    gr(i-1)=0.0;
    x = cs_lsolve(L,x);
    x = cs_ltsolve(L,x);
    x = cs_pvec(S.pinv,x);
    ofs << setprecision(5) << setscientific()
        << setw(14) << u(i) << " " << sqrt(x(i-1)) << endl;;
    x.shift(1);
    ofs1 << x;
    x.shift(0);
  }
}
//#include "cs.h"
/* C = A*B */
hs_smatrix cs_multiply(const hs_smatrix &AA, const hs_smatrix  &BB)
{
    //ADUNCONST(hs_smatrix,A)
    //ADUNCONST(hs_smatrix,B)
    hs_smatrix& A = (hs_smatrix&)AA;
    hs_smatrix& B = (hs_smatrix&)BB;
    int p, j, nz = 0, anz,  m, n, bnz;
    //hs_smatrix *pC ;
    //hs_smatrix C(n,anz + bnz);
    //hs_smatrix& C=*pC ;

     //  if (!CS_CSC (A) || !CS_CSC (B)) return (NULL) ;      /* check inputs */
       if (A.n != B.m) return (NULL) ;
       m = A.m ; anz = A.p[A.n] ;
       n = B.n ; ivector & Bp = B.p ; ivector & Bi = B.i ;
       dvector & Bx = B.x ; bnz = Bp[n] ;
       //w = cs_calloc (m, sizeof (int)) ;                   /* get workspace */
       ivector w(0,m);                    /* get workspace */
       //values = (A.x != NULL) && (Bx != NULL) ;
       //x = values ? cs_malloc (m, sizeof (double)) : NULL ;/* get workspace */
       dvector x(0,m);  /* get workspace */
       hs_smatrix C(n,anz + bnz) ;        /* allocate result */
       //if (!C || !w || (values && !x)) return (cs_done (C, w, x, 0)) ;
       ivector & Cp = C.p ;
       for (j = 0 ; j < n ; j++)
       {
           C.reallocate(2*(C.nzmax)+m);

           //if (nz + m > C.nzmax && !cs_sprealloc (C, 2*(C.nzmax)+m))
           //{
           //    return (cs_done (C, w, x, 0)) ;             /* out of memory */
           //}
           ivector& Ci = C.i ;
           dvector& Cx = C.x ;       /* C->i and C->x may be reallocated */
           Cp [j] = nz ;                   /* column j of C starts here */
           for (p = Bp [j] ; p < Bp [j+1] ; p++)
           {
               nz = cs_scatter (A, Bi [p], Bx[p], w, x, j+1, C, nz) ;
           }
           for (p = Cp [j] ; p < nz ; p++) Cx [p] = x [Ci [p]] ;
       }
       Cp [n] = nz ;                       /* finalize the last column of C */

    return C;
      //cs_sprealloc (C, 0) ;               /* remove extra space from C */
   //return (cs_done (C, w, x, 1)) ;     /* success; free workspace, return C */
}

hs_smatrix operator * (const hs_smatrix &A, const hs_smatrix  &B)
{
  return cs_multiply(A,B);
}
dcompressed_triplet make_dcompressed_triplet(const dmatrix & M)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  int n=mmax-mmin+1;
  int _jmin=M(mmin).indexmin();
  int _jmax=M(mmax).indexmax();
  int m=_jmax-_jmin+1;
  int ii=0;
  for (int i=mmin;i<=mmax;i++)
  {
    int jmin=M(i).indexmin();
    int jmax=M(i).indexmax();
    for (int j=jmin;j<=jmax;j++)
    {
      if (M(i,j) !=0) ii++;
    }
  }
  dcompressed_triplet dct(1,ii,n,m);
  ii=0;
  for (int i=mmin;i<=mmax;i++)
  {
    int jmin=M(i).indexmin();
    int jmax=M(i).indexmax();
    for (int j=jmin;j<=jmax;j++)
    {
      if (M(i,j) !=0)
      {
        ii++;
        dct(ii)=M(i,j);
        dct(1,ii)=i;
        dct(2,ii)=j;
      }
    }
  }
  return dct;
}
/*
extern "C"  {
  void ad_boundf(int i)
  {
    // so we can stop here
    exit(i);
  }
}
*/

hs_smatrix make_hs_smatrix(const dmatrix & M)
{
  return hs_smatrix(make_dcompressed_triplet(M));
}

ostream& operator << (const ostream& _ofs,const hs_smatrix& M)
{
  ADUNCONST(ostream,ofs)
  ofs << "nrows " << M.m << " ncols " << M.n  << " nzmax " << M.nzmax
      << endl;
  ofs << "p = " << M.p << endl;
  ofs << "i = " << M.i << endl;
  ofs << "x = " << M.x << endl;
  return ofs;
}

dmatrix make_dmatrix(const hs_smatrix& M)
{
  int n=M.m;
  int m=M.n;
  dmatrix tmp(1,n,1,m);
  tmp.initialize();
  int ii=0;
  for (int j=1;j<=m;j++)
  {
    for (int i=M.p(j-1);i<M.p(j);i++)
    {
      tmp(M.i(ii)+1,j)=M.x(ii);
      ii++;
    }
  }
  return tmp;
}


 //
 //main()
 //{
 //
 //  ad_exit=&ad_boundf;
 //  int i,j;
 //  int n=20;
 //  int n2=n*n;
 //  double alpha=0.3;
 //  double beta=0.4;
 // /*
 //  dmatrix X(1,6,1,5);
 //  X.initialize();
 //  X(1,1)=1.;
 //  X(2,1)=2.;
 //  X(6,1)=3.;
 //  X(1,3)=4.;
 //  X(2,3)=5.;
 //  X(6,3)=6.;
 //  X(5,4)=7.;
 //  dcompressed_triplet dct1=make_dcompressed_triplet(X);
 //  hs_smatrix Z0=hs_smatrix(dct1);
 //  cout << Z0 << endl;
 //  cout << X << endl;
 //  cout << norm2(X-make_dmatrix(Z0)) << endl;
 //  cout << make_dmatrix(dct1) << endl;
 //  X.initialize();
 //  X(1,1)=1.;
 //  X(2,2)=2.;
 //  X(3,3)=3.;
 //  X(3,1)=5.;
 //  X(3,2)=9.;
 //  X(3,4)=7.;
 //  dcompressed_triplet dct2=make_dcompressed_triplet(X);
 //  hs_smatrix Z2=hs_smatrix(dct2);
 //  cout << X << endl;
 //  cout << make_dmatrix(dct2) << endl;
 // */
 //
 //  dmatrix M(1,n2,1,n2);
 //  M(1,1)=1;
 //  M(1,2)=beta;
 //  for (i=2;i<n2;i++)
 //  {
 //    M(i,i-1)=alpha;
 //    M(i,i)=1;
 //    M(i,i+1)=beta;
 //  }
 //  M(n2,n2-1)=alpha;
 //  M(n2,n2)=1;
 //  //dcompressed_triplet dct=make_dcompressed_triplet(M);
 //  hs_smatrix SM=make_hs_smatrix(M);
 //  //cout << norm2(make_dmatrix(dct)-M) << endl;
 //
 //  dmatrix L(1,n2,1,n2);
 //  L.initialize();
 //  int ii=1;
 //  for (i=1;i<=n;i++)
 //  {
 //    for (j=1;j<=n;j++)
 //    {
 //       L(ii,(j-1)*n+i)=1;
 //       ii++;
 //    }
 //  }
 //  hs_smatrix SL=make_hs_smatrix(L);
 //  dmatrix Y=make_dmatrix(SM*SL);
 //
 //  cout << norm2(Y-M*L) << endl;
 //  exit(2);
 //  //cout << L << endl;
 //
 //  //cout <<  M << endl;
 //  //cout << trans(L) * M * L << endl;
 //  dmatrix N= M * trans(L) * M * L;
 //  dmatrix N2=N*trans(N);
 //  ii=0;
 //  for (i=1;i<=n2;i++)
 //  {
 //    for (j=1;j<=n2;j++)
 //    {
 //      if (fabs(N(i,j))>1.e-8) ii++;
 //    }
 //  }
 //  cout << "N num no zero " << ii << " percentage full "
 //       << ii/double(n2*n2) << endl;
 //  ii=0;
 //  for (i=1;i<=n2;i++)
 //  {
 //    for (j=1;j<=n2;j++)
 //    {
 //      if (fabs(N2(i,j))>1.e-8) ii++;
 //    }
 //  }
 //  cout << "N*trans(N) num no zero " << ii << " percentage full "
 //       << ii/double(n2*n2) << endl;
 //  //cout << setfixed() << setprecision(2) << setw(5) << N << endl;
 //}
 //
