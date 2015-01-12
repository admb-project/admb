/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#include <admodel.h>




  vector_kludge::vector_kludge(const param_init_number_vector & _v) : 
    dvar_vector()
  {
    param_init_number_vector & v = (param_init_number_vector &) _v; 
    int mmin=v.indexmin();
    int mmax=v.indexmax();
    dvar_vector::allocate(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i)=v(i);
    }
  }
    
  vector_kludge::vector_kludge(const param_init_bounded_number_vector & _v) : 
    dvar_vector()
  {
    param_init_number_vector & v = (param_init_number_vector &) _v; 
    int mmin=v.indexmin();
    int mmax=v.indexmax();
    dvar_vector::allocate(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i)=v(i);
    }
  }
    

  matrix_kludge::matrix_kludge(const param_init_vector_vector & _v) : 
    dvar_matrix()
  {
    param_init_vector_vector & v = (param_init_vector_vector &) _v; 
    int mmin=v.indexmin();
    int mmax=v.indexmax();
    dvar_matrix::allocate(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i).shallow_copy(v(i));
    }
  }
    
  matrix_kludge::matrix_kludge(const param_init_bounded_vector_vector & _v) : 
    dvar_matrix()
  {
    param_init_bounded_vector_vector & v = (param_init_bounded_vector_vector &) _v; 
    int mmin=v.indexmin();
    int mmax=v.indexmax();
    dvar_matrix::allocate(mmin,mmax);
    for (int i=mmin;i<=mmax;i++)
    {
      (*this)(i).shallow_copy(v(i));
    }
  }
    


// 
//   ostream& operator <<  (const ostream& _s, const param_init_number_vector v)
//   {
//     ostream & s = (ostream &)(_s);
//     int mmin=v.indexmin(); 
//     int mmax=v.indexmax(); 
//     for (int i=mmin;i<=mmax;i++)
//     {
//       s << v(i) << endl;
//     }
//     return s;
//   }
// 
//   ostream& operator <<  (const ostream& _s, const param_init_bounded_number_vector v)
//   {
//     ostream & s = (ostream &)(_s);
//     int mmin=v.indexmin(); 
//     int mmax=v.indexmax(); 
//     for (int i=mmin;i<=mmax;i++)
//     {
//       s << v(i) << endl;
//     }
//     return s;
//   }
// 
//   ostream& operator <<  (const ostream& _s, const param_init_vector_vector v)
//   {
//     ostream & s = (ostream &)(_s);
//     int mmin=v.indexmin(); 
//     int mmax=v.indexmax(); 
//     for (int i=mmin;i<=mmax;i++)
//     {
//       s << v(i) << endl;
//     }
//     return s;
//   }
// 
//   ostream& operator <<  (const ostream& _s, const param_init_bounded_vector_vector v)
//   {
//     ostream & s = (ostream &)(_s);
//     int mmin=v.indexmin(); 
//     int mmax=v.indexmax(); 
//     for (int i=mmin;i<=mmax;i++)
//     {
//       s << v(i) << endl;
//     }
//     return s;
//   }
// 
//   ostream& operator <<  (const ostream& _s, const param_init_matrix_vector v)
//   {
//     ostream & s = (ostream &)(_s);
//     int mmin=v.indexmin(); 
//     int mmax=v.indexmax(); 
//     for (int i=mmin;i<=mmax;i++)
//     {
//       s << v(i) << endl;
//     }
//     return s;
//   }
// 
//   ostream& operator <<  (const ostream& _s, const param_init_bounded_matrix_vector v)
//   {
//     ostream & s = (ostream &)(_s);
//     int mmin=v.indexmin(); 
//     int mmax=v.indexmax(); 
//     for (int i=mmin;i<=mmax;i++)
//     {
//       s << v(i) << endl;
//     }
//     return s;
//   }
