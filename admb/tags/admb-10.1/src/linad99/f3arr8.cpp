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

/**
 * Description not yet available.
 * \param
 */
   dvar3_array pow(_CONST dvar3_array& m, int e)
   {
     dvar3_array tmp;
     tmp.allocate(m);
     for (int i=tmp.slicemin();i<=tmp.slicemax();i++)
     {
       tmp(i)=pow(m(i),e);
     }
     return tmp;
   }
