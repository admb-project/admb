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
void dvector::fill_multinomial(const int& seed, const dvector& p)
  // Fils a dvector with random numbers drawn from a multinomial distribution
  {
    double sum=mean(p)*p.size();
    int pmin=p.indexmin();
    int pmax=p.indexmax();
    dvector tmp(pmin,pmax);
    dvector tmp1(pmin,pmax);
    dvector choose(indexmin(),indexmax());
    choose.fill_randu(seed);
    tmp=p/sum;
    tmp1(pmin)=tmp(pmin);
    for (int j=pmin+1;j<=pmax-1;j++)
    {
      tmp1(j)=tmp1(j-1)+tmp(j);
    }
    tmp1(pmax)=1.0;

    for (int i=indexmin();i<=indexmax();i++)
    {
      int j=pmin;
      while (choose(i)>tmp1(j))
      {
        j++;
      }
      (*this)(i)=j;
    }
  }

/**
 * Description not yet available.
 * \param
 */
void ivector::fill_multinomial(const int& seed, const dvector& p)
  // Fills a dvector with random numbers drawn from a multinomial distribution
  {
    double sum=mean(p)*p.size();
    int pmin=p.indexmin();
    int pmax=p.indexmax();
    dvector tmp(pmin,pmax);
    dvector tmp1(pmin,pmax);
    dvector choose(indexmin(),indexmax());
    choose.fill_randu(seed);
    tmp=p/sum;
    tmp1(pmin)=tmp(pmin);
    for (int j=pmin+1;j<=pmax-1;j++)
    {
      tmp1(j)=tmp1(j-1)+tmp(j);
    }
    tmp1(pmax)=1.0;

    for (int i=indexmin();i<=indexmax();i++)
    {
      int j=pmin;
      while (choose(i)>tmp1(j))
      {
        j++;
      }
      (*this)(i)=j;
    }
  }

/**
 * Description not yet available.
 * \param
 */
void lvector::fill_multinomial(const int& seed, const dvector& p)
  // Fils a dvector with random numbers drawn from a multinomial distribution
  {
    double sum=mean(p)*p.size();
    int pmin=p.indexmin();
    int pmax=p.indexmax();
    dvector tmp(pmin,pmax);
    dvector tmp1(pmin,pmax);
    dvector choose(indexmin(),indexmax());
    choose.fill_randu(seed);
    tmp=p/sum;
    tmp1(pmin)=tmp(pmin);
    for (int j=pmin+1;j<=pmax-1;j++)
    {
      tmp1(j)=tmp1(j-1)+tmp(j);
    }
    tmp1(pmax)=1.0;

    for (int i=indexmin();i<=indexmax();i++)
    {
      int j=pmin;
      while (choose(i)>tmp1(j))
      {
        j++;
      }
      (*this)(i)=j;
    }
  }
