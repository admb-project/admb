/**
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/

#include "fvar.hpp"
#include <cassert>

/**
Returns d3_array with computed logs from elements in m.
*/
d3_array log(const d3_array& m)
{
  d3_array ret;
  ret.allocate(m);
  for (int i = ret.slicemin(); i <= ret.slicemax(); ++i)
  {
    ret(i) = log(m(i));
  }
  return ret;
}
/**
Returns d3_array with computed e from elements in m.
*/
d3_array exp(const d3_array& m)
{
  d3_array ret;
  ret.allocate(m);
  for (int i = ret.slicemin(); i <= ret.slicemax(); ++i)
  {
    ret(i) = exp(m(i));
  }
  return ret;
}

/**
 * Description not yet available.
 * \param
 */
d3_array sin(const d3_array& m)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=sin(m(i));
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
d3_array cos(const d3_array& m)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=cos(m(i));
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
d3_array tan(const d3_array& m)
   {
     d3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=tan(m(i));
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
d3_array elem_prod(const d3_array& m1, const d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=elem_prod(m1(i),m2(i));
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
d3_array elem_div(const d3_array& m1, const d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=elem_div(m1(i),m2(i));
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
d3_array operator+(const d3_array& m1, const d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)+m2(i);
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
d3_array operator-(const d3_array& m1, const d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)-m2(i);
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
double norm(const d3_array& m)
    {
      double tmp=0.0;
      for (int k=m.slicemin();k<=m.slicemax();k++)
      {
        tmp+=norm2(m(k));
      }
      tmp=sqrt(tmp);
      return tmp;
    }

/**
 * Description not yet available.
 * \param
 */
double norm2(const d3_array& m)
    {
      double tmp=0.0;
      for (int k=m.slicemin();k<=m.slicemax();k++)
      {
         tmp+=norm2(m(k));
      }
      return tmp;
    }
double sumsq(const d3_array& m) { return(norm2(m)); }

/**
 * Description not yet available.
 * \param
 */
d3_array operator+(double d, const d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d+m2(i);
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
d3_array operator-( double d,const d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d-m2(i);
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
d3_array operator+(const d3_array& m1, double d)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)+d;
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
d3_array operator-(const d3_array& m1, double d)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)-d;
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
d3_array operator*(const d3_array& m1, double d)
   {
     d3_array tmp;
     tmp.allocate(m1);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=m1(i)*d;
     }
     return tmp;
   }

/**
 * Description not yet available.
 * \param
 */
d3_array operator*( double d, const d3_array& m2)
   {
     d3_array tmp;
     tmp.allocate(m2);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d*m2(i);
     }
     return tmp;
   }
