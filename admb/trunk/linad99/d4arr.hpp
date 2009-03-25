/**
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


#ifndef D4ARR_HPP
  #define D4ARR_HPP
#ifndef USE_CONST
  #ifdef _CONST
    #undef _CONST
  #endif
  #define USE_CONST
  #define _CONST const
#endif

  class four_array_shape
  {
    unsigned int ncopies;
    int hslice_min;
    int hslice_max;
    int slice_min;
    int slice_max;
    int row_min;
    int row_max;
    int col_min;
    int col_max;
    four_array_shape(int hsl,int hsu, int sl,int sh,int rl,
      int ru,int cl,int cu);
    //mat_shape(){};

    friend class d4_array;
    friend class dvar4_array;

  }; // End of class four_array_shape


class d4_array
{
  four_array_shape * shape;
  d3_array * t;
public:
  void allocate(int hsl,int hsu,int sl,int sh,int nrl,
    int nrh,int ncl,int nch);
  void allocate(int hsl,int hsu, int sl,_CONST ivector& sh,int nrl,
    _CONST imatrix& nrh,int ncl,_CONST imatrix& nch);
  void allocate(int hsl,int hsu, int sl,_CONST ivector& sh,int nrl,
    _CONST imatrix& nrh,int ncl,_CONST i3_array& nch);
  void allocate(int hsl,int hsu,int sl,int sh,int nrl,
    int nrh,_CONST ivector& ncl,_CONST ivector& nch);
  void allocate(int hsl,int hsu,int sl,int sh,_CONST ivector& nrl,_CONST ivector& nrh,_CONST ivector& ncl,_CONST ivector& nch);
  void allocate(int hsl,int hsu,int sl,_CONST ivector& sh,
   int nrl, _CONST imatrix& nrh,int ncl,int nch);
  void deallocate(void);
  void allocate(void);
  void allocate(_CONST d4_array&);
  void allocate(_CONST dvar4_array&);
  int operator ! (void) _CONST {return (shape == NULL);}
  d4_array(int hsl,int hsu, int sl,int sh,ivector nrl,ivector nrh,
    ivector ncl,ivector nch);
  d4_array(int hsl,int hsu, int sl,_CONST ivector& sh,int nrl,
    _CONST imatrix& nrh,int ncl,_CONST i3_array& nch);
  d4_array& operator = (_CONST d4_array&);
  d4_array(d4_array& m2);
  d4_array(int,int,int,int,int,int,int,int);
  //d4_array(int,int,int,ivector,int,imatrix,int,int);
  d4_array(int hsl,int hsu,int sl,_CONST ivector& sh,
   int nrl, _CONST imatrix& nrh,int ncl,int nch);
  d4_array();
  ~d4_array();
   d3_array& elem(int i) { return t[i];}
   dmatrix& elem (int i ,int j) {return ((*this)(i))(j);}
   dvector& elem(int i,int j,int k) {return (((*this)(i,j))(k));}
   double& elem(int i,int j,int k,int l)
   {
     return ( ((*this)(i,j,k))(l));
   }
  #ifdef OPT_LIB
    d3_array& operator ( ) (int i) { return t[i];}
    d3_array& operator [] (int i) { return t[i];}
    dmatrix& operator ( ) (int i ,int j) {return ((*this)(i))(j);}
    dvector& operator ( ) (int i,int j,int k) {return (((*this)(i,j))(k));}
    double& operator ( ) (int i,int j,int k,int l)
    {
      return ( ((*this)(i,j,k))(l));
    }
    #ifdef USE_CONST
     inline _CONST d3_array& operator ( ) (int i)_CONST { return t[i];}
     inline _CONST d3_array& operator [] (int i)_CONST { return t[i];}
     inline _CONST dmatrix& operator ( ) (int i ,int j)_CONST {return ((*this)(i))(j);}
     inline _CONST dvector& operator ( ) (int i,int j,int k)_CONST {return (((*this)(i,j))(k));}
     inline _CONST double& operator ( ) (int i,int j,int k,int l)_CONST
     {
       return ( ((*this)(i,j,k))(l));
     }
    #endif
  #else
    #ifdef USE_CONST
      _CONST d3_array& operator ( ) (int i)_CONST;
      _CONST d3_array& operator [] (int i)_CONST;
      _CONST dmatrix& operator ( ) (int i ,int j)_CONST;
      _CONST dvector& operator ( ) (int i,int j,int k)_CONST;
      _CONST double& operator ( ) (int i,int j,int k,int l)_CONST;
    #endif
    d3_array& operator ( ) (int);
    d3_array& operator [] (int);
    dmatrix& operator ( ) (int,int);
    dvector& operator ( ) (int,int,int);
    double& operator ( ) (int,int,int,int);
  #endif
  //access functions
  friend class four_array_shape;
  int hslicemin(void) { return(shape->hslice_min);}
  int hslicemax(void) { return(shape->hslice_max);}
  int slicemin(void) { return(shape->slice_min);}
  int slicemax(void) { return(shape->slice_max);}
  int colmin(void) { return(shape->col_min);}
  int colmax(void) { return(shape->col_max);}
  int rowmin(void) { return(shape->row_min);}
  int rowmax(void) { return(shape->row_max);}
  int hslicesize() {return (shape->hslice_max-shape->hslice_min+1);} // returns the number of rows
  int slicesize() {return (shape->slice_max-shape->slice_min+1);} // returns the number of rows
  int rowsize() {return (shape->row_max-shape->row_min+1);} // returns the number of rows
  int colsize() {return (shape->col_max-shape->col_min+1);} // returns the number of columns
 #ifdef USE_CONST
  int hslicemin(void) _CONST { return(shape->hslice_min);}
  int hslicemax(void) _CONST { return(shape->hslice_max);}
  int slicemin(void) _CONST { return(shape->slice_min);}
  int slicemax(void) _CONST { return(shape->slice_max);}
  int colmin(void) _CONST { return(shape->col_min);}
  int colmax(void) _CONST { return(shape->col_max);}
  int rowmin(void) _CONST { return(shape->row_min);}
  int rowmax(void) _CONST { return(shape->row_max);}
  int hslicesize() _CONST {return (shape->hslice_max-shape->hslice_min+1);} // returns the number of rows
  int slicesize() _CONST {return (shape->slice_max-shape->slice_min+1);} // returns the number of rows
  int rowsize() _CONST {return (shape->row_max-shape->row_min+1);} // returns the number of rows
  int colsize() _CONST {return (shape->col_max-shape->col_min+1);} // returns the number of columns
 #endif
  void initialize(void);
};

class dvar4_array
{
  four_array_shape * shape;
  dvar3_array * t;
public:
  void allocate(int hsl,int hsu,int sl,int sh,int nrl,
    int nrh,int ncl,int nch);
  void allocate(int hsl,int hsu,int sl,int sh,int nrl,
    int nrh,_CONST ivector& ncl,_CONST ivector& nch);
  void allocate(int hsl,int hsu,int sl,int sh,_CONST ivector& nrl,_CONST ivector& nrh,_CONST ivector& ncl,_CONST ivector& nch);
  void deallocate(void);
  void allocate(void);
  void allocate(_CONST d4_array&);
  void allocate(_CONST dvar4_array&);
  int operator ! (void) _CONST {return (shape == NULL);}
  dvar4_array(int hsl,int hsu, int sl,int sh,ivector nrl,ivector nrh,
    ivector ncl,ivector nch);
  dvar4_array(d4_array& m1);
  dvar4_array(dvar4_array& m2);
  dvar4_array(int,int,int,int,int,int,int,int);
  dvar4_array(int hsl,int hsu,int sl,_CONST ivector& sh,
   int nrl, _CONST imatrix& nrh,int ncl,int nch);
  void allocate(int hsl,int hsu,int sl,_CONST ivector& sh,
   int nrl, _CONST imatrix& nrh,int ncl,int nch);
  //dvar4_array(int,int,int,ivector,int,imatrix,int,int);
  dvar4_array();
  ~dvar4_array();
   dvar3_array& elem(int i) { return t[i];}
   dvar_matrix& elem (int i ,int j) {return ((*this)(i))(j);}
   dvar_vector& elem(int i,int j,int k) {return (((*this)(i,j))(k));}
   prevariable elem(int i,int j,int k,int l)
   {
     return ( ((*this)(i,j,k))(l));
   }
  
  d4_array vale(d4_array&);
  dvar4_array& operator = (_CONST d4_array&);
  dvar4_array& operator = (_CONST dvar4_array&);
  #ifdef OPT_LIB
    dvar3_array& operator ( ) (int i) { return t[i];}
    dvar3_array& operator [] (int i) { return t[i];}
    dvar_matrix& operator ( ) (int i ,int j) {return ((*this)(i))(j);}
    dvar_vector& operator ( ) (int i,int j,int k) {return (((*this)(i,j))(k));}
    prevariable operator ( ) (int i,int j,int k,int l)
    {
      return ( ((*this)(i,j,k))(l));
    }
    #ifdef USE_CONST
     inline _CONST dvar3_array& operator ( ) (int i)_CONST { return t[i];}
     inline _CONST dvar3_array& operator [] (int i)_CONST { return t[i];}
     inline _CONST dvar_matrix& operator ( ) (int i ,int j)_CONST {return ((*this)(i))(j);}
     inline _CONST dvar_vector& operator ( ) (int i,int j,int k)_CONST {return (((*this)(i,j))(k));}
     inline _CONST prevariable operator ( ) (int i,int j,int k,int l)_CONST
     {
       return ( ((*this)(i,j,k))(l));
     }
    #endif
  #else
    #ifdef USE_CONST
      _CONST dvar3_array& operator ( ) (int i)_CONST;
      _CONST dvar3_array& operator [] (int i)_CONST;
      _CONST dvar_matrix& operator ( ) (int i ,int j)_CONST;
      _CONST dvar_vector& operator ( ) (int i,int j,int k)_CONST;
      _CONST prevariable operator ( ) (int i,int j,int k,int l)_CONST;
    #endif
    dvar3_array& operator ( ) (int);
    dvar3_array& operator [] (int);
    dvar_matrix& operator ( ) (int,int);
    dvar_vector& operator ( ) (int,int,int);
    prevariable operator ( ) (int,int,int,int);
  #endif
  //access functions
  friend class four_array_shape;
  int hslicemin(void) { return(shape->hslice_min);}
  int hslicemax(void) { return(shape->hslice_max);}
  int slicemin(void) { return(shape->slice_min);}
  int slicemax(void) { return(shape->slice_max);}
  int colmin(void) { return(shape->col_min);}
  int colmax(void) { return(shape->col_max);}
  int rowmin(void) { return(shape->row_min);}
  int rowmax(void) { return(shape->row_max);}
  int hslicesize() {return (shape->hslice_max-shape->hslice_min+1);} // returns the number of rows
  int slicesize() {return (shape->slice_max-shape->slice_min+1);} // returns the number of rows
  int rowsize() {return (shape->row_max-shape->row_min+1);} // returns the number of rows
  int colsize() {return (shape->col_max-shape->col_min+1);} // returns the number of columns
 #ifdef USE_CONST
  int hslicemin(void) _CONST { return(shape->hslice_min);}
  int hslicemax(void) _CONST { return(shape->hslice_max);}
  int slicemin(void) _CONST { return(shape->slice_min);}
  int slicemax(void) _CONST { return(shape->slice_max);}
  int colmin(void) _CONST { return(shape->col_min);}
  int colmax(void) _CONST { return(shape->col_max);}
  int rowmin(void) _CONST { return(shape->row_min);}
  int rowmax(void) _CONST { return(shape->row_max);}
  int hslicesize() _CONST {return (shape->hslice_max-shape->hslice_min+1);} // returns the number of rows
  int slicesize() _CONST {return (shape->slice_max-shape->slice_min+1);} // returns the number of rows
  int rowsize() _CONST {return (shape->row_max-shape->row_min+1);} // returns the number of rows
  int colsize() _CONST {return (shape->col_max-shape->col_min+1);} // returns the number of columns
 #endif
  void initialize(void);
};

d4_array exp(_CONST d4_array& x);
dvar4_array exp(_CONST dvar4_array& x);
d4_array sqrt(_CONST d4_array& x);
dvar4_array sqrt(_CONST dvar4_array& x);

ostream& operator<<(BOR_CONST ostream& ostr, d4_array & z);
istream& operator>>(BOR_CONST istream& istr, d4_array & z);
ostream& operator<<(BOR_CONST ostream& ostr, dvar4_array & z);
istream& operator>>(BOR_CONST istream& istr, dvar4_array & z);

#endif  // #ifndef D4ARR_HPP
