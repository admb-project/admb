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
dvector operator&(const dvector& t1, const dvector& t2)
  {
    int size =t1.size()+t2.size();
    dvector tmp(1,size);
    int min=t1.indexmin();
    int max=t1.indexmax();
    int ii=0;
    int i;
    for (i=min;i<=max;i++)
    {
      tmp(++ii)=t1(i);
    }
    min=t2.indexmin();
    max=t2.indexmax();
    for (i=min;i<=max;i++)
    {
      tmp(++ii)=t2(i);
    }
    return tmp;
  }

/**
 * Description not yet available.
 * \param
 */
dvar_vector operator&(const dvar_vector& t1, const dvar_vector& t2)
  {
    int size =t1.size()+t2.size();
    dvar_vector tmp(1,size);
    int min=t1.indexmin();
    int max=t1.indexmax();
    int ii=0;
    int i;
    for (i=min;i<=max;i++)
    {
      tmp(++ii)=t1(i);
    }
    min=t2.indexmin();
    max=t2.indexmax();
    for (i=min;i<=max;i++)
    {
      tmp(++ii)=t2(i);
    }
    return tmp;
  }
