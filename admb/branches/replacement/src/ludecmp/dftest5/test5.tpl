DATA_SECTION
  init_int n
  init_matrix CM(1,n,1,n)
  matrix Id
  init_number cv
 !! Id=identity_matrix(1,n);
PARAMETER_SECTION
  init_matrix VCM(1,n,1,n)
  random_effects_matrix M(1,n,1,n)
  objective_function_value f
PROCEDURE_SECTION
  dvar_matrix S=M+VCM;
  f=square(ln_det(Id+S*trans(S)));
  f+=norm2(S-2.0*Id);
  f+=0.5*(norm2(VCM));
  f+=0.5*(norm2(M));
  f+=square(VCM(n,n-1)-10.0);
  f+=square(VCM(n,n-2)-15.0);


GLOBALS_SECTION
  #include <df1b2fun.h>
  #include <fvar.hpp>
  #include "../../linad99/ludcmp.hpp"
  #include "../../df1b2-separable/df1b2ludcmp.hpp"
  df1b2ludecomp ludecomp_pivot(const df1b2matrix & M);
  cltudecomp ludecomp_pivot(const dmatrix & M);

  double ln_det2(const dmatrix & m1, const int &_sgn)
  {
   dmatrix M = m1;
   int sign = _sgn;
   cltudecomp clu1 = ludecomp_pivot(M);
   sign = clu1.get_sign();
   ivector index2 = clu1.get_index2();
   int mmin = M.indexmin();
   int mmax = M.indexmax();
   double lndet = 0.0;
   dmatrix & gamma = clu1.get_U();
   dmatrix & alpha = clu1.get_L();

   for (int i = mmin; i <= mmax; i++)
   {
      if (gamma(i, i) < 0)
      {
	 sign = -sign;
	 lndet += log(-gamma(i, i));
      } else
      {
	 lndet += log(gamma(i, i));
      }
   }
   return lndet;
  }

  df1b2variable myln_det(const df1b2matrix & m1)
  {
   int mmin = m1.indexmin();
   int mmax = m1.indexmax();

   df1b2matrix M(mmin,mmax,mmin,mmax);
   M = m1;
   //int sign = _sgn;
   df1b2ludecomp clu1 = ludecomp_pivot(M);

   int sign = clu1.get_sign();
   ivector index2 = clu1.get_index2();
   df1b2variable lndet = 0.0;
   df1b2matrix & gamma = clu1.get_U();
   df1b2matrix & alpha = clu1.get_L();

   //dmatrix dmat(mmin,mmax,mmin,mmax);
   //dmat = value(M);
   //ln_det2(dmat,1);

   // only need to save the diagonal of gamma
   for (int i = mmin; i <= mmax; i++)
   {
      if (value(gamma(i, i)) < 0.0)
      {
	 sign = -sign;
	 lndet += log(-gamma(i, i));
      } else
      {
	 lndet += log(gamma(i, i));
      }
   }
   return lndet;
  }

  dvariable myln_det(const dvar_matrix & a)
  {
   int sgn;
   return ln_det(a, sgn);
  }
