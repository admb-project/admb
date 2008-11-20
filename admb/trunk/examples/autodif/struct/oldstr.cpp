
#include <fvar.hpp>

void fcomp(dvector& u,dvector& v,dvar_vector& w);

int main()
{
  dvector u(1,3);
  dvector v(1,5);
  u.fill_seqadd(-1,1);
  v.fill_seqadd(1,2);
 gradient_structure gs;
 {
   dvar_vector w(1,7);
   w.fill_seqadd(0,2.5);
   fcomp(u,v,w);
 }
  return 0;
}

void fcomp(dvector& u,dvector& v,dvar_vector& w)
{
  cout << u << "\n";
  cout << v << "\n";
  cout << w << "\n\n";
}
