#include <iostream>
#include <sstream>
#include <fvar.hpp>
#include <admodel.h>
//#include "contrib.h"

/**
Write out gradients into external file.

Created by Jiashen Tang 
*/
void save_gradients(const dvector& g)
{
  int ph = initial_params::current_phase;
  if (ph > 0)
  {
    std::ostringstream cvt;
    cvt << ph;
    std::string phn = cvt.str();
    std::string ofsn;
    // for last phase, change the file name to "gradient.dat"
    if (ph < initial_params:: max_number_phases)
      ofsn = "gradient." + phn;
    else
      ofsn = "gradient.dat";
            
    const char* ofsnc= ofsn.c_str();
         
    ofstream ofs(ofsnc);
    int offset = 1;
    initial_params::save_all(ofs, 6, g);
    ofs.close();
  }
}
