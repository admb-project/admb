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
// compiler specific stack length specifications
#ifdef __BCPLUSPLUS__
  #include <iomanip.h>
  extern unsigned _stklen = 20000;
#endif
#ifdef __ZTC__
  #include <iomanip.hpp>
  long _stack = 20000;
#endif
int main()
{
  using std::cout;
  using std::endl;
  using std::ofstream;
  using std::ifstream;
  int n = 20;
  int m = 5;
  int i, j;
  {
    gradient_structure gs;
    dvar_matrix x(1, n, 1, m);
    // compute some values for x
    for (i=1; i<=n; i++)
    {
      x.rowfill_seqadd(i,i+1./1000.,1./1000.);
    }

    // display x on screen
    cout << "Prior to write and read tests\n";
    cout << "  In default format:\n";
    cout << x << endl;
    cout << "  In fixed point notation:\n";
    cout << setw(13) << std::setprecision(4) << std::ios::fixed << x << endl;
    cout << "  In scientific notation:\n";
    cout << setw(13) << std::setprecision(4) << std::ios::scientific << x << endl;

    // write x to formatted file, read back into y and display on screen
    cout << "After formatted write and read:\n";
    {
      ofstream f1("file1.tmp");  // open output file
      if (!f1)
      {
        cerr << "Error trying to open file file1.tmp\n";
        exit(1);
      }

      f1 << x;   // write x to file with default format
      if (!f1)
      {
        cerr << "Error trying to write x to file1.tmp\n";
        exit(1);
      }
    }  // f1 goes out of scope so file1.tmp is closed
    {
      dvar_matrix y(1, n, 1, m);
      ifstream f1( "file1.tmp");  // open input file
      if (!f1)
      {
        cerr << "Error trying to open input file file1.tmp\n";
        exit(1);
      }
      f1 >> y;  // read back into y
      if (!f1)
      {
        cerr << "Error trying to read y from file1.tmp\n";
        exit(1);
      }
      cout << setw(14) << setprecision(4) << y << endl;
    }  // y and f1 go out of scope; file1.tmp is closed

    // write x to unformatted file, read back into y and display on screen
    cout << "After unformatted write and read:\n";
    {
      uostream f1("file2.tmp");  // open output file
      if (!f1)
      {
        cerr << "Error trying to open unformatted output file file1.tmp\n";
        exit(1);
      }
      f1 << x; // write x to file
      if (!f1)
      {
        cerr << "Error trying unformatted write x to file1.tmp\n";
        exit(1);
      }
    } // f1 goes out of scope so file2.tmp is closed
    {
      dvar_matrix y(1, n, 1, m);
      uistream f1( "file2.tmp");  // open input file
      f1 >> y;  // read back into y
      cout << setw(14) << setprecision(4) << y << endl;
    } // y and f1 go out of scope; file2.tmp is closed
  } // x and gs go out of scope
  return 0;
}
