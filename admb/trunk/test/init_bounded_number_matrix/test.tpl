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
DATA_SECTION
  int rowmin
  !! rowmin = 1;
  int rowmax
  !! rowmax = 5;
  vector lower_bounds_vector(rowmin,rowmax)
  !! lower_bounds_vector = 4;
  vector upper_bounds_vector(rowmin,rowmax)
  !! upper_bounds_vector = 10;
  ivector phases_vector(rowmin,rowmax)
  !! phases_vector = 1;
  int colmin
  !! colmin = 1;
  int colmax
  !! colmax = 5;
  matrix lower_bounds_matrix(rowmin,rowmax,colmin,colmax)
  !! double value = 0;
  !! for (int i = rowmin; i <= rowmax; i++)
  !! {
  !!   for (int j = colmin; i <= colmax; i++)
  !!   {
  !!     lower_bounds_matrix(i, j) = value;
  !!     value += 0.5;
  !!   } 
  !! } 
  matrix upper_bounds_matrix(rowmin,rowmax,colmin,colmax)
  !! upper_bounds_matrix = 100;
  imatrix phases_matrix(rowmin,rowmax,colmin,colmax)
  !! phases_matrix = 1;
PARAMETER_SECTION
  init_bounded_number_vector ibnv(rowmin,rowmax,lower_bounds_vector,upper_bounds_vector,phases_vector)
  init_bounded_number_matrix pibnm(rowmin,rowmax,rowmin,rowmax,lower_bounds_matrix,upper_bounds_matrix,phases_matrix)
  objective_function_value f
PROCEDURE_SECTION
  dvar_vector v(ibnv);
  f += norm2(v);

  dvar_matrix m(pibnm);
  f += norm2(m);
