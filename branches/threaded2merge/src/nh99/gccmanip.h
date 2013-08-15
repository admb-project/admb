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
  #ifndef __GCCMANIP_HPP
  #define __GCCMANIP_HPP

//   #ifndef __GNUDOS__
//     #include <admanip.h>
//   #else
//     #include <iostream.h>
//   #endif
//
//   class smanip_int
//   {
//   public:
//       smanip_int(BOR_CONST ios &(*f)(BOR_CONST ios&, int), int v)
//       {
//         func=f;
//         val=v;
//       }
//       friend istream &operator>>(BOR_CONST istream&, BOR_CONST smanip_int&);
//       friend ostream &operator<<(BOR_CONST ostream&, BOR_CONST smanip_int&);
//   private:
//       ios &(*func)(BOR_CONST ios&, int);
//       int val;
//   };
//
//   inline istream &operator>>(BOR_CONST istream &s, BOR_CONST smanip_int &m)
//   {
//     (*m.func)(s, m.val);
//     return s;
//   }
//   inline ostream &operator<<(BOR_CONST ostream &s, BOR_CONST smanip_int &m)
//   {
//     (*m.func)(s, m.val);
//     return s;
//   }
//
//
//  smanip_int setprecision(int);
//  smanip_int setw(int);
   #endif
