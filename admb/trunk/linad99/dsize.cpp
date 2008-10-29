  
#define HOME_VERSION //COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include "fvar.hpp"

int size_count(_CONST dvector& x)
{
  return x.size();
}

int size_count_partial(_CONST dvector& x, int n)
{
  return n;
}

int size_count(_CONST dmatrix& x)
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

int size_count_partial(_CONST dmatrix& x, int n)
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

int size_count(_CONST d3_array& x)
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

int size_count_partial(_CONST d3_array& x,int n)
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

#undef HOME_VERSION
