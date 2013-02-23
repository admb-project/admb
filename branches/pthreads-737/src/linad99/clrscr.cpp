/*
 * $Id: clrscr.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#if  defined(__linux__) 
  void clrscr(void){;}
#endif

#if defined(__GNUDOS__) && !defined(__linux__) 
  extern "C" void clrscr(void){;}
#elif defined(__MSVC32__)
  void __cdecl clrscr(void){;}
#endif
