/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
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

fmm_control::fmm_control(BOR_CONST fmm_control & t)
{
  fringe = fringe;
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

fmm_control::fmm_control()
{
  set_defaults();
}


fmm_control::fmm_control(_CONST lvector& ipar)
{
  set_defaults();
  maxfn  = ipar[1];
  iprint = ipar[2];
  #ifdef __HP__
    crit   = .0001;
  #else
    crit   = pow(double(10), int(-ipar[3]));
  #endif
  imax   = ipar[4];
  scroll_flag = ipar[5];
}

ostream& operator<<(BOR_CONST ostream& s, const fmm_control& fmc)
{
  fmc.writeon(s);
  return (ostream&)s;
}

void fmm_control::writeon(BOR_CONST ostream& _s) const
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

