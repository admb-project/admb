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
#include <fvar.hpp>

extern  int ctlc_flag;

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
fmm::fmm(void)
{
  disk_save=0;
  ctlc_flag = 0;
  n=0;
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
}

void fmm::allocate(int nvar,int _disk_save)
{
  w.allocate(1,4*nvar); funval.allocate(1,10);
  xx.allocate(0,nvar); gbest.allocate(0,nvar);
  xsave.allocate(0,nvar); gsave.allocate(0,nvar);
  disk_save=_disk_save;
  if (!disk_save) h.allocate(nvar); 
  ctlc_flag = 0;
  n = nvar;
  fbest=1.e+100;
}
