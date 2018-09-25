/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#if defined(_MSC_VER)
  void __cdecl clrscr(){}
#else
  extern "C" void clrscr(){}
#endif
