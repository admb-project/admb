/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
\file cifstrem.cpp
Implementation of the cifstream class.
*/
#include <sstream>
using std::istringstream;

#include <fvar.hpp>

#if defined(__GNUC__) && (__GNUC__ < 3)
  #pragma implementation "cifstrem.h"
#endif

#include "cifstrem.h"

/**
Destructor
*/
cifstream::~cifstream()
{
}
void cifstream::set_eof_bit(void)
{
#ifdef __BCPLUSPLUS__
  int current_state = rdstate();
  setstate(current_state | ios::eofbit);
#endif
#ifdef __ZTC__
  int current_state = rdstate();
  clear(current_state | ios::eofbit);
#endif
}
/**
Get the signature line of inputfile.
*/
char* cifstream::signature()
{
  if (strlen(signature_line) <= 0)
  {
    int c = bp->sgetc();

    int n = 0;
    while ((n < SIGNATURE_LENGTH) && (c != '\n'))
    {
      signature_line[n++] = (char)c;
      c = bp->snextc();
    }
    signature_line[n++] = '\0';
    strcpy(comment_line, signature_line);

    // read until end of line incase line is longer than SIGNATURE_LENGTH
    while (c != '\n')
    {
      c = bp->snextc();
    }

    // just position buffer to first character of next line
    bp->snextc();

    line++;
  }
  return signature_line;
}

adstring cifstream::get_file_name(void)
{
  return file_name;
}

cifstream::cifstream(const char* fn, int open_m, char cc)
#if defined (_MSC_VER) || defined (__WAT32__)
 : ifstream(fn, ios::in | open_m) , file_name(fn)
#elif defined(__BCPLUSPLUS__)
 : ifstream(fn, ios::in | open_m) , file_name(fn)
#elif defined (__NDPX__)
 : ifstream(fn, ios::in | open_m) , file_name(fn)
#elif defined (__INTEL_COMPILER)
 : ifstream(fn) , file_name(fn)
#elif defined(__SUNPRO_CC) && (__SUNPRO_CC < 0x5140)
 : ifstream(fn, ios::in | open_m) , file_name(fn)
#elif defined (__ZTC__)
 : ios(&buffer), ifstream(fn, ios::in | open_m) , file_name(fn)
#else
 : ifstream(fn, ios::in | std::ios::openmode(open_m)) , file_name(fn)
#endif
{
  bp = rdbuf();
  COMMENT_CHAR = cc;
  if (this->good())
  {
    line = 1;
    field = 0;
    ignore_eof = 1;
  }
  else
  {
    line = 0;
    field = 0;
    ignore_eof = 0;
  }
  memset(comment_line, '\0', SIGNATURE_LENGTH);
  memset(signature_line, '\0', SIGNATURE_LENGTH);
}

void cifstream::filter(void)
{
  //char testc = bp->NEXTCHAR();
  int testc = bp->sgetc();
 // cout << "in filter testc= " << testc << endl;
  while (isspace(testc))
  {
    testc = bp->snextc();
 //   cout << "in filter testc= " << testc << endl;
  }

  while ( (good()) && (testc == COMMENT_CHAR) && (testc != EOF))
  {
    int n = 0;
    // skip characters until newline
    do
    {
      if (n < SIGNATURE_LENGTH)
        comment_line[n++] = (char)testc;

      testc = bp->snextc();
      //cout << "in filter testc= " << testc << endl;
      if (testc == '\n')
      {
        comment_line[n++] = '\0';
        if (line == 1)
          strcpy(signature_line, comment_line);
        line ++;
        field = 0;
      }
    } while (testc != '\n');

    // get first character in next line
    testc = bp->snextc();

    while (testc == ' ' || testc == '\n' || testc == '\r')
      testc = bp->snextc();
  }
  if ( (!good()) || (testc == EOF))
  {
    if (testc == EOF)
      set_eof_bit();
    report_error(
      "function: void cifstream::prefilter(); premature end of file?");
  }
}

void cifstream::get_field(char* s, int space_flag)
{
  filter();

  // remove leading blanks
  int testc = bp->sgetc();
  while (isspace(testc))
  {
    testc = bp->snextc();
  }

  int n = 0;
  if (!space_flag)
  {
    while ( (n < FILTER_BUF_SIZE) && !isspace(testc) && (testc != EOF))
    {
      s[n++] = (char)testc;
      testc = bp->snextc();
    }
  }
  else
  {
    while ( (n < FILTER_BUF_SIZE) && (testc != EOF))
    {
      s[n++] = (char)testc;
      testc = bp->snextc();
    }
  }
  if (n>=FILTER_BUF_SIZE)
  {
    report_error("function: void cifstream::prefilter();"
        " Buffer size exceeded?");
  }

  if ( (!good()) || (testc == EOF))
  {
    if (testc == EOF)
      set_eof_bit();
    report_error(
      "function: void cifstream::prefilter(); premature end of file?");
  }
  s[n++] = '\0';
  field ++;
}
/**
Reads to s from input cifstream.

\param s adstring
*/
cifstream& cifstream::operator>>(adstring& s)
{
  char * t = new char[FILTER_BUF_SIZE];
  (*this) >> t;
  s.realloc(t);
  delete [] t;
  return (*this);
}
/**
Reads to _s from input cifstream.

\param _s adstring
*/
cifstream& cifstream::operator>>(const adstring& _s)
{
  adstring& s = (adstring&) _s;
  char * t = new char[FILTER_BUF_SIZE];
  (*this) >> t;
  s.realloc(t);
  delete [] t;
  return (*this);
}
/**
Reads to str from input cifstream.

\param str line_adstring
*/
cifstream& cifstream::operator>>(line_adstring& str)
{
  filter();
  char line[256];
  getline(line, 256);
  str.realloc(&line[0]);
  return *this;
}
/**
Reads to str from input cifstream.

\param str line_adstring
*/
cifstream& cifstream::operator>>(const line_adstring& str)
{
  return operator>>(const_cast<line_adstring&>(str));
}
/**
Reads to c from input cifstream.

\param c char*
*/
cifstream& cifstream::operator>>(char* c)
{
  get_field(c);
  return *this;
}
/**
Reads to c from input cifstream.

\param c char*
*/
cifstream& cifstream::operator>>(const char* c)
{
  get_field(const_cast<char*>(c));
  return *this;
}
/**
Reads to i from input cifstream.

\param i long
*/
cifstream& cifstream::operator>>(const long& i)
{
  char * s = new char[FILTER_BUF_SIZE];
  get_field(s);
  istringstream is(s);
  is >> (long&) i;
#ifdef __NDPX__
  if (is.eof()) is.clear();
#endif
  if (!is)
  {
    this->clear(is.rdstate());
    report_error("lont int extraction operator");
  }
  delete []s;
  return *this;
}

#if defined(__ADSGI__)
istream& istream::operator>>(long long & x)
{
  long int i;
  (*this) >> i;
  x=i;
  return *this;
}
#else
/**
Reads to _i from input cifstream.

\param _i long long
*/
cifstream& cifstream::operator>>(const long long& _i)
{
  ADUNCONST(long long,i)
  char * s = new char[FILTER_BUF_SIZE];
  get_field(s);
  istringstream is(s);
  is >> i;
#ifdef __NDPX__
  if (is.eof()) is.clear();
#endif
  if (!is)
  {
    this->clear(is.rdstate());
    report_error("lont int extraction operator");
  }
  delete []s;
  return *this;
}
/**
Reads to i from input cifstream.

\param i long long
*/
cifstream& cifstream::operator>>(long long& i)
{
  char * s = new char[FILTER_BUF_SIZE];
  get_field(s);
  istringstream is(s);
  is >> i;
#ifdef __NDPX__
  if (is.eof()) is.clear();
#endif
  if (!is)
  {
    this->clear(is.rdstate());
    report_error("lont int extraction operator");
  }
  delete []s;
  return *this;
}
#endif

void js_strip_leading_zeros(char * s)
{
  size_t n = strlen(s) - 1;
  size_t i = 0;

  while ((i < n) && (s[i]=='0') )
  {
     s[i] = ' ';
     i++;
  }
}
/**
Reads to i from input cifstream.

\param i int
*/
cifstream& cifstream::operator>>(const int& i)
{
  char * s = new char[FILTER_BUF_SIZE];
  get_field(s);
  //cout << "cifstream& cifstream::operator >> (int& i) s = '" << s
  //     << "'" << endl;
  js_strip_leading_zeros(s);
  istringstream is(s);
  is >> (int&)i;
#ifdef __NDPX__
  if (is.eof()) is.clear();
#endif
  if (!is)
  {
    this->clear(is.rdstate());
    report_error("int extraction operator");
  }
  delete []s;
  return *this;
}
/**
Reads to _x from input cifstream.

\param _x double
*/
cifstream& cifstream::operator>>(const double& _x)
{
  double& x = (double&)(_x);
  //char * s = new char[FILTER_BUF_SIZE];
  char* s = (char*)malloc(8000*sizeof(char));
  if (s)
  {
    get_field(s);
    if (s[0]=='#' && s[1] == '\0')
      get_field(s);

#if !defined(__BORLANDC__)
    istringstream is(s);
    if (!is)
    {
      this->clear(is.rdstate());
      report_error("double extraction operator");
    }
    is >> x;

  #ifdef __NDPX__
    if (is.eof()) is.clear();
  #endif
    if (!is)
    {
      this->clear(is.rdstate());
      report_error("double extraction operator");
    }
#else
    char* end=0;
    x=strtod(s,&end);
#endif

    //delete [] s;
    free(s);
    s = 0;
  }
  return *this;
}
/**
Reads to x from input cifstream.

\param x float
*/
cifstream& cifstream::operator>>(const float& x)
{
  char * s = new char[FILTER_BUF_SIZE];
  get_field(s);
  istringstream is(s);
  is >> (float&)x;
#ifdef __NDPX__
  if (is.eof()) is.clear();
#endif
  if (!is)
  {
    this->clear(is.rdstate());
    report_error("float extraction operator");
  }
  delete []s;
  return *this;
}
/**
\todo Need Test case
*/
cifstream& cifstream::getline(char* s, int k, char d)
{
  filter();

  s[0] = '\0';
  int n = 0;
  int testc = bp->sbumpc();
  while ( (!eof()) && (n < k) && (testc != d) && (testc != EOF))
  {
    s[n++] = (char)testc;
    testc = bp->sbumpc();
  }
  s[n++] = '\0';

  return *this;
}

/*
void cifstream::report_error(const char * msg)
{
  int ss  = rdstate();
  //cout << "stream state = " << ss << endl;
#ifdef __BCPLUSPLUS___
  int end = eof();
#endif
#ifdef __ZTC__
  int end = (ss < 4);
#endif
  //cout << "eof() = " << end << endl;
  //cout << "ignore_eof = " << ignore_eof << endl;

  if (!end || (end && ignore_eof))
  {
    cerr << "\n** error reading file '" << file_name
         << "' at line " << line
         << ", field " << field
         << endl;
    if (msg)
      cerr << "   " << msg << endl;
    if (end)
      cerr << "   end of file" << endl;
    //exit(1);
  }
}
*/

void cifstream::report_error(const char * msg) {;}

/*
#if !defined(__ADSGI__)
  void strnset(char * comment_line, char x, size_t len)
#else
  void strnset(char * comment_line, const char x, size_t len)
#endif
  {
    unsigned int tlen;
    //len=100;
    //tlen=strlen(comment_line);
    tlen=strlen("x");
    if (tlen>len)tlen=len;
    memset(comment_line,x,tlen);
  }
*/
