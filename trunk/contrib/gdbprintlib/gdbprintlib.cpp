#include "gdbprintlib.h"

void pad(const adstring & v)
{
  cout << v << endl;
}

void pad(const dvar3_array & v)
{
  cout << v << endl;
}

void pad(const dvar3_array & v,int i)
{
  cout << v(i) << endl;
}

void pad(const dvar3_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void pad(const dvar4_array & v)
{
  cout << v << endl;
}

void pad(const dvar4_array & v,int i)
{
  cout << v(i) << endl;
}

void pad(const dvar4_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void pad(const dvar4_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}

void pad(const d4_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}

void pad(const d4_array & v)
{
  cout << v << endl;
}

void pad(const d4_array & v,int i)
{
  cout << v(i) << endl;
}

void pad(const d4_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void pad(const dvar3_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}

void pad(const d3_array & v)
{
  cout << v << endl;
}

void pad(const d3_array & v,int i)
{
  cout << v(i) << endl;
}

void pad(const d3_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void pad(const d3_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}

void pad(const i3_array & v)
{
  cout << v << endl;
}

void pad(const i3_array & v,int i)
{
  cout << v(i) << endl;
}

void pad(const i3_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void pad(const i3_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}

void pad(const i4_array & v)
{
  cout << v << endl;
}

void pad(const i4_array & v,int i)
{
  cout << v(i) << endl;
}
void pad(const i4_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void pad(const i4_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}
void pad(const i4_array & v,int i,int j,int k,int l)
{
  cout << v(i,j,k,l) << endl;
}

void pad(const dvar_vector & v,const char * s)
{
  if (!strcmp(s,"s"))
  {
    cout << sum(v) << endl;
  }
}

void pad(const dvar_vector & v,int i)
{
  cout << v[i] << endl;
}

//void pad(const dvar_vector & v,int i,int j)
//{
//  cout << v(i,j) << endl;
//}

//void pad(const dvector & v,int i,int j)
//{
//  cout << v(i,j) << endl;
//}

void pads(const dvar_vector & v,int i)
{
  cout << setscientific() << setprecision(5) << v[i] << endl;
}

void pads(const dvar_vector & v)
{
  cout << setscientific() << setprecision(5) << v << endl;
}

void pad(const dvar_vector & v)
{
  cout << v << endl;
}

void pad(double v)
{
  cout << v << endl;
}

void pad(const prevariable & v)
{
  cout << v << endl;
}

void pad(const dvector & v)
{
  cout << v << endl;
}

void pad(const ivector & v)
{
  cout << v << endl;
}

void padp(const dmatrix & v,int i)
{
  cout << setprecision(12) << v(i) << endl;
}

void padp(const dvar_matrix & v,int i)
{
  cout << setprecision(12) << v(i) << endl;
}

void pad(const dvar_matrix & v,int i)
{
  cout << v(i) << endl;
}

void pad(const dvar_matrix & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void pad(const dvar_matrix & v)
{
  cout << v << endl;
}

void pad(const dmatrix & v)
{
  cout << v << endl;
}

void pad(const imatrix & v)
{
  cout << v << endl;
}

void pad(const imatrix & v,int i)
{
  cout << v(i) << endl;
}
void pad(const imatrix & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void sumprint(const dvar_vector & v)
{
  cout << sum(v) << endl;
}

void sumprint(const dvector & v)
{
  cout << sum(v) << endl;
}

void sumprint(const ivector & v)
{
  cout << sum(v) << endl;
}

void sumprint(const dvar_matrix & v,int i)
{
  cout << v(i) << endl;
}

void sumprint(const dvar_matrix & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void sumprint(const dvar_matrix & v)
{
  cout << sum(v) << endl;
}

void sumprint(const dmatrix & v)
{
  cout << sum(v) << endl;
}

void sumprint(const imatrix & v)
{
  cout << sum(v) << endl;
}
