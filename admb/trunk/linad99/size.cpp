/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */


  
#include "fvar.hpp"


int size_count(_CONST dvar_vector& x)
{
  if (!(x))
    return 0;
  else  
    return x.size();
}

int size_count_partial(_CONST dvar_vector& x,int n)
{
  if (!(x))
    return 0;
  else  
    return n;
}

int size_count(_CONST dvar_matrix& x)
{
  if (!(x))
    return 0;
  else
  {  
    int tmp=0;
    int min=x.rowmin();
    int max=x.rowmax();
    for (int i=min;i<=max;i++)
    {
      tmp+=size_count(x(i));
    }
    return tmp;
  }
}

int size_count_partial(_CONST dvar_matrix& x, int n)
{
  if (!(x))
    return 0;
  else
  {
    int tmp=0;
    int min=x.rowmin();
    int max=x.rowmax();
    for (int i=min;i<=max;i++)
    {
      tmp+=size_count_partial(x(i),n);
    }
    return tmp;
  }
}

int size_count(_CONST dvar3_array& x)
{
  if (!(x))
    return 0;
  else
  {
    int tmp=0;
    int min=x.slicemin();
    int max=x.slicemax();
    for (int i=min;i<=max;i++)
    {
      tmp+=size_count(x(i));
    }
    return tmp;
  }
}

int size_count(_CONST dvar4_array& x)
{
  if (!(x))
    return 0;
  else
  {
    int tmp=0;
    int min=x.indexmin();
    int max=x.indexmax();
    for (int i=min;i<=max;i++)
    {
      tmp+=size_count(x(i));
    }
    return tmp;
  }
}

int size_count(_CONST d4_array& x)
{
  if (!(x))
    return 0;
  else
  {
    int tmp=0;
    int min=x.indexmin();
    int max=x.indexmax();
    for (int i=min;i<=max;i++)
    {
      tmp+=size_count(x(i));
    }
    return tmp;
  }
}

int size_count_partial(_CONST dvar3_array& x, int n)
{
  if (!(x))
    return 0;
  else
  {
    int tmp=0;
    int min=x.slicemin();
    int max=x.slicemax();
    for (int i=min;i<=max;i++)
    {
      tmp+=size_count_partial(x(i),n);
    }
    return tmp;
  }
}

