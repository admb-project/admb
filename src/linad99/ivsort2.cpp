/*
 * $Id$
 * Author: David Fournier
 *
 * Copyright (c) 2009 ADMB Foundation
 */
#include <fvar.hpp>

namespace admb_deprecated {

/** Quicksort.
    \param v Vector of integers to be sorted
    \param NSTACK Lenth of intermediate storage vector. Default is NSTACK = 60.
    \return ivector object containing the input vector sorted in ascending order.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 8
*/
ivector sort(const ivector& v, int NSTACK)
{
   const int M=7;
   const int  FM=7875;
   const int  FA=211;
   const int  FC=1663;

  int n=v.size();
  ivector arr(v.indexmin(),v.indexmax());
  arr=v;
  arr.shift(1);
  int l=1,jstack=0,j,ir,iq,i;
  ivector istack(1,NSTACK+1);
  long int fx=0L;
  int a;

  ir=n;
  for (;;)
  {
    if (ir-l < M)
    {
      for (j=l+1;j<=ir;j++)
      {
        a=arr[j];
        for (i=j-1;i>0 && arr[i]>a;i--) arr[i+1]=arr[i];
        arr[i+1]=a;
      }
      if (jstack == 0) 
      {
        arr.shift(v.indexmin());
        return arr;
      }
      ir=istack[jstack--];
      l=istack[jstack--];
    } 
    else 
    {
      i=l;
      j=ir;
      fx=(fx*FA+FC) % FM;
      iq=l+((ir-l+1)*fx)/FM;
      a=arr[iq];
      arr[iq]=arr[l];
      for (;;)
      {
        while (j > 0 && a < arr[j]) j--;
        if (j <= i)
        {
          arr[i]=a;
          break;
        }
        arr[i++]=arr[j];
        while (i <= n && a > arr[i] ) i++;
        if (j <= i) 
        {
          arr[(i=j)]=a;
          break;
        }
        arr[j--]=arr[i];
      }
      if (ir-i >= i-l) 
      {
        istack[++jstack]=i+1;
        istack[++jstack]=ir;
        ir=i-1;
      } else 
      {
        istack[++jstack]=l;
        istack[++jstack]=i-1;
        l=i+1;
      }
      if (jstack > NSTACK)
      {
         cerr << "Need to increase the stack in sort(const ivector&)\n";
         ad_exit(1);
      }
    }
  }
}

/** Quicksort.
    \param _v Vector of integers to be sorted
    \param _index ivector on return containing the input order of the origian vector.
    \param NSTACK Lenth of intermediate storage vector. Default is NSTACK = 60.
    \return ivector object containing the input vector sorted in ascending order.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 8
*/
ivector sort(const ivector& _v, const ivector& _index, int NSTACK)
{
   const int M=7;
   const int  FM=7875;
   const int  FA=211;
   const int  FC=1663;
   int iii;
   ivector& index = (ivector&) _index;
   ivector& v = (ivector&) _v;

  if (v.size() != index.size())
  {
    cerr << " Incompatible array sizes in vector v and ivector index\n"
      << " in ivector sort(const ivector& v, const ivector& index)\n";
    ad_exit(1);
  }
  int n=v.size();
  int One=1;
  int nne=v.indexmin();
  index.fill_seqadd(nne,One);
  ivector arr(v.indexmin(),v.indexmax());
  arr=v;
  arr.shift(1);
  index.shift(1);
  int l=1,jstack=0,j,ir,iq,i;
  ivector istack(1,NSTACK+1);
  long int fx=0L;
  int a;

  ir=n;
  int i1;
  int tmp;
  for (;;)
  {
    if (ir-l < M)
    {
      for (j=l+1;j<=ir;j++)
      {
        a=arr[j];
        iii=index[j];
        for (i=j-1;i>0;i--)
        {
          tmp=arr[i];
          i1=i+1;
          if (tmp <=a) break;
          arr[i1]=tmp;
          index[i1]=index[i];
        }
        arr[i+1]=a;
        index[i+1]=iii;
      }
      if (jstack == 0)
      {
        arr.shift(v.indexmin());
        index.shift(v.indexmin());
        return arr;
      }
      ir=istack[jstack--];
      l=istack[jstack--];
    }
    else
    {
      i=l;
      j=ir;
      fx=(fx*FA+FC) % FM;
      iq=l+((ir-l+1)*fx)/FM;
      a=arr[iq];
      iii=index[iq];
      arr[iq]=arr[l];
      index[iq]=index[l];
      for (;;)
      {
        while (j > 0 && a < arr[j]) j--;
        if (j <= i)
        {
          arr[i]=a;
          index[i]=iii;
          break;
        }
        arr[i]=arr[j];
        index[i++]=index[j];
        while (i <= n && a > arr[i]) i++;
        if (j <= i)
        {
          arr[(i=j)]=a;
          index[i]=iii;
          break;
        }
        arr[j]=arr[i];
        index[j--]=index[i];
      }
      if (ir-i >= i-l)
      {
        istack[++jstack]=i+1;
        istack[++jstack]=ir;
        ir=i-1;
      } else
      {
        istack[++jstack]=l;
        istack[++jstack]=i-1;
        l=i+1;
      }
      if (jstack > NSTACK)
      {
         cerr << "Need to increase the stack in sort(const ivector&)\n";
         ad_exit(1);
      }
    }
  }
}

}
