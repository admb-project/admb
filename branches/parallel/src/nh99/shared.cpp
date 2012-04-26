/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>
 
#  if defined(USE_SHARE_FLAGS)
  static int integer(const index_type& it)
  {
    return it.integer();
  }

  int initial_params::shared_size_count(void)
  {
    cerr << " Error -- shared_size_count not defined for this class"
         << endl;
    ad_exit(1);
    return 0;
  }

  void initial_params::shared_set_value(const dvar_vector& x,
    const int& ii,const dvariable& pen)
  {
    cerr << " Error -- shared_scaled_set_value_inv not defined for this class"
         << endl;
    ad_exit(1);
  }

  void initial_params::shared_set_value_inv(const dvector& x,const int& ii)
  {
    cerr << " Error -- shared_scaled_set_value_inv not defined for this class"
         << endl;
    ad_exit(1);
  }
  int param_init_matrix::shared_size_count(void)
  {
    if (share_flags->get_current_phase() != current_phase)
    {
      share_flags->get_inv_matrix_shared(current_phase);
    }
    return share_flags->get_maxshare();
  }

  int param_init_vector::shared_size_count(void)
  {
    if (share_flags->get_current_phase() != current_phase)
    {
      share_flags->get_inv_vector_shared(current_phase);
    }
    return share_flags->get_maxshare();
  }

  void param_init_matrix::shared_set_value_inv(const dvector& _x,const int& _ii)
  {
    ADUNCONST(int,ii)
    ADUNCONST(dvector,x)
    index_type& it=*(share_flags->get_invflags());
    //int mmin=share_flags->invflags->indexmin();
    //int mmax=share_flags->invflags->indexmax();
    int mmin=it.indexmin();
    int mmax=it.indexmax();
    int i;
    for (i=mmin;i<=mmax;i++)
    {
      x(ii++)=value((*this)(it(i)(1).integer(),it(i)(2).integer()));
    }
  }

  void param_init_vector::shared_set_value_inv(const dvector& _x,const int& _ii)
  {
    ADUNCONST(int,ii)
    ADUNCONST(dvector,x)
    index_type& it=*(share_flags->get_invflags());
    int mmin=it.indexmin();
    int mmax=it.indexmax();
    int i;
    for (i=mmin;i<=mmax;i++)
    {
      x(ii++)=value((*this)(it(i).integer()));
    }
  }

  void param_init_bounded_matrix::shared_set_value_inv
    (const dvector& _x,const int& _ii)
  {
    ADUNCONST(int,ii)
    ADUNCONST(dvector,x)
    index_type& it=*(share_flags->get_invflags());
    int mmin=it.indexmin();
    int mmax=it.indexmax();
    int i;
    for (i=mmin;i<=mmax;i++)
    {
      x(ii++)=
        boundpin((*this)(it(i)(1).integer(),it(i)(2).integer()),
        minb,maxb);
    }
  }

  void param_init_matrix::shared_set_value(const dvar_vector& _x,
    const int& _ii,const dvariable& pen)
  {
    ADUNCONST(int,ii)
    ADUNCONST(dvar_vector,x)
    int mmin=indexmin();
    int mmax=indexmax();
    int i,j;
    index_type& sf=*(share_flags->get_shareflags());
    index_type& af=*(share_flags->get_activeflags());
    for (i=mmin;i<=mmax;i++)
    {

      int jmin=(*this)(i).indexmin();
      int jmax=(*this)(i).indexmax();
      for (j=jmin;j<=jmax;j++)
      {
        int afvalue=integer(af(i)(j));
        if (afvalue && afvalue<=current_phase)
        {
          int is=sf(i)(j).integer();
          (*this)(i,j)=x(ii+is-1);
        }
      }
    }
    ii+=share_flags->get_maxshare();
  }

  void param_init_vector::shared_set_value(const dvar_vector& _x,
    const int& _ii,const dvariable& pen)
  {
    ADUNCONST(int,ii)
    ADUNCONST(dvar_vector,x)
    int mmin=indexmin();
    int mmax=indexmax();
    int i;
    index_type& sf=*(share_flags->get_shareflags());
    index_type& af=*(share_flags->get_activeflags());
    for (i=mmin;i<=mmax;i++)
    {
      int afvalue=integer(af(i));
      if (afvalue && afvalue<=current_phase)
      {
        int is=sf(i).integer();
        (*this)(i)=x(ii+is-1);
      }
    }
    ii+=share_flags->get_maxshare();
  }

  void param_init_bounded_matrix::shared_set_value(const dvar_vector& _x,
    const int& _ii,const dvariable& pen)
  {
    ADUNCONST(int,ii)
    ADUNCONST(dvar_vector,x)
    int mmin=indexmin();
    int mmax=indexmax();
    int i,j;
    index_type& sf=*(share_flags->get_shareflags());
    index_type& af=*(share_flags->get_activeflags());
    for (i=mmin;i<=mmax;i++)
    {

      int jmin=(*this)(i).indexmin();
      int jmax=(*this)(i).indexmax();
      for (j=jmin;j<=jmax;j++)
      {
        int afvalue=integer(af(i)(j));
        if (afvalue && afvalue<=current_phase)
        {
          int is=sf(i)(j).integer();
          //(*this)(i,j)=x(ii+is-1);
          (*this)(i,j)=boundp(x(ii+is-1),minb,maxb,pen);
        }
      }
    }
    ii+=share_flags->get_maxshare();
  }

  void initial_params::setshare(const index_type& sf,
    const index_type& af) 
  { 
    cerr << " setshare not yet defined for this class " << endl;
    ad_exit(1);
  }

  shareinfo::~shareinfo(void)
  { 
    delete sflags; 
    delete original_sflags; 
    delete aflags; 
    delete invflags; 
    delete bmap; 
    sflags=0; 
    aflags=0; 
    original_sflags=0; 
    invflags=0; 
    current_phase=-1;
    maxshare=0;
    bmap=0;
  }

  int &  shareinfo::get_current_phase(void)
  { 
    return current_phase; 
  }
  index_type * shareinfo::get_original_shareflags(void)
  { 
    return original_sflags; 
  }
  index_type * shareinfo::get_shareflags(void)
  { 
    return sflags; 
  }
  i3_array & shareinfo::get_bmap(void)
  { 
    return *bmap;
  }
  index_type * shareinfo::get_invflags(void)
  { 
    return invflags;
  }
  index_type * shareinfo::get_activeflags(void)
  { 
    return aflags;
  }
  void shareinfo::set_invflags(const index_type& sf)
  { 
    invflags=new index_type(sf);
  }
  void shareinfo::set_bmap(const i3_array & _bmap)
  { 
    bmap=new i3_array(_bmap);
  }
  void shareinfo::reset_bmap(const i3_array & _bmap)
  { 
    if (bmap) 
    {
      delete bmap;
      bmap=0;
    }
    bmap=new i3_array(_bmap);
  }
  void shareinfo::reset_shareflags(const index_type& sf)
  { 
    if (sflags)
    {
      delete sflags;
      sflags=0;
    }
    sflags=new index_type(sf);
  }
  void shareinfo::set_original_shareflags(const index_type& sf)
  { 
    original_sflags=new index_type(sf);
  }
  void shareinfo::set_shareflags(const index_type& sf)
  { 
    sflags=new index_type(sf);
  }
  void shareinfo::set_activeflags(const index_type& af)
  { 
    aflags=new index_type(af);
  }
  shareinfo::shareinfo(const index_type& sf,const index_type& af) 
  {
    set_shareflags(sf); 
    set_original_shareflags(sf); 
    set_activeflags(af); 
    invflags=0;
    current_phase=-1;
  }

  void shareinfo::get_inv_matrix_shared(int _cf)
  {
    if (current_phase != _cf)
    {
      current_phase = _cf;
      const index_type& sf=*(get_original_shareflags());
      const index_type& af=*(get_activeflags());
      if (sf.dimension() !=2)
      {
        cerr << "error " << endl;
        ad_exit(1);
      }
      int imin= sf.indexmin();
      int imax= sf.indexmax();
      int fmin,fmax;
      int i,k;
      int ibreak=0;
      // get intial values for min and max active flag values
      for (i=imin;i<=imax;i++)
      {
        int jmin= sf(i).indexmin();
        int jmax= sf(i).indexmax();
        for (int j=jmin;j<=jmax;j++)
        {
          int afvalue=integer(af(i)(j));
          if (afvalue && afvalue<=current_phase)
          {
            fmax=integer(sf(i)(j));
            fmin=integer(sf(i)(j));
            ibreak=1;
            break;
          }
        }
        if (ibreak)
          break;
      }
      // get initial values for minimum and maximum shared
      // flags -- not just active ones
      int fmax1=integer(sf(imin)(sf(imin).indexmin()));
      int fmin1=integer(sf(imin)(sf(imin).indexmin()));
      for (i=imin;i<=imax;i++)
      {
        int jmin= sf(i).indexmin();
        int jmax= sf(i).indexmax();
        for (int j=jmin;j<=jmax;j++)
        {
          fmax1=max(fmax1,integer(sf(i)(j)));
          fmin1=min(fmin1,integer(sf(i)(j)));
          int afvalue=integer(af(i)(j));
          if (afvalue && afvalue<=current_phase)
          {
            fmax=max(fmax,integer(sf(i)(j)));
            fmin=min(fmin,integer(sf(i)(j)));
          }
        }
      }
      // set up info for sanity test on shared and active flags
      ivector icount2(fmin1,fmax1);
      icount2.initialize();
      for (i=imin;i<=imax;i++)
      {
        int jmin= sf(i).indexmin();
        int jmax= sf(i).indexmax();
        for (int j=jmin;j<=jmax;j++)
        {
          int sfvalue=integer(sf(i)(j));
          icount2(sfvalue)++;
        }
      }
      i3_array bmap2(fmin1,fmax1,1,icount2,1,2);
      icount2.initialize();
      for (i=imin;i<=imax;i++)
      {
        int jmin= sf(i).indexmin();
        int jmax= sf(i).indexmax();
        for (int j=jmin;j<=jmax;j++)
        {
          int sfvalue=integer(sf(i)(j));
          int ind=++icount2(sfvalue);
          bmap2(sfvalue,ind,1)=i;
          bmap2(sfvalue,ind,2)=j;
        }
      }
      for (k=fmin1;k<=fmax1;k++)
      {
        int lmin=bmap2(k).indexmin();
        int lmax=bmap2(k).indexmax();
        
        if (lmax>0)
        {
          int i1=bmap2(k,lmin,1);
          int j1=bmap2(k,lmin,2);
          int a1=integer(af(i1)(j1));

          for (int l=lmin+1;l<=lmax;l++)
          {
            int i2=bmap2(k,l,1);
            int j2=bmap2(k,l,2);
            int a2=integer(af(i2)(j2));
            if (a1 !=a2)
            {
              cerr << "Sanity error in grouping/active flags"
               << endl << "for indices (" << i2 << "," << j2 << ")"
               << endl;
              ad_exit(1);
            }
          }
        }
      }
        
  
      // indirect will cotain pointers for the number 
      // of active parameters it starts out with the
      // number of shared flags and removes the inactive ones
      ivector indirect(fmin1,fmax1);
      ivector processed_flag(fmin1,fmax1);
      processed_flag.initialize();
      ivector mindx(imin,imax);
      ivector maxx(imin,imax);
      indirect.fill_seqadd(1,1);
      for (i=imin;i<=imax;i++)
      {
        int jmin= sf(i).indexmin();
        int jmax= sf(i).indexmax();
        mindx(i)=jmin;
        maxx(i)=jmax;
        for (int j=jmin;j<=jmax;j++)
        {
          int afvalue=integer(af(i)(j));
          if (afvalue==0 || afvalue>current_phase)
          {
            int in=integer(sf(i)(j));
            if (processed_flag(in)==0)
            {
              processed_flag(in)=1;
              for (k=in;k<=fmax1;k++)
              {
                indirect(k)-=1;
              }
            }
          }
        }
      }
      imatrix tmp1(imin,imax,mindx,maxx);
      for (i=imin;i<=imax;i++)
      {
        int jmin= sf(i).indexmin();
        int jmax= sf(i).indexmax();
        for (int j=jmin;j<=jmax;j++)
        {
          int afvalue=integer(af(i)(j));
          if (afvalue && afvalue<=current_phase)
          {
             tmp1(i,j)=indirect(integer(sf(i)(j)));
          }
          else
          {
            tmp1(i,j)=0;
          }
        }
      }
      int itmp=indirect(fmax1);
      imatrix tmp(1,itmp,1,2);
      ivector counter(1,itmp);
      counter.initialize();
      for (i=imin;i<=imax;i++)
      {
        int jmin= sf(i).indexmin();
        int jmax= sf(i).indexmax();
        for (int j=jmin;j<=jmax;j++)
        {
          int afvalue=integer(af(i)(j));
          if (afvalue && afvalue<=current_phase)
          {
            if (++counter(tmp1(i,j))==1)
            {
              tmp(tmp1(i,j),1)=i;
              tmp(tmp1(i,j),2)=j;
            }
          }
        }
      }
      i3_array _bmap(1,itmp,1,counter,1,2);

      counter.initialize();
      _bmap.initialize();
      for (i=imin;i<=imax;i++)
      {
        int jmin= sf(i).indexmin();
        int jmax= sf(i).indexmax();
        for (int j=jmin;j<=jmax;j++)
        {
          int afvalue=integer(af(i)(j));
          if (afvalue && afvalue<=current_phase)
          {
            int ind=++counter(tmp1(i,j));
            _bmap(tmp1(i,j),ind,1)=i;
            _bmap(tmp1(i,j),ind,2)=j;
          }
        }
      }
      {
        cout <<  endl;
        for (int i=1;i<=itmp;i++)
          cout << _bmap(i) << endl << endl;
      }
      set_bmap(_bmap);

      get_maxshare()=itmp;
      reset_shareflags(tmp1);
      set_invflags(tmp);
      cout << tmp1 << endl;
      //return tmp1;
    }
  }

  void shareinfo::get_inv_vector_shared(int _cf)
  {
    if (current_phase != _cf)
    {
      current_phase = _cf;
      const index_type& sf=*(get_original_shareflags());
      const index_type& af=*(get_activeflags());
      if (sf.dimension() !=1)
      {
        cerr << "error " << endl;
        ad_exit(1);
      }
      int imin= sf.indexmin();
      int imax= sf.indexmax();
      int i,k;
      //int ibreak=0;
      // get intial values for min and max active flag values
      // get initial values for minimum and maximum shared
      // flags -- not just active ones
      int fmax1=integer(sf(imin));
      int fmin1=integer(sf(imin));
      for (i=imin;i<=imax;i++)
      {
        fmax1=max(fmax1,integer(sf(i)));
        fmin1=min(fmin1,integer(sf(i)));
      }
  
      ivector indirect(fmin1,fmax1);
      ivector processed_flag(fmin1,fmax1);
      processed_flag.initialize();
      indirect.fill_seqadd(1,1);
      for (i=imin;i<=imax;i++)
      {
        {
          int afvalue=integer(af(i));
          if (afvalue==0 || afvalue>current_phase)
          {
            int in=integer(sf(i));
            if (processed_flag(in)==0)
            {
              processed_flag(in)=1;
              for (k=in;k<=fmax1;k++)
              {
                indirect(k)-=1;
              }
            }
          }
        }
      }
      ivector tmp1(imin,imax);
      for (i=imin;i<=imax;i++)
      {
        {
          int afvalue=integer(af(i));
          if (afvalue && afvalue<=current_phase)
          {
             tmp1(i)=indirect(integer(sf(i)));
          }
          else
          {
            tmp1(i)=0;
          }
        }
      }
      int itmp=indirect(fmax1);
      ivector tmp(1,itmp);
      ivector counter(1,itmp);
      counter.initialize();
      for (i=imin;i<=imax;i++)
      {
        int afvalue=integer(af(i));
        if (afvalue && afvalue<=current_phase)
        {
          if (++counter(tmp1(i))==1)
          {
            tmp(tmp1(i))=i;
          }
        }
      }
      get_maxshare()=itmp;
      reset_shareflags(tmp1);
      set_invflags(tmp);
    }
  }

  void param_init_vector::setshare(const index_type& sf,const index_type& af)
  {
    share_flags = new shareinfo(sf,af);
    int idim1= share_flags->get_shareflags()->dimension();
    share_flags->get_dimension()=idim1;
    //int idim2= share_flags->get_activeflags()->dimension();
    if (idim1==2)
    {
      cout << " Error dim too high" << endl;
      ad_exit(1);
    }
       // check rationality
    /*
      int mmin1= share_flags->get_shareflags()->indexmin();
      int mmax1= share_flags->get_shareflags()->indexmax();
      int mmin2= share_flags->get_activeflags()->indexmin();
      int mmax2= share_flags->get_activeflags()->indexmax();
      int mmin=indexmin();
      int mmax=indexmax();
      if (mmin1 != mmin || mmax1 != mmax ||
        mmin2 != mmin || mmax2 != mmax)
      {
        cerr << "sanity error" << endl;
        ad_exit(1);
      }
    */
    share_flags->get_inv_vector_shared(current_phase);
  }

  void param_init_matrix::setshare(const index_type& sf,const index_type& af)
  {
    share_flags = new shareinfo(sf,af);
    int idim1= share_flags->get_shareflags()->dimension();
    share_flags->get_dimension()=idim1;
    int idim2= share_flags->get_activeflags()->dimension();
    switch (idim1)
    {
    case 1:
      share_flags->get_inv_vector_shared(current_phase);
      break;
    case 2:
      {
        cout << idim1 << " " << idim2 << endl;
         // check rationality
        int mmin1= share_flags->get_shareflags()->indexmin();
        int mmax1= share_flags->get_shareflags()->indexmax();
        int mmin2= share_flags->get_activeflags()->indexmin();
        int mmax2= share_flags->get_activeflags()->indexmax();
        int mmin=indexmin();
        int mmax=indexmax();
        if (mmin1 != mmin || mmax1 != mmax ||
          mmin2 != mmin || mmax2 != mmax)
        {
          cerr << "sanity error" << endl;
          ad_exit(1);
        }
        share_flags->get_inv_matrix_shared(current_phase);
      }
      break;
    default:
      cerr << "Error" << endl;
      ad_exit(1);
    }
  }
#  endif
 

