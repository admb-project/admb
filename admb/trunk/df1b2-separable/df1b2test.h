
#if !defined(__DF1B2TEST__)
#  define __DF1B2TEST__ 
#if defined(__GNUC__)
//#pragma interface
#endif
#include <df1b2fun.h>
#include <admodel.h>

  class df1b2function2c
  {
  public:
    double (*f)(double,double); 
    double (*df)(double,double); 
    double (*d2f)(double,double); 
    double (*d3f)(double,double); 
    adstring funname;

    df1b2function2c
    (
      double (*_f)(double,double),
      double (*_df)(double,double),
      double (*_d2f)(double,double),
      double (*_d3f)(double,double),
      const adstring & funame="unnamed"
    );

    df1b2variable operator () (const df1b2variable& x,double y);
    df1b2variable operator () (double x,const df1b2variable& y);
  }; 

#endif   //if !defined(__DF1B2TEST__)
