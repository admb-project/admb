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
#include <cstring>
#if !defined(__BORLANDC__) && !defined(_MSC_VER)
#include <inttypes.h>
#endif
#include <df1b2fun.h>
#include "admb_messages.h"
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

do_naught_kludge df1b2_init_number::do_naught_kludge_a;

//#define  ADDEBUG_PRINT
#if defined(ADDEBUG_PRINT)
    int addebug_count=0;
#endif

//df1b2_gradlist * f1b2gradlist = NULL;
int max_num_init_df1b2variable=500;

char AD_allocation_error_message[]="Error: trying to allocate memory for ";

unsigned int get_f1b2buffer_size(const char* s);

#if defined(CHECK_COUNT)
  int df1b2_gradlist::ncount_check=-1;
#endif

adpool * df1b2variable::pool= new adpool();

/**
 * Description not yet available.
 * \param
 */
df1b2function1::df1b2function1(double (*_f)(double),double (*_df)(double),
    double (*_d2f)(double),double (*_d3f)(double), const adstring& _s )
{
  f=_f;
  df=_df;
  d2f=_d2f;
  d3f=_d3f;
  funname=_s;
}

/**
 * Description not yet available.
 * \param
 */
ad_dstar::~ad_dstar(void)
{
  if (p) delete []p;
  p = 0;
}

/**
 * Description not yet available.
 * \param
 */
unsigned int df1b2variable::get_blocksize()
{
  return get_blocksize(nvar);
}

/**
 * Description not yet available.
 * \param
 */
unsigned int df1b2variable::get_blocksize(const unsigned int n)
{
  return 6*n+5;
  //return 6*n+4;
}

/**
 * Description not yet available.
 * \param
 */
void df1b2variable::set_blocksize()
{
  blocksize=get_blocksize();
  pool->set_size(sizeof(double)*blocksize);
  pool->nvar=df1b2variable::get_nvar();
}

//init_df1b2variable * init_df1b2variable::list[max_num_init_df1b2variable];
init_df1b2variable ** init_df1b2variable::list=0;
unsigned int df1b2variable::nvar = 0;
int df1b2variable::minder=0;
int df1b2variable::maxder=0;
unsigned int df1b2variable::blocksize=0;
int init_df1b2variable::num_variables=0;
int df1b2_gradlist::no_derivatives=0;
int df1b2variable::passnumber=0;
unsigned int ad_dstar::n=0;

void ad_read_pass2(void);
// should inline this
#if !defined(__BORLANDC__)
int adptr_diff(void* x, void* y)
{
  intptr_t a = (intptr_t)x;
  intptr_t b = (intptr_t)y;
  ptrdiff_t diff = a - b;
#ifndef OPT_LIB
  assert(diff <= INT_MAX);
#endif
  return (int)diff;
}
#endif

#if defined(__CHECK_MEMORY__)
  int sanity_flag=0;
#endif

/**
Initialize
*/
void df1b2variable::initialize(void)
{
#if defined(__CHECK_MEMORY__)
  if (sanity_flag)
  {
    df1b2variable::pool->sanity_check();
  }
#endif
  unsigned int nvar=((twointsandptr*)ptr)->ptr->nvar;
  initialize(nvar);
}

/**
Initialize nvariables

/param n nvariables
*/
void df1b2variable::initialize(const unsigned int n)
{
  //int bs=get_blocksize(n);
  //for (double * tmp=ptr+2;tmp<ptr+bs-1;*tmp++=0);
  size_t nbytes = (get_blocksize(n) - 2) * sizeof(double);
  memset(ptr + 2, 0, nbytes);
}

/**
 * Description not yet available.
 * \param
 */
  void init_df1b2variable::set_u_dot(void)
  {
    //int j;
    double uvalue=*get_u();
    initialize();
    int nder=maxder-minder+1;
    for (int i=0;i<nder;i++)
    {
      u_dot[i]=0.0;
    }
    if (ind_index>=minder && ind_index<=maxder)
    {
      int offset= ind_index-minder;
      u_dot[offset]=1.0;
    }
    *get_u()=uvalue;
  }

/**
 * Description not yet available.
 * \param
 */
  void init_df1b2variable::operator = (double d)
  {
    //int nc=*ncopies;
    initialize();
    //*ncopies=nc;
    if (ind_index>=minder && ind_index<=maxder)
    {
      int offset= ind_index-minder;
      u_dot[offset]=1.0;
    }
    get_ind_index()=-1;
    *u=d;
  }

/**
 * Description not yet available.
 * \param
 */
  df1b2variable::df1b2variable(const df1b2variable& v)
  {
#if defined(__CHECK_MEMORY__)
    if (pchecker)
    {
      if (v.ptr == pchecker)
      {
        cout << " copy constructor called  " << endl;
      }
    }
#endif
    if (v.ptr)
    {
      ptr=v.ptr;
      ncopies=v.ncopies;
      (*ncopies)++;
      u=v.u;
      u_dot=v.u_dot;
      u_bar=v.u_bar;
      u_dot_bar=v.u_dot_bar;
      u_tilde=v.u_tilde;
      u_dot_tilde=v.u_dot_tilde;
      u_bar_tilde=v.u_bar_tilde;
      u_dot_bar_tilde=v.u_dot_bar_tilde;
    }
    else
    {
      ptr=NULL;
      ncopies=NULL;
      u=NULL;
      u_dot=NULL;
      u_bar=NULL;
      u_dot_bar=NULL;
      u_tilde=NULL;
      u_dot_tilde=NULL;
      u_bar_tilde=NULL;
      u_dot_bar_tilde=NULL;
    }
  }

  adkludge1 * adkludgexxx;

typedef init_df1b2variable * PINIT_DF1B2VARIABLE;

/**
 * Description not yet available.
 * \param
 */
  init_df1b2variable::init_df1b2variable(double v) : df1b2variable(adkludgexxx)
  {
    ++num_variables;
   /*
    if (list==0)
    {
      list =new PINIT_DF1B2VARIABLE[max_num_init_df1b2variable];
    }
    if (++num_variables>= max_num_init_df1b2variable)
    {
      cerr << "Need to increase the maximum number of init_df1b2variables"
       << endl << "Use command line option -mni N" << endl;
    }

    if (num_variables>=df1b2variable::nvar)
    {
      cerr << "Maximum number of independent variables exceeded"
           << endl;
      cerr << "current max is " << df1b2variable::nvar << endl;
    }
    list[num_variables]=this;
    */
    ind_index=num_variables;
    *get_u()=v;
    if (num_variables>=minder && num_variables<=maxder)
    {
      //int offset= num_variables-minder;
      //u_dot[offset]=1.0;
    }
  }
/**
Destructor
*/
df1b2variable::~df1b2variable()
{
  deallocate();
}
/**
If no other copies exist, free df1b2variable::ptr.
*/
void df1b2variable::deallocate(void)
{
  if (ptr)
  {
#if defined(__CHECK_MEMORY__)
    if (pchecker)
    {
      if (ptr == pchecker)
      {
        cout << "destructor called  " << endl;
      }
    }
#endif
    if (ncopies && *ncopies)
    {
      (*ncopies)--;
    }
    else
    {
      if (!df1b2_gradlist::no_derivatives)
        f1b2gradlist->write_save_pass2_tilde_values(this);
      ((twointsandptr*)ptr)->ptr->free(ptr);

      ptr = 0;
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
  void init_df1b2vector::set_value(const dvector& v)
  {
    int mmin=indexmin();
    int mmax=indexmax();
    if (v.indexmin() != mmin || v.indexmax() != mmax )
    {
      cerr << "incompatible shape in "
        "init_df1b2vector::set_value(const dvector& v)" << endl;
    }

    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i)=v(i);
    }
  }

/**
Default constructor
*/
init_df1b2vector::init_df1b2vector()
{
  allocate();
}
/**
Constructs vector with range lb to ub.
*/
init_df1b2vector::init_df1b2vector(int lb, int ub)
{
  allocate(lb, ub);
}

/**
 */
void init_df1b2vector::allocate(int lb,int ub)
{
  init_df1b2variable::num_variables= 0;
  index_min=lb;
  index_max=ub;
  ncopies=new int;
  *ncopies=0;
  int size = ub < lb ? 0 : indexmax() - indexmin() + 1;
  if (init_df1b2variable::list == 0)
  {
    max_num_init_df1b2variable
      = max(size, max_num_init_df1b2variable);

    init_df1b2variable::list = new PINIT_DF1B2VARIABLE[static_cast<unsigned int>(
      max_num_init_df1b2variable < 0 ? 0 : max_num_init_df1b2variable)];
    if (init_df1b2variable::list == 0)
    {
      cerr << "Error allocating memory for init_df1b2variable::list" << endl;
      ad_exit(1);
    }
  }

// ****************************************
  trueptr = new init_df1b2variable[static_cast<unsigned int>(size)];
  if (trueptr == 0)
  {
    cerr << "Error allocating memory for init_df1b2variable" << endl;
    ad_exit(1);
  }
  //AD_ALLOCATE(trueptr,init_df1b2variable,size,df1b2_gradlist)
// ****************************************

  ptr = trueptr;
  ptr -= lb;
}

/**
 * Description not yet available.
 * \param
 */
  void init_df1b2vector::reallocate()
  {
    int mmin=indexmin();
    int mmax=indexmax();
    for (int i=mmin;i<=mmax;i++)
    {
      ptr[i].allocate();
    }
  }
/**
Do not allocate, but just initialize class members.
*/
void init_df1b2vector::allocate(void)
{
  //deallocate(); a// don;t know why this was ever here DF 6june09
  index_min = 0;
  index_max = -1;
  ncopies = NULL;
  trueptr = NULL;
  ptr = NULL;
}
/**
Destructor
*/
init_df1b2vector::~init_df1b2vector()
{
  if (ncopies)
  {
    if (*ncopies)
      (*ncopies)--;
    else
    {
      if (trueptr)
      {
        delete [] trueptr;
        trueptr = NULL;
      }
      delete ncopies;
      ncopies = NULL;
    }
  }
}
/**
Similar to destructor.
*/
void init_df1b2vector::deallocate()
{
  if (ncopies)
  {
    if (*ncopies)
      (*ncopies)--;
    else
    {
      delete [] trueptr;
      trueptr = NULL;
      delete ncopies;
      ncopies = NULL;
    }
  }
}
/**
Copy constructor
*/
init_df1b2vector::init_df1b2vector(const init_df1b2vector& v)
{
  ncopies = v.ncopies;
  if (v.ncopies)
  {
    (*ncopies)++;
    trueptr = v.trueptr;
    ptr = v.ptr;
    index_min = v.index_min;
    index_max = v.index_max;
  }
  else
  {
    allocate();
  }
  //cout << *ncopies << endl;
}

/**
 * Description not yet available.
 * \param
 */
  double& value(const df1b2variable& _x)
  {
    ADUNCONST(df1b2variable,x)
    return *x.u;
  }

/**
 * Description not yet available.
 * \param
 */
  df1b2function2::df1b2function2(double (*_f)(double,double),
  double (*_df1)(double,double),double (*_df2)(double,double),
  double (*_d2f11)(double,double),
    double (*_d2f12)(double,double),
    double (*_d2f22)(double,double),
    double (*_d3f111)(double,double),
    double (*_d3f112)(double,double),
    double (*_d3f122)(double,double),
    double (*_d3f222)(double,double), const adstring& _s)
  {
    f=_f;
    df1=_df1; df2=_df2;
    d2f11=_d2f11; d2f12=_d2f12; d2f22=_d2f22;
    d3f111=_d3f111;
    d3f112=_d3f112;
    d3f122=_d3f122;
    d3f222=_d3f222;
    funname=_s;
  }
  typedef double (* PTDF)(double);

/**
 * Description not yet available.
 * \param
 */
  PTDF tan_address()
  {
    return &tan;
  }

/**
 * Description not yet available.
 * \param
 */
  df1b2variable df1b2function1::operator () (const df1b2variable& _x)
  {
    ADUNCONST(df1b2variable,x)
    df1b2variable z;
    double xu=*x.get_u();
    double * xd=x.get_u_dot();
    double * zd=z.get_u_dot();
    *z.get_u()=(*f)(xu);
    double dfx=(*df)(xu);
    for (unsigned int i=0;i<df1b2variable::nvar;i++)
    {
      *zd++ =dfx * *xd++;
    }

    // WRITE WHATEVER ON TAPE
    //df1b2tape->set_tapeinfo_header(&x,&z,this,xd);
    // save stuff for first reverse pass
    // need &x, &z, this,
    if (!df1b2_gradlist::no_derivatives)
    {
      if ((void*)(f)==tan_address())
        f1b2gradlist->write_pass1x(&x,&z,this);
      else
        f1b2gradlist->write_pass1(&x,&z,this);
    }
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
  df1b2variable df1b2function2::operator () (const df1b2variable& _x,
    const df1b2variable& _y)
  {
    ADUNCONST(df1b2variable,x)
    ADUNCONST(df1b2variable,y)
    df1b2variable z;
    double xu=*x.get_u();
    double yu=*y.get_u();
    double * xd=x.get_u_dot();
    double * yd=y.get_u_dot();
    double * zd=z.get_u_dot();
    *z.get_u()=(*f)(xu,yu);
    double dfx=(*df1)(xu,yu);
    double dfy=(*df2)(xu,yu);
    for (unsigned int i=0;i<df1b2variable::nvar;i++)
    {
      *zd++ =dfx * *xd++ + dfy * *yd++;
    }

    // WRITE WHATEVER ON TAPE
    if (!df1b2_gradlist::no_derivatives)
      f1b2gradlist->write_pass1(&x,&y,&z,this);
    return z;
  }

/**
 * Description not yet available.
 * \param
 */
void df1b2_gradlist::reset(void)
{
  ncount=0;
  list.reset();
  nlist.reset();
  list2.reset();
  nlist2.reset();
  list3.reset();
  nlist3.reset();
}

/**
 * Description not yet available.
 * \param
 */
df1b2_gradlist::df1b2_gradlist
(
  unsigned int _bs, unsigned int _nbs,
  unsigned int _bs2, unsigned int _nbs2,
  unsigned int _bs3, unsigned int _nbs3,
  const adstring& _filename
)
{
  unsigned int bs=get_f1b2buffer_size("-l1");
  if (!bs) bs=_bs;
  list.allocate(bs,_filename);

  unsigned int nbs=get_f1b2buffer_size("-nl1");
  if (!nbs) nbs=_nbs;
  nlist.allocate(nbs,"n"+_filename);

  unsigned int bs2=get_f1b2buffer_size("-l2");
  if (!bs2) bs2=_bs2;
  list2.allocate(bs2,_filename+"2");

  unsigned int nbs2=get_f1b2buffer_size("-nl2");
  if (!nbs2) nbs2=_nbs2;
  nlist2.allocate(nbs2,"n"+_filename+"2");

  unsigned int bs3=get_f1b2buffer_size("-l3");
  if (!bs3) bs3=_bs3;
  list3.allocate(bs3,_filename+"3");

  unsigned int nbs3=get_f1b2buffer_size("-nl3");
  if (!nbs3) nbs3=_nbs3;
  nlist3.allocate(nbs3,"n"+_filename+"3");

  list3.set_noreadflag(1);
  nlist3.set_noreadflag(1);

  ncount=0;
}
/*
smartlist::smartlist(void)
{
  bufsize=0;
  filename=0;
  buffer=0;
  buffend=0;
  bptr=buffer;
  fp=-1;
}
*/

/**
Constructor
*/
smartlist::smartlist(unsigned int _bufsize,const adstring& _filename):
  sbptr(NULL)
{
#ifndef OPT_LIB
  //cerr << "need to modify smartlist class for multibyte char" << endl;
  assert(sizeof(char) == 1);
#endif

  bufsize=_bufsize;
  filename=_filename;
  AD_ALLOCATE(buffer,char,bufsize,df1b2_gradlist)
  buffend=buffer+bufsize-1;
  bptr=buffer;
  fp = open((char*)filename,
    O_RDWR | O_CREAT | O_TRUNC | O_BINARY, S_IREAD | S_IWRITE);
  if (fp == -1)
  {
    cerr << "Error trying to open file " << filename
         << " in class smartlist " << endl;
    exit(1);
  }
}

void ad_dstar::allocate(const unsigned int _n)
{
  n = _n;
}

/**
 * Description not yet available.
 * \param
 */
ad_dstar::ad_dstar(void)
{
  if (!n)
  {
    cerr << "need to initialize size in class ad_dstar" << endl;
    exit(1);
  }
  p = new double[n];
}

/**
 * Description not yet available.
 * \param
 */
void set_dependent_variable(const df1b2variable& _x)
{
  df1b2variable& x=(df1b2variable&) (_x);
  //cout << "dep " << int(x.u) << endl;
  for (unsigned int i=0;i<df1b2variable::nvar;i++)
  {
    x.u_dot_bar[i]=1.0;
  }
}

/**
 * Description not yet available.
 * \param
 */
dmatrix get_hessian(const init_df1b2vector& _x)
{
  ADUNCONST(init_df1b2vector,x)
#ifdef OPT_LIB
  int nvar = (int)df1b2variable::nvar;
#else
  unsigned int _nvar=df1b2variable::nvar;
  assert(_nvar <= INT_MAX);
  int nvar = (int)_nvar;
#endif
  dmatrix h(1,nvar,1,nvar);
  for (int i=1;i<=nvar;i++)
  {
    for (int j=1;j<=nvar;j++)
    {
      h(i,j)=x(i).u_bar[j-1];
    }
  }
  return h;
}

typedef df1b2variable (*P_USER_FUNCTION)(const init_df1b2vector& x);

/**
 * Description not yet available.
 * \param
 */
double d1F(P_USER_FUNCTION pu,const init_df1b2vector& _x,int i,double _delta)
{
  ADUNCONST(init_df1b2vector,x)
  double delta=.3*_delta;
  double xsave=value(x(i));
  x(i)=xsave+delta;
  double fp=value(pu(x));
  x(i)=xsave-delta;
  double fm=value(pu(x));
  x(i)=xsave;
  double d1fa=(fp-fm)/(2.0*delta);
  x(i)=xsave+2.0*delta;
  fp=value(pu(x));
  x(i)=xsave-2.0*delta;
  fm=value(pu(x));
  x(i)=xsave;
  double d1fb=(fp-fm)/(4.0*delta);
  double d1f=(8.0*d1fa-d1fb)/7.0;
  return d1f;
}

/**
 * Description not yet available.
 * \param
 */
double d2F(P_USER_FUNCTION pu,const init_df1b2vector& _x,int i,int j,
  double delta)
{
  ADUNCONST(init_df1b2vector,x)
  double xsave=value(x(i));
  x(i)=xsave+delta;
  double fp=d1F(pu,x,j,delta);
  x(i)=xsave-delta;
  double fm=d1F(pu,x,j,delta);
  double d1fa=(fp-fm)/(2.0*delta);
  x(i)=xsave+2.0*delta;
  fp=d1F(pu,x,j,delta);
  x(i)=xsave-2.0*delta;
  fm=d1F(pu,x,j,delta);
  x(i)=xsave;
  double d1fb=(fp-fm)/(4.0*delta);
  double d1f=(8.0*d1fa-d1fb)/7.0;
  return d1f;
}

/**
 * Description not yet available.
 * \param
 */
double d3F(P_USER_FUNCTION pu,const init_df1b2vector& _x,int i,int j,int k,
  double delta)
{
  ADUNCONST(init_df1b2vector,x)
  double xsave=value(x(i));
  x(i)=xsave+delta;
  double fp=d2F(pu,x,j,k,delta);
  x(i)=xsave-delta;
  double fm=d2F(pu,x,j,k,delta);
  x(i)=xsave;
  double d1f=(fp-fm)/(2.0*delta);
  return d1f;
}

/**
 * Description not yet available.
 * \param
 */
dmatrix check_second_derivatives(const init_df1b2vector& x)
{
  f1b2gradlist->set_no_derivatives();
#ifdef OPT_LIB
  int nvar = (int)df1b2variable::nvar;
#else
  unsigned int _nvar=df1b2variable::nvar;
  assert(_nvar <= INT_MAX);
  int nvar = (int)_nvar;
#endif
  dmatrix h(1, nvar, 1, nvar);
  //const double delta=1.e-3;
  h.initialize();
  for (int i=1;i<=init_df1b2variable::num_variables;i++)
  {
    for (int j=1;j<=init_df1b2variable::num_variables;j++)
    {
      //h(i,j)=d2F(user_function,x,i,j,delta);
    }
  }
  return h;
}

/**
 * Description not yet available.
 * \param
 */
d3_array check_third_derivatives(const init_df1b2vector& x)
{
  f1b2gradlist->set_no_derivatives();
#ifdef OPT_LIB
  int nvar = (int)df1b2variable::nvar;
#else
  unsigned int _nvar=df1b2variable::nvar;
  assert(_nvar <= INT_MAX);
  int nvar = (int)_nvar;
#endif
  d3_array h(1, nvar, 1, nvar, 1, nvar);
  //const double delta=2.e-4;
  h.initialize();
  for (int i=1;i<=init_df1b2variable::num_variables;i++)
  {
    for (int j=1;j<=init_df1b2variable::num_variables;j++)
    {
      for (int k=1;k<=init_df1b2variable::num_variables;k++)
      {
        //h(i,j,k)=d3F(user_function,x,i,j,k,delta);
      }
    }
  }
  return h;
}

#if defined(__DERCHECK__)

/**
 * Description not yet available.
 * \param
 */
dercheck_info::dercheck_info(int _node_number,double _delta,int _index) :
  node_number(_node_number), delta(_delta), index(_index)
{
  der_value=0.0;
  pass_number=0;
  counter=0;
  f1=0.0;
  f2=0.0;
}
dercheck_info * derchecker;

#endif


re_objective_function_value * re_objective_function_value::pobjfun=0;

/**
 * Description not yet available.
 * \param
 */
re_objective_function_value::re_objective_function_value(void)
{
  pobjfun=this;
}

/**
 * Description not yet available.
 * \param
 */
re_objective_function_value::~re_objective_function_value()
{
  pobjfun=0;
}

/**
 * Description not yet available.
 * \param
 */
re_objective_function_value& re_objective_function_value::operator =
  (const df1b2variable& v)
{
  df1b2variable::operator = (v);
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
re_objective_function_value& re_objective_function_value::operator =
  (double v)
{
  df1b2variable::operator = (v);
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
void re_objective_function_value::allocate(void)
{
  df1b2variable::allocate();
}

/**
 * Description not yet available.
 * \param
 */
void re_objective_function_value::allocate(const char * s)
{
  pobjfun=this;
  df1b2variable::allocate();
}

#if !defined(OPT_LIB)
/**
 * Description not yet available.
 * \param
 */
init_df1b2variable& init_df1b2vector::operator () (int i)
{
  if (i < indexmin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too low",
    "init_df1b2variable& init_df1b2vector::operator () (int i)",
    indexmin(), indexmax(), i);
  }
  if (i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too high",
    "init_df1b2variable& init_df1b2vector::operator () (int i)",
    indexmin(), indexmax(), i);
  }
  return ptr[i];
}

/**
 * Description not yet available.
 * \param
 */
init_df1b2variable& init_df1b2vector::operator [] (int i)
{
  if (i < indexmin())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too low",
    "init_df1b2variable& init_df1b2vector::operator [] (int i)",
    indexmin(), indexmax(), i);
  }
  if (i > indexmax())
  {
    ADMB_ARRAY_BOUNDS_ERROR("Index too high",
    "init_df1b2variable& init_df1b2vector::operator [] (int i)",
    indexmin(), indexmax(), i);
  }
  return ptr[i];
}
#endif
/**
Get f1b2buffer size from commandline options.
*/
unsigned int get_f1b2buffer_size(const char* s)
{
  unsigned int n = 0;
  int on1=-1;
  int nopt=0;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,s,nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage " << s << " option needs integer  -- ignored" << endl;
    }
    else
    {
      int i = atoi(ad_comm::argv[on1+1]);
      if (i > 0)
      {
        n = (unsigned int)i;
      }
    }
  }
  return n;
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable::df1b2variable(const random_effects_bounded_vector_info& rebv)
{
  df1b2variable& v= *(rebv.pv->v+rebv.i);
  if (v.ptr)
  {
    ptr=v.ptr;
    ncopies=v.ncopies;
    (*ncopies)++;
    u=v.u;
    u_dot=v.u_dot;
    u_bar=v.u_bar;
    u_dot_bar=v.u_dot_bar;
    u_tilde=v.u_tilde;
    u_dot_tilde=v.u_dot_tilde;
    u_bar_tilde=v.u_bar_tilde;
    u_dot_bar_tilde=v.u_dot_bar_tilde;
  }
  else
  {
    ptr=NULL;
    ncopies=NULL;
    u=NULL;
    u_dot=NULL;
    u_bar=NULL;
    u_dot_bar=NULL;
    u_tilde=NULL;
    u_dot_tilde=NULL;
    u_bar_tilde=NULL;
    u_dot_bar_tilde=NULL;
  }
}
