/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <df1b2fun.h>
void read_pass1_minus_eq_1(void);
void read_pass1_minus_eq_2(void);
void read_pass1_minus_eq_3(void);
//#define ADDEBUG_PRINT
#if defined(ADDEBUG_PRINT)
  extern int addebug_count;
#endif
//#define PRINT_DERS


df1b2variable& df1b2variable::operator -= (const df1b2variable& _x)
{
  ADUNCONST(df1b2variable,x) 
  double * xd=x.get_u_dot();
  double * zd=get_u_dot();
  *get_u()-=*x.get_u();
  for (int i=0;i<df1b2variable::nvar;i++)
  {
    *zd++ -= *xd++;
  }
  
  // WRITE WHATEVER ON TAPE
  //df1b2tape->set_tapeinfo_header(&x,&z,this,xd);
  // save stuff for first reverse pass
  // need &x, &z, this,
  if (!df1b2_gradlist::no_derivatives)
    f1b2gradlist->write_pass1_minuseq(&x,this);
  return *this;
}


void ad_read_pass1_minus_eq(void);

int df1b2_gradlist::write_pass1_minuseq(const df1b2variable * _px, 
  df1b2variable * pz)
{
  ncount++;
#if defined(CHECK_COUNT)
  if (ncount >= ncount_check)
    ncount_checker(ncount,ncount_check);
#endif
  int nvar=df1b2variable::nvar;
  ADUNCONST(df1b2variable*,px) 
  fixed_smartlist & nlist=f1b2gradlist->nlist; 
  test_smartlist& list=f1b2gradlist->list; 

  int total_bytes=sizeof(df1b2_header)+sizeof(df1b2_header);
#if defined(SAFE_ALL)
  char ids[]="LC";
  int slen=strlen(ids);
  total_bytes+=slen;
#endif
  list.check_buffer_size(total_bytes);
  void * tmpptr=list.bptr;
#if defined(SAFE_ALL)
  memcpy(list,ids,slen);
#endif
  
  memcpy(list,(df1b2_header*)(px),sizeof(df1b2_header));
  memcpy(list,(df1b2_header*)(pz),sizeof(df1b2_header));

  // ***** write  record size
  nlist.bptr->numbytes=adptr_diff(list.bptr,tmpptr);
  nlist.bptr->pf=(ADrfptr)(&ad_read_pass1_minus_eq);
  ++nlist;
  return 0;
}

void ad_read_pass1_minus_eq(void)
{
  switch(df1b2variable::passnumber)
  {
  case 1:
    read_pass1_minus_eq_1();
    break;
  case 2:
    read_pass1_minus_eq_2();
    break;
  case 3:
    read_pass1_minus_eq_3();
    break;
  default:
    cerr << "illegal value for df1b2variable::pass = " 
         << df1b2variable::passnumber << endl;
    exit(1);
  }
}

    
void read_pass1_minus_eq_1(void)
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
#if defined(SAFE_ARRAYS)
  checkidentiferstring("LC",list);
#endif

  // get info from tape1
  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;

  list.restoreposition(); // save pointer to beginning of record;
  int i;
  
  // Do first reverse paSS calculations
  // ****************************************************************
  // turn this off if no third derivatives are calculated
  // if (!no_third_derivatives)
  // {
  // save for second reverse pass
  // save identifier 1
  //   fixed_smartlist2& nlist2=f1b2gradlist->nlist2; 
  //   test_smartlist& list2=f1b2gradlist->list2; 
  //int total_bytes=2*nvar*sizeof(double);
// string identifier debug stuff
#if defined(SAFE_ALL)
  //char ids[]="KM";
  //int slen=strlen(ids);
  //total_bytes+=slen;
#endif
  //list2.check_buffer_size(total_bytes);
  //void * tmpptr2=list2.bptr;
#if defined(SAFE_ALL)
  //memcpy(list2,ids,slen);
#endif
     //memcpy(list2,pz->get_u_bar(),nvar*sizeof(double));
     //memcpy(list2,pz->get_u_dot_bar(),nvar*sizeof(double));
     //*nlist2.bptr=adptr_diff(list2.bptr,tmpptr2);
     //nlist2++;
  // }
  //
  // ****************************************************************
 
  for (i=0;i<nvar;i++)
  {
    px->u_bar[i]-=pz->u_bar[i];
  }
  for (i=0;i<nvar;i++)
  {
    px->u_dot_bar[i]-=pz->u_dot_bar[i];
  }
#if defined(PRINT_DERS)
 print_derivatives(px,"x"); 
 print_derivatives(pz,"z"); 
#endif
}

void read_pass1_minus_eq_2(void)
{
  const int nlist_record_size=sizeof(int)+sizeof(char*);
  // We are going forward for bptr and backword for bptr2
  //
  // list 1
  //
  int nvar=df1b2variable::nvar;
  test_smartlist & list=f1b2gradlist->list; 

  int total_bytes=sizeof(df1b2_header)+sizeof(df1b2_header);
#if defined(SAFE_ALL)
  char ids[]="LC";
  int slen=strlen(ids);
  total_bytes+=slen;
#endif
  list.check_buffer_size(total_bytes);

  list.saveposition(); // save pointer to beginning of record;
  fixed_smartlist & nlist=f1b2gradlist->nlist; 
   // nlist-=sizeof(int);
  // get record size
  int num_bytes=nlist.bptr->numbytes;
    // nlist+=nlist_record_size;
  //
  // list 2
  //
  //test_smartlist & list2=f1b2gradlist->list2; 
  //fixed_smartlist2 & nlist2=f1b2gradlist->nlist2; 
  // get record size
  //int num_bytes2=*nlist2.bptr;
  //nlist2--;
  // backup the size of the record
  //list2-=num_bytes2;
  //list2.saveposition(); // save pointer to beginning of record;
  // save the pointer to the beginning of the record
  // bptr and bptr2 now both point to the beginning of their records
#if defined(SAFE_ARRAYS)
  checkidentiferstring("LC",list);
  //checkidentiferstring("KM",list2);
#endif


  // get info from tape1
  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;

  list.restoreposition(num_bytes); // save pointer to beginning of record;


  //double * zbar=(double*)list2.bptr;
  //double * zdotbar=(double*)(list2.bptr+nvar*sizeof(double));

  double * x_bar_tilde=px->get_u_bar_tilde();
  double * x_dot_bar_tilde=px->get_u_dot_bar_tilde();
  double * z_bar_tilde=pz->get_u_bar_tilde();
  double * z_dot_bar_tilde=pz->get_u_dot_bar_tilde();
  // Do second "reverse-reverse" pass calculations
  int i;
  for (i=0;i<nvar;i++)
  {
    z_bar_tilde[i]-=x_bar_tilde[i];
  }

  for (i=0;i<nvar;i++)
  {
    z_dot_bar_tilde[i]-=x_dot_bar_tilde[i];
  }
  //list2.restoreposition(); // save pointer to beginning of record;
#if defined(PRINT_DERS)
 print_derivatives(px,"x"); 
 print_derivatives(pz,"z"); 
#endif
}

void read_pass1_minus_eq_3(void)
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

#if defined(SAFE_ARRAYS)
  checkidentiferstring("LC",list);
#endif
  // get info from tape1
  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;

  list.restoreposition(); // save pointer to beginning of record;
  int i;
  
  // Do first reverse paSS calculations

  *(px->u_tilde)-=*pz->u_tilde;
  for (i=0;i<nvar;i++)
  {
    px->u_dot_tilde[i]-=pz->u_dot_tilde[i];
  }
#if defined(PRINT_DERS)
 print_derivatives(px,"x"); 
 print_derivatives(pz,"z"); 
#endif
}

