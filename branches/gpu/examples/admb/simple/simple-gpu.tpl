// Copyright (c) 2008, 2009, 2010 Regents of the University of California.
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
  init_int nobs
  init_vector Y(1,nobs)
  init_vector x(1,nobs)
PARAMETER_SECTION
  init_number a   
  init_number b   
  vector pred_Y(1,nobs)
  objective_function_value f
PROCEDURE_SECTION
  pred_Y=a*x+b;
  f=(norm2(pred_Y-Y)); 
  f=nobs/2.*log(f);    // make it a likelihood function so that
                       // covariance matrix is correct
GLOBALS_SECTION
  #include <adpar32.h>

TOP_OF_MAIN_SECTION
  time_t start,finish;
  int mdim,matMultTest,deviceTest;
  double elapsed_time,frac_second;
  long hour,minute,second;

  bool testGPUDevice = true;
  bool testGPUMM = true; 
  
  if(testGPUDevice){
    deviceTest = oclDeviceTest();
	}
  if(testGPUMM){
    // ** GPU testing **
    mdim = 1024;
    ProfTimer t;
    t.Start();
    //matMultTest = oclMatMult(mdim,mdim,mdim,mdim,true);
    matMultTest = oclMatMult(mdim,mdim,mdim,mdim,false);
    t.Stop();
    double dur = t.GetDurationInSecs();
    cout<<"admb_tpl: GPU matrix multiplication runtime was "<<dur<<" seconds."<<endl<<endl;
  
    // ** CPU testing **
    cout<<"admb_tpl: Starting CPU matrix multiplication....."<<endl;
    t.Start();
    //matMultTest = cpuMatMult(mdim,mdim,mdim,mdim,true);
    matMultTest = cpuMatMult(mdim,mdim,mdim,mdim,false);
    t.Stop();
    dur = t.GetDurationInSecs();
    cout<<"admb_tpl: CPU matrix multiplication runtime was "<<dur<<" seconds."<<endl<<endl;
	}

