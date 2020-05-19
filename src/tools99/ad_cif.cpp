/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Overloaded cifstream operators for autodif classes.
*/

#include <fvar.hpp>
#include "cifstrem.h"

//VECTOR_OPERATOR_DEFINE(dvector)
//VECTOR_OPERATOR_DEFINE(ivector)
//VECTOR_OPERATOR_DEFINE(lvector)

//MATRIX_OPERATOR_DEFINE(dmatrix)
//MATRIX_OPERATOR_DEFINE(imatrix)
//MATRIX_OPERATOR_DEFINE(lmatrix)


/**
Reads values into var from istr.

\param istr comment formatted input stream
\param var prevariable
*/
cifstream& operator>>(cifstream& istr, const prevariable& var)
{
  istr >> value(var);
  return istr;
}
/**
Reads values into lvec from cifstream.

\param lvec lvector
*/
cifstream& cifstream::operator>>(const lvector& lvec)
{
  if (allocated(lvec))
  {
    for (int i = lvec.indexmin(); i <= lvec.indexmax(); ++i)
    {
      *this >> lvec[i];
    }
  }
  return *this;
}
/**
Reads values into dvec from cifstream.

\param dvec dvector
*/
cifstream& cifstream::operator>>(const dvector& dvec)
{
  if (allocated(dvec))
  {
    for (int i = dvec.indexmin(); i <= dvec.indexmax(); ++i)
    {
      *this >> dvec[i];
    }
  }
  return *this;
}
/**
Reads values into dmat from istr.

\param istr comment formatted input stream
\param dmat dmatrix
*/
cifstream& operator>>(cifstream& istr, const dmatrix& dmat)
{
  if (allocated(dmat))
  {
    for (int i = dmat.indexmin(); i <= dmat.indexmax(); ++i)
    {
      istr >> dmat[i];
    }
  }
  return istr;
}
/**
Reads values into darr from istr.

\param istr comment formatted input stream
\param darr d3_array
*/
cifstream& operator>>(cifstream& istr, const d3_array& darr)
{
  if (allocated(darr))
  {
    for (int i = darr.indexmin(); i <= darr.indexmax(); ++i)
    {
      istr >> darr[i];
    }
  }
  return istr;
}
/**
Reads values into darr from istr.

\param istr comment formatted input stream
\param darr d4_array
*/
cifstream& operator>>(cifstream& istr, const d4_array& darr)
{
  if (allocated(darr))
  {
    for (int i = darr.indexmin(); i <= darr.indexmax(); ++i)
    {
      istr >> darr[i];
    }
  }
  return istr;
}
/**
Reads values into darr from istr.

\param istr comment formatted input stream
\param darr d5_array
*/
cifstream& operator>>(cifstream& istr, const d5_array& darr)
{
  if (allocated(darr))
  {
    for (int i = darr.indexmin(); i <= darr.indexmax(); ++i)
    {
      istr >> darr[i];
    }
  }
  return istr;
}
/**
Reads values into darr from istr.

\param istr comment formatted input stream
\param darr d6_array
*/
cifstream& operator>>(cifstream& istr, const d6_array& darr)
{
  if (allocated(darr))
  {
    for (int i = darr.indexmin(); i <= darr.indexmax(); ++i)
    {
      istr >> darr[i];
    }
  }
  return istr;
}
/**
Reads values into darr from istr.

\param istr comment formatted input stream
\param darr d7_array
*/
cifstream& operator>>(cifstream& istr, const d7_array& darr)
{
  if (allocated(darr))
  {
    for (int i = darr.indexmin(); i <= darr.indexmax(); ++i)
    {
      istr >> darr[i];
    }
  }
  return istr;
}
/**
Reads values into ivec from istr.

\param istr comment formatted input stream
\param ivec ivector
*/
cifstream& cifstream::operator>>(const ivector& ivec)
{
  if (allocated(ivec))
  {
    for (int i = ivec.indexmin(); i <= ivec.indexmax(); ++i)
    {
      *this >> ivec[i];
    }
  }
  return *this;
}
/**
Reads values into imat from istr.

\param istr comment formatted input stream
\param imat imatrix
*/
cifstream& operator>>(cifstream& istr, const imatrix& imat)
{
  if (allocated(imat))
  {
    for (int i = imat.indexmin(); i <= imat.indexmax(); ++i)
    {
      istr >> imat[i];
    }
  }
  return istr;
}
/**
Reads values into i3_array from istr.

\param istr comment formatted input stream
\param iarr i3_array
*/
cifstream& operator>>(cifstream& istr, const i3_array& iarr)
{
  if (allocated(iarr))
  {
    for (int i = iarr.indexmin(); i <= iarr.indexmax(); ++i)
    {
      istr >> iarr[i];
    }
  }
  return istr;
}
/**
Reads values into i4_array from istr.

\param istr comment formatted input stream
\param iarr i4_array
*/
cifstream& operator>>(cifstream& istr, const i4_array& iarr)
{
  if (allocated(iarr))
  {
    for (int i = iarr.indexmin(); i <= iarr.indexmax(); ++i)
    {
      istr >> iarr[i];
    }
  }
  return istr;
}
/**
Reads values into i5_array from istr.

\param istr comment formatted input stream
\param iarr i5_array
*/
cifstream& operator>>(cifstream& istr, const i5_array& iarr)
{
  if (allocated(iarr))
  {
    for (int i = iarr.indexmin(); i <= iarr.indexmax(); ++i)
    {
      istr >> iarr[i];
    }
  }
  return istr;
}
