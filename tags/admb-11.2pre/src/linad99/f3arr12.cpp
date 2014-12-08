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
#ifndef OPT_LIB

/**
 * Description not yet available.
 * \param
 */
const prevariable dvar3_array::operator()(int k, int i, int j) const
    {
        if (k<slicemin())
        {
          cerr << "array bound exceeded -- slice index too"
           " low in d3_array::operator(int,int,int)\n"
           " mimumum bound is " << slicemin() << "  you have "
           << k << "\n";
          ad_exit(1);
        }
        if (k>slicemax())
        {
          cerr << "array bound exceeded -- slice index too"
           " high in d3_array::operator(int,int,int)\n"
           " maximum bound is " << slicemax() << "  you have "
           << k << "\n";
          ad_exit(1);
        }
        return ( ((t[k].m[i]).va)+j );
    }

/**
 * Description not yet available.
 * \param
 */
const dvar_vector& dvar3_array::operator()(int k, int i) const
    {
        if (k<slicemin())
        {
          cerr << "array bound exceeded -- slice index too"
           " low in d3_array::operator(int,int)\n"
           " mimumum bound is " << slicemin() << "  you have "
           << k << "\n";
          ad_exit(1);
        }
        if (k>slicemax())
        {
          cerr << "array bound exceeded -- slice index too"
           " high in d3_array::operator(int,int)\n"
           " maximum bound is " << slicemax() << "  you have "
           << k << "\n";
          ad_exit(1);
        }
      return ( t[k].m[i]);
    }
#endif
