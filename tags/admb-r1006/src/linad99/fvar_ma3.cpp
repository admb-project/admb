/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

/*
 dvar_vector  operator * (_CONST dvar_vector& x,_CONST dmatrix& m)
 {
   RETURN_ARRAYS_INCREMENT();

   if (x.indexmin() != m.rowmin() || x.indexmax() != m.rowmax())
   {
     cerr << " Incompatible array bounds in dvar_vector  operator * (_CONST dvar_vector& x,_CONST dmatrix& m)\n";
     ad_exit(21);
   }
   dvar_vector tmp(m.colmin(),m.colmax());

   for (int j=m.colmin(); j<=m.colmax(); j++)
   {
     tmp[j]=0.0;
     for (int i=x.indexmin(); i<=x.indexmax(); i++)
     {
       tmp[j]+=x[i]*m[i][j];
     }
     //cout << "tmp[j]= "<< value(tmp[j])<<"\n";
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }      

 dvar_vector  operator * (_CONST dmatrix& m,_CONST dvar_vector& x )
 {
   RETURN_ARRAYS_INCREMENT();

   if (x.indexmin() != m.colmin() || x.indexmax() != m.colmax())
   {
     cerr << " Incompatible array bounds in dvar_vector  operator * (_CONST dvar_vector& x,_CONST dmatrix& m)\n";
     ad_exit(21);
   }

   dvar_vector tmp(m.rowmin(),m.rowmax());

   for (int i=m.rowmin(); i<=m.rowmax(); i++)
   {
     tmp[i]=0.0;
     for (int j=x.indexmin(); j<=x.indexmax(); j++)
     {
       tmp[i]+=m[i][j]*x[j];
     }
   }
   RETURN_ARRAYS_DECREMENT();
   return(tmp);
 }      
*/

/**
 * Description not yet available.
 * \param
 */
  dvariable norm(_CONST dvar_matrix& m1)
    {
      RETURN_ARRAYS_INCREMENT();

      dvariable tmp;
      tmp=0.0;
      for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
      {
        tmp+=norm2(m1.elem(i));
      }
      if (tmp>0.)
      {
        tmp=pow(tmp,.5);
      }
      else
      {
        tmp=0.0;
      }
      RETURN_ARRAYS_DECREMENT();
      return(tmp);
    }

    dvariable norm2(_CONST dvar_matrix& m1)
    {
      RETURN_ARRAYS_INCREMENT();

      dvariable tmp;
      tmp=0.0;
      for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
      {
        tmp+=norm2(m1.elem(i));
      }
      RETURN_ARRAYS_DECREMENT();
      return(tmp);
    }

   /*
    dvar_matrix trans(_CONST dvar_matrix& m1)
    {
      RETURN_ARRAYS_INCREMENT();

      dvar_matrix tmp(m1.colmin(),m1.colmax(),m1.rowmin(),m1.rowmax());

      for (int i=m1.rowmin(); i<=m1.rowmax(); i++)
      {
        for (int j=m1.colmin(); j<=m1.colmax(); j++)
        {
          tmp.elem(j,i)=m1.elem(i,j);
        }
      }
      RETURN_ARRAYS_DECREMENT();
      return (tmp);
    }
   */

