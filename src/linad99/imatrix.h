/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2014 Regents of the University of California
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
#ifndef __ADMB_IMATRIX_H__
#define __ADMB_IMATRIX_H__

/**
 * Description not yet available.
 * \param
 */
class imatrix_position
{
public:
  int row_min;
  int row_max;
  ivector lb;
  ivector ub;
  ptr_vector ptr;
  imatrix_position(const imatrix &);
  imatrix_position(int min, int max);
  imatrix_position(const imatrix_position &);
  ivector_position operator()(int i);
};

//imatrix_position restore_imatrix_position(DF_FILE* fp);
imatrix restore_imatrix_value(const imatrix_position &);

/**
 * Description not yet available.
 * \param
 */
class imatrix
{
protected:
   int index_min;
   int index_max;
   ivector* m;
   mat_shapex* shape;

public:
   int operator!(void) const
   {
      return (shape == NULL);
   }

   imatrix(int, int);
   // makes a matrix [0..nr][0..nc]

   imatrix(int nrl, int nrh, const ivector & iv);

   imatrix(int, int, int, int);
   // makes a matrix [nrl..nrh][ncl..nch]
   imatrix(int, int, int, const ivector &);
   imatrix sub(int, int);
   imatrix(int, int, const ivector &, const ivector &);
   imatrix(const ad_integer & nrl, const ad_integer & nrh,
     const index_type & ncl, const index_type & nch);

   imatrix& operator=(const imatrix & t);
   imatrix& operator=(const int);
   imatrix(const imatrix &);
   // copy initializer
   imatrix(const imatrix_position &);
   imatrix(void);

   ~imatrix();
   void shallow_copy(const imatrix &);

   void save_imatrix_value(DF_FILE* fp);
   void save_imatrix_position(DF_FILE* fp);
   imatrix restore_imatrix_value(const imatrix_position & mpos);
   imatrix_position restore_imatrix_position(void);

   void allocate(void);
   void allocate(int nrl, int nrh, const ivector & iv);
   void allocate(const imatrix& dm);
   void allocate(int nrl, int nrh, int ncl, int nch);
   void allocate(int nrl, int nrh);
   void allocate(int nrl, int nrh, int ncl, const ivector& nch);
   void allocate(int nrl, int nrh, const ivector & ncl, const ivector & nch);
   void allocate(const ad_integer & nrl, const ad_integer & nrh,
     const index_type & ncl, const index_type & nch);
   void deallocate();

   ivector& operator[](int);
   ivector& operator()(int);
   int& operator()(int, int);
   const ivector& operator[](int) const;
   const ivector& operator()(int) const;
   const int& operator()(int, int) const;


  ivector* begin() const
  {
    return m ? &m[indexmin()] : nullptr;
  }
  ivector* end() const
  {
    return m ? &m[indexmin()] + rowsize(): nullptr;
  }
  int indexmin() const
  {
    return rowmin();
  }
  int indexmax() const
  {
    return rowmax();
  }
  int rowmin() const
  {
    return index_min;
  }
  int rowmax() const
  {
    return index_max;
  }

   int colmin(void) const
   {
      return ((*this) (indexmin()).indexmin());
   }
   int colmax(void) const
   {
      return ((*this) (indexmin()).indexmax());
   }

  /// Returns the number of rows.
  unsigned int rowsize() const
  {
    return static_cast<unsigned int>(rowmax() - rowmin() + 1);
  }
  /// Returns the number of columns.
  unsigned int colsize() const
  {
    return static_cast<unsigned int>(colmax() - colmin() + 1);
  }

   void rowshift(int min);
ivector& elem(int i);
const ivector& elem(int i) const;

   inline int &elem(int i, int j)
   {
      return (*((*(m + i)).v + j));
   }
   inline const int &elem(int i, int j) const
   {
      return (*((*(m + i)).v + j));
   }

   void write_on(const ostream &) const;
   void write_on(const uostream &) const;
   void read_from(const istream &);
   void read_from(const uistream &);
   void initialize(void);
   void fill_seqadd(int, int);
   void colfill_seqadd(int, int, int);

  bool is_valid_row(const int i) const;

   friend char* fform(const char*, const dmatrix&);
   friend class i3_array;

  unsigned int get_ncopies() const { return shape ? shape->ncopies : 0; }
};

#ifdef OPT_LIB
inline ivector& imatrix::operator()(int i)
{
  return m[i];
}
inline int& imatrix::operator()(int i, int j)
{
  return (*((*(m + i)).v + j));
}
inline ivector& imatrix::operator[](int i)
{
  if (!m)
    throw std::bad_alloc();
  else
    return m[i];
}
inline const ivector& imatrix::operator()(int i) const
{
  return m[i];
}
inline const int& imatrix::operator()(int i, int j) const
{
  return (*((*(m + i)).v + j));
}
inline const ivector& imatrix::operator[](int i) const
{
  return m[i];
}
#endif
inline ivector& imatrix::elem(int i)
{
  if (i < rowmin())
  {
    cerr << "matrix bound exceeded -- row index too low in "
            "imatrix::operator[i] value was \"" << i << "\".\n";
    ad_exit(1);
  }
  if (i > rowmax())
  {
    cerr << "matrix bound exceeded -- row index too high in "
            "imatrix::operator[i] value was \"" << i << "\".\n";
    ad_exit(1);
  }
  return *(m + i);
}
inline const ivector& imatrix::elem(int i) const
{
  if (i < rowmin())
  {
    cerr << "matrix bound exceeded -- row index too low in "
            "imatrix::operator[i] value was \"" << i << "\".\n";
    ad_exit(1);
  }
  if (i > rowmax())
  {
    cerr << "matrix bound exceeded -- row index too high in "
            "imatrix::operator[i] value was \"" << i << "\".\n";
    ad_exit(1);
  }
  return *(m + i);
}
#endif
