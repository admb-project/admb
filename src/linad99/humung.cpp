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
// file fvar.cpp
// constructors, destructors and misc functions involving class prevariable
#include "fvar.hpp"

#if defined(__ZTC__)
//  void _far * _cdecl _farptr_norm(void _far *);
  void _far * _cdecl _farptr_fromlong(unsigned long);
  long _cdecl _farptr_tolong(void _far *);
#endif

/**
Default constructor
*/
humungous_pointer::humungous_pointer():
  adjustment(0),
  ptr(NULL)
{
}

/**
 * Description not yet available.
 * \param
 */
void humungous_pointer::free()
{
  ptr -= adjustment;
  adjustment = 0;
#if defined(__BORLANDC__) || defined(__ZTC__)
  farfree(ptr);
#else
  ::free(ptr);
#endif
  ptr = NULL;
}

/**
 * Description not yet available.
 * \param
 */
void humungous_pointer::adjust(const size_t a)
{
  adjustment = a;
  ptr += adjustment;
}

/**
 * Description not yet available.
 * \param
 */
int humungous_pointer::operator == (void * p)
{
  return (ptr==p);
}

/**
 * Description not yet available.
 * \param
 */
int humungous_pointer::operator != (void * p)
{
  return (ptr!=p);
}

/**
 * Description not yet available.
 * \param
 */
humungous_pointer::operator char* ()
{
  return ptr;
}

/**
 * Description not yet available.
 * \param
 */
humungous_pointer::operator void* ()
{
  return (void*)ptr;
}

/**
 * Description not yet available.
 * \param
 */
humungous_pointer::operator double_and_int* ()
{
  return (double_and_int*)ptr;
}

/**
 * Description not yet available.
 * \param
 */
humungous_pointer::operator double* ()
{
  return (double*)ptr;
}

/**
Note that pointer addition is in bytes not the size of the object pointed to
*/
humungous_pointer humungous_pointer::operator + (unsigned long int& offset)
{
  humungous_pointer tmp;
#if defined(__ZTC__)
  tmp.ptr=(char*)(_farptr_fromlong(_farptr_tolong(ptr)+offset));
#else
  tmp.ptr=(ptr+offset);
#endif
  return tmp;
}

/**
Note that pointer addition is in bytes not the size of the object pointed to
*/
humungous_pointer& humungous_pointer::operator += (unsigned long int& offset)
{
#if defined(__ZTC__)
  ptr=(char*)(_farptr_fromlong(_farptr_tolong(ptr)+offset));
#else
  ptr=(ptr+offset);
#endif
  return *this;
}

/**
 * Description not yet available.
 * \param
 */
humungous_pointer& humungous_pointer::operator = (void * p)
{
#if defined(__BORLANDC__)
  ptr = (char huge *) p;
#else
  ptr = (char*) p;
#endif
  return *this;
}
