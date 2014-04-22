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

extern  int ctlc_flag;

/**
 * Description not yet available.
 * \param
 */
fmm::fmm(int nvar, const lvector& ipar, int _disk_save)
: fmm_control(ipar),
  w(1,4*nvar), funval(1,10),
  xx(0,nvar), gbest(0,nvar), xsave(0,nvar), gsave(0,nvar)
{
  disk_save=_disk_save;
  if (!disk_save) h.allocate(nvar);
  ctlc_flag = 0;
  n = nvar;
  fbest=1.e+100;
}

/**
 * Description not yet available.
 * \param
 */
fmm::fmm(int nvar,int _disk_save)
: w(1,4*nvar), funval(1,10),
  xx(0,nvar), gbest(0,nvar), xsave(0,nvar), gsave(0,nvar)
{
  disk_save=_disk_save;
  if (!disk_save) h.allocate(nvar);
  ctlc_flag = 0;
  n = nvar;
  fbest=1.e+100;
//  cout << " In fmm::fmm(int nvar) nvar = " << nvar
//       << " and n = " << n << "\n";
}
