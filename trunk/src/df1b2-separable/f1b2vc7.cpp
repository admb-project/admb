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
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
df1b2vector& df1b2vector::shift(int min)
{
  v += indexmin()-min;
  index_max=index_max-index_min+min;
  index_min=min;
  //shape->shift(min);
  return *this;
}

/*
 df1b2vector::df1b2vector(const predf1b2vector& pdv)
 {
#ifndef OPT_LIB
   if (pdv.ub<pdv.lb)
   {
     cerr << "lower index greater than upper index in df1b2vector::"
       " dvar-vector(const predf1b2vector&) " << endl;
     ad_exit (1);
   }
   if ((pdv.lb<pdv.p->indexmin()) || (pdv.lb>pdv.p->indexmax()))
   {
     cerr << "lower index out of bounds in df1b2vector::"
       " operator(int lb,int ub) " << endl;
     ad_exit (1);
   }

   if ((pdv.ub<pdv.p->indexmin()) || (pdv.ub>pdv.p->indexmax()))
   {
     cerr << " upper index out of bounds in df1b2vector::"
       " operator(int lb,int ub) " << endl;
     ad_exit (1);
   }
#endif
   index_min=pdv.lb;
   index_max=pdv.ub;
   shape=pdv.p->shape;
   (shape->ncopies)++;
   v = pdv.p->v;
 }
*/
