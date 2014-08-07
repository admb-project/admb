//$Id: trace.h 2853 2011-09-21 19:15:11Z jsibert $
#ifndef __TRACE__
#define __TRACE__
#if (__GNUC__ >=3)
  #include <fstream>
  using std::ofstream;
#else
  #include <fstream.h>
#endif
/** 
\file trace.h
Macros for inserting diagnostics in the logfile
*/

/** The log file.
Must be declared and opened in a different file, usually the file containing
main()
*/
extern ofstream clogf;

#undef HERE
/**
\def HERE
Indicates the line number of the file which the statement appears.
*/
#define HERE clogf << "reached " << __LINE__ << " in " << __FILE__ << endl;

#undef HALT
/**
\def HALT
Prints the file name and line number and exits with exict code = 1.
*/
#define HALT cout <<"\nBailing out in file"<<__FILE__<<" at line " <<__LINE__<< endl; exit(1);

#undef TRACE
/**
\def TRACE
Prints the value of its argument, file name and line number.
*/
#define TRACE(object) clogf << "line " << __LINE__ << ", file " << __FILE__ << ", " << #object " = " << setprecision(5) << object << endl;

#undef TTRACE
/**
\def TTRACE
Prints the value of two arguments (note the double 'T'), file name and line number.
*/
#define TTRACE(o1,o2) clogf << "line " << __LINE__ << ", file " << __FILE__ << ", " << #o1 " = " << setprecision(5) << o1<< ", " << #o2 " = " << setprecision(5) << o2 << endl;

#undef ASSERT
/** 
\def ASSERT
It the argument is logically false, prints the file name, line number and value of argument and exits with exict code = 1.
*/
#define ASSERT(object) if (!object) { cerr << "ASSERT: line = " << __LINE__ << " file = " << __FILE__ << " " << #object << " = " << object << " (false)\n"; exit(1); }
#endif
