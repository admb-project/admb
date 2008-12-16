/*
 * $Id$
 * Author: David Fournier
 * Copyright (c) 2008 Regents of the University of California 
 */

#include <admodel.h>
#if !defined(__GNUG__) 
#  include <new.h>
#else
#  if __GNUG__>=3 
#    include <new.h>
#  endif
#endif

#if !defined(__GNUG__) ||   (defined(__GNUG__) && __GNUG__>=3) 
extern "C"  {
#if defined(__MSVC32__)   // will need to deal with different VC versions
 int adnewhandler(size_t i)
#else
    void adnewhandler(void)
#endif
{
   cout << "Memory allocation error -- Perhaps you are trying to allocate too" 
     " much memory in your program "<< endl;
   ad_exit(1);
#if defined(__MSVC32__)   // will need to deal with different VC versions
   return 0;
#else
   return;
#endif
}
} // extern "C"

void ad_set_new_handler (void)
{
#if defined(__MSVC32__)   // will need to deal with different VC versions
  _set_new_handler (adnewhandler);
#else
  set_new_handler (adnewhandler);
#endif

}
#endif
