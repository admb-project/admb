/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <admodel.h>


#if !defined(OPT_LIB)
   param_init_vector& param_init_vector_vector::operator [] (int i) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_vector_vector operator []"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_vector_vector operator []"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i];
   }
   param_init_vector& param_init_vector_vector::operator () (int i) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_vector_vector operator ()"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_vector_vector operator ()"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i];
   }
   prevariable param_init_vector_vector::operator () (int i,int j) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_vector_vector operator ()"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_vector_vector operator ()"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
#if defined(__BORLANDC__)
#  if (__BORLANDC__  >= 0x0540) 
     return (prevariable&) (v[i][j]);
#  else
     return v[i][j];
#  endif
#else
#  if ( defined(linux) && __GNUC__ < 4)
     return (prevariable&) (v[i][j]);
#  else
     return v[i][j];
#  endif
#endif
   }
   param_init_matrix& param_init_matrix_vector::operator [] (int i) 
   {
     if (i<indexmin()) {
       cerr << "Index too low in param_init_matrix_vector operator []"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_matrix_vector operator []"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i];
   }
   param_init_matrix& param_init_matrix_vector::operator () (int i) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_matrix_vector operator ()"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_matrix_vector operator ()"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i];
   }
   dvar_vector& param_init_matrix_vector::operator () (int i,int j) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_matrix_vector operator ()"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_matrix_vector operator ()"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i][j];
   }
   prevariable param_init_matrix_vector::operator () (int i,int j,int k) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_matrix_vector operator ()"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_matrix_vector operator ()"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
#if defined(__BORLANDC__)
#  if (__BORLANDC__  >= 0x0540) 
     return (prevariable&) (v[i](j,k));
#  else
     return v[i](j,k);
#  endif
#else
#  if ( defined(linux) && __GNUC__ < 4)
     return (prevariable&) v[i](j,k);
#  else
     return v[i](j,k);
#  endif
#endif
   }
   param_init_bounded_vector& param_init_bounded_vector_vector::operator [] 
     (int i) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_bounded_vector_vector operator []"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_bounded_vector_vector operator []"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i];
   }
   param_init_bounded_vector& param_init_bounded_vector_vector::operator () 
     (int i) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_bounded_vector_vector operator ()"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_bounded_vector_vector operator ()"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i];
   }
   prevariable param_init_bounded_vector_vector::operator () (int i,int j) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_bounded_vector_vector operator ()"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_bounded_vector_vector operator ()"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
#if defined(__BORLANDC__)
#  if (__BORLANDC__  >= 0x0540) 
     return (prevariable&) (v[i][j]);
#  else
     return v[i][j];
#  endif
#else
#  if ( defined(linux) && __GNUC__ < 4)
     return (prevariable&) (v[i][j]);
#  else
     return v[i][j];
#  endif
#endif
   }

   param_init_bounded_matrix& param_init_bounded_matrix_vector::operator [] (int i) 
   {
     if (i<indexmin()) {
       cerr << "Index too low in param_init_bounded_matrix_vector operator []"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_bounded_matrix_vector operator []"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i];
   }
   param_init_bounded_matrix& param_init_bounded_matrix_vector::operator () (int i) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_bounded_matrix_vector operator ()"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_bounded_matrix_vector operator ()"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i];
   }
   dvar_vector& param_init_bounded_matrix_vector::operator () (int i,int j) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_bounded_matrix_vector operator ()"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_bounded_matrix_vector operator ()"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i][j];
   }
   prevariable param_init_bounded_matrix_vector::operator () (int i,int j,int k) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_bounded_matrix_vector operator ()"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_bounded_matrix_vector operator ()"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
#if defined(__BORLANDC__)
#  if (__BORLANDC__  >= 0x0540) 
     return (prevariable&) (v[i](j,k));
#  else
     return v[i](j,k);
#  endif
#else
#  if ( defined(linux) && __GNUC__ < 4)
     return (prevariable&) v[i](j,k);
#  else
     return v[i](j,k);
#  endif
#endif
   }

   param_init_number& param_init_number_vector::operator [] (int i) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_number_vector operator []"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_number_vector operator []"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i];
   }
   param_init_number& param_init_number_vector::operator () (int i) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_number_vector operator ()"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_number_vector operator ()"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i];
   }

   param_init_bounded_number& param_init_bounded_number_vector::operator [] (int i) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_bounded_number_vector operator []"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_bounded_number_vector operator []"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i];
   }
   param_init_bounded_number& param_init_bounded_number_vector::operator () (int i) 
   { 
     if (i<indexmin()) {
       cerr << "Index too low in param_init_bounded_number_vector operator ()"
         " value " << i << " minimum " << indexmin() << endl;
       ad_exit(1); 
     }
     if (i>indexmax()) {
       cerr << "Index too high in param_init_bounded_number_vector operator ()"
         " value " << i << " minimum " << indexmax() << endl;
       ad_exit(1); 
     }
     return v[i];
   }
#endif
