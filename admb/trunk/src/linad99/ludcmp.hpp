/*
 * $Id$
 *
 * Copyright (c) 2009-2011 ADMB Foundation
 */
/**
 * \file
 * LU Decomposition classes
 */

#ifndef __LUDCMP_HPP__
#define __LUDCMP_HPP__
#include <admodel.h>

const double eps = 1.e-25;

/**
 * Description not yet available.
 * \param
 */
class cltudecomp
{
   dmatrix L;
   dmatrix U;
   ivector indx;
   ivector indx2;
   int sign;
 public:
   void initialize(void)
   {
      indx.initialize();
      indx2.fill_seqadd(indexmin(), 1);
      sign = 1;
      L.initialize();
      U.initialize();
      for (int i = L.indexmin(); i <= L.indexmax(); i++)
      {
	 L(i, i) = 1.0;
      }
   }

   cltudecomp(dmatrix & alpha, dmatrix & gamma);

   cltudecomp(void)
   {
   }

   void allocate(int lb, int ub)
   {
      indx.allocate(lb, ub);
      indx2.allocate(lb, ub);
      ivector iv(lb + 1, ub);
      iv.fill_seqadd(lb, 1);
      L.allocate(lb + 1, ub, lb, iv);
      ivector iv1(lb, ub);
      iv1.fill_seqadd(lb, 1);
      U.allocate(lb, ub, lb, iv1);
      indx2.fill_seqadd(lb, 1);
   }
   cltudecomp(int lb, int ub):indx(lb, ub), indx2(lb, ub)
   {
      ivector iv(lb + 1, ub);
      iv.fill_seqadd(lb, 1);
      L.allocate(lb + 1, ub, lb, iv);
      ivector iv1(lb, ub);
      iv1.fill_seqadd(lb, 1);
      U.allocate(lb, ub, lb, iv1);
      indx2.fill_seqadd(lb, 1);
   }

   cltudecomp & assign_value(const dvar_matrix & M)
   {
      int mmin = indexmin();
      int mmax = indexmax();

      if (mmin != M.indexmin() || mmax != M.indexmax())
      {
	 cerr << "Shape error in =" << endl;
	 ad_exit(1);
      }
      for (int i = mmin; i <= mmax; i++)
	 for (int j = mmin; j <= mmax; j++)
	    elem(i, j) = value(M(i, j));
      return *this;
   }

   dmatrix & get_L()
   {
      return L;
   }
   int indexmin()
   {
      return U.indexmin();
   }
   int indexmax()
   {
      return U.indexmax();
   }
   dmatrix & get_U()
   {
      return U;
   }
   ivector & get_index()
   {
      return indx;
   }
   ivector & get_index2()
   {
      return indx2;
   }
   int &get_sign()
   {
      return sign;
   }
   double &elem(int i, int j)
   {
      if (i > j)
	 return L(i, j);
      else
	 return U(j, i);
   }
   // overload () (int,int) to look like Numerical Recipes
   double &operator() (int i, int j)
   {
      if (i > j)
	 return L(i, j);
      else
	 return U(j, i);
   }
};

/**
 * Description not yet available.
 * \param
 */
class dvector_for_adjoint
{
   dmatrix D;
   ivector count;
 public:
   int indexmin()
   {
      return D.indexmin();
   }
   int indexmax()
   {
      return D.indexmax();
   }
   const int indexmin() const
   {
      return D.indexmin();
   }
   const int indexmax() const
   {
      return D.indexmax();
   }
   double &operator () (int i)
   {
      return D(i, count(i));
   }
   const double &operator () (int i) const
   {
      return D(i, count(i));
   }
   dvector_for_adjoint operator () (int mmin, int mmax)
   {
      return dvector_for_adjoint(D.sub(mmin, mmax), count(mmin, mmax));
   }
 dvector_for_adjoint(const dmatrix & _D, const ivector & _count):
   D(_D), count(_count)
   {
   }
};

double operator *
   (const dvector_for_adjoint & v, const dvector_for_adjoint & w);

dvector operator *(double x, const dvector_for_adjoint & w);

/**
 * Description not yet available.
 * \param
 */
class dmatrix_for_adjoint
{
   d3_array D;
   imatrix count;
 public:
   void initialize(void)
   {
      D.initialize();
      count = 1.0;
   }
   int indexmin()
   {
      return D.indexmin();
   }
   int indexmax()
   {
      return D.indexmax();
   }
   dvector_for_adjoint operator () (int i)
   {
      return dvector_for_adjoint(D(i), count(i));
   }

   void increment(int i, int j)
   {
      count(i, j)++;
      if (count(i, j) > 3)
	 cout << count(i, j) << endl;
   }
   void decrement(int i, int j)
   {
      count(i, j)--;
   }

   double &operator () (int i, int j)
   {
      return D(i, j, count(i, j));
   }
   void allocate(int lb, int ub, int l1, ivector & iv, int l2, int u2)
   {
      D.allocate(lb, ub, l1, iv, l2, u2);
      count.allocate(lb, ub, l1, iv);
      count = 1;
   }
};

/**
 * Description not yet available.
 * \param
 */
class cltudecomp_for_adjoint
{
   dmatrix_for_adjoint L;
   dmatrix_for_adjoint U;
   cltudecomp dfclu;
   dvar_matrix_position *pMpos;
   ivector indx;
   ivector indx2;
   int sign;
 public:
   void initialize(void)
   {
      pMpos = 0;
      indx.initialize();
      indx2.fill_seqadd(indexmin(), 1);
      sign = 1;
      L.initialize();
      U.initialize();
      for (int i = L.indexmin(); i <= L.indexmax(); i++)
      {
	 L(i, i) = 1.0;
      }
   }

   int indexmin()
   {
      return U.indexmin();
   }
   int indexmax()
   {
      return U.indexmax();
   }

   void ludecomp_pivot_for_adjoint_1(void);

   void ludecomp_pivot_for_adjoint_2(void);
   cltudecomp_for_adjoint(void)
   {
      pMpos = 0;
   }

   ~cltudecomp_for_adjoint()
   {
      if (pMpos)
	 delete pMpos;
   }

   void allocate(int lb, int ub, int n, int m)
   {
      indx.allocate(lb, ub);
      indx2.allocate(lb, ub);
      dfclu.allocate(lb, ub);
      ivector iv(lb + 1, ub);
      iv.fill_seqadd(lb, 1);
      L.allocate(lb + 1, ub, lb, iv, 1, n);
      ivector iv1(lb, ub);
      iv1.fill_seqadd(lb, 1);
      U.allocate(lb, ub, lb, iv1, 1, m);
   }

   cltudecomp_for_adjoint(int lb, int ub, int n, int m):indx(lb, ub),
      dfclu(lb, ub), pMpos(0)
   {
      ivector iv(lb + 1, ub);
      iv.fill_seqadd(lb, 1);
      L.allocate(lb + 1, ub, lb, iv, 1, n);
      ivector iv1(lb, ub);
      iv1.fill_seqadd(lb, 1);
      U.allocate(lb, ub, lb, iv1, 1, m);
   }

   cltudecomp & get_dfclu()
   {
      return dfclu;
   }
   dmatrix_for_adjoint & get_L()
   {
      return L;
   }
   dmatrix_for_adjoint & get_U()
   {
      return U;
   }
   ivector & get_index()
   {
      return indx;
   }
   int &get_sign()
   {
      return sign;
   }
   // overload () (int,int) to look like Numerical Recipes
   void decrement(int i, int j)
   {
      if (i > j)
	 L.decrement(i, j);
      else
	 U.decrement(j, i);
   }
   void increment(int i, int j)
   {
      if (i > j)
	 L.increment(i, j);
      else
	 U.increment(j, i);
   }
   double &operator () (int i, int j)
   {
      if (i > j)
	 return L(i, j);
      else
	 return U(j, i);
   }
   friend class double_for_assign;
};


dmatrix get_dmatrix(cltudecomp & clu);
dmatrix get_dmatrix(cltudecomp_for_adjoint & clu);
dmatrix get_lower_matrix(cltudecomp_for_adjoint & clu);
dmatrix get_upper_matrix(cltudecomp_for_adjoint & clu);
dvar_vector solve(const dvar_matrix & aa, const dvar_vector & z,
		  prevariable & ln_unsigned_det,
		  const prevariable & _sign);
#endif				//#ifndef __LUDCMP_HPP__
