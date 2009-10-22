/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California
 * 
 * License:
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "New BSD" license
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



#ifndef __STRING_HPP__
#define __STRING_HPP__

#if defined(__BORLANDC__ )
#  pragma interface
#endif

#include "clist.h"
#include <string.h>
#include <fvar.hpp>

#include <stdio.h>

#ifdef HERE
  #undef HERE
#endif
//#define HERE cout << "reached line " << __LINE__ << " in " << __FILE__ << endl;
#define HERE 

#define USE_CONST
#ifdef USE_CONST
  #define _CONST const
#else
  #define _CONST 
#endif
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
  friend class adstring_array;
public :
  friend ostream & operator << (ostream & c, _CONST adstring & t);
  friend istream & operator >> (istream & c, adstring & t);

  adstring(_CONST char * t);
  void allocate(_CONST char * t);
  adstring(int lb, int ub);
  adstring(_CONST adstring & v);
  void realloc(const char * t);
  //adstring(_CONST unsigned char v);
  adstring(_CONST char v);
  adstring(void);
  ~adstring();
  unsigned int size(void) _CONST;
  unsigned int buff_size(void);
  unsigned char & operator()(_CONST int i);
  unsigned char & operator[] (_CONST int i);
#ifdef USE_CONST
   const unsigned char & operator()(_CONST int i) _CONST;
  _CONST unsigned char & operator[] (_CONST int i) _CONST;
#endif

  friend adstring operator + (_CONST adstring & u,_CONST adstring & v); 

  friend adstring operator + (_CONST adstring & u, _CONST unsigned char v);

  friend adstring operator + (_CONST adstring & u, _CONST signed char v);

  friend adstring operator + (_CONST adstring & u, _CONST unsigned char * v);

  friend adstring operator + (_CONST adstring & u, _CONST signed char * v);

  friend adstring operator + (_CONST unsigned char * v,_CONST adstring& u);

  friend adstring operator + (_CONST char * v,_CONST adstring & u);

  friend adstring operator + (_CONST unsigned char u,_CONST  adstring & v);

  adstring & operator += (_CONST adstring & u);
  inline adstring & operator += (_CONST char u)
    { return(*this += adstring(u)); }

  int operator == (_CONST adstring & u) ;

  inline int operator == (const char* u)
    { return *this == adstring(u); }

  inline int operator != (_CONST adstring & u)
    { return(!(*this==u)); }

  adstring operator()(int i, int j);
  #if defined(USE_CONST)
  int operator == (_CONST char* u) _CONST;

  int operator == (_CONST adstring & u)_CONST;
    adstring operator() (int i, int j) _CONST;
  #endif 

  adstring & operator = (_CONST adstring & t);
  adstring & operator = (_CONST char t);
   // { return (*this = adstring(t)); }

  operator unsigned char * ();
  operator char * ();
#ifdef USE_CONST
  operator _CONST unsigned char * () _CONST;
   operator _CONST char * () _CONST;
#endif

  // Pascal-like adstring functions

  int pos(_CONST adstring& substr) _CONST;  // returns the starting position of substr

  // converts a double into a adstring
  friend adstring str(double x, int minwidth, int decplaces);
  friend adstring str(_CONST int x);
  friend void val(_CONST adstring& s, int& v, int& code);
  friend int val(const adstring& s);
};

adstring str(double x, int minwidth=17, int decplaces=-1);
adstring str(_CONST int x);
void val(_CONST adstring& s, int& v, int& code);
int val(const adstring& s);

class cifstream;
 
class line_adstring : public adstring
{
public:
  line_adstring(void) : adstring() {}
  line_adstring(_CONST adstring& s) : adstring(s) {}
  line_adstring& operator = (_CONST adstring& s);
  line_adstring& operator = (_CONST char * s);
  friend istream & operator >> (istream & c, line_adstring & t);
};

adstring itoa(int n,int d);

void str(_CONST int, adstring&);
adstring chr(int c);
int length(_CONST adstring& t);
int pos(_CONST adstring& substr,_CONST adstring& s);

//adstring operator + (_CONST char u, _CONST char v)
//  { return (adstring(u) + adstring(v) ); }
#if defined(__BORLANDC__)
#  if (__BORLANDC__  <= 0x0520) 
     class ifstream;
     class ofstream;
     class cifstream;
#  endif
#endif

#ifndef _VECTOR_SHAPE
  #define _VECTOR_SHAPE
  class vector_shape
  {
    unsigned int ncopies;
    int index_min;
    int index_max;
    void shift(int min);
    friend class dvector;
    friend class dvar_vector;
    friend class ivector;
    friend class lvector;
    friend class ptr_vector;
  public:
    vector_shape(int& lb, int& lu) {index_min=lb;index_max=lu;ncopies=0;}
    _CONST int indexmin(void) _CONST {return index_min;}
    _CONST int indexmax(void) _CONST {return index_max;}
  };
#endif


class adstring_array : public clist
{
  vector_shape * shape;
  adstring ** ptr;
public:
  int size() _CONST { return shape->indexmax()-shape->indexmin()+1;}
  _CONST int indexmin(void) _CONST { return shape->indexmin();}
  _CONST int indexmax(void) _CONST { return shape->indexmax();}
  adstring_array(_CONST adstring_array& sa);
  ~adstring_array();
  adstring_array(int min,int max);
  void allocate(int min,int max);
  adstring_array(void); 
  #ifdef USE_CONST
  _CONST adstring& operator [] (int i) _CONST;
  _CONST adstring& operator () (int i) _CONST;
  #endif
  adstring& operator [] (int i);
  adstring& operator () (int i);
  adstring_array& /*adstring_array::*/operator += (const adstring& s);
  adstring_array& /*adstring_array::*/append_distinct(const adstring& s);
  friend ifstream& operator >> (ifstream& ifs,adstring_array& sa);
  friend ostream& operator << (BOR_CONST ostream& ifs,_CONST adstring_array& sa);
  friend cifstream& operator >> (cifstream& ifs,adstring_array& sa);
};   // end class adstring_array

ostream& operator << (BOR_CONST ostream& ifs,_CONST adstring_array& sa);


int atoi(adstring& s);
#endif //#ifndef __STRING_HPP__
