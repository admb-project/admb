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
#define HOME_VERSION
#include "fvar.hpp"
#include "smartbuf.h"
#ifdef _MSC_VER
  #define lseek _lseek
  #define  read _read
  #define write _write
  #include <sys\stat.h>
#else
  #include <iostream>
  using namespace std;
  #include <memory.h>
  #include <fcntl.h>
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>
#endif

#if defined(__TURBOC__)
  #pragma hdrstop
  #include <iostream.h>
  #include <sys\stat.h>
  #include <fcntl.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
  #define S_IREAD 0000400
  #define S_IWRITE 0000200
  #include <fcntl.h>
#endif

#ifdef __NDPX__
  #define O_RDONLY 0
  #define O_WRONLY 1
  #define O_RDWR 2
  extern "C"
  {
    int lseek(int, int, int);
    int open(const char*, int);
    int creat(const char*, int);
    int close(int);
    int write(int, char*, int);
    int read(int, char*, int);
  };
#endif

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
  char lastchar(char *);

  void byte_copy(void * dest,void * source, unsigned num_bytes);
  extern char ad_random_part[6];

/**
 * Description not yet available.
 * \param
 */
  ad_sbuffer::ad_sbuffer(unsigned long int sz,const char * froot)
  {
    // need some code here to decide where to put the file
    file_name=froot;

    const int us=sizeof(unsigned int);
    if (sz > UINT_MAX)
    {
      cout << "Error -- largest size for CMPDIF_BUFFER_SIZE is "
        << INT_MAX<<endl;
    }
    if ( (buff=new char[sz])==NULL)
    {
      cerr << "Error trying to allocate memory for ad_sbuffer buffer"<<endl;
      ad_exit(1);
    }
    buff_size=sz;
    buff_end=sz-us-2;
    offset=0;
    toffset=0;


#if defined(USE_ADPVM)
    char * path = getenv("ADTMP1"); // NULL if not defined
    adstring string_path;
    if (path) string_path=path;
    int on=0;
    int nopt=0;
    adstring currdir;
    ad_getcd(currdir);
    if (ad_comm::pvm_manager)
    {
      if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-slave",nopt))>-1)
      {
        if (nopt ==1)
        {
          {
            int ierr=make_sub_directory(ad_comm::argv[on+1]);
            ad_comm::subdir=ad_comm::argv[on+1];
            string_path+=ad_comm::subdir;
            path=(char*) string_path;
          }
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

#if defined(_MSC_VER)
    file_ptr=open(file_name, O_RDWR | O_CREAT | O_TRUNC );
#else
    file_ptr=open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777 );
#endif

    if (file_ptr == -1)
    {
      if (ad_printf) (*ad_printf)("Error opening temporary gradient"
        " file %s\n", (char*)file_name );
      ad_exit(1);
    }
  }



  ad_sbuffer::~ad_sbuffer()
  {
    delete buff;
    buff=0;
    buff_end=0;

    if (close(file_ptr))
    {
      cerr << "Error closing file " << cmpdif_file_name << "\n";
    }
#if defined (_MSC_VER)
      adstring currentdir;
      ad_getcd(currentdir);
      int xxx=remove(cmpdif_file_name);
      if (xxx) {
        cerr << "Error trying to delete file " << cmpdif_file_name << endl;
        xxx=unlink(cmpdif_file_name);
        cout << xxx << endl;
      }
#else
      unlink(cmpdif_file_name);
#endif
  }


/**
 * Description not yet available.
 * \param
 */
void ad_sbuffer::fread(void* s,const size_t num_bytes)
{
  if (toffset < num_bytes)
  {
    long lpos = lseek(file_ptr,-((long int) buff_size),SEEK_CUR);
    //cout << "In fread filepos = " << lpos << endl;
    read_cmpdif_stack_buffer(lpos);
/*
    for(int i=0;i<sizeof(unsigned int);i++)
    {
       fourb[i] = *(buff+buff_end+1+i);
    }
*/
   // cout << "roffset: " << offset << endl;
    offset -= num_bytes;
    toffset = offset;
  }
  else
  {
    toffset-=num_bytes; //decrement the temporary offset count
  }
  byte_copy((char *)s,buff+toffset,num_bytes);
  offset=toffset;
}

/**
 * Description not yet available.
 * \param
 */
void ad_sbuffer::fwrite(void* s, const size_t num_bytes)
{
  #ifdef NO_DERIVS
    if (gradient_structure::no_derivatives)
    {
      return;
    }
  #endif
  toffset+=num_bytes; //increment the temporary offset count
  if (toffset>buff_end)
  {
    if (num_bytes > buff_end)
    {
      const int us=sizeof(unsigned int);
      cerr << "Need to increase gradient_structure::CMPDIF_BUFFER_SIZE "
       "to at least" << long (toffset)+long(us)+2L << endl;
    }
    write_cmpdif_stack_buffer();
    toffset=num_bytes;
    offset=0;
  }
  byte_copy(buff+offset,(char *) s,num_bytes);
  offset=toffset;
}

/**
 * Description not yet available.
 * \param
 */
void ad_sbuffer::read_cmpdif_stack_buffer(long int& lpos)
{
  if (lpos == -1L)
  { cerr << "Error rewinding file in ad_sbuffer:fread"<<endl;
    ad_exit(1);
  }
    //cout << " trying to read buff_size = " << buff_size
      //   << " from cmpdif file" << endl;
  //cout << "offset before read is " << lseek(file_ptr,0,SEEK_CUR)<< endl;
  if (read(file_ptr,buff,buff_size) < 0)
  {
    cerr << "End of file trying to read "<< cmpdif_file_name << endl;
    ad_exit(1);
  }
  lpos = lseek(file_ptr,-((long int) buff_size),SEEK_CUR);
  //cout << "offset after read is " << lseek(file_ptr,0,SEEK_CUR)<< endl;
  for(unsigned int i=0;i<sizeof(unsigned int);i++)
  {
     fourb[i] = *(buff+buff_end+1+i);
  }
}

/**
 * Description not yet available.
 * \param
 */
  void ad_sbuffer::write_cmpdif_stack_buffer(void)
  {
    //cout << " trying to write buff_size = " << buff_size
      //   << " into cmpdif file" << endl;
    //clogf << " trying to write buff_size = " << buff_size
         //<< " into cmpdif file" << endl;
    //cout << "offset before write is " << lseek(file_ptr,0,SEEK_CUR)<< endl;
    //if (write(file_ptr,buff,buff_size)<buff_size)
    for(unsigned int i=0;i<sizeof(unsigned int);i++)
    {
      // save the offset at the end of the used part of the buffer
      *(buff+buff_end+1+i)=fourb[i];
    }
    if (write(file_ptr,buff,buff_size) < 0)
    {
      cerr << "End of file trying to write to file "<< cmpdif_file_name << endl;
      cerr << "There is probably no more room on the TMP1 (if defined) device\n"
      "If possible set TMP1 environment string to a device with more room\n";
      ad_exit(1);
    }
    //cout << "offset after write is " << lseek(file_ptr,0,SEEK_CUR)<< endl;
    //clogf << "offset after write is " << lseek(file_ptr,0,SEEK_CUR)<< endl;
  }

/**
 * Description not yet available.
 * \param
 */
void byte_copy(void* dest, void* source, unsigned num_bytes)
{
#if defined(__ADSGI__)
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
#else
  memcpy((char*)dest, (char*)source, num_bytes);
#endif
 }
