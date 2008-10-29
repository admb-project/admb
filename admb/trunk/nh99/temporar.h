

#include <fvar.hpp>

  class ttemporary
  {
  public:
    char x[10];
    friend ttemporary operator * (const ttemporary& u,const ttemporary& v);
    friend ttemporary operator / (const ttemporary& u,const ttemporary& v);
    friend ttemporary operator + (const ttemporary& u,const ttemporary& v);
    friend ttemporary operator - (const ttemporary& u,const ttemporary& v);
    ttemporary(const double& u=0.0);
    ttemporary(const ttemporary& u);
    //operator double ();
    operator double () const;
    ttemporary& operator = (const double& d);
    ttemporary& operator = (const ttemporary& d);
  };
