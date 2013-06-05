#include <admodel.h>
#include <df1b2fun.h>
df1b2_compressed_triplet::df1b2_compressed_triplet(int mmin,int mmax,int _n,int _m)
{
  allocate(mmin,mmax,_n,_m);
}

void df1b2_compressed_triplet::initialize(void)
{
  x.initialize();
}

df1b2_compressed_triplet::df1b2_compressed_triplet(void)
{
  n=0;
  m=-1;
}

void df1b2_compressed_triplet::allocate(int mmin,int mmax,int _n,int _m)
{
  n=_n;
  m=_m;
  coords.allocate(1,2,mmin,mmax);
  x.allocate(mmin,mmax);
}

  // this is for a symmetrixc matrix
  df1b2vector operator * (const df1b2_compressed_triplet& _M,const dvector& _v)
  {
    ADUNCONST(df1b2_compressed_triplet,M)
    ADUNCONST(dvector,v)
    
    if (v.indexmin()!=1 ||
         M.get_m() !=v.indexmax() )
    {
      cerr << "Indices do not match in "
        " operator * (const dcompressed_triplet& _M,const dvector& _v)"
        << endl;
      ad_exit(1);
    }
    imatrix& coords= M.get_coords();
    df1b2vector& x= M.get_x();
    df1b2vector tmp(1,v.indexmax());
    int mmin=x.indexmin();
    int mmax=x.indexmax();
    tmp.initialize();
    for (int i=mmin;i<=mmax;i++)
    {
      tmp(coords(1,i))+=x(i)*v(coords(2,i));
      if(coords(1,i)!=coords(2,i))
        tmp(coords(2,i))+=x(i)*v(coords(1,i));
    }
     
    return tmp;
  } 
    
