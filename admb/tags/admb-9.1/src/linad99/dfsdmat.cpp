/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#define SAFE_ARRAYS
#include <fvar.hpp>

#if defined (__WAT32__)
  #include <io.h>
  #include <fcntl.h>
#endif


  #ifdef __MSVC32__
  #include <io.h>
  #include <fcntl.h>

    #define lseek _lseek
    #define  read _read
    #define write _write 
    #define open _open
    #define close _close 

  #endif



#if defined(__TURBOC__) && !defined(__linux__)
  #pragma hdrstop
  #include <iostream.h>
  #include <iomanip.h>
  #include <sys\stat.h>
  #include <fcntl.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #define S_IREAD 0000400
  #define S_IWRITE 0000200
  #include <fcntl.h>
#endif

#ifdef __NDPX__
  #define O_RDONLY 0
  #define O_WRONLY 1
  #define O_RDWR 2
  extern "C"
  {
    int lseek(int, int, int);
    int open(const char*, int);
    int creat(const char*, int);
    int close(int);
    int write(int, char*, int);
  };
#endif

#ifdef __SUN__
  #include <iostream.h>
  #include <fcntl.h>
  #include <sys/stat.h>
  #include <sys/types.h>
  #ifdef __MSC__
    #define lseek _lseek
    #define  read _read
    #define write _write 
    #define open _open
    #define close _close 
  #endif
  #ifndef __MSVC32__
    #include <unistd.h>
  #endif
#endif

#ifdef __GNU__
  //#include <iostream.h>
  #include <fcntl.h>
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*class dfsdmat
{
  double * ptr;
  double ** m;
  double* minp;
  double* maxp;
  int n;
public:
  double * getminp(void){ return minp;}
  int size(void) {return n;} 
  dfsdmat(int n);
  dfsdmat();
  allocate(n);
  ~dfsdmat();
  deallocate(void);
  double& elem(int i,int j);
  double& oprator ()(int i,int j);
};
*/

dfsdmat::dfsdmat(void)
{
  tmp_file=0;
  allocate();
}

void dfsdmat::allocate(void)
{
  shared_memory=0;
  ptr=NULL;
  m=NULL;
  minp=NULL;
  maxp=NULL;
  n=0;
}

dfsdmat::dfsdmat(int _n)
{
  tmp_file=0;
  allocate(_n);
}

void dfsdmat::allocate(int _n)
{
  n=_n;
  if (gradient_structure::get_USE_FOR_HESSIAN())
  {
    ptr=gradient_structure::hessian_ptr;
    shared_memory=1;
    disk_save_flag=1;
  }
  else
  {
    ptr= new double [(n*(n+1))/2];
    shared_memory=0;
    disk_save_flag=0;
  }
  minp=ptr;
  maxp=ptr+((n*(n+1))/2-1);
  m=new double * [n];
  m-=1;
  double * tmp =ptr;
  for (int i=1;i<=n;i++)
  {
    m[i]=tmp-1;
    tmp+=i;
  }
  tmp_file=NULL; 
  /*
  if (!tmp_file) 
  {
    tmp_file=open("fmm_tmp.tmp", O_RDWR | O_CREAT | O_TRUNC |
      O_BINARY , 0777);
    if (tmp_file == -1)
    {
      cerr << "error trying to open temporary hessian file\n";
      ad_exit(1);
    }
  }
   */
}  

dfsdmat::dfsdmat(int _n, BOR_CONST gradient_structure& gs)
{
  tmp_file=0;
  disk_save_flag=1;
  allocate(_n,gs);
}

void dfsdmat::allocate(int _n, BOR_CONST gradient_structure& gs)
{
  n=_n;
  ptr= (double *) gs.ARRAY_MEMBLOCK_BASE;
  shared_memory=1;
  minp=ptr;
  maxp=ptr+((n*(n+1))/2-1);
  m=new double * [n];
  m-=1;
  double * tmp =ptr;
  for (int i=1;i<=n;i++)
  {
    m[i]=tmp-1;
    tmp+=i;
  }
}

dfsdmat::~dfsdmat()
{
  deallocate();
}

void dfsdmat::deallocate()
{
  if (ptr && !shared_memory) 
  {
    delete [] ptr;
    ptr=NULL;
  }
  if (m)
  {
    m+=1;
    delete [] m;
    m=NULL;
  }
  n=0;
  if (tmp_file)
  {
    close(tmp_file);
    tmp_file=0;
  }
}  

#if !defined(OPT_LIB)
double& dfsdmat::elem(int i,int j)
{
  double * tmp= m[i]+j;
  if (tmp < minp || tmp > maxp)
  {
    cerr << "Index out of bounds in double& dfsdmat::elem(int i,int j)"
         << endl;
    ad_exit(1);
  }
  return *tmp;
}

double& dfsdmat::operator () (int i,int j)
{
  double * tmp= m[i]+j;
  if (tmp < minp || tmp > maxp)
  {
    cerr << "Index out of bounds in double& dfsdmat::elem(int i,int j)"
         << endl;
    ad_exit(1);
  }
  return *tmp;
}
#endif

uostream& operator << (BOR_CONST uostream& ofs,BOR_CONST dfsdmat& m)
{
  double * p=((dfsdmat&)m).getminp();
  int nn=((dfsdmat&)m).size();
  nn=(nn*(nn+1))/2;
  for (int i=1;i<=nn;i++)
  {
    (uostream&)ofs << *p++;
  }
  return (uostream&)ofs;
} 

uistream& operator >> (BOR_CONST uistream& _ifs,BOR_CONST dfsdmat& _m)
{
  uistream& ifs= (uistream&) _ifs;
  dfsdmat& m=(dfsdmat&) _m;
  double * p=m.getminp();
  int nn=m.size();
  nn=(nn*(nn+1))/2;
  for (int i=1;i<=nn;i++)
  {
    ifs >> *p++;
  }
  return ifs;
} 

void dfsdmat::save()
{
  if (!tmp_file) 
  {
    tmp_file=open("fmm_tmp.tmp", O_RDWR | O_CREAT | O_TRUNC |
      O_BINARY , 0777);
    if (tmp_file == -1)
    {
      cerr << "error trying to open temporary hessian file\n";
      ad_exit(1);
    }
  }
  int _n=size();
  int nn=(_n*(_n+1))/2;
  lseek(tmp_file,0L,SEEK_SET);
  write(tmp_file,&_n,sizeof(int));
  int num_bytes=write(tmp_file,ptr,nn*sizeof(double));
  if (num_bytes < nn) 
  {
    cerr << "Error writing to temporary hess file in dfsdmat::save()"
         << endl;
  }
  /*
  if (BOR_CONST ptr && !shared_memory) 
  {
    delete [] ptr;
    ptr=NULL;
  }
  if (m)
  {
    m+=1;
    delete [] m;
    m=NULL;
  }
  n=0;
 */
}

void dfsdmat::restore()
{
  int _n=0;
  lseek(tmp_file,0L,SEEK_SET);
  read(tmp_file,&_n,sizeof(int));
  int nn=(_n*(_n+1))/2;
  //if (!shared_memory) allocate(_n);
  int num_bytes=read(tmp_file,ptr,nn*sizeof(double));
  if (num_bytes < nn) 
  {
    cerr << "Error reading from temporary hess file in dfsdmat::save()"
         << endl;
  }
  if (tmp_file) close(tmp_file);
  tmp_file=NULL;
}


