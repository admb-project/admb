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
#define HOME_VERSION

#if  defined(__linux__) 
  void clrscr(void){;}
#endif

#if defined(__GNUDOS__) && !defined(__linux__) 
  extern "C" void clrscr(void){;}
#elif defined(__MSVC32__)
  void __cdecl clrscr(void){;}
#endif

#undef HOME_VERSION
