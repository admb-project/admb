/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#ifdef __ZTC__
  #include <conio.h>
#endif
 
#include "fvar.hpp"

#if !defined(__SUN__) && !defined(__GNU__) && !defined(__linux__)
	#if !defined(__NDPX__) 
	  #include <conio.h>
	#else
	  extern "C" {
	  }
	#endif
#endif

#include <ctype.h>
#include <stdlib.h>

int derchflag=0;
double derch_stepsize=0.0;

static ofstream * pofs=0;

/**
 * Description not yet available.
 * \param
 */
void derch(BOR_CONST double& _f, BOR_CONST independent_variables & _x,BOR_CONST dvector& _gg,
       int n, BOR_CONST int & _ireturn)
{
  dvector& gg=(dvector&) _gg;
  double& f=(double&) _f;
  int& ireturn = (int&) _ireturn;
  independent_variables& x= (independent_variables&) _x;
  static long int i, n1 ,n2,ii;
  static double fsave;
  static int order_flag;
  static double s, f1, f2, g2, xsave;
  static long int j = 1;
  static int si;
  si=gg.indexmax();
  static dvector g(1,si);
  static dvector index(1,si);

  if (ireturn == 4 ) goto label4;
  else if (ireturn == 5) goto label5;
  g=gg;
  {
    int maxind=0;
    double  maxg;
    maxind=g.indexmin();
    maxg=fabs(g(maxind));
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
    index=ivector(column(dtmp,1));
  }
  while (j > 0)
  {
    //cout << "\nEntering derivative checker.\n";
    cout << "\n Enter index (1 ... "<< n <<") of derivative to check.";
    cout << "  To check all derivatives, enter 0: ";
    cout << "  To quit  enter -1: ";
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
    cout << "   Enter step size (to quit derivative checker, enter 0): ";
    flush(cout);
#   if defined(__BORLANDC__)
      char mystring[1000];
      cin >> mystring;
      s=atof(mystring);
#   else
      cin >> s;
#   endif
//    cout << "\n       X           Function     Analytical     Finite Diff;  Index\n";
  
    if (s <= 0) ad_exit(0);
    if (j==0)
    {
      cout << endl << "   If you want the derivatives approximated in order"
        << endl << "   of decreasing magnitude enter 1" 
        << endl << "   Else enter 0" << endl;
      int tmpint=0;
      cin >> tmpint;
      if (tmpint==1)
        order_flag=1;
      else
        order_flag=0;
    }
    cout << "\n       X           Function     Analytical     Finite Diff;  Index"
         << endl;

    for (ii=n1; ii<=n2; ii++)
    {
      if (order_flag==1)
        i=index(ii);
      else
        i=ii;

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
#if !defined( __SUN__) && !defined( __GNU__) && !defined(__linux__)
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
