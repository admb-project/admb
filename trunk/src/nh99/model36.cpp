/*
 * $Id: model36.cpp 945 2011-01-12 23:03:57Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include <admodel.h>

void named_adstring::allocate(const char * s1,const char * _s)
{
  model_name_tag::allocate(_s);
  (*this)=s1;
}

void named_adstring::operator = (const char * _s)
{
  adstring::operator = (_s);
}

void named_adstring::operator = (const adstring& _s)
{
  adstring::operator = (_s);
}

void dll_named_adstring::operator = (const char * _s)
{
  adstring::operator = (_s);
}

void dll_named_adstring::operator = (const adstring& _s)
{
  adstring::operator = (_s);
}

void dll_named_adstring::allocate(char ** ps1,const char * _s)
{
  named_adstring::allocate(*ps1,_s);
}    

dll_named_adstring::~dll_named_adstring()
{
  strcpy(*d,(char*)(*this));
}
