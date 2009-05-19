/**
 * $Id$
 * 
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California
 */

#include <admodel.h>

  int * smart_counter::get_ncopies(void) 
  { 
    return ncopies;
  }
  smart_counter::smart_counter(void) 
  { 
    ncopies=new int; 
    *ncopies=0; 
  }
  smart_counter::smart_counter(const smart_counter & sc) 
  { 
    ncopies=sc.ncopies; 
    (*ncopies)++;
  }
  smart_counter::~smart_counter(void) 
  { 
    if (*ncopies==0) 
    {
      delete ncopies;
      ncopies=0;
    }
    else
    {
      (*ncopies)--;
    }
  }

  ad_integer::ad_integer(const index_type& it) : d(it.integer()) {}

  index_guts * matrix_index::operator [] (int i)
  {
    return new vector_index(imatrix::operator [](i));
  }
 
  int index_type::integer(void) const
  {
    return int(*p);
  }
  /*
  index_type::index_type(const data_int& x)
  {
    p = new number_index(int(data_int(x)));
  }
   */
  index_type::index_type(const index_type & it) : smart_counter(it)
  {
    p = it.p;
  }

  index_type::index_type(int x)
  {
    p = new number_index(x);
  }
  index_type::index_type(BOR_CONST ivector& x)
  {
    p = new vector_index((BOR_CONST ivector&)(x));
  }
  index_type::index_type(BOR_CONST imatrix& x)
  {
    p = new matrix_index((BOR_CONST imatrix&)(x));
  }
  
  matrix_index::~matrix_index()
  {
    //cout << "in ~matrix_index()" << endl;
  }

  index_type::index_type(BOR_CONST  i3_array& x)
  {
    p = new i3_index((i3_array&)(x));
  }
  index_type::index_type(BOR_CONST  i4_array& x)
  {
    p = new i4_index((i4_array&)(x));
  }
  index_type::index_type(BOR_CONST pre_index_type& pit)
  { 
    p = (*(*(pit.a)).p)[pit.i];
  // Dave uncommented this august 1998 because program crashed
   // (*p->ncopies)++;
  }

  index_type index_type::operator [] (int i) const 
  { 
    return pre_index_type(this,i);
  }
  index_type index_type::operator () (int i) const 
  { 
    return pre_index_type(this,i);
  }
  index_type index_type::operator [] (int i) 
  { 
    return pre_index_type(this,i);
  }
  index_type index_type::operator () (int i) 
  { 
    return pre_index_type(this,i);
  }

  vector_index::~vector_index() {}

  index_type::~index_type () 
  { 
    if (*get_ncopies()==0)
    {
      if (!p)
      {
        cerr << "trying to delete a NULL optr in ~index_type()"  << endl;
      }
      else
      {
        if (!(*(p->ncopies)))
        { 
          delete p; 
          p = NULL;
        }
        else
        {
          (*(p->ncopies))--;
        }
      }
    }
  }

 dmatrix::dmatrix(const ad_integer& nrl,const ad_integer& nrh,
   const index_type& ncl,const index_type& nch)
 {
   allocate(nrl,nrh,ncl,nch);
 }

 void dmatrix::allocate(const ad_integer& nrl,const ad_integer& nrh,
   const index_type& ncl,const index_type& nch)
 {
   if (nrh<nrl)
   {
     allocate();
     return;
   }

   if ( (ncl.isinteger() && (nrl !=ncl.indexmin() || nrh !=ncl.indexmax())) ||
     (nch.isinteger() && (nrl !=nch.indexmin() || nrh !=nch.indexmax())))
   {
     cerr << "Incompatible array bounds in dmatrix(int nrl,int nrh,"
      "_CONST ivector& ncl,_CONST ivector& nch)" << endl;
     ad_exit(1);
   }
   index_min=int(nrl);
   index_max=int(nrh);

   int rs=rowsize();
   if ( (m = new dvector [rs]) == 0)
   {
     cerr << " Error allocating memory in dmatrix contructor" << endl;
     ad_exit(21);
   }
   if ( (shape = new mat_shapex(m))== 0)
   {
     cerr << " Error allocating memory in dmatrix contructor" << endl;
     ad_exit(21);
   }
   m -= int(nrl);
   for (int i=nrl; i<=nrh; i++)
   {
     m[i].allocate(ncl[i],nch[i]);
   }
 }

 d3_array::d3_array(const ad_integer& sl,const ad_integer& sh,
   const index_type& nrl,const index_type& nrh,
   const index_type& ncl,const index_type& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }


 i3_array::i3_array(int sl,int sh,const index_type& nrl,const index_type& nrh,
   const index_type& ncl,const index_type& nch)
 {
   allocate(sl,sh,nrl,nrh,ncl,nch);
 }

 void i3_array::allocate(int sl,int sh,const index_type& nrl,
  const index_type& nrh,const index_type& ncl,const index_type& nch)
 {

   if (sl>sh)
   {
     allocate();
     return;
   }

   int imin=nrh.indexmin();
   //int rmin=nch.rowmin();
   //int cmin=nch(rmin).indexmin();
   if ( (nrl.isinteger() && (sl !=nrl.indexmin() || sh !=nrl.indexmax())) ||
       (nch.isinteger() && (sl !=nch.indexmin() || sh !=nch.indexmax())) ||
       (ncl.isinteger() && (sl !=ncl.indexmin() || sh !=ncl.indexmax())) ||
       (nrh.isinteger() && (sl !=nrh.indexmin() || sh !=nrh.indexmax())) )
   {
     cout << nrl.isinteger() << endl;
     cout << nrl.indexmin() << endl;
     cout << nrl.indexmax() << endl;
     cout << nrh.isinteger() << endl;
     cout << nrh.indexmin() << endl;
     cout << nrh.indexmax() << endl;
     cout << ncl.isinteger() << endl;
     cout << ncl.indexmin() << endl;
     cout << ncl.indexmax() << endl;
     cout << nch.isinteger() << endl;
     cout << nch.indexmin() << endl;
     cout << nch.indexmax() << endl;
     cerr << "Incompatible array bounds in i3_array(int nrl,int nrh,"
      "_CONST index_type& nrl,_CONST index_type& nrh," 
      "_CONST index_type& ncl,_CONST index_type& nch)" << endl;
     cout << sl << " " << nrl.indexmin() << endl
          << sh << " " << nrl.indexmax() << endl
          << sl << " " << nrh.indexmin() << endl
          << sh << " " << nrh.indexmax() << endl
          << sl << " " << ncl.indexmin() << endl
          << sh << " " << ncl.indexmax() << endl
          << sl << " " << nch.indexmin() << endl
          << sh << " " << nch.indexmax() << endl;
           
     ad_exit(1);
   }

   if ( (shape=new three_array_shape(sl,sh)) == 0)
   {
     cerr << " Error allocating memory in i3_array contructor" << endl;
   }
   int ss=slicesize();
   if ( (t = new imatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in i3_array contructor" << endl;
     ad_exit(21);
   }
   t -= slicemin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl(i),nrh(i),ncl(i),nch(i));  
   } 
 }


 void d3_array::allocate(const ad_integer& sl,const ad_integer& sh,
   _CONST index_type& nrl,_CONST index_type& nrh,_CONST index_type& ncl,
   _CONST index_type& nch)
 {
  
   if (int(sl)>int(sh))
   {
     allocate();
     return;
   }

   if ( (nrl.isinteger() && (sl !=nrl.indexmin() || sh !=nrl.indexmax())) ||
       (nrh.isinteger() && (sl !=nrh.indexmin() || sh !=nrh.indexmax())) )
   {
     cerr << "Incompatible array bounds in i3_array(int nrl,int nrh,"
      "_CONST index_type& nrl,_CONST index_type& nrh," 
      "_CONST index_type& ncl,_CONST index_type& nch)" << endl;
     ad_exit(1);
   }

   if ( (shape=new three_array_shape(sl,sh))== 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
   }

   int ss=slicesize();
   if ( (t = new dmatrix[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor" << endl;
     ad_exit(21);
   }
   t -= indexmin();
   for (int i=sl; i<=sh; i++)
   {
     t[i].allocate(nrl[i],nrh[i],ncl[i],nch[i]);
   }
 }


 void imatrix::allocate(const ad_integer& nrl,const ad_integer& nrh,
    const index_type& ncl,const index_type& nch)
 {
   if (nrl>nrh)
   {
     allocate();
     return;
   }
   index_min=nrl;
   index_max=nrh;
   if ( (ncl.isinteger() && (nrl !=ncl.indexmin() || nrh !=ncl.indexmax())) ||
     (nch.isinteger() && (nrl !=nch.indexmin() || nrh !=nch.indexmax())))
   {
     cerr << "Incompatible array bounds in dmatrix(int nrl,int nrh,_CONST ivector& ncl,_CONST ivector& nch)\n";
     ad_exit(1);
   }
   int ss=nrh-nrl+1;
   if ( (m = new ivector [ss]) == 0)
   {
     cerr << " Error allocating memory in imatrix contructor\n";
     ad_exit(21);
   }
   if ( (shape = new mat_shapex(m))== 0)
   {
     cerr << " Error allocating memory in imatrix contructor\n";
     ad_exit(21);
   }
   m -= int(nrl);
   for (int i=nrl; i<=nrh; i++)
   {
     m[i].allocate(ncl(i),nch(i));
   }
 }

index_guts::~index_guts()
{ 
  if (!(*ncopies)) 
  {
    delete ncopies; 
    ncopies=NULL;
  }
}


 dvector::dvector(const ad_integer& ncl,const index_type& nch)
 {
   allocate(ncl,nch);
 }

 void dvector::allocate(const ad_integer& _ncl,const index_type& _nch)
 {
   int ncl=_ncl;
   int nch=ad_integer(_nch);
   int itemp=nch-ncl;
   if (itemp<0)
   {
     allocate();
     return;
   }
   if ( (v = new double [itemp+1]) ==0)
   {
     cerr << " Error trying to allocate memory for dvector\n";
     ad_exit(21);
   }
#if defined(THREAD_SAFE)
   if ( (shape=new ts_vector_shapex(ncl,nch,v)) == NULL)
#else
   if ( (shape=new vector_shapex(ncl,nch,v)) == NULL)
#endif
   {
     cerr << "Error trying to allocate memory for dvector\n";
     ad_exit(1);
   }

   index_min=ncl;
   index_max=nch;
   v -= indexmin();
   #ifdef SAFE_INITIALIZE
     for ( int i=indexmin(); i<=indexmax(); i++)
     {
       v[i]=0.;
     }
   #endif
 }


 ivector::ivector(const ad_integer& ncl,const index_type& nch)
 {
   allocate(ncl,nch);
 }

 void ivector::allocate(const ad_integer& _ncl,const index_type& _nch)
 {
   index_min=_ncl;
   index_max=ad_integer(_nch);
   int itemp=index_max-index_min;
   if (itemp<0)
   {
     allocate();
     return;
   }
   if ( (v = new int [itemp+1]) ==0)
   {
     cerr << " Error trying to allocate memory for dvector\n";
     ad_exit(21);
   }
   if ( (shape=new vector_shapex(index_min,index_max,v)) == NULL)
   {
     cerr << "Error trying to allocate memory for dvector\n";
     ad_exit(1);
   }

   v -= indexmin();
   #ifdef SAFE_INITIALIZE
     for ( int i=indexmin(); i<=indexmax(); i++)
     {
       v[i]=0.;
     }
   #endif
 }

void xxjj(void);

vector_index::vector_index(BOR_CONST ivector& v) : ivector(v)
{
  //xxjj();
}

void xxjj(void){;}

index_guts::index_guts()
{
  ncopies = new int;
  *ncopies=0;
}

index_guts::index_guts(const index_guts& ig)
{
  ncopies = ig.ncopies;
  (*ncopies)++;
}

index_guts * number_index::operator [] (int i)
{
  return new number_index(int(*this));
}
