/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <admodel.h>

  double_index_type::double_index_type(const double_index_type& pit)
  {
    p=pit.p;
    (*(p->ncopies))++;
  }

  ad_double::ad_double(const double_index_type& it) : d(it.ddouble()) {}

  double_index_guts * dmatrix_index::operator [] (int i)
  {
    return new dvector_index(dmatrix::operator [](i));
  }
 
  double double_index_type::ddouble(void) const
  {
    return double(*p);
  }
  /*
  index_type::index_type(const data_int& x)
  {
    p = new number_index(int(data_int(x)));
  }
   */
  double_index_type::double_index_type(double x)
  {
    p = new double_index(x);
  }
  double_index_type::double_index_type(BOR_CONST dvector& x)
  {
    p = new dvector_index((BOR_CONST dvector&)(x));
  }
  double_index_type::double_index_type(BOR_CONST dmatrix& x)
  {
    p = new dmatrix_index((BOR_CONST dmatrix&)(x));
  }
  
  dmatrix_index::~dmatrix_index()
  {
    //cout << "in ~matrix_index()" << endl;
  }

  double_index_type::double_index_type(BOR_CONST  d3_array& x)
  {
    p = new d3_index((d3_array&)(x));
  }
  double_index_type::double_index_type(BOR_CONST pre_double_index_type& pit)
  { 
    p = (*(*(pit.a)).p)[pit.i];
  // Dave uncommented this august 1998 because program crashed
   // (*p->ncopies)++;
  }

  double_index_type double_index_type::operator [] (int i) const 
  { 
    return pre_double_index_type(this,i);
  }
  double_index_type double_index_type::operator () (int i) const 
  { 
    return pre_double_index_type(this,i);
  }
  double_index_type double_index_type::operator [] (int i) 
  { 
    return pre_double_index_type(this,i);
  }
  double_index_type double_index_type::operator () (int i) 
  { 
    return pre_double_index_type(this,i);
  }

  dvector_index::~dvector_index() {}

  double_index_type::~double_index_type () 
  { 
    if (!p)
    {
      cerr << "trying to delete a NULL optr in ~double_index_type()"  << endl;
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

double_index_guts::~double_index_guts()
{ 
  if (!(*ncopies)) 
  {
    delete ncopies; 
    ncopies=NULL;
  }
}


dvector_index::dvector_index(BOR_CONST dvector& v) : dvector(v)
{
  //xxjj();
}


double_index_guts::double_index_guts()
{
  ncopies = new int;
  *ncopies=0;
}

double_index_guts::double_index_guts(const double_index_guts& ig)
{
  ncopies = ig.ncopies;
  (*ncopies)++;
}

double_index_guts * double_index::operator [] (int i)
{
  return new double_index(double(*this));
}
