/*
 * $Id$
 *
 * Author: David Fournier and Mollie Brooks
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <df1b2fun.h>

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const df1b2vector& _v,double x)
{
  ADUNCONST(df1b2vector,v);
  //check_shape(x,M,"operator *");
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++) tmp(i)=pow(v(i),x);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const  df1b2vector& _x,const df1b2vector& _v)
{
  ADUNCONST(df1b2vector,x);
  ADUNCONST(df1b2vector,v);
  //check_shape(x,M,"operator *");
  //check_shape(x,M,"operator *");
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++) tmp(i)=pow(x(i),v(i));
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const df1b2vector& _v,const df1b2variable & _x)
{
  ADUNCONST(df1b2vector,v);
  ADUNCONST(df1b2variable,x);
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=pow(v(i),x);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const df1b2variable & _v,const df1b2vector& _x)
{
  ADUNCONST(df1b2variable,v);
  ADUNCONST(df1b2vector,x);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=pow(v,x(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const double v,const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=pow(v,x(i));
  }
  return tmp;
}
/**
 \brief raise x to the power a.
 \param x vector of bases
 \param a the exponent
 */
df1b2vector pow(const dvector& x,  const df1b2variable& a)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();
  df1b2vector y(x.indexmin(), x.indexmax());
  for(int i=x.indexmin(); i<=x.indexmax(); i++)
  {
    y(i)=pow(x(i),a);
  }

  gs->RETURN_ARRAYS_DECREMENT();
  return(y);
}
/**
 \brief raise x to the power a.
 \param x vector of bases
 \param a vector of exponents
 */
df1b2vector pow(const dvector& x,  const df1b2vector& a)
{
  gradient_structure* gs = gradient_structure::_instance;
  gs->RETURN_ARRAYS_INCREMENT();
  df1b2vector y(x.indexmin(), x.indexmax());

  for(int i=x.indexmin(); i<=x.indexmax(); i++)
  {
    y(i)=pow(x(i),a(i));
  }

  gs->RETURN_ARRAYS_DECREMENT();
  return(y);
}
/**
 \brief raise v1 to the power v2.
 \param v1 vector of bases
 \param v2 vector of exponents
 */
  dvar_vector pow(const dvar_vector& v1, const dvector& v2)
  {
    gradient_structure* gs = gradient_structure::_instance;
    gs->RETURN_ARRAYS_INCREMENT();

    dvar_vector tmp(v1.indexmin(),v1.indexmax());
    for (int i=v1.indexmin();i<=v1.indexmax();i++)
    {
      tmp.elem(i)=pow(v1.elem(i),v2.elem(i));
    }
    gs->RETURN_ARRAYS_DECREMENT();
    return(tmp);
  }
/**
 \brief raise x to the power v.
 \param x vector of bases
 \param v vector of exponents
 */
  df1b2vector pow(df1b2vector const& _x,dvector const& v)
  {
   ADUNCONST(df1b2vector,x);
   int mmin=v.indexmin();
   int mmax=v.indexmax();
   df1b2vector tmp;
   tmp.noallocate(mmin,mmax);
   for (int i=mmin;i<=mmax;i++) tmp(i)=pow(x(i),v(i));
   return tmp;
  }

/**
 * Description not yet available.
 * \param
 */
df1b2variable operator*(const df1b2vector& _x, const df1b2vector& _y)
{
  ADUNCONST(df1b2vector,x)
  ADUNCONST(df1b2vector,y)
  df1b2variable tmp=0.0;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    *tmp.get_u() += *x(i).get_u() *  *y(i).get_u();
  }
  {
    double* zd=tmp.get_u_dot();
    for (unsigned int j=0;j<df1b2variable::nvar;j++)
    {
      *zd++ = 0;
    }
  }
  for (int i=mmin;i<=mmax;i++)
  {
    double * zd=tmp.get_u_dot();
    double * xd=x(i).get_u_dot();
    double * yd=y(i).get_u_dot();
    double xu= *x(i).get_u();
    double yu= *y(i).get_u();

    for (unsigned int j=0;j<df1b2variable::nvar;j++)
    {
      *zd++ += yu * *xd++ + xu * *yd++;
    }
  }
  // WRITE WHATEVER ON TAPE
  if (!df1b2_gradlist::no_derivatives)
    f1b2gradlist->write_pass1_prod(&x,&y,&tmp);

  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void ad_read_pass2_prod_vector(void);

 int df1b2_gradlist::write_pass1_prod(const df1b2vector * _px,
   const df1b2vector * _py,df1b2variable * pz)
 {
   ADUNCONST(df1b2vector*,px)
   ADUNCONST(df1b2vector*,py)
   ncount++;
#if defined(CHECK_COUNT)
  if (ncount >= ncount_check)
    cout << ncount << endl;
#endif
  unsigned int nvar=df1b2variable::nvar;

  int mmin=px->indexmin();
  int mmax=px->indexmax();
#ifndef OPT_LIB
  assert(mmax >= mmin);
#endif
  size_t size = (size_t)(mmax - mmin + 1);
  constexpr size_t sizeofdouble = sizeof(double);

  //int total_bytes=3*sizeof(df1b2_header)+2*(nvar+1)*sizeof(double);
  size_t total_bytes= 2*sizeof(int) + 2 * size * sizeof(df1b2_header)
    + sizeof(df1b2_header) + 2 * size * sizeofdouble
    + 2 * size * nvar * sizeofdouble;
// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="DL";
  size_t slen=strlen(ids);
  total_bytes+=slen;
#endif

  list.check_buffer_size(total_bytes);

  void * tmpptr=list.bptr;
#if defined(SAFE_ALL)
  memcpy(list,ids,slen);
#endif
// end of string identifier debug stuff

   memcpy(list,&mmin,sizeof(int));
   memcpy(list,&mmax,sizeof(int));
   for (int i=mmin;i<=mmax;i++)
   {
     memcpy(list,(df1b2_header*)( &(*px)(i)  ),sizeof(df1b2_header));
     memcpy(list,(df1b2_header*)( &(*py)(i)  ),sizeof(df1b2_header));
   }
   memcpy(list,(df1b2_header*)(pz),sizeof(df1b2_header));

   for (int i=mmin;i<=mmax;i++)
   {
     memcpy(list,(*px)(i).get_u(),sizeofdouble);
     memcpy(list,(*py)(i).get_u(),sizeofdouble);
   }
   for (int i=mmin;i<=mmax;i++)
   {
     memcpy(list,(*px)(i).get_u_dot(),nvar*sizeofdouble);
     memcpy(list,(*py)(i).get_u_dot(),nvar*sizeofdouble);
   }
   // ***** write  record size
   nlist.bptr->numbytes=adptr_diff(list.bptr,tmpptr);
   //cout << "XX " << nlist.bptr->numbytes << " " << total_bytes << endl;
   nlist.bptr->pf=(ADrfptr)(&ad_read_pass2_prod_vector);
      ++nlist;
   return 0;
 }

void read_pass2_1_prod_vector(void);
void read_pass2_2_prod_vector(void);
void read_pass2_3_prod_vector(void);

/**
 * Description not yet available.
 * \param
 */
void ad_read_pass2_prod_vector(void)
{
  switch(df1b2variable::passnumber)
  {
  case 1:
    read_pass2_1_prod_vector();
    break;
  case 2:
    read_pass2_2_prod_vector();
    break;
  case 3:
    read_pass2_3_prod_vector();
    break;
  default:
    cerr << "illegal value for df1b2variable::pass = "
         << df1b2variable::passnumber << endl;
    ad_exit(1);
  }
}

/**
 * Description not yet available.
 * \param
 */
void read_pass2_1_prod_vector(void)
{
  size_t nvar = df1b2variable::nvar;

  constexpr size_t sizeofdouble = sizeof(double);
  size_t size = nvar * sizeofdouble;

  test_smartlist& list=f1b2gradlist->list;
  int num_bytes=f1b2gradlist->nlist.bptr->numbytes;
  list-=num_bytes;
  list.saveposition(); // save pointer to beginning of record;

#if defined(SAFE_ALL)
  checkidentiferstring("DL",f1b2gradlist->list);
#endif
  char * bptr=f1b2gradlist->list.bptr;
  int& mmin = *(int *) bptr;
  bptr+=sizeof(int);
  int& mmax = *(int *) bptr;
  bptr+=sizeof(int);
  df1b2_header_ptr_vector px(mmin,mmax);
  df1b2_header_ptr_vector py(mmin,mmax);
  double_ptr_vector xdot(mmin,mmax);
  double_ptr_vector ydot(mmin,mmax);
  dvector xu(mmin,mmax);
  dvector yu(mmin,mmax);

  df1b2_header** ppxi = &px(mmin);
  df1b2_header** ppyi = &py(mmin);
  for (int i=mmin;i<=mmax;i++)
  {
    // df1b2_header *
    *ppxi = (df1b2_header*)bptr;
    bptr+=sizeof(df1b2_header);
    // df1b2_header *
    *ppyi = (df1b2_header*)bptr;
    bptr+=sizeof(df1b2_header);

    ++ppxi;
    ++ppyi;
  }
  df1b2_header * pz=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);

  double* pxui = xu.get_v() + mmin;
  double* pyui = yu.get_v() + mmin;
  for (int i=mmin;i<=mmax;i++)
  {
    memcpy(pxui, bptr, sizeofdouble);
    bptr+=sizeofdouble;
    memcpy(pyui, bptr, sizeofdouble);
    bptr+=sizeofdouble;

    ++pxui;
    ++pyui;
  }
  size_t nvarsizeofdouble = nvar * sizeofdouble;
  for (int i=mmin;i<=mmax;i++)
  {
    // double *
    xdot(i)=(double*)bptr;
    bptr += nvarsizeofdouble;
    // double *
    ydot(i)=(double*)bptr;
    bptr += nvarsizeofdouble;
  }

  list.restoreposition(); // save pointer to beginning of record;

  // ****************************************************************
  // turn this off if no third derivatives are calculated
  // if (!no_third_derivatives)
  // {
  // save for second reverse pass
  // save identifier 1
     test_smartlist & list2 = f1b2gradlist->list2;

  size_t total_bytes=2*nvar*sizeof(double);
// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="QK";
  size_t slen=strlen(ids);
  total_bytes+=slen;
#endif

  list2.check_buffer_size(total_bytes);

  void * tmpptr=list2.bptr;
#if defined(SAFE_ALL)
  memcpy(list2,ids,slen);
#endif

  fixed_smartlist2 & nlist2 = f1b2gradlist->nlist2;

  memcpy(list2,pz->get_u_bar(), size);
  memcpy(list2,pz->get_u_dot_bar(), size);
  *nlist2.bptr=adptr_diff(list2.bptr,tmpptr);
  ++nlist2;

  // Do first reverse pass calculations
  ppxi = &px(mmin);
  ppyi = &py(mmin);
  double* pyu = yu.get_v() + mmin;
  double* pxu = xu.get_v() + mmin;
  for (int i=mmin;i<=mmax;i++)
  {
    double yui = *pyu;
    double* pz_u_bar = pz->u_bar;
    double* pxi_u_bar = (*ppxi)->u_bar;
    for (size_t j = 0; j < nvar; ++j)
    {
      *pxi_u_bar += yui * *pz_u_bar;

      ++pz_u_bar;
      ++pxi_u_bar;
    }
    ++pyu;

    double xui = *pxu;
    pz_u_bar = pz->u_bar;
    double* pyi_u_bar = (*ppyi)->u_bar;
    for (size_t j = 0; j < nvar; ++j)
    {
      *pyi_u_bar += xui * *pz_u_bar;

      ++pz_u_bar;
      ++pyi_u_bar;
    }
    ++pxu;
    ++ppxi;
    ++ppyi;
  }

  ppxi = &px(mmin);
  ppyi = &py(mmin);
  pyu = yu.get_v() + mmin;
  pxu = xu.get_v() + mmin;
  for (int i=mmin;i<=mmax;i++)
  {
    double* pydoti = ydot(i);
    double* pz_u_dot_bar = pz->u_dot_bar;
    double* pxi_u_bar = (*ppxi)->u_bar;
    for (size_t j=0;j<nvar;j++)
    {
      *pxi_u_bar += *pydoti * *pz_u_dot_bar;

      ++pydoti;
      ++pz_u_dot_bar;
      ++pxi_u_bar;
    }

    pz_u_dot_bar = pz->u_dot_bar;
    double* pxdoti = xdot(i);
    double* pyi_u_bar = (*ppyi)->u_bar;
    for (size_t j=0;j<nvar;j++)
    {
      *pyi_u_bar += *pxdoti * *pz_u_dot_bar;

      ++pxdoti;
      ++pz_u_dot_bar;
      ++pyi_u_bar;
    }

    double yui = *pyu;
    pz_u_dot_bar = pz->u_dot_bar;
    double* pxi_u_dot_bar = (*ppxi)->u_dot_bar;
    for (size_t j=0;j<nvar;j++)
    {
      *pxi_u_dot_bar += yui * *pz_u_dot_bar;

      ++pz_u_dot_bar;
      ++pxi_u_dot_bar;
    }
    ++pyu;

    double xui = *pxu;
    pz_u_dot_bar = pz->u_dot_bar;
    double* pyi_u_dot_bar = (*ppyi)->u_dot_bar;
    for (size_t j=0;j<nvar;j++)
    {
      *pyi_u_dot_bar += xui * *pz_u_dot_bar;

      ++pz_u_dot_bar;
      ++pyi_u_dot_bar;
    }
    ++pxu;
    ++ppyi;
    ++ppxi;
  }

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  memset(pz->u_bar, 0, size);
  memset(pz->u_dot_bar, 0, size);
}

/**
 * Description not yet available.
 * \param
 */
void read_pass2_2_prod_vector(void)
{
  //const int nlist_record_size=sizeof(int)+sizeof(char*);
  // We are going forward for bptr and backword for bptr2
  //
  // list 1
  //
  unsigned int nvar=df1b2variable::nvar;
  test_smartlist & list=f1b2gradlist->list;

  //int total_bytes=3*sizeof(df1b2_header)+sizeof(char*)
  //  +2*(nvar+1)*sizeof(double);
  //int total_bytes=3*sizeof(df1b2_header)
  //  +2*(nvar+1)*sizeof(double);
// string identifier debug stuff
#if defined(SAFE_ALL)
  //char ids[]="DL";
  //int slen=strlen(ids);
  //total_bytes+=slen;
#endif
// end of string identifier debug stuff

  fixed_smartlist & nlist=f1b2gradlist->nlist;
  int total_bytes = nlist.bptr->numbytes;
  if (total_bytes > 0)
  {
    list.check_buffer_size((size_t)total_bytes);
  }
  list.saveposition(); // save pointer to beginning of record;
  //cout << "YY " << total_bytes <<  endl;
  //
  // list 2
  //
  test_smartlist & list2=f1b2gradlist->list2;
  fixed_smartlist2 & nlist2=f1b2gradlist->nlist2;
  // get record size
  int num_bytes2=*nlist2.bptr;
  --nlist2;
  // backup the size of the record
  list2-=num_bytes2;
  list2.saveposition(); // save pointer to beginning of record;
  // save the pointer to the beginning of the record
  // bptr and bptr2 now both point to the beginning of their records

  //df1b2_header x,z;
  //df1b2function2 * pf;

  // get info from tape1
  // get info from tape1
#if defined(SAFE_ALL)
  checkidentiferstring("DL",list);
  checkidentiferstring("QK",list2);
#endif
  int mmin = *(int *) list.bptr;
  list.bptr+=sizeof(int);
  int mmax = *(int *) list.bptr;
  list.bptr+=sizeof(int);

  df1b2_header_ptr_vector px(mmin,mmax);
  df1b2_header_ptr_vector py(mmin,mmax);
  double_ptr_vector xdot(mmin,mmax);
  double_ptr_vector ydot(mmin,mmax);
  dvector xu(mmin,mmax);
  dvector yu(mmin,mmax);

  df1b2_header** ppxi = &px(mmin);
  df1b2_header** ppyi = &py(mmin);
  for (int i=mmin;i<=mmax;i++)
  {
    // df1b2_header * //
    *ppxi = (df1b2_header*)list.bptr;
    list.bptr+=sizeof(df1b2_header);
    // df1b2_header *
    *ppyi = (df1b2_header*)list.bptr;
    list.bptr+=sizeof(df1b2_header);

    ++ppxi;
    ++ppyi;
  }

  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);

  constexpr size_t sizeofdouble = sizeof(double);
  double* pxui = xu.get_v() + mmin;
  double* pyui = yu.get_v() + mmin;
  for (int i=mmin;i<=mmax;i++)
  {
    memcpy(pxui,list.bptr, sizeofdouble);
    list.bptr += sizeofdouble;
    memcpy(pyui,list.bptr, sizeofdouble);
    list.bptr += sizeofdouble;

    ++pxui;
    ++pyui;
  }

  size_t nvarsizeofdouble = nvar * sizeofdouble;
  for (int i=mmin;i<=mmax;i++)
  {
    xdot(i)=(double*)list.bptr;
    list.bptr += nvarsizeofdouble;
    ydot(i)=(double*)list.bptr;
    list.bptr += nvarsizeofdouble;
  }
  list.restoreposition(total_bytes); // save pointer to beginning of record;

  double* zbar=(double*)list2.bptr;
  double* zdotbar=(double*)(list2.bptr + nvarsizeofdouble);
  list2.restoreposition(); // save pointer to beginning of record;

  double* z_bar_tilde=pz->get_u_bar_tilde();
  double* z_dot_bar_tilde=pz->get_u_dot_bar_tilde();

  memset(z_bar_tilde, 0, nvarsizeofdouble);
  memset(z_dot_bar_tilde, 0, nvarsizeofdouble);

  ppxi = &px(mmin);
  ppyi = &py(mmin);
  double* pyu = yu.get_v() + mmin;
  double* pxu = xu.get_v() + mmin;
  for (int i=mmin;i<=mmax;i++)
  {
    double* x_tilde= (*ppxi)->get_u_tilde();
    double* x_dot_tilde= (*ppxi)->get_u_dot_tilde();
    double* x_bar_tilde= (*ppxi)->get_u_bar_tilde();
    double* x_dot_bar_tilde= (*ppxi)->get_u_dot_bar_tilde();
    double* y_tilde= (*ppyi)->get_u_tilde();
    double* y_dot_tilde= (*ppyi)->get_u_dot_tilde();
    double* y_bar_tilde= (*ppyi)->get_u_bar_tilde();
    double* y_dot_bar_tilde= (*ppyi)->get_u_dot_bar_tilde();

    double yui = *pyu;
    // start wjth x and add y
    double* px_bar_tilde = x_bar_tilde;
    for (size_t j=0;j<nvar;j++)
    {
      z_bar_tilde[j]+= yui * *px_bar_tilde;
      *y_tilde+=zbar[j]* *px_bar_tilde;
      ++px_bar_tilde;
    }

    double* px_dot_bar_tilde = x_dot_bar_tilde;
    for (size_t j=0;j<nvar;j++)
    {
      *y_tilde+=zdotbar[j]* *px_dot_bar_tilde;
      z_dot_bar_tilde[j]+= yui * *px_dot_bar_tilde;
      ++px_dot_bar_tilde;
    }
    ++pyu;

    double xui = *pxu;
    // start wjth y and add x
    double* py_bar_tilde = y_bar_tilde;
    for (size_t j=0;j<nvar;j++)
    {
      *x_tilde+=zbar[j]* *py_bar_tilde;
      z_bar_tilde[j]+= xui * *py_bar_tilde;
      ++py_bar_tilde;
    }

    double* py_dot_bar_tilde = y_dot_bar_tilde;
    for (size_t j=0;j<nvar;j++)
    {
      *x_tilde+=zdotbar[j]* *py_dot_bar_tilde;
      z_dot_bar_tilde[j]+= xui * *py_dot_bar_tilde;
      ++py_dot_bar_tilde;
    }
    ++pxu;

    px_bar_tilde = x_bar_tilde;
    for (size_t j=0;j<nvar;j++)
    {
      y_dot_tilde[j]+=zdotbar[j]* *px_bar_tilde;
      z_dot_bar_tilde[j]+=ydot(i)[j]* *px_bar_tilde;
      ++px_bar_tilde;
    }
    py_bar_tilde = y_bar_tilde;
    for (size_t j=0;j<nvar;j++)
    {
      x_dot_tilde[j]+=zdotbar[j]* *py_bar_tilde;
      z_dot_bar_tilde[j]+=xdot(i)[j]* *py_bar_tilde;
      ++py_bar_tilde;
    }
    ++ppxi;
    ++ppyi;
  }
}

/**
 * Description not yet available.
 * \param
 */
void read_pass2_3_prod_vector(void)
{
  // We are going backword for bptr and forward for bptr2
  // the current entry+2 in bptr is the size of the record i.e
  // points to the next record
  unsigned int nvar=df1b2variable::nvar;
  fixed_smartlist & nlist=f1b2gradlist->nlist;
  test_smartlist& list=f1b2gradlist->list;
   // nlist-=sizeof(int);
  // get record size
  int num_bytes=nlist.bptr->numbytes;
  // backup the size of the record
  list-=num_bytes;
  list.saveposition(); // save pointer to beginning of record;
  // save the pointer to the beginning of the record

  //df1b2_header x,z;
  //df1b2function2 * pf;

  // get info from tape1
  // get info from tape1
#if defined(SAFE_ALL)
  checkidentiferstring("DL",list);
#endif
  int& mmin = *(int *) list.bptr;
  list.bptr+=sizeof(int);
  int& mmax = *(int *) list.bptr;
  list.bptr+=sizeof(int);
  df1b2_header_ptr_vector px(mmin,mmax);
  df1b2_header_ptr_vector py(mmin,mmax);
  double_ptr_vector xdot(mmin,mmax);
  double_ptr_vector ydot(mmin,mmax);
  dvector xu(mmin,mmax);
  dvector yu(mmin,mmax);
  int i;
  df1b2_header** ppxi = &px(mmin);
  df1b2_header** ppyi = &py(mmin);
  for (i=mmin;i<=mmax;i++)
  {
    // df1b2_header *
    *ppxi = (df1b2_header*)list.bptr;
    list.bptr+=sizeof(df1b2_header);
    // df1b2_header *
    *ppyi = (df1b2_header*)list.bptr;
    list.bptr+=sizeof(df1b2_header);

    ++ppxi;
    ++ppyi;
  }
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);

  constexpr size_t sizeofdouble = sizeof(double);

  double* pxui = xu.get_v() + mmin;
  double* pyui = yu.get_v() + mmin;
  for (i=mmin;i<=mmax;i++)
  {
    memcpy(pxui, list.bptr, sizeofdouble);
    list.bptr+=sizeofdouble;
    memcpy(pyui, list.bptr, sizeofdouble);
    list.bptr+=sizeofdouble;

    ++pxui;
    ++pyui;
  }

  size_t nvarsizeofdouble = nvar * sizeofdouble;
  for (i=mmin;i<=mmax;i++)
  {
    // double *
    xdot(i)=(double*)list.bptr;
    list.bptr += nvarsizeofdouble;
    // double *
    ydot(i)=(double*)list.bptr;
    list.bptr += nvarsizeofdouble;
  }

  list.restoreposition(); // save pointer to beginning of record;

  pxui = xu.get_v() + mmin;
  pyui = yu.get_v() + mmin;
  ppxi = &px(mmin);
  ppyi = &py(mmin);
  for (i=mmin;i<=mmax;i++)
  {
    *((*ppxi)->u_tilde) += *pyui * *(pz->u_tilde);
    *((*ppyi)->u_tilde) += *pxui * *(pz->u_tilde);

    double* pz_u_dot_tildej = pz->u_dot_tilde;
    for (size_t j=0;j<nvar;j++)
    {
      *((*ppyi)->u_tilde) += xdot(i)[j]* *pz_u_dot_tildej;
      *((*ppxi)->u_tilde) += ydot(i)[j]* *pz_u_dot_tildej;

      ++pz_u_dot_tildej;
    }

    double* ppxi_u_dot_tildej = (*ppxi)->u_dot_tilde;
    double* ppyi_u_dot_tildej = (*ppyi)->u_dot_tilde;
    pz_u_dot_tildej = pz->u_dot_tilde;
    for (size_t j=0;j<nvar;j++)
    {
      *ppxi_u_dot_tildej += *pyui * *pz_u_dot_tildej;
      *ppyi_u_dot_tildej += *pxui * *pz_u_dot_tildej;

      ++ppxi_u_dot_tildej;
      ++ppyi_u_dot_tildej;
      ++pz_u_dot_tildej;
    }

    ++pxui;
    ++pyui;
    ++ppxi;
    ++ppyi;
  }
  *(pz->u_tilde)=0;

  memset(pz->u_dot_tilde, 0, nvarsizeofdouble);
}
