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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
  multi_index::multi_index(int min,int max,int dim) :
    mind(min),maxd(max),depth(min), index(1, dim)
  {
    index=min;
  }
  void multi_index::operator ++ (void)
  {
    int imin=index.indexmin();
    int imax=index.indexmax();
    index(imin)++;
    int tmpdepth=1;
    for (int i=imin;i<=imax;i++)
    {
      if (index(i)>maxd)
      {
        if (i<imax)
        {
          index(i+1)++;
        }
        index(i)=mind;
        tmpdepth=i+1;
      }
      else
      {
        break;
      }
    }
    if (tmpdepth>depth)
      depth =tmpdepth;
  }
  int multi_index::get_offset(void)
  {
    int imin=index.indexmin();
    int imax=index.indexmax();
    int offset=index(imin)-mind;
    int mx=min(depth,imax);
    int sz=maxd-mind+1;
    for (int i=imin+1;i<=mx;i++)
    {
      offset+=int(pow(double(sz),i-imin))*(index(i)-mind);
    }
    return offset;
  }

/**
 * Description not yet available.
 * \param
 */
  void multi_index::initialize(void)
  {
    index=mind;
    depth=mind;
  }
