/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <admodel.h>

cifstream&  operator >>(BOR_CONST cifstream &,BOR_CONST prevariable &);

cifstream& operator >> (BOR_CONST cifstream& _s, BOR_CONST param_init_number& x)
{
  cifstream&  s=(cifstream&) _s;
  s >> value(x);
  return s;
}

cifstream& operator >> (BOR_CONST cifstream& _s, BOR_CONST param_init_vector& _v)
{
  ADUNCONST(param_init_vector,v)
  cifstream&  s=(cifstream&) _s;
  int mmin=v.indexmin();
  int mmax=v.indexmax();
  for (int i=mmin;i<=mmax;i++)
  {
    s >> v(i);
    if (!s)
    {
      cerr << "Error reading element " << i << " of the vector "
        << v.label() << endl;
    }
  }
  return s;
}

cifstream& operator >> (BOR_CONST cifstream& _s, BOR_CONST param_init_matrix& m)
{
  cifstream&  s=(cifstream&) _s;
  s >> dvar_matrix(m);
  return s;
}

ostream& operator << (BOR_CONST ostream& _s,BOR_CONST label_class& lc)
{
  ostream&  s=(ostream&) _s;
  s << "# " << lc.name <<":" << endl;
  return s;
}

void named_dvar_matrix::allocate(int rmin,int rmax,int cmin,int cmax,
  const char * s)
{
  dvar_matrix::allocate(rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_dvar_matrix::allocate(int rmin,int rmax,
  const char * s)
{
  dvar_matrix::allocate(rmin,rmax);
  model_name_tag::allocate(s);
}

void named_dvar_matrix::allocate(const char * s)
{
  dvar_matrix::allocate();
  model_name_tag::allocate(s);
}

void named_dvar_matrix::allocate(int rmin,int rmax,const index_type& cmin,
  const index_type& cmax, const char * s)
{
  dvar_matrix::allocate(rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

named_dvar_matrix& named_dvar_matrix::operator = (_CONST dvar_matrix& m)
{
  this->dvar_matrix::operator=(m);
  return *this;
}
named_dvar_matrix& named_dvar_matrix::operator = (_CONST dmatrix& m)
{
  this->dvar_matrix::operator=(m);
  return *this;
}
named_dvar_matrix& named_dvar_matrix::operator = (CGNU_DOUBLE m)
{
  this->dvar_matrix::operator=(m);
  return *this;
}

named_dvar_matrix& named_dvar_matrix::operator = (_CONST dvariable& m)
{
  this->dvar_matrix::operator=(m);
  return *this;
}


param_stddev_matrix& param_stddev_matrix::operator = (_CONST dvar_matrix& m)
{
  this->dvar_matrix::operator=(m);
  return *this;
}
param_stddev_matrix& param_stddev_matrix::operator = (_CONST dmatrix& m)
{
  this->dvar_matrix::operator=(m);
  return *this;
}
param_stddev_matrix& param_stddev_matrix::operator = (CGNU_DOUBLE m)
{
  this->dvar_matrix::operator=(m);
  return *this;
}

param_stddev_vector& param_stddev_vector::operator = (_CONST dvar_vector& m)
{
  this->dvar_vector::operator=(m);
  return *this;
}

named_dvar_vector& named_dvar_vector::operator = (_CONST dvar_vector& m)
{
  this->dvar_vector::operator=(m);
  return *this;
}
named_dvar_vector& named_dvar_vector::operator = (_CONST dvector& m)
{
  this->dvar_vector::operator=(m);
  return *this;
}
named_dvar_vector& named_dvar_vector::operator = (CGNU_DOUBLE m)
{
  this->dvar_vector::operator=(m);
  return *this;
}

named_dvar_vector& named_dvar_vector::operator = (_CONST prevariable& m)
{
  this->dvar_vector::operator=(m);
  return *this;
}

named_dvector& named_dvector::operator = (_CONST dvector& m)
{
  this->dvector::operator=(m);
  return *this;
}
named_dvector& named_dvector::operator = (CGNU_DOUBLE m)
{
  this->dvector::operator=(m);
  return *this;
}

data_vector& data_vector::operator = (_CONST dvector& m)
{
  this->dvector::operator=(m);
  return *this;
}
data_vector& data_vector::operator = (CGNU_DOUBLE m)
{
  this->dvector::operator=(m);
  return *this;
}


param_stddev_vector& param_stddev_vector::operator = (_CONST dvector& m)
{
  this->dvar_vector::operator=(m);
  return *this;
}
param_stddev_vector& param_stddev_vector::operator = (CGNU_DOUBLE m)
{
  this->dvar_vector::operator=(m);
  return *this;
}

param_init_number& param_init_number::operator = (CGNU_DOUBLE m)
{
  this->dvariable::operator=(m);
  return *this;
}

param_init_number& param_init_number::operator = (_CONST prevariable& m)
{
  this->dvariable::operator=(m);
  return *this;
}

param_init_bounded_number& param_init_bounded_number::operator = (CGNU_DOUBLE m)
{
  this->dvariable::operator=(m);
  return *this;
}

param_init_bounded_number& param_init_bounded_number::operator = (_CONST prevariable& m)
{
  this->dvariable::operator=(m);
  return *this;
}

  const char * param_init_matrix::label(void)
  {
    return model_name_tag::label().mychar();
  }


  const char * param_init_bounded_number::label(void)
  {
    return model_name_tag::label().mychar();
  }


  const char * param_init_bounded_vector::label(void)
  {
    return model_name_tag::label().mychar();
  }


  const char * param_init_vector::label(void)
  {
    return model_name_tag::label().mychar();
  }


  const char * param_init_number::label(void)
  {
    return model_name_tag::label().mychar();
  }


void named_dvar3_array::allocate(int hsl,int hsu,int rmin,int rmax,
  int cmin,int cmax,const char * s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_dvar3_array::allocate(int hsl,int hsu,int rmin,int rmax,
  const char * s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax);
  model_name_tag::allocate(s);
}

void named_dvar3_array::allocate(int hsl,int hsu,
  const index_type& rmin,const index_type& rmax, const char * s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax);
  model_name_tag::allocate(s);
}

void named_dvar3_array::allocate(int hsl,int hsu,const char * s)
{
  dvar3_array::allocate(hsl,hsu);
  model_name_tag::allocate(s);
}

void named_dvar3_array::allocate(const char * s)
{
  dvar3_array::allocate();
  model_name_tag::allocate(s);
}

void named_dvar3_array::allocate(int hsl,int hsu,_CONST ivector& rmin,
  int rmax, int cmin,int cmax,const char * s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_dvar3_array::allocate(int hsl,int hsu,int rmin,
  _CONST ivector& rmax, int cmin,int cmax,const char * s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_dvar3_array::allocate(int hsl,int hsu,_CONST ivector& rmin,
  _CONST ivector& rmax, int cmin,int cmax,const char * s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}


void named_dvar3_array::allocate(int hsl,int hsu,int rmin,int rmax,
  _CONST ivector& cmin,int cmax,const char * s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_dvar3_array::allocate(int hsl,int hsu,int rmin,int rmax,
  _CONST ivector& cmin,_CONST ivector&  cmax,const char * s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_dvar3_array::allocate(int hsl,int hsu,int rmin,int rmax,
  int cmin,_CONST ivector&  cmax,const char * s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

named_dvar3_array& named_dvar3_array::operator = (_CONST dvar3_array& m)
{
  this->dvar3_array::operator=(m);
  return *this;
}



named_dvar3_array& named_dvar3_array::operator = (_CONST d3_array& m)
{
  this->dvar3_array::operator=(m);
  return *this;
}
void named_dmatrix::allocate(int rmin,int rmax,int cmin,int cmax,
  const char * s)
{
  dmatrix::allocate(rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}


void named_dmatrix::allocate(int rmin,int rmax,const ivector& cmin,int cmax,
  const char * s)
{
  dmatrix::allocate(rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}


void named_dmatrix::allocate(int rmin,int rmax,const char * s)
{
  dmatrix::allocate(rmin,rmax);
  model_name_tag::allocate(s);
}


void named_dmatrix::allocate(const char * s)
{
  dmatrix::allocate();
  model_name_tag::allocate(s);
}


void named_dmatrix::allocate(int rmin,int rmax,int cmin,const ivector& cmax,
  const char * s)
{
  dmatrix::allocate(rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_dmatrix::allocate(int rmin,int rmax,const ivector& cmin,
  const ivector& cmax, const char * s)
{
  dmatrix::allocate(rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

named_dmatrix& named_dmatrix::operator = (_CONST dmatrix& m)
{
  dmatrix::operator=(m);
  return *this;
}
named_dmatrix& named_dmatrix::operator = (CGNU_DOUBLE m)
{
  dmatrix::operator=(m);
  return *this;
}

param_stddev_number& param_stddev_number::operator = (_CONST prevariable& m)
{
  prevariable::operator=(m);
  return *this;
}

param_stddev_number& param_stddev_number::operator = (CGNU_DOUBLE m)
{
  prevariable::operator=(m);
  return *this;
}

named_dvariable& named_dvariable::operator = (CGNU_DOUBLE m)
{
  prevariable::operator=(m);
  return *this;
}

named_dvariable& named_dvariable::operator = (_CONST prevariable& m)
{
  prevariable::operator=(m);
  return *this;
}

void named_d3_array::allocate(int hsl,int hsu,int rmin,int rmax,
  int cmin,int cmax,const char * s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl,int hsu,int rmin,int rmax,
  const char * s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl,int hsu,
  const index_type& rmin,const index_type& rmax,const char * s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl,int hsu,const char * s)
{
  d3_array::allocate(hsl,hsu);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(const char * s)
{
  d3_array::allocate();
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl,int hsu,_CONST index_type& rmin,
  _CONST index_type& rmax,_CONST  index_type& cmin,
   _CONST index_type& cmax,const char * s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl,int hsu,_CONST ivector& rmin,
  int rmax,int cmin,int  cmax,const char * s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl,int hsu,int rmin,
  _CONST ivector& rmax,int cmin,int  cmax,const char * s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl,int hsu,_CONST ivector& rmin,
  _CONST ivector& rmax,int cmin,int  cmax,const char * s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl,int hsu,int rmin,int rmax,
  _CONST ivector& cmin,int cmax,const char * s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl,int hsu,int rmin,int rmax,
  int cmin,_CONST ivector& cmax,const char * s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl,int hsu,int rmin,int rmax,
  _CONST ivector& cmin,_CONST ivector& cmax,const char * s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

named_d3_array& named_d3_array::operator = (_CONST d3_array& m)
{
  d3_array::operator=(m);
  return *this;
}

data_matrix& data_matrix::operator = (_CONST dmatrix& m)
{
  named_dmatrix::operator = (m);
  return *this;
}

data_matrix& data_matrix::operator = (_CONST double& m)
{
  named_dmatrix::operator = (m);
  return *this;
}

