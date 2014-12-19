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
#if defined(_MSC_VER)
  void __cdecl clrscr(){}
#else
  extern "C" void clrscr(){}
#endif
