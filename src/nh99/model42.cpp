/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

void copy_value_from_vector(const double& _sd,const dvector& x,const int & _ii)
{
  double& sd = (double&) _sd;
  int& ii = (int&) _ii;
  sd=x(++ii);
}

void copy_value_from_vector(const dvector& _sd,const dvector& x,const int & _ii)
{
  dvector& sd = (dvector&) _sd;
  int& ii = (int&) _ii;
  int mmin=sd.indexmin();
  int mmax=sd.indexmax();
  for (int i=mmin;i<=mmax;i++)
    sd(i)=x(++ii);
}

void copy_value_from_vector(const dmatrix& _sd,const dvector& x,const int & _ii)
{
  dmatrix& sd = (dmatrix&) _sd;
  int& ii = (int&) _ii;
  int mmin=sd.indexmin();
  int mmax=sd.indexmax();
  for (int i=mmin;i<=mmax;i++)
    copy_value_from_vector(sd(i),x,ii);
}
