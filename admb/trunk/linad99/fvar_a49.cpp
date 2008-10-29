#define HOME_VERSION
//COPYRIGHT (c) 1991 OTTER RESEARCH LTD
#include <fvar.hpp>

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <math.h>

  dvariable var(_CONST dvar_vector& v)
  {
    dvariable tmp;
    RETURN_ARRAYS_INCREMENT();
    tmp=norm(v)/sqrt(double(v.size()));
    dvariable tmp1;
    tmp1=mean(v);
    RETURN_ARRAYS_DECREMENT();
    return(tmp*tmp-tmp1*tmp1);
  }

  dvariable std_dev(_CONST dvar_vector& v)
  {
    dvariable tmp;
    RETURN_ARRAYS_INCREMENT();
    tmp=norm(v)/sqrt(double(v.size()));
    dvariable tmp1;
    tmp1=mean(v);
    RETURN_ARRAYS_DECREMENT();
    return(sqrt(tmp*tmp-tmp1*tmp1));
  }

  dvariable mean(_CONST dvar_vector& v)
  {
    dvariable tmp;
    RETURN_ARRAYS_INCREMENT();
    tmp=sum(v)/double(v.size());
    RETURN_ARRAYS_DECREMENT();
    return(tmp);
  }

#undef HOME_VERSION
