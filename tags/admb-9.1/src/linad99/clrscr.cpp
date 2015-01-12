/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#if  defined(__linux__) 
  void clrscr(void){;}
#endif

#if defined(__GNUDOS__) && !defined(__linux__) 
  extern "C" void clrscr(void){;}
#elif defined(__MSVC32__)
  void __cdecl clrscr(void){;}
#endif

