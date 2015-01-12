/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <admodel.h>

int xxxmax(int x,int y)
{
  if (x<y) return y;
  return x;
}
int xxxmin(int x,int y)
{
  if (x<y) return x;
  return y;
}
  void get_confidence_interval(BOR_CONST dvector& _left_bd,BOR_CONST dvector& _right_bd,
    dmatrix& ms,BOR_CONST dvector& xs,BOR_CONST dvector& siglevel,BOR_CONST int& level_index,
    int index)
  {
    dvector& left_bd=(dvector&) _left_bd;
    dvector& right_bd=(dvector&) _right_bd;
    dvector& fval=ms(index);
    int lb=0;
    int rb=0;
    double xdiff=0.0;
    double isum=0;

    int mmin=fval.indexmin();
    int mmax=fval.indexmax();
    double tmp=fval(mmin);
    int imax=mmin;
    int i;
    for (i=mmin+1;i<=mmax;i++)
    {
      if (fval(i)>tmp)
      {
        tmp=fval(i);
        imax=i;
      }
    }
    if (imax>mmin)
    {
      lb=imax-1;
      rb=imax;
    }
    else
    {
      lb=imax;
      rb=imax+1;
    }
    double integral=0.0;

    for (i=mmin+1;i<=mmax;i++)
    {
      integral+=fval(i)*(xs(i)-xs(i-1)); 
    }
    cout << integral << endl;
    do
    {
      if (lb <= fval.indexmin() &&  rb > fval.indexmax())
      {
        int lower=xxxmax(lb,fval.indexmin());
        int upper=xxxmin(rb-1,fval.indexmax());
        left_bd(level_index)=xs(lower);
        right_bd(level_index)=xs(upper);
        break;
      }

      if (fval(lb)>=fval(rb) || rb==fval.indexmax())
      {
        if (lb>fval.indexmin())
        {
          xdiff=xs(lb)-xs(lb-1);
        }
        else
        {
          int minind=fval.indexmin();
          xdiff=xs(minind+1)-xs(minind);
        }
        double incr=fval(lb)*xdiff/integral;
        //double incr=fval(lb);
        if ( incr >= (siglevel(level_index)-isum)) 
        {
          double diff = siglevel(level_index) - isum;
          double delta=diff/incr;
          if (lb>fval.indexmin())
          { 
            left_bd(level_index)=xs(lb)-delta*(xdiff);
          }
          else
          {
            left_bd(level_index)=xs(fval.indexmin());
          }
          right_bd(level_index)=xs(rb);
          break;
        }
        isum+=incr;
        lb--;
      }
      else
      {
        xdiff=xs(rb)-xs(rb-1);
        double incr=fval(rb)*xdiff/integral;
        //double incr=fval(rb);
        if ( incr >= (siglevel(level_index)-isum) ||
          rb == mmax)
        {
          double diff = siglevel(level_index) - isum;
          double delta=diff/incr;
          left_bd(level_index)=xs(lb);
          right_bd(level_index)=xs(rb)+delta*(xdiff);
          break;
        }
        isum+=incr;
        rb++;
      }
    }
    while (1);
  }

  void get_onesided_intervals(BOR_CONST dvector& _left_bd,BOR_CONST dvector& _right_bd,
    dmatrix& ms,BOR_CONST dvector& xs,BOR_CONST dvector& siglevel,BOR_CONST int& level_index,
    int index)
  {
    dvector& left_bd=(dvector&) _left_bd;
    dvector& right_bd=(dvector&) _right_bd;
    dvector& fval=ms(index);
    int lb=fval.indexmin()+1;
    int ub=fval.indexmax();
    double xdiff=0.0;
    double isum=0;
    double tmpsum=0.0;
    int ii;
    for (ii=lb+1;ii<=ub;ii++)
    {
      tmpsum+=fval(ii)*(xs(ii)-xs(ii-1));
    }

    isum=0.0;
    for (ii=lb+1;ii<=ub;ii++)
    {
      xdiff=xs(ii)-xs(ii-1);
      double incr=fval(ii)*xdiff/tmpsum;
      double fdiff = 1.-siglevel(level_index) - isum;
      if ( incr >= fdiff)
      {
        double delta=fdiff/incr;
        left_bd(level_index)=xs(ii)+delta*xdiff;
        break;
      }
      isum+=incr;
    }
    //cout << "tmpsum = " << tmpsum << endl;
    isum=0;
    for (ii=ub-1;ii>=lb;ii--)
    {
      xdiff=xs(ii+1)-xs(ii);
      double incr=fval(ii)*xdiff/tmpsum;
      double fdiff = 1.-siglevel(level_index) - isum;
      if ( incr >= fdiff)
      {
        double delta=fdiff/incr;
        right_bd(level_index)=xs(ii)+delta*xdiff;
        break;
      }
      isum+=incr;
    }
  }

