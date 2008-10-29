#ifndef CIFSTREM_H
  #define CIFSTREM_H

#ifdef __BCPLUSPLUS__
  #include <fstream.h>
  #include <strstrea.h>
#endif
#ifdef __ZTC__
  #include <iomanip.hpp>
  #include <fstream.hpp>
  #include <strstrea.hpp>
#endif
#ifdef __NDPX__
  #include <fstream.h>
  #include <sstream.h>
  extern "C" {
  #include <dos.h>
  }
#endif

#if defined(__GNU__) || defined(__GNUDOS__)
  #include <fstream.h>
  #include <strstrea.h>
#endif

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#ifndef FVAR_HPP
  class dvar_vector;
  class dvector;
  class svector;
  class ivector;
  class lvector;
  class dvar_matrix;
  class d3_array;
  class s3_array;
  class dmatrix;
  class smatrix;
  class imatrix;
  class lmatrix;
#endif

#ifndef DOUBLE
  class svector;
  class smatrix;
  class s3_array;
#endif

extern const int FILTER_BUF_SIZE;
extern const int SIGNATURE_LENGTH;

#define HERE cout << "reached line " << __LINE__ << " in " << __FILE__ << endl;

class myifstream : public ifstream , myistream; 

class myistream : public istream, myios;



class cifstream : public myifstream
{
#if defined(__ZTC__) || defined(__GNUDOS__)
  streambuf* bp;
#endif
  char COMMENT_CHAR;
  char comment_line[SIGNATURE_LENGTH+1];
  char signature_line[SIGNATURE_LENGTH+1];
  char file_name[13];
  int  line;
  int  field;
  int  ignore_eof;

  void filter(void);
  void get_field(char * s);
  void report_error(const char* s = NULL);
  void set_eof_bit(void);

public:

  cifstream(const char*, int = ios::nocreate, char cc = '#');
  #ifdef __BCPLUSPLUS__
  cifstream() : myifstream() { ; }
  #endif
  #ifdef __NDPX__
  cifstream() : myifstream() { ; }
  #endif
  #ifdef __ZTC__
  cifstream() : ios(&buffer), myifstream() { ; }
  #endif

  void open(const char*, int = ios::nocreate);

  char* comment() { return comment_line; }
  char* signature();

  cifstream& operator >> (long& i);
  cifstream& operator >> (int& i);
  cifstream& operator >> (double& x);
  cifstream& operator >> (float& x);
  cifstream& operator >> (char* x);
  cifstream& getline(char*, int, char = '\n');

  cifstream& operator>>(dvar_vector& z);
  cifstream& operator>>(dvector& z);
  //cifstream& operator>>(svector& z);
  cifstream& operator>>(lvector& z);
  cifstream& operator>>(ivector& z);

  void set_ignore_eof() {ignore_eof = 0;}
  void set_use_eof() {ignore_eof = 1;}
};

cifstream& operator>>(cifstream& istr, dvar_matrix& z);
cifstream& operator>>(cifstream& istr, d3_array& z);
//cifstream& operator>>(cifstream& istr, s3_array& z);
cifstream& operator>>(cifstream& istr, dmatrix& z);
//cifstream& operator>>(cifstream& istr, smatrix& z);
cifstream& operator>>(cifstream& istr, imatrix& z);
//cifstream& operator>>(cifstream& istr, lmatrix& z);

#endif //#define CIFSTREM_H
