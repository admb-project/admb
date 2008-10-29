#include <admodel.h>

 //char cc[43]={"Copyright (c) 1993,1994 Otter Research Ltd"};

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


#undef HOME_VERSION
