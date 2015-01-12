/**
 * $Id$
 * 
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>
#if defined(__cpluscplus)
extern "C" {
#endif

void exit_handler(int k)
{
  exit(1);
}

#if defined(__cpluscplus)
}
#endif

