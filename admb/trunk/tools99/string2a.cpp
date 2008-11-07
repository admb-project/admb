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
#include <string.h>
#include <stdlib.h>
#include <safe_mem.h>

  line_adstring& line_adstring::operator = (_CONST adstring& s)
  {
   this->adstring::operator =(s);
   return *this;
  }

  line_adstring& line_adstring::operator = (_CONST char * s)
  {
    this->adstring::operator =(s);
    return *this;
  }
