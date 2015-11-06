/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <admodel.h>

/**
 * Description not yet available.
 * \param
 */
  double_index_type::double_index_type(const double_index_type& pit)
  {
    p=pit.p;
    (*(p->ncopies))++;
  }

  ad_double::ad_double(const double_index_type& it) : d(it.ddouble()) {}

/**
 * Description not yet available.
 * \param
 */
  double_index_guts * dmatrix_index::operator [] (int i)
  {
    return new dvector_index(dmatrix::operator [](i));
  }

/**
 * Description not yet available.
 * \param
 */
  double double_index_type::ddouble(void) const
  {
    return double(*p);
  }

/*
index_type::index_type(const data_int& x)
{
  p = new number_index(x);
}
*/

/**
 * Description not yet available.
 * \param
 */
  double_index_type::double_index_type(double x)
  {
    p = new double_index(x);
  }

/**
 * Description not yet available.
 * \param
 */
double_index_type::double_index_type(const dvector& x)
  {
    p = new dvector_index((const dvector&)(x));
  }

/**
 * Description not yet available.
 * \param
 */
  double_index_type::double_index_type(const dmatrix& x)
  {
    p = new dmatrix_index((const dmatrix&)(x));
  }

/**
Destructor
*/
dmatrix_index::~dmatrix_index()
{
  //DoesNothing
}

/**
 * Description not yet available.
 * \param
 */
  double_index_type::double_index_type(const d3_array& x)
  {
    p = new d3_index((d3_array&)(x));
  }

/**
 * Description not yet available.
 * \param
 */
  double_index_type::double_index_type(const pre_double_index_type& pit)
  {
    p = (*(*(pit.a)).p)[pit.i];
  // Dave uncommented this august 1998 because program crashed
   // (*p->ncopies)++;
  }

/**
 * Description not yet available.
 * \param
 */
  double_index_type double_index_type::operator [] (int i) const
  {
    return pre_double_index_type(this,i);
  }

/**
 * Description not yet available.
 * \param
 */
  double_index_type double_index_type::operator () (int i) const
  {
    return pre_double_index_type(this,i);
  }

/**
 * Description not yet available.
 * \param
 */
  double_index_type double_index_type::operator [] (int i)
  {
    return pre_double_index_type(this,i);
  }

/**
 * Description not yet available.
 * \param
 */
  double_index_type double_index_type::operator () (int i)
  {
    return pre_double_index_type(this,i);
  }

/**
Destructor
*/
dvector_index::~dvector_index()
{
  //DoesNothing
}

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
double_index_guts::~double_index_guts()
{
  if (!(*ncopies))
  {
    delete ncopies;
    ncopies=NULL;
  }
}

/**
 * Description not yet available.
 * \param
 */
dvector_index::dvector_index(const dvector& v) : dvector(v)
{
}

/**
 * Description not yet available.
 * \param
 */
double_index_guts::double_index_guts()
{
  ncopies = new int;
  *ncopies=0;
}

/**
 * Description not yet available.
 * \param
 */
double_index_guts::double_index_guts(const double_index_guts& ig)
{
  ncopies = ig.ncopies;
  (*ncopies)++;
}

/**
 * Description not yet available.
 * \param
 */
double_index_guts * double_index::operator [] (int i)
{
  return new double_index(double(*this));
}
