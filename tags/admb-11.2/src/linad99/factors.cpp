/*
 * $Id$
 *
 * Authors: Anders Nielsen <anders@nielsensweb.org>
 * Copyright (c) 2010-2012 ADMB Foundation
 */
/**
 * \file
 * Support functions for factor.
 */
#include <fvar.hpp>
#include "factors.h"

int count_factor(const dvector& v, const double& eps){
  int from=v.indexmin();
  int to=v.indexmax();
  int counter=1;
  int seenBefore;
  for(int i=from+1; i<=to; ++i){ // can be optimized
    seenBefore=0;
    for(int j=from; j<=(i-1); ++j){
      if(fabs(v(j)-v(i))<eps){
        seenBefore=1;
        break;
      }
    }
    if(seenBefore==0){
      counter++;
    }
  }
  return counter;
}

ivector as_factor(const dvector& v, const double eps){
  int from=v.indexmin();
  int to=v.indexmax();
  ivector idxlocal(from,to);
  int nlevels=count_factor(v,eps);
  dvector whichlevel(1,nlevels);
    int  whichlevelindex=0;
    whichlevel(++whichlevelindex)=v(from);
    int seenBefore;
    for(int i=from+1; i<=to; ++i){
      seenBefore=0;
      for(int j=1; j<=whichlevelindex; ++j){
        if(fabs(whichlevel(j)-v(i))<eps){
          seenBefore=1;
          break;
        }
      }
      if(!seenBefore){
        whichlevel(++whichlevelindex)=v(i);
      }
    }
    for(int j=1; j<=nlevels; ++j){
      for(int i=from; i<=to; ++i){
        if(fabs(v(i)-whichlevel(j))<eps){
          idxlocal(i)=j;
        };
      }
    }
    return idxlocal;
}

int count_factor(const ivector& v){
  int from=v.indexmin();
  int to=v.indexmax();
  int counter=1;
  int seenBefore;
  for(int i=from+1; i<=to; ++i){ // can be optimized
    seenBefore=0;
    for(int j=from; j<=(i-1); ++j){
      if(v(j)==v(i)){
        seenBefore=1;
        break;
      }
    }
    if(seenBefore==0){
      counter++;
    }
  }
  return counter;
}

void factor::allocate(const ivector& v, dvar_vector & par){
  int from=v.indexmin();
  int to=v.indexmax();

  ivector idxlocal(from,to);
  if(par.indexmin()!=1)
  {
    cout<<"Error: par indexmin is not 1 in factor - something is wrong"<<endl;
    ad_exit(1);
  }
  nlevels=par.indexmax();
  ivector whichlevel(1,nlevels);
  int  whichlevelindex=0;
  whichlevel(++whichlevelindex)=v(from);
  int seenBefore;
  for(int i=from+1; i<=to; ++i){
    seenBefore=0;
    for(int j=1; j<=whichlevelindex; ++j){
      if(whichlevel(j)==v(i)){
        seenBefore=1;
        break;
      }
    }
    if(!seenBefore){
      whichlevel(++whichlevelindex)=v(i);
    }
  }
  for(int j=1; j<=nlevels; ++j){
    for(int i=from; i<=to; ++i){
      if(v(i)==whichlevel(j)){
        idxlocal(i)=j;
      };
    }
  }
  idx=idxlocal;
  levels=par;
}

dvariable factor::operator () (int i){
  return levels(idx(i));
}

