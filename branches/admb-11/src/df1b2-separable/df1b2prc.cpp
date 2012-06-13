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
  int debugcounter=0;

/*
  df1b2variable operator / (double x,const df1b2variable& y) 
  {
    return x*inv(y);
  }
*/

/**
 * Description not yet available.
 * \param
 */
  df1b2variable operator / (const df1b2variable& x,double y) 
  {
    return x*(1.0/y);
  }

/**
 * Description not yet available.
 * \param
 */
  df1b2variable operator * (double x,const df1b2variable& _y) 
  {
    ADUNCONST(df1b2variable,y)
    df1b2variable z;
    double * yd=y.get_u_dot();
    double * zd=z.get_u_dot();
    double yu=*y.get_u();

    *z.get_u()=x*yu;

    for (int i=0;i<df1b2variable::nvar;i++)
    {
      *zd++ = x * *yd++;
    }
    
    // WRITE WHATEVER ON TAPE
    if (!df1b2_gradlist::no_derivatives)
      f1b2gradlist->write_pass1_prod(x,&y,&z);
    return z;
  }


void ad_read_pass2_prodc1(void);

/**
 * Description not yet available.
 * \param
 */
 int df1b2_gradlist::write_pass1_prod(double x,const df1b2variable * _py,
   df1b2variable * pz)
 {
   ADUNCONST(df1b2variable*,py)
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

   memcpy(list,&x,sizeof(double));
   memcpy(list,(df1b2_header*)(py),sizeof(df1b2_header));
   memcpy(list,(df1b2_header*)(pz),sizeof(df1b2_header));
   memcpy(list,py->get_u(),sizeof(double));
   memcpy(list,py->get_u_dot(),nvar*sizeof(double));
   // ***** write  record size
   nlist.bptr->numbytes=adptr_diff(list.bptr,tmpptr);
   if (total_bytes != nlist.bptr->numbytes)
   {
     cerr << "error in byte calculation in "
       " write_pass1_prod" << endl;
     ad_exit(1);
   }
   nlist.bptr->pf=(ADrfptr)(&ad_read_pass2_prodc1);
      ++nlist;
   return 0;
 }


void read_pass2_1_prodc1(void);
void read_pass2_2_prodc1(void);
void read_pass2_3_prodc1(void);

/**
 * Description not yet available.
 * \param
 */
void ad_read_pass2_prodc1(void)
{
  switch(df1b2variable::passnumber)
  {
  case 1:
    read_pass2_1_prodc1();
    break;
  case 2:
    read_pass2_2_prodc1();
    break;
  case 3:
    read_pass2_3_prodc1();
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
void read_pass2_1_prodc1(void)
{
  //  vmon_begin();
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
  double yu;

  // get info from tape1
#if defined(SAFE_ARRAYS)
  checkidentiferstring("DL",f1b2gradlist->list);
#endif
  char * bptr=f1b2gradlist->list.bptr;
  double xu=*(double *) bptr;
  bptr+=sizeof(double);
  df1b2_header * py=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);
  memcpy(&yu,bptr,sizeof(double));
  bptr+=sizeof(double);
  //double * ydot=(double*)bptr;

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
  /*
  if (debugcounter++>569)
  {
    cout << debugcounter++ << endl;
    memcpy(list2,pz->get_u_bar(),2*nvar*sizeof(double));
    memcpy(list2,pz->get_u_bar(),nvar*sizeof(double));
    memcpy(list2,pz->get_u_dot_bar(),nvar*sizeof(double));
  }
  else
  */
  {
    memcpy(list2,pz->get_u_bar(),nvar*sizeof(double));
    memcpy(list2,pz->get_u_dot_bar(),nvar*sizeof(double));
  }
  *nlist2.bptr=adptr_diff(list2.bptr,tmpptr);
  ++nlist2;

  // Do first reverse pass calculations
  int i;
  for (i=0;i<nvar;i++)
  {
    py->u_bar[i]+=xu*pz->u_bar[i];
  }
  
  for (i=0;i<nvar;i++)
  {
    py->u_dot_bar[i]+=xu*pz->u_dot_bar[i];
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
void read_pass2_2_prodc1(void)
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

  double yu;
  double * ydot;
  //df1b2_header x,z;
  //df1b2function2 * pf;

  // get info from tape1
  // get info from tape1
#if defined(SAFE_ARRAYS)
  checkidentiferstring("DL",list);
  checkidentiferstring("QK",list2);
#endif
  double xu=*(double *) list.bptr;
  list.bptr+=sizeof(double);
  df1b2_header * py=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  //pf=*(df1b2function2 **) list.bptr;
  //list.bptr+=sizeof(char*);
  memcpy(&yu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  ydot=(double*)list.bptr;
  list.restoreposition(num_bytes); // save pointer to beginning of record;
  
  double * zbar;
  double * zdotbar;


  zbar=(double*)list2.bptr;
  zdotbar=(double*)(list2.bptr+nvar*sizeof(double));
  list2.restoreposition(); // save pointer to beginning of record;

  //double * y_tilde=py->get_u_tilde();
  //double * y_dot_tilde=py->get_u_dot_tilde();
  double * y_bar_tilde=py->get_u_bar_tilde();
  double * y_dot_bar_tilde=py->get_u_dot_bar_tilde();
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
    z_bar_tilde[i]+=xu*y_bar_tilde[i];
  }

  for (i=0;i<nvar;i++)
  {
    z_dot_bar_tilde[i]+=xu*y_dot_bar_tilde[i];
  }
}

/**
 * Description not yet available.
 * \param
 */
void read_pass2_3_prodc1(void)
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
  double yu;
  double * ydot;
  //df1b2_header z;
  //df1b2function2 * pf;

  // get info from tape1
  // get info from tape1
#if defined(SAFE_ARRAYS)
  checkidentiferstring("DL",list);
#endif
  double xu=*(double*) list.bptr;
  list.bptr+=sizeof(double);
  df1b2_header * py=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  memcpy(&yu,list.bptr,sizeof(double));
  list.bptr+=sizeof(double);
  ydot=(double*)list.bptr;
  list.restoreposition(); // save pointer to beginning of record;
  int i;
  
  *(py->u_tilde)+=xu* *(pz->u_tilde);
  for (i=0;i<nvar;i++)
  {
    py->u_dot_tilde[i]+=xu*pz->u_dot_tilde[i];
  }
  *(pz->u_tilde)=0;
  for (i=0;i<nvar;i++)
  {
    pz->u_dot_tilde[i]=0;
  }
}
