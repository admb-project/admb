
#define HOME_VERSION

#include <fvar.hpp>


  void dvar_vector::fill_multinomial(BOR_CONST int& seed,_CONST dvector& p)
  {
    dvector tmp(indexmin(),indexmax());
    tmp.fill_multinomial(seed,p);
    *(this)=tmp;
  }
