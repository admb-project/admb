/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

 int stddev_params::num_stddev_params=0;
 int stddev_params::num_stddev_number_params=0;
 stddev_params * stddev_params::stddev_number_ptr[150]; // this should be a resizeable array

 stddev_params * stddev_params::stddevptr[150]; // this should be a resizeable array

  void stddev_params::add_to_list(void)
  {
    if (num_stddev_params>=150) 
    {
      cerr << "This version of ADMB only supports " << num_stddev_params
           << " stddev_params." << endl;
      exit(1);
    } 
    stddevptr[num_stddev_params++]= this; // this is the list of 
  }

  void stddev_params::add_to_gui_list(void)
  {
    if (num_stddev_number_params>=150) 
    {
      cerr << "This version of ADMB only supports " << num_stddev_params
           << " stddev_params." << endl;
      exit(1);
    } 
    stddev_number_ptr[num_stddev_number_params++]= this; // this is the list of 
  }

  ivector stddev_params::copy_all_number_offsets(void)
  {
    int ndv=stddev_params::num_stddev_number_calc();
    ivector no(1,ndv);
    for (int i=0;i<ndv;i++)
    {
      no(i+1)=stddev_number_ptr[i]->getindex();
    }
    return no;
  }


  int stddev_params::num_stddev_calc(void)
  {
    int nvar=0;
    for (int i=0;i<num_stddev_params;i++)
    {
      nvar+= (stddevptr[i])->size_count();
    }
    return nvar;
  }

  void stddev_params::setindex(int _index){;}
  int stddev_params::getindex(void){return 0;}

  int param_stddev_number::getindex(void)
  {
    return index;
  }
  void param_stddev_number::setindex(int _index)
  {
    index=_index;
  }

  void stddev_params::get_stddev_number_offset(void)
  {
    int offset=1;
    int ii=0;
    for (int i=0;i<num_stddev_params;i++)
    {
      if (stddevptr[i]==stddev_number_ptr[ii])
      {
        stddev_number_ptr[ii]->setindex(offset);
        if (++ii>=num_stddev_number_params) break;
      }
      offset+= (stddevptr[i])->size_count();
    }
  }

  int stddev_params::num_stddev_number_calc(void)
  {
    return stddev_params::num_stddev_number_params;
  }

  param_stddev_number::param_stddev_number() : named_dvariable() ,
    stddev_params()
  {
    add_to_list();
    add_to_gui_list();
    setindex(0);
  }

  int param_stddev_number::size_count(void)
  {
    return 1;
  }

  void param_stddev_number::set_dependent_variables(void)
  {
    #ifndef __ZTC__
    dvariable(*this) << dvariable(*this);
    #else
    *this << *this;
    #endif
  }


  void param_stddev_number::allocate(const char * _s)
  {
    named_dvariable::allocate(_s);
    stddev_params::allocate();
  }

  int param_stddev_vector::size_count(void)
  {
    return ::size_count(*this);
  }

  param_stddev_vector::param_stddev_vector(void) : named_dvar_vector() ,
    stddev_params()
  {
    add_to_list();
  }

  void param_stddev_vector::allocate(int imin,int imax,const char * s)
  {
    sd.allocate(imin,imax);
    named_dvar_vector::allocate(imin,imax,s);
    stddev_params::allocate();
  }

  void param_stddev_vector::set_dependent_variables(void)
  {
    dvar_vector(*this) << dvar_vector(*this);
  }

  param_stddev_matrix::param_stddev_matrix() : named_dvar_matrix() ,
    stddev_params()
  {
    add_to_list();
  }

  int param_stddev_matrix::size_count(void)
  {
    return ::size_count(*this);
  }

  void param_stddev_matrix::allocate(int rmin,int rmax,int cmin,int cmax,
    const char * s)
  {
    sd.allocate(rmin,rmax,cmin,cmax);
    named_dvar_matrix::allocate(rmin,rmax,cmin,cmax,s);
    stddev_params::allocate();
  }

  void param_stddev_matrix::set_dependent_variables(void)
  {
    dvar_matrix(*this) << dvar_matrix(*this);
  }


/*
dvar_vector& operator << (BOR_CONST dvar_vector& v,_CONST dvar_vector& w)
{
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    v[i] << w[i];
  }
  return v;
}

dvar_matrix& operator << (BOR_CONST dvar_matrix& v,_CONST dvar_matrix& w)
{
  int mmin=v.rowmin();
  int mmax=v.rowmax();
  for (int i=mmin;i<=mmax;i++)
  {
    v[i] << w[i];
  }
  return v;
}
*/

  const char * param_stddev_vector::label(void)
  {
    return model_name_tag::label().mychar();
  }

  const char * param_stddev_number::label(void)
  {
    return model_name_tag::label().mychar();
  }

  const char * param_stddev_matrix::label(void)
  {
    return model_name_tag::label().mychar();
  }

  /*
class param_stddev_number: public named_dvariable , stddev_params
{
  param_stddev_number& operator = (_CONST prevariable&);
  param_stddev_number& operator = (CGNU_DOUBLE);
  void allocate(const char *s="UNNAMED");
  virtual int size_count(void); // get the number of active parameters
  virtual const char * label(void);
  param_stddev_number();
  friend class model_parameters;
  virtual void set_dependent_variables(void);
};

class param_stddev_matrix: public named_dvar_matrix , stddev_params
{
  virtual int size_count(void);
  //virtual void read_value(void);
  virtual const char * label(void);
  void allocate(int rmin,int rmax,int cmin,int cmax,
    const char * s="UNNAMED");
  param_stddev_matrix(void);
  friend class model_parameters;
  virtual void set_dependent_variables(void);
};
*/
