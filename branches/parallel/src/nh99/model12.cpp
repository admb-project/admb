/*
 * $Id: model12.cpp 945 2011-01-12 23:03:57Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

  void initial_params::save(BOR_CONST ofstream& _ofs,int prec)
  {
    ofstream& ofs=(ofstream&) _ofs;
    ofs << setw(prec+6) << setshowpoint();
    for (int i=0;i<num_initial_params;i++)
    {
      (varsptr[i])->save_value(ofs,prec);
    }
  }

  void param_init_number::save_value(BOR_CONST ofstream& _ofs,int prec)
  {
    ofstream& ofs=(ofstream&) _ofs;
    #ifndef __ZTC__
      ofs << setprecision(prec) << dvariable(*this) << endl;
    #else
      ofs << setw(prec+6) << setprecision(prec) << *this << endl;
    #endif
  }

  void param_init_vector::save_value(BOR_CONST ofstream& _ofs,int prec)
  {
    ofstream& ofs=(ofstream&) _ofs;
    ofs << setw(prec+6) << setprecision(prec) << dvar_vector(*this) << endl;
  }

  void param_init_bounded_vector::save_value(BOR_CONST ofstream& _ofs,int prec)
  {
    ofstream& ofs=(ofstream&) _ofs;
    ofs << setw(prec+6) << setprecision(prec) << dvar_vector(*this) << endl;
  }

  void param_init_matrix::save_value(BOR_CONST ofstream& _ofs,int prec)
  {
    ofstream& ofs=(ofstream&) _ofs;
    ofs << setw(prec+6) << setprecision(prec) << dvar_matrix(*this) << endl;
  }
