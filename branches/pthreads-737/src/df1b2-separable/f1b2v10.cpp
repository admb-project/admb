/*
 * $Id: f1b2v10.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier and Mollie Brooks
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
df1b2vector pow(const df1b2vector& _v,double x)
{
  ADUNCONST(df1b2vector,v);
  //check_shape(x,M,"operator *");
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++) tmp(i)=pow(v(i),x);
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const  df1b2vector& _x,const df1b2vector& _v)
{
  ADUNCONST(df1b2vector,x);
  ADUNCONST(df1b2vector,v);
  //check_shape(x,M,"operator *");
  //check_shape(x,M,"operator *");
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++) tmp(i)=pow(x(i),v(i));
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const df1b2vector& _v,const df1b2variable & _x)
{
  ADUNCONST(df1b2vector,v);
  ADUNCONST(df1b2variable,x);
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=pow(v(i),x);
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const df1b2variable & _v,const df1b2vector& _x)
{
  ADUNCONST(df1b2variable,v);
  ADUNCONST(df1b2vector,x);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=pow(v,x(i));
  }
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
df1b2vector pow(const double v,const df1b2vector& _x)
{
  ADUNCONST(df1b2vector,x);
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  df1b2vector tmp;
  tmp.noallocate(mmin,mmax);
  for (int i=mmin;i<=mmax;i++)
  {
    tmp(i)=pow(v,x(i));
  }
  return tmp;
}
/**
 \brief raise x to the power a.
 \param x vector of bases
 \param a the exponent	
 */
df1b2vector pow(const dvector& x,  const df1b2variable& a)
{
    RETURN_ARRAYS_INCREMENT();	
	df1b2vector y(x.indexmin(), x.indexmax());
	
	for(int i=x.indexmin(); i<=x.indexmax(); i++)
	{
		y(i)=pow(x(i),a);
	}	

	RETURN_ARRAYS_DECREMENT();	
    return(y);
}
/**
 \brief raise x to the power a.
 \param x vector of bases
 \param a vector of exponents	
 */
df1b2vector pow(const dvector& x,  const df1b2vector& a)
{
    RETURN_ARRAYS_INCREMENT();	
	df1b2vector y(x.indexmin(), x.indexmax());

	for(int i=x.indexmin(); i<=x.indexmax(); i++)
	{
		y(i)=pow(x(i),a(i));
	}	

	RETURN_ARRAYS_DECREMENT();	
    return(y);
}
/**
 * Description not yet available.
 * \param
 */
df1b2variable operator * (const df1b2vector& _x,const df1b2vector& _y)
{
  ADUNCONST(df1b2vector,x)
  ADUNCONST(df1b2vector,y)
  df1b2variable tmp=0.0;
  int mmin=x.indexmin();
  int mmax=x.indexmax();
  int i;
  for (i=mmin;i<=mmax;i++)
  {
    *tmp.get_u() += *x(i).get_u() *  *y(i).get_u();
  }
  double * zd=tmp.get_u_dot();
  for (int j=0;j<df1b2variable::nvar;j++)
  {
    *zd++ = 0;
  }
  for (i=mmin;i<=mmax;i++)
  {
    double * zd=tmp.get_u_dot();
    double * xd=x(i).get_u_dot();
    double * yd=y(i).get_u_dot();
    double xu= *x(i).get_u();
    double yu= *y(i).get_u();
  
    for (int j=0;j<df1b2variable::nvar;j++)
    {
      *zd++ += yu * *xd++ + xu * *yd++;
    }
  }
  // WRITE WHATEVER ON TAPE
  if (!df1b2_gradlist::no_derivatives)
    f1b2gradlist->write_pass1_prod(&x,&y,&tmp);
    

  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
void ad_read_pass2_prod_vector(void);

 int df1b2_gradlist::write_pass1_prod(const df1b2vector * _px, 
   const df1b2vector * _py,df1b2variable * pz)
 {
   ADUNCONST(df1b2vector*,px)
   ADUNCONST(df1b2vector*,py)
   ncount++;
#if defined(CHECK_COUNT)
  if (ncount >= ncount_check)
    cout << ncount << endl;
#endif
   int nvar=df1b2variable::nvar;

   int mmin=px->indexmin();
   int mmax=px->indexmax();

   //int total_bytes=3*sizeof(df1b2_header)
    // +2*(nvar+1)*sizeof(double);
   int total_bytes= 2*sizeof(int) + 2*(mmax-mmin+1)*sizeof(df1b2_header)
    + sizeof(df1b2_header) + 2*(mmax-mmin+1)*sizeof(double)
    + 2*(mmax-mmin+1)*nvar*sizeof(double);
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

   int i;
   memcpy(list,&mmin,sizeof(int));
   memcpy(list,&mmax,sizeof(int));
   for (i=mmin;i<=mmax;i++)
   {
     memcpy(list,(df1b2_header*)( &(*px)(i)  ),sizeof(df1b2_header));
     memcpy(list,(df1b2_header*)( &(*py)(i)  ),sizeof(df1b2_header));
   }
   memcpy(list,(df1b2_header*)(pz),sizeof(df1b2_header));


   for (i=mmin;i<=mmax;i++)
   {
     memcpy(list,(*px)(i).get_u(),sizeof(double));
     memcpy(list,(*py)(i).get_u(),sizeof(double));
   }
   for (i=mmin;i<=mmax;i++)
   {
     memcpy(list,(*px)(i).get_u_dot(),nvar*sizeof(double));
     memcpy(list,(*py)(i).get_u_dot(),nvar*sizeof(double));
   }
   // ***** write  record size
   nlist.bptr->numbytes=adptr_diff(list.bptr,tmpptr);
   //cout << "XX " << nlist.bptr->numbytes << " " << total_bytes << endl;
   nlist.bptr->pf=(ADrfptr)(&ad_read_pass2_prod_vector);
      ++nlist;
   return 0;
 }



void read_pass2_1_prod_vector(void);
void read_pass2_2_prod_vector(void);
void read_pass2_3_prod_vector(void);

/**
 * Description not yet available.
 * \param
 */
void ad_read_pass2_prod_vector(void)
{
  switch(df1b2variable::passnumber)
  {
  case 1:
    read_pass2_1_prod_vector();
    break;
  case 2:
    read_pass2_2_prod_vector();
    break;
  case 3:
    read_pass2_3_prod_vector();
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
void read_pass2_1_prod_vector(void)
{
  int nvar=df1b2variable::nvar;
  test_smartlist& list=f1b2gradlist->list; 
  int num_bytes=f1b2gradlist->nlist.bptr->numbytes;
  list-=num_bytes;
  list.saveposition(); // save pointer to beginning of record;

#if defined(SAFE_ARRAYS)
  checkidentiferstring("DL",f1b2gradlist->list);
#endif
  char * bptr=f1b2gradlist->list.bptr;
  int& mmin = *(int *) bptr;
  bptr+=sizeof(int);
  int& mmax = *(int *) bptr;
  bptr+=sizeof(int);
  df1b2_header_ptr_vector px(mmin,mmax);
  df1b2_header_ptr_vector py(mmin,mmax);
  double_ptr_vector xdot(mmin,mmax);
  double_ptr_vector ydot(mmin,mmax);
  dvector xu(mmin,mmax);
  dvector yu(mmin,mmax);
  int i;
  for (i=mmin;i<=mmax;i++)
  {
    // df1b2_header *
    px(i)=(df1b2_header *) bptr;
    bptr+=sizeof(df1b2_header);
    // df1b2_header * 
    py(i)=(df1b2_header *) bptr;
    bptr+=sizeof(df1b2_header);
  }
  df1b2_header * pz=(df1b2_header *) bptr;
  bptr+=sizeof(df1b2_header);
  for (i=mmin;i<=mmax;i++)
  {
    memcpy(&(xu(i)),bptr,sizeof(double));
    bptr+=sizeof(double);
    memcpy(&(yu(i)),bptr,sizeof(double));
    bptr+=sizeof(double);
  }
  for (i=mmin;i<=mmax;i++)
  {
    // double * 
    xdot(i)=(double*)bptr;
    bptr+=nvar*sizeof(double);
    // double * 
    ydot(i)=(double*)bptr;
    bptr+=nvar*sizeof(double);
  }

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

  int j;
  // Do first reverse pass calculations
  for (i=mmin;i<=mmax;i++)
  {
    for (j=0;j<nvar;j++)
    {
      px(i)->u_bar[j]+=yu(i)*pz->u_bar[j];
    }
    for (j=0;j<nvar;j++)
    {
      py(i)->u_bar[j]+=xu(i)*pz->u_bar[j];
    }
  }
  
  for (i=mmin;i<=mmax;i++)
  {
    for (j=0;j<nvar;j++)
    {
      px(i)->u_bar[j]+=ydot(i)[j]*pz->u_dot_bar[j];
    }
    
    for (j=0;j<nvar;j++)
    {
      py(i)->u_bar[j]+=xdot(i)[j]*pz->u_dot_bar[j];
    }
    for (j=0;j<nvar;j++)
    {
      px(i)->u_dot_bar[j]+=yu(i)*pz->u_dot_bar[j];
    }
    for (j=0;j<nvar;j++)
    {
      py(i)->u_dot_bar[j]+=xu(i)*pz->u_dot_bar[j];
    }
  }

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  for (j=0;j<nvar;j++)
  {
    pz->u_bar[j]=0;
  }
  for (j=0;j<nvar;j++)
  {
    pz->u_dot_bar[j]=0;
  }
}

/**
 * Description not yet available.
 * \param
 */
void read_pass2_2_prod_vector(void)
{
  //const int nlist_record_size=sizeof(int)+sizeof(char*);
  // We are going forward for bptr and backword for bptr2
  //
  // list 1
  //
  int nvar=df1b2variable::nvar;
  test_smartlist & list=f1b2gradlist->list; 

  //int total_bytes=3*sizeof(df1b2_header)+sizeof(char*)
  //  +2*(nvar+1)*sizeof(double);
  //int total_bytes=3*sizeof(df1b2_header)
  //  +2*(nvar+1)*sizeof(double);
// string identifier debug stuff
#if defined(SAFE_ALL)
  //char ids[]="DL";
  //int slen=strlen(ids);
  //total_bytes+=slen;
#endif
// end of string identifier debug stuff

  fixed_smartlist & nlist=f1b2gradlist->nlist; 
  int total_bytes=nlist.bptr->numbytes;
  list.check_buffer_size(total_bytes);
  list.saveposition(); // save pointer to beginning of record;
  //cout << "YY " << total_bytes <<  endl;
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

  //df1b2_header x,z;
  //df1b2function2 * pf;

  // get info from tape1
  // get info from tape1
#if defined(SAFE_ARRAYS)
  checkidentiferstring("DL",list);
  checkidentiferstring("QK",list2);
#endif
  int mmin = *(int *) list.bptr;
  list.bptr+=sizeof(int);
  int mmax = *(int *) list.bptr;
  list.bptr+=sizeof(int);

  df1b2_header_ptr_vector px(mmin,mmax);
  df1b2_header_ptr_vector py(mmin,mmax);
  double_ptr_vector xdot(mmin,mmax);
  double_ptr_vector ydot(mmin,mmax);
  dvector xu(mmin,mmax);
  dvector yu(mmin,mmax);
  int i;
  int j;

  for (i=mmin;i<=mmax;i++)
  {
    // df1b2_header * //
    px(i)=(df1b2_header *) list.bptr;
    list.bptr+=sizeof(df1b2_header);
    // df1b2_header * 
    py(i)=(df1b2_header *) list.bptr;
    list.bptr+=sizeof(df1b2_header);
  }

  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);

  for (i=mmin;i<=mmax;i++)
  {
    memcpy(&(xu(i)),list.bptr,sizeof(double));
    list.bptr+=sizeof(double);
    memcpy(&(yu(i)),list.bptr,sizeof(double));
    list.bptr+=sizeof(double);
  }
  for (i=mmin;i<=mmax;i++)
  {
    xdot(i)=(double*)list.bptr;
    list.bptr+=nvar*sizeof(double);
    ydot(i)=(double*)list.bptr;
    list.bptr+=nvar*sizeof(double);
  }
  list.restoreposition(total_bytes); // save pointer to beginning of record;
  
  double * zbar;
  double * zdotbar;


  zbar=(double*)list2.bptr;
  zdotbar=(double*)(list2.bptr+nvar*sizeof(double));
  list2.restoreposition(); // save pointer to beginning of record;

  double * z_bar_tilde=pz->get_u_bar_tilde();
  double * z_dot_bar_tilde=pz->get_u_dot_bar_tilde();

  for (j=0;j<nvar;j++)
  {
    z_bar_tilde[j]=0;
    z_dot_bar_tilde[j]=0;
  }
  
  for (i=mmin;i<=mmax;i++)
  {
    double * x_tilde=px(i)->get_u_tilde();
    double * x_dot_tilde=px(i)->get_u_dot_tilde();
    double * x_bar_tilde=px(i)->get_u_bar_tilde();
    double * x_dot_bar_tilde=px(i)->get_u_dot_bar_tilde();
    double * y_tilde=py(i)->get_u_tilde();
    double * y_dot_tilde=py(i)->get_u_dot_tilde();
    double * y_bar_tilde=py(i)->get_u_bar_tilde();
    double * y_dot_bar_tilde=py(i)->get_u_dot_bar_tilde();

    int j;
    
    // start wjth x and add y
    for (j=0;j<nvar;j++)
    {
      z_bar_tilde[j]+=yu(i)*x_bar_tilde[j];
      *y_tilde+=zbar[j]*x_bar_tilde[j];
    }
  
    for (j=0;j<nvar;j++)
    {
      *y_tilde+=zdotbar[j]*x_dot_bar_tilde[j];
      z_dot_bar_tilde[j]+=yu(i)*x_dot_bar_tilde[j];
    }
  
    // start wjth y and add x
    for (j=0;j<nvar;j++)
    {
      *x_tilde+=zbar[j]*y_bar_tilde[j];
      z_bar_tilde[j]+=xu(i)*y_bar_tilde[j];
    }
  
    for (j=0;j<nvar;j++)
    {
      *x_tilde+=zdotbar[j]*y_dot_bar_tilde[j];
      z_dot_bar_tilde[j]+=xu(i)*y_dot_bar_tilde[j];
    }
  
    for (j=0;j<nvar;j++)
    {
      y_dot_tilde[j]+=zdotbar[j]*x_bar_tilde[j];
      z_dot_bar_tilde[j]+=ydot(i)[j]*x_bar_tilde[j];
    }
    for (j=0;j<nvar;j++)
    {
      x_dot_tilde[j]+=zdotbar[j]*y_bar_tilde[j];
      z_dot_bar_tilde[j]+=xdot(i)[j]*y_bar_tilde[j];
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void read_pass2_3_prod_vector(void)
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
  //df1b2function2 * pf;

  // get info from tape1
  // get info from tape1
#if defined(SAFE_ARRAYS)
  checkidentiferstring("DL",list);
#endif
  int& mmin = *(int *) list.bptr;
  list.bptr+=sizeof(int);
  int& mmax = *(int *) list.bptr;
  list.bptr+=sizeof(int);
  df1b2_header_ptr_vector px(mmin,mmax);
  df1b2_header_ptr_vector py(mmin,mmax);
  double_ptr_vector xdot(mmin,mmax);
  double_ptr_vector ydot(mmin,mmax);
  dvector xu(mmin,mmax);
  dvector yu(mmin,mmax);
  int i;
  int j;
  for (i=mmin;i<=mmax;i++)
  {
    // df1b2_header *
    px(i)=(df1b2_header *) list.bptr;
    list.bptr+=sizeof(df1b2_header);
    // df1b2_header * 
    py(i)=(df1b2_header *) list.bptr;
    list.bptr+=sizeof(df1b2_header);
  }
  df1b2_header * pz=(df1b2_header *) list.bptr;
  list.bptr+=sizeof(df1b2_header);
  for (i=mmin;i<=mmax;i++)
  {
    memcpy(&(xu(i)),list.bptr,sizeof(double));
    list.bptr+=sizeof(double);
    memcpy(&(yu(i)),list.bptr,sizeof(double));
    list.bptr+=sizeof(double);
  }
  for (i=mmin;i<=mmax;i++)
  {
    // double * 
    xdot(i)=(double*)list.bptr;
    list.bptr+=nvar*sizeof(double);
    // double * 
    ydot(i)=(double*)list.bptr;
    list.bptr+=nvar*sizeof(double);
  }

  list.restoreposition(); // save pointer to beginning of record;
  
  for (i=mmin;i<=mmax;i++)
  {
    *(px(i)->u_tilde)+=yu(i) * *(pz->u_tilde);
    *(py(i)->u_tilde)+=xu(i) * *(pz->u_tilde);
    for (j=0;j<nvar;j++)
    {
      *(py(i)->u_tilde)+=xdot(i)[j]*pz->u_dot_tilde[j];
      *(px(i)->u_tilde)+=ydot(i)[j]*pz->u_dot_tilde[j];
    }
    for (j=0;j<nvar;j++)
    {
      px(i)->u_dot_tilde[j]+=yu(i)*pz->u_dot_tilde[j];
      py(i)->u_dot_tilde[j]+=xu(i)*pz->u_dot_tilde[j];
    }
  }
  *(pz->u_tilde)=0;
  for (j=0;j<nvar;j++)
  {
    pz->u_dot_tilde[j]=0;
  }
}
