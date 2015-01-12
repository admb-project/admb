/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California
 */

#include <fvar.hpp>

#pragma implementation "cifstrem.h"

#include "cifstrem.h"
/*
#ifdef __GNUDOS__
  void strnset(char *, const char, size_t n); // is never referenced
#endif
*/
void cifstream::set_eof_bit(void)
{
  int current_state = rdstate();
#ifdef __BCPLUSPLUS__
  setstate(current_state | ios::eofbit);
#endif
#ifdef __ZTC__
  clear(current_state | ios::eofbit);
#endif
}


char* cifstream::signature()
{
  if (strlen(signature_line) <= 0)
  {
    char c = bp->sgetc();
    //COUT_TRACE(c)
    int n = 0;
    while ( (n < SIGNATURE_LENGTH) && (c != '\n') )
    {
      signature_line[n++] = c;
      c = bp->snextc();
     // cout << "in sig testc= " << c << endl; 
    }
    signature_line[n++] = '\0';
    strcpy(comment_line, signature_line);

    // read until end of line incase line is longer than SIGNATURE_LENGTH
    while (c != '\n')
    {
      c = bp->snextc();
      //cout << "in sig testc= " << c << endl; 
    }

    // position buffer to first character of next  line
    c = bp->snextc();
    line ++;
  }
  return signature_line;
}

adstring cifstream::get_file_name(void)
{ 
  return file_name;
}

cifstream::cifstream(const char* fn, int open_m, char cc) 
#if defined (__MSVC32__) || defined (__WAT32__)
 : ifstream(fn, ios::in | open_m) , file_name(fn)
#elif defined(__BCPLUSPLUS__)
 : ifstream(fn, ios::in | open_m) , file_name(fn)
#elif defined (__NDPX__)
 : ifstream(fn, ios::in | open_m) , file_name(fn)
#elif defined (__GNUDOS__)
 : ifstream(fn, ios::in | open_m) , file_name(fn)
#elif defined (__ZTC__)
 : ios(&buffer), ifstream(fn, ios::in | open_m) , file_name(fn)
#else
  xxxx need to define this foir this compiler you idiot!
#endif
{
  #if defined(__ZTC__) || defined(__GNUDOS__) || defined (__WAT32__)
    bp = rdbuf();
  #endif
#if defined(__MSVC32__)
#  if (__MSVC32__  >= 7) 
    bp = rdbuf();
#  endif
#endif
#if defined(__BORLANDC__)
#  if (__BORLANDC__  >= 0x0520) 
    bp = rdbuf();
#  endif
#endif
  COMMENT_CHAR = cc;
  if (this->good())
  {
    line = 1;
    field = 0;
    memset(comment_line, '\0', SIGNATURE_LENGTH);
    memset(signature_line, '\0', SIGNATURE_LENGTH);
    ignore_eof = 1;
  }
}
//#define COUT_TRACE(x) cout << x << endl;

void cifstream::filter(void)
{
  //HERE
  //char testc = bp->NEXTCHAR();
  char testc = bp->sgetc();
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
	comment_line[n++] = testc;

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

    while ( testc == ' ' || testc == '\n')
      testc = bp->snextc();

  }
  if ( (!good()) || (testc == EOF))
  {
    if (testc == EOF)
      set_eof_bit();
    report_error("function: void cifstream::prefilter(); premature end of file?");
  }
}

void cifstream::get_field(char * s,int space_flag)
{
  filter();
  // remove leading blanks
  char testc = bp->sgetc();
   // COUT_TRACE(testc)
  char oldtest = '\0';
  while (isspace(testc))
  {
    oldtest = testc;
    testc = bp->snextc();
  }

  int n = 0;
  if (!space_flag)
  {
    while ( (n < FILTER_BUF_SIZE) && !isspace(testc) && (testc != EOF))
    {
      s[n++] = testc;
      testc = bp->snextc();
    }
  }
  else
  {
    while ( (n < FILTER_BUF_SIZE) && (testc != EOF))
    {
      s[n++] = testc;
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
    report_error("function: void cifstream::prefilter(); premature end of file?");
  }
  s[n++] = '\0';
  field ++;
}

cifstream& cifstream::operator >> (adstring& s)
{
  char * t = new char[FILTER_BUF_SIZE];
  (*this) >> t;
  s.realloc(t);
  delete [] t;
  return (*this); 
}


// the new version
cifstream& cifstream::operator >> (const adstring& _s)
{
  adstring& s = (adstring&) _s;
  char * t = new char[FILTER_BUF_SIZE];
  (*this) >> t;
  s.realloc(t);
  delete [] t;
  return (*this); 
}


cifstream& cifstream::operator >> (const line_adstring& s)
{
  get_field((char*)(const char *)(s),1);
  return (*this); 
}


cifstream& cifstream::operator >> (char* c)
{
  get_field((char*)c);
  return *this;
}

cifstream& cifstream::operator >> (const char* c)
{
  get_field((char*)c);
  return *this;
}

cifstream& cifstream::operator >> (BOR_CONST long& i)
{
  char * s = new char[FILTER_BUF_SIZE];
  get_field(s);
  istrstream is(s, strlen(s));
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

#if defined(USE_LONG_LONG)
#if defined(__ADSGI__)
istream& istream::operator >> (long long & x)
{
  long int i;
  (*this) >> i;
  x=i;
  return *this;
}
#endif
cifstream& cifstream::operator >> (long long & i)
{
  char * s = new char[FILTER_BUF_SIZE];
  get_field(s);
  istrstream is(s, strlen(s));
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
  int n = strlen(s) - 1;
  int i = 0;

  while ((i < n) && (s[i]=='0') )
  {
     s[i] = ' ';
     i++;
  }
}

cifstream& cifstream::operator >> (BOR_CONST int& i)
{
  char * s = new char[FILTER_BUF_SIZE];
  get_field(s);
  //cout << "cifstream& cifstream::operator >> (int& i) s = '" << s 
  //     << "'" << endl;
  js_strip_leading_zeros(s);
  istrstream is(s, strlen(s));
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

cifstream& cifstream::operator >> (BOR_CONST double& _x)
{
  double& x = (double&)(_x);
  //char * s = new char[FILTER_BUF_SIZE];
  char * s = (char*) malloc(8000*sizeof(char));
  get_field(s);
  if (s[0]=='#' && s[1] == '\0')
    get_field(s);

#if !defined(__BORLANDC__)
  istrstream is(s, strlen(s));
  if (!is)
  {
    this->clear(is.rdstate());
    report_error("double extraction operator");
  }
  is >> x;
  
#  ifdef __NDPX__
  if (is.eof()) is.clear();
#  endif
  if (!is)
  {
    this->clear(is.rdstate());
    report_error("double extraction operator");
  }
  //delete []s;
#else
  char * end=0;
  x=strtod(s,&end);
#endif

  free(s);
  return *this;
}

cifstream& cifstream::operator >> (BOR_CONST float& x)
{
  char * s = new char[FILTER_BUF_SIZE];
  get_field(s);
  istrstream is(s, strlen(s));
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

cifstream& cifstream::getline(char* s, int k, char d)
{
  filter();

  s[0] = '\0';
  int n = 0;
  char testc = bp->sbumpc();
  while ( (!eof()) && (n < k) && (testc != d) && (testc != EOF))
  {
    s[n++] = testc;
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
#if defined(__GNUDOS__) 
#  if !defined(__ADSGI__)
  void strnset(char * comment_line, char x, size_t len)
#  else
  void strnset(char * comment_line, const char x, size_t len)
#  endif
  {
    unsigned int tlen;
    //len=100;
    //tlen=strlen(comment_line);
    tlen=strlen("x");
    if (tlen>len)tlen=len;
    memset(comment_line,x,tlen);
  }
#endif
*/

