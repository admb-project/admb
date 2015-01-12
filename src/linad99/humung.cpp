/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

// file fvar.cpp
// constructors, destructors and misc functions involving class prevariable 
#define DOS386

#include "fvar.hpp"


#if (defined(__ZTC__) && !defined(DOS386))
//  void _far * _cdecl _farptr_norm(void _far *);
  void _far * _cdecl _farptr_fromlong(unsigned long);
  long _cdecl _farptr_tolong(void _far *);
#endif

void humungous_pointer::free(void)
{
  ptr-=adjustment;
  adjustment=0;
  #if (defined(__BORLANDC__))
    #if (!defined(DOSX286) && !defined(DOS386))
      farfree(ptr);
    #else
      ::free(ptr);
    #endif
  #endif
  #if (defined(__ZTC__))
    #if (!defined(DOS386))
      farfree(ptr);
    #else
      ::free(ptr);
    #endif
  #endif
  #if (!defined(__BORLANDC__)&& !defined(__ZTC__))
    ::free(ptr);
  #endif
  ptr=NULL;
}
void humungous_pointer::adjust(int a)
{
  ptr+=a;
  adjustment=a;
  //ptr=NULL;
}
humungous_pointer::humungous_pointer()
{
  adjustment=0;
  //ptr=NULL;
}
int humungous_pointer::operator == (void * p) 
{ 
  return (ptr==p);
}
int humungous_pointer::operator != (void * p) 
{
  return (ptr!=p);
}
humungous_pointer::operator char* () 
{
  return ptr;
}
humungous_pointer::operator void* () 
{
  return (void *) ptr;
}
humungous_pointer::operator double_and_int* ()
{
  return (double_and_int *)ptr;
}
humungous_pointer::operator double* ()
{
  return (double *)ptr;
}


humungous_pointer humungous_pointer::operator + (unsigned long int& offset)
// Note that pointer addition is in bytes not the size of the
// object pointed to
{
  humungous_pointer tmp;
  #if (defined(__ZTC__) && !defined(DOS386))
    tmp.ptr=(char*)(_farptr_fromlong(_farptr_tolong(ptr)+offset));
  #else
    tmp.ptr=(ptr+offset);
  #endif
  return tmp;
}

humungous_pointer& humungous_pointer::operator += (unsigned long int& offset)
// Note that pointer addition is in bytes not the size of the
// object pointed to
{
  char * tmp;
  #if (defined(__ZTC__) && !defined(DOS386))
    ptr=(char*)(_farptr_fromlong(_farptr_tolong(ptr)+offset));
  #else
    ptr=(ptr+offset);
  #endif
  return *this;
}

humungous_pointer& humungous_pointer::operator = (void * p)
{
  #if defined(__BORLANDC__) && !defined(DOS386)
    ptr = (char huge *) p;
  #else
    ptr = (char *) p;
  #endif
  return *this; 
}  
        
