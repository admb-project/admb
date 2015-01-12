/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
// file: fvarm_io.cpp
#include "fvar.hpp"

//////// i/o operations for class dvar_matrix


#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
  #include <iomanip.h>
  #include <fstream.h>
  #define __USE_IOSTREAM__
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #include <iomanip.hpp>
  #include <fstream.hpp>
  #define __USE_IOSTREAM__
#endif


// unformatted i/o

#ifdef __USE_IOSTREAM__
/**
 * Description not yet available.
 * \param
 */
uistream& operator>>(BOR_CONST uistream& istr,BOR_CONST dvar_matrix& _z)
{
  ADUNCONST(dvar_matrix,z)
  z.read_from(istr);
  return (uistream&)istr;
}

/**
 * Description not yet available.
 * \param
 */
void dvar_matrix::read_from(BOR_CONST uistream& s)
{
  if (allocated(*this))
  {  
    int n = rowmin() + rowsize() - 1;

    for (int i=rowmin(); i <= n; i++)
    {
      s >> (*this)[i];
      if (!s.good()) 
      {
        cerr << " Error in dvar_matrix read\n";
        ad_exit(1);
      }
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
uostream& operator<<(BOR_CONST uostream& ostr,_CONST dvar_matrix& z)
{
  if (allocated(z))
    z.write_on(ostr);

  return (uostream&)ostr;
}

/**
 * Description not yet available.
 * \param
 */
void dvar_matrix::write_on(BOR_CONST uostream& s) _CONST
{
  if (allocated(*this))
  {  
    int n = rowmin() + rowsize() - 1;
    for (int i=rowmin(); i <= n; i++)
    {
      s << (*this)[i];
      if (!s.good()) 
      {
        cerr << " Error in dvar_matrix write\n";
        ad_exit(1);
      }
    }
  }
}
#endif

