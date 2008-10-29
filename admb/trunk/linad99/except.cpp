#include <fvar.hpp>

  vector_range_exception::vector_range_exception(int i,int imin,int imax)
  {
      cerr << "Index " << i << " out of bounds minvalue = " << imin
           << " maxvalue = " << imax << endl;
  }
