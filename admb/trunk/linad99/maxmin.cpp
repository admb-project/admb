#define HOME_VERSION
//#define DIAG
#include <fvar.hpp>
#if defined(__TURBOC__) && !defined(__linux__)
#pragma hdrstop
#include <conio.h>
#include <iomanip.h>
#endif

double max( CGNU_DOUBLE u, CGNU_DOUBLE v)
{
  if (u > v)
  {
    return u;
  }
  else
  {
    return v;
  }
}

double min( CGNU_DOUBLE u, CGNU_DOUBLE v)
{
  if (u < v)
  {
    return u;
  }
  else
  {
    return v;
  }
}

// #undef DIAG
#undef HOME_VERSION
