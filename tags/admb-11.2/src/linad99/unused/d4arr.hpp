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
/**
 * \file
 * Description not yet available.
 */
#ifndef D4ARR_HPP
#define D4ARR_HPP

/**
 * Description not yet available.
 * \param
 */
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

/**
 * Description not yet available.
 * \param
 */
class d4_array
{
  four_array_shape * shape;
  d3_array * t;
public:
  void allocate(int hsl,int hsu,int sl,int sh,int nrl,
    int nrh,int ncl,int nch);
  void allocate(int hsl, int hsu, int sl, const ivector& sh, int nrl,
                const imatrix& nrh, int ncl, const imatrix& nch);
  void allocate(int hsl, int hsu, int sl, const ivector& sh, int nrl,
                const imatrix& nrh, int ncl, const i3_array& nch);
  void allocate(int hsl, int hsu, int sl, int sh, int nrl,
                int nrh, const ivector& ncl, const ivector& nch);
  void allocate(int hsl, int hsu, int sl, int sh, const ivector& nrl,
                const ivector& nrh, const ivector& ncl, const ivector& nch);
  void allocate(int hsl, int hsu, int sl, const ivector& sh,
                int nrl, const imatrix& nrh, int ncl, int nch);
  void deallocate(void);
  void allocate(void);
  void allocate(const d4_array&);
  void allocate(const dvar4_array&);
  int operator!(void) const { return (shape == NULL); }
  d4_array(int hsl,int hsu, int sl,int sh,ivector nrl,ivector nrh,
    ivector ncl,ivector nch);
  d4_array(int hsl, int hsu, int sl, const ivector& sh, int nrl,
           const imatrix& nrh, int ncl, const i3_array& nch);
  d4_array& operator=(const d4_array&);
  d4_array(d4_array& m2);
  d4_array(int,int,int,int,int,int,int,int);
  //d4_array(int,int,int,ivector,int,imatrix,int,int);
  d4_array(int hsl, int hsu, int sl, const ivector& sh,
           int nrl, const imatrix& nrh, int ncl, int nch);
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
     inline const d3_array& operator()(int i) const { return t[i]; }
     inline const d3_array& operator[](int i) const { return t[i]; }
     inline const dmatrix& operator()(int i, int j) const
       { return ((*this)(i))(j); }
     inline const dvector& operator()(int i, int j, int k) const
       { return (((*this)(i, j))(k)); }
     inline const double& operator()(int i, int j, int k, int l) const
     {
       return (((*this)(i, j, k))(l));
     }
  #else
      const d3_array& operator()(int i) const;
      const d3_array& operator[](int i) const;
      const dmatrix& operator()(int i, int j) const;
      const dvector& operator()(int i, int j, int k) const;
      const double& operator()(int i, int j, int k, int l) const;
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

   // returns the number of rows
  int hslicesize() {return (shape->hslice_max-shape->hslice_min+1);}
  // returns the number of rows
  int slicesize() {return (shape->slice_max-shape->slice_min+1);}
  // returns the number of rows
  int rowsize() {return (shape->row_max-shape->row_min+1);}
  // returns the number of columns
  int colsize() {return (shape->col_max-shape->col_min+1);}
  int hslicemin(void) const { return (shape->hslice_min); }
  int hslicemax(void) const { return (shape->hslice_max); }
  int slicemin(void) const { return (shape->slice_min); }
  int slicemax(void) const { return (shape->slice_max); }
  int colmin(void) const { return (shape->col_min); }
  int colmax(void) const { return (shape->col_max); }
  int rowmin(void) const { return (shape->row_min); }
  int rowmax(void) const { return (shape->row_max); }
  // returns the number of rows
  int hslicesize() const { return (shape->hslice_max-shape->hslice_min + 1); }
  // returns the number of rows
  int slicesize() const { return (shape->slice_max-shape->slice_min + 1); }
  // returns the number of rows
  int rowsize() const { return (shape->row_max-shape->row_min + 1); }
  // returns the number of columns
  int colsize() const { return (shape->col_max-shape->col_min + 1); }
  void initialize(void);
};

/**
 * Description not yet available.
 * \param
 */
class dvar4_array
{
  four_array_shape * shape;
  dvar3_array * t;
public:
  void allocate(int hsl,int hsu,int sl,int sh,int nrl,
    int nrh,int ncl,int nch);
  void allocate(int hsl, int hsu, int sl, int sh, int nrl,
                int nrh, const ivector& ncl, const ivector& nch);
  void allocate(int hsl, int hsu, int sl, int sh, const ivector& nrl,
                const ivector& nrh, const ivector& ncl, const ivector& nch);
  void deallocate(void);
  void allocate(void);
  void allocate(const d4_array&);
  void allocate(const dvar4_array&);
  int operator!(void) const { return (shape == NULL); }
  dvar4_array(int hsl,int hsu, int sl,int sh,ivector nrl,ivector nrh,
    ivector ncl,ivector nch);
  dvar4_array(d4_array& m1);
  dvar4_array(dvar4_array& m2);
  dvar4_array(int,int,int,int,int,int,int,int);
  dvar4_array(int hsl, int hsu, int sl, const ivector& sh,
              int nrl, const imatrix& nrh, int ncl, int nch);
  void allocate(int hsl, int hsu, int sl, const ivector& sh,
                int nrl, const imatrix& nrh, int ncl, int nch);
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
  dvar4_array& operator=(const d4_array&);
  dvar4_array& operator=(const dvar4_array&);
  #ifdef OPT_LIB
    dvar3_array& operator ( ) (int i) { return t[i];}
    dvar3_array& operator [] (int i) { return t[i];}
    dvar_matrix& operator ( ) (int i ,int j) {return ((*this)(i))(j);}
    dvar_vector& operator ( ) (int i,int j,int k) {return (((*this)(i,j))(k));}
    prevariable operator ( ) (int i,int j,int k,int l)
    {
      return ( ((*this)(i,j,k))(l));
    }
     inline const dvar3_array& operator()(int i) const { return t[i]; }
     inline const dvar3_array& operator[](int i) const { return t[i]; }
     inline const dvar_matrix& operator()(int i, int j) const
       { return ((*this)(i))(j); }
     inline const dvar_vector& operator()(int i, int j, int k) const
       {return (((*this)(i, j))(k)); }
     inline const prevariable operator()(int i, int j, int k, int l) const
     {
       return ( ((*this)(i,j,k))(l));
     }
  #else
      const dvar3_array& operator()(int i) const;
      const dvar3_array& operator[](int i) const;
      const dvar_matrix& operator()(int i, int j) const;
      const dvar_vector& operator()(int i, int j, int k) const;
      const prevariable operator()(int i, int j, int k, int l) const;
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
  // returns the number of rows
  int hslicesize() {return (shape->hslice_max-shape->hslice_min+1);}
  // returns the number of rows
  int slicesize() {return (shape->slice_max-shape->slice_min+1);}
  // returns the number of rows
  int rowsize() {return (shape->row_max-shape->row_min+1);}
  // returns the number of columns
  int colsize() {return (shape->col_max-shape->col_min+1);}
  int hslicemin(void) const { return (shape->hslice_min); }
  int hslicemax(void) const { return (shape->hslice_max); }
  int slicemin(void) const { return (shape->slice_min); }
  int slicemax(void) const { return (shape->slice_max); }
  int colmin(void) const { return (shape->col_min); }
  int colmax(void) const { return (shape->col_max); }
  int rowmin(void) const { return (shape->row_min); }
  int rowmax(void) const { return (shape->row_max); }
  // returns the number of rows
  int hslicesize() const { return (shape->hslice_max-shape->hslice_min + 1); }
  // returns the number of rows
  int slicesize() const { return (shape->slice_max-shape->slice_min + 1); }
  // returns the number of rows
  int rowsize() const { return (shape->row_max-shape->row_min + 1); }
  // returns the number of columns
  int colsize() const { return (shape->col_max-shape->col_min + 1); }
  void initialize(void);
};

d4_array exp(const d4_array& x);
dvar4_array exp(const dvar4_array& x);
d4_array sqrt(const d4_array& x);
dvar4_array sqrt(const dvar4_array& x);

ostream& operator<<(const ostream& ostr, d4_array &z);
istream& operator>>(const istream& istr, d4_array &z);
ostream& operator<<(const ostream& ostr, dvar4_array &z);
istream& operator>>(const istream& istr, dvar4_array &z);

#endif  // #ifndef D4ARR_HPP
