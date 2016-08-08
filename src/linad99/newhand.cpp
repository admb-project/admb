/**
Author: David Fournier
Copyright (c) 2008-2012 Regents of the University of California
*/

#if defined(__GNUC__) && (__GNUC__ < 4)
  #include <iostream.h>
  #include <new.h>
#elif defined(_MSC_VER)
  #include <iostream>
  #include <new.h>
#else
  #include <iostream>
  using namespace std;
  #include <new>
#endif

#include <admodel.h>

extern "C"  {

#if defined(_MSC_VER)   // will need to deal with different VC versions
int adnewhandler(size_t i)
#else
void adnewhandler(void)
#endif
{
   cout << "Memory allocation error -- Perhaps you are trying to allocate too"
     " much memory in your program "<< endl;
   ad_exit(1);
#if defined(_MSC_VER)   // will need to deal with different VC versions
   return 0;
#endif
}

} // extern "C"

/**
 * Description not yet available.
 * \param
 */
void ad_set_new_handler (void)
{
#if defined(_MSC_VER)   // will need to deal with different VC versions
  _set_new_handler (adnewhandler);
#else
  set_new_handler (adnewhandler);
#endif
}
