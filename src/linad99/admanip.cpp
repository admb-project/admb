/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>

//#ifdef __GNUDOS__
/*
ostream& setfixed(BOR_CONST ostream& _s)
{
  ostream& s=(ostream&)(_s);
  s.setf(ios::fixed,ios::floatfield);
  return s;
}

ostream& setscientific(BOR_CONST ostream& _s)
{
  ostream& s=(ostream&)(_s);
  s.setf(ios::scientific,ios::floatfield);
  return s;
}


ostream& setshowpoint(BOR_CONST ostream& _s)
{
  ostream& s=(ostream&)(_s);
  s.setf(ios::showpoint);
  return s;
}
*/

preshowpoint setshowpoint(void)
{
  preshowpoint tmp;
  return tmp;
}

ostream& operator << (BOR_CONST ostream& _s,preshowpoint p)
{
  ostream& s=(ostream&)(_s);
  s.setf(ios::showpoint);
  return s;
}

#if !(__MSVC32__>=7 || __BORLANDC__  >= 0x0560) 
prefixed setfixed(void)
{
  prefixed tmp;
  return tmp;
}

ostream& operator << (BOR_CONST ostream& _s,prefixed p)
{
  ostream& s=(ostream&)(_s);
  s.setf(ios::fixed,ios::floatfield);
  return s;
}

prescientific setscientific(void)
{
  prescientific tmp;
  return tmp;
}

ostream& operator << (BOR_CONST ostream& _s,prescientific p)
{
  ostream& s=(ostream&)(_s);
  s.setf(ios::scientific,ios::floatfield);
  return s;
}
#endif
