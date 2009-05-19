/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <fvar.hpp>
#pragma hdrstop
#include "fmmq.hpp"

fmmq::fmmq(int nv) : xa(1,nv) , xb(1,nv) , d(1,nv) , ga(1,nv),
   gb(1,nv) , h(1,(nv*(nv+1))/2) , w(1,4*nv) , scale(1,nv) ,
   funval(1,10), xsave(1,nv) , gsave(1,nv), xbest(1,nv),
   gbest(1,nv)
{
  mode = 1;
  igwindow = 2;
  n=nv;
  scale.fill_seqadd(1.,0.);
  maxfn=500;
  iprint=1;
  imax=30;
  iexit = 0;
  ifn = 0;
  itn = 0;
  ihang = 0;
  ialph = 0;
  ihflag = 0;
  gmax = 0;
  istop = 0;
  crit=.0001;
  min_improve=1.e-6;
  funval.initialize();
}
