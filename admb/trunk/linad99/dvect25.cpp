/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */



#include <fvar.hpp>

  void dvector::fill_multinomial(BOR_CONST random_number_generator& rng,_CONST dvector& p)
  // Fils a dvector with random numbers drawn from a multinomial distribution
  {
    double sum=mean(p)*p.size();
    int pmin=p.indexmin();
    int pmax=p.indexmax();
    dvector tmp(pmin,pmax);
    dvector tmp1(pmin,pmax);
    dvector choose(indexmin(),indexmax());
    choose.fill_randu(rng);
    tmp=p/sum;
    tmp1(pmin)=tmp(pmin);
    int j;
    for (j=pmin+1;j<=pmax-1;j++)
    {
      tmp1(j)=tmp1(j-1)+tmp(j);
    }
    tmp1(pmax)=1.0;

    for (int i=indexmin();i<=indexmax();i++)
    {
      j=pmin;
      while (choose(i)>tmp1(j))
      {
        j++;
      }
      (*this)(i)=j;
    }
  }

  void ivector::fill_multinomial(BOR_CONST random_number_generator& rng,_CONST dvector& p)
  // Fills a dvector with random numbers drawn from a multinomial distribution
  {
    double sum=mean(p)*p.size();
    int pmin=p.indexmin();
    int pmax=p.indexmax();
    dvector tmp(pmin,pmax);
    dvector tmp1(pmin,pmax);
    dvector choose(indexmin(),indexmax());
    choose.fill_randu(rng);
    tmp=p/sum;
    tmp1(pmin)=tmp(pmin);
    int j;
    for (j=pmin+1;j<=pmax-1;j++)
    {
      tmp1(j)=tmp1(j-1)+tmp(j);
    }
    tmp1(pmax)=1.0;

    for (int i=indexmin();i<=indexmax();i++)
    {
      j=pmin;
      while (choose(i)>tmp1(j))
      {
        j++;
      }
      (*this)(i)=j;
    }
  }

  void lvector::fill_multinomial(BOR_CONST random_number_generator& rng,_CONST dvector& p)
  // Fils a dvector with random numbers drawn from a multinomial distribution
  {
    double sum=mean(p)*p.size();
    int pmin=p.indexmin();
    int pmax=p.indexmax();
    dvector tmp(pmin,pmax);
    dvector tmp1(pmin,pmax);
    dvector choose(indexmin(),indexmax());
    choose.fill_randu(rng);
    tmp=p/sum;
    tmp1(pmin)=tmp(pmin);
    int j;
    for (j=pmin+1;j<=pmax-1;j++)
    {
      tmp1(j)=tmp1(j-1)+tmp(j);
    }
    tmp1(pmax)=1.0;

    for (int i=indexmin();i<=indexmax();i++)
    {
      j=pmin;
      while (choose(i)>tmp1(j))
      {
        j++;
      }
      (*this)(i)=j;
    }
  }
