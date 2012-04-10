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
#include <fvar.hpp>

/**
 * Description not yet available.
 * \param
 */
  vector_range_exception::vector_range_exception(int i,int imin,int imax)
  {
      cerr << "Index " << i << " out of bounds minvalue = " << imin
           << " maxvalue = " << imax << endl;
  }
