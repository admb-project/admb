/*
 * $Id: expm.cpp 246 2012-02-03 20:06:15Z johnoel $
 *
 * Authors: Anders Nielsen <anders@nielsensweb.org>
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Support functions for factor. 
 */
#include <fvar.hpp>

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
