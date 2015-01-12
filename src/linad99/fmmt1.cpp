/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>

extern  int ctlc_flag;
fmmt1::fmmt1(int nvar,_CONST lvector& ipar)
: fmm_control(ipar),
  w(1,4*nvar), funval(1,10),
  xx(0,nvar), gbest(0,nvar), xsave(0,nvar), gsave(0,nvar)
{
  ctlc_flag = 0;
  n = nvar;
}

fmmt1::fmmt1(int nvar,int _xm)
: w(1,4*nvar), funval(1,10),
  xx(0,nvar), gbest(0,nvar), xsave(0,nvar), gsave(0,nvar) ,
  xstep(0,_xm+1,1,nvar), xy(0,_xm+1,1,nvar), xrho(0,_xm+1), 
  xold(1,nvar), gold(1,nvar), rrr(1,nvar) 
{
  ctlc_flag = 0;
  n = nvar;
  xm=_xm;
  xrho.initialize();
//  cout << " In fmm::fmm(int nvar) nvar = " << nvar 
//       << " and n = " << n << "\n";
}
