/*
 * $Id: signalh.cpp 946 2011-01-12 23:52:45Z johnoel $
 * 
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <fvar.hpp>
#if defined(__cpluscplus)
extern "C" {
#endif

/**
 * Description not yet available.
 * \param
 */
void exit_handler(int k)
{
  exit(1);
}

#if defined(__cpluscplus)
}
#endif
