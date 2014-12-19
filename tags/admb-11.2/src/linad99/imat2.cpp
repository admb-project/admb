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
#include "fvar.hpp"
#include "admb_messages.h"
#ifdef __TURBOC__
  #pragma hdrstop
#endif

#if !defined(OPT_LIB)

/**
 * Description not yet available.
 * \param
 */
 int& imatrix::operator() (int i,int j)
 {
   if (i < rowmin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low",
     "int& imatrix::operator() (int i, int j)", rowmin(), rowmax(), i);
   }
   if (i > rowmax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high",
     "int& imatrix::operator() (int i, int j)", rowmin(), rowmax(), i);
   }
   if (j < (*this)(i).indexmin())
   {
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too low",
     "int& imatrix::operator() (int i, int j)",
     (*this)(i).indexmin(), (*this)(i).indexmax(), j);
   }
   if (j > (*this)(i).indexmax())
   {
     ADMB_ARRAY_BOUNDS_ERROR("matrix bound exceeded -- row index too high",
     "int& imatrix::operator() (int i, int j)",
     (*this)(i).indexmin(), (*this)(i).indexmax(), j);
   }
   return(*((*(m+i)).v+j));
 }

/**
 * Description not yet available.
 * \param
 */
const int& imatrix::operator()(int i, int j) const
 {
     if (i<rowmin())
     {
       cerr << "matrix bound exceeded -- row index too low in "
       "imatrix::operator()(int, int)"
             << "\nvalue was " << i << endl;
       ad_exit(21);
     }
     if (i>rowmax())
     {
       cerr << "matrix bound exceeded -- row index too high in "
       "imatrix::operator()(int, int)"
             << "\nvalue was " << i << endl;
       ad_exit(22);
     }
     if (j<(*this)(i).indexmin())
     {
       cerr << "matrix bound exceeded -- column index too low in "
       "imatrix::operator()(int, int)"
            << "\nvalue was " << j << endl;
       ad_exit(21);
     }
     if (j>(*this)(i).indexmax())
     {
       cerr << "matrix bound exceeded -- column index too high in "
       "imatrix::operator()(int, int)"
            << "\nvalue was " << j << endl;
       ad_exit(22);
     }
   return(*((*(m+i)).v+j));
 }
#endif
