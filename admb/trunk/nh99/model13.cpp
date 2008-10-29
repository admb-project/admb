#include <admodel.h>

 //char cc[43]={"Copyright (c) 1993,1994 Otter Research Ltd"};

  void initial_params::restore(BOR_CONST ifstream& ofs)
  {
    for (int i=0;i<num_initial_params;i++)
    {
		 (varsptr[i])->restore_value(ofs);
    }
  }

  void param_init_number::restore_value(BOR_CONST ifstream& ofs)
  {
    #ifndef __ZTC__
      ofs  >> dvariable(*this);
    #else
      ofs  >> *this;
    #endif
  }

  void param_init_vector::restore_value(BOR_CONST ifstream& ofs)
  {
    ofs  >> dvar_vector(*this);
  }

  void param_init_bounded_vector::restore_value(BOR_CONST ifstream& ofs)
  {
    ofs  >> dvar_vector(*this);
  }

  void param_init_matrix::restore_value(BOR_CONST ifstream& ofs)
  {
    ofs  >> dvar_matrix(*this);
  }


#undef HOME_VERSION

