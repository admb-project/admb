/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

 void param_init_vector_vector::set_initial_value(const double_index_type& _it)
 {
    it=new double_index_type(_it);
 }
     
 param_init_vector_vector::param_init_vector_vector()
 {
   it=NULL;
 }
   
 void param_init_vector_vector::allocate(int min1,int max1,
   const index_type& min,
   const index_type& max,
   const char * s)
 {
   allocate(min1,max1,min,max,1,s);
 }

 void param_init_vector_vector::allocate(int min1,int max1,
   const index_type& min,
   const index_type& max,
   const index_type& phase_start,
   const char * s)
 {
   index_min=min1;
   index_max=max1;
   int size=indexmax()-indexmin()+1;
   if (size>0)
   {
     if (!(v=new param_init_vector[size]))
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
       v[i].allocate(min[i],max[i],phase_start[i],(char*)(ss) );
     }
   }
   else
     v=NULL;
 }

 void param_init_vector::allocate(const ad_integer& imin,
   const ad_integer&imax,const ad_integer& phase_start,
    const char * s)
 {
   named_dvar_vector::allocate(imin,imax,s);
   if (!(!(*this)))
   {
     initial_params::allocate(phase_start);
     if (ad_comm::global_bparfile)
     {
       *(ad_comm::global_bparfile) >> dvar_vector(*this);
     }
     else if (ad_comm::global_parfile)
     {
       *(ad_comm::global_parfile) >> dvar_vector(*this);
     }
     else
     {
       dvar_vector::operator=(initial_value);
     }
   }
   else
   {
     initial_params::allocate(-1);
   }
 }

   param_init_vector_vector::~param_init_vector_vector()
   {
     deallocate();
   }
  
  
   void param_init_vector_vector::deallocate(void)
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
