/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Functions for str.
*/
#include <fvar.hpp>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef __NDPX__
  #include <dos.h> //itoa
#endif
#ifndef OPT_LIB
  #include <cassert>
  #include <climits>
#endif

/**
Convert x to adstring with minimum width and total number
of decimal places.
*/
adstring str(double x, int minwidth, int decplaces)
{
   int w = 0;
   int d = 0;
   char  buffer[50];

   int maxwidth = 0;
   if (fabs(x) > 0)
     maxwidth = int(log10(fabs(x)));
   else
     maxwidth = minwidth;

   if (decplaces < 0) // decplaces not specified
   {
     if (minwidth < 8)
       w = 8;
     else
       w = minwidth;

     if (x < 0)
       w++;

     d = minwidth-7;
     if (d>10)
       d = 10;

     //tmp = new adstring(1,w-1);
     //sprintf(tmp->s,"%*.*e",w,d,x);
     sprintf(buffer,"%*.*e",w,d,x);
   }
   else // decplaces specified
   {
     if (decplaces > 11)
       d = 11;
     else
       d = decplaces;

     w = maxwidth;
     if (w < minwidth)
       w = minwidth;

     w += d;//+3;
     if (x < 0)
       w++;
     //tmp = new adstring(1,w-1);

     sprintf(buffer,"%*.*f",w,d,x);
/*
     if (d>=0)
     {
       //sprintf(tmp->s,"%*.*f",w,d,x);
       sprintf(buffer,"%*.*f",w,d,x);
     }
     else
     {
       //sprintf(tmp->s,"%*.f",w,x);
       sprintf(buffer,"%*.f",w,x);
     }
*/
   }
   //return (*tmp);
   adstring tmp(buffer);
   return (tmp);
}
/**
Convert integer a to adstring s.

\param a Value to be converted.
\param s Converted adstring of a.
*/
void str(const int a, adstring& s)
{
#if defined(_MSC_VER)
  char  buffer[50];
  itoa(a, buffer, 10);
  s = adstring(buffer);
#else
  s = itoa(a,10);
#endif
}
/**
Returns converted string representation of integer a.

\param a Value to be converted.
*/
adstring str(const int a)
{
#if defined(_MSC_VER)
  char  buffer[50];
  itoa(a, buffer, 10);
  //adstring* tmp = new adstring(1,strlen(buffer));
  //*tmp = adstring(buffer);
  adstring tmp((char*)buffer);
#else
  adstring tmp = itoa(a,10);
#endif
  return tmp;
}

adstring chr(int c)
{
#ifndef OPT_LIB
  assert(0 <= c && c <= CHAR_MAX);
#endif
  return adstring((char)c);
}
