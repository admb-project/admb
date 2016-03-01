/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>
#include <fcntl.h>

#if defined (__WAT32__)
  #include <io.h>
#endif

#ifdef _MSC_VER
  #include <io.h>
  #define lseek _lseek
  #define  read _read
  #define write _write
  #define open _open
  #define close _close
  #ifdef _M_X64
  typedef __int64 ssize_t;
  #else
  typedef int ssize_t;
  #endif
#else
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

#if defined(__TURBOC__)
  #pragma hdrstop
  #include <iostream.h>
  #include <iomanip.h>
  #include <sys\stat.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #define S_IREAD 0000400
  #define S_IWRITE 0000200
#endif

#if !defined(OPT_LIB) || defined(__MINGW64__) || defined(_MSC_VER)
  #include <cassert>
  #include <climits>
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
  #include <sys/stat.h>
  #include <sys/types.h>
  #ifdef _MSC_VER
    #define lseek _lseek
    #define  read _read
    #define write _write
    #define open _open
    #define close _close
  #endif
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

/**
Default constructor
*/
dfsdmat::dfsdmat():
  disk_save_flag(1)
{
  tmp_file = 0;
  allocate();
}
/**
Initialize members but does not allocate.
*/
void dfsdmat::allocate()
{
  shared_memory=0;
  ptr=NULL;
  m=NULL;
  minp=NULL;
  maxp=NULL;
  n=0;
}

/**
 * Description not yet available.
 * \param
 */
dfsdmat::dfsdmat(int _n)
{
  tmp_file=0;
  allocate(_n);
}

/**
 * Description not yet available.
 * \param
 */
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
  tmp_file = 0;
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

/**
 * Description not yet available.
 * \param
 */
dfsdmat::dfsdmat(int _n, const gradient_structure& gs)
{
  tmp_file=0;
  disk_save_flag=1;
  allocate(_n,gs);
}

/**
 * Description not yet available.
 * \param
 */
void dfsdmat::allocate(int _n, const gradient_structure& gs)
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

/**
Destructor
*/
dfsdmat::~dfsdmat()
{
  deallocate();
}

/**
 * Description not yet available.
 * \param
 */
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

#if !defined(OPT_LIB) || defined(__INTEL_COMPILER)

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
uostream& operator<<(const uostream& ofs, const dfsdmat& m)
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

/**
 * Description not yet available.
 * \param
 */
uistream& operator>>(const uistream& _ifs, const dfsdmat& _m)
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
/**
Save values to file.
*/
void dfsdmat::save()
{
  if (tmp_file < 0)
  {
    tmp_file=open("fmm_tmp.tmp", O_RDWR | O_CREAT | O_TRUNC |
      O_BINARY , 0777);
    if (tmp_file < 0)
    {
      cerr << "error trying to open temporary hessian file\n";
      ad_exit(1);
    }
  }
  lseek(tmp_file, 0L, SEEK_SET);

  unsigned int _n = (unsigned int)size();
  unsigned int nn = (_n*(_n+1))/2;
#ifdef OPT_LIB
  write(tmp_file,&_n,sizeof(int));
#else
  ssize_t ret = write(tmp_file,&_n,sizeof(int));
  assert(ret != -1);
#endif
#ifdef __MINGW64__
  size_t size = nn * sizeof(double);
  assert(size <= UINT_MAX);
  ssize_t num_bytes = write(tmp_file, ptr, (unsigned int)size);
#else
  ssize_t num_bytes=write(tmp_file,ptr,nn*sizeof(double));
#endif
  if (num_bytes <= 0)
  {
    cerr << "Error writing to temporary hess file in dfsdmat::save()"
         << endl;
  }
  /*
  if (const ptr && !shared_memory)
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
/**
Restore values to file.
*/
void dfsdmat::restore()
{
  int _n=0;
  lseek(tmp_file,0L,SEEK_SET);
#if defined(OPT_LIB) && !defined(_MSC_VER)
  read(tmp_file,&_n,sizeof(int));
#else
  ssize_t ret = read(tmp_file,&_n,sizeof(int));
  assert(ret != -1);
  assert(_n > 0);
#endif
  size_t nn = (size_t)((_n * (_n + 1))/2);
  //if (!shared_memory) allocate(_n);
#ifdef __MINGW64__
  size_t size = nn * sizeof(double);
  assert(size <= UINT_MAX);
  ssize_t num_bytes=read(tmp_file, ptr, (unsigned int)size);
#else
  ssize_t num_bytes=read(tmp_file,ptr,nn*sizeof(double));
#endif
  if (num_bytes <= 0)
  {
    cerr << "Error reading from temporary hess file in dfsdmat::save()"
         << endl;
  }
  if (tmp_file) close(tmp_file);
  tmp_file = 0;
}
