#include <fvar.hpp>

#ifdef __GNUC__
#include <sstream>
using std::istringstream;
#else
#include <strstream>
using std::istrstream;
#endif

int atoi(adstring& s)
{
#ifdef __GNUC__
  istringstream is((char*)s);
#else
  istrstream is((char*)s);
#endif
  int i;
  is >> i;
  return i;
}
