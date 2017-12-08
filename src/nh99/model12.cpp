/**
 * Author: David Fournier
 * Copyright (c) 2008-2014 Regents of the University of California
 */
#include <admodel.h>

/**
Write values of param_init_number into output stream _ofs.

\param _ofs output stream
\param precision sets the floating point precision
*/
void initial_params::save(
  const ofstream& _ofs,
  int precision)
{
  ofstream& ofs=(ofstream&)_ofs;
  ofs << setw(precision+6) << setshowpoint();
  for (int i=0;i<num_initial_params;i++)
  {
    (varsptr[i])->save_value(ofs,precision);
  }
}
/**
Write values of param_init_number into output stream _ofs.

\param _ofs output stream
\param precision sets the floating point precision
*/
void param_init_number::save_value(
  const ofstream& _ofs,
  int precision)
{
  ofstream& ofs=(ofstream&)_ofs;
#ifndef __ZTC__
  ofs << setprecision(precision) << dvariable(*this) << endl;
#else
  ofs << setw(precision+6) << setprecision(precision) << *this << endl;
#endif
}
/**
Write values of param_init_matrix into output stream _ofs.

\param _ofs output stream
\param precision sets the floating point precision
*/
void param_init_vector::save_value(
  const ofstream& _ofs,
  int precision)
{
  ofstream& ofs=(ofstream&)_ofs;
  ofs << setw(precision+6) << setprecision(precision) << dvar_vector(*this) << endl;
}
/**
Write values of param_init_matrix  into output stream _ofs.

\param _ofs output stream
\param precision sets the floating point precision
*/
void param_init_bounded_vector::save_value(
  const ofstream& _ofs,
  int precision)
{
  ofstream& ofs=(ofstream&)_ofs;
  ofs << setw(precision+6) << setprecision(precision) << dvar_vector(*this) << endl;
}
/**
Write values of param_init_matrix  into output stream _ofs.

\param _ofs output stream
\param precision sets the floating point precision
*/
void param_init_matrix::save_value(
  const ofstream& _ofs,
  int precision)
{
  ofstream& ofs = (ofstream&)_ofs;
  ofs << setw(precision+6) << setprecision(precision) << dvar_matrix(*this) << endl;
}
/**
Write values of g into output stream _ofs, then update offset
index to the next set of data.

\param _ofs output stream
\param precision sets the floating point precision
\param g the data to output
\param offset beginning index for g for param_init_matrix
*/
void param_init_number::save_value(
  const ofstream& _ofs,
  int precision,
  const dvector& g,
  int& offset)
{
  ADUNCONST(ofstream,ofs)
  ofs << label() << " "
      << setw(precision+6) << setprecision(precision) << *this << " "
      << setw(precision+6) << setprecision(precision) << g(offset++) << endl;
}
/**
Write values of g into output stream _ofs, then update offset
index to the next set of data.

\param _ofs output stream
\param precision sets the floating point precision
\param g the data to output
\param offset beginning index for g for param_init_matrix
*/
void param_init_vector::save_value(
  const ofstream& _ofs,
  int precision,
  const dvector& g,
  int& offset)
{
  ADUNCONST(ofstream,ofs)
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    ofs << label()
        << "(" << i << ") "
        << setw(precision+6) << setprecision(precision) << (*this)(i) << " "
        << setw(precision+6) << setprecision(precision) << g(offset++) << endl;
  }
}
/**
Write values of g into output stream _ofs, then update offset
index to the next set of data.

\param _ofs output stream
\param precision sets the floating point precision
\param g the data to output
\param offset beginning index for g for param_init_matrix
*/
void param_init_bounded_vector::save_value(
  const ofstream& _ofs,
  int precision,
  const dvector& g,
  int& offset)
{
  ADUNCONST(ofstream,ofs)
  int mmin=indexmin();
  int mmax=indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    ofs << label()
        << "(" << i << ") "
        << setw(precision+6) << setprecision(precision) << (*this)(i) << " "
        << setw(precision+6) << setprecision(precision) << g(offset++) << endl;
  }
}
/**
Write all values of g into output stream _ofs.

**Note:** precision is hardcoded to 6.

\param _ofs output stream
\param precision sets the floating point precision
\param g the data to output
*/
void initial_params::save_all(
  const ofstream& _ofs,
  int precision,
  const dvector& g)
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
/**
Write values of g into output stream _ofs, then update offset
index to the next set of data.

\param _ofs output stream
\param precision sets the floating point precision
\param g the data to output
\param offset beginning index for g for param_init_matrix
*/
void param_init_matrix::save_value(
  const ofstream& _ofs,
  int precision,
  const dvector& g,
  int& offset)
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
          << setw(precision+6) << setprecision(precision) << (*this)(i,j) << " "
          << setw(precision+6) << setprecision(precision) << g(offset++) << endl;
    }
  }
}
