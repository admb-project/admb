/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"
#include <d4arr.hpp>
 d4_array::d4_array(int nrl,int nrh)
 {
   allocate(nrl,nrh);
 }


four_array_shape::four_array_shape(int hsl,int hsu) //,int sl,int su,int rl,
 // int ru,int cl,int cu)
{
  hslice_min=hsl;
  hslice_max=hsu;
  //slice_min=sl;
  //slice_max=su;
  //row_min=rl;
  //row_max=ru;
  //col_min=cl;
  //col_max=cu;
  ncopies=0;
}

double sum(_CONST d4_array& m)
{
  double tmp=0.;
  for (int i=m.indexmin();i<=m.indexmax();i++)
  {
    tmp+=sum(m.elem(i));
  }
  return tmp;
}
    
 d4_array d4_array::sub(int nrl,int nrh)
 {
   if (allocated(*this))
   {
     d4_array tmp(nrl,nrh);
     for (int i=nrl; i<=nrh; i++)
     {
       tmp[i].shallow_copy((*this)(i));
     }
     return tmp;
   }
   else
   {
     return *this;
   }
 }

 d4_array::d4_array(const d4_array& m2)
 {
   if (m2.shape)
   {
     shape=m2.shape;
     (shape->ncopies)++;
     t = m2.t;
   }
   else
   {
     shape=NULL;
     t=NULL;
   }
 }

 void d4_array::shallow_copy(const d4_array& m2)
 {
   if (m2.shape)
   {
     shape=m2.shape;
     (shape->ncopies)++;
     t = m2.t;
   }
   else
   {
     shape=NULL;
     t=NULL;
   }
 }

 void d4_array::deallocate()
 {
   if (shape)
   {
     if (shape->ncopies)
     {
       (shape->ncopies)--;
     }
     else
     {
       t += hslicemin();
       delete [] t;
       delete shape;
     }
   }
   else
   { 
#    if defined(SAFE_ALL)
   //  cerr << "Warning -- trying to deallocate an unallocated d4_array"<<endl;
#    endif 
   }
 }

 d4_array::~d4_array() 
 {
   deallocate();
 }

 d4_array& d4_array::operator =  (_CONST d4_array& m)
 {
   int mmin=hslicemin();
   int mmax=hslicemax();
   if (mmin!=m.hslicemin() || mmax!=m.hslicemax())
   { 
     cerr << "Incompatible bounds in"
      " d4_array& d4_array:: operator =  (_CONST d4_array& m)"
      << endl;
     ad_exit(1);
    }
   for (int i=mmin; i<=mmax; i++)
   {
     (*this)(i)=m(i);
   }
   return *this;
 }

 void d4_array::allocate(_CONST d4_array& m1)
 {
   if ( (shape=new four_array_shape(m1.hslicemin(),m1.hslicemax()))
       == 0)
   {
     cerr << " Error allocating memory in dvar4_array contructor" << endl;
   }
   int ss=hslicesize();
   if ( (t = new d3_array[ss]) == 0)
   {
     cerr << " Error allocating memory in dvar4_array contructor" << endl;
     ad_exit(21);
   }
   t -= hslicemin();
   for (int i=hslicemin(); i<=hslicemax(); i++)
   {
     t[i].allocate(m1[i]);
   }
 }

  #ifndef OPT_LIB

    d3_array& d4_array::operator ( ) (int i)
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "d3_array& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }

    d3_array& d4_array::operator [] (int i)
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "d3_array& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }


    dmatrix& d4_array::operator ( ) (int i ,int j)
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "dmatrix& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return ((*this)(i))(j);
    }
    dvector& d4_array::operator ( ) (int i,int j,int k)
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
	    "dvector& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return (((*this)(i,j))(k));
    }
    double& d4_array::operator ( ) (int i,int j,int k,int l)
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "double& d4_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return ( ((*this)(i,j,k))(l));
    }

   #ifdef USE_CONST

    _CONST d3_array& d4_array::operator ( ) (int i) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "d3_array& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }

    _CONST d3_array& d4_array::operator [] (int i) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "d3_array& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return t[i];
    }


    _CONST dmatrix& d4_array::operator ( ) (int i ,int j) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "dmatrix& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return ((*this)(i))(j);
    }

    _CONST dvector& d4_array::operator ( ) (int i,int j,int k) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
	    "dvector& d4_array::operator ( )" << endl;
          ad_exit(1);
        }
      #endif
      return (((*this)(i,j))(k));
    }

    _CONST double& d4_array::operator ( ) (int i,int j,int k,int l) _CONST
    {
      #ifdef SAFE_ARRAYS
        if (i<hslicemin()||i>hslicemax())
        { cerr << "Error hslice index out of bounds in\n"
            "double& d4_array::operator ( )"  << endl;
          ad_exit(1);
        }
      #endif
      return ( ((*this)(i,j,k))(l));
    }

   #endif
  #endif



void d4_array::allocate(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch)
 {
   if ( (shape=new four_array_shape(hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor\n";
     ad_exit(21);
   }
   int ss=hslicesize();
   if ( (t = new d3_array[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor\n";
     ad_exit(21);
   }
   t -= hslicemin();
   for (int i=hsl; i<=hsu; i++)
   {
     (*this)(i).allocate(sl,sh,nrl,nrh,ncl,nch);
   }
 }

 void d4_array::allocate(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,_CONST ivector& ncl,_CONST ivector& nch)
 {
   if ( (shape=new four_array_shape (hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in d4_array contructor\n";
   }

   int ss=hslicesize();
   if ( (t = new d3_array[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor\n";
     ad_exit(21);
   }
   t -= hslicemin();
   for (int i=hsl; i<=hsu; i++)
   {
     (*this)(i).allocate(sl,sh,nrl,nrh,ncl,nch);
   }
 }

 void d4_array::allocate(int hsl,int hsu,int sl,int sh,_CONST ivector& nrl,
   _CONST ivector& nrh,_CONST ivector& ncl,_CONST ivector& nch)
 {
   if ( (shape=new four_array_shape(hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in d4_array contructor\n";
   }

   int ss=hslicesize();
   if ( (t = new d3_array[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor\n";
     ad_exit(21);
   }
   t -= hslicemin();
   for (int i=hsl; i<=hsu; i++)
   {
     (*this)(i).allocate(sl,sh,nrl(i),nrh(i),ncl(i),nch(i));
   }
 }

 d4_array::d4_array(int hsl,int hsu,int sl,_CONST ivector& sh,
   int nrl, _CONST imatrix& nrh,int ncl,int nch)
 {
   allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
 }

 void d4_array::allocate(int hsl,int hsu,int sl,_CONST ivector& sh,
   int nrl, _CONST imatrix& nrh,int ncl,int nch)
 {
   int rmin=nrh.rowmin();
   int cmin=nrh(rmin).indexmin();
   if ( (shape=new four_array_shape(hsl,hsu)) == 0)
   {
     cerr << " Error allocating memory in d4_array contructor\n";
   }

   int ss=hslicesize();
   if ( (t = new d3_array[ss]) == 0)
   {
     cerr << " Error allocating memory in d3_array contructor\n";
     ad_exit(21);
   }
   t -= hslicemin();
   for (int i=hsl; i<=hsu; i++)
   {
     (*this)(i).allocate(sl,sh(i),nrl,nrh(i),ncl,nch);
   }
 }



 d4_array::d4_array(int hsl,int hsu,int sl,int sh,int nrl,
   int nrh,int ncl,int nch)
 {
   allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
 }


 d4_array::d4_array(int hsl,int hsu, int sl,int sh,ivector nrl,ivector nrh,
    ivector ncl,ivector nch)
 {
   allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);

 }

 void d4_array::initialize()
 {
   if (!(!(*this)))  // only initialize allocated objects
   {
     for (int i=hslicemin();i<=hslicemax();i++)
     {
       elem(i).initialize();
     }
   }
 }

d4_array::d4_array(int hsl,int hsu, int sl,_CONST ivector& sh,int nrl,
  _CONST imatrix& nrh,int ncl,_CONST i3_array& nch)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
}


void d4_array::allocate(int hsl,int hsu, int sl,_CONST ivector& sh,int nrl,
  _CONST imatrix& nrh,int ncl,_CONST i3_array& nch)
{
  int rmin=nrh.rowmin();
  int cmin=nrh(rmin).indexmin();
  int sl1=nch.slicemin();
  int rmin1=nch(sl1).rowmin();
  int cmin1=nch(sl1,rmin1).indexmin();
  if ( (shape=new four_array_shape(hsl,hsu)) == 0)
  {
    cerr << " Error allocating memory in d4_array contructor\n";
  }
  int ss=hslicesize();
  if ( (t = new d3_array[ss]) == 0)
  {
    cerr << " Error allocating memory in d3_array contructor\n";
    ad_exit(21);
  }
  t -= hslicemin();
  for (int i=hsl; i<=hsu; i++)
  {
    (*this)(i).allocate(sl,sh(i),nrl,nrh(i),ncl,nch(i));
  }
}
d4_array::d4_array(int hsl,int hsu,const index_type& sl,
    const index_type& sh,const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch)
{
  allocate(hsl,hsu,sl,sh,nrl,nrh,ncl,nch);
}

void d4_array::allocate(ad_integer hsl,ad_integer hsu,const index_type& sl,
    const index_type& sh,const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch)
{
   if (hsl>hsu)
   {
     allocate();
     return;
   }
  int ss=hsu-hsl+1;
  if ( (t = new d3_array[ss]) == 0)
  {
    cerr << " Error allocating memory in d3_array contructor\n";
    ad_exit(21);
  }
  if ( (shape=new four_array_shape(hsl,hsu)) == 0)
  {
    cerr << " Error allocating memory in d3_array contructor\n";
    ad_exit(21);
  }
  t -= int(hsl);
  for (int i=hsl; i<=hsu; i++)
  {
    const index_type& rsl=sl[i];
    const index_type& rsh=sh[i];
    const index_type& rnrl=nrl[i];
    const index_type& rnrh=nrh[i];
    const index_type& rncl=ncl[i];
    const index_type& rnch=nch[i];

    const ad_integer& aa=ad_integer(rsl);
    const ad_integer& bb=ad_integer(rsh);

    (*this)(i).allocate(aa,bb,rnrl,rnrh,rncl,rnch);

    //(*this)(i).allocate(sl[i],sh[i],nrl[i],nrh[i],ncl[i],nch[i]);
  }
}

void d4_array::allocate(int hsl,int hsu,const index_type& sl,
    const index_type& sh,const index_type& nrl,const index_type& nrh,
    const index_type& ncl,const index_type& nch)
{
   if (hsl>hsu)
   {
     allocate();
     return;
   }
  int ss=hsu-hsl+1;
  if ( (t = new d3_array[ss]) == 0)
  {
    cerr << " Error allocating memory in d3_array contructor\n";
    ad_exit(21);
  }
  if ( (shape=new four_array_shape(hsl,hsu)) == 0)
  {
    cerr << " Error allocating memory in d3_array contructor\n";
    ad_exit(21);
  }
  t -= int(hsl);
  for (int i=hsl; i<=hsu; i++)
  {
    const index_type& rsl=sl[i];
    const index_type& rsh=sh[i];
    const index_type& rnrl=nrl[i];
    const index_type& rnrh=nrh[i];
    const index_type& rncl=ncl[i];
    const index_type& rnch=nch[i];

    const ad_integer& aa=ad_integer(rsl);
    const ad_integer& bb=ad_integer(rsh);

    (*this)(i).allocate(aa,bb,rnrl,rnrh,rncl,rnch);

    //(*this)(i).allocate(sl[i],sh[i],nrl[i],nrh[i],ncl[i],nch[i]);
  }
}

void d4_array::allocate(ad_integer hsl,ad_integer hsu,const index_type& sl,
    const index_type& sh,const index_type& nrl,const index_type& nrh)
{
   if (hsl>hsu)
   {
     allocate();
     return;
   }
  int ss=hsu-hsl+1;
  if ( (t = new d3_array[ss]) == 0)
  {
    cerr << " Error allocating memory in d3_array contructor\n";
    ad_exit(21);
  }
  if ( (shape=new four_array_shape(hsl,hsu)) == 0)
  {
    cerr << " Error allocating memory in d3_array contructor\n";
    ad_exit(21);
  }
  t -= int(hsl);
  for (int i=hsl; i<=hsu; i++)
  {
    const index_type& rsl=sl[i];
    const index_type& rsh=sh[i];
    const index_type& rnrl=nrl[i];
    const index_type& rnrh=nrh[i];
    const ad_integer& aa=ad_integer(rsl);
    const ad_integer& bb=ad_integer(rsh);
    (*this)(i).allocate(aa,bb,rnrl,rnrh);
  }
}

void d4_array::allocate(ad_integer hsl,ad_integer hsu,const index_type& sl,
    const index_type& sh)
{
   if (hsl>hsu)
   {
     allocate();
     return;
   }
  int ss=hsu-hsl+1;
  if ( (t = new d3_array[ss]) == 0)
  {
    cerr << " Error allocating memory in d3_array contructor\n";
    ad_exit(21);
  }
  if ( (shape=new four_array_shape(hsl,hsu)) == 0)
  {
    cerr << " Error allocating memory in d3_array contructor\n";
    ad_exit(21);
  }
  t -= int(hsl);
  for (int i=hsl; i<=hsu; i++)
  {
    const index_type& rsl=sl[i];
    const index_type& rsh=sh[i];
    const ad_integer& aa=ad_integer(rsl);
    const ad_integer& bb=ad_integer(rsh);
    (*this)(i).allocate(aa,bb);
  }
}

void d4_array::allocate(ad_integer hsl,ad_integer hsu)
{
   if (hsl>hsu)
   {
     allocate();
     return;
   }
  int ss=hsu-hsl+1;
  if ( (t = new d3_array[ss]) == 0)
  {
    cerr << " Error allocating memory in d3_array contructor\n";
    ad_exit(21);
  }
  if ( (shape=new four_array_shape(hsl,hsu)) == 0)
  {
    cerr << " Error allocating memory in d3_array contructor\n";
    ad_exit(21);
  }
  t -= int(hsl);
  for (int i=hsl; i<=hsu; i++)
  {
    (*this)(i).allocate();
  }
}


