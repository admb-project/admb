/*
 * $Id: df1b2ludcmp.hpp 778 2010-09-22 22:07:39Z dseiple $
 *
 * Copyright (c) 2010-2011 ADMB Foundation
 */
/**
 * LU Decomposition classes for random effects
 */
#ifndef __DF1B2LUDCMP_HPP__
#define __DF1B2LUDCMP_HPP__
#include <df1b2fun.h>

  //class stuff
  class df1b2ludecomp
  {
     df1b2matrix L;
     df1b2matrix U;
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
  
     df1b2ludecomp(df1b2matrix & alpha, df1b2matrix & gamma);
  
     df1b2ludecomp(void)
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
     df1b2ludecomp(int lb, int ub):indx(lb, ub), indx2(lb, ub)
     {
        ivector iv(lb + 1, ub);
        iv.fill_seqadd(lb, 1);
        L.allocate(lb + 1, ub, lb, iv);
        ivector iv1(lb, ub);
        iv1.fill_seqadd(lb, 1);
        U.allocate(lb, ub, lb, iv1);
        indx2.fill_seqadd(lb, 1);
     }
  
     df1b2ludecomp & assign_value(const df1b2matrix & M)
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
  
     df1b2matrix & get_L()
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
     df1b2matrix & get_U()
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
     df1b2variable &elem(int i, int j)
     {
        if (i > j)
  	 return L(i, j);
        else
  	 return U(j, i);
     }
     // overload () (int,int) to look like Numerical Recipes
     df1b2variable &operator() (int i, int j)
     {
        if (i > j)
  	 return L(i, j);
        else
  	 return U(j, i);
     }
  };
  //end class stuff

df1b2ludecomp ludecomp_pivot(const df1b2matrix & M);
df1b2vector solve(const df1b2matrix& aa,const dvector& z);
df1b2variable ln_det(const df1b2matrix & m1);
df1b2vector solve(const df1b2matrix & aa, const df1b2vector & z,
      df1b2variable & ln_unsigned_det,
      const df1b2variable & _sign);

#endif	//#ifndef __DF1B2LUDCMP_HPP__
