#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(__BORLANDC__) || defined(__GNUDOS__)
  #include <fstream.h>
#endif
#ifdef __ZTC__
  #include <fstream.hpp>
#endif

#ifndef PRN_T
#define PRN_T
class prnstream : public ofstream
{
private:
  int count;
  void outstr(const char*, const char q = '\0');
public:
  prnstream(const char* fn);

  prnstream& put(char);

//  prnstream& operator << (const char);
  prnstream& operator << (const char*);
  prnstream& operator << (const int);
  prnstream& operator << (const long);
  prnstream& operator << (const float);
  prnstream& operator << (const double);

  prnstream& operator<< (prnstream& (*fn)(prnstream &));
//  prnstream& operator<< (ios& (*_f)(ios&));

};

inline prnstream& prnstream::operator<< (prnstream& (*_f)(prnstream &))
		{ return (*_f)(*this); }

prnstream& endl(prnstream&);

#endif // #ifndef PRN_T
