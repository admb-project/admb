/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <admodel.h>


 int initial_params::num_initial_params=0;

#if !defined(BIG_INIT_PARAMS)
  const int initial_params::max_num_initial_params=4000;
#  if (__BORLANDC__  >= 0x0550) 
 initial_params * initial_params::varsptr[4001]; // this should be a resizeable array
#  else
 initial_params * initial_params::varsptr[initial_params::max_num_initial_params+1]; // this should be a resizeable array
#  endif
#else
  const int initial_params::max_num_initial_params=250;
  adlist_ptr initial_params::varsptr(initial_params::max_num_initial_params);
#endif
 int initial_params::max_number_phases=1;
 int initial_params::current_phase=1;
 int initial_params::restart_phase=0;
 int initial_params::sd_phase=0;
 int initial_params::mc_phase=0;
 int initial_params::mceval_phase=0;
 int AD_gaussflag=0;
 int ADqd_flag=0;

 double initial_params::get_scalefactor(void)
 { 
   return scalefactor;
 }
 void initial_params::set_scalefactor(const double sf) 
 {
   scalefactor=sf;
 }

 dvector function_minimizer::convergence_criteria;
 dvector function_minimizer::maximum_function_evaluations;
 int function_minimizer::sd_flag;
 adstring function_minimizer::user_data_file;
 adstring function_minimizer::user_par_file;

  int withinbound(int lb,int n,int ub)
  {
    if (lb<=n && n<=ub) 
      return 1;
    else 
     return 0;
  }
  
  initial_params::~initial_params()
  {
#  if defined(USE_SHARE_FLAGS)
    if (share_flags)
    {
      delete share_flags;
      share_flags=0;
    }
#  endif
  }
  
  initial_params::initial_params(void)
  {
#  if defined(USE_SHARE_FLAGS)
     share_flags=0;
#  endif
    phase_start=0;
    phase_save=-9999;
    initial_value=0;
    initial_value_flag=0;
    active_flag=0;
    scalefactor=0;
  }

  void initial_params::set_initial_value(double x)
  {
    initial_value=x;
    initial_value_flag=1;
  }

  double initial_params::get_initial_value(void)
  {
    return initial_value;
  }

  void initial_params::set_phase_start(int i)
  {
    phase_start=i;
    phase_save=i;
  }

  int initial_params::get_phase_start(void)
  {
    return phase_start;
  }


  void model_name_tag::allocate(const char * s)
  {
    name=s;
  }

  void initial_params::allocate(int _phase_start)
  {
#if !defined(BIG_INIT_PARAMS)
    add_to_list();
#else
    varsptr.add_to_list(this);
    num_initial_params++;
#endif
    phase_start=_phase_start;
    phase_save=phase_start;
    if (max_number_phases<_phase_start) max_number_phases=_phase_start;
  }

  void initial_params::add_to_list(void)
  {
    if (num_initial_params>=initial_params::max_num_initial_params)
    {
      cerr << " This version of ADMB only supports "
          << initial_params::max_num_initial_params << " initial parameter"
        " objects" << endl;
      ad_exit(1);
    }
    varsptr[num_initial_params++]= this; // this is the list of 
                                         // fundamental objects
  }

  int initial_params::correct_for_dev_objects(BOR_CONST dmatrix&H)
  {
    cout << H << endl << endl;
    int ii=1;
    for (int i=0;i<num_initial_params;i++)
    {
      if (withinbound(0,(varsptr[i])->phase_start,current_phase))
      {
	(varsptr[i])->dev_correction(H,ii);
      }
    }
    cout << H << endl << endl;
    return ii-1;
  }

  int initial_params::nvarcalc()
  {
    int nvar=0;
    for (int i=0;i<num_initial_params;i++)
    {
      //if ((varsptr[i])->phase_start <= current_phase)
#  if defined(USE_SHARE_FLAGS)
       if (varsptr[i]->share_flags !=0)  
       {
          nvar+=(varsptr[i])->shared_size_count();
       }
       else
       {
#  endif
          if (withinbound(0,(varsptr[i])->phase_start,current_phase))
          {
    	    nvar+= (varsptr[i])->size_count();
          }
#  if defined(USE_SHARE_FLAGS)
        }
#  endif
    }
    return nvar;
  }

  int initial_params::num_active_calc()
  {
    int ntypes=0;
    for (int i=0;i<num_initial_params;i++)
    {
      //if ((varsptr[i])->phase_start <= current_phase)
      if (withinbound(0,(varsptr[i])->phase_start,current_phase))
      {
	ntypes++;
      }
    }
    return ntypes;
  }

  int initial_params::stddev_vscale(const dvar_vector& d,const dvar_vector& x)
  {
    int ii=1;
    for (int i=0;i<num_initial_params;i++)
    {
      if (withinbound(0,(varsptr[i])->phase_start,current_phase))
	(varsptr[i])->sd_vscale(d,x,ii);
    }
    return ii-1;
  }

  int initial_params::stddev_scale(BOR_CONST dvector& d,BOR_CONST dvector& x)
  {
    int ii=1;
    for (int i=0;i<num_initial_params;i++)
    {
      //if ((varsptr[i])->phase_start <= current_phase)
      if (withinbound(0,(varsptr[i])->phase_start,current_phase))
	(varsptr[i])->sd_scale(d,x,ii);
    }
    return ii-1;
  }

  int initial_params::stddev_curvscale(BOR_CONST dvector& d,BOR_CONST dvector& x)
  {
    int ii=1;
    for (int i=0;i<num_initial_params;i++)
    {
      //if ((varsptr[i])->phase_start <= current_phase)
      if (withinbound(0,(varsptr[i])->phase_start,current_phase))
	(varsptr[i])->curv_scale(d,x,ii);
    }
    return ii-1;
  }

  void initial_params::xinit(BOR_CONST dvector& x)
  {
    int ii=1;
    for (int i=0;i<num_initial_params;i++)
    {
      //if ((varsptr[i])->phase_start <= current_phase)
#  if defined(USE_SHARE_FLAGS)
       if (varsptr[i]->share_flags !=0)  
       {
          (varsptr[i])->shared_set_value_inv(x,ii);
       }
       else
       {
#  endif 
         if (withinbound(0,(varsptr[i])->phase_start,current_phase))
         {
           (varsptr[i])->set_value_inv(x,ii);
           (varsptr[i])->set_active_flag();
         }
#  if defined(USE_SHARE_FLAGS)
        }
#  endif 
    }
  }

  void initial_params::set_active_only_random_effects(void)
  {
    for (int i=0;i<num_initial_params;i++)
    {
      (varsptr[i])->set_only_random_effects_active();
    }
  }

  void initial_params::set_inactive_only_random_effects(void)
  {
    for (int i=0;i<num_initial_params;i++)
    {
      (varsptr[i])->set_only_random_effects_inactive();
    }
  }

  void initial_params::set_active_random_effects(void)
  {
    for (int i=0;i<num_initial_params;i++)
    {
      (varsptr[i])->set_random_effects_active();
    }
  }

  void initial_params::restore_start_phase(void)
  {
    for (int i=0;i<num_initial_params;i++)
    {
      (varsptr[i])->restore_phase_start();
    }
  }

  void initial_params::restore_phase_start(void)
  {
    phase_start=phase_save;
  }

  void initial_params::set_inactive_random_effects(void)
  {
    for (int i=0;i<num_initial_params;i++)
    {
      (varsptr[i])->set_random_effects_inactive();
    }
  }

  void initial_params::xinit1(BOR_CONST dvector& _x,BOR_CONST dvector& g)
  {
    int ii=1;
    dvector& x=(dvector&) _x;
    for (int i=0;i<num_initial_params;i++)
    {
      //if ((varsptr[i])->phase_start <= current_phase)
      if (withinbound(0,(varsptr[i])->phase_start,current_phase))
      {
        (varsptr[i])->set_value_inv(x,ii);
        (varsptr[i])->set_active_flag();
      }
    }
    x=elem_prod(x,g);
  }

  dvariable initial_params::reset(BOR_CONST dvar_vector& x,BOR_CONST dvector& __pen)
  {
    dvector& _pen=(dvector&) __pen;
    int ii=1;
    dvariable pen=0.0;
    dvariable pen1;
    for (int i=0;i<num_initial_params;i++)
    {
      if (withinbound(0,(varsptr[i])->phase_start,current_phase))
      {
        (varsptr[i])->set_value(x,ii,pen1);
        _pen(ii-1)=value(pen1);
        pen+=pen1; 
      }
    }
    return pen;
  }

  dvariable initial_params::reset1(BOR_CONST dvar_vector& _x,BOR_CONST dvector& g)
  {
    dvar_vector& x=(dvar_vector&) _x;
    int ii=1;
    dvariable pen=0.0;
    x=elem_div(x,g);
    for (int i=0;i<num_initial_params;i++)
    {
      //if ((varsptr[i])->phase_start <= current_phase)
      if (withinbound(0,(varsptr[i])->phase_start,current_phase))
        (varsptr[i])->set_value(x,ii,pen);
    }
    return pen;
  }

  dvariable initial_params::reset(BOR_CONST dvar_vector& x)
  {
    int ii=1;
    dvariable pen=0.0;
    for (int i=0;i<num_initial_params;i++)
    {
#  if defined(USE_SHARE_FLAGS)
      if (varsptr[i]->share_flags !=0)  
      {
         (varsptr[i])->shared_set_value(x,ii,pen);
      }
      else
      {
#  endif 
        //if ((varsptr[i])->phase_start <= current_phase)
        if (withinbound(0,(varsptr[i])->phase_start,current_phase))
        (varsptr[i])->set_value(x,ii,pen);
#  if defined(USE_SHARE_FLAGS)
      }
#  endif 
    }
    return pen;
  }

  dvariable initial_params::reset(BOR_CONST dvector& x)
  {
    int ii=1;
    dvariable pen=0.0;
    for (int i=0;i<num_initial_params;i++)
    {
      //if ((varsptr[i])->phase_start <= current_phase)
      if (withinbound(0,(varsptr[i])->phase_start,current_phase))
        (varsptr[i])->set_value(x,ii,pen);
    }
    return pen;
  }

  void initial_params::save()
  {
    adstring tmp;
    if (current_phase==max_number_phases)
    {
      tmp="ar";
    }
    else if (current_phase>=10)
    {
      tmp=str(current_phase);
    }
    else
    {
      tmp="0" + str(current_phase);
    }
    {
      adstring tadstring=ad_comm::adprogram_name + adstring(".p") + tmp;
      ad_comm::global_savefile = new ofstream((char*)tadstring);
      if (ad_comm::global_savefile)
      {
        *(ad_comm::global_savefile) << setshowpoint();
        *(ad_comm::global_savefile) <<  "# Number of parameters = "
           << initial_params::nvarcalc() << " ";
        *(ad_comm::global_savefile) <<  " Objective function value = "
           << *objective_function_value::pobjfun;
        *(ad_comm::global_savefile) <<  "  Maximum gradient component = "
           << objective_function_value::gmax << endl;
        *(ad_comm::global_savefile) << setshowpoint();
        
        for (int i=0;i<num_initial_params;i++)
        {
           (varsptr[i])->save_value();
        }
        delete ad_comm::global_savefile;
        ad_comm::global_savefile=NULL;
      }
    }
    {
      adstring tadstring=ad_comm::adprogram_name + adstring(".b") + tmp;
      ad_comm::global_bsavefile = new uostream((char*)tadstring);
      
      if (ad_comm::global_bsavefile)
      {
        for (int i=0;i<num_initial_params;i++)
        {
           (varsptr[i])->bsave_value();
        }
        delete ad_comm::global_bsavefile;
        ad_comm::global_bsavefile=NULL;
      }
    }

  }

  void initial_params::set_active_flag(void)
  {
    active_flag=1;
  }

  void initial_params::set_inactive_flag(void)
  {
    active_flag=0;
  }

  int active(const initial_params& ip)
  {
    return ip.active_flag;
  }

  void param_init_number::set_value(const dvar_vector& x,BOR_CONST int& ii,
    BOR_CONST dvariable& pen)
  {
    if (!scalefactor)
      ::set_value(*this,x,ii);
    else
      ::set_value(*this,x,ii,scalefactor);
  }

  void param_init_number::set_value_inv(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    if (!scalefactor)
      ::set_value_inv(*this,(BOR_CONST dvector&)(x),ii);
    else
      ::set_value_inv(*this,(BOR_CONST dvector&)(x),ii,scalefactor);
  }

  param_init_number::param_init_number() : named_dvariable() ,
    initial_params()
  {
    //add_to_list();
  }

  int param_init_number::size_count(void)
  {
    return 1;
  }

  void param_init_bounded_number::allocate(double _minb,
    double _maxb,int _phase_start,const char * _s)
  {
    minb=_minb;
    maxb=_maxb;
    if (minb>maxb)
    {
      cerr << "Error allocating init_bounded_number " << endl
        << " minb = " << minb << " maxb = " << maxb << endl;
      ad_exit(1);
    }
    named_dvariable::allocate(_s);
    initial_params::allocate(_phase_start);
    if (ad_comm::global_bparfile)
    {
      *(ad_comm::global_bparfile) >> value(*this);
        if (!(*(ad_comm::global_bparfile)))
        {
          cerr << "error reading parameters from binary file "
               <<  endl;
          ad_exit(1);
        }
    }
    else if (ad_comm::global_parfile)
    {
      *(ad_comm::global_parfile) >> value(*this);
        if (!(*(ad_comm::global_parfile)))
        {
          cerr << "error reading parameters from file "
               << ad_comm::global_parfile->get_file_name() << endl;
          ad_exit(1);
        }
    }
    else
    {
      if ((!initial_value_flag) || initial_value <=minb 
           || initial_value >= maxb)
      {
        prevariable::operator=((minb+maxb)/2.);
      }
      else
      {
        prevariable::operator=(initial_value);
      }
    }
  }
  void param_init_bounded_number::set_value(const dvar_vector& x,
    BOR_CONST int& ii,BOR_CONST dvariable& pen)
  {
    if (!scalefactor)
      ::set_value(*this,x,ii,minb,maxb,pen);
    else
      ::set_value(*this,x,ii,minb,maxb,pen,scalefactor);
  }

  void param_init_bounded_number::set_value_inv(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    if (!scalefactor)
      ::set_value_inv(*this,x,ii,minb,maxb);
    else
      ::set_value_inv(*this,x,ii,minb,maxb,scalefactor);
  }
  void param_init_bounded_number::allocate(double _minb,double _maxb,
    const char * _s)
  {
    allocate(_minb,_maxb,1,_s);
  }

  void check_datafile_pointer(void * p)
  {
    if (!p)
    {
      cerr << " Error trying to read in model data " << endl;
      cerr << " This is usual caused by a missing DAT file " << endl;
      ad_exit(1);
    }
  }

  data_number& data_number::operator =(_CONST double& v)
  {
    val=v;
    return *this;
  }

  void data_number::allocate(const char * s)
  {
    check_datafile_pointer(ad_comm::global_datafile);
    model_name_tag::allocate(s);
    *(ad_comm::global_datafile) >> val;
  }

  void named_dvariable::allocate(const char * s)
  {
    model_name_tag::allocate(s);
  }

  void named_dvector::allocate(int mmin,int mmax,const char * s)
  {
    dvector::allocate(mmin,mmax);
    model_name_tag::allocate(s);
  }

  void named_dvector::allocate(const char * s)
  {
    dvector::allocate();
    model_name_tag::allocate(s);
  }


  void named_ivector::allocate(int mmin,int mmax,const char * s)
  {
    ivector::allocate(mmin,mmax);
    model_name_tag::allocate(s);
  }

  void named_dvar_vector::allocate(int mmin,int mmax,const char * s)
  {
    dvar_vector::allocate(mmin,mmax);
    model_name_tag::allocate(s);
  }
  void named_dvar_vector::allocate(const char * s)
  {
    dvar_vector::allocate();
    model_name_tag::allocate(s);
  }

  void param_init_number::allocate( int phasestart,const char * s)
  {
    named_dvariable::allocate(s);
    initial_params::allocate(phasestart);
    if (ad_comm::global_bparfile)
    {
      *(ad_comm::global_bparfile) >> value(*this);
        if (!(*(ad_comm::global_bparfile)))
        {
          cerr << "error reading parameters from binary file "
               << endl;
          ad_exit(1);
        }
    }
    else if (ad_comm::global_parfile)
    {
      *(ad_comm::global_parfile) >> value(*this);
        if (!(*(ad_comm::global_parfile)))
        {
          cerr << "error reading parameters from file "
               << ad_comm::global_parfile->get_file_name() << endl;
          ad_exit(1);
        }
    }
    else
    {
      prevariable::operator=(initial_value);
    }
  }

  void param_init_number::allocate(const char * _s)
  {
    allocate(1,_s);
  }

  void param_init_number::save_value(void)
  {
    #ifndef __ZTC__
      *(ad_comm::global_savefile) << label_class(this->label())
        << setprecision(12) << dvariable(*this) << endl;
    #else
      *(ad_comm::global_savefile) <<  label_class(this->label())
        << *this << endl;
    #endif
  }

  void param_init_number::bsave_value(void)
  {
    dvariable tmp=*this;
    *(ad_comm::global_bsavefile) << tmp;
  }

  void param_init_vector::set_value(const dvar_vector& x,
    BOR_CONST int& ii,BOR_CONST dvariable& pen)
  {
    if (!scalefactor)
      ::set_value(*this,x,ii);
    else
      ::set_value(*this,x,ii,scalefactor);
  }

  void param_init_vector::set_value_inv(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
#  if defined(USE_SHARE_FLAGS)
    if (share_flags)
    {
      int ndim=share_flags->get_shareflags()->dimension();
      if (ndim!=1)
      {
        cerr << "grouping flags dimension error" << endl;
        ad_exit(1);
      }
    }
    else
    {
#  endif
    if (!scalefactor)
      ::set_value_inv(*this,x,ii);
    else
      ::set_value_inv(*this,x,ii,scalefactor);
#  if defined(USE_SHARE_FLAGS)
    }
#  endif
  }

  int param_init_vector::size_count(void)
  {
    return ::size_count(*this);
  }

  param_init_vector::param_init_vector(void) : named_dvar_vector() ,
    initial_params()
  {
    //add_to_list();
  }

  void param_init_vector::save_value(void)
  {
    if (!(!(*this)))
      *(ad_comm::global_savefile) << label_class(this->label()) << dvar_vector(*this) << endl;
  }

  void param_init_vector::bsave_value(void)
  {
    if (!(!(*this)))
    {
      dvar_vector& tmp=*this;
      *(ad_comm::global_bsavefile) << tmp;
    }
  }

 /*
  void param_init_vector::allocate(int imin,int imax,
     const ivector& ishare,const char * s)
  {
    share_flags=new index_type(ishare);
    allocate(imin,imax,1,s);
  }
 */

  void param_init_vector::allocate(int imin,int imax,int phase_start,
     const char * s)
  {
    named_dvar_vector::allocate(imin,imax,s);
    if (!(!(*this)))
    {
      initial_params::allocate(phase_start);
      if (ad_comm::global_bparfile)
      {
        *(ad_comm::global_bparfile) >> dvar_vector(*this);
        if (!(*(ad_comm::global_bparfile)))
        {
          cerr << "error reading parameters from binary file "
               << endl;
          ad_exit(1);
        }
      }
      else if (ad_comm::global_parfile)
      {
        *(ad_comm::global_parfile) >> dvar_vector(*this);
        if (!(*(ad_comm::global_parfile)))
        {
          cerr << "error reading parameters from file "
               << ad_comm::global_parfile->get_file_name() << endl;
          ad_exit(1);
        }
      }
      else
      {
        dvar_vector::operator=(initial_value);
      }
    }
    else
    {
      initial_params::allocate(-1);
    }
  }

  void param_init_matrix::allocate(int rmin,int rmax,int cmin,int cmax,
    const char * s)
  {
    allocate(rmin,rmax,cmin,cmax,1,s);
  }

 /*
  void param_init_matrix::allocate(int rmin,int rmax,int cmin,int cmax,
    const imatrix& jshare,const char * s)
  {
    share_flags=new index_type(jshare);
    allocate(rmin,rmax,cmin,cmax,1,s);
  }
 */

  void param_init_matrix::allocate(int rmin,int rmax,int cmin,int cmax,
    int _phase_start, const char * s)
  {
    named_dvar_matrix::allocate(rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      initial_params::allocate(_phase_start);
      if (ad_comm::global_bparfile)
      {
        *(ad_comm::global_bparfile) >> dvar_matrix(*this);
        if (!(*(ad_comm::global_bparfile)))
        {
          cerr << "error reading parameters from binary file "
               << endl;
          ad_exit(1);
        }
      }
      else if (ad_comm::global_parfile)
      {
        *(ad_comm::global_parfile) >> dvar_matrix(*this);
        if (!(*(ad_comm::global_parfile)))
        {
          cerr << "error reading parameters from file "
               << ad_comm::global_parfile->get_file_name() << endl;
          ad_exit(1);
        }
      }
      else
      {
        dvar_matrix::operator=(initial_value);
      }
    }
    else
    {
      initial_params::allocate(-1);
    }
  }

  void param_init_vector::allocate(int imin,int imax,const char * s)
  {
    allocate(imin,imax,1,s);
  }

  void param_init_bounded_vector::set_value(const dvar_vector& x,
    BOR_CONST int& ii,BOR_CONST dvariable& pen)
  {
    if (!(!(*this)))
    {
      if (initial_params::mc_phase)
      {
        set_value_mc(*this,x,ii,minb,maxb);
      }
      else
      {
        if (!scalefactor)
          ::set_value(*this,x,ii,minb,maxb,pen);
        else
          ::set_value(*this,x,ii,minb,maxb,pen,scalefactor);
      }
    }
  }

  void param_init_bounded_vector::set_value_inv(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    if (!(!(*this)))
    {
      if (initial_params::mc_phase)
      {
        set_value_inv_mc(*this,x,ii,minb,maxb);
      }
      else 
      {
        if (!scalefactor)
          ::set_value_inv(*this,x,ii,minb,maxb);
        else 
          ::set_value_inv(*this,x,ii,minb,maxb,scalefactor);
      }
    }
  }

  int param_init_bounded_vector::size_count(void)
  {
    return ::size_count(*this);
  }

  param_init_bounded_vector::param_init_bounded_vector(void) :
    named_dvar_vector() , initial_params()
  {
    //add_to_list();
  }

  param_init_bounded_number::param_init_bounded_number(void) :
    param_init_number() {}
  //{
   // add_to_list();
  //}

  void param_init_bounded_vector::allocate(int imin,int imax,
    double _minb,double _maxb,int _phase_start,const char * s)
  {
    minb=_minb;
    maxb=_maxb;
    named_dvar_vector::allocate(imin,imax,s);
    initial_params::allocate(_phase_start);
    if (!(!(*this)))
    {
      if (ad_comm::global_bparfile)
      {
        *(ad_comm::global_bparfile) >> dvar_vector(*this);
        if (!(*(ad_comm::global_bparfile)))
        {
          cerr << "error reading parameters from binary file "
               << endl;
          ad_exit(1);
        }
      }
      else if (ad_comm::global_parfile)
      {
        *(ad_comm::global_parfile) >> dvar_vector(*this);
        if (!(*(ad_comm::global_parfile)))
        {
          cerr << "error reading parameters from file "
               << ad_comm::global_parfile->get_file_name() << endl;
          ad_exit(1);
        }
      }
      else
      {
        if ((!initial_value_flag) || initial_value <=minb 
             || initial_value >= maxb)
        {
          initial_value=(minb+maxb)/2.; 
        } 
        dvar_vector::operator=(initial_value);
      }
    }
    else
    {
      initial_params::allocate(-1);
    }
  }

  void param_init_bounded_vector::allocate(int imin,int imax,
    double _minb,double _maxb,const char * s)
  {
    allocate(imin,imax,_minb,_maxb,1,s);
  }

  void param_init_bounded_vector::save_value(void)
  {
    if (!(!(*this)))
      *(ad_comm::global_savefile) << label_class(this->label())
                    << dvar_vector(*this) << endl;
  }

  void param_init_bounded_vector::bsave_value(void)
  {
    if (!(!(*this)))
    {
      dvar_vector& tmp=*this;
      *(ad_comm::global_bsavefile) << tmp;
    }
  }

  void param_init_matrix::set_value(const dvar_vector& x,BOR_CONST int& ii,
    BOR_CONST dvariable& pen)
  {
    if (!scalefactor)
      ::set_value(*this,x,ii);
    else
      ::set_value(*this,x,ii,scalefactor);
  }


  void param_init_matrix::set_value_inv(BOR_CONST dvector& x,BOR_CONST int& ii)
  {
    if (!scalefactor)
      ::set_value_inv(*this,x,ii);
    else
      ::set_value_inv(*this,x,ii,scalefactor);
  }

  param_init_matrix::param_init_matrix() : named_dvar_matrix() , 
    initial_params()
  {
    //add_to_list();
  }

  int param_init_matrix::size_count(void)
  {
    return ::size_count(*this);
  }

  void param_init_matrix::save_value(void)
  {
    if (!(!(*this)))
      *(ad_comm::global_savefile) << label_class(this->label()) 
        << dvar_matrix(*this) << endl;
  }

  void param_init_matrix::bsave_value(void)
  {
    if (!(!(*this)))
    {
      dvar_matrix& tmp=*this;
      *(ad_comm::global_bsavefile) << tmp;
    }
  }


  void data_matrix::allocate(int rmin,int rmax,int cmin,int cmax,
    const char * s)
  {
    named_dmatrix::allocate(rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> *this;
    }
  }

  void data_matrix::allocate(int rmin,int rmax,BOR_CONST ivector& cmin,BOR_CONST ivector& cmax,
    const char * s)
  {
    named_dmatrix::allocate(rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> *this;
    }
  }

  void data_matrix::allocate(int rmin,int rmax,int cmin,BOR_CONST ivector& cmax,
    const char * s)
  {
    named_dmatrix::allocate(rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> *this;
    }
  }

  void data_matrix::allocate(int rmin,int rmax,BOR_CONST ivector& cmin,int cmax,
    const char * s)
  {
    named_dmatrix::allocate(rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> *this;
    }
  }

  void data_3array::allocate(int hsl,int hsu,int rmin,int rmax,
    int cmin,int cmax,const char * s)
  {
    named_d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> d3_array(*this);
    }
  }

  void data_3array::allocate(int hsl,int hsu,_CONST index_type& rmin,
    _CONST index_type& rmax,_CONST  index_type& cmin,
     _CONST index_type& cmax,const char * s)
  {
    named_d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> d3_array(*this);
    }
  }

      
  void data_3array::allocate(int hsl,int hsu,_CONST ivector& rmin,
    int rmax,int cmin,int cmax,const char * s)
  {
    named_d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> d3_array(*this);
    }
  }

  void data_3array::allocate(int hsl,int hsu,int rmin,
    _CONST ivector& rmax,int cmin,int cmax,const char * s)
  {
    named_d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> d3_array(*this);
    }
  }

  void data_3array::allocate(int hsl,int hsu,_CONST ivector& rmin,
    _CONST ivector& rmax,int cmin,int cmax,const char * s)
  {
    named_d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> d3_array(*this);
    }
  }

  void data_3array::allocate(int hsl,int hsu,int rmin,int rmax,
    _CONST ivector& cmin,int cmax,const char * s)
  {
    named_d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> d3_array(*this);
    }
  }

  void data_3array::allocate(int hsl,int hsu,int rmin,int rmax,
    int cmin,_CONST ivector& cmax,const char * s)
  {
    named_d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> d3_array(*this);
    }
  }

  void data_3array::allocate(int hsl,int hsu,int rmin,int rmax,
    _CONST ivector& cmin,_CONST ivector& cmax,const char * s)
  {
    named_d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> d3_array(*this);
    }
  }

  void data_imatrix::allocate(int rmin,int rmax,int cmin,int cmax,
   const char * s)
  {
    named_imatrix::allocate(rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> imatrix(*this);
    }
  }

  void data_imatrix::allocate(int rmin,int rmax,_CONST index_type& cmin,
    _CONST index_type& cmax, const char * s)
  {
    named_imatrix::allocate(rmin,rmax,cmin,cmax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> imatrix(*this);
    }
  }

  void data_int::allocate(int n,const char * s)
  {
    val=n;
    model_name_tag::allocate(s);
  }

  void data_int::allocate(const char * s)
  {
    check_datafile_pointer(ad_comm::global_datafile);
    *(ad_comm::global_datafile) >> val;
    model_name_tag::allocate(s);
  }

void named_imatrix::allocate(int rmin,int rmax,int cmin,int cmax,
  const char * s)
{
  imatrix::allocate(rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_imatrix::allocate(int rmin,int rmax,_CONST index_type& cmin,
  _CONST index_type& cmax, const char * s)
{
  imatrix::allocate(rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

  void data_vector::allocate(int imin,int imax,const char * s)
  {
    named_dvector::allocate(imin,imax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> dvector(*this);
    }
  }


  void data_ivector::allocate(int imin,int imax,const char * s)
  {
    named_ivector::allocate(imin,imax,s);
    if (!(!(*this)))
    {
      check_datafile_pointer(ad_comm::global_datafile);
      *(ad_comm::global_datafile) >> ivector(*this);
    }
  }


adstring initial_params::get_reportfile_name(void)
{
  adstring tmp;
  if (current_phase==max_number_phases)
    tmp="rep";
  else if (current_phase>=10)
    tmp="r" + str(current_phase);
  else
    tmp="r0" + str(current_phase);
  tmp = "." + tmp;
  return tmp;
}

void initial_params::set_only_random_effects_active(void)
{
  //phase_save=phase_start;
  phase_start=-1;
}

void initial_params::set_only_random_effects_inactive(void)
{
  phase_start=phase_save;
}
void initial_params::set_random_effects_active(void) {;}

void initial_params::set_random_effects_inactive(void) {;}


#if defined(__SPDLL__)
#  if !defined(linux)
#    include <windows.h>
#  endif
void get_sp_printf(void)
{
#if !defined(linux)
  ad_printf=NULL;
  HINSTANCE h=LoadLibrary("sqpe.dll");
  if(h)
    ad_printf= (fptr) GetProcAddress(h,"S_newio_printf");
#endif
}
#endif

  pinitial_params & adlist_ptr::operator [] (int i)
  {
    return (pinitial_params &) ptr[i];
  }

  adlist_ptr::adlist_ptr(int init_size)
  {
    current=0;
    ptr = new ptovoid[init_size];
    if (ptr==0)
    {
      cerr << "Errorl allocating memory in adlist_ptr" << endl;
    }
    current_size=init_size;
  } 
  void adlist_ptr::resize(void)
  {
    current_size*=2;
    ptovoid * tmp = new ptovoid[current_size];
    if (tmp==0)
    {
      cerr << "Errorl allocating memory in adlist_ptr" << endl;
    }
    for (int i=0;i<current;i++)
    {
      tmp[i]=ptr[i];
    }
    delete [] ptr;
    ptr = tmp;
  }
  void adlist_ptr::add_to_list(void * p)
  {
    if (current>current_size)
    {
      cerr << "This can't happen in adlist_ptr" << endl;
      exit(1);
    }
    if (current==current_size)
    {
      resize();
    }
    ptr[current++]=p;
  }

  adlist_ptr::~adlist_ptr()
  {
    current=0;
    current_size=-1;
    if (ptr)
    {
      delete [] ptr;
      ptr=0;
    }
  } 


