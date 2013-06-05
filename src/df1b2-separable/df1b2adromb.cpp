
/*
 * $Id: df1b2fun.cpp 494 2012-06-13 20:41:16Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <df1b2fun.h>
  const int JMAX=50;
  void function_minimizer::trapzd(
    df1b2variable (df1b2_parameters::*func)(const df1b2variable&),
    const double a,
    const double b, const df1b2variable& _ss,int n)
  {
    ADUNCONST(df1b2variable,ss)

    double x,num_interval,hn;
    df1b2variable sum;
    static df1b2variable s;
    static int interval;
    int j;

    df1b2_parameters * ptr= (df1b2_parameters *) mycast();
 
    if (n == 1) {
      interval=1;
      s=0.5*(b-a)*
        ((ptr->*func)(df1b2variable(a))+(ptr->*func)(df1b2variable(b)));
      ss=s;
    } else {
      num_interval=interval;
      hn=(b-a)/num_interval;
      x=a+0.5*hn;
      for (sum=0.0,j=1;j<=interval;j++,x+=hn) sum += (ptr->*func)(x);
      interval *= 2;
      s=0.5*(s+(b-a)*sum/num_interval);
      ss=s;
    }
  }

  void function_minimizer::trapzd(
    df1b2variable (df1b2_parameters::*func)(const df1b2variable&,void *),
    const double a,
    const double b, const df1b2variable& _ss,void *ptr1,int n)
  {
    ADUNCONST(df1b2variable,ss)

    double x,num_interval,hn;
    df1b2variable sum;
    //static df1b2variable s;
    static int interval;
    int j;

    df1b2_parameters * ptr= (df1b2_parameters *) mycast();
  
    if (n == 1) {
      interval=1;
      ss=0.5*(b-a)*
        ((ptr->*func)(df1b2variable(a),ptr1)
           +(ptr->*func)(df1b2variable(b),ptr1));
    } else {
      num_interval=interval;
      hn=(b-a)/num_interval;
      x=a+0.5*hn;
      for (sum=0.0,j=1;j<=interval;j++,x+=hn) sum += (ptr->*func)(x,ptr1);
      interval *= 2;
      ss=0.5*(ss+(b-a)*sum/num_interval);
    }
  }

  void function_minimizer::adromb(
     df1b2variable (df1b2_parameters::*func)(const df1b2variable&),
     double a,double b,const df1b2variable& _v,int ns)
  {
    ADUNCONST(df1b2variable,v)
    const double base = 4;
    int MAXN = min(JMAX, ns);
    df1b2vector s(1,MAXN+1);
  
    for(int j=1; j<=MAXN+1; j++)
    {
      trapzd(func,a,b,s[j],j);
    }
  
    for(int iter=1; iter<=MAXN+1; iter++)
    {
      for(int j=1; j<=MAXN+1-iter; j++)
      {
        s[j] = (pow(base,iter)*s[j+1]-s[j])/(pow(base,iter)-1);
      }
    }
    v=s[1];
  }

  void function_minimizer::adromb(
     df1b2variable (df1b2_parameters::*func)(const df1b2variable&,void *ptr),
     double a,double b,const df1b2variable& _v,void * ptr,int ns)
  {
    ADUNCONST(df1b2variable,v)
    const double base = 4;
    int MAXN = min(JMAX, ns);
    df1b2vector s(1,MAXN+1);
    df1b2variable ss;
  
    for(int j=1; j<=MAXN+1; j++)
    {
      trapzd(func,a,b,s[j],ptr,j);
    }
  
    for(int iter=1; iter<=MAXN+1; iter++)
    {
      for(int j=1; j<=MAXN+1-iter; j++)
      {
        s[j] = (pow(base,iter)*s[j+1]-s[j])/(pow(base,iter)-1);
      }
    }
    v=s[1];
  }

