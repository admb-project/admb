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

/**
 * Description not yet available.
 * \param
 */
static ios &sfill(const ios &s, int c)
{
    s.fill(c);
    return s;
}

/**
 * Description not yet available.
 * \param
 */
SMANIP(int) setfill(int c)
{
    return SMANIP(int)(sfill, c);
}

/**
 * Description not yet available.
 * \param
 */
static ios &swidth(const ios &s, int w)
{
    s.width(w);
    return s;
}

/**
 * Description not yet available.
 * \param
 */
SMANIP(int) setw(int w)
{
    return SMANIP(int)(swidth, w);
}

/**
 * Description not yet available.
 * \param
 */
static ios &sprec(const ios &s, int p)
{
    s.precision(p);
    return s;
}

/**
 * Description not yet available.
 * \param
 */
SMANIP(int) setprecision(int p)
{
    return SMANIP(int)(sprec, p);
}

/**
 * Description not yet available.
 * \param
 */
static ios &rsf(const ios& s, long v)
{
    s.unsetf(v);
    return s;
}

/**
 * Description not yet available.
 * \param
 */
SMANIP(long) resetiosflags(long v)
{
    return SMANIP(long)(rsf, v);
}

/**
 * Description not yet available.
 * \param
 */
static ios &sf(const ios& s, long v)
{
    s.flags(v|s.flags());
    return s;
}

/**
 * Description not yet available.
 * \param
 */
SMANIP(long) setiosflags(long v)
{
    return SMANIP(long)(sf, v);
}

