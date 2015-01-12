/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include "fvar.hpp"
#ifdef __MSVC32__
  #define lseek _lseek
  #define  read _read
  #define write _write 
  #include <sys\stat.h>
#endif

#if defined (__WAT32__)
  #include <fcntl.h>
#endif

#if defined(__TURBOC__) && !defined(__linux__)
  #pragma hdrstop
  #include <iostream.h>
  #include <iomanip.h>
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

#if  defined(__GNU__) || defined(__linux__)
#include <memory.h>
  #if (__GNUC__ >3)
     #include <iostream>
     using namespace std;
  #else   
    #include <iostream.h>
  #endif
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#ifdef __SUN__
#include <memory.h>
#include <iostream.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifndef __MSVC32__
#include <unistd.h>
#endif
#endif

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
  char lastchar(char *);

  void byte_copy(void * dest,void * source, unsigned num_bytes);
  extern char ad_random_part[6];

  DF_FILE::DF_FILE(unsigned long int sz)
  {
    const int us=sizeof(unsigned int);
    if (sz > UINT_MAX)
    {
      cout << "Error -- largest size for CMPDIF_BUFFER_SIZE is "
        << INT_MAX<<endl;
    }
    if ( (buff=new char[sz])==NULL)
    {
      cerr << "Error trying to allocate memory for DF_FILE buffer"<<endl;
      ad_exit(1);
    }
    for (int i=0;i<sz;i++)
    {
      buff[i]='\0';
    }
    buff_size=sz;
    buff_end=sz-us-2;
    offset=0;
    toffset=0;

    char * path = getenv("ADTMP1"); // NULL if not defined

#if defined(USE_ADPVM)
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

    if (path != NULL)
#if defined (__SUN__) ||defined (__GNU__)
    {
      sprintf(&cmpdif_file_name[0],"%s/cmpdiff.%s", path,
        ad_random_part);
    }
#else
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
#endif
    else
    {
      sprintf(&cmpdif_file_name[0],"cmpdiff.%s",ad_random_part);
    }
#if defined (__MSVC32__) || defined (__WAT32__)
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
#elif ( defined (__SUN__) || defined (__GNU__) )
    file_ptr=open(cmpdif_file_name, O_RDWR | O_CREAT | O_TRUNC |
       O_BINARY, 0777);
#elif ( !defined (__GNU__) && defined (__GNUDOS__)) 
    file_ptr=open(cmpdif_file_name, O_RDWR | O_CREAT | O_TRUNC |
       O_BINARY, 0777);
#else
 xxxx // need to define this for this compiler
#endif

    if (file_ptr == -1)
    {
      if (ad_printf) (*ad_printf)("Error opening temporary gradient"
        " file %s\n", cmpdif_file_name );
      ad_exit(1);
    }
  }



  DF_FILE::~DF_FILE()
  {
    delete [] buff;
    buff=0;
    buff_end=0;

    int repfs=option_match(ad_comm::argc,ad_comm::argv,"-fsize");

    if (ad_comm::global_logfile && repfs)
    {
      my_off_t pos;
      pos=lseek(file_ptr,0,SEEK_END);
      *ad_comm::global_logfile << "size of file " << cmpdif_file_name
        << " = " << pos << endl;
    }

    if (close(file_ptr))
    {
      cerr << "Error closing file " << cmpdif_file_name << "\n";
    }
#   if defined ( __SUN__) ||  defined ( __GNU__)
      unlink(cmpdif_file_name);
#else
      adstring currentdir;
      ad_getcd(currentdir);
      int xxx=remove(cmpdif_file_name);
      if (xxx) {
        cerr << "Error trying to delete file " << cmpdif_file_name << endl;
        xxx=unlink(cmpdif_file_name);
        cout << xxx << endl;
      }
#endif
  }



void DF_FILE::fread(void* s,const size_t num_bytes)
{
  if (toffset < num_bytes)
  {
    my_off_t lpos = lseek(file_ptr,-((long int) buff_size),SEEK_CUR);
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

void DF_FILE::fwrite(void* s, const size_t num_bytes)
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

void DF_FILE::read_cmpdif_stack_buffer(my_off_t & lpos)
{
  if (lpos == -1L)
  { cerr << "Error rewinding file in DF_FILE:fread"<<endl;
    ad_exit(1);
  }
    //cout << " trying to read buff_size = " << buff_size 
      //   << " from cmpdif file" << endl;
  //cout << "offset before read is " << lseek(file_ptr,0,SEEK_CUR)<< endl;
  if (read(file_ptr,buff,buff_size)<buff_size)
  {
    cerr << "End of file trying to read "<< cmpdif_file_name << endl;
    ad_exit(1);
  }
  lpos = lseek(file_ptr,-((long int) buff_size),SEEK_CUR);
  //cout << "offset after read is " << lseek(file_ptr,0,SEEK_CUR)<< endl;
  for(int i=0;i<sizeof(unsigned int);i++)
  {
     fourb[i] = *(buff+buff_end+1+i);
  }
}

  void DF_FILE::write_cmpdif_stack_buffer(void)
  {
    //cout << " trying to write buff_size = " << buff_size 
      //   << " into cmpdif file" << endl;
    //clogf << " trying to write buff_size = " << buff_size 
         //<< " into cmpdif file" << endl;
    //cout << "offset before write is " << lseek(file_ptr,0,SEEK_CUR)<< endl;
    //if (write(file_ptr,buff,buff_size)<buff_size)
    for(int i=0;i<sizeof(unsigned int);i++)
    {
	 *(buff+buff_end+1+i)=fourb[i]; // save the offset at the
			//end of the used part of the buffer
    }
    if (write(file_ptr,buff,buff_size)<buff_size)
    {
      cerr << "End of file trying to write to file "<< cmpdif_file_name << endl;
      cerr << "There is probably no more room on the TMP1 (if defined) device\n"
      "If possible set TMP1 environment string to a device with more room\n";
      ad_exit(1);
    }
    //cout << "offset after write is " << lseek(file_ptr,0,SEEK_CUR)<< endl;
    //clogf << "offset after write is " << lseek(file_ptr,0,SEEK_CUR)<< endl;
  }

void byte_copy(void * dest,void * source, unsigned num_bytes)
{
#if !defined (__SUN__) && !defined (__WAT32__) && !defined(__ADSGI__) && !defined (__MSVC32__) && !defined(linux)
  int ii=0;
  while (ii++<num_bytes)
  {
   *((char *)dest)++ = *((char *)source)++;
  }
#else
  memcpy((char*)dest, (char*)source, num_bytes);
#endif
 }
