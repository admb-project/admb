/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "New BSD" license
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
/**
 * \file
 * Description not yet available.
 */
//#pragma hdrstop
/*
class fmmq : public fmm_control
{
private:
  dvector h;
  dvector w;
  dvector funval;

  double dmin,fbest,df;
  long int llog,n1,ic,iconv,i1,link;
  double z,zz,gys,gs,sig,gso,alpha,tot,fy,dgs;
  long int itn,icc,np,nn,is,iu,iv,ib,ifn;
  int i, j;
  double gmax;
  double fsave;
  dvector gbest;
  dvector xbest;
  dvector xsave;
  dvector gsave;
  dvector scale;
  dvector xa;
  dvector xb;
  dvector d;
  dvector ga;
  dvector gb;
  int mode;
  int igwindow;
int  ir;
int isfv;
int istart;
int istop;
double c;
double cc;
double dff;
double fa;
double fb;
double dga;
double dgb;
double stmin;
double stepbd;
double tfmin;
double gmin;
double step;
double gl1;
double gl2;
unsigned int k;
int ititle;
int print;
int ipra;
int ip;
int n;
public:
  fmmq(int nvar);
  fmmq(int nvar, const lvector& ipar);
  double minimize(const dvector& x,double (*pf)(const dvar_vector&));
  double minimize(const independent_variables & x, const dvector& c,
                  double (*pf)(const dvar_vector&, const dvector&));
  void fmin(const double& f, const dvector& x, const dvector& g);
  void va13c(const dvector& x, const double& f, const dvector& g);
};
*/

void fgcomp(const double& f, const dvector& x, const dvector& g);

void mc11b(const dvector& h, const int& n, const int& k);
void mc11e(const dvector& h, const int& n, const dvector& d, const dvector& w,
  const int& nn);

// if you pass ir by referenc it stops after the third func eval
// if you pass ir by value it runs but is wrong

void mc11a(const dvector& h, const int& n, const dvector& xb, const double& sig,
  const dvector& w, int& ir, const int& mk, const double& eps);

void mc11adp(const dvector& h, const int& n, const dvector& d, const double&,
  const dvector& , const int& ir, int& mk, const double&);

double fmax(const double& x, const double& y);
double ffmin(const double& x, const double& y);
double ffmin(const int& x, const int& y);
double mypow(double x, double p);
double dafsqrt(double x);

void fmmq_disp(int nfun, int itn, double f, double gmax, const dvector& x,
  const dvector& g);
void here(const char* place);

//  dvector xa(1,nvar);
//  dvector xb(1,nvar);
//  dvector d(1,nvar);
//  dvector ga(1,nvar);
//  dvector gb(1,nvar);
//  const int mode = 1;
//  const int igwindow = 2;
