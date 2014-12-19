/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "BSD" license.
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
#ifndef __param_init_bounded_number_matrix_h__
#define __param_init_bounded_number_matrix_h__
#include "admodel.h"

/**
 *
 */
class param_init_bounded_number_matrix
{
public:
  param_init_bounded_number_matrix();
  param_init_bounded_number_matrix(const param_init_bounded_number_matrix&);
  virtual ~param_init_bounded_number_matrix()
  {
    deallocate();
  }
public:
  /**
   *
   */
  void allocate(int rowmin, int rowmax,
                int colmin, int colmax,
                const dmatrix& bmin, const dmatrix& bmax,
                const char* s);
  /**
   *
   */
  void allocate(int rowmin, int rowmax,
                int colmin, int colmax,
                const dmatrix& bmin, const dmatrix& bmax,
                const imatrix& phase_start,
                const char* s);
  /**
   *
   */
  void set_scalefactor(const double scalefactor);
  /**
   *
   */
  void set_scalefactor(const dmatrix& scalefactor);
  /**
   *
   */
  dmatrix get_scalefactor() const;
  /**
   *
   */
  param_init_bounded_number_vector& operator[](const int i) const;
  /**
   *
   */
  param_init_bounded_number_vector& operator()(const int i) const;
  /**
   *
   */
  param_init_bounded_number& operator()(const int i, const int j) const;
  /**
   *
   */
  bool allocated() const { return v != NULL; }
  /**
   *
   */
  int indexmin() const { return index_min; }
  /**
   *
   */
  int indexmax() const { return index_max; }
private:
  /**
   *
   */
  void deallocate();
private:
  param_init_bounded_number_vector* v;
  int index_min;
  int index_max;
/*
  void set_initial_value(const double_index_type& it);

  double_index_type* it;
*/
};
#endif
