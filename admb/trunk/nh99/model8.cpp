
  #include <admodel.h>

 //char cc[40]={"Copyright (c) 1993,1994 Otter Research Ltd"};
  objective_function_value * objective_function_value::pobjfun=NULL;
  double objective_function_value::gmax=0;

  objective_function_value::objective_function_value() {pobjfun=this;}
  objective_function_value& objective_function_value::operator =
    (_CONST prevariable& v)
  {
    prevariable::operator = (v);
    return *this;
  }
  objective_function_value& objective_function_value::operator =
    (CGNU_DOUBLE v)
  {
    prevariable::operator = (v);
    return *this;
  }
