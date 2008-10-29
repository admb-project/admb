

  int operator >= (const df1b2variable& x,const df1b2variable& y);
  int operator >= (double x,const df1b2variable& y);
  int operator >= (const df1b2variable& x,double y);
  
  int operator <= (const df1b2variable& x,const df1b2variable& y);
  int operator <= (double x,const df1b2variable& y);
  int operator <= (const df1b2variable& x,double y);

  int operator > (const df1b2variable& x,const df1b2variable& y);
  int operator > (double x,const df1b2variable& y);
  int operator > (const df1b2variable& x,double y);
  
  int operator < (const df1b2variable& x,const df1b2variable& y);
  int operator < (double x,const df1b2variable& y);
  int operator < (const df1b2variable& x,double y);
  
  int operator == (const df1b2variable& x,const df1b2variable& y);
  int operator == (double x,const df1b2variable& y);
  int operator == (const df1b2variable& x,double y);
  
   dvariable posfun(const dvariable&x,const double eps);
   df1b2variable posfun(_CONST df1b2variable&x,const double eps);
