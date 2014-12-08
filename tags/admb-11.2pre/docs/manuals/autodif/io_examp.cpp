\begin{lstlisting}
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
void main()
{
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
    cout << " In default format:\n";
    cout << x << endl;
    cout << " In fixed point notation:\n";
    cout << setw(13) << setprecision(4) << setfixed << x << endl;
    cout << " In scientific notation:\n";
    cout << setw(13) << setprecision(4) << setscientific << x << endl;

    // write x to formatted file, read back into y and display on screen
    cout << "After formatted write and read:\n";
    {
      ofstream f1("file1.tmp"); // open output file
      if (!f1)
      {
        cerr << "Error trying to open file file1.tmp\n";
        exit(1);
      }

      f1 << x; // write x to file with default format
      if (!f1)
      {
        cerr << "Error trying to write x to file1.tmp\n";
        exit(1);
      }
    } // f1 goes out of scope so file1.tmp is closed
    {
      dvar_matrix y(1, n, 1, m);
      ifstream f1( "file1.tmp"); // open input file
      if (!f1)
      {
        cerr << "Error trying to open input file file1.tmp\n";
        exit(1);
      }
      f1 >> y; // read back into y
      if (!f1)
      {
        cerr << "Error trying to read y from file1.tmp\n";
        exit(1);
      }
      cout << setw(14) << setprecision(4) << y << endl;
    } // y and f1 go out of scope; file1.tmp is closed

    // write x to unformatted file, read back into y and display on screen
    cout << "After unformatted write and read:\n";
    {
      uostream f1("file2.tmp"); // open output file
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
      uistream f1( "file2.tmp"); // open input file
      f1 >> y; // read back into y
      cout << setw(14) << setprecision(4) << y << endl;
    } // y and f1 go out of scope; file2.tmp is closed
  } // x and gs go out of scope
  exit(0);
}
\end{lstlisting}