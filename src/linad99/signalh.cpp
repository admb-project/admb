/*
 * $Id: signalh.cpp 542 2012-07-10 21:04:06Z johnoel $
 * 
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
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
