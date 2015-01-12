/**
 * Copyright (c) 2008, 2009 Regents of the University of California.
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "BSD" license
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
#include <fvar.hpp>
#define TINY 1.0e-20;
#ifdef __TURBOC__
  #pragma hdrstop
  #include <iomanip.h>
  extern unsigned _stklen=24000;
#endif

#ifdef __ZTC__
  #include <iomanip.hpp>
  unsigned _stack=24000;
#endif


double fff(dvar_vector& x);

// finds a the minimum of a funtion of the elements of
// a nsize*nize matrix
//int nsize=100; // 10,000 variables!
int nsize=10; 

int main()
{
  int nvar=nsize*nsize;
  independent_variables x(1,nvar);
  int ii=0;
  double f;
  dvector g(1,nvar);
  x.fill_randu(1001);
  // ifstream infile("matinv.est");
  // infile >> x;

  if (nvar>200)
    gradient_structure::set_MAX_NVAR_OFFSET(nvar);

 gradient_structure::set_GRADSTACK_BUFFER_SIZE(200);
 gradient_structure gs(400000L);

 fmmc fmc(nvar);
 fmc.crit1=.05;


  int ij=0;
  int ireturn=1;
  long int icount=0;
  while (fmc.ireturn>=0)
  {
    fmc.fmin(f,x,g);
    if (fmc.ireturn>0)
    {
      f=fff(x);
      cout << "f = " << f << endl;
      gradcalc(nvar,g);
    }
  }
  ofstream outfile("matinv.est");
  outfile << x << endl;
  return 0;
}

double fff(dvar_vector& x)
{
  dvar_matrix M(1,nsize,1,nsize);
  int ii=0;
  dvariable f=0.0;
  dvariable tmp=0.0;
  for (int i=1;i<=nsize;i++)
  {
    for (int j=1;j<=nsize;j++)
    {
      M[i][j]=x[++ii];
    }
    M[i][i]+=1.0;
  }
  dvar_matrix N=inv(M);
  {
    tmp=norm(M);
    f=tmp*tmp; 
  }

  {
    tmp=norm(N);
    f+=tmp*tmp; 
  }

  tmp=0.;
  for (i=1;i<=nsize;i++)
  {
    tmp+=M[i][i]*M[i][i];
  }
  f-=.01*tmp;
  tmp=0.;
  for (i=1;i<=nsize;i++)
  {
     tmp+=N[i][i]*N[i][i];
  }
  f-=.01*tmp;
  return value(f);
}

