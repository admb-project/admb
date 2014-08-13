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

/**
 * Description not yet available.
 * \param
 */
  df1b2variable operator * (const df1b2variable& _x, double y)
  {
    ADUNCONST(df1b2variable,x)
    df1b2variable z;
    double * xd=x.get_u_dot();
    double * zd=z.get_u_dot();
    double xu=*x.get_u();

    *z.get_u()=y*xu;

    for (int i=0;i<df1b2variable::nvar;i++)
    {
      *zd++ = y * *xd++;
    }

    // WRITE WHATEVER ON TAPE
    if (!df1b2_gradlist::no_derivatives)
      f1b2gradlist->write_pass1_prod(&x,y,&z);
    return z;
  }

void ad_read_pass2_prodc2(void);

/**
 * Description not yet available.
 * \param
 */
 int df1b2_gradlist::write_pass1_prod(const df1b2variable * _px,double y,
   df1b2variable * pz)
 {
   ADUNCONST(df1b2variable*,px)
   ncount++;
#if defined(CHECK_COUNT)
  if (ncount >= ncount_check)
    cout << ncount << endl;
#endif
   int nvar=df1b2variable::nvar;

   //int total_bytes=3*sizeof(df1b2_header)+sizeof(char*)
   //  +2*(nvar+1)*sizeof(double);
   int total_bytes=2*sizeof(df1b2_header)
     +(nvar+2)*sizeof(double);
// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="DL";
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
   memcpy(list,&y,sizeof(double));
   memcpy(list,(df1b2_header*)(pz),sizeof(df1b2_header));
   memcpy(list,px->get_u(),sizeof(double));
   memcpy(list,px->get_u_dot(),nvar*sizeof(double));
   // ***** write  record size
   nlist.bptr->numbytes=adptr_diff(list.bptr,tmpptr);
   if (total_bytes != nlist.bptr->numbytes)
   {
     cerr << "error in byte calculation in "
       " write_pass1_prod" << endl;
     ad_exit(1);
   }
   nlist.bptr->pf=(ADrfptr)(&ad_read_pass2_prodc2);
      ++nlist;
   return 0;
 }


void read_pass2_1_prodc2(void);
void read_pass2_2_prodc2(void);
void read_pass2_3_prodc2(void);

/**
 * Description not yet available.
 * \param
 */
void ad_read_pass2_prodc2(void)
{
  switch(df1b2variable::passnumber)
  {
  case 1:
    read_pass2_1_prodc2();
    break;
  case 2:
    read_pass2_2_prodc2();
    break;
  case 3:
    read_pass2_3_prodc2();
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
void read_pass2_1_prodc2(void)
{
  // We are going backword for bptr and nbptr
  // and  forward for bptr2 and nbptr2
  // the current entry+2 in bptr is the size of the record i.e
  // points to the next record
  //char * bptr=f1b2gradlist->bptr;
  //char * bptr2=f1b2gradlist2->bptr;
  int nvar=df1b2variable::nvar;
  test_smartlist& list=f1b2gradlist->list;
  //f1b2gradlist->nlist-=sizeof(int);
  int num_bytes=f1b2gradlist->nlist.bptr->numbytes;
  list-=num_bytes;
  list.saveposition(); // save pointer to beginning of record;
  double xu;

  // get info from tape1
#if defined(SAFE_ALL)
  checkidentiferstring("DL",f1b2gradlist->list);
#endif
  char * bptr=f1b2gradlist->list.bptr;
  df1b2_header * px=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);
  double yu=*(double *) bptr;
  bptr+=sizeof(double);
  df1b2_header * pz=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);
  memcpy(&xu,bptr,sizeof(double));
  //bptr+=sizeof(double); double* xdot=(double*)bptr;

  list.restoreposition(); // save pointer to beginning of record;

  // ****************************************************************
  // turn this off if no third derivatives are calculated
  // if (!no_third_derivatives)
  // {
  // save for second reverse pass
  // save identifier 1
     test_smartlist & list2 = f1b2gradlist->list2;


   int total_bytes=2*nvar*sizeof(double);
// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="QK";
  int slen=strlen(ids);
  total_bytes+=slen;
#endif
  list2.check_buffer_size(total_bytes);
  void * tmpptr=list2.bptr;
#if defined(SAFE_ALL)
  memcpy(list2,ids,slen);
#endif

  fixed_smartlist2 & nlist2 = f1b2gradlist->nlist2;
  memcpy(list2,pz->get_u_bar(),nvar*sizeof(double));
  memcpy(list2,pz->get_u_dot_bar(),nvar*sizeof(double));
  *nlist2.bptr=adptr_diff(list2.bptr,tmpptr);
  ++nlist2;

  // Do first reverse pass calculations
  int i;
  for (i=0;i<nvar;i++)
  {
    px->u_bar[i]+=yu*pz->u_bar[i];
  }

  for (i=0;i<nvar;i++)
  {
    px->u_dot_bar[i]+=yu*pz->u_dot_bar[i];
  }

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  for (i=0;i<nvar;i++)
  {
    pz->u_bar[i]=0;
  }
  for (i=0;i<nvar;i++)
  {
    pz->u_dot_bar[i]=0;
  }
}

/**
 * Description not yet available.
 * \param
 */
void read_pass2_2_prodc2(void)
{
  //const int nlist_record_size=sizeof(int)+sizeof(char*);
  // We are going forward for bptr and backword for bptr2
  //
  // list 1
  //
  int nvar=df1b2variable::nvar;
  test_smartlist & list=f1b2gradlist->list;

   int total_bytes=2*sizeof(df1b2_header)
     +(nvar+2)*sizeof(double);
// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="DL";
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

  double xu;
  //df1b2_header x,z;
  //df1b2function2 * pf;

  // get info from tape1
  // get info from tape1
#if defined(SAFE_ALL)
  checkidentiferstring("DL",list);
  checkidentiferstring("QK",list2);
#endif
  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  double yu=*(double *) list.bptr;
  list.bptr+=sizeof(double);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  memcpy(&xu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  //double* xdot=(double*)list.bptr;
  list.restoreposition(num_bytes); // save pointer to beginning of record;

  //double* zbar=(double*)list2.bptr;
  //double* zdotbar=(double*)(list2.bptr+nvar*sizeof(double));

  list2.restoreposition(); // save pointer to beginning of record;

  //double * x_tilde=px->get_u_tilde();
  //double * x_dot_tilde=px->get_u_dot_tilde();
  double * x_bar_tilde=px->get_u_bar_tilde();
  double * x_dot_bar_tilde=px->get_u_dot_bar_tilde();
  double * z_bar_tilde=pz->get_u_bar_tilde();
  double * z_dot_bar_tilde=pz->get_u_dot_bar_tilde();
  // Do second "reverse-reverse" pass calculations

  int i;

  for (i=0;i<nvar;i++)
  {
    z_bar_tilde[i]=0;
    z_dot_bar_tilde[i]=0;
  }

  // start with y and add x
  for (i=0;i<nvar;i++)
  {
    z_bar_tilde[i]+=yu*x_bar_tilde[i];
  }

  for (i=0;i<nvar;i++)
  {
    z_dot_bar_tilde[i]+=yu*x_dot_bar_tilde[i];
  }
}

/**
 * Description not yet available.
 * \param
 */
void read_pass2_3_prodc2(void)
{
  // We are going backword for bptr and forward for bptr2
  // the current entry+2 in bptr is the size of the record i.e
  // points to the next record
  int nvar=df1b2variable::nvar;
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
  //df1b2_header z;
  //df1b2function2 * pf;

  // get info from tape1
  // get info from tape1
#if defined(SAFE_ALL)
  checkidentiferstring("DL",list);
#endif
  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  double yu=*(double*) list.bptr;
  list.bptr+=sizeof(double);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  memcpy(&xu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  //double* xdot=(double*)list.bptr;
  list.restoreposition(); // save pointer to beginning of record;
  int i;

  *(px->u_tilde)+=yu* *(pz->u_tilde);
  for (i=0;i<nvar;i++)
  {
    px->u_dot_tilde[i]+=yu*pz->u_dot_tilde[i];
  }
  *(pz->u_tilde)=0;
  for (i=0;i<nvar;i++)
  {
    pz->u_dot_tilde[i]=0;
  }
}
