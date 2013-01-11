//$Id: pt_trace.h 3054 2013-01-10 22:54:36Z jsibert $
#ifndef __TRACE__
#define __TRACE__

#if (__GNUC__ >=3)
  #include <fstream>
  //using std::ofstream;
  using namespace std;
#else
  #include <fstream.h>
#endif
#include <pthread.h>

extern pthread_mutex_t trace_mutex;
/** 
\file pt_trace.h
Thread-safe macros for inserting diagnostics in the logfile
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
#define HERE pthread_mutex_lock(&trace_mutex);\
clogf << "reached " << dec << __LINE__ << " in " << __FILE__ << endl;\
pthread_mutex_unlock(&trace_mutex);

#undef HALT
/**
\def HALT
Prints the file name and line number and exits with exict code = 1.
*/
#define HALT pthread_mutex_lock(&trace_mutex);\
cout <<"\nBailing out in file"<<__FILE__<<" at line " <<__LINE__<< endl; exit(1);\
pthread_mutex_unlock(&trace_mutex);

#undef TRACE
/**
\def TRACE
Prints the value of its argument, file name and line number.
*/
#define TRACE(object) pthread_mutex_lock(&trace_mutex);\
clogf << "line " << __LINE__ << ", file " << __FILE__ << ", " << #object " = " << setprecision(5) << object << endl;\
pthread_mutex_unlock(&trace_mutex);

#undef TTRACE
/**
\def TTRACE
Prints the value of two arguments (note the double 'T'), file name and line number.
*/
#define TTRACE(o1,o2) pthread_mutex_lock(&trace_mutex);\
clogf << "line " << __LINE__ << ", file " << __FILE__ << ", " << #o1 " = " << setprecision(5) << o1<< ", " << #o2 " = " << setprecision(5) << o2 << endl;\
pthread_mutex_unlock(&trace_mutex);

#undef TTTRACE
/**
\def TTTRACE
Prints the value of three arguments (note the tripple 'T'), file name and line number.
*/
#define TTTRACE(o1,o2,o3) pthread_mutex_lock(&trace_mutex);\
clogf << "line " << __LINE__ << ", file " << __FILE__ << ", " << #o1 " = " << setprecision(5) << o1<< ", " \
<< #o2 " = " << setprecision(5) << o2 << ", " \
<< #o3 " = " << setprecision(5) << o3 << endl;\
pthread_mutex_unlock(&trace_mutex);

#undef ASSERT
/** 
\def ASSERT
It the argument is logically false, prints the file name, line number and value of argument and exits with exict code = 1.
*/
#define ASSERT(object) pthread_mutex_lock(&trace_mutex);\
if (!object) { cerr << "ASSERT: line = " << __LINE__ << " file = " << __FILE__ << " " << #object << " = " << object << " (false)\n"; exit(1); }\
pthread_mutex_unlock(&trace_mutex);

#endif // #ifndef __TRACE__
