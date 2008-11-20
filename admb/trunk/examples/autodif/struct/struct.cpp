#include <fvar.hpp>
class const_parameters
{
public:
  dvector * pv;
  dvector * pw;
  const_parameters(int n1,int n2) {pv=new dvector(1,n1);pw=new dvector(1,n2);}
  ~const_parameters() {delete pv; delete pw;}
};

class var_parameters
{
public:
  dvector * pv;
  dvar_vector * pw;
  var_parameters(const_parameters& cp)
  {
    pv=new dvector(*(cp.pv));
    pw=new dvar_vector(*(cp.pw));
  }
  ~var_parameters() {delete pv; delete pw;}
};

void fcomp(var_parameters&);

main()
{
  const_parameters cp(5,7);
 (*cp.pv).fill_seqadd(1,2);
 (*cp.pw).fill_seqadd(0,2.5);
 gradient_structure gs;
 {
   fcomp(cp);
 }
}

void fcomp(var_parameters& vp)
{
  dvector& v=*(vp.pv);
  dvar_vector& w=*(vp.pw);
  cout << *(vp.pw) << "\n";
  cout << *(vp.pv) << "\n\n";
  cout << v << "\n";
  cout << w << "\n\n";

}