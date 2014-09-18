/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "New BSD" license
 *
 * License:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2.  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3.  Neither the name of the  University of California, Otter Research,
 * nor the ADMB Foundation nor the names of its contributors may be used
 * to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef __ADSTRING_HPP__
#define __ADSTRING_HPP__

#include "clist.h"
#include <string.h>
//#include <fvar.hpp>
#include <ostream>

#include <stdio.h>

class adstring_shape
{
  unsigned int sz;
protected :
  friend class adstring;
  adstring_shape(unsigned int n)
  {
    sz = n;
  }
  unsigned int & size()
  {
    return (sz);
  }
};

class adstring_array;

class adstring : public clist
{
  adstring_shape * shape;
#if (defined __ZTC__) || (defined __NDPX__)
  char * s;
#else
  unsigned char * s;
#endif
  void allocate(int sz);
  void deallocate(void);
  friend class adstring_array;
public :
  friend std::ostream & operator<<(std::ostream & c, const adstring & t);
  friend std::istream & operator >> (std::istream & c, adstring & t);

  adstring(const char *t);
  void allocate(const char *t);
  adstring(int lb, int ub);
  adstring(const adstring &v);
  void realloc(const char * t);
  //adstring(const unsigned char v);
  adstring(const char v);
  adstring(void);
  ~adstring();
  unsigned int size(void) const;
  unsigned int buff_size(void);
  unsigned char &operator()(const int i);
  unsigned char &operator[](const int i);
  const unsigned char& operator()(const int i) const;
  const unsigned char& operator[](const int i) const;

#ifdef __INTEL_COMPILER
  friend adstring operator+(const adstring &u, const char* v)
  {
    adstring a(v);
    return u + a;
  }
#endif

  friend adstring operator+(const adstring &u, const adstring &v);

  friend adstring operator+(const adstring &u, const unsigned char v);

  friend adstring operator+(const adstring &u, const signed char v);

  friend adstring operator+(const adstring &u, const unsigned char *v);

  friend adstring operator+(const adstring & u, const signed char *v);

  friend adstring operator+(const unsigned char *v, const adstring& u);

  friend adstring operator+(const char *v, const adstring &u);

  friend adstring operator+(const unsigned char u, const adstring &v);

  adstring& operator+=(const adstring &u);
  inline adstring& operator+=(const char u)
    { return(*this += adstring(u)); }

  int operator==(const adstring &u);

  inline int operator == (const char* u)
    { return *this == adstring(u); }

  inline int operator!=(const adstring &u)
    { return(!(*this==u)); }

  adstring operator()(int i, int j);
  int operator==(const char* u) const;

  int operator==(const adstring &u) const;
  adstring operator()(int i, int j) const;

  adstring& operator=(const adstring &t);
  adstring& operator=(const char t);
   // { return (*this = adstring(t)); }

  operator unsigned char * ();
  operator char * ();
  operator const unsigned char*() const;
  operator const char*() const;

  // Pascal-like adstring functions

  // returns the starting position of substr
  int pos(const adstring& substr) const;

  // converts a double into a adstring
  friend adstring str(double x, int minwidth, int decplaces);
  friend adstring str(const int x);
  friend void val(const adstring& s, int& v, int& code);
  friend int val(const adstring& s);

  void to_upper(void);
  void to_lower(void);
  adstring to_upper(adstring& s);
  adstring to_lower(adstring& s);
};
adstring to_lower(adstring& s);
adstring to_upper(adstring& s);
adstring str(double x, int minwidth=17, int decplaces=-1);
adstring str(const int x);
void val(const adstring& s, int& v, int& code);
int val(const adstring& s);

class cifstream;

class line_adstring : public adstring
{
public:
  line_adstring(void) : adstring() {}
  line_adstring(const adstring& s) : adstring(s) {}
  line_adstring& operator=(const adstring& s);
  line_adstring& operator=(const char *s);
  friend std::istream & operator >> (std::istream & c, line_adstring & t);
};

adstring itoa(int n,int d);

void str(const int, adstring&);
adstring chr(int c);
int length(const adstring& t);
int pos(const adstring& substr, const adstring& s);

//adstring operator+(const char u, const char v)
//  { return (adstring(u) + adstring(v) ); }
#if defined(__BORLANDC__)
#  if (__BORLANDC__  <= 0x0520)
     class ifstream;
     class ofstream;
     class cifstream;
#  endif
#endif

class vector_shape;

class adstring_array : public clist
{
  vector_shape* shape;
  adstring** ptr;
public:
  int size() const;
  int indexmin(void) const;
  int indexmax(void) const;
  adstring_array(const adstring_array& sa);
  ~adstring_array();
  adstring_array(int min,int max);
  void allocate(int min,int max);
  adstring_array(void);
  const adstring& operator[](int i) const;
  const adstring& operator()(int i) const;
  adstring& operator [] (int i);
  adstring& operator () (int i);
  adstring_array& operator += (const adstring& s);
  adstring_array& append_distinct(const adstring& s);
  friend std::ifstream& operator >> (std::ifstream& ifs,adstring_array& sa);
  friend std::ostream& operator<<(const std::ostream& ifs,
    const adstring_array& sa);
  friend cifstream& operator >> (cifstream& ifs,adstring_array& sa);

  void to_upper(void);
  void to_lower(void);
  adstring_array to_upper(adstring_array& s);
  adstring_array to_lower(adstring_array& s);
  adstring_array& operator=(const adstring_array&);
};   // end class adstring_array
adstring_array to_lower(adstring_array& s);
adstring_array to_upper(adstring_array& s);

std::ostream& operator<<(const std::ostream& ifs, const adstring_array& sa);

int atoi(adstring& s);
#endif //#ifndef __STRING_HPP__
