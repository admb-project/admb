/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_vector::allocate(int mmin,int mmax,const adstring&s)
{
  allocate(mmin,mmax,1,s);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_vector::allocate(int mmin,int mmax,int ps,const adstring&s)
{
  set_phase_start(ps);
  df1b2vector::allocate(mmin,mmax);
}

/**
 * Description not yet available.
 * \param
 */
void initial_df1b2params::add_to_list(void)
{
  if (num_initial_df1b2params>=1000)
  {
    cerr << " This version of ADMB only supports 1000 initial df1b2parameter"
      " objects" << endl;
    ad_exit(1);
  }
  varsptr[num_initial_df1b2params++]= this;
}

/**
 * Description not yet available.
 * \param
 */
void initial_df1b2params::reset(const init_df1b2vector& x,
  const df1b2variable& _pen)
{
  ADUNCONST(df1b2variable,pen)
  //df1b2variable::nvar=global_nvar;
  pen=0.0;
  df1b2variable pen1=0.0;
  int ii=1;
  for (int i=0;i<num_initial_df1b2params;i++)
  {
    if (withinbound(0,(varsptr[i])->phase_start,current_phase))
    {
      (varsptr[i])->set_value(x,ii,pen1);
    }
  }
  pen+=pen1;
}

/**
 * Description not yet available.
 * \param
 */
int initial_df1b2params::set_index(void)
{
  int ii=1;
  for (int i=0;i<num_initial_df1b2params;i++)
  {
    if (withinbound(0,(varsptr[i])->phase_start,current_phase))
    {
      (varsptr[i])->set_index(1,ii);
    }
    else
    {
      (varsptr[i])->set_index(0,ii);
    }
  }
  return ii-1;
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_vector::set_value(const init_df1b2vector& _x,
  const int& _ii,const df1b2variable& pen)
{
  ADUNCONST(init_df1b2vector,x)
  ADUNCONST(int,ii)

  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    (*this)(i) = (x(ii++));
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_vector::set_index(int aflag,const int& _ii)
{
  ADUNCONST(int,ii)

  int mmin=indexmin();
  int mmax=indexmax();
  if (aflag)
  {
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i).get_ind_index() = ii++;
    }
  }
  else
  {
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i).get_ind_index() = -1;
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_number::set_index(int aflag,const int& _ii)
{
  ADUNCONST(int,ii)
  if (aflag)
  {
    get_ind_index()=ii++;
  }
  else
  {
    get_ind_index()=-1;
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_matrix::set_index(int aflag,const int& _ii)
{
  ADUNCONST(int,ii)

  int rmin=indexmin();
  int rmax=indexmax();
  if (aflag)
  {
    for (int i=rmin;i<=rmax;i++)
    {
      int cmin=(*this)(i).indexmin(); 
      int cmax=(*this)(i).indexmax(); 
      {
        for (int j=cmin;j<=cmax;j++)
        {
          (*this)(i,j).get_ind_index() = ii++;
        }
      }
    }
  }
  else
  {
    for (int i=rmin;i<=rmax;i++)
    {
      int cmin=(*this)(i).indexmin(); 
      int cmax=(*this)(i).indexmax(); 
      {
        for (int j=cmin;j<=cmax;j++)
        {
          (*this)(i,j).get_ind_index() = -1;
        }
      }
    }
  }
}

/**
 * Description not yet available.
 * \param
 */  
void df1b2_init_matrix::set_value(const init_df1b2vector& _x,
  const int& _ii,const df1b2variable& pen)
{
  ADUNCONST(init_df1b2vector,x)
  ADUNCONST(int,ii)

  int rmin=indexmin();
  int rmax=indexmax();
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=(*this)(i).indexmin(); 
    int cmax=(*this)(i).indexmax(); 
    {
      for (int j=cmin;j<=cmax;j++)
      {
        (*this)(i,j) = (x(ii++));
      }
    }
  }
}

/**
 * Description not yet available.
 * \param
 */  
void df1b2_init_number::set_value(const init_df1b2vector& _x,const int& _ii,
    const df1b2variable& pen)
{
  ADUNCONST(init_df1b2vector,x)
  ADUNCONST(int,ii)
  operator = (x(ii++));
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_number::allocate(const adstring& s)
{
  if (!df1b2variable::noallocate)
  {
    df1b2variable::allocate();
  }
  set_phase_start(1);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_number::allocate(int _n,const adstring& s)
{
  df1b2variable::allocate();
  set_phase_start(_n);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2variable::allocate(const char *s)
{
  df1b2variable::allocate();
}

/**
 * Description not yet available.
 * \param
 */
df1b2_init_number::df1b2_init_number() :  df1b2variable(do_naught_kludge_a)
{ 
  //cout << "Here" << endl;
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_number::operator = (const df1b2variable& _x) 
{
  df1b2variable::operator = (_x);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_number::allocate(double _minb,double _maxb,
 int _n,const char * s) 
{
  minb=_minb;
  maxb=_maxb;
  df1b2_init_number::allocate(s);

  set_phase_start(_n);
}

/**
 * Description not yet available.
 * \param
 */  
void df1b2_init_bounded_number::allocate(double _minb,
  double _maxb,const char * s) 
{
  minb=_minb;
  maxb=_maxb;
  df1b2_init_number::allocate(s);
  set_phase_start(1);
}

/**
 * Description not yet available.
 * \param
 */  
void df1b2_init_bounded_number::set_value(const init_df1b2vector& _x,
  const int& _ii,const df1b2variable& pen)
{
  ADUNCONST(init_df1b2vector,x)
  ADUNCONST(int,ii)
  ::set_value(*this,x,ii,minb,maxb,pen);
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const df1b2variable& _u,const init_df1b2vector& _x,
  const int& _ii,double fmin,double fmax,const df1b2variable& _fpen)
{
  ADUNCONST(init_df1b2vector,x)
  ADUNCONST(int,ii)
  ADUNCONST(df1b2variable,u)
  ADUNCONST(df1b2variable,fpen)
  if (!initial_params::straight_through_flag)
  {
    u=boundp(x(ii++),fmin,fmax,fpen);
  }
  else
  {
    u=x(ii);
    value(u)=boundp(value(x(ii++)),fmin,fmax);
    double diff=fmax-fmin;
    //t=fmin + diff*ss;
    df1b2variable ss=(u-fmin)/diff;
#   ifdef USE_BARD_PEN
      const double l4=log(4.0);
      double pen=.000001/diff;
      fpen-=pen*(log(ss+1.e-40)+log((1.0-ss)+1.e-40)+l4);
#   else 
          XXXX
#   endif
  }
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable boundp(const df1b2variable& x, double fmin, double fmax,
  const df1b2variable& _fpen)
{
  ADUNCONST(df1b2variable,fpen)
  df1b2variable t;
  //df1b2variable y;
  //y=x;
  double diff=fmax-fmin;
  const double l4=log(4.0);
  df1b2variable ss=0.49999999999999999*sin(x*1.57079632679489661)+0.50;
  t=fmin + diff*ss;

#ifdef USE_BARD_PEN
  double pen=.000001/diff;
  fpen-=pen*(log(ss+1.e-40)+log((1.0-ss)+1.e-40)+l4);
#else 
  if (x < -.9999)
  {
    fpen+=cube(-0.9999-x);
    if (x < -1.)
    {
      fpen+=1.e+6*cube(-1.0-x);
      if (x < -1.02)
      {
        fpen+=1.e+10*cube(-1.02-x);
      }
    }
  }
  if (x > 0.9999)
  {
    fpen+=cube(x-0.9999);
    if (x > 1.)
    {
      fpen+=1.e+6*cube(x-1.);
      if (x > 1.02)
      {
        fpen+=1.e+10*cube(x-1.02);
      }
    }
  }
#endif
  return(t);
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable boundp(const df1b2variable& x, double fmin, double fmax)
{
  df1b2variable t;
  //df1b2variable y;
  //y=x;
  double diff=fmax-fmin;
  df1b2variable ss=0.49999999999999999*sin(x*1.57079632679489661)+0.50;
  t=fmin + diff*ss;

  return(t);
}

/**
 * Description not yet available.
 * \param
 */
void set_value_mc(const df1b2vector& _x,const init_df1b2vector& _v, const int& _ii,
  double fmin,double fmax)
{
  ADUNCONST(int,ii)
  ADUNCONST(df1b2vector,x)
  ADUNCONST(init_df1b2vector,v)
  int min=x.indexmin();
  int max=x.indexmax();
  for (int i=min;i<=max;i++)
  {
    //x(i)=boundp(v(ii++),fmin,fmax,fpen);
    const double pinv=1./3.1415927;
    df1b2variable y=atan(v(ii++))*pinv+0.5;
    x(i)=fmin+(fmax-fmin)*y;
  }
}

/**
 * Description not yet available.
 * \param
 */
void set_value(const df1b2vector& _x,const init_df1b2vector& _v, const int& _ii,
  double fmin,double fmax,const df1b2variable& fpen)
{
  ADUNCONST(int,ii)
  ADUNCONST(df1b2vector,x)
  ADUNCONST(init_df1b2vector,v)
  int min=x.indexmin();
  int max=x.indexmax();
  for (int i=min;i<=max;i++)
  {
    x(i)=boundp(v(ii++),fmin,fmax,fpen);
    //cout << setprecision(15) << fpen << " " << fmin << " " << fmax
     //  << " " << v(ii-1) << " " << x(i) << endl; 
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_vector::set_value(const init_df1b2vector& _x,
  const int& ii,const df1b2variable& pen)
{
  init_df1b2vector& x=(init_df1b2vector&) _x;
  if (initial_params::mc_phase)
  {
    ::set_value_mc(*this,x,ii,minb,maxb);
  }
  else
  {
    ::set_value(*this,x,ii,minb,maxb,pen);
  }

}

/**
 * Description not yet available.
 * \param
 */
re_df1b2_init_bounded_vector::re_df1b2_init_bounded_vector(void)
{
  initial_df1b2params::have_bounded_random_effects=1;
}

/**
 * Description not yet available.
 * \param
 */
void re_df1b2_init_bounded_vector::set_value(const dvector& _x,
  const int& _ii)
{
  df1b2_init_bounded_vector::set_value(_x,_ii);
}

/**
 * Description not yet available.
 * \param
 */
void re_df1b2_init_bounded_vector::set_value(const init_df1b2vector& _x,
  const int& _ii,const df1b2variable& _pen)
{
  ADUNCONST(int,ii)
  ADUNCONST(df1b2variable,pen)
  init_df1b2vector& x=(init_df1b2vector&) _x;
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    df1b2variable& y=df1b2vector::operator()(i);
    if (!initial_params::straight_through_flag)
    {
      y = (boundp(x(ii++),getminb(),getmaxb(),pen));
    }
    else
    {
      y = (x(ii++));
      *y.get_u()=boundp(*y.get_u(),getminb(),getmaxb());
      double diff=getmaxb()-getminb();
      df1b2variable ss=(y-getminb())/diff;
#     ifdef USE_BARD_PEN
        const double l4=log(4.0);
        double wght=.000001/diff;
        pen-=wght*(log(ss+1.e-40)+log((1.0-ss)+1.e-40)+l4);
#     else 
       XXXX
#     endif
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_dev_vector::set_value(const init_df1b2vector& x,
  const int& ii,const df1b2variable& _pen)
{
  ADUNCONST(df1b2variable,pen);
  df1b2_init_bounded_vector::set_value(x,ii,pen);
  df1b2variable m=mean(*this);
  pen+=1000.0*square(m);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_vector::allocate(int mmin,int mmax,
  double _minb,double _maxb)
{
  minb=_minb;
  maxb=_maxb;
  df1b2_init_vector::allocate(mmin,mmax);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_vector::allocate(int mmin,int mmax,
  double _minb,double _maxb,const char * s)
{
  allocate(mmin,mmax,_minb,_maxb);
}

/**
 * Description not yet available.
 * \param
 */
void df1b2_init_bounded_vector::allocate(int mmin,int mmax,
  double _minb,double _maxb,int n,const char * s)
{
  allocate(mmin,mmax,_minb,_maxb);
  set_phase_start(n);
}

/**
 * Description not yet available.
 * \param
 */
int active(const df1b2_init_vector& x)
{
   if (x.current_phase >= x.phase_start)
     return 1;
   else
     return 0;
}

/**
 * Description not yet available.
 * \param
 */
int active(const df1b2_init_number& x)
{
   if (x.current_phase >= x.phase_start)
     return 1;
   else
     return 0;
}

/**
 * Description not yet available.
 * \param
 */
int active(const df1b2_init_matrix& x)
{
   if (x.current_phase >= x.phase_start)
     return 1;
   else
     return 0;
}

/**
 * Description not yet available.
 * \param
 */
void random_effects_bounded_vector_info::set_value
  (const init_df1b2vector& _x,const int& _ii,const df1b2variable& _pen)
{
  ADUNCONST(int,ii)
  ADUNCONST(init_df1b2vector,x)
  ADUNCONST(df1b2variable,pen);
  df1b2variable& y=pv->df1b2vector::operator()(i);
  if (!initial_params::straight_through_flag)
  {
    // df1b2variable& tmp = boundp(x(ii++),b.getminb(),b.getmaxb(),pen);
    // df1b2variable::operator = (tmp);
    //df1b2variable::operator = 
    y = (boundp(x(ii++),pv->getminb(),pv->getmaxb(),pen));
  }
  else
  {
    y = (x(ii++));
    *y.get_u()=boundp(*y.get_u(),pv->getminb(),pv->getmaxb());
    double diff=pv->getmaxb()-pv->getminb();
    df1b2variable ss=(y-pv->getminb())/diff;
#   ifdef USE_BARD_PEN
      const double l4=log(4.0);
      double wght=.000001/diff;
      pen-=wght*(log(ss+1.e-40)+log((1.0-ss)+1.e-40)+l4);
#   else 
     XXXX
#   endif
  }
}
