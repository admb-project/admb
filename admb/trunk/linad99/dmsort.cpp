/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: Unknown
  */
#define HOME_VERSION
#include <fvar.hpp>


dmatrix sort(_CONST dmatrix& m,int column,int NSTACK)
{
  ivector ind(m.rowmin(),m.rowmax());
  ivector ind1(m.rowmin(),m.rowmax());
  ivector ind2(m.rowmin(),m.rowmax());
  int i;
  for (i=m.rowmin();i<=m.rowmax();i++)
  {
    ind1(i)=m(i).indexmin();
    ind2(i)=m(i).indexmax();
  }
  sort(extract_column(m,column),ind);
  dmatrix tmp(m.rowmin(),m.rowmax(),ind1,ind2);
  for (i=m.rowmin();i<=m.rowmax();i++)
  {
    tmp(i)=m(ind(i));
  }
  return tmp;
}


/*
dmatrix sort(_CONST dmatrix& m,BOR_CONST int& column,BOR_CONST int& NSTACK)
{
  const int M=7;
  const int  FM=7875;
  const int  FA=211;
  const int  FC=1663;
  int iii;
  int rowsave=m.rowmin();
  m.rowshift(1);
  int n=m.rowsize();
  dvector arr=extract_column(m,column);
  ivector index(1,n);
  index.fill_seqadd(1,1);
  dmatrix MOUT(1,n,m.colmin(),m.colmax());
  int l=1,jstack=0,j,ir,iq,i;
  ivector istack(1,NSTACK+1);
  long int fx=0L;
  float a;

  ir=n;
  for (;;)
  {
    if (ir-l < M)
    {
      for (j=l+1;j<=ir;j++)
      {
        a=arr[j];
        iii=index[j];
        for (i=j-1;i>0 && arr[i]>a;i--)
        {
          arr[i+1]=arr[i];
          index[i+1]=index[i];
        }
        arr[i+1]=a;
        index[i+1]=iii;
      }
      if (jstack == 0)
      {
        for (int ii=1;ii<=n;ii++)
        {
          MOUT[ii]=m(index(ii));
        }
        MOUT.rowshift(rowsave);
        return MOUT;
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
         cerr << "Need to increase the stack in sort(_CONST dvector&)\n";
         ad_exit(1);
      }
    }
  }

}
*/

#undef HOME_VERSION
