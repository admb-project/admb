/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <df1b2fun.h>
  ostream& operator << (const ostream& _os, const df1b2variable& _x)
  {
      
    ADUNCONST(df1b2variable,x)
    ADUNCONST(ostream,os)
    os << *x.u;
   /*
    os << dvector(df1b2variable::nvar,x.u_dot+1) << endl;
    os << dvector(df1b2variable::nvar,x.u_bar+1) << endl;
    os << dvector(df1b2variable::nvar,x.u_dot_bar+1) << endl;
   */
    return os;
  }

  ostream& operator << (const ostream& _os, const df1b2vector& _x)
  {
    ADUNCONST(ostream,os)
    ADUNCONST(df1b2vector,x)
    int mmin=x.indexmin();
    int mmax=x.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      os << x(i) << " ";
    }  
    return os;
  }

  ostream& operator << (const ostream& _os, const df1b2matrix& _x)
  {
    ADUNCONST(ostream,os)
    ADUNCONST(df1b2matrix,x)
    int mmin=x.indexmin();
    int mmax=x.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      os << x(i) << " ";
      if (i<mmax) os << endl;
    }  
    return os;
  }

  ostream& operator << (const ostream& _os, const df1b2_init_number_vector& _x)
  {
    ADUNCONST(ostream,os)
    ADUNCONST(df1b2_init_number_vector,x)
    int mmin=x.indexmin();
    int mmax=x.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      os << x(i) << " ";
    }  
    return os;
  }

  ostream& operator << (const ostream& _os, 
    const df1b2_init_bounded_number_vector& _x)
  {
    ADUNCONST(ostream,os)
    ADUNCONST(df1b2_init_number_vector,x)
    int mmin=x.indexmin();
    int mmax=x.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      os << x(i) << " ";
    }  
    return os;
  }

  ostream& operator << (const ostream& _os, 
    const init_df1b2vector& _x)
  {
    ADUNCONST(ostream,os)
    ADUNCONST(init_df1b2vector,x)
    int mmin=x.indexmin();
    int mmax=x.indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      os << x(i) << " ";
    }  
    return os;
  }

