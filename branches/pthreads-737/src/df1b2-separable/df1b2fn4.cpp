/*
 * $Id: df1b2fn4.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <df1b2fun.h>
void read_pass1_eq_1(void);
void read_pass1_eq_2(void);
void read_pass1_eq_3(void);

//#define ADDEBUG_PRINT
#if defined(ADDEBUG_PRINT)
  extern int addebug_count;
#endif

/**
 * Description not yet available.
 * \param
 */
df1b2variable& df1b2variable::operator = (const df1b2variable& _x)
{
  if (ptr != _x.ptr)
  {
    ADUNCONST(df1b2variable,x)
    if (allocated() )
    {
      //int nc=*ncopies;
      initialize();
      //*ncopies=nc;
      double * xd=x.get_u_dot();
      double * zd=get_u_dot();
      *get_u()=*x.get_u();
      for (int i=0;i<df1b2variable::nvar;i++)
      {
        *zd++ += *xd++;
      }
      
      // WRITE WHATEVER ON TAPE
      //df1b2tape->set_tapeinfo_header(&x,&z,this,xd);
      // save stuff for first reverse pass
      // need &x, &z, this,
    
      // !!! nov 1 02
      // !!! nov 11 02
      if (!df1b2_gradlist::no_derivatives)
        f1b2gradlist->write_save_pass2_tilde_values(this);
      if (!df1b2_gradlist::no_derivatives)
        f1b2gradlist->write_pass1_eq(&x,this);
    }
    else  // guts of copy constructor
    {
      if (x.ptr)
      {
        ptr=x.ptr;
        ncopies=x.ncopies;
        (*ncopies)++;
        u=x.u;
        u_dot=x.u_dot;
        u_bar=x.u_bar;         
        u_dot_bar=x.u_dot_bar;
        u_tilde=x.u_tilde;
        u_dot_tilde=x.u_dot_tilde;
        u_bar_tilde=x.u_bar_tilde;
        u_dot_bar_tilde=x.u_dot_bar_tilde;
      }
      else
      {
        ptr=NULL;
        ncopies=NULL;
        u=NULL;
        u_dot=NULL;
        u_bar=NULL;
        u_dot_bar=NULL;
        u_tilde=NULL;
        u_dot_tilde=NULL;
        u_bar_tilde=NULL;
        u_dot_bar_tilde=NULL;
      }
    }
  }
  return *this;
}

void ad_read_pass1_eq(void);

/**
 * Description not yet available.
 * \param
 */
int df1b2_gradlist::write_pass1_eq(const df1b2variable * _px, 
  df1b2variable * pz)
{
  ADUNCONST(df1b2variable*,px)
  //char * pg=0;
  ncount++;
#if defined(CHECK_COUNT)
  if (ncount >= ncount_check)
    ncount_checker(ncount,ncount_check);
#endif
  //int nvar=df1b2variable::nvar;

  int total_bytes=sizeof(df1b2_header)+sizeof(df1b2_header);
// string identifier debug stuff
#if defined(SAFE_ALL)
  char ids[]="GV";
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
  
  nlist.bptr->numbytes=adptr_diff(list.bptr,tmpptr);
  nlist.bptr->pf=(ADrfptr)(&ad_read_pass1_eq);
  ++nlist;
  return 0;
}

/**
 * Description not yet available.
 * \param
 */
void ad_read_pass1_eq(void)
{
  switch(df1b2variable::passnumber)
  {
  case 1:
    read_pass1_eq_1();
    break;
  case 2:
    read_pass1_eq_2();
    break;
  case 3:
    read_pass1_eq_3();
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
void read_pass1_eq_1(void)
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
  checkidentiferstring("GV",list);
#endif

  // get info from tape1
  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
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
#if defined(SAFE_ALL)
  char ids[]="HT";
  int slen=strlen(ids);
  total_bytes+=slen;
#endif
  list2.check_buffer_size(total_bytes);
  void * tmpptr2=list2.bptr;
#if defined(SAFE_ALL)
  memcpy(list2,ids,slen);
#endif


     memcpy(list2,pz->get_u_bar(),nvar*sizeof(double));
     memcpy(list2,pz->get_u_dot_bar(),nvar*sizeof(double));
     *nlist2.bptr=adptr_diff(list2.bptr,tmpptr2);
     ++nlist2;
  // }
  //
  // ****************************************************************
#if defined(PRINT_DERS)
 print_derivatives(" assign ", 1 ,1 ,0, 0,1);
 print_derivatives(pz,"z"); 
 print_derivatives(px,"x"); 
#endif
 
 

  for (i=0;i<nvar;i++)
  {
    px->u_bar[i]+=pz->u_bar[i];
#if defined(ADDEBUG_PRINT)
    addebug_count++;
    if (addebug_count == 49)
    {
      cout << "trap" << endl;
    }
    cout << px->u_bar[i] << " " << pz->u_bar[i] << " " << addebug_count << endl;
#endif
  }
  for (i=0;i<nvar;i++)
  {
    px->u_dot_bar[i]+=pz->u_dot_bar[i];
  }
  for (i=0;i<nvar;i++)
  {
    pz->u_bar[i]=0;
  }
  for (i=0;i<nvar;i++)
  {
    pz->u_dot_bar[i]=0;
  }
#if defined(PRINT_DERS)
 print_derivatives(px,"x"); 
 print_derivatives(pz,"z"); 
#endif
}

/**
 * Description not yet available.
 * \param
 */
void read_pass1_eq_2(void)
{
  //const int nlist_record_size=sizeof(int)+sizeof(char*);
  // We are going forward for bptr and backword for bptr2
  //
  // list 1
  //
  int nvar=df1b2variable::nvar;
  test_smartlist & list=f1b2gradlist->list; 

  int total_bytes=sizeof(df1b2_header)+sizeof(df1b2_header);
#if defined(SAFE_ALL)
  char ids[]="GV";
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
  test_smartlist & list2=f1b2gradlist->list2; 
  fixed_smartlist2 & nlist2=f1b2gradlist->nlist2; 
  // get record size
  int num_bytes2=*nlist2.bptr;
  --nlist2;
  // backup the size of the record
  list2-=num_bytes2;
  list2.saveposition(); // save pointer to beginning of record;
#if defined(SAFE_ARRAYS)
  checkidentiferstring("GV",list);
  checkidentiferstring("HT",list2);
#endif
  // save the pointer to the beginning of the record
  // bptr and bptr2 now both point to the beginning of their records

  // get info from tape1
  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.restoreposition(num_bytes); // save pointer to beginning of record;

  double * zbar;
  double * zdotbar;

  zbar=(double*)list2.bptr;
  zdotbar=(double*)(list2.bptr+nvar*sizeof(double));
  list2.restoreposition(); // save pointer to beginning of record;

  double * x_bar_tilde=px->get_u_bar_tilde();
  double * x_dot_bar_tilde=px->get_u_dot_bar_tilde();
  double * z_bar_tilde=pz->get_u_bar_tilde();
  double * z_dot_bar_tilde=pz->get_u_dot_bar_tilde();
  // Do second "reverse-reverse" pass calculations
#if defined(PRINT_DERS)
 print_derivatives(" assign ", 1 ,1 ,0, 0,1);
 print_derivatives(pz,"z"); 
 print_derivatives(px,"x"); 
#endif
 
  int i;
  for (i=0;i<nvar;i++)
  {
    z_bar_tilde[i]=0;
    z_dot_bar_tilde[i]=0;
  }
  for (i=0;i<nvar;i++)
  {
    z_bar_tilde[i]+=x_bar_tilde[i];
  }

  for (i=0;i<nvar;i++)
  {
    z_dot_bar_tilde[i]+=x_dot_bar_tilde[i];
  }
#if defined(PRINT_DERS)
 print_derivatives(px,"x"); 
 print_derivatives(pz,"z"); 
#endif
}

/**
 * Description not yet available.
 * \param
 */
void read_pass1_eq_3(void)
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
  checkidentiferstring("GV",list);
#endif
  // get info from tape1
  df1b2_header * px=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.restoreposition(); // save pointer to beginning of record;
  int i;
  
#if defined(PRINT_DERS)
 print_derivatives(" assign ", 1 ,1 ,0, 0,1);
 print_derivatives(pz,"z"); 
 print_derivatives(px,"x"); 
#endif
 

  *(px->u_tilde)+=*pz->u_tilde;
#if defined(ADDEBUG_PRINT)
    addebug_count++;
    if (addebug_count == 49)
    {
      cout << "trap" << endl;
    }
    cout << *(px->u_tilde) << " " << *(pz->u_tilde) << " " << addebug_count << endl;
#endif
  for (i=0;i<nvar;i++)
  {
    px->u_dot_tilde[i]+=pz->u_dot_tilde[i];
  }
#if defined(PRINT_DERS)
 print_derivatives(px,"x"); 
 print_derivatives(pz,"z"); 
#endif
  *(pz->u_tilde)=0;
  for (i=0;i<nvar;i++)
  {
    pz->u_dot_tilde[i]=0;
  }
}
