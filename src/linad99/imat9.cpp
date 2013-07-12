/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
int max(const imatrix & M)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  int n1=max(M(mmin));
  for (int i=mmin+1;i<=mmax;i++)
  {
    int n=max(M(i));
    if (n1<n) n1=n;
  }
  return n1;
}

/**
 * Description not yet available.
 * \param
 */
int min(const imatrix & M)
{
  int mmin=M.indexmin();
  int mmax=M.indexmax();
  int n1=min(M(mmin));
  for (int i=mmin+1;i<=mmax;i++)
  {
    int n=min(M(i));
    if (n1>n) n1=n;
  }
  return n1;
}
