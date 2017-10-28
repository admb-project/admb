/*
Author: David Fournier
Copyright (c) 2008-2016 ADMB Foundation and
  Regents of the University of California
*/
#include "fvar.hpp"
#include <fcntl.h>
#if !defined(_MSC_VER) && !defined(__MINGW64__)
  #include <limits>
#endif

#ifdef _MSC_VER
  #include <sys\stat.h>
#else
  #include <iostream>
  using namespace std;
  #include <memory.h>
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

#if defined(__TURBOC__)
  #pragma hdrstop
  #include <iostream.h>
  #include <iomanip.h>
  #include <sys\stat.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #define S_IREAD 0000400
  #define S_IWRITE 0000200
#endif

#ifdef __NDPX__
  #define O_RDONLY 0
  #define O_WRONLY 1
  #define O_RDWR 2
  extern "C"
  {
    int LSEEK(int, int, int);
    int open(const char*, int);
    int creat(const char*, int);
    int close(int);
    int write(int, char*, int);
    int read(int, char*, int);
  };
#endif

#ifdef __SUN__
#include <memory.h>
#include <iostream.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#endif

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char lastchar(char*);

#if defined(__ADSGI__)
/**
Copies count bytes from the object pointed to by src to the
object pointed to by dest.

\param dest pointer to the memory location to copy to
\param source pointer to the memory location to copy from
\param num_bytes number of bytes to copy
*/
void byte_copy(void* dest, void* source, const size_t num_bytes)
{
  char* pdest = (char*)dest;
  char* psource = (char*)source;
  int ii=0;
  while (ii < num_bytes)
  {
    //*((char *)dest)++ = *((char *)source)++;
    *pdest = *psource;
    pdest++;
    psource++;
    ii++;
  }
  //memcpy((char*)dest, (char*)source, num_bytes);
}
#endif

extern char ad_random_part[6];

/**
Constructor to allocate buffer.

\param nbytes size of buffer
*/
DF_FILE::DF_FILE(const size_t nbytes):
  buff_end(static_cast<OFF_T>(nbytes)),
#if defined(_MSC_VER) || defined(__MINGW64__)
  buff_size(static_cast<unsigned int>(nbytes + sizeof(OFF_T) + 1))
#else
  buff_size(nbytes + sizeof(OFF_T) + 1)
#endif
{
#if defined(_MSC_VER) || defined(__MINGW64__)
  if (nbytes > UINT_MAX)
  {
    cout << "Error -- largest size for CMPDIF_BUFFER_SIZE = "
         << UINT_MAX << endl;
    ad_exit(1);
  }
#else
  if (nbytes > std::numeric_limits<OFF_T>::max())
  {
    cout << "Error -- largest size for CMPDIF_BUFFER_SIZE is "
         << INT_MAX<<endl;
  }
#endif

  buff = new char[buff_size];
  if (buff == NULL)
  {
    cerr << "Error trying to allocate memory for DF_FILE buffer"<<endl;
    ad_exit(1);
  }
#ifndef OPT_LIB
  memset(buff, 0, buff_size);
#endif

  offset = 0;
  toffset = 0;

  char* path = getenv("ADTMP1"); // NULL if not defined

#if defined(USE_ADPVM)
  adstring string_path;
  if (path) string_path=path;

  adstring currdir;
  ad_getcd(currdir);
  if (ad_comm::pvm_manager)
  {
    int on = 0;
    int nopt = 0;
    if ((on = option_match(ad_comm::argc,ad_comm::argv,"-slave",nopt)) > -1)
    {
      if (nopt == 1)
      {
        int ierr=make_sub_directory(ad_comm::argv[on+1]);
        ad_comm::subdir=ad_comm::argv[on+1];
        string_path+=ad_comm::subdir;
        path=(char*) string_path;
      }
      else
      {
        cerr << "Wrong number of options to -slave -- must be 1"
          " you have " << nopt << endl;
        ad_exit(1);
      }
    }
  }
#endif

  if (path != NULL && strlen(path) <= 45)
#if !defined (_WIN32)
  {
      sprintf(&cmpdif_file_name[0],"%s/cmpdiff.%s", path,
        ad_random_part);
  }
#else
  {
    if (lastchar(path) != '\\')
    {
      sprintf(&cmpdif_file_name[0],"%s\\cmpdiff.%s", path,
        ad_random_part);
    }
    else
    {
      sprintf(&cmpdif_file_name[0],"%scmpdiff.%s", path,
        ad_random_part);
    }
  }
#endif
  else
  {
    sprintf(&cmpdif_file_name[0],"cmpdiff.%s",ad_random_part);
  }
#if defined (_MSC_VER) || defined (__WAT32__)
  file_ptr=open(cmpdif_file_name, O_RDWR | O_CREAT | O_TRUNC |
                     O_BINARY, S_IREAD | S_IWRITE);
#elif defined (__TURBOC__)
  file_ptr=open(cmpdif_file_name, O_RDWR | O_CREAT | O_TRUNC |
                     O_BINARY, S_IREAD | S_IWRITE);
#elif defined (__ZTC__)
  file_ptr=open(cmpdif_file_name, O_RDWR | O_CREAT | O_TRUNC ,
                     S_IREAD | S_IWRITE);
#elif  defined (__NDPX__)
  file_ptr=creat(cmpdif_file_name, O_RDWR);
#else
  file_ptr=open(cmpdif_file_name, O_RDWR | O_CREAT | O_TRUNC |
       O_BINARY, 0777);
#endif

  if (file_ptr == -1)
  {
    if (ad_printf) (*ad_printf)("Error opening temporary gradient"
        " file %s\n", cmpdif_file_name );
    ad_exit(1);
  }
}
/**
Destructor
*/
DF_FILE::~DF_FILE()
{
  delete [] buff;
  buff = nullptr;

  int repfs = option_match(ad_comm::argc,ad_comm::argv,"-fsize");

  if (ad_comm::global_logfile && repfs)
  {
    OFF_T pos = LSEEK(file_ptr, 0, SEEK_END);
    *ad_comm::global_logfile << "size of file " << cmpdif_file_name
        << " = " << pos << endl;
  }
  if (close(file_ptr))
  {
    cerr << "Error closing file " << cmpdif_file_name << "\n";
  }
#if !defined (_WIN32)
  unlink(cmpdif_file_name);
#else
  adstring currentdir;
  ad_getcd(currentdir);
  int xxx=remove(cmpdif_file_name);
  if (xxx)
  {
    cerr << "Error trying to delete file " << cmpdif_file_name << endl;
    xxx=unlink(cmpdif_file_name);
    cout << xxx << endl;
  }
#endif
}
/**
Reads num_bytes from buffer and copies to s.

\param s pointer to copy bytes from.
\param num_bytes number of bytes to read from buffer.
*/
void DF_FILE::fread(void* s, const size_t num_bytes)
{
  if (toffset < static_cast<OFF_T>(num_bytes))
  {
    OFF_T lpos = LSEEK(file_ptr, -static_cast<OFF_T>(buff_size), SEEK_CUR);
    read_cmpdif_stack_buffer(lpos);
    offset -= num_bytes;
    toffset = offset;
  }
  else
  {
    toffset-=num_bytes; //decrement the temporary offset count
  }
#if defined(__ADSGI__)
  byte_copy((char*)s, buff + toffset, num_bytes);
#else
  memcpy(s, buff + toffset, num_bytes);
#endif
  offset=toffset;
}
/**
Reads num_bytes from s and writes to buffer.

\param s pointer to read bytes from.
\param num_bytes number of bytes to write to buffer.
*/
void DF_FILE::fwrite(const void* s, const size_t num_bytes)
{
#ifdef NO_DERIVS
  if (gradient_structure::no_derivatives)
  {
    return;
  }
#endif
  toffset += num_bytes; //increment the temporary offset count
  if (toffset > buff_end)
  {
    if (static_cast<OFF_T>(num_bytes) > buff_end)
    {
      OFF_T us = toffset + static_cast<OFF_T>(sizeof(size_t) + 2L);
      cerr << "Need to increase gradient_structure::CMPDIF_BUFFER_SIZE "
       "to at least" << us << endl;
    }
    write_cmpdif_stack_buffer();
    toffset = static_cast<OFF_T>(num_bytes);
    offset=0;
  }
#if defined(__ADSGI__)
  byte_copy(buff+offset,(char *) s,num_bytes);
#else
  memcpy(buff + offset, s, num_bytes);
#endif
  offset = toffset;
}
/**
 * Description not yet available.
 * \param
 */
void DF_FILE::read_cmpdif_stack_buffer(OFF_T& lpos)
{
  if (lpos == -1L)
  {
    cerr << "Error rewinding file in DF_FILE:fread"<<endl;
    ad_exit(1);
  }
  if (READ(file_ptr, buff, buff_size) < 0)
  {
    cerr << "End of file trying to read "<< cmpdif_file_name << endl;
    ad_exit(1);
  }
  lpos = LSEEK(file_ptr, -static_cast<OFF_T>(buff_size), SEEK_CUR);
  for (size_t i = 0;i < sizeof(OFF_T); i++)
  {
    fourb[i] = *(buff+buff_end+1+i);
  }
}
/**
 * Description not yet available.
 * \param
 */
void DF_FILE::write_cmpdif_stack_buffer(void)
{
  // save the offset at the end of the used part of the buffer
  for (size_t i = 0; i < sizeof(OFF_T); i++)
  {
    *(buff+buff_end+1+i) = fourb[i];
  }
  if (WRITE(file_ptr, buff, buff_size) < 0)
  {
    cerr << "End of file trying to write to file "<< cmpdif_file_name << endl;
    cerr << "There is probably no more room on the TMP1 (if defined) device\n"
    "If possible set TMP1 environment string to a device with more room\n";
    ad_exit(1);
  }
}
