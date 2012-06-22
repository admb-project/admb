/**
 * Copyright (c) 2008, 2009, 2010 Regents of the University of California
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
#include <fvar.hpp>
class const_parameters
{
public:
  dvector * pv;
  dvector * pw;
  const_parameters(int n1,int n2) {pv=new dvector(1,n1);pw=new dvector(1,n2);}
  ~const_parameters() {delete pv; delete pw;}
};

class var_parameters
{
public:
  dvector * pv;
  dvar_vector * pw;
  var_parameters(const_parameters& cp)
  {
    pv=new dvector(*(cp.pv));
    pw=new dvar_vector(*(cp.pw));
  }
  ~var_parameters() {delete pv; delete pw;}
};

void fcomp(const_parameters&);
void fcomp(var_parameters&);

int main()
{
  const_parameters cp(5,7);
 (*cp.pv).fill_seqadd(1,2);
 (*cp.pw).fill_seqadd(0,2.5);
 gradient_structure gs;
 {
   var_parameters vp(cp);
   fcomp(cp);
   fcomp(vp);
 }
  return 0;
}

void fcomp(const_parameters& cp)
{
  dvector& v=*(cp.pv);
  dvector& w=*(cp.pw);
  cout << *(cp.pw) << "\n";
  cout << *(cp.pv) << "\n\n";
  cout << v << "\n";
  cout << w << "\n\n";
}

void fcomp(var_parameters& vp)
{
  dvector& v=*(vp.pv);
  dvar_vector& w=*(vp.pw);
  cout << *(vp.pw) << "\n";
  cout << *(vp.pv) << "\n\n";
  cout << v << "\n";
  cout << w << "\n\n";
}
