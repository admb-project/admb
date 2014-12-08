/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#ifdef __ZTC__
  #include <conio.h>
#endif

#include "fvar.hpp"

#if defined(_WIN32)
  #include <conio.h>
#endif

#include <ctype.h>
#include <stdlib.h>

#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

int derchflag=0;
double derch_stepsize=0.0;

static ofstream* pofs=0;

/**
 * Description not yet available.
 * \param
 */
void derch(const double& _f, const independent_variables & _x,
 const dvector& _gg, int n, const int & _ireturn)
{
  dvector& gg=(dvector&) _gg;
  double& f=(double&) _f;
  int& ireturn = (int&) _ireturn;
  independent_variables& x= (independent_variables&) _x;
  static int i, n1 ,n2,ii;
  static double fsave;
  static int order_flag;
  static double s, f1, f2, g2, xsave;
  static int j = 1;
  static int si;
  si=gg.indexmax();
  static dvector g(1,si);
  static dvector index(1,si);

  if (ireturn == 4 ) goto label4;
  else if (ireturn == 5) goto label5;
  g=gg;
  {
    int maxind = g.indexmin();
    double maxg=fabs(g(maxind));
    dmatrix tmp(1,3,g.indexmin(),g.indexmax());
    tmp(1).fill_seqadd(1,1);
    tmp(2)=g;
    tmp(3)=-fabs(g);
    ofstream ofs("derivatives");
    dmatrix dtmp=sort(trans(tmp),3);
    ofs << dtmp << endl;
    for (int i=g.indexmin();i<=g.indexmax();i++)
    {
      if (fabs(g(i))>maxg)
      {
        maxg=fabs(g(i));
        maxind=i;
      }
    }
    cout << "maxind = " << maxind << " maxg = " << maxg << endl;
    index=column(dtmp,1);
  }
  while (j > 0)
  {
    cout << "\nEntering derivative checker.\n";
    cout << "   Enter index (1 ... "<< n <<") of derivative to check.\n";
    cout << "     To check all derivatives, enter 0;\n";
    cout << "     To quit  enter -1: ";
    flush(cout);
    cin >> j;
    if (j == -1)
    {
      ireturn = -1;
      return;
    }
    if (j == 0)
    {
      cout << "\n   Checking all derivatives. Press X to terminate checking.\n";
      flush(cout);
      pofs=new ofstream("ders.dat");
      (*pofs) << "      index  analytical        finite     % error " << endl;
      (*pofs) << "                              difference " << endl;
      n1 = 1;
      n2 = n;
    }
    else
    {
      n1 = j;
      n2 = j;
    }
    cout << "\n   Enter step size.\n";
    cout << "      To quit derivative checker enter -1;\n";
    cout << "      to check for uninitialized variables enter 0): ";
    flush(cout);
#if defined(__BORLANDC__)
    char mystring[1000];
    cin >> mystring;
    s=atof(mystring);
#else
    cin >> s;
#endif
    if (s < 0) ad_exit(0);

    if (j==0)
    {
      cout << "\n   If you want the derivatives approximated in order\n"
           << "   of decreasing magnitude enter 1;\n"
           << "   else enter 0: ";
      flush(cout);
      int tmpint=0;
      cin >> tmpint;
      if (tmpint==1)
        order_flag=1;
      else
        order_flag=0;
    }
    if (s != 0)
    {
      cout <<
        "\n   X             Function      Analytical    Finite Diff ; Index"
        << endl;
    }

    for (ii=n1; ii<=n2; ii++)
    {
      i = ii;
      if (order_flag==1)
      {
        int count = 0;
        for (int _ii = index.indexmin(); _ii <= index.indexmax(); ++_ii)
        {
#ifdef OPT_LIB
          int idx = (int)index(_ii);
#else
          double _idx = index(_ii);
          assert(_idx <= (double)INT_MAX);
          int idx = (int)_idx;
#endif
          if (x.indexmin() <= idx && idx <= x.indexmax())
          {
            ++count;
          }
          if (count == ii)
          {
            i = idx;
            break;
          }
        }
      }
      derch_stepsize=s;
      derchflag=1;
      xsave=x(i);
      x(i)=xsave+s;
      fsave = f;
      ireturn = 4; // fgcomp(&f1,x,g1,n, params, vars);
      return;

    label4:
      derch_stepsize=s;
      derchflag=-1;
      f1 = f;
      x(i)=xsave-s;
      ireturn= 5; //fgcomp(&f2,x,g1,n, params, vars);
      return;

    label5:
      f2 = f;
      f = fsave;
      x(i)=xsave;
      if (s==0.0)
      {
        if (fabs(f1-f2)>0.0)
        {
          cout << "There appear to be uninitialized variables in "
               << "the objective function "  << endl
               << "    f1 = " << setprecision(15) << f1
               << " f2 = " << setprecision(15) << f2 << endl;
        }
        else
        {
          cout << "There do not appear to be uninitialized variables in" << endl
               << "the objective function " << endl;
        }
      }
      else
      {
        g2=(f1-f2)/(2.*s);
        derchflag=0;
        double perr= fabs(g2-g(i))/(fabs(g(i))+1.e-6);

        if (pofs)
        {
          if (perr > 1.e-3)
            (*pofs) << " ** ";
          else
            (*pofs) << "    ";
          (*pofs) << "  " << setw(4) << i
                  << "  " <<  setw(12) << g(i)
                  << "  " <<  setw(12) << g2
                  << "  " <<  setw(12) <<  perr
                  << endl;
        }
        if (ad_printf)
        {
          (*ad_printf)("  %12.5e  %12.5e  %12.5e  %12.5e ; %5d \n",
                x(i), f, g(i), g2, i);
          fflush(stdout);
        }
      }
#if defined(_MSC_VER)
      if ( kbhit() )
      {
        int c = toupper(getch());
        if ( c == 'X')
        {
          cout << "   Exiting derivative checker by user interrupt.\n";
          ad_exit(0);
        }
      }
#endif
    } // for loop
  } // while (j > 0)
//  ireturn = 2;
  ad_exit(0);
}
