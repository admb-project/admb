DATA_SECTION
  init_int nobs
  init_vector y(1,nobs)
  vector predm(1,nobs)
PARAMETER_SECTION
  init_number m1
  init_number m2
  init_number cp
  objective_function_value f
PROCEDURE_SECTION

  double s=1;
  switch (current_phase())
  {
  case 1:
    s=1.0;
    break;
  case 2:
    s=10.0;
    break;
  case 3:
    s=100.0;
    break;
  default:
    s=1000.0;
    break;
  }

  for (int i=1;i<=nobs;i++)
  {
    dvariable p=f1(i,cp,s);
    dvariable m=p*m1+(1.0-p)*m2;
    predm(i)=value(m);
    f+=square(y(i)-m);
  }
  
REPORT_SECTION

  report << predm << endl;

GLOBALS_SECTION

  #include <admodel.h>

  dvariable f1(int i,const prevariable& cp,double s)
  {
    dvariable z=s*(cp-double(i));
    if (value(z)<20.)
    {
      return 1.0/(1+exp(z));
    }
    else
    {
      return exp(-z)/(1.0+exp(-z));
    }
  }

