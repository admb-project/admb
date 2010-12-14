/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>

  vector_range_exception::vector_range_exception(int i,int imin,int imax)
  {
      cerr << "Index " << i << " out of bounds minvalue = " << imin
           << " maxvalue = " << imax << endl;
  }
