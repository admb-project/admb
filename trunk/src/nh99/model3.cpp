/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

void initial_params::copy_all_values(const dvector& x, const int& ii)
  {
    for (int i=0;i<num_initial_params;i++)
    {
      //if ((varsptr[i])->phase_start <= current_phase)
      if (withinbound(0,(varsptr[i])->phase_start,current_phase))
      {
        (varsptr[i])->copy_value_to_vector(x,ii);
      }
    }
  }

void param_init_number::copy_value_to_vector(const dvector& x, const int& ii)
  {
    ::copy_value_to_vector(*this,x,ii);
  }
void param_init_bounded_number::copy_value_to_vector(const dvector& x,
  const int& ii)
  {
    ::copy_value_to_vector(*this,x,ii);
  }

void param_init_vector::copy_value_to_vector(const dvector& x, const int& ii)
  {
    ::copy_value_to_vector(*this,x,ii);
  }

void param_init_bounded_vector::copy_value_to_vector(const dvector& x,
  const int& ii)
  {
    ::copy_value_to_vector(*this,x,ii);
  }

void param_init_matrix::copy_value_to_vector(const dvector& x, const int& ii)
  {
    ::copy_value_to_vector(*this,x,ii);
  }

void copy_value_to_vector(const prevariable& x, const dvector& _v,
  const int& _ii)
  {
    dvector& v=(dvector&) _v;
    int& ii=(int&) _ii;
    v(ii++)=value(x);
  }

void copy_value_to_vector(const dvar_vector& x, const dvector& _v,
  const int& _ii)
  {
    dvector& v=(dvector&) _v;
    int& ii=(int&) _ii;
    if (!(!(x)))
    {
      int mmin=x.indexmin();
      int mmax=x.indexmax();
      for (int i=mmin;i<=mmax;i++)
      {
        v(ii++)=value(x(i));
      }
    }
  }

void copy_value_to_vector(const dvar_matrix& x, const dvector& v, const int& ii)
  {
    if (!(!(x)))
    {
      int mmin=x.rowmin();
      int mmax=x.rowmax();
      for (int i=mmin;i<=mmax;i++)
      {
        copy_value_to_vector(x(i),v,ii);
      }
    }
  }
void copy_value_to_vector(const dvar3_array& x, const dvector& v, const int& ii)
  {
    if (!(!(x)))
    {
      int mmin=x.slicemin();
      int mmax=x.slicemax();
      for (int i=mmin;i<=mmax;i++)
      {
        copy_value_to_vector(x(i),v,ii);
      }
    }
  }
void initial_params::restore_all_values(const dvector& x, const int& ii)
  {
    for (int i=0;i<num_initial_params;i++)
    {
      //if ((varsptr[i])->phase_start <= current_phase)
      if (withinbound(0,(varsptr[i])->phase_start,current_phase))
      {
        (varsptr[i])->restore_value_from_vector(x,ii);
      }
    }
  }

void param_init_number::restore_value_from_vector(const dvector& x,
  const int& ii)
  {
    ::restore_value_from_vector(*this,x,ii);
  }

void param_init_bounded_number::restore_value_from_vector(const dvector& x,
  const int& ii)
  {
    ::restore_value_from_vector(*this,x,ii);
  }

void param_init_vector::restore_value_from_vector(const dvector& x,
  const int& ii)
  {
    ::restore_value_from_vector(*this,x,ii);
  }

void param_init_bounded_vector::restore_value_from_vector(const dvector& x,
  const int& ii)
  {
    ::restore_value_from_vector(*this,x,ii);
  }

void param_init_matrix::restore_value_from_vector(const dvector& x,
  const int& ii)
  {
    ::restore_value_from_vector(*this,x,ii);
  }

void restore_value_from_vector(const prevariable& _x, const dvector& v,
  const int& _ii)
  {
    ADUNCONST(prevariable,x)
    int& ii=(int&) _ii;
    //v(ii++)=value(x);
    x=v(ii++);
  }

void restore_value_from_vector(const dvar_vector& _x, const dvector& v,
  const int& _ii)
  {
    ADUNCONST(dvar_vector,x)
    int& ii=(int&) _ii;
    if (!(!(x)))
    {
      int mmin=x.indexmin();
      int mmax=x.indexmax();
      for (int i=mmin;i<=mmax;i++)
      {
        //v(ii++)=value(x(i));
        x(i)=v(ii++);
      }
    }
  }

void restore_value_from_vector(const dvar_matrix& x, const dvector& v,
  const int& ii)
  {
    if (!(!(x)))
    {
      int mmin=x.rowmin();
      int mmax=x.rowmax();
      for (int i=mmin;i<=mmax;i++)
      {
        restore_value_from_vector(x(i),v,ii);
      }
    }
  }

void restore_value_from_vector(dvar3_array& x, const dvector& v, const int& ii)
  {
    if (!(!(x)))
    {
      int mmin=x.slicemin();
      int mmax=x.slicemax();
      for (int i=mmin;i<=mmax;i++)
      {
        restore_value_from_vector(x(i),v,ii);
      }
    }
  }
