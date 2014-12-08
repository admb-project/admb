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
