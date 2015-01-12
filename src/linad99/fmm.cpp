/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>

extern  int ctlc_flag;
fmm::fmm(int nvar,_CONST lvector& ipar,int _disk_save)
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
