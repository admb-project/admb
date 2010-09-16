DATA_SECTION
  init_int n
  init_matrix CM(1,n,1,n)
  init_number cv
PARAMETER_SECTION
  init_matrix VCM(1,n,1,n)
  random_effects_matrix M(1,n,1,n)
  objective_function_value f
PROCEDURE_SECTION
  f=square(myln_det(M+VCM));
  f+=0.5*square(norm2(VCM));
  f+=0.5*square(norm2(M));


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
  //cout << "1M " << endl << M << endl << endl;
   sign = clu1.get_sign();
   ivector index2 = clu1.get_index2();
   int mmin = M.indexmin();
   int mmax = M.indexmax();
   double lndet = 0.0;
   dmatrix & gamma = clu1.get_U();
   dmatrix & alpha = clu1.get_L();
  //cout << "1gamma " << endl << gamma << endl << endl;
  //cout << "1alpha " << endl << alpha << endl << endl;
   // only need to save the diagonal of gamma
   for (int i = mmin; i <= mmax; i++)
   {
      if (gamma(i, i) < 0)
      {
	 sign = -sign;
         cout << "1:gamma " << i << " " << gamma(i,i) << endl;
	 //lndet += log(-gamma(i, i));
      } else
      {
         cout << "1:gamma " << i << " " << gamma(i,i) << endl;
	 //lndet += log(gamma(i, i));
      }
   }
    cout << "lndet " << lndet << endl;
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

   //sign = clu1.get_sign();
   ivector index2 = clu1.get_index2();
   df1b2variable lndet = 0.0;
   df1b2matrix & gamma = clu1.get_U();
   df1b2matrix & alpha = clu1.get_L();

   dmatrix dmat(mmin,mmax,mmin,mmax);
   dmat = value(M);
   ln_det2(dmat,1);
  //cout << "2M " << endl << M << endl << endl;
  //cout << "2gamma " << endl << gamma << endl << endl;
  //cout << "2alpha " << endl << alpha << endl << endl;


   // only need to save the diagonal of gamma
   for (int i = mmin; i <= mmax; i++)
   {
      if (value(gamma(i, i)) < 0.0)
      {
	 //sign = -sign;
         cout << "2:gamma " << i << " " << gamma(i,i) << endl;
	 //lndet += log(-gamma(i, i));
      } else
      {
         cout << "2:gamma " << i << " " << gamma(i,i) << endl;
	 //lndet += log(gamma(i, i));
      }
   }
    cout << "lndet " << lndet << endl;
   return lndet;
  }

  dvariable myln_det(const dvar_matrix & a)
  {
   int sgn;
   return ln_det(a, sgn);
  }
