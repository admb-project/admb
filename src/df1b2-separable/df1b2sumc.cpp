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

/**
 * Description not yet available.
 * \param
 */
  df1b2variable operator + (double x, const df1b2variable& _y)
  {
    ADUNCONST(df1b2variable,y)
    df1b2variable z;
    double * yd=y.get_u_dot();
    double * zd=z.get_u_dot();
    *z.get_u()=x+*y.get_u();
    for (int i=0;i<df1b2variable::nvar;i++)
    {
      *zd++ = *yd++;
    }
    
    // WRITE WHATEVER ON TAPE
    if (!df1b2_gradlist::no_derivatives)
      f1b2gradlist->write_pass1_sum(x,&y,&z);
    return z;
  }

void ad_read_pass2_sumc(void);

/**
 * Description not yet available.
 * \param
 */
 int df1b2_gradlist::write_pass1_sum(double x,const df1b2variable * _py,
   df1b2variable * pz)
 {
   ADUNCONST(df1b2variable*,py)
   ncount++;
#if defined(CHECK_COUNT)
  if (ncount >= ncount_check)
    cout << ncount << endl;
#endif
   //int nvar=df1b2variable::nvar;

   int total_bytes=2*sizeof(df1b2_header);
// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="TU";
  int slen=strlen(ids);
  total_bytes+=slen;
#endif
  list.check_buffer_size(total_bytes);
  void * tmpptr=list.bptr;
#if defined(SAFE_ALL)
  memcpy(list,ids,slen);
#endif
// end of string identifier debug stuff

   memcpy(list,(df1b2_header*)(py),sizeof(df1b2_header));
   memcpy(list,(df1b2_header*)(pz),sizeof(df1b2_header));
   // ***** write  record size
   nlist.bptr->numbytes=adptr_diff(list.bptr,tmpptr);
   nlist.bptr->pf=(ADrfptr)(&ad_read_pass2_sumc);
      ++nlist;
  return 0;
 }


void read_pass2_1_sumc(void);
void read_pass2_2_sumc(void);
void read_pass2_3_sumc(void);

/**
 * Description not yet available.
 * \param
 */
void ad_read_pass2_sumc(void)
{
  switch(df1b2variable::passnumber)
  {
  case 1:
    read_pass2_1_sumc();
    break;
  case 2:
    read_pass2_2_sumc();
    break;
  case 3:
    read_pass2_3_sumc();
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
void read_pass2_1_sumc(void)
{
  // We are going backword for bptr and nbptr
  // and  forward for bptr2 and nbptr2
  // the current entry+2 in bptr is the size of the record i.e
  // points to the next record
  int nvar=df1b2variable::nvar;
  test_smartlist& list=f1b2gradlist->list; 
  int num_bytes=f1b2gradlist->nlist.bptr->numbytes;
  list-=num_bytes;
  list.saveposition(); // save pointer to beginning of record;

  // get info from tape1
#if defined(SAFE_ARRAYS)
  checkidentiferstring("TU",f1b2gradlist->list);
#endif
  char * bptr=f1b2gradlist->list.bptr;
  df1b2_header * py=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) bptr;

  list.restoreposition(); // save pointer to beginning of record;
 
  // ****************************************************************
  // turn this off if no third derivatives are calculated
  // if (!no_third_derivatives)
  // {
  // save for second reverse pass
  // save identifier 1

  int i;
  for (i=0;i<nvar;i++)
  {
    py->u_bar[i]+=pz->u_bar[i];
  }
  for (i=0;i<nvar;i++)
  {
    py->u_dot_bar[i]+=pz->u_dot_bar[i];
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
void read_pass2_2_sumc(void)
{
  //const int nlist_record_size=sizeof(int)+sizeof(char*);
  // We are going forward for bptr and backword for bptr2
  //
  // list 1
  //
  int nvar=df1b2variable::nvar;
  test_smartlist & list=f1b2gradlist->list; 

  int total_bytes=2*sizeof(df1b2_header);
// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="BY";
  int slen=strlen(ids);
  total_bytes+=slen;
#endif
  list.check_buffer_size(total_bytes);
// end of string identifier debug stuff

  list.saveposition(); // save pointer to beginning of record;
  fixed_smartlist & nlist=f1b2gradlist->nlist; 
  // get record size
  int num_bytes=nlist.bptr->numbytes;
  // get info from tape1
#if defined(SAFE_ARRAYS)
  checkidentiferstring("TU",list);
#endif
  df1b2_header * py=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.restoreposition(num_bytes); // save pointer to beginning of record;
  
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
    z_bar_tilde[i]+=y_bar_tilde[i];
  }

  for (i=0;i<nvar;i++)
  {
    z_dot_bar_tilde[i]+=y_dot_bar_tilde[i];
  }
}

/**
 * Description not yet available.
 * \param
 */
void read_pass2_3_sumc(void)
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
  //df1b2_header x,z;

  // get info from tape1
  // get info from tape1
#if defined(SAFE_ARRAYS)
  checkidentiferstring("TU",list);
#endif
  df1b2_header * py=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;

  list.restoreposition(); // save pointer to beginning of record;
  int i;
  
  *(py->u_tilde)+=*(pz->u_tilde);
  for (i=0;i<nvar;i++)
  {
    py->u_dot_tilde[i]+=pz->u_dot_tilde[i];
  }
  *(pz->u_tilde)=0;
  for (i=0;i<nvar;i++)
  {
    pz->u_dot_tilde[i]=0;
  }
}
