/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#ifdef __GNUDOS__
 #include <admanip.h>
 #ifndef IOMANIPdeclare
  #define IOMANIPdeclare(T) \

  IOMANIPdeclare(int);
  IOMANIPdeclare(long);
  #ifndef _IOMANIP_H
    #define _IOMANIP_H
  #endif
 #endif /*!IOMANIPdeclare*/
#else
  #include <iomanip.h>
  #include <iostream.h>
#endif

static ios &sfill(BOR_CONST ios &s, int c)
{
    s.fill(c);
    return s;
}

SMANIP(int) setfill(int c)
{
    return SMANIP(int)(sfill, c);
}

static ios &swidth(BOR_CONST ios &s, int w)
{
    s.width(w);
    return s;
}

SMANIP(int) setw(int w)
{
    return SMANIP(int)(swidth, w);
}

static ios &sprec(BOR_CONST ios &s, int p)
{
    s.precision(p);
    return s;
}

SMANIP(int) setprecision(int p)
{
    return SMANIP(int)(sprec, p);
}

static ios &rsf(BOR_CONST ios& s, long v)
{
    s.unsetf(v);
    return s;
}

SMANIP(long) resetiosflags(long v)
{
    return SMANIP(long)(rsf, v);
}

static ios &sf(BOR_CONST ios& s, long v)
{
    s.flags(v|s.flags());
    return s;
}

SMANIP(long) setiosflags(long v)
{
    return SMANIP(long)(sf, v);
}

