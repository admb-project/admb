/*
 * $Id: fmmt1.cpp 608 2012-09-12 01:42:45Z johnoel $
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
extern  int ctlc_flag;
fmmt1::fmmt1(int nvar, const lvector& ipar)
: fmm_control(ipar),
  w(1,4*nvar),
  funval(1,10),
  xx(0,nvar),
  gbest(0,nvar),
  xsave(0,nvar),
  gsave(0,nvar)
{
  ctlc_flag = 0;
  n = nvar;
}

/**
 * Description not yet available.
 * \param
 */
void fmmt1::allocate(int nvar,int _xm)
{
  w.allocate(1,4*nvar); funval.allocate(1,10);
  xx.allocate(0,nvar); gbest.allocate(0,nvar); xsave.allocate(0,nvar);
  gsave.allocate(0,nvar);xstep.allocate(0,_xm+1,1,nvar);
  xy.allocate(0,_xm+1,1,nvar); xrho.allocate(0,_xm+1); 
  xold.allocate(1,nvar); gold.allocate(1,nvar); rrr.allocate(1,nvar);
  ctlc_flag = 0;
  n = nvar;
  xm=_xm;
  xrho.initialize();
}
fmmt1::fmmt1(int nvar,int _xm)
: w(1,4*nvar),
  funval(1,10),
  xstep(0,_xm+1,1,nvar),
  xrho(0,_xm+1), 
  rrr(1,nvar),
  xy(0,_xm+1,1,nvar),
  xold(1,nvar),
  gold(1,nvar),
  xx(0,nvar),
  gbest(0,nvar),
  xsave(0,nvar),
  gsave(0,nvar)
{
  ctlc_flag = 0;
  n = nvar;
  xm=_xm;
  xrho.initialize();
//  cout << " In fmm::fmm(int nvar) nvar = " << nvar 
//       << " and n = " << n << "\n";
}
fmmt1::fmmt1(void)
{
  ctlc_flag = 0;
  n = 0;
  xm=0;
}
