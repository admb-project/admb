void mp(const adstring & v)
{
  cout << v << endl;
}
void mp(const dvar3_array & v)
{
  cout << v << endl;
}
void mp(const dvar3_array & v,int i)
{
  cout << v(i) << endl;
}
void mp(const dvar3_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}
void mp(const dvar4_array & v)
{
  cout << v << endl;
}
void mp(const dvar4_array & v,int i)
{
  cout << v(i) << endl;
}
void mp(const dvar4_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}
void mp(const dvar4_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}
void mp(const d4_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}
void mp(const d4_array & v)
{
  cout << v << endl;
}
void mp(const d4_array & v,int i)
{
  cout << v(i) << endl;
}
void mp(const d4_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}
void mp(const dvar3_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}
void mp(const d3_array & v)
{
  cout << v << endl;
}
void mp(const d3_array & v,int i)
{
  cout << v(i) << endl;
}
void mp(const d3_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void mp(const d3_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}


void mp(const i3_array & v)
{
  cout << v << endl;
}

void mp(const i3_array & v,int i)
{
  cout << v(i) << endl;
}
void mp(const i3_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void mp(const i3_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}

void mp(const i4_array & v)
{
  cout << v << endl;
}

void mp(const i4_array & v,int i)
{
  cout << v(i) << endl;
}
void mp(const i4_array & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void mp(const i4_array & v,int i,int j,int k)
{
  cout << v(i,j,k) << endl;
}
void mp(const i4_array & v,int i,int j,int k,int l)
{
  cout << v(i,j,k,l) << endl;
}

void mp(const dvar_vector & v,const char * s)
{
  if (!strcmp(s,"s"))
  {
    cout << sum(v) << endl;
  }
}

void mp(const dvar_vector & v,int i)
{
  cout << v[i] << endl;
}

void mp(const dvar_vector & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void mp(const dvector & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void mps(const dvar_vector & v,int i)
{
  
  cout << setscientific() << setprecision(5) << v[i] << endl;
}

void mps(const dvar_vector & v)
{
  
  cout << setscientific() << setprecision(5) << v << endl;
}

void mp(const dvar_vector & v)
{
  cout << v << endl;
}

void mp(double v)
{
  cout << v << endl;
}

void mp(const prevariable & v)
{
  cout << v << endl;
}

void mp(const dvector & v)
{
  cout << v << endl;
}

void mp(const ivector & v)
{
  cout << v << endl;
}

void mpp(const dmatrix & v,int i)
{
  cout << setprecision(12) << v(i) << endl;
}

void mpp(const dvar_matrix & v,int i)
{
  cout << setprecision(12) << v(i) << endl;
}

void mp(const dvar_matrix & v,int i)
{
  cout << v(i) << endl;
}

void mp(const dvar_matrix & v,int i,int j)
{
  cout << v(i,j) << endl;
}

void mp(const dvar_matrix & v)
{
  cout << v << endl;
}

void mp(const dmatrix & v)
{
  cout << v << endl;
}

void mp(const imatrix & v)
{
  cout << v << endl;
}

void mp(const imatrix & v,int i)
{
  cout << v(i) << endl;
}
void mp(const imatrix & v,int i,int j)
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
