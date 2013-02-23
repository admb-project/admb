/*
 * $Id: str_aio.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
#include <fvar.hpp>
#include <cifstrem.h>

 ifstream& operator >> (ifstream& ifs,adstring_array& sa)
 {
   if (sa.ptr)
   {
     int min=sa.indexmin();
     int max=sa.indexmax();
     for (int i=min;i<=max;i++)
     {
       ifs >> sa[i];
     }
   }
   return ifs;
 }
 
 ostream& operator<<(const ostream& _ofs, const adstring_array& sa)
 {
   ostream& ofs = (ostream&) _ofs;
   if (sa.ptr)
   {
     int min=sa.indexmin();
     int max=sa.indexmax();
     for (int i=min;i<=max;i++)
     {
       ofs << sa[i];
       if (i<max) ofs << endl;
     }
   }
   return ofs;
 }
 cifstream& operator >> (cifstream& ifs,adstring_array& sa)
 {
   if (sa.ptr)
   {
     int min=sa.indexmin();
     int max=sa.indexmax();
     for (int i=min;i<=max;i++)
     {
       ifs >> sa[i];
     }
   }
   return ifs;
 }
