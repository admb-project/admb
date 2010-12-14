/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */

#if defined(__SPDLL__)
#  if !defined(linux)
#    include <windows.h>
#  endif
#include <admodel.h>
#endif

#include "fvar.hpp"

#if defined(__TURBOC__) && !defined(__linux__)
  #pragma hdrstop
  #include <conio.h>
#endif

#ifdef __ZTC__
  #include <disp.h>

  // preprocessor defines and function definitions that emulate Borland
  // text screen managment functions using the Zortech disp_ package
  // note the order of includes is important - this stuff should come
  // after stdio.h, disp.h and anything that might also include these

//  #define if (ad_printf) (*ad_printf) disp_if (ad_printf) (*ad_printf)

  void gotoxy(int x, int y)
  {
    disp_move(y-1, x-1);
  }

  struct text_info
  {
    unsigned char  winleft,   wintop;
    unsigned char  winright,  winbottom;
  //unsigned char  attribute, normattr;
    unsigned char  currmode;
    unsigned char  screenheight;
    unsigned char  screenwidth;
    unsigned char  curx, cury;
  };

  void gettextinfo(struct text_info *r)
  {
     r->winleft = 1;
     r->wintop = 1;
     r->winright = disp_numcols;
     r->winbottom = disp_numrows-1;
     //attribute , normattr;
     r->currmode = disp_mode;;
     r->screenheight = disp_numrows;
     r->screenwidth = disp_numcols;
     r->curx = disp_cursorcol+1;
     r->cury = disp_cursorrow+1;
  }

#endif

#if defined(__NDPX__) || defined(__SUN__)  || defined(__GNU__)  
  void gotoxy(int x, int y) { ; }

  struct text_info
  {
    unsigned char  winleft,   wintop;
    unsigned char  winright,  winbottom;
  //unsigned char  attribute, normattr;
    unsigned char  currmode;
    unsigned char  screenheight;
    unsigned char  screenwidth;
    unsigned char  curx, cury;
  };

  void gettextinfo(struct text_info *r) {;}
#endif

#include <string.h>

void fmmdisp(_CONST dvector& x,_CONST dvector& g,
             const int& nvar, int scroll_flag,int noprintx)
{
  if (!noprintx)
  {
    int      headings = 3;     /* number of heading lines */
    int      cols = 3;     /* number of columns to display  */
  
    int      rownum;       /* row number to print */
    static int colnum[3] = {1, 28, 55}; /* position in line for each column */
    int      i, j, ij;
    int      imax;         /* number of lines to display */
    int      wmax;         /* number of lines in current window */
  
  
    char     colhead[30];
  
    char format[20];
    char format1[20];
    char format2[20];
    char format3[20];
    #if defined(__ZTC__)
      // Zortech uses 3 digits to print exponent in e format
      strcpy(format,"%3d%9.5lf %12.4le");
      strcpy(format1,"%3d%9.4lf %12.4le");
      strcpy(format2,"%3d%9.3lf %12.4le");
      strcpy(format3,"%3d%9.2lf %12.4le");
                 /*  12345678901234567 */
    #elif defined(__MSVC32__)
      strcpy(format,"%3d%8.4lf %12.4le");
      strcpy(format1,"%3d%8.3lf %12.4le");
      strcpy(format2,"%3d%8.2lf %12.4le");
      strcpy(format3,"%3d%8.1lf %12.4le");
              /*  12345678901234567 */
    #else
      strcpy(format,"%3d%9.5lf %12.5le");
      strcpy(format1,"%3d%9.4lf %12.5le");
      strcpy(format2,"%3d%9.3lf %12.5le");
      strcpy(format3,"%3d%9.2lf %12.5le");
              /*  12345678901234567 */
    #endif
  
    wmax = 22;
    strcpy(colhead,"Var   Value    Gradient   ");
    if (ad_printf) (*ad_printf)("%26s|%26s|%26s\n",colhead,colhead,colhead);
    imax = nvar / cols;
    if (nvar % cols > 0) imax++;
    if ( (scroll_flag == 0) && (imax > wmax-headings) )
      imax = wmax - headings - 1;
    rownum = headings;
  
    
    for (i=1; i<=imax; i++)
    {
      for (j=0; j<cols; j++)
      {
        ij = cols*(i-1)+(j+1);
        if (ij <= nvar)
        {
	  if (fabs(x[ij])<100)
	  {  
            if (ad_printf) (*ad_printf)(format, ij, x[ij], g[ij]);
	  }
	  else if (fabs(x[ij])<1000)
	  {  
            if (ad_printf) (*ad_printf)(format1, ij, x[ij], g[ij]);
	  }
	  else if (fabs(x[ij])<10000)
	  {  
            if (ad_printf) (*ad_printf)(format2, ij, x[ij], g[ij]);
	  }
	  else
	  {  
            if (ad_printf) (*ad_printf)(format3, ij, x[ij], g[ij]);
	  }
          if (j<cols-1)
          {
            if (ad_printf) (*ad_printf)(" |");
          }
        }
      } // j loop
      if (i<=imax) if (ad_printf) (*ad_printf)("\n");
    }  // i loop
    if (ad_printf) fflush(stdout);
  }
} 
  
void fmmdisp(_CONST double * x,_CONST double * g,
             const int& nvar, int scroll_flag,int noprintx)
{
  if (!noprintx)
  {
    int      headings = 3;     /* number of heading lines */
    int      cols = 3;     /* number of columns to display  */
  
    int      rownum;       /* row number to print */
    static int colnum[3] = {1, 28, 55}; /* position in line for each column */
    int      i, j, ij;
    int      imax;         /* number of lines to display */
    int      wmax;         /* number of lines in current window */
  
  
    char     colhead[30];
  
    char format[30];
    char format1[30];
    char format2[30];
    char format3[30];
    #if defined(__ZTC__)
      // Zortech uses 3 digits to print exponent in e format
      strcpy(format,"%3d%9.5lf             ");
      strcpy(format1,"%3d%9.4lf            ");
      strcpy(format2,"%3d%9.3lf            ");
      strcpy(format3,"%3d%9.2lf            ");
                 /*  12345678901234567 */
    #elif defined(__MSVC32__)
      strcpy(format,"%3d%8.4lf             ");
      strcpy(format1,"%3d%8.3lf            ");
      strcpy(format2,"%3d%8.2lf            ");
      strcpy(format3,"%3d%8.1lf            ");
              /*  12345678901234567 */
    #else
      strcpy(format,"%3d%9.5lf             ");
      strcpy(format1,"%3d%9.4lf            ");
      strcpy(format2,"%3d%9.3lf            ");
      strcpy(format3,"%3d%9.2lf            ");
              /*  12345678901234567 */
    #endif
  
    wmax = 22;
    strcpy(colhead,"Var   Value               ");
    if (ad_printf) (*ad_printf)("%26s|%26s|%26s\n",colhead,colhead,colhead);
    imax = nvar / cols;
    if (nvar % cols > 0) imax++;
    if ( (scroll_flag == 0) && (imax > wmax-headings) )
      imax = wmax - headings - 1;
    rownum = headings;
  
    
    for (i=1; i<=imax; i++)
    {
      for (j=0; j<cols; j++)
      {
        ij = cols*(i-1)+(j+1);
        if (ij <= nvar)
        {
	  if (fabs(x[ij])<100)
	  {  
            if (ad_printf) (*ad_printf)(format, ij, x[ij]);
	  }
	  else if (fabs(x[ij])<1000)
	  {  
            if (ad_printf) (*ad_printf)(format1, ij, x[ij]);
	  }
	  else if (fabs(x[ij])<10000)
	  {  
            if (ad_printf) (*ad_printf)(format2, ij, x[ij]);
	  }
	  else
	  {  
            if (ad_printf) (*ad_printf)(format3, ij, x[ij]);
	  }
          if (j<cols-1)
          {
            if (ad_printf) (*ad_printf)(" |");
          }
        }
      } // j loop
      if (i<=imax) if (ad_printf) (*ad_printf)("\n");
    }  // i loop
    if (ad_printf) fflush(stdout);
  }
} 
  
  
//void fmmdisp(_CONST dvector& x,_CONST dvector& g,
//             const int& nvar, int scroll_flag)
//{
//  int      headings = 3;     /* number of heading lines */
//  int      cols = 3;     /* number of columns to display  */
//
//  int      rownum;       /* row number to print */
//  static int colnum[3] = {1, 28, 55}; /* position in line for each column */
//  int      i, j, ij;
//  int      imax;         /* number of lines to display */
//  int      wmax;         /* number of lines in current window */
//
//
//  char     colhead[30];
//
//  char format[20];
//  #ifdef __ZTC__
//    // Zortech uses 3 digits to print exponent in e format
//    strcpy(format,"%3d%9.5lf %12.4le");
//               /*  12345678901234567 */
//  #else
//    strcpy(format,"%3d%9.5lf %12.5le");
//            /*  12345678901234567 */
//  #endif
//
//#if defined(__NDPX__) || defined(__SUN__) || defined(__GNU__) || defined(_Windows)
//  wmax = 22;
//#if  defined(__SUN__) || defined(__GNU__) || defined(_WINDOWS)
//  strcpy(colhead,"Var   Value    Gradient   ");
//  if (ad_printf) (*ad_printf)("%26s|%26s|%26s\n",colhead,colhead,colhead);
//#else
//  strcpy(colhead,"Var   Value    Gradient");
//  if (ad_printf) (*ad_printf)("%23s   |%23s   |%23s\n",colhead,colhead,colhead);
//#endif
//  imax = nvar / cols;
//  // cout << "imax = " << imax << endl;
//  if (nvar % cols > 0) imax++;
//  if ( (scroll_flag == 0) && (imax > wmax-headings) )
//    imax = wmax - headings - 1;
//  // cout << "imax = " << imax << endl;
//#else
//  struct text_info ti;   /* size etc of text screen */
//  gettextinfo(&ti);
//  gotoxy(1,ti.cury);
//  strcpy(colhead,"Var   Value    Gradient   ");
//  if (ad_printf) (*ad_printf)("%26s|%26s|%26s\n",colhead,colhead,colhead);
//  wmax = ti.winbottom - ti.wintop + 1;
//  gettextinfo(&ti);
//  headings = ti.cury - 2;
//
//  imax = nvar / cols;
//  if (nvar % cols > 0) imax++;
//  if ( (scroll_flag == 0) && (imax > wmax-headings) )
//    imax = wmax - headings - 1;
//#endif
//
//
//  rownum = headings;
//
//  for (i=1; i<=imax; i++)
//  {
//#if !defined(__NDPX__) && !defined(__SUN__) && !defined(__GNU__) && !defined(_Windows)
//    rownum++;
//    if (rownum > ti.winbottom)
//    {
//      gotoxy(1, ti.winbottom);
//      if (ad_printf) (*ad_printf)("\n");
//      rownum = ti.winbottom;
//    }
//#endif
//
//    for (j=0; j<cols; j++)
//    {
//      ij = cols*(i-1)+(j+1);
//      if (ij <= nvar)
//      {
//#if !defined(__NDPX__) && !defined(__SUN__)  && !defined(__SUN__) 
//        gotoxy(colnum[j], rownum);
//#endif
//        if (ad_printf) (*ad_printf)(format, ij, x[ij], g[ij]);
//        if (j<cols-1)
//        {
//          if (ad_printf) (*ad_printf)(" |");
//        }
//      }
//    } // j loop
//#if defined(__NDPX__) || defined(__SUN__)  || defined(__GNU__) 
//    if (ad_printf) (*ad_printf)("\n");
//#endif
//  }  // i loop
//
//  if  (scroll_flag)
//#if defined(__NDPX__) || defined(__SUN__)  || defined(__GNU__)  || defined(_Windows)
//    if (ad_printf) (*ad_printf)("\n");
//#else
//    if (ad_printf) (*ad_printf)("\n\n");
//  gettextinfo(&ti);
//  gotoxy(1,ti.cury);
//#endif
//}
//

