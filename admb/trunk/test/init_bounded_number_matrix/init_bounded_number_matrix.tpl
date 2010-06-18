// Copyright (c) 2008, 2009 Regents of the University of California.
//
// ADModelbuilder and associated libraries and documentations are
// provided under the general terms of the "BSD" license.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2.  Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3.  Neither the name of the  University of California, Otter Research,
// nor the ADMB Foundation nor the names of its contributors may be used
// to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//2GLOBALS_SECTION
GLOBALS_SECTION
  #include "test_init_bounded_number_matrix.h"

  void me();

DATA_SECTION
  init_int rowmin
  init_int rowmax
  init_int colmin
  init_int colmax

  init_matrix lower_bounds(rowmin,rowmax,colmin,colmax)
  init_matrix upper_bounds(rowmin,rowmax,colmin,colmax)
  init_imatrix phases(rowmin,rowmax,colmin,colmax)

  //DEFECT: should allow spaces after commas
  //-> init_matrix lower_bounds(rowmin, rowmax, colmin, colmax)

PARAMETER_SECTION
  init_number a
  !!//init_bounded_number_matrix ibnm(rowmin, rowmax, colmin, colmax, lower_bounds, upper_bounds, phases);
  objective_function_value f


PROCEDURE_SECTION
  param_init_bounded_number_matrix ibnm;
  //j;
  for (int i = rowmin; i <= rowmax; i++)
  {
    //f += ibnm(i);
    f = a * a;
  }

  //me(); 
