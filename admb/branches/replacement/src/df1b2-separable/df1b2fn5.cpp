/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <df1b2fun.h>
void read_pass1_init_1(void);
void read_pass1_init_2(void);
void read_pass1_init_3(void);

//#define ADDEBUG_PRINT
#if defined(ADDEBUG_PRINT)
  extern int addebug_count;
#endif

void ad_read_pass1_initialize(void);
void df1b2variable::operator = (double d) 
{
  initialize();
  //ptr[blocksize-1]=8219.4;
  get_ind_index()=-1;
  *u=d;
  double * zd=get_u_dot();
  // !!! nov 1 02
  if (!df1b2_gradlist::no_derivatives)
    f1b2gradlist->write_save_pass2_tilde_values(this);
  if (!df1b2_gradlist::no_derivatives)
    f1b2gradlist->write_pass1_initialize(this);
}

df1b2variable::df1b2variable(double d) 
{
  // vectors are all 1,...,nvar
  ptr = (double*) pool->alloc();
  //AD_ALLOCATE(ptr,double,blocksize,df1b2variable) 
  initialize();
  double * block=ptr;
  //block[blocksize-1]=8219.4;
  get_ind_index()=-1;
  ncopies=&(((twointsandptr*)block)->ncopies);
  *ncopies=0;
  u=block+=2;   
  u_dot=block+=1;  // u has size 1
  u_bar=block+=nvar;  // u_dot has size  nvar        
  u_dot_bar=block+=nvar;  // u_bar has size  nvar                     
  u_tilde=block+=nvar; // u_dot_bar has size  nvar  
  u_dot_tilde=block+=1;  // u_tilde has size 1
  u_bar_tilde=block+=nvar; // u_dot_tilde has size nvar
  u_dot_bar_tilde=block+=nvar;  // u_bar_tilde has size nvar
  *u=d;
  if (!df1b2_gradlist::no_derivatives)
    f1b2gradlist->write_pass1_initialize(this);
}

df1b2variable::df1b2variable(void) 
{
  if (!df1b2variable::noallocate)
  {
    allocate();
  }
  else
  {
    ptr=0;
#if defined(SAFE_ALL)
  ncopies=0;
  u=0;  
  u_dot=0;  
  u_bar=0;  
  u_dot_bar=0; 
  u_tilde=0; 
  u_dot_tilde=0;
  u_bar_tilde=0;
  u_dot_bar_tilde=0;
#endif
  }
}

df1b2variable::df1b2variable(const newadkludge* z) 
{
  ptr=0;
#if defined(SAFE_ALL)
  ncopies=0;
  u=0;  
  u_dot=0;  
  u_bar=0;  
  u_dot_bar=0; 
  u_tilde=0; 
  u_dot_tilde=0;
  u_bar_tilde=0;
  u_dot_bar_tilde=0;
#endif
}

void df1b2variable::allocate(void) 
{
  // vectors are all 1,...,nvar
  ptr = (double*) pool->alloc();
  //cout << *(int*)ptr << endl;
  //AD_ALLOCATE(ptr,double,blocksize,df1b2variable) 
  initialize();
  double * block=ptr;
  //block[blocksize-1]=8219.4;
  get_ind_index()=-1;
  ncopies=&(((twointsandptr*)block)->ncopies);
  *ncopies=0;
  u=block+=2;   
  u_dot=block+=1;  // u has size 1
  u_bar=block+=nvar;  // u_dot has size  nvar        
  u_dot_bar=block+=nvar;  // u_bar has size  nvar                     
  u_tilde=block+=nvar; // u_dot_bar has size  nvar  
  u_dot_tilde=block+=1;  // u_tilde has size 1
  u_bar_tilde=block+=nvar; // u_dot_tilde has size nvar
  u_dot_bar_tilde=block+=nvar;  // u_bar_tilde has size nvar
  if (!df1b2_gradlist::no_derivatives)
    f1b2gradlist->write_pass1_initialize(this);
}

df1b2variable::df1b2variable(adkludge1 * adkludgexxx)
{
  // vectors are all 1,...,nvar
  ptr = (double*) pool->alloc();
  //AD_ALLOCATE(ptr,double,blocksize,df1b2variable) 
  initialize();
  double * block=ptr;
  block[blocksize-1]=8219.4;
  get_ind_index()=-1;
  ncopies=&(((twointsandptr*)block)->ncopies);
  *ncopies=0;
  u=block+=2;   
  u_dot=block+=1;  // u has size 1
  u_bar=block+=nvar;  // u_dot has size  nvar        
  u_dot_bar=block+=nvar;  // u_bar has size  nvar                     
  u_tilde=block+=nvar; // u_dot_bar has size  nvar  
  u_dot_tilde=block+=1;  // u_tilde has size 1
  u_bar_tilde=block+=nvar; // u_dot_tilde has size nvar
  u_dot_bar_tilde=block+=nvar;  // u_bar_tilde has size nvar
  //if (!df1b2_gradlist::no_derivatives)
   // f1b2gradlist->write_pass1_initialize(this);
}

//int df1b2_gradlist::write_pass1_initialize(const df1b2variable * px, 
//  df1b2variable * pz)
int df1b2_gradlist::write_pass1_initialize(df1b2variable * pz)
{
  char * pg=0;
  ncount++;
 
#if defined(CHECK_COUNT)
  if (ncount >= ncount_check)
    ncount_checker(ncount,ncount_check);
#endif
  int nvar=df1b2variable::nvar;
  int total_bytes=sizeof(df1b2_header)+sizeof(char *);

// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="AZ";
  int slen=strlen(ids);
  total_bytes+=slen;
#endif
  list.check_buffer_size(total_bytes);
  void * tmpptr=list.bptr;
  
#if defined(SAFE_ALL)
  memcpy(list,ids,slen);
#endif
// end of string identifier debug stuff

  memcpy(list,(df1b2_header*)(pz),sizeof(df1b2_header));
  //list.bptr+=sizeof(df1b2_header);
  // ***************** don't need this ***************
  memcpy(list,&pg,sizeof(char *));
  //*(char**)(list.bptr)=(char*)pg;
  //list.bptr+=sizeof(char*);
  // ***** write  record size
  nlist.bptr->numbytes=adptr_diff(list.bptr,tmpptr);
  nlist.bptr->pf=(ADrfptr)(&ad_read_pass1_initialize);
  ++nlist;
  return 0;
}

void ad_read_pass1_initialize(void)
{
  switch(df1b2variable::passnumber)
  {
  case 1:
    read_pass1_init_1();
    break;
  case 2:
    read_pass1_init_2();
    break;
  case 3:
    read_pass1_init_3();
    break;
  default:
    cerr << "illegal value for df1b2variable::pass = " 
         << df1b2variable::passnumber << endl;
    exit(1);
  }
}

void checkidentiferstring(const char * ids,test_smartlist& list)
{
  int slen=strlen(ids);
  char * s=(char*)list.bptr;
  int ss=strncmp(ids,s,slen);
  if (ss)
  {
    cerr << "Error in string identifer in list value should be " << ids
     << endl << " it appears to be " << s[0] << s[1] << s[2] << s[3] 
     << " ... " << endl;
    ad_exit(1);
  }
  list.bptr+=slen;
}
    
void read_pass1_init_1(void)
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
  df1b2_header z;
  df1b2function1 * pf;

  // get info from tape1
#if defined(SAFE_ARRAYS)
  checkidentiferstring("AZ",list);
#endif
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  pf=*(df1b2function1 **) list.bptr;
  list.bptr+=sizeof(char*);
  list.restoreposition(); // save pointer to beginning of record;
  int i;
  
  // Do first reverse paSS calculations
  // ****************************************************************
  // turn this off if no third derivatives are calculated
  // if (!no_third_derivatives)
  // {
  // save for second reverse pass
  // save identifier 1
     fixed_smartlist2& nlist2=f1b2gradlist->nlist2; 
     test_smartlist& list2=f1b2gradlist->list2; 

     int total_bytes=2*nvar*sizeof(double);

// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="EF";
  int slen=strlen(ids);
  total_bytes+=slen;
#endif
  list2.check_buffer_size(total_bytes);
  void * tmpptr2=list2.bptr;
#if defined(SAFE_ALL)
  memcpy(list2,ids,slen);
#endif

     memcpy(list2,pz->get_u_bar(),nvar*sizeof(double));
     //list2.bptr+=nvar*sizeof(double);
     memcpy(list2,pz->get_u_dot_bar(),nvar*sizeof(double));
     //list2.bptr+=nvar*sizeof(double);
     *nlist2.bptr=adptr_diff(list2.bptr,tmpptr2);
     ++nlist2;
  // }
  //
  // ****************************************************************
 
  // This should *NEVER* be used (I think) 
 /*
  for (i=0;i<nvar;i++)
  {
    pz->u_bar[i]=0;
  }
  for (i=0;i<nvar;i++)
  {
    pz->u_dot_bar[i]=0;
  }
  */
 
}

void read_pass1_init_2(void)
{
  const int nlist_record_size=sizeof(int)+sizeof(char*);
  // We are going forward for bptr and backword for bptr2
  //
  // list 1
  //
  int nvar=df1b2variable::nvar;
  test_smartlist & list=f1b2gradlist->list; 

  int total_bytes=sizeof(df1b2_header)+sizeof(char *);
// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="AZ";
  int slen=strlen(ids);
  total_bytes+=slen;
#endif
// end of string identifier debug stuff
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
  test_smartlist & list2=f1b2gradlist->list2; 
  fixed_smartlist2 & nlist2=f1b2gradlist->nlist2; 
  // get record size
  int num_bytes2=*nlist2.bptr;
  --nlist2;
  // backup the size of the record
  list2-=num_bytes2;
  // save the pointer to the beginning of the record
  // bptr and bptr2 now both point to the beginning of their records

  df1b2_header z;
  df1b2function1 * pf;

  // get info from tape1
  list2.saveposition(); // save pointer to beginning of record;
#if defined(SAFE_ALL)
  checkidentiferstring("AZ",list);
  checkidentiferstring("EF",list2);
#endif
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  pf=*(df1b2function1 **) list.bptr;
  list.bptr+=sizeof(char*);
  list.restoreposition(num_bytes); // save pointer to beginning of record;

  
  double * zbar;
  double * zdotbar;


  zbar=(double*)list2.bptr;
  zdotbar=(double*)(list2.bptr+nvar*sizeof(double));

  list2.restoreposition(); // save pointer to beginning of record;

  double * z_bar_tilde=pz->get_u_bar_tilde();
  double * z_dot_bar_tilde=pz->get_u_dot_bar_tilde();
  // Do second "reverse-reverse" pass calculations
  int i;
 
  // !!!! oct31 02
  
  *pz->get_u_tilde()=0.0;
  for (i=0;i<nvar;i++)
  {
    z_bar_tilde[i]=0;
    z_dot_bar_tilde[i]=0;
  }
  
}

void read_pass1_init_3(void)
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
  df1b2_header z;
  df1b2function1 * pf;

  // get info from tape1
#if defined(SAFE_ALL)
  checkidentiferstring("AZ",list);
#endif
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.restoreposition(); // save pointer to beginning of record;

  int i;
  *(pz->u_tilde)=0;
  for (i=0;i<nvar;i++)
  {
    pz->u_dot_tilde[i]=0;
  }

}

