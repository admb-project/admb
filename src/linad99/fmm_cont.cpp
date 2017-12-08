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
#include "fvar.hpp"

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #define endl "\n"
#endif
#include <math.h>

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/**
 * Description not yet available.
 * \param
 */
void fmm_control::set_defaults()
{
  noprintx=0;
  fringe = 0.0;
  maxfn  = 500;
  iprint = 1;
  crit   = 0.0001;
  imax   = 30;
  dfn    = 0;
  ifn    = 0;
  iexit  = 0;
  ialph  = 0;
  ihflag = 0;
  ihang  = 0;
  scroll_flag = 1;
  maxfn_flag=0;
  quit_flag=0;
  min_improve=.0000001;
  ireturn = 0;
  dcheck_flag = -1;
  use_control_c=1;
}

/**
 * fmm_control Function minimizer copy constructor
 * \param t object
 */
fmm_control::fmm_control(const fmm_control & t)
{
  fringe = t.fringe;
  maxfn  = t.maxfn;
  iprint = t.iprint;
  crit   = t.crit;
  imax   = t.imax;
  dfn    = t.dfn;
  ifn    = t.ifn;
  iexit  = t.iexit;
  min_improve =t.min_improve;
  ialph  = t.ialph;
  ihflag = t.ihflag;
  ihang  = t.ihang;
  scroll_flag = t.scroll_flag;
  dcheck_flag = t.dcheck_flag;

  ireturn = t.ireturn;
}

/**
Default constructor
*/
fmm_control::fmm_control()
{
  set_defaults();
}
/**
Constructs function minimizer with values from
ipar and overrides the extended defaults.

\param ipar integer vector of settings
*/
fmm_control::fmm_control(const lvector& ipar)
{
  set_defaults();

#if defined(__MINGW64__)
  #ifndef OPT_LIB
  assert(ipar[1] <= LONG_MAX);
  assert(ipar[2] <= LONG_MAX);
  #endif
  maxfn  = static_cast<long>(ipar[1]);
  iprint = static_cast<long>(ipar[2]);
#else
  maxfn  = ipar[1];
  iprint = ipar[2];
#endif

#ifdef __HP__
  crit = .0001;
#else
  #ifndef OPT_LIB
  assert(ipar[3] <= INT_MAX);
  #endif
  crit = pow(double(10), static_cast<int>(-ipar[3]));
#endif

#if defined(__MINGW64__)
  #ifndef OPT_LIB
  assert(ipar[4] <= LONG_MAX);
  #endif
  imax = static_cast<long>(ipar[4]);
#else
  imax = ipar[4];
#endif

#ifndef OPT_LIB
  assert(ipar[5] <= INT_MAX);
#endif
  scroll_flag = static_cast<int>(ipar[5]);
}

/**
 * << operator to write function minimizer details
 * \param s string of details
 * \param fmc function minimizer control object
 * \return output stream of details.
 */
ostream& operator<<(const ostream& s, const fmm_control& fmc)
{
  fmc.writeon(s);
  return (ostream&)s;
}

/**
 * writeon Writes function minimizing status
 * \param s string that contains results
 */
void fmm_control::writeon(const ostream& _s) const
{
  ostream& s = (ostream&) _s;
  s << "values of fmm_control structure:\n";
  s << "  maxfn  =  " << maxfn  << endl;
  s << "  iprint =  " << iprint << endl;
  s << "  crit   =  " << crit   << endl;
  s << "  imax   =  " << imax   << endl;
  s << "  dfn    =  " << dfn    << endl;
  s << "  ifn    =  " << ifn    << endl;
  s << "  iexit  =  " << iexit  << endl;
  s << "  ialph  =  " << ialph   << endl;
  s << "  ihflag =  " << ihflag << endl;
  s << "  ihang  =  " << ihang  << endl;
  s << "  scroll_flag  =  " << scroll_flag  << endl;
  s << "  ireturn  = " << ireturn  << endl;
}
