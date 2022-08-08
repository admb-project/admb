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
#include <df1b2fun.h>

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

void ad_read_pass2_dvdv(void);

/**
 * Description not yet available.
 * \param
 */
 int df1b2_gradlist::write_pass1(const df1b2variable * _px,
   const df1b2variable * _py,df1b2variable * pz,double df_x,
   double df_y,
   double df_xx,
   double df_xy,
   double df_yy,
   double df_xxx,
   double df_xxy,
   double df_xyy,
   double df_yyy)
 {
   ADUNCONST(df1b2variable*,px)
   ADUNCONST(df1b2variable*,py)
   ncount++;
#if defined(CHECK_COUNT)
  if (ncount >= ncount_check)
    ncount_checker(ncount,ncount_check);
#endif
  size_t nvar=df1b2variable::nvar;

  size_t total_bytes=3*sizeof(df1b2_header)+sizeof(char*)
     +(2*nvar+11)*sizeof(double);

// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="UZ";
  size_t slen=strlen(ids);
  total_bytes+=slen;
#endif

  list.check_buffer_size(total_bytes);

  void * tmpptr=list.bptr;
#if defined(SAFE_ALL)
  memcpy(list,ids,slen);
#endif
// end of string identifier debug stuff

   memcpy(list,(df1b2_header*)(px),sizeof(df1b2_header));
   memcpy(list,(df1b2_header*)(py),sizeof(df1b2_header));
   memcpy(list,(df1b2_header*)(pz),sizeof(df1b2_header));
   //memcpy(list,&pf,sizeof(char *));
   //*(char**)(list.bptr)=(char*)pf;

   size_t sizeofdouble = sizeof(double);

   memcpy(list,&df_x,sizeofdouble);
   memcpy(list,&df_y,sizeofdouble);
   memcpy(list,&df_xx,sizeofdouble);
   memcpy(list,&df_xy,sizeofdouble);
   memcpy(list,&df_yy,sizeofdouble);
   memcpy(list,&df_xxx,sizeofdouble);
   memcpy(list,&df_xxy,sizeofdouble);
   memcpy(list,&df_xyy,sizeofdouble);
   memcpy(list,&df_yyy,sizeofdouble);

   memcpy(list,px->get_u(),sizeofdouble);
   memcpy(list,py->get_u(),sizeofdouble);
   memcpy(list,px->get_u_dot(),nvar*sizeofdouble);
   memcpy(list,py->get_u_dot(),nvar*sizeofdouble);
   // ***** write  record size
   nlist.bptr->numbytes=adptr_diff(list.bptr,tmpptr);
   nlist.bptr->pf=(ADrfptr)(&ad_read_pass2_dvdv);
   ++nlist;
   return 0;
 }


void read_pass2_1_dvdv(void);
void read_pass2_2_dvdv(void);
void read_pass2_3_dvdv(void);

/**
 * Description not yet available.
 * \param
 */
void ad_read_pass2_dvdv(void)
{
  switch(df1b2variable::passnumber)
  {
  case 1:
    read_pass2_1_dvdv();
    break;
  case 2:
    read_pass2_2_dvdv();
    break;
  case 3:
    read_pass2_3_dvdv();
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
void read_pass2_1_dvdv(void)
{
  // We are going backword for bptr and nbptr
  // and  forward for bptr2 and nbptr2
  // the current entry+2 in bptr is the size of the record i.e
  // points to the next record
  //char * bptr=f1b2gradlist->bptr;
  //char * bptr2=f1b2gradlist2->bptr;
  size_t nvar = df1b2variable::nvar;
  test_smartlist& list=f1b2gradlist->list;
  //f1b2gradlist->nlist-=sizeof(int);
  int num_bytes=f1b2gradlist->nlist.bptr->numbytes;
  list-=num_bytes;
  list.saveposition(); // save pointer to beginning of record;
  double xu,yu;
  //ad_dstar xdot,ydot;
  //df1b2function2 * pf;

  // get info from tape1
#if defined(SAFE_ALL)
  checkidentiferstring("UZ",f1b2gradlist->list);
#endif
  char * bptr=f1b2gradlist->list.bptr;
  df1b2_header * px=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);
  df1b2_header * py=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);
  //pf=*(df1b2function2 **) bptr;
  //bptr+=sizeof(char*);

  double df1=*(double*) bptr;
  bptr+=sizeof(double);

  double df2=*(double*) bptr;
  bptr+=sizeof(double);

  double d2f11=*(double*) bptr;
  bptr+=sizeof(double);

  double d2f12=*(double*) bptr;
  bptr+=sizeof(double);

  double d2f22=*(double*) bptr;
  bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f111=*(double*) bptr;
#endif
  bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f112=*(double*) bptr;
#endif
  bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f122=*(double*) bptr;
#endif
  bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f222=*(double*) bptr;
#endif
  bptr+=sizeof(double);

  memcpy(&xu,bptr,sizeof(double));
  bptr+=sizeof(double);
  memcpy(&yu,bptr,sizeof(double));
  bptr+=sizeof(double);
  double * xdot=(double*)bptr;
  bptr+=nvar*sizeof(double);
  double * ydot=(double*)bptr;

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
  char ids[]="FW";
  size_t slen=strlen(ids);
  total_bytes+=slen;
#endif

  list2.check_buffer_size(total_bytes);
  void * tmpptr=list2.bptr;
#if defined(SAFE_ALL)
  memcpy(list2,ids,slen);
#endif

     fixed_smartlist2 & nlist2 = f1b2gradlist->nlist2;
  size_t sizeofdouble = sizeof(double);
  memcpy(list2,pz->get_u_bar(),nvar*sizeofdouble);
  memcpy(list2,pz->get_u_dot_bar(),nvar*sizeofdouble);
  *nlist2.bptr=adptr_diff(list2.bptr,tmpptr);
  ++nlist2;
  // }
  //
  // ****************************************************************
#if defined(PRINT_DERS)
 print_derivatives(funname,(f),(df1),
  (df2),(d2f11),(d2f12),(d2f22),
  (d3f111),(d3f112),(d3f122),
  (d3f222),1);
 print_derivatives(pz,"z");
 print_derivatives(px,"x");
 print_derivatives(py,"y");
#endif
#if defined(__DERCHECK__)
  if (derchecker)
  if (derchecker->node_number)
  {
    if (derchecker->counter == derchecker->node_number)
    {
      switch (derchecker->pass_number) // increment the variable of interest
      {
      case 2:
        switch(derchecker->vartype)
        {
        case 1:
          if (!derchecker->dotflag)
            px->u_bar[derchecker->index-1]+=derchecker->delta;
          else
            px->u_dot_bar[derchecker->index-1]+=derchecker->delta;
          break;
        case 2:
          if (!derchecker->dotflag)
            py->u_bar[derchecker->index-1]+=derchecker->delta;
          else
            py->u_dot_bar[derchecker->index-1]+=derchecker->delta;
          break;
        case 3:
          if (!derchecker->dotflag)
            pz->u_bar[derchecker->index-1]+=derchecker->delta;
          else
            pz->u_dot_bar[derchecker->index-1]+=derchecker->delta;
          break;
        default:
          cerr << "Invalid index value for dercheck_index was "
               << derchecker->index << endl;
          break;
        }
        break;
      case 3:
        switch(derchecker->vartype)
        {
        case 1:
          if (!derchecker->dotflag)
            px->u_bar[derchecker->index-1]-=derchecker->delta;
          else
            px->u_dot_bar[derchecker->index-1]-=derchecker->delta;
          break;
        case 2:
          if (!derchecker->dotflag)
            py->u_bar[derchecker->index-1]-=derchecker->delta;
          else
            py->u_dot_bar[derchecker->index-1]-=derchecker->delta;
          break;
        case 3:
          if (!derchecker->dotflag)
            pz->u_bar[derchecker->index-1]-=derchecker->delta;
          else
            pz->u_dot_bar[derchecker->index-1]-=derchecker->delta;
          break;
        default:
          cerr << "Invalid index value for dercheck_index was "
               << derchecker->index << endl;
          break;
        }
        break;
      }
    }
  }
#endif

  // Do first reverse pass calculations
  size_t i;
  double* px_u_bari = px->u_bar;
  double* pz_u_bari = pz->u_bar;
  for (i=0;i<nvar;i++)
  {
    *px_u_bari += df1 * *pz_u_bari;

    ++px_u_bari;
    ++pz_u_bari;
  }
  double* py_u_bari = py->u_bar;
  pz_u_bari = pz->u_bar;
  for (i=0;i<nvar;i++)
  {
    *py_u_bari += df2 * *pz_u_bari;

    ++py_u_bari;
    ++pz_u_bari;
  }
  px_u_bari = px->u_bar;
  double* pz_u_dot_bari = pz->u_dot_bar;
  double* xdoti = xdot;
  double* ydoti = ydot;
  for (i=0;i<nvar;i++)
  {
    *px_u_bari += d2f11 * *xdoti * *pz_u_dot_bari;
    *px_u_bari += d2f12 * *ydoti * *pz_u_dot_bari;

    ++px_u_bari;
    ++pz_u_dot_bari;
    ++xdoti;
    ++ydoti;

#if defined(ADDEBUG_PRINT)
    cout << px->u_bar[i] << " " << pz->u_dot_bar[i] << " " << addebug_count
         << endl;
#endif
  }
  py_u_bari = py->u_bar;
  xdoti = xdot;
  ydoti = ydot;
  pz_u_dot_bari = pz->u_dot_bar;
  for (i=0;i<nvar;i++)
  {
    //py->u_bar[i]+=(d2f22)(*(px->u),*(py->u))*ydot[i]*pz->u_dot_bar[i];
    //py->u_bar[i]+=(d2f12)(*(px->u),*(py->u))*xdot[i]*pz->u_dot_bar[i];
    *py_u_bari += d2f22 * *ydoti * *pz_u_dot_bari;
    *py_u_bari += d2f12 * *xdoti * *pz_u_dot_bari;

    ++xdoti;
    ++ydoti;
    ++py_u_bari;
    ++pz_u_dot_bari;

#if defined(ADDEBUG_PRINT)
    cout << py->u_bar[i] << " " << pz->u_dot_bar[i] << " " << addebug_count
         << endl;
#endif
  }
  double* px_u_dot_bari = px->u_dot_bar;
  pz_u_dot_bari = pz->u_dot_bar;
  for (i=0;i<nvar;i++)
  {
    //px->u_dot_bar[i]+=(df1)(*(px->u),*(py->u))*pz->u_dot_bar[i];
    *px_u_dot_bari += df1 * *pz_u_dot_bari;

    ++px_u_dot_bari;
    ++pz_u_dot_bari;
#if defined(ADDEBUG_PRINT)
    cout << px->u_dot_bar[i] << " " << addebug_count << endl;
    cout << pz->u_dot_bar[i] << " " << addebug_count << endl;
#endif
  }
  pz_u_dot_bari = pz->u_dot_bar;
  double* py_u_dot_bari = py->u_dot_bar;
  for (i=0;i<nvar;i++)
  {
    *py_u_dot_bari += df2 * *pz_u_dot_bari;

    ++py_u_dot_bari;
    ++pz_u_dot_bari;
#if defined(ADDEBUG_PRINT)
    cout << py->u_dot_bar[i] << " " << addebug_count << endl;
    cout << pz->u_dot_bar[i] << " " << addebug_count << endl;
#endif
  }

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  memset(pz->u_dot_bar, 0, nvar * sizeofdouble);
  memset(pz->u_bar, 0, nvar * sizeofdouble);

#if defined(PRINT_DERS)
 print_derivatives(pz,"z");
 print_derivatives(px,"x");
 print_derivatives(py,"y");
#endif
}

/**
 * Description not yet available.
 * \param
 */
void read_pass2_2_dvdv(void)
{
  //const int nlist_record_size=sizeof(int)+sizeof(char*);
  // We are going forward for bptr and backword for bptr2
  //
  // list 1
  //
  unsigned int nvar=df1b2variable::nvar;
  test_smartlist & list=f1b2gradlist->list;
  // !!!!!!!!!!!!!!!!!!!!!! change here
  size_t total_bytes=3*sizeof(df1b2_header)+sizeof(char*)
     +(2*nvar+11)*sizeof(double);
  //int total_bytes=3*sizeof(df1b2_header)+sizeof(char*)
   // +2*(nvar+1)*sizeof(double);
// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="UZ";
  size_t slen=strlen(ids);
  total_bytes+=slen;
#endif

  list.check_buffer_size(total_bytes);

// end of string identifier debug stuff

  list.saveposition(); // save pointer to beginning of record;
  fixed_smartlist & nlist=f1b2gradlist->nlist;
   // nlist-=sizeof(int);
  // get record size
  int num_bytes=nlist.bptr->numbytes;
    // nlist+=nlist_record_size;
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

  double xu,yu;
  //df1b2_header x,z;
  //df1b2function2 * pf;

  // get info from tape1
  // get info from tape1
#if defined(SAFE_ALL)
  checkidentiferstring("UZ",list);
  checkidentiferstring("FW",list2);
#endif
  /*
  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * py=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  pf=*(df1b2function2 **) list.bptr;
  list.bptr+=sizeof(char*);
  memcpy(&xu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  memcpy(&yu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  xdot=(double*)list.bptr;
  list.bptr+=nvar*sizeof(double);
  ydot=(double*)list.bptr;
  */
  //char * bptr=f1b2gradlist->list.bptr;
  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * py=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  //pf=*(df1b2function2 **) list.bptr;
  //list.bptr+=sizeof(char*);

  constexpr size_t sizeofdouble = sizeof(double);
  double df1=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double df2=*(double*) list.bptr;
  list.bptr+=sizeofdouble;

  double d2f11=*(double*) list.bptr;
  list.bptr+=sizeofdouble;

  double d2f12=*(double*) list.bptr;
  list.bptr+=sizeofdouble;

  double d2f22=*(double*) list.bptr;
  list.bptr+=sizeofdouble;

  double d3f111=*(double*) list.bptr;
  list.bptr+=sizeofdouble;

  double d3f112=*(double*) list.bptr;
  list.bptr+=sizeofdouble;

  double d3f122=*(double*) list.bptr;
  list.bptr+=sizeofdouble;

  double d3f222=*(double*) list.bptr;
  list.bptr+=sizeofdouble;

  memcpy(&xu,list.bptr,sizeofdouble);
  list.bptr+=sizeofdouble;
  memcpy(&yu,list.bptr,sizeofdouble);
  list.bptr+=sizeofdouble;
  double * xdot=(double*)list.bptr;
  list.bptr+=nvar*sizeofdouble;
  double * ydot=(double*)list.bptr;

  list.restoreposition(num_bytes); // save pointer to beginning of record;

  double * zbar;
  double * zdotbar;

  zbar=(double*)list2.bptr;
  zdotbar=(double*)(list2.bptr+nvar*sizeofdouble);
  list2.restoreposition(); // save pointer to beginning of record;

  double * x_tilde=px->get_u_tilde();
  double * x_dot_tilde=px->get_u_dot_tilde();
  double * x_bar_tilde=px->get_u_bar_tilde();
  double * x_dot_bar_tilde=px->get_u_dot_bar_tilde();
  double * y_tilde=py->get_u_tilde();
  double * y_dot_tilde=py->get_u_dot_tilde();
  double * y_bar_tilde=py->get_u_bar_tilde();
  double * y_dot_bar_tilde=py->get_u_dot_bar_tilde();
  double * z_bar_tilde=pz->get_u_bar_tilde();
  double * z_dot_bar_tilde=pz->get_u_dot_bar_tilde();
  // Do second "reverse-reverse" pass calculations
#if defined(PRINT_DERS)
 print_derivatives(funname,(f),(df1),
  (df2),(d2f11),(d2f12),(d2f22),
  (d3f111),(d3f112),(d3f122),
  (d3f222),1);
 print_derivatives(pz,"z");
 print_derivatives(px,"x");
 print_derivatives(py,"y");
#endif

  memset(z_bar_tilde, 0, nvar * sizeofdouble);
  memset(z_dot_bar_tilde, 0, nvar * sizeofdouble);


  // start with x and add y
  double* x_bar_tildei = x_bar_tilde;
  double* zbari = zbar;
  double* z_bar_tildei = z_bar_tilde;
  for (size_t i=0;i<nvar;i++)
  {
    *x_tilde += d2f11 * *zbari * *x_bar_tildei;
    *z_bar_tildei += df1 * *x_bar_tildei;
    *y_tilde += d2f12 * *zbari * *x_bar_tildei;

    ++x_bar_tildei;
    ++zbari;
    ++z_bar_tildei;
  }

  double* x_dot_bar_tildei = x_dot_bar_tilde;
  double* zdotbari = zdotbar;
  double* z_dot_bar_tildei = z_dot_bar_tilde;
  for (size_t i=0;i<nvar;i++)
  {
    *x_tilde += d2f11 * *zdotbari * *x_dot_bar_tildei;
    *y_tilde += d2f12 * *zdotbari * *x_dot_bar_tildei;
    *z_dot_bar_tildei += df1 * *x_dot_bar_tildei;

    ++x_dot_bar_tildei;
    ++zdotbari;
    ++z_dot_bar_tildei;
  }
  x_bar_tildei = x_bar_tilde;
  zdotbari = zdotbar;
  double* xdoti = xdot;
  double* x_dot_tildei = x_dot_tilde;
  z_dot_bar_tildei = z_dot_bar_tilde;
  for (size_t i=0;i<nvar;i++)
  {
    *x_dot_tildei += d2f11 * *zdotbari * *x_bar_tildei;
    *z_dot_bar_tildei += d2f11 * *xdoti * *x_bar_tildei;
    *x_tilde += d3f111 * *xdoti * *zdotbari * *x_bar_tildei;
    *y_tilde += d3f112 * *xdoti * *zdotbari * *x_bar_tildei;

    ++x_bar_tildei;
    ++zdotbari;
    ++xdoti;
    ++x_dot_tildei;
    ++z_dot_bar_tildei;
  }
  // start with y and add x
  double* y_bar_tildei = y_bar_tilde;
  zbari = zbar;
  z_bar_tildei = z_bar_tilde;
  for (size_t i=0;i<nvar;i++)
  {
    *y_tilde += d2f22 * *zbari * *y_bar_tildei;
    *x_tilde += d2f12 * *zbari * *y_bar_tildei;
    *z_bar_tildei += df2 * *y_bar_tildei;

    ++y_bar_tildei;
    ++zbari;
    ++z_bar_tildei;
  }
  double* y_dot_bar_tildei = y_dot_bar_tilde;
  zdotbari = zdotbar;
  z_dot_bar_tildei = z_dot_bar_tilde;
  for (size_t i=0;i<nvar;i++)
  {
    *y_tilde += d2f22 * *zdotbari * *y_dot_bar_tildei;
    *x_tilde += d2f12 * *zdotbari * *y_dot_bar_tildei;
    *z_dot_bar_tildei += df2 * *y_dot_bar_tildei;

    ++y_dot_bar_tildei;
    ++zdotbari;
    ++z_dot_bar_tildei;
  }
  y_bar_tildei = y_bar_tilde;
  zdotbari = zdotbar;
  double* ydoti = ydot;
  double* y_dot_tildei = y_dot_tilde;
  z_dot_bar_tildei = z_dot_bar_tilde;
  for (size_t i=0;i<nvar;i++)
  {
    *y_dot_tildei += d2f22 * *zdotbari * *y_bar_tildei;
    *z_dot_bar_tildei += d2f22 * *ydoti * *y_bar_tildei;
    *y_tilde += d3f222 * *ydoti * *zdotbari * *y_bar_tildei;
    *x_tilde += d3f122 * *ydoti * *zdotbari * *y_bar_tildei;

    ++y_bar_tildei;
    ++zdotbari;
    ++ydoti;
    ++y_dot_tildei;
    ++z_dot_bar_tildei;
  }
  x_bar_tildei = x_bar_tilde;
  ydoti = ydot;
  zdotbari = zdotbar;
  y_dot_tildei = y_dot_tilde;
  z_dot_bar_tildei = z_dot_bar_tilde;
  for (size_t i=0;i<nvar;i++)
  {
    *x_tilde += d3f112 * *ydoti * *zdotbari * *x_bar_tildei;
    *y_tilde += d3f122 * *ydoti * *zdotbari * *x_bar_tildei;
    *y_dot_tildei += d2f12 * *zdotbari * *x_bar_tildei;
    *z_dot_bar_tildei += d2f12 * *ydoti * *x_bar_tildei;

    ++x_bar_tildei;
    ++ydoti;
    ++zdotbari;
    ++y_dot_tildei;
    ++z_dot_bar_tildei;
  }
  zdotbari = zdotbar;
  y_bar_tildei = y_bar_tilde;
  xdoti = xdot;
  x_dot_tildei = x_dot_tilde;
  z_dot_bar_tildei = z_dot_bar_tilde;
  for (size_t i=0;i<nvar;i++)
  {
    *x_tilde+= d3f112 * *xdoti * *zdotbari * *y_bar_tildei;
    *y_tilde+= d3f122 * *xdoti * *zdotbari * *y_bar_tildei;
    *x_dot_tildei += d2f12 * *zdotbari * *y_bar_tildei;
    *z_dot_bar_tildei += d2f12 * *xdoti * *y_bar_tildei;

    ++zdotbari;
    ++y_bar_tildei;
    ++xdoti;
    ++x_dot_tildei;
    ++z_dot_bar_tildei;
  }
#if defined(__DERCHECK__)
  if (derchecker->node_number)
  {
    if (derchecker->counter == derchecker->node_number)
    {
      if (derchecker->pass_number==1) // increment the variable of interest
      {
        switch(derchecker->vartype)
        {
        case 1:
          if (!derchecker->dotflag)
            derchecker->der_value=
              px->u_bar_tilde[derchecker->index-1];
          else
            derchecker->der_value=
              px->u_dot_bar_tilde[derchecker->index-1];
          break;
        case 2:
          if (!derchecker->dotflag)
            derchecker->der_value=
              py->u_bar_tilde[derchecker->index-1];
          else
            derchecker->der_value=
              py->u_dot_bar_tilde[derchecker->index-1];
          break;
        case 3:
          if (!derchecker->dotflag)
            derchecker->der_value=
              pz->u_bar_tilde[derchecker->index-1];
          else
            derchecker->der_value=
              pz->u_dot_bar_tilde[derchecker->index-1];
          break;
        default:
          cerr << "Invalid index value for dercheck_index was "
               << derchecker->index << endl;
        }
      }
    }
  }
#endif
#if defined(PRINT_DERS)
 print_derivatives(pz,"z");
 print_derivatives(px,"x");
 print_derivatives(py,"y");
#endif
}

/**
 * Description not yet available.
 * \param
 */
void read_pass2_3_dvdv(void)
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
  double xu;
  double yu;
  //df1b2_header x,z;
  //df1b2function2 * pf;

  // get info from tape1
  // get info from tape1
#if defined(SAFE_ALL)
  checkidentiferstring("UZ",list);
#endif
 /*
  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * py=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  pf=*(df1b2function2 **) list.bptr;
  list.bptr+=sizeof(char*);
  memcpy(&xu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  memcpy(&yu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  xdot=(double*)list.bptr;
  list.bptr+=nvar*sizeof(double);
  ydot=(double*)list.bptr;
 */
  constexpr size_t sizeofdouble = sizeof(double);
  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * py=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  //pf=*(df1b2function2 **) list.bptr;
  //list.bptr+=sizeof(char*);

  double df1=*(double*) list.bptr;
  list.bptr+=sizeofdouble;

  double df2=*(double*) list.bptr;
  list.bptr+=sizeofdouble;

  double d2f11=*(double*) list.bptr;
  list.bptr+=sizeofdouble;

  double d2f12=*(double*) list.bptr;
  list.bptr+=sizeofdouble;

  double d2f22=*(double*) list.bptr;
  list.bptr+=sizeofdouble;

#if defined(PRINT_DERS)
  double d3f111=*(double*) list.bptr;
#endif
  list.bptr+=sizeofdouble;

#if defined(PRINT_DERS)
  double d3f112=*(double*) list.bptr;
#endif
  list.bptr+=sizeofdouble;

#if defined(PRINT_DERS)
  double d3f122=*(double*) list.bptr;
#endif
  list.bptr+=sizeofdouble;

#if defined(PRINT_DERS)
  double d3f222=*(double*) list.bptr;
#endif
  list.bptr+=sizeofdouble;

  memcpy(&xu,list.bptr,sizeofdouble);
  list.bptr+=sizeofdouble;
  memcpy(&yu,list.bptr,sizeofdouble);
  list.bptr+=sizeofdouble;
  double * xdot=(double*)list.bptr;
  list.bptr+=nvar*sizeofdouble;
  double * ydot=(double*)list.bptr;

  list.restoreposition(); // save pointer to beginning of record;
#if defined(PRINT_DERS)
 print_derivatives(funname,(f),(df1),
  (df2),(d2f11),(d2f12),(d2f22),
  (d3f111),(d3f112),(d3f122),
  (d3f222),1);
 print_derivatives(pz,"z");
 print_derivatives(px,"x");
 print_derivatives(py,"y");
#endif

  *(px->u_tilde)+=(df1)* *(pz->u_tilde);
  *(py->u_tilde)+=(df2)* *(pz->u_tilde);

  double* pz_u_dot_tildei = pz->u_dot_tilde;
  double* xdoti = xdot;
  double* ydoti = ydot;
  for (size_t i=0;i<nvar;i++)
  {
    *(px->u_tilde) += d2f11 * *xdoti * *pz_u_dot_tildei;
    *(py->u_tilde) += d2f12 * *xdoti * *pz_u_dot_tildei;
    *(py->u_tilde) += d2f22 * *ydoti * *pz_u_dot_tildei;
    *(px->u_tilde) += d2f12 * *ydoti * *pz_u_dot_tildei;

    ++pz_u_dot_tildei;
    ++ydoti;
    ++xdoti;
  }

  double* px_u_dot_tildei = px->u_dot_tilde;
  double* py_u_dot_tildei = py->u_dot_tilde;
  pz_u_dot_tildei = pz->u_dot_tilde;
  for (size_t i=0;i<nvar;i++)
  {
    *px_u_dot_tildei += df1 * *pz_u_dot_tildei;
    *py_u_dot_tildei += df2 * *pz_u_dot_tildei;

    ++px_u_dot_tildei;
    ++py_u_dot_tildei;
    ++pz_u_dot_tildei;
  }
  *(pz->u_tilde)=0;
  memset(pz->u_dot_tilde, 0, nvar * sizeofdouble);
#if defined(PRINT_DERS)
 print_derivatives(pz,"z");
 print_derivatives(px,"x");
 print_derivatives(py,"y");
#endif
}
