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
#include <admodel.h>
#include <df1b2fun.h>
#include "f1b2locl.h"
#include <adrndeff.h>

static void xxx(double*,double*){;}
//static void xxx(double[]){;}

/**
 * Description not yet available.
 * \param
 */
static void begin_local_calculations(int& nap)
{
  df1b2_gradlist::set_no_derivatives();
  local_init_var::allocate_all();
  local_dep_var::allocate_all();
  nap=local_init_var::num_active_parameters;
}

int write_pass1(const df1b2variable * _px,
  const df1b2variable * _py,
  const df1b2variable * _pz,int nap);

/**
 * Description not yet available.
 * \param
 */
df1b2variable plocal_tester(int i,const df1b2variable& x ,
  const df1b2variable& y)
{
  df1b2variable z;
  z=square(x+2.0*y+2.5);
  return z;
}

/**
 * Description not yet available.
 * \param
 */
df1b2variable   local_tester(int i,local_init_df1b2variable x ,
  local_init_df1b2variable y)
{
  int nap;
  local_dep_df1b2variable z;
  {
    begin_local_calculations(nap);
    z=square(x+2.0*y+2.5);
    local_init_var::end_local_calculations();
    // WRITE WHATEVER ON TAPE
  }
  if (!df1b2_gradlist::no_derivatives)
  {
    write_pass1(x.p,y.p,z.p,nap);
    //f1b2gradlist->write_pass1(&x,&y);
  }
  return *(z.p);
}
 void ad_read_xxx(void);

/**
 * Description not yet available.
 * \param
 */
int write_pass1(const df1b2variable * px,
  const df1b2variable * py,
  const df1b2variable * pz,int nap)
 {
   //ADUNCONST(local_init_df1b2variable *,px)
#if defined(CHECK_COUNT)
  if (ncount >= ncount_check)
    cout << ncount << endl;
#endif
   int nvar=df1b2variable::nvar;

   //int total_bytes=3*sizeof(df1b2_header)+sizeof(char*)
   //  +2*(nvar+1)*sizeof(double);
   int total_bytes=3*sizeof(df1b2_header)
     +2*(nvar+1)*sizeof(double);
// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="DL";
  int slen=strlen(ids);
  total_bytes+=2*slen;
#endif
  f1b2gradlist->list.check_buffer_size(total_bytes);
  void * tmpptr=f1b2gradlist->list.bptr;
#if defined(SAFE_ALL)
  memcpy(f1b2gradlist->list,ids,slen);
#endif
// end of string identifier debug stuff
   df1b2_header& tmphead1=(df1b2_header&)(*px);
   df1b2_header& tmphead2=(df1b2_header&)(*py);
   df1b2_header& dephead1=(df1b2_header&)(*pz);

   // copy the headers
   memcpy(f1b2gradlist->list,&tmphead1,sizeof(df1b2_header));
   memcpy(f1b2gradlist->list,&tmphead2,sizeof(df1b2_header));
   memcpy(f1b2gradlist->list,&dephead1,sizeof(df1b2_header));

   // copy u
   memcpy(f1b2gradlist->list,px->get_u(),sizeof(double));
   memcpy(f1b2gradlist->list,py->get_u(),sizeof(double));
   memcpy(f1b2gradlist->list,pz->get_u(),sizeof(double));

   // copy u_dot
   int gnv=((twointsandptr*)(px->ptr))->nvar;
   memcpy(f1b2gradlist->list,&gnv,sizeof(int));
   memcpy(f1b2gradlist->list,&nap,sizeof(int));
   memcpy(f1b2gradlist->list,px->get_u_dot(),gnv*sizeof(double));
   memcpy(f1b2gradlist->list,py->get_u_dot(),gnv*sizeof(double));
   memcpy(f1b2gradlist->list,pz->get_u_dot(),gnv*sizeof(double));

#if defined(SAFE_ALL)
  char ids2[]="EL";
  int slen2=strlen(ids2);
  memcpy(f1b2gradlist->list,ids2,slen2);
#endif
   // ***** write  record size
   f1b2gradlist->nlist.bptr->numbytes=
      adptr_diff(f1b2gradlist->list.bptr,tmpptr);
   f1b2gradlist->nlist.bptr->pf=(ADrfptr)(&ad_read_xxx);
      ++(f1b2gradlist->nlist);
   return 0;
 }

/**
 * Description not yet available.
 * \param
 */
void read_xxx_1(void)
{
  // We are going backword for bptr and forward for bptr2
  // the current entry+2 in bptr is the size of the record i.e
  // points to the next record
  //int nvar=df1b2variable::nvar;
  fixed_smartlist & nlist=f1b2gradlist->nlist;
  test_smartlist& list=f1b2gradlist->list;
   // nlist-=sizeof(int);
  // get record size
  int num_bytes=nlist.bptr->numbytes;
  // backup the size of the record
  list-=num_bytes;
  list.saveposition(); // save pointer to beginning of record;
  // save the pointer to the beginning of the record
#if defined(SAFE_ARRAYS)
  checkidentiferstring("DL",list);
#endif
  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * py=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  //double xu,xpu,yu,ypu,zu,zpu;
  double xu,yu,zu;
  memcpy(&xu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);

  memcpy(&yu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);

  memcpy(&zu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);

  int nvx;
  int nap;
  double *xudot,*yudot,*zudot;
  memcpy(&nvx,list.bptr,sizeof(int));
  list.bptr+=sizeof(int);
  memcpy(&nap,list.bptr,sizeof(int));
  list.bptr+=sizeof(int);
  xudot = (double*) list.bptr;
  list.bptr+=nvx*sizeof(double);
  yudot = (double*) list.bptr;
  list.bptr+=nvx*sizeof(double);
  zudot = (double*) list.bptr;
  list.bptr+=nvx*sizeof(double);
#if defined(SAFE_ARRAYS)
  checkidentiferstring("EL",list);
#endif
  xxx(xudot,yudot);
  xxx(zudot,yudot);

  list.restoreposition(); // save pointer to beginning of record;

  f1b2gradlist=localf1b2gradlist;
  df1b2variable::save_adpool_pointer();


  adpool * tmppool=df1b2variable::pool;
  if (tmppool)
  {
    //cout << tmppool << endl;
    // check if current pool is the right size
    if (tmppool->nvar != nap)
    {
      // check sizes of other pools
      int found_pool_flag=0;
      for (int i=0;i<df1b2variable::adpool_counter;i++)
      {
        if (df1b2variable::adpool_vector[i]->nvar == nap)
        {
          adpool * tmp = df1b2variable::pool;
          df1b2variable::pool=df1b2variable::adpool_vector[i];
          df1b2variable::nvar=nap;
          if (!tmp->on_adpool_vector())
          {
            df1b2variable::adpool_vector[df1b2variable::adpool_counter]=tmp;
            df1b2variable::nvar_vector[df1b2variable::adpool_counter]=
              tmp->nvar;
            //df1b2variable::adpool_counter++;
            df1b2variable::increment_adpool_counter();
            tmp->on_adpool_vector()=1;
          }
          found_pool_flag=1;
          break;
        }
      }
      if (!found_pool_flag)
      {
        cerr << "coudn't find right sized pool -- this can't happen"
             << endl;
        ad_exit(1);
      }
    }
  }

  df1b2_gradlist::set_yes_derivatives();
  //local_init_df1b2variable x(xu,xpudot), y(yu,ypudot);

  local_init_pass1_df1b2variable x(xu,xudot);
  local_init_pass1_df1b2variable y(yu,yudot);

  //local_init_pass1_var::allocate_all();
  local_init_pass1_var::set_dot_all();

  //local_dep_df1b2variable z(zudot,zpudot);
  local_dep_df1b2variable z;


  z=square(x+2.0*y+2.5);

  df1b2_gradlist::set_no_derivatives();

  set_dependent_variable(z);
  df1b2variable::passnumber=1;
  df1b2_gradcalc1();
  df1b2variable::restore_adpool_pointer();
  f1b2gradlist=globalf1b2gradlist;

  double * zprime=z.get_u_dot();   // size nvp
  double * pxubar=px->get_u_bar();
  double * pyubar=py->get_u_bar();
  double * pzubar=pz->get_u_bar();
  double * xudotbar=px->get_u_dot_bar();
  double * yudotbar=py->get_u_dot_bar();
  double * pzudotbar=pz->get_u_dot_bar();

  //double zdottmp[100];
  {
    for (int i=0;i<nvx;i++)
    {
      //zdottmp[i] = zprime[0] * xudot[i] + zprime[1] * yudot[i];
     // pzubar[0]+=xudot[i]*pzudotbar[i];
     // pzubar[1]+=xudot[i]*pzudotbar[i];
      xudotbar[i]+=zprime[0]*pzudotbar[i];
      yudotbar[i]+=zprime[1]*pzudotbar[i];

      pxubar[i]+=(x.u_bar[0]*xudot[i]+x.u_bar[1]*yudot[i])*pzudotbar[i];
      pyubar[i]+=(y.u_bar[0]*xudot[i]+y.u_bar[1]*yudot[i])*pzudotbar[i];

      pxubar[i]+=zprime[0]*pzubar[i];
      pyubar[i]+=zprime[1]*pzubar[i];
    }
  }
}

void read_xxx_2(void);
void read_xxx_3(void){;}

/**
 * Description not yet available.
 * \param
 */
void ad_read_xxx(void)
{
  switch(df1b2variable::passnumber)
  {
  case 1:
    read_xxx_1();
    break;
  case 2:
    read_xxx_2();
    break;
  case 3:
    read_xxx_3();
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
void read_xxx_2(void)
{
  // We are going backword for bptr and forward for bptr2
  // the current entry+2 in bptr is the size of the record i.e
  // points to the next record
  int nvar=df1b2variable::nvar;
  //fixed_smartlist & nlist=f1b2gradlist->nlist;
  test_smartlist& list=f1b2gradlist->list;
  int total_bytes=3*sizeof(df1b2_header)
    +2*(nvar+1)*sizeof(double);
  //int num_bytes=nlist.bptr->numbytes;
  f1b2gradlist->list.check_buffer_size(total_bytes);
  list.saveposition(); // save pointer to beginning of record;
  // save the pointer to the beginning of the record
#if defined(SAFE_ARRAYS)
  checkidentiferstring("DL",list);
#endif
  //df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  //df1b2_header * py=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  //df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  //double xu,xpu,yu,ypu,zu,zpu;
  double xu,yu,zu;
  memcpy(&xu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);

  memcpy(&yu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);

  memcpy(&zu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);

  int nvx;
  int nap;
  double *xudot,*yudot,*zudot;
  memcpy(&nvx,list.bptr,sizeof(int));
  list.bptr+=sizeof(int);
  memcpy(&nap,list.bptr,sizeof(int));
  list.bptr+=sizeof(int);
  xudot = (double*) list.bptr;
  list.bptr+=nvx*sizeof(double);
  yudot = (double*) list.bptr;
  list.bptr+=nvx*sizeof(double);
  zudot = (double*) list.bptr;
  list.bptr+=nvx*sizeof(double);
#if defined(SAFE_ARRAYS)
  checkidentiferstring("EL",list);
#endif
  xxx(xudot,yudot);
  xxx(zudot,yudot);

  list.restoreposition(); // save pointer to beginning of record;

  f1b2gradlist=localf1b2gradlist;
  f1b2gradlist->reset();
  df1b2variable::save_adpool_pointer();


  adpool * tmppool=df1b2variable::pool;
  if (tmppool)
  {
    //cout << tmppool << endl;
    // check if current pool is the right size
    if (tmppool->nvar != nap)
    {
      // check sizes of other pools
      int found_pool_flag=0;
      for (int i=0;i<df1b2variable::adpool_counter;i++)
      {
        if (df1b2variable::adpool_vector[i]->nvar == nap)
        {
          adpool * tmp = df1b2variable::pool;
          df1b2variable::pool=df1b2variable::adpool_vector[i];
          df1b2variable::nvar=nap;
          if (!tmp->on_adpool_vector())
          {
            df1b2variable::adpool_vector[df1b2variable::adpool_counter]=tmp;
            df1b2variable::nvar_vector[df1b2variable::adpool_counter]=
              tmp->nvar;
            //df1b2variable::adpool_counter++;
            df1b2variable::increment_adpool_counter();
            tmp->on_adpool_vector()=1;
          }
          found_pool_flag=1;
          break;
        }
      }
      if (!found_pool_flag)
      {
        cerr << "coudn't find right sized pool -- this can't happen"
             << endl;
        ad_exit(1);
      }
    }
  }

  df1b2_gradlist::set_yes_derivatives();
  //local_init_df1b2variable x(xu,xpudot), y(yu,ypudot);

  local_init_pass1_df1b2variable x(xu,xudot);
  local_init_pass1_df1b2variable y(yu,yudot);

  //local_init_pass1_var::allocate_all();
  local_init_pass1_var::set_dot_all();

  //local_dep_df1b2variable z(zudot,zpudot);
  local_dep_df1b2variable z;


  z=square(x+2.0*y+2.5);

  df1b2_gradlist::set_no_derivatives();

  set_dependent_variable(z);
  df1b2variable::passnumber=1;
  df1b2_gradcalc1();

  x.get_u_bar_tilde()[0]=1;
  x.get_u_bar_tilde()[1]=0;
  y.get_u_bar_tilde()[0]=0;
  y.get_u_bar_tilde()[1]=0;

  df1b2variable::passnumber=2;
  df1b2_gradcalc1();

  df1b2variable::passnumber=3;
  df1b2_gradcalc1();

  x.get_u_bar_tilde()[0]=0;
  x.get_u_bar_tilde()[1]=1;
  y.get_u_bar_tilde()[0]=0;
  y.get_u_bar_tilde()[1]=0;

  df1b2variable::passnumber=2;
  df1b2_gradcalc1();

  df1b2variable::passnumber=3;
  df1b2_gradcalc1();
}
