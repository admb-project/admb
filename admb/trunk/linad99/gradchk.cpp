/**
  * $Id:   $
  *
  * $Rev   ::                       $: Revision of last commit
  * $Author::                       $: Author of last commit
  * $Date  ::                       $: Date of last commit
  *
  * Author: David Fournier
  * Copyright (c) 2008 Regents of the University of California 
  */
#include <fvar.hpp>
void grad_chk(void)
{

  if(gradient_structure::GRAD_STACK1->ptr
       <= gradient_structure::GRAD_STACK1->ptr_first)
  {
    cout << " 0 offset in gradstack " << endl;
  }    // current is one past the end so -- it
  else
  {
    cout << int(gradient_structure::GRAD_STACK1->ptr)
       -int(gradient_structure::GRAD_STACK1->ptr_first)
     << " offset in gradstack " << endl;
  }
}

