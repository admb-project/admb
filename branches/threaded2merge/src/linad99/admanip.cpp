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
#include <fvar.hpp>

//#ifdef __GNUDOS__
/*
ostream& setfixed(const ostream& _s)
{
  ostream& s=(ostream&)(_s);
  s.setf(ios::fixed,ios::floatfield);
  return s;
}

ostream& setscientific(const ostream& _s)
{
  ostream& s=(ostream&)(_s);
  s.setf(ios::scientific,ios::floatfield);
  return s;
}


ostream& setshowpoint(const ostream& _s)
{
  ostream& s=(ostream&)(_s);
  s.setf(ios::showpoint);
  return s;
}
*/

/**
 * Description not yet available.
 * \param
 */
preshowpoint setshowpoint(void)
{
  preshowpoint tmp;
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& _s, preshowpoint p)
{
  ostream& s=(ostream&)(_s);
  s.setf(ios::showpoint);
  return s;
}

#if !(__MSVC32__>=7 || __BORLANDC__  >= 0x0560)

/**
 * Description not yet available.
 * \param
 */
prefixed setfixed(void)
{
  prefixed tmp;
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& _s, prefixed p)
{
  ostream& s=(ostream&)(_s);
  s.setf(ios::fixed,ios::floatfield);
  return s;
}

/**
 * Description not yet available.
 * \param
 */
prescientific setscientific(void)
{
  prescientific tmp;
  return tmp;
}

/**
 * Description not yet available.
 * \param
 */
ostream& operator<<(const ostream& _s, prescientific p)
{
  ostream& s=(ostream&)(_s);
  s.setf(ios::scientific,ios::floatfield);
  return s;
}
#endif
