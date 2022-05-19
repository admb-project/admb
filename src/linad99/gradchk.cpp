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
#include <stdint.h>

/**
 * Description not yet available.
 * \param
 */
void grad_chk(void)
{
  gradient_structure* gs = gradient_structure::get();
  if(gs->GRAD_STACK1->ptr <= gs->GRAD_STACK1->ptr_first)
  {
    cout << " 0 offset in gradstack " << endl;
  }    // current is one past the end so -- it
  else
  {
#if (defined(__GNUC__) && defined(__i386)) || (defined(_MSC_VER) && defined(_M_IX86))
    cout << int(gs->GRAD_STACK1->ptr) - int(gs->GRAD_STACK1->ptr_first)
#else
    cout << intptr_t(gs->GRAD_STACK1->ptr) - intptr_t(gs->GRAD_STACK1->ptr_first)
#endif
     << " offset in gradstack " << endl;
  }
}
