/**
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California
 * 
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "BSD" license.
 * 
 * License:
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2.  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * 3.  Neither the name of the  University of California, Otter Research,
 * nor the ADMB Foundation nor the names of its contributors may be used
 * to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#define HOME_VERSION
#include <math.h>
#include <fvar.hpp>

#ifdef __TURBOC__
  #include <iostream.h>
  #undef __ZTC__
  #define __USE_IOSTREAM__
#endif

#ifdef __ZTC__
  #include <stream.hpp>
  #undef __USE_IOSTREAM__
#endif

#define M1 714025
#define IA1 1366 
#define IC1 150889 
#define RM1 (1.0/M1)
#define M3 134456
#define IA3 8121
#define IC3 28411
#define M2 243000
#define IA2 4561
#define IC2 51349
#define RM2 (1.0/M2)

double auto_rand(long int& idum, int reset);

void reinitialize_auto_rand()
{
  auto_rand(1,-1);
}

double auto_rand(long int& idum, int reset)
{
  static long ix1,ix2,ix3;
  static float r[108];
  double temp;
  static int iff=0;
  int j;
  long int iu;

  if (reset < 0) 
  {
    iff =0;
    return .5;
  }

  if (idum < 0 || iff == 0)
  {
    iff=2;
    ix1=(IC1-(idum))%M1;
    ix1=ix1 % M1;


    ix1=(IA1*ix1+IC1);
    ix1=ix1 % M1;

    ix2=ix1 % M2;
    ix1=(IA1*ix1+IC1);
    ix1=ix1 % M1;
    ix3=ix1 % M3;
    for (j=1;j<=107;j++) 
    {
      ix2=(IA2*ix2+IC2) % M2;
      ix1=(IA1*ix1+IC1);
              ix1=ix1 % M1;
          
      iu=ix2*RM2;
      r[j]=(ix1+iu)*RM1;
    }
  }
  idum =6;

  ix3=(IA3*ix3+IC3) % M3;
  ix3=ix3 % M3;
  ix1=(IA1*ix1+IC1) % M1;
  ix1=ix1 % M1;
  ix2=(IA2*ix2+IC2) % M2;
  ix2=ix2 % M2;
  j=1 + ((107*ix3)/M3);
  if (j > 107 || j < 1) cerr << " Error in random number generator\n"; 
  temp=r[j];
  r[j]=ix2*RM2;
  r[j]=(ix1+r[j]);
  r[j]=r[j]*RM1;
  return temp;
}

#undef M1
#undef IA1
#undef IC1
#undef RM1
#undef M2
#undef IA2
#undef IC2
#undef RM2
#undef M3
#undef IA3
#undef IC3

double randn(long int& n)
{
  long int nn;
  nn=n;
  double x,y;
  x=auto_rand(nn,1);
  y=auto_rand(nn,1);
  double u=sqrt(-2*log(x))*cos(2*PI*y);
  return(u);
}
  

  void dvar_vector::fill_randu(long int& n)
  {
    long int nn;
    RETURN_ARRAYS_INCREMENT();
    nn=n;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=auto_rand(nn,1);
    }
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }


  void dvar_vector::fill_randbi(long int& n, double p)
  {
    if ( p<0 || p>1)
    {
      cerr << "Error in dvar_vector::fill_randbi proportions of"
       " successes must lie between 0 and 1\n";
      exit(1);
    }
    long int nn;
    RETURN_ARRAYS_INCREMENT();
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
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }


  void dvector::fill_randbi(long int& n, double p)
  {
    if ( p<0 || p>1)
    {
      cerr << "Error in dvar_vector::fill_randbi proportions of"
       " successes must lie between 0 and 1\n";
      exit(1);
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
    reinitialize_auto_rand();
  }


  void dvector::fill_randu(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=auto_rand(nn,1);
    }
    reinitialize_auto_rand();
  }


  void dvar_matrix::colfill_randu(int&j,long int&n)
  {
    long int nn;
    RETURN_ARRAYS_INCREMENT();
    nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=auto_rand(nn,1);
    }
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }


  void dvar_matrix::rowfill_randu(int& i,long int& n)
  {
    long int nn;
    RETURN_ARRAYS_INCREMENT();
    nn=n;
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=auto_rand(nn,1);
    }
    RETURN_ARRAYS_DECREMENT();
    reinitialize_auto_rand();
  }


  void dmatrix::colfill_randu(int&j,long int&n)
  {
    long int nn;
    nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=auto_rand(nn,1);
    }
    reinitialize_auto_rand();
  }


  void dmatrix::rowfill_randu(int& i,long int& n)
  {
    long int nn;
    nn=n;
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=auto_rand(nn,1);
    }
    reinitialize_auto_rand();
  }


  void dvar_vector::fill_randn(long int& n)
  {
    long int nn;
    RETURN_ARRAYS_INCREMENT();
    nn=n;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=randn(nn);
    }
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }


  void dvector::fill_randn(long int& n)
  {
    long int nn;
    nn=n;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
      elem(i)=randn(nn);
    }
    reinitialize_auto_rand();
  }


  void dvar_matrix::colfill_randn(int&j,long int&n)
  {
    long int nn;
    RETURN_ARRAYS_INCREMENT();
    nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=randn(nn);
    }
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }


  void dvar_matrix::rowfill_randn(int& i,long int& n)
  {
    long int nn;
    RETURN_ARRAYS_INCREMENT();
    nn=n;
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=randn(nn);
    }
    reinitialize_auto_rand();
    RETURN_ARRAYS_DECREMENT();
  }


  void dmatrix::colfill_randn(int&j,long int&n)
  {
    long int nn;
    nn=n;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=randn(nn);
    }
    reinitialize_auto_rand();
  }


  void dmatrix::rowfill_randn(int& i,long int& n)
  {
    long int nn;
    nn=n;
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=randn(nn);
    }
    reinitialize_auto_rand();
  }

  double std_dev(dvector& v)
  {
    double tmp;
    tmp=norm(v)/sqrt(v.size());
    double tmp1;
    tmp1=mean(v);
    return(sqrt(tmp*tmp-tmp1*tmp1));
  }


  dvariable std_dev(dvar_vector& v)
  {
    dvariable tmp;
    RETURN_ARRAYS_INCREMENT();
    tmp=norm(v)/sqrt(v.size());
    dvariable tmp1;
    tmp1=mean(v);
    RETURN_ARRAYS_DECREMENT();
    return(sqrt(tmp*tmp-tmp1*tmp1));
  }

  double mean(dvector& v)
  {
    double tmp=0;
    for (int i=v.indexmin(); i<=v.indexmax(); i++)
    {
      tmp+=v.elem(i);
    }
    return(tmp/v.size());
  }


  dvariable mean(dvar_vector& v)
  {
    dvariable tmp;
    RETURN_ARRAYS_INCREMENT();
    tmp=0;
    for (int i=v.indexmin(); i<=v.indexmax(); i++)
    {
      tmp+=v.elem(i);
    }
    RETURN_ARRAYS_DECREMENT();
    return(tmp/v.size());
  }


  void dvar_vector::fill_seqadd(double& base, double& offset)
  {
    RETURN_ARRAYS_INCREMENT();
    double temp=0;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
       elem(i)=base+temp;
       temp=temp+offset;
    }
    RETURN_ARRAYS_DECREMENT();
  }

  void dvector::fill_seqadd(double& base, double& offset)
  {
    double temp=0;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
       elem(i)=base+temp;
       temp=temp+offset;
    }
  }


  void ivector::fill_seqadd(int& base, int& offset)
  {
    int temp=0;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
       elem(i)=base+temp;
       temp=temp+offset;
    }
  }


  void lvector::fill_seqadd(long int& base, long int& offset)
  {
    long int temp=0;
    for (int i=indexmin(); i<=indexmax(); i++)
    {
       elem(i)=base+temp;
       temp=temp+offset;
    }
  }


  void dvar_matrix::colfill_seqadd(int& j,double& base, double& offset)
  {
    double temp=0;
    RETURN_ARRAYS_INCREMENT();
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=base+temp;
      temp=temp+offset;
    }
    RETURN_ARRAYS_DECREMENT();
  }


  void dvar_matrix::rowfill_seqadd(int& i,double& base, double& offset)
  {
    double temp=0;
    RETURN_ARRAYS_INCREMENT();
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=base+temp;
      temp=temp+offset;
    }
    RETURN_ARRAYS_DECREMENT();
  }


  void dmatrix::colfill_seqadd(int& j,double& base, double& offset)
  {
    double temp=0;
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      elem(i,j)=base+temp;
      temp=temp+offset;
    }
  }


  void dmatrix::colfill(int& j,dvector& v)
  {
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      (*this)[i][j]=v[i];
    }
  }


  void dvar_matrix::colfill(int& j,dvar_vector& v)
  {
    RETURN_ARRAYS_INCREMENT();
    for (int i=rowmin(); i<=rowmax(); i++)
    {
      (*this)[i][j]=v[i];
    }
    RETURN_ARRAYS_DECREMENT();
  }

  void dmatrix::rowfill(int& i,dvector& v)
  {
    for (int j=colmin(); j<=colmax(); j++)
    {
      (*this)[i][j]=v[j];
    }
  }



  void dvar_matrix::rowfill(int& i,dvar_vector& v)
  {
    RETURN_ARRAYS_INCREMENT();
    for (int j=colmin(); j<=colmax(); j++)
    {
      (*this)[i][j]=v[j];
    }
    RETURN_ARRAYS_DECREMENT();
  }




  void dmatrix::rowfill_seqadd(int& i,double& base, double& offset)
  {
    double temp=0;
    for (int j=colmin(); j<=colmax(); j++)
    {
      elem(i,j)=base+temp;
      temp=temp+offset;
    }
  }
#undef HOME_VERSION
