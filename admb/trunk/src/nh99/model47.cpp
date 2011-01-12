/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

 void param_init_number_vector::set_initial_value(const double_index_type& _it)
 {
    it=new double_index_type(_it);
 }
 param_init_number_vector::param_init_number_vector()
 {
   it=NULL;
 }
     
 param_init_number_vector::~param_init_number_vector()
 {
   deallocate();
 }

 void param_init_number_vector::deallocate(void)
 {
   if(it)
   {
     delete it;
     it=NULL;
   }
   if (v)
   {
     v+=indexmin();
     delete [] v;
     v=NULL;
   }
 }


 void param_init_number_vector::allocate(int min1,int max1,
   const char * s)
 {
   allocate(min1,max1,1,s);
 }

 void param_init_number_vector::allocate(int min1,int max1,
   const index_type& phase_start,const char * s)
 {
   index_min=min1;
   index_max=max1;
   int size=indexmax()-indexmin()+1;
   if (size>0)
   {
     if (!(v=new param_init_number[size]))
     {
        cerr << " error trying to allocate memory in "
          "param_init_vector_vector " << endl;
        exit(1);
     }
     v-=indexmin();
     for (int i=indexmin();i<=indexmax();i++)
     {
       if (it) v[i].set_initial_value(ad_double((*it)[i]));
       adstring ss=s + adstring("[") + str(i) + adstring("]");
       v[i].allocate(ad_integer(phase_start[i]),(char*)(ss) );
     }
   }
   else
     v=NULL;
 }


