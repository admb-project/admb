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
#include <fvar.hpp>

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
#if defined(__SUNPRO_CC) && defined(__x86_64)
    cout << long(gradient_structure::GRAD_STACK1->ptr)
       -long(gradient_structure::GRAD_STACK1->ptr_first)
#else
    cout << int(gradient_structure::GRAD_STACK1->ptr)
       -int(gradient_structure::GRAD_STACK1->ptr_first)
#endif
     << " offset in gradstack " << endl;
  }
}
