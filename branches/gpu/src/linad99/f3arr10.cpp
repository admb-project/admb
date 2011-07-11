/*
 * $Id: f3arr10.cpp 946 2011-01-12 23:52:45Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"

/**
 * Description not yet available.
 * \param
 */
   dvar3_array operator / (_CONST prevariable& d,_CONST dvar3_array& m)
   {
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d/m(i);
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   dvar3_array operator / (_CONST prevariable& d,_CONST d3_array& m)
   {
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d/m(i);
     }
     return tmp;
   }  

/**
 * Description not yet available.
 * \param
 */
   dvar3_array operator / ( CGNU_DOUBLE d,_CONST dvar3_array& m)
   {
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=d/m(i);
     }
     return tmp;
   }
