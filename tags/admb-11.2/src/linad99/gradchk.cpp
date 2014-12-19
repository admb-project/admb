/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>
#if defined(__x86_64)
  #include <stdint.h>
#endif

/**
 * Description not yet available.
 * \param
 */
void grad_chk(void)
{
  if(gradient_structure::GRAD_STACK1->ptr
       <= gradient_structure::GRAD_STACK1->ptr_first)
  {
    cout << " 0 offset in gradstack " << endl;
  }    // current is one past the end so -- it
  else
  {
#if defined(__x86_64)
    cout << intptr_t(gradient_structure::GRAD_STACK1->ptr)
            - intptr_t(gradient_structure::GRAD_STACK1->ptr_first)
#else
    cout << int(gradient_structure::GRAD_STACK1->ptr)
       -int(gradient_structure::GRAD_STACK1->ptr_first)
#endif
     << " offset in gradstack " << endl;
  }
}
