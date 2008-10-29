
#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include <fvar.hpp>


#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <math.h>


double auto_rand(long int& idum, int reset);
void reinitialize_auto_rand();
double randn(long int& n);

  void dvector::fill_randbi_ni(long int& n, double p)
  {
    if ( p<0 || p>1)
    {
      cerr << "Error in dvar_vector::fill_randbi proportions of"
       " successes must lie between 0 and 1\n";
      ad_exit(1);
    }
    long int nn;
    nn=n;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      if (auto_rand(nn,1)<=p)
      {
        elem(i)=1;
      }
      else
      {
        elem(i)=0;
      } 
    }
  }


  void dvector::fill_randu_ni(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=auto_rand(nn,1);
    }
  }

  void dmatrix::colfill_randu_ni(BOR_CONST int&j,long int&n)
  {
    long int nn;
    nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=auto_rand(nn,1);
    }
  }


  void dmatrix::rowfill_randu_ni(BOR_CONST int& i,long int& n)
  {
    long int nn;
    nn=n;
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=auto_rand(nn,1);
    }
  }


  void dvector::fill_randn_ni(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=randn(nn);
    }
  }

  void dmatrix::fill_randn_ni(long int& n)
  {
    long int nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i).fill_randn_ni(nn);
      nn+=2;
    }
  }

  void d3_array::fill_randn_ni(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=slicemin(); i<=slicemax(); i++)
    {
      elem(i).fill_randn_ni(nn);
      nn+=2;  
    }
  }

  void d3_array::fill_randu_ni(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=slicemin(); i<=slicemax(); i++)
    {
      elem(i).fill_randu_ni(nn);
      nn+=2;  
    }
  }


  void dmatrix::fill_randu_ni(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i).fill_randu_ni(nn);
      nn+=2;  
    }
  }


  void dmatrix::colfill_randn_ni(BOR_CONST int&j,long int&n)
  {
    long int nn;
    nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=randn(nn);
    }
  }


  void dmatrix::rowfill_randn_ni(BOR_CONST int& i,long int& n)
  {
    long int nn;
    nn=n;
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=randn(nn);
    }
  }

#undef HOME_VERSION
