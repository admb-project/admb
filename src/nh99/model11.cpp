/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

cifstream& operator>>(const cifstream&, const prevariable&);

cifstream& operator>>(const cifstream& _s, const param_init_number& x)
{
  cifstream&  s=(cifstream&) _s;
  s >> value(x);
  return s;
}

cifstream& operator>>(const cifstream& _s, const param_init_vector& _v)
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

cifstream& operator>>(const cifstream& _s, const param_init_matrix& m)
{
  cifstream&  s=(cifstream&) _s;
  s >> dvar_matrix(m);
  return s;
}

ostream& operator<<(const ostream& _s, const label_class& lc)
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
/**
Assign named_dvar_matrix with values.

\param values dvar_matrix
*/
named_dvar_matrix& named_dvar_matrix::operator=(const dvar_matrix& values)
{
  this->dvar_matrix::operator=(values);
  return *this;
}
named_dvar_matrix& named_dvar_matrix::operator=(const dmatrix& m)
{
  this->dvar_matrix::operator=(m);
  return *this;
}
/**
Assign named_dvar_matrix with value.

\param value double
*/
named_dvar_matrix& named_dvar_matrix::operator=(const double value)
{
  this->dvar_matrix::operator=(value);
  return *this;
}
/**
Assign named_dvar_matrix with value.

\param value dvariable
*/
named_dvar_matrix& named_dvar_matrix::operator=(const dvariable& values)
{
  this->dvar_matrix::operator=(values);
  return *this;
}
/**
Assign param_stddev_matrix with values.

\param values dvar_matrix
*/
param_stddev_matrix& param_stddev_matrix::operator=(const dvar_matrix& values)
{
  this->dvar_matrix::operator=(values);
  return *this;
}
/**
Assign param_stddev_matrix with values.

\param values dmatrix
*/
param_stddev_matrix& param_stddev_matrix::operator=(const dmatrix& value)
{
  this->dvar_matrix::operator=(value);
  return *this;
}
/**
Assign param_stddev_matrix with value.

\param value double
*/
param_stddev_matrix& param_stddev_matrix::operator=(const double value)
{
  this->dvar_matrix::operator=(value);
  return *this;
}

param_stddev_vector& param_stddev_vector::operator=(const dvar_vector& m)
{
  this->dvar_vector::operator=(m);
  return *this;
}

named_dvar_vector& named_dvar_vector::operator=(const dvar_vector& m)
{
  this->dvar_vector::operator=(m);
  return *this;
}
named_dvar_vector& named_dvar_vector::operator=(const dvector& m)
{
  this->dvar_vector::operator=(m);
  return *this;
}
named_dvar_vector& named_dvar_vector::operator=(const double m)
{
  this->dvar_vector::operator=(m);
  return *this;
}

named_dvar_vector& named_dvar_vector::operator=(const prevariable& m)
{
  this->dvar_vector::operator=(m);
  return *this;
}

named_dvector& named_dvector::operator=(const dvector& m)
{
  this->dvector::operator=(m);
  return *this;
}
named_dvector& named_dvector::operator=(const double m)
{
  this->dvector::operator=(m);
  return *this;
}

data_vector& data_vector::operator=(const dvector& m)
{
  this->dvector::operator=(m);
  return *this;
}
data_vector& data_vector::operator=(const double m)
{
  this->dvector::operator=(m);
  return *this;
}


param_stddev_vector& param_stddev_vector::operator=(const dvector& m)
{
  this->dvar_vector::operator=(m);
  return *this;
}
param_stddev_vector& param_stddev_vector::operator=(const double m)
{
  this->dvar_vector::operator=(m);
  return *this;
}

param_init_number& param_init_number::operator=(const double m)
{
  this->dvariable::operator=(m);
  return *this;
}

param_init_number& param_init_number::operator=(const prevariable& m)
{
  this->dvariable::operator=(m);
  return *this;
}

param_init_bounded_number& param_init_bounded_number::operator=(const double m)
{
  this->dvariable::operator=(m);
  return *this;
}

param_init_bounded_number& param_init_bounded_number::operator=(
  const prevariable& m)
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

void named_dvar3_array::allocate(int hsl, int hsu, const ivector& rmin,
  int rmax, int cmin, int cmax, const char *s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_dvar3_array::allocate(int hsl,int hsu,int rmin,
  const ivector& rmax, int cmin, int cmax, const char *s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_dvar3_array::allocate(int hsl, int hsu, const ivector& rmin,
  const ivector& rmax, int cmin, int cmax, const char *s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}


void named_dvar3_array::allocate(int hsl, int hsu, int rmin, int rmax,
  const ivector& cmin, int cmax, const char *s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_dvar3_array::allocate(int hsl, int hsu, int rmin, int rmax,
  const ivector& cmin, const ivector&  cmax, const char *s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_dvar3_array::allocate(int hsl, int hsu, int rmin, int rmax,
  int cmin, const ivector& cmax, const char *s)
{
  dvar3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

named_dvar3_array& named_dvar3_array::operator=(const dvar3_array& m)
{
  this->dvar3_array::operator=(m);
  return *this;
}



named_dvar3_array& named_dvar3_array::operator=(const d3_array& m)
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
/**
Assign named_dmatrix with values.

\param values dmatrix
*/
named_dmatrix& named_dmatrix::operator=(const dmatrix& values)
{
  dmatrix::operator=(values);
  return *this;
}
/**
Assign named_dmatrix with value.

\param value double
*/
named_dmatrix& named_dmatrix::operator=(const double value)
{
  dmatrix::operator=(value);
  return *this;
}

param_stddev_number& param_stddev_number::operator=(const prevariable& m)
{
  prevariable::operator=(m);
  return *this;
}

param_stddev_number& param_stddev_number::operator=(const double m)
{
  prevariable::operator=(m);
  return *this;
}

named_dvariable& named_dvariable::operator=(const double m)
{
  prevariable::operator=(m);
  return *this;
}

named_dvariable& named_dvariable::operator=(const prevariable& m)
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

void named_d3_array::allocate(int hsl, int hsu, const index_type& rmin,
  const index_type& rmax, const index_type& cmin,
  const index_type& cmax, const char *s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl, int hsu, const ivector& rmin,
  int rmax,int cmin,int  cmax,const char * s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl,int hsu,int rmin,
  const ivector& rmax, int cmin, int  cmax, const char *s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl, int hsu, const ivector& rmin,
  const ivector& rmax,int cmin,int  cmax,const char * s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl, int hsu, int rmin, int rmax,
  const ivector& cmin, int cmax, const char *s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl, int hsu, int rmin, int rmax,
  int cmin, const ivector& cmax, const char *s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

void named_d3_array::allocate(int hsl, int hsu, int rmin, int rmax,
  const ivector& cmin, const ivector& cmax, const char * s)
{
  d3_array::allocate(hsl,hsu,rmin,rmax,cmin,cmax);
  model_name_tag::allocate(s);
}

named_d3_array& named_d3_array::operator=(const d3_array& m)
{
  d3_array::operator=(m);
  return *this;
}
/**
Assign data_matrix with values.

/param values dmatrix
*/
data_matrix& data_matrix::operator=(const dmatrix& values)
{
  named_dmatrix::operator=(values);
  return *this;
}
/**
Assign data_matrix with value.

/param value double
*/
data_matrix& data_matrix::operator=(const double& value)
{
  named_dmatrix::operator=(value);
  return *this;
}
