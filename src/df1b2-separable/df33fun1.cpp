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
#include "df33fun.h"

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

void ad_read_pass2_dvdvdv(void);

/**
 * Description not yet available.
 * \param
 */
 int df1b2_gradlist::write_pass1(const df1b2variable * _px,
   const df1b2variable * _py,const df1b2variable * pw,
   const df1b2variable * pz,
   double df_x, double df_y, double df_z,
   double df_xx, double df_xy,double df_xz,double df_yy,
   double df_yz,double df_zz,
   double df_xxx,
   double df_xxy,
   double df_xxz,
   double df_xyy,
   double df_xyz,
   double df_xzz,
   double df_yyy,
   double df_yyz,
   double df_yzz,
   double df_zzz)
 {
   ADUNCONST(df1b2variable*,px)
   ADUNCONST(df1b2variable*,py)
   ncount++;
#if defined(CHECK_COUNT)
  if (ncount >= ncount_check)
    ncount_checker(ncount,ncount_check);
#endif
   int _nvar=df1b2variable::nvar;
#ifndef OPT_LIB
  assert(_nvar > 0);
#endif
   size_t nvar = (size_t)_nvar;

   size_t total_bytes=4*sizeof(df1b2_header)+sizeof(char*)
     +(3*nvar+22)*sizeof(double);

// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="U8";
  int slen=strlen(ids);
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
   memcpy(list,(df1b2_header*)(pw),sizeof(df1b2_header));
   memcpy(list,(df1b2_header*)(pz),sizeof(df1b2_header));
   //memcpy(list,&pf,sizeof(char *));
   //*(char**)(list.bptr)=(char*)pf;

  /*
   memcpy(list,&df_x,sizeof(double));
   memcpy(list,&df_y,sizeof(double));
   memcpy(list,&df_xx,sizeof(double));
   memcpy(list,&df_xy,sizeof(double));
   memcpy(list,&df_yy,sizeof(double));
   memcpy(list,&df_xxx,sizeof(double));
   memcpy(list,&df_xxy,sizeof(double));
   memcpy(list,&df_xyy,sizeof(double));
   memcpy(list,&df_yyy,sizeof(double));
  */
   const int sizeofdouble = sizeof(double);
   memcpy(list,&df_x,sizeofdouble);
   memcpy(list,&df_y,sizeofdouble);
   memcpy(list,&df_z,sizeofdouble);
   memcpy(list,&df_xx,sizeofdouble);
   memcpy(list,&df_xy,sizeofdouble);
   memcpy(list,&df_xz,sizeofdouble);
   memcpy(list,&df_yy,sizeofdouble);
   memcpy(list,&df_yz,sizeofdouble);
   memcpy(list,&df_zz,sizeofdouble);
   memcpy(list,&df_xxx,sizeofdouble);
   memcpy(list,&df_xxy,sizeofdouble);
   memcpy(list,&df_xxz,sizeofdouble);
   memcpy(list,&df_xyy,sizeofdouble);
   memcpy(list,&df_xyz,sizeofdouble);
   memcpy(list,&df_xzz,sizeofdouble);
   memcpy(list,&df_yyy,sizeofdouble);
   memcpy(list,&df_yyz,sizeofdouble);
   memcpy(list,&df_yzz,sizeofdouble);
   memcpy(list,&df_zzz,sizeofdouble);

   memcpy(list,px->get_u(),sizeofdouble);
   memcpy(list,py->get_u(),sizeofdouble);
   memcpy(list,pw->get_u(),sizeofdouble);
   memcpy(list,px->get_u_dot(),nvar*sizeofdouble);
   memcpy(list,py->get_u_dot(),nvar*sizeofdouble);
   memcpy(list,pw->get_u_dot(),nvar*sizeofdouble);
   // ***** write  record size
   nlist.bptr->numbytes=adptr_diff(list.bptr,tmpptr);
   nlist.bptr->pf=(ADrfptr)(&ad_read_pass2_dvdvdv);
   ++nlist;
   return 0;
 }


void read_pass2_1_dvdvdv(void);
void read_pass2_2_dvdvdv(void);
void read_pass2_3_dvdvdv(void);

/**
 * Description not yet available.
 * \param
 */
void ad_read_pass2_dvdvdv(void)
{
  switch(df1b2variable::passnumber)
  {
  case 1:
    read_pass2_1_dvdvdv();
    break;
  case 2:
    read_pass2_2_dvdvdv();
    break;
  case 3:
    read_pass2_3_dvdvdv();
    break;
  default:
    cerr << "illegal value for df1b2variable::pass = "
         << df1b2variable::passnumber << endl;
    exit(1);
  }
}

/**
 * Description not yet available.
 * \param
 */
void read_pass2_1_dvdvdv(void)
{
  // We are going backword for bptr and nbptr
  // and  forward for bptr2 and nbptr2
  // the current entry+2 in bptr is the size of the record i.e
  // points to the next record
  //char * bptr=f1b2gradlist->bptr;
  //char * bptr2=f1b2gradlist2->bptr;
   int _nvar=df1b2variable::nvar;
#ifndef OPT_LIB
  assert(_nvar > 0);
#endif
   size_t nvar = (size_t)_nvar;
  test_smartlist& list=f1b2gradlist->list;
  //f1b2gradlist->nlist-=sizeof(int);
  int num_bytes=f1b2gradlist->nlist.bptr->numbytes;
  list-=num_bytes;
  list.saveposition(); // save pointer to beginning of record;
  double xu,yu,wu;
  //ad_dstar xdot,ydot;
  //df1b2function2 * pf;

  // get info from tape1
#if defined(SAFE_ARRAYS)
  checkidentiferstring("U8",f1b2gradlist->list);
#endif
  char * bptr=f1b2gradlist->list.bptr;
  df1b2_header * px=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);
  df1b2_header * py=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);
  df1b2_header * pw=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);
  //pf=*(df1b2function2 **) bptr;
  //bptr+=sizeof(char*);

  double df1=*(double*) bptr;
  bptr+=sizeof(double);

  double df2=*(double*) bptr;
  bptr+=sizeof(double);

  double df3=*(double*) bptr;
  bptr+=sizeof(double);

  double d2f11=*(double*) bptr;
  bptr+=sizeof(double);

  double d2f12=*(double*) bptr;
  bptr+=sizeof(double);

  double d2f13=*(double*) bptr;
  bptr+=sizeof(double);

  double d2f22=*(double*) bptr;
  bptr+=sizeof(double);

  double d2f23=*(double*) bptr;
  bptr+=sizeof(double);

  double d2f33=*(double*) bptr;
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
  double d3f113=*(double*) bptr;
#endif
  bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f122=*(double*) bptr;
#endif
  bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f123=*(double*) bptr;
#endif
  bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f133=*(double*) bptr;
#endif
  bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f222=*(double*) bptr;
#endif
  bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f223=*(double*) bptr;
#endif
  bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f233=*(double*) bptr;
#endif
  bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f333=*(double*) bptr;
#endif
  bptr+=sizeof(double);

  memcpy(&xu,bptr,sizeof(double));
  bptr+=sizeof(double);
  memcpy(&yu,bptr,sizeof(double));
  bptr+=sizeof(double);
  memcpy(&wu,bptr,sizeof(double));
  bptr+=sizeof(double);
  double * xdot=(double*)bptr;
  bptr+=nvar*sizeof(double);
  double * ydot=(double*)bptr;
  bptr+=nvar*sizeof(double);
  double * wdot=(double*)bptr;

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
  char ids[]="FX";
  int slen=strlen(ids);
  total_bytes+=slen;
#endif

  list2.check_buffer_size(total_bytes);
  void * tmpptr=list2.bptr;
#if defined(SAFE_ALL)
  memcpy(list2,ids,slen);
#endif

     fixed_smartlist2 & nlist2 = f1b2gradlist->nlist2;
  const int sizeofdouble = sizeof(double);
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
  for (size_t i=0;i<nvar;i++)
  {
    px->u_bar[i]+=(df1)*pz->u_bar[i];
  }
  for (size_t i=0;i<nvar;i++)
  {
    py->u_bar[i]+=(df2)*pz->u_bar[i];
  }
  for (size_t i=0;i<nvar;i++)
  {
    pw->u_bar[i]+=(df3)*pz->u_bar[i];
  }
  for (size_t i=0;i<nvar;i++)
  {
    px->u_bar[i]+=(d2f11)*xdot[i]*pz->u_dot_bar[i];
    px->u_bar[i]+=(d2f12)*ydot[i]*pz->u_dot_bar[i];
    px->u_bar[i]+=(d2f13)*wdot[i]*pz->u_dot_bar[i];
  }
  for (size_t i=0;i<nvar;i++)
  {
    py->u_bar[i]+=(d2f12)*xdot[i]*pz->u_dot_bar[i];
    py->u_bar[i]+=(d2f22)*ydot[i]*pz->u_dot_bar[i];
    py->u_bar[i]+=(d2f13)*wdot[i]*pz->u_dot_bar[i];
  }
  for (size_t i=0;i<nvar;i++)
  {
    pw->u_bar[i]+=(d2f13)*xdot[i]*pz->u_dot_bar[i];
    pw->u_bar[i]+=(d2f23)*ydot[i]*pz->u_dot_bar[i];
    pw->u_bar[i]+=(d2f33)*wdot[i]*pz->u_dot_bar[i];
  }
  for (size_t i=0;i<nvar;i++)
  {
    px->u_dot_bar[i]+=(df1)*pz->u_dot_bar[i];
  }
  for (size_t i=0;i<nvar;i++)
  {
    py->u_dot_bar[i]+=(df2)*pz->u_dot_bar[i];
  }
  for (size_t i=0;i<nvar;i++)
  {
    pw->u_dot_bar[i]+=(df3)*pz->u_dot_bar[i];
  }

  for (size_t i=0;i<nvar;i++)
  {
    pz->u_bar[i]=0;
  }
  for (size_t i=0;i<nvar;i++)
  {
    pz->u_dot_bar[i]=0;
  }
}

/**
 * Description not yet available.
 * \param
 */
void read_pass2_2_dvdvdv(void)
{
  //const int nlist_record_size=sizeof(int)+sizeof(char*);
  // We are going forward for bptr and backword for bptr2
  //
  // list 1
  //
   int _nvar=df1b2variable::nvar;
#ifndef OPT_LIB
  assert(_nvar > 0);
#endif
   size_t nvar = (size_t)_nvar;
  test_smartlist & list=f1b2gradlist->list;

  size_t total_bytes=3*sizeof(df1b2_header)+sizeof(char*)
    +2*(nvar+1)*sizeof(double);
// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="U8";
  int slen=strlen(ids);
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

  double xu,yu,wu;
  //df1b2_header x,z;
  //df1b2function2 * pf;

  // get info from tape1
  // get info from tape1
#if defined(SAFE_ARRAYS)
  checkidentiferstring("U8",list);
  checkidentiferstring("FX",list2);
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
  df1b2_header * pw=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);

  double df1=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double df2=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double df3=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d2f11=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d2f12=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d2f13=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d2f22=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d2f23=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d2f33=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d3f111=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d3f112=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d3f113=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d3f122=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d3f123=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d3f133=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d3f222=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d3f223=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d3f233=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d3f333=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  memcpy(&xu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  memcpy(&yu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  memcpy(&wu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  double * xdot=(double*)list.bptr;
  list.bptr+=nvar*sizeof(double);
  double * ydot=(double*)list.bptr;
  list.bptr+=nvar*sizeof(double);
  double * wdot=(double*)list.bptr;

  list.restoreposition(num_bytes); // save pointer to beginning of record;

  double * zbar;
  double * zdotbar;


  zbar=(double*)list2.bptr;
  zdotbar=(double*)(list2.bptr+nvar*sizeof(double));
  list2.restoreposition(); // save pointer to beginning of record;

  double * x_tilde=px->get_u_tilde();
  double * x_dot_tilde=px->get_u_dot_tilde();
  double * x_bar_tilde=px->get_u_bar_tilde();
  double * x_dot_bar_tilde=px->get_u_dot_bar_tilde();
  double * y_tilde=py->get_u_tilde();
  double * y_dot_tilde=py->get_u_dot_tilde();
  double * y_bar_tilde=py->get_u_bar_tilde();
  double * y_dot_bar_tilde=py->get_u_dot_bar_tilde();
  double * w_tilde=pw->get_u_tilde();
  double * w_dot_tilde=pw->get_u_dot_tilde();
  double * w_bar_tilde=pw->get_u_bar_tilde();
  double * w_dot_bar_tilde=pw->get_u_dot_bar_tilde();
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
 print_derivatives(pw,"x");
 print_derivatives(py,"y");
#endif

  for (size_t i=0;i<nvar;i++)
  {
    z_bar_tilde[i]=0;
    z_dot_bar_tilde[i]=0;
  }

  for (size_t i=0;i<nvar;i++)
  {
    *x_tilde+=(d2f11)*zbar[i]*x_bar_tilde[i];
    *y_tilde+=(d2f12)*zbar[i]*x_bar_tilde[i];
    *w_tilde+=(d2f13)*zbar[i]*x_bar_tilde[i];

    *x_tilde+=(d2f12)*zbar[i]*y_bar_tilde[i];
    *y_tilde+=(d2f22)*zbar[i]*y_bar_tilde[i];
    *w_tilde+=(d2f23)*zbar[i]*y_bar_tilde[i];

    *x_tilde+=(d2f13)*zbar[i]*w_bar_tilde[i];
    *y_tilde+=(d2f23)*zbar[i]*w_bar_tilde[i];
    *w_tilde+=(d2f33)*zbar[i]*w_bar_tilde[i];
  }

  for (size_t i=0;i<nvar;i++)
  {
    *x_tilde+=(d2f11)*zdotbar[i]*x_dot_bar_tilde[i];
    *y_tilde+=(d2f12)*zdotbar[i]*x_dot_bar_tilde[i];
    *w_tilde+=(d2f13)*zdotbar[i]*x_dot_bar_tilde[i];

    *x_tilde+=(d2f12)*zdotbar[i]*y_dot_bar_tilde[i];
    *y_tilde+=(d2f22)*zdotbar[i]*y_dot_bar_tilde[i];
    *w_tilde+=(d2f23)*zdotbar[i]*y_dot_bar_tilde[i];

    *x_tilde+=(d2f13)*zdotbar[i]*w_dot_bar_tilde[i];
    *y_tilde+=(d2f23)*zdotbar[i]*w_dot_bar_tilde[i];
    *w_tilde+=(d2f33)*zdotbar[i]*w_dot_bar_tilde[i];
  }

  for (size_t i=0;i<nvar;i++)
  {
    *x_tilde+=(d3f111)*xdot[i]*zdotbar[i]*x_bar_tilde[i];
    *y_tilde+=(d3f112)*xdot[i]*zdotbar[i]*x_bar_tilde[i];
    *w_tilde+=(d3f113)*xdot[i]*zdotbar[i]*x_bar_tilde[i];

    *x_tilde+=(d3f112)*xdot[i]*zdotbar[i]*y_bar_tilde[i];
    *y_tilde+=(d3f122)*xdot[i]*zdotbar[i]*y_bar_tilde[i];
    *w_tilde+=(d3f123)*xdot[i]*zdotbar[i]*y_bar_tilde[i];

    *x_tilde+=(d3f113)*xdot[i]*zdotbar[i]*w_bar_tilde[i];
    *y_tilde+=(d3f123)*xdot[i]*zdotbar[i]*w_bar_tilde[i];
    *w_tilde+=(d3f133)*xdot[i]*zdotbar[i]*w_bar_tilde[i];

    *x_tilde+=(d3f112)*ydot[i]*zdotbar[i]*x_bar_tilde[i];
    *y_tilde+=(d3f122)*ydot[i]*zdotbar[i]*x_bar_tilde[i];
    *w_tilde+=(d3f123)*ydot[i]*zdotbar[i]*x_bar_tilde[i];

    *x_tilde+=(d3f122)*ydot[i]*zdotbar[i]*y_bar_tilde[i];
    *y_tilde+=(d3f222)*ydot[i]*zdotbar[i]*y_bar_tilde[i];
    *w_tilde+=(d3f223)*ydot[i]*zdotbar[i]*y_bar_tilde[i];

    *x_tilde+=(d3f123)*ydot[i]*zdotbar[i]*w_bar_tilde[i];
    *y_tilde+=(d3f223)*ydot[i]*zdotbar[i]*w_bar_tilde[i];
    *w_tilde+=(d3f233)*ydot[i]*zdotbar[i]*w_bar_tilde[i];

    *x_tilde+=(d3f113)*wdot[i]*zdotbar[i]*x_bar_tilde[i];
    *y_tilde+=(d3f123)*wdot[i]*zdotbar[i]*x_bar_tilde[i];
    *w_tilde+=(d3f133)*wdot[i]*zdotbar[i]*x_bar_tilde[i];

    *x_tilde+=(d3f123)*wdot[i]*zdotbar[i]*y_bar_tilde[i];
    *y_tilde+=(d3f223)*wdot[i]*zdotbar[i]*y_bar_tilde[i];
    *w_tilde+=(d3f233)*wdot[i]*zdotbar[i]*y_bar_tilde[i];

    *x_tilde+=(d3f133)*wdot[i]*zdotbar[i]*w_bar_tilde[i];
    *y_tilde+=(d3f233)*wdot[i]*zdotbar[i]*w_bar_tilde[i];
    *w_tilde+=(d3f333)*wdot[i]*zdotbar[i]*w_bar_tilde[i];
  }

  for (size_t i=0;i<nvar;i++)
  {
    z_bar_tilde[i]+=(df1)*x_bar_tilde[i];
    z_bar_tilde[i]+=(df2)*y_bar_tilde[i];
    z_bar_tilde[i]+=(df3)*w_bar_tilde[i];
  }

  for (size_t i=0;i<nvar;i++)
  {
    z_dot_bar_tilde[i]+=(df1)*x_dot_bar_tilde[i];
    z_dot_bar_tilde[i]+=(df2)*y_dot_bar_tilde[i];
    z_dot_bar_tilde[i]+=(df3)*w_dot_bar_tilde[i];
  }

  for (size_t i=0;i<nvar;i++)
  {
    x_dot_tilde[i]+=(d2f11)*zdotbar[i]*x_bar_tilde[i];
    y_dot_tilde[i]+=(d2f12)*zdotbar[i]*x_bar_tilde[i];
    w_dot_tilde[i]+=(d2f13)*zdotbar[i]*x_bar_tilde[i];

    x_dot_tilde[i]+=(d2f12)*zdotbar[i]*y_bar_tilde[i];
    y_dot_tilde[i]+=(d2f22)*zdotbar[i]*y_bar_tilde[i];
    w_dot_tilde[i]+=(d2f23)*zdotbar[i]*y_bar_tilde[i];

    x_dot_tilde[i]+=(d2f13)*zdotbar[i]*w_bar_tilde[i];
    y_dot_tilde[i]+=(d2f23)*zdotbar[i]*w_bar_tilde[i];
    w_dot_tilde[i]+=(d2f33)*zdotbar[i]*w_bar_tilde[i];
  }

  for (size_t i=0;i<nvar;i++)
  {
    z_dot_bar_tilde[i]+=(d2f11)*xdot[i]*x_bar_tilde[i];
    z_dot_bar_tilde[i]+=(d2f12)*xdot[i]*y_bar_tilde[i];
    z_dot_bar_tilde[i]+=(d2f13)*xdot[i]*w_bar_tilde[i];

    z_dot_bar_tilde[i]+=(d2f12)*ydot[i]*x_bar_tilde[i];
    z_dot_bar_tilde[i]+=(d2f22)*ydot[i]*y_bar_tilde[i];
    z_dot_bar_tilde[i]+=(d2f23)*ydot[i]*w_bar_tilde[i];

    z_dot_bar_tilde[i]+=(d2f13)*wdot[i]*x_bar_tilde[i];
    z_dot_bar_tilde[i]+=(d2f23)*wdot[i]*y_bar_tilde[i];
    z_dot_bar_tilde[i]+=(d2f33)*wdot[i]*w_bar_tilde[i];
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
void read_pass2_3_dvdvdv(void)
{
  // We are going backword for bptr and forward for bptr2
  // the current entry+2 in bptr is the size of the record i.e
  // points to the next record
   int _nvar=df1b2variable::nvar;
#ifndef OPT_LIB
  assert(_nvar > 0);
#endif
   size_t nvar = (size_t)_nvar;
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
  double wu;
  //df1b2_header x,z;
  //df1b2function2 * pf;

  // get info from tape1
  // get info from tape1
#if defined(SAFE_ARRAYS)
  checkidentiferstring("U8",list);
#endif

  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * py=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pw=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);

  double df1=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double df2=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double df3=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d2f11=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d2f12=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d2f13=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d2f22=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d2f23=*(double*) list.bptr;
  list.bptr+=sizeof(double);

  double d2f33=*(double*) list.bptr;
  list.bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f111=*(double*) list.bptr;
#endif
  list.bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f112=*(double*) list.bptr;
#endif
  list.bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f113=*(double*) list.bptr;
#endif
  list.bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f122=*(double*) list.bptr;
#endif
  list.bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f123=*(double*) list.bptr;
#endif
  list.bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f133=*(double*) list.bptr;
#endif
  list.bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f222=*(double*) list.bptr;
#endif
  list.bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f223=*(double*) list.bptr;
#endif
  list.bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f233=*(double*) list.bptr;
#endif
  list.bptr+=sizeof(double);

#if defined(PRINT_DERS)
  double d3f333=*(double*) list.bptr;
#endif
  list.bptr+=sizeof(double);

  memcpy(&xu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  memcpy(&yu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  memcpy(&wu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  double * xdot=(double*)list.bptr;
  list.bptr+=nvar*sizeof(double);
  double * ydot=(double*)list.bptr;
  list.bptr+=nvar*sizeof(double);
  double * wdot=(double*)list.bptr;

  list.restoreposition(); // save pointer to beginning of record;
#if defined(PRINT_DERS)
 print_derivatives(funname,(f),(df1),
  (df2),(d2f11),(d2f12),(d2f22),
  (d3f111),(d3f112),(d3f122),
  (d3f222),1);
 print_derivatives(pz,"z");
 print_derivatives(px,"x");
 print_derivatives(py,"y");
 print_derivatives(pw,"y");
#endif

  *(px->u_tilde)+=(df1)* *(pz->u_tilde);
  *(py->u_tilde)+=(df2)* *(pz->u_tilde);
  *(pw->u_tilde)+=(df3)* *(pz->u_tilde);

  for (size_t i=0;i<nvar;i++)
  {
    *(px->u_tilde)+=(d2f11)*xdot[i]*pz->u_dot_tilde[i];
    *(py->u_tilde)+=(d2f12)*xdot[i]*pz->u_dot_tilde[i];
    *(pw->u_tilde)+=(d2f13)*xdot[i]*pz->u_dot_tilde[i];

    *(px->u_tilde)+=(d2f12)*ydot[i]*pz->u_dot_tilde[i];
    *(py->u_tilde)+=(d2f22)*ydot[i]*pz->u_dot_tilde[i];
    *(pw->u_tilde)+=(d2f23)*ydot[i]*pz->u_dot_tilde[i];

    *(px->u_tilde)+=(d2f13)*wdot[i]*pz->u_dot_tilde[i];
    *(py->u_tilde)+=(d2f23)*wdot[i]*pz->u_dot_tilde[i];
    *(pw->u_tilde)+=(d2f33)*wdot[i]*pz->u_dot_tilde[i];
  }
  for (size_t i=0;i<nvar;i++)
  {
    px->u_dot_tilde[i]+=(df1)*pz->u_dot_tilde[i];
    py->u_dot_tilde[i]+=(df2)*pz->u_dot_tilde[i];
    pw->u_dot_tilde[i]+=(df3)*pz->u_dot_tilde[i];
  }
  *(pz->u_tilde)=0;
  for (size_t i=0;i<nvar;i++)
  {
    pz->u_dot_tilde[i]=0;
  }


#if defined(PRINT_DERS)
 print_derivatives(pz,"z");
 print_derivatives(px,"x");
 print_derivatives(py,"y");
 print_derivatives(pw,"y");
#endif
}
