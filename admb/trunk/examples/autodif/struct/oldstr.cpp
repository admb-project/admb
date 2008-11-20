
#include <fvar.hpp>

void fcomp(var_parameters&);

main()
{
  dvector u(1,3);
  dvector v(1,5);
  dvector w(1,7);
  u.fill_seqadd(-1,1);
  v.fill_seqadd(1,2);
  w.fill_seqadd(0,2.5);
 gradient_structure gs;
 {
   fcomp(u,v,w);
 }
}

void fcomp(dvector& u,dvector& v,dvar_vector& w)
{
  cout << u << "\n";
  cout << v << "\n";
  cout << w << "\n\n";
}
