/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2014 Regents of the University of California
 */
#include <admodel.h>

void initial_params::save(const ofstream& _ofs, int prec)
{
  ofstream& ofs=(ofstream&)_ofs;
  ofs << setw(prec+6) << setshowpoint();
  for (int i=0;i<num_initial_params;i++)
  {
    (varsptr[i])->save_value(ofs,prec);
  }
}

void param_init_number::save_value(const ofstream& _ofs, int prec)
{
  ofstream& ofs=(ofstream&)_ofs;
#ifndef __ZTC__
  ofs << setprecision(prec) << dvariable(*this) << endl;
#else
  ofs << setw(prec+6) << setprecision(prec) << *this << endl;
#endif
}

void param_init_vector::save_value(const ofstream& _ofs, int prec)
{
  ofstream& ofs=(ofstream&)_ofs;
  ofs << setw(prec+6) << setprecision(prec) << dvar_vector(*this) << endl;
}

void param_init_bounded_vector::save_value(const ofstream& _ofs, int prec)
{
  ofstream& ofs=(ofstream&)_ofs;
  ofs << setw(prec+6) << setprecision(prec) << dvar_vector(*this) << endl;
}

void param_init_matrix::save_value(const ofstream& _ofs, int prec)
{
  ofstream& ofs=(ofstream&)_ofs;
  ofs << setw(prec+6) << setprecision(prec) << dvar_matrix(*this) << endl;
}

void param_init_number::save_value(const ofstream& _ofs, int prec,
  const dvector& g, int& offset)
{
  ADUNCONST(ofstream,ofs)
  ofs << label() << " "
      << setw(prec+6) << setprecision(prec) << *this << " "
      << setw(prec+6) << setprecision(prec) << g(offset++) << endl;
}

void param_init_vector::save_value(const ofstream& _ofs, int prec,
  const dvector& g, int& offset)
{
  ADUNCONST(ofstream,ofs)
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    ofs << label()
        << "(" << i << ") "
        << setw(prec+6) << setprecision(prec) << (*this)(i) << " "
        << setw(prec+6) << setprecision(prec) << g(offset++) << endl;
  }
}

void param_init_bounded_vector::save_value(const ofstream& _ofs, int prec,
  const dvector& g, int& offset)
{
  ADUNCONST(ofstream,ofs)
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    ofs << label()
        << "(" << i << ") "
        << setw(prec+6) << setprecision(prec) << (*this)(i) << " "
        << setw(prec+6) << setprecision(prec) << g(offset++) << endl;
  }
}

void initial_params::save_all(const ofstream& _ofs, int prec, const dvector& g)
{
  ADUNCONST(ofstream,ofs)
  int offset = 1;
  ofs <<"ParName"<< "   "<< "Value"<< "   " <<"Gradient"<< endl;
  for (int i = 0; i < initial_params::num_initial_params; i++)
  {
    if (withinbound(0,(varsptr[i])->phase_start,current_phase))
    {
      // ofs << i+1 <<"       ";
      (initial_params::varsptr[i])->save_value(ofs, 6, g, offset);
    }
  }
}

void param_init_matrix::save_value(const ofstream& _ofs, int prec,
  const dvector& g, int& offset)
{
  ADUNCONST(ofstream,ofs)
  int rmin=indexmin();
  int rmax=indexmax();
  for (int i=rmin;i<=rmax;i++)
  {
    int cmin=(*this)(i).indexmin();
    int cmax=(*this)(i).indexmax();
    for (int j=cmin;j<=cmax;j++)
    {
      ofs << label()
          << "(" << i << "," <<  j << ") "
          << setw(prec+6) << setprecision(prec) << (*this)(i,j) << " "
          << setw(prec+6) << setprecision(prec) << g(offset++) << endl;
    }
  }
}
