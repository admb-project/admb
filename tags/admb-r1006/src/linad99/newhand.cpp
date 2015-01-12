/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <admodel.h>
#if !defined(__GNUG__) 
#  include <new.h>
#else
#  if __GNUG__>=3 
#    include <iostream>
     using namespace std;

#     if __GNUG__<4 
#       include <new.h>
#     endif
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

/**
 * Description not yet available.
 * \param
 */
void ad_set_new_handler (void)
{
#if defined(__MSVC32__)   // will need to deal with different VC versions
  _set_new_handler (adnewhandler);
#else
  set_new_handler (adnewhandler);
#endif

}
#endif
