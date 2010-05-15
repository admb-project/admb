/*
 * $Id$
 * Author: David Fournier
 *
 * Copyright (c) 2009 ADMB Foundation
 */
#include <fvar.hpp>

static void quicksort1(dvector& a, int left, int right);
static void quicksort2(dvector& a, ivector& b, int left, int right);

/** Quicksort.
    \param v Vector of doubles to be sorted
    \param NSTACK Lenth of intermediate storage vector. Default is NSTACK = 60.
    \return dvector object containing the input vector sorted in ascending order.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 8
*/
dvector sort(_CONST dvector& v, int NSTACK)
{
  dvector arr(v.indexmin(),v.indexmax());
  arr=v;

  quicksort1(arr, arr.indexmin(), arr.indexmax());

  arr.shift(v.indexmin());
  return arr;
}

/*dvector sort(_CONST dvector& v, int NSTACK)
{
   const int M=7;
   const int  FM=7875;
   const int  FA=211;
   const int  FC=1663;

  int n=v.size();
  int minsave=v.indexmin();
  dvector arr(v.indexmin(),v.indexmax());
  arr=v;
  arr.shift(1);
  int l=1,jstack=0,j,ir,iq,i;
  ivector istack(1,NSTACK+1);
  long int fx=0L;
  double a;

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
      if (iq<=0)
      {
        iq=l+((ir-l+1.0)*fx)/FM;
      } 
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
         cerr << "Need to increase the stack in sort(_CONST dvector&)\n";
         ad_exit(1);
      }
    }
  }
}*/

/** Quicksort.
    \param _v Vector to be sorted
    \param _index ivector on return containing the input order of the origian vector.
    \param NSTACK Lenth of intermediate storage vector. Default is NSTACK = 60.
    \return dvector object containing the input vector sorted in ascending order.

    \n\n The implementation of this algorithm was inspired by
    "Numerical Recipes in C", 2nd edition,
    Press, Teukolsky, Vetterling, Flannery, chapter 8
*/

dvector sort(_CONST dvector& _v,BOR_CONST ivector& _index, int NSTACK)
{
  ivector& index = (ivector&) _index;
  dvector& v = (dvector&) _v;

  if (v.size() != index.size())
  {
    cerr << " Incompatible array sizes in vector v and ivector index\n"
      << " in dvector sort(_CONST dvector& v,_CONST ivector& index)\n";
    ad_exit(1);
  }

  int One=1;
  int nne=v.indexmin();
  index.fill_seqadd(nne,One);
  dvector arr(v.indexmin(),v.indexmax());
  arr=v;
  arr.shift(1);
  index.shift(1);

  quicksort2(arr, index, arr.indexmin(), arr.indexmax());

  arr.shift(v.indexmin());
  index.shift(v.indexmin());
  return arr;
}

/*dvector sort(_CONST dvector& _v,BOR_CONST ivector& _index, int NSTACK)
{
   const int M=7;
   const int  FM=7875;
   const int  FA=211;
   const int  FC=1663;
   int iii;
   ivector& index = (ivector&) _index;
   dvector& v = (dvector&) _v;

  if (v.size() != index.size())
  {
    cerr << " Incompatible array sizes in vector v and ivector index\n"
      << " in dvector sort(_CONST dvector& v,_CONST ivector& index)\n";
    ad_exit(1);
  }
  int n=v.size();
  int One=1;
  int nne=v.indexmin();
  index.fill_seqadd(nne,One);
  dvector arr(v.indexmin(),v.indexmax());
  arr=v;
  arr.shift(1);
  index.shift(1);
  int l=1,jstack=0,j,ir,iq,i;
  ivector istack(1,NSTACK+1);
  long int fx=0L;
  double a;

  ir=n;
  int i1;
  double tmp;
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
      if (iq<0)
      {
        iq=l+((ir-l+1.0)*fx)/FM;
      }
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
         cerr << "Need to increase the stack in sort(_CONST dvector&)\n";
         ad_exit(1);
      }
    }
  }
}*/

/*
 * Based on Robert Sedgewick and Kevin Wayne quicksort
 * from slides disscussing the algorithm from their book
 * 'Algorthms'. This uses quicksort3 (3way partition) and
 * an insertion sort once sublists are of length < 8.
 * Modified by Derek Seiple
 */

static void quicksort1(dvector& a, int left, int right)
{
  int i = left-1, j = right, p = left-1, q = right;
  double temp;
  int r_m_l = right-left;
  if (r_m_l <= 0) return;

  if((r_m_l)<8) {
    for(int i=left+1;i<=right;i++) {
      for(int k = i; k >= left+1; k--) {
        if(a[k] < a[k-1]) { temp=a[k];a[k]=a[k-1];a[k-1]=temp; }
      }
    }
    return;
  }

  double v = a[right];

  for(;;)
    {
      while (a[++i] < v);
      while (v < a[--j]) if (j == left) break;
      if (i >= j) break;
      temp=a[i];a[i]=a[j];a[j]=temp;               
      if (a[i] == v) { p++; temp=a[p];a[p]=a[i];a[i]=temp; }
      if (v == a[j]) { q--; temp=a[j];a[j]=a[q];a[q]=temp; }
    }
  temp=a[i];a[i]=a[right];a[right]=temp; j = i-1; i = i+1;
  for (int k = left; k <= p; k++, j--) { temp=a[k];a[k]=a[j];a[j]=temp; }
  for (k = right-1; k >= q; k--, i++) { temp=a[i];a[i]=a[k];a[k]=temp; }
  quicksort1(a, left, j);
  quicksort1(a, i, right);
}


static void quicksort2(dvector& a, ivector& b, int left, int right)
{
  int i = left-1, j = right, p = left-1, q = right;
  int r_m_l = right-left;
  double temp;
  if (r_m_l <= 0) return;

  if((r_m_l)<7) {
    for(int i=left+1;i<=right;i++) {
      for(int k = i; k >= left+1; k--) {
        if(a[k] < a[k-1]) {
          temp=a[k];a[k]=a[k-1];a[k-1]=temp;
          temp=b[k];b[k]=b[k-1];b[k-1]=temp;
        }
      }
    }
    return;
  }

  double v =a[right];

  for(;;)
    {
      while (a[++i] < v);
      while (v < a[--j]) if (j == left) break;
      if (i >= j) break;
      temp=a[i];a[i]=a[j];a[j]=temp;
      temp=b[i];b[i]=b[j];b[j]=temp;
      if (a[i] == v) {
        p++;
        temp=a[p];a[p]=a[i];a[i]=temp;
        temp=b[p];b[p]=b[i];b[i]=temp;
      }
      if (v == a[j]) {
        q--;
        temp=a[j];a[j]=a[q];a[q]=temp;
        temp=b[j];b[j]=b[q];b[q]=temp;
      }
    }
  temp=a[i];a[i]=a[right];a[right]=temp;
  temp=b[i];b[i]=b[right];b[right]=temp;
  j = i-1; i = i+1;
  for (int k = left; k <= p; k++, j--) {
    temp=a[k];a[k]=a[j];a[j]=temp;
    temp=b[k];b[k]=b[j];b[j]=temp;
  }
  for (k = right-1; k >= q; k--, i++) {
    temp=a[i];a[i]=a[k];a[k]=temp;
    temp=b[i];b[i]=b[k];b[k]=temp;
  }
  quicksort2(a, b, left, j);
  quicksort2(a, b, i, right);
}
