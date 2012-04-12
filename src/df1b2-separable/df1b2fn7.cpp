/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <df1b2fun.h>

//#define  ADDEBUG_PRINT 
#if defined(ADDEBUG_PRINT)
    int addebug_count=0;
#endif

void ad_read_write_tilde_values(void);
void read_tilde_values_1(void);
void read_tilde_values_2(void);
void read_tilde_values_3(void);
void zero_it(double * p,int n);

/**
 * Description not yet available.
 * \param
 */
int df1b2_gradlist::write_save_pass2_tilde_values(const df1b2variable * _px) 
{
  ADUNCONST(df1b2variable*, px) 
  ncount++;
#if defined(CHECK_COUNT)
  if (ncount >= ncount_check)
    ncount_checker(ncount,ncount_check);
#endif
  int total_bytes=sizeof(df1b2_header);

#if defined(SAFE_ALL)
  char ids[]="YS";
  int slen=strlen(ids);
  total_bytes+=slen;
#endif
  list.check_buffer_size(total_bytes);
  void * tmpptr=list.bptr;
#if defined(SAFE_ALL)
  memcpy(list,ids,slen);
#endif

  memcpy(list,(df1b2_header*)(px),sizeof(df1b2_header));
  //list.bptr+=sizeof(df1b2_header);
  // ***** write  record size
  nlist.bptr->numbytes=adptr_diff(list.bptr,tmpptr);
  nlist.bptr->pf=(ADrfptr)(&ad_read_write_tilde_values);
  ++nlist;
  return 0;
}

/**
 * Description not yet available.
 * \param
 */
void ad_read_write_tilde_values(void)
{
  switch(df1b2variable::passnumber)
  {
  case 1:
    read_tilde_values_1();
    break;
  case 2:
    read_tilde_values_2();
    break;
  case 3:
    read_tilde_values_3();
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
void read_tilde_values_1(void)
{
  // We are going backword for bptr and nbptr
  // and  forward for bptr2 and nbptr2
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
#if defined(SAFE_ARRAYS)
  checkidentiferstring("YS",list);
#endif
  df1b2_header * px=(df1b2_header *) list.bptr; // we don't need this here
  list.restoreposition(); // save pointer to beginning of record;

  // don't need this here for = since it zeroes this out.
  for (int i=0;i<nvar;i++)
  {
    px->u_bar[i]=0;
    px->u_dot_bar[i]=0;
  }
}

/**
 * Description not yet available.
 * \param
 */
void read_tilde_values_2(void)
{
  //const int nlist_record_size=sizeof(int)+sizeof(char*);
  // We are going forward for bptr and backword for bptr2
  //
  // list 1
  //
  int nvar=df1b2variable::nvar;
  test_smartlist & list=f1b2gradlist->list; 

  int total_bytes=sizeof(df1b2_header);
#if defined(SAFE_ALL)
  char ids[]="YS";
  int slen=strlen(ids);
  total_bytes+=slen;
#endif
  list.check_buffer_size(total_bytes);
  list.saveposition(); // save pointer to beginning of record;
#if defined(SAFE_ARRAYS)
  checkidentiferstring("YS",list);
#endif

  //fixed_smartlist & nlist=f1b2gradlist->nlist; 
   // nlist-=sizeof(int);
  // get record size
  //int num_bytes=nlist.bptr->numbytes;
    // nlist+=nlist_record_size;
  df1b2_header * px=(df1b2_header *) list.bptr; 
  //
  // list 3
  //
  fixed_smartlist2& nlist3=f1b2gradlist->nlist3; 
  test_smartlist& list3=f1b2gradlist->list3; 

  int total_bytes2=(nvar+1)*sizeof(double);
#if defined(SAFE_ALL)
  char ids2[]="WF";
  int slen2=strlen(ids2);
  total_bytes2+=slen2;
#endif
  list3.check_buffer_size(total_bytes2);
  void * tmpptr3=list3.bptr;
#if defined(SAFE_ALL)
  memcpy(list3,ids2,slen);
#endif

  memcpy(list3,px->get_u_tilde(),sizeof(double));
  memcpy(list3,px->get_u_dot_tilde(),nvar*sizeof(double));


  zero_it(px->get_u_bar_tilde(),nvar);
  zero_it(px->get_u_dot_bar_tilde(),nvar);
  zero_it(px->get_u_dot_tilde(),nvar);
  zero_it(px->get_u_tilde(),1);
  *nlist3.bptr=adptr_diff(list3.bptr,tmpptr3);
  list.bptr+=sizeof(df1b2_header);
  ++nlist3;
}

/**
 * Description not yet available.
 * \param
 */
void read_tilde_values_3(void)
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
#if defined(SAFE_ARRAYS)
  checkidentiferstring("YS",list);
#endif
  df1b2_header * px=(df1b2_header *) list.bptr; 
  list.restoreposition(); // save pointer to beginning of record;
  // save the pointer to the beginning of the record
  fixed_smartlist2& nlist3=f1b2gradlist->nlist3; 
  test_smartlist& list3=f1b2gradlist->list3; 
  --nlist3;
  // get record size
  int num_bytes3=*nlist3.bptr;
  // backup the size of the record
  list3-=num_bytes3;
  list3.saveposition(); // save pointer to beginning of record;
#if defined(SAFE_ARRAYS)
  checkidentiferstring("WF",list3);
#endif
  memcpy(px->get_u_tilde(),list3.bptr,sizeof(double));
  list3.bptr+=sizeof(double);
  memcpy(px->get_u_dot_tilde(),list3.bptr,nvar*sizeof(double));
  list3.restoreposition(); // save pointer to beginning of record;
}

/**
 * Description not yet available.
 * \param
 */
void zero_it(double * p,int n)
{
  for (int i=0;i<n;i++) *p++=0.0;
}
