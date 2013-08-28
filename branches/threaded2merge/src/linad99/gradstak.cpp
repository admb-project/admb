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
#include "fvar.hpp"
#include <adstring.hpp>

#if defined (__WAT32__)
  #include <fcntl.h>
  #include <io.h>
#endif

  #ifdef __MSVC32__
    #define lseek _lseek
    #define  read _read
    #define write _write
    #define open _open
    #define close _close
    #include <sys\stat.h>
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
  };
#endif

#ifdef __SUN__
  #include <iostream.h>
  #include <fcntl.h>
  #include <sys/stat.h>
  #include <sys/types.h>
  #ifdef __MSC__
    #define lseek _lseek
    #define  read _read
    #define write _write
    #define open _open
    #define close _close
  #endif
  #ifndef __MSVC32__
    #include <unistd.h>
  #endif
#endif

#if  defined(__GNU__) || defined(__linux__)
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

  char lastchar(char *);

  char ad_random_part[6]="tmp";

/**
 * Description not yet available.
 * \param
 */
  void fill_ad_random_part(void)
  {
   /*
    time_t t,tt;
    time(&t);
    tt=t;
    int div=1;
    for (int i=0;i<6;i++)
    {
      ad_random_part[i]=(tt/div)%10+48;
      div*=10;
    }
   */
  }

/**
 * Description not yet available.
 * \param
 */
  grad_stack::grad_stack()
  {
    gradient_structure::TOTAL_BYTES = 0;
    gradient_structure::PREVIOUS_TOTAL_BYTES=0;
    true_length = gradient_structure::GRADSTACK_BUFFER_SIZE;
    length = true_length;
    if ( (true_ptr_first = new  grad_stack_entry [(size_t)length]) == 0)
    {
      cerr << "Memory allocation error in grad_stack constructor\n"
        << " trying to allocate "
                   << length * sizeof(grad_stack_entry)<<" bytes\n";
      ad_exit(1);
    }

    test_the_pointer();

    ptr_first=true_ptr_first;
    ptr = ptr_first;
    ptr_last=ptr_first+(length-1);
//    table=new lvector(-128,250);

    _GRADFILE_PTR = -1; // set to illegal value for later checking
    end_pos  = 0;
    end_pos1 = 0;
    end_pos2 = 0;

    char* path = getenv("ADTMP"); // NULL if not defined
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
    {
    #  if defined ( __SUN__) ||  defined ( __GNU__)
      sprintf(&gradfile_name1[0],"%s/gradfil1.%s", path,ad_random_part);
    #  else
      if (lastchar(path)!='\\')
      {
        sprintf(&gradfile_name1[0],"%s\\gradfil1.%s", path,ad_random_part);
      }
      else
      {
        sprintf(&gradfile_name1[0],"%sgradfil1.%s", path,ad_random_part);
      }
    #  endif
    }
    else
    {
      sprintf(&gradfile_name1[0],"gradfil1.%s",ad_random_part);
    }

    path = getenv("ADTMP1"); // NULL if not defined
#if defined(USE_ADPVM)
    adstring string_path2;
    if (path) string_path2=path;
    string_path2+=ad_comm::subdir;
    path=(char*) string_path2;
#endif
    if (path != NULL)
    {
      #if defined ( __SUN__) ||  defined ( __GNU__)  || defined(linux)
	if (strlen(path)>0)
	{    	
	  sprintf(&var_store_file_name[0],"%s/varssave.%s",path,
            ad_random_part);
	  sprintf(&gradfile_name2[0],"%s/gradfil2.%s", path,
            ad_random_part);
	}
	else
	{    	
	  sprintf(&var_store_file_name[0],"varssave.tmp");
	  sprintf(&gradfile_name2[0],"gradfil2.tmp");
	}
      #else
        if (lastchar(path)!='\\')
        {
	  sprintf(&gradfile_name2[0],"%s\\gradfil2.%s", path,
            ad_random_part);
	  sprintf(&var_store_file_name[0],"%s\\varssave.%s",path,
            ad_random_part);
        }
        else
        {
	  sprintf(&gradfile_name2[0],"%sgradfil2.%s", path,
            ad_random_part);
	  sprintf(&var_store_file_name[0],"%svarssave.%s",path,
            ad_random_part);
        }
      #endif
    }
    else
    {
      sprintf(&gradfile_name2[0],"gradfil2.%s",
        ad_random_part);
      sprintf(&var_store_file_name[0],"varssave.%s",
        ad_random_part);
    }
    create_gradfile();

    strcpy(gradfile_name, gradfile_name1);
    _GRADFILE_PTR = _GRADFILE_PTR1;

}

/**
Destructor
*/
grad_stack::~grad_stack()
{
  int repfs=option_match(ad_comm::argc, ad_comm::argv, "-fsize");
  if (ad_comm::global_logfile && repfs)
  {
    int pos = lseek(_GRADFILE_PTR1,0,SEEK_END);
    *ad_comm::global_logfile << "size of file " << gradfile_name1
      << " = " << pos << endl;

    pos=lseek(_GRADFILE_PTR2,0,SEEK_END);
    *ad_comm::global_logfile << "size of file " << gradfile_name2
      << " = " << pos << endl;

    pos=lseek(_VARSSAV_PTR,0,SEEK_END);
    *ad_comm::global_logfile << "size of file " << var_store_file_name
      << " = " << pos << endl;
  }

  if (close(_GRADFILE_PTR1))
  {
    cerr << "Error closing file " << gradfile_name1 << "\n";
  }
  if (close(_GRADFILE_PTR2))
  {
    cerr << "Error closing file " << gradfile_name2 << "\n";
  }
  if (close(_VARSSAV_PTR))
  {
    cerr << "Error closing file " << var_store_file_name << "\n";
  }
#if defined(__SUN__) || defined( __GNU__)
  unlink(gradfile_name1);
  unlink(gradfile_name2);
  unlink(var_store_file_name);
#else
  remove(gradfile_name1);
  remove(gradfile_name2);
  remove(var_store_file_name);
#endif

  delete [] true_ptr_first;
  true_ptr_first = 0;
}

/**
 * Description not yet available.
 * \param
 */
  void  grad_stack::write_grad_stack_buffer()
  {
    unsigned int ierr;

    #ifdef GRAD_DIAG
      cout << "Grad_stack size exceeded\n ";
      cout << "Writing to temporary file -- \n";
    #endif

    ptr--;

    #ifdef GRAD_DIAG
      {
      long int lpos = lseek(_GRADFILE_PTR,0L,SEEK_CUR);
      cout << "Offset in file before write is " << lpos
                              << " bytes from the beginning\n";
      }
    #endif

    // if the buffer is really large only write the end of it
    set_gbuffer_pointers();
    unsigned nbw = (unsigned) sizeof(grad_stack_entry)* (unsigned) length;

    char * ttmp = (char *) ptr_first;
    ttmp--;

    // save the current end of file in case we can't write the whole buffer
    end_pos = lseek(_GRADFILE_PTR,0L,SEEK_CUR);
    #if !defined(__NDPX__ ) && !defined(__SUN__)  && !defined(__GNU__)
    ierr = write(_GRADFILE_PTR, ptr_first, nbw);
    #else
    ierr = write(_GRADFILE_PTR, (char*)ptr_first, nbw);
    #endif

    if  (ierr != nbw)
    {
       cout << "Wrote " << ierr <<" not " << nbw << endl;
      lseek(_GRADFILE_PTR,end_pos,SEEK_SET);
      //save the end of file for this file so we can reposition later
      end_pos1 = end_pos;
      increment_current_gradfile_ptr();
      #if !defined(__NDPX__ ) && !defined(__SUN__)   && !defined(__GNU__)
      ierr = write(_GRADFILE_PTR, ptr_first, nbw);
      #else
      ierr = write(_GRADFILE_PTR, (char*)ptr_first, nbw);
      #endif

      if  (ierr != nbw)
      {
	perror("Error writing to temporary gradient stack file");
	cerr <<"   File name: " << gradfile_name << "\n";
	#if !defined(__NDPX__ ) && !defined(__SUN__)   && !defined(__GNU__)
	cerr <<"   File length: "
	   << filelength(_GRADFILE_PTR)
           << " bytes.\n";
	#endif
	cerr <<"   Attempting to write " << nbw <<" bytes; wrote " << ierr << ".\n";
	exit(1);
      }
    }
    else
    {
      #ifdef GRAD_DIAG
	cout << "Wrote " << ierr << "bytes into temp. grad. file\n";
      #endif
    }

    #ifdef GRAD_DIAG
    {
      long int lpos = lseek(gradient_structure::_GRADFILE_PTR,0L,SEEK_CUR);
      cout << "Offset in file after write is " << lpos
				      << " bytes from the beginning\n";
    }
    #endif
    gradient_structure::TOTAL_BYTES+=nbw; //keep track of the size of the grad_stack
    ptr = ptr_first;
  }

/**
 * Description not yet available.
 * \param
 */
void grad_stack::create_gradfile()
{

  #if defined (__TURBOC__)
   _GRADFILE_PTR1=open(gradfile_name1, O_RDWR | O_CREAT |
       O_TRUNC | O_BINARY, S_IREAD | S_IWRITE);

   _VARSSAV_PTR=open(var_store_file_name, O_RDWR | O_CREAT |
       O_TRUNC | O_BINARY, S_IREAD | S_IWRITE);

  #elif defined (__ZTC__)
    _GRADFILE_PTR1=open(gradfile_name1, O_RDWR | O_CREAT |
	O_TRUNC , S_IREAD | S_IWRITE);
    _VARSSAV_PTR=open(var_store_file_name, O_RDWR | O_CREAT
	| O_TRUNC,  S_IREAD | S_IWRITE);

  #elif defined (__NDPX__)
    _GRADFILE_PTR1=creat(gradfile_name1, O_RDWR);
     _VARSSAV_PTR=creat(var_store_file_name, O_RDWR);

  #elif ( defined ( __SUN__) ||  defined ( __GNU__))

    _GRADFILE_PTR1=open(gradfile_name1, O_RDWR | O_CREAT | O_TRUNC |
      O_BINARY , 0777);
    _VARSSAV_PTR=open(var_store_file_name, O_RDWR |
      O_CREAT | O_TRUNC | O_BINARY, 0777);

  #elif (defined (__GNUDOS__) && !defined(__GNU__))
    _GRADFILE_PTR1=open(gradfile_name1, O_RDWR | O_CREAT | O_TRUNC |
		O_BINARY ,   0777);
    _VARSSAV_PTR=open(var_store_file_name, O_RDWR |
      O_CREAT | O_TRUNC | O_BINARY, 0777);

  #elif defined (__MSVC32__)
    _GRADFILE_PTR1=open(gradfile_name1, O_RDWR | O_CREAT | O_TRUNC |
		O_BINARY ,   0777);
    _VARSSAV_PTR=open(var_store_file_name, O_RDWR |
      O_CREAT | O_TRUNC | O_BINARY, 0777);

  #elif defined (__WAT32__)
   _GRADFILE_PTR1=open(gradfile_name1, O_RDWR | O_CREAT |
       O_TRUNC | O_BINARY, S_IREAD | S_IWRITE);

   _VARSSAV_PTR=open(var_store_file_name, O_RDWR | O_CREAT |
       O_TRUNC | O_BINARY, S_IREAD | S_IWRITE);
  #else
    xxxxx   // need to define this for thei compiler!
  #endif

  if (_GRADFILE_PTR1 == -1)
  {
    if (ad_printf) (*ad_printf)("Error opening temporary gradient file"
     " %s\n",gradfile_name1);
    ad_exit(1);
  }

  if (_VARSSAV_PTR == -1)
  {
    perror("Error opening temporary gradient file");
    cerr <<"  Attempting to open " << var_store_file_name <<"\n";
    ad_exit(1);
  }

  #if defined (__TURBOC__)
    _GRADFILE_PTR2=open(gradfile_name2, O_RDWR | O_CREAT | O_TRUNC |
		     O_BINARY, S_IREAD | S_IWRITE);
  #elif defined (__ZTC__)
    _GRADFILE_PTR2=open(gradfile_name2, O_RDWR | O_CREAT | O_TRUNC ,
		     S_IREAD | S_IWRITE);
  #elif defined (__NDPX__)
    _GRADFILE_PTR2=creat(gradfile_name2, O_RDWR);

  #elif ( defined (__SUN__) ||  defined (__GNU__) )
    _GRADFILE_PTR2=open(gradfile_name2, O_RDWR | O_CREAT | O_TRUNC |
		O_BINARY , 0777);

  #elif (defined (__GNUDOS__) && !defined (__GNU__))
    _GRADFILE_PTR2=open(gradfile_name2, O_RDWR | O_CREAT | O_TRUNC |
		O_BINARY , 0777);

  #elif defined (__MSVC32__)
    _GRADFILE_PTR2=open(gradfile_name2, O_RDWR | O_CREAT | O_TRUNC |
		     O_BINARY, S_IREAD | S_IWRITE);

  #elif defined (__WAT32__)
    _GRADFILE_PTR2=open(gradfile_name2, O_RDWR | O_CREAT | O_TRUNC |
		     O_BINARY, S_IREAD | S_IWRITE);
  #else
    xxxx  // need to define this for this compiler
  #endif

  if (_GRADFILE_PTR2 == -1)
  {
    perror("Error opening temporary gradient file");
    cerr <<"  Attempting to open " << gradfile_name2 <<"\n";
    ad_exit(1);
  }
}

/**
 * Description not yet available.
 * \param
 */
void grad_stack::increment_current_gradfile_ptr()
{
  if (_GRADFILE_PTR == _GRADFILE_PTR2)
  {
// If there is another file set the handle to point to it otherwise
// we are out of room
    cerr << "Attempted to open a third gradient file -- There is\n"
      "probably no more room on the TMP1 (if defined) device\n"
      "if possible set TMP1 environment string to a device with more room\n";
    ad_exit(1);
  }
   strcpy(gradfile_name, gradfile_name2);
  _GRADFILE_PTR = _GRADFILE_PTR2;
}

/**
 * Description not yet available.
 * \param
 */
int grad_stack::decrement_current_gradfile_ptr()
// If there is a previous file set the handle to point to it otherwise
// return a -1
{
  if (_GRADFILE_PTR == _GRADFILE_PTR1)
  {
    return -1;
  }
  strcpy(gradfile_name, gradfile_name1);
  _GRADFILE_PTR = _GRADFILE_PTR1;
  return 0;
}

#ifndef __MSC__
  int& grad_stack::gradfile_handle()
#else
  int grad_stack::gradfile_handle()
#endif
{
  return(_GRADFILE_PTR);
}

/**
 * Description not yet available.
 * \param
 */
char* grad_stack::get_gradfile_name()
{
  return(gradfile_name);
}

/**
 * Description not yet available.
 * \param
 */
void grad_stack::set_gbuffer_pointers()
{
  if (length > 10000L)
  {
    //make the buffer end_buf_size
    unsigned int end_buf_size=5000L;
    ptr_first+=length-end_buf_size;
    length=end_buf_size;
  }
}

/**
 * Description not yet available.
 * \param
 */
void grad_stack::set_gradient_stack0(void (* func)(void),double * dep_addr)
{
  #ifdef NO_DERIVS
    if (!gradient_structure::no_derivatives)
    {
  #endif
      if (ptr > ptr_last)
      {
         // current buffer is full -- write it to disk and reset pointer
         // and counter
         this->write_grad_stack_buffer();
      }
      ptr->func = func;
      ptr->dep_addr = dep_addr;
      ptr++;
  #ifdef NO_DERIVS
    }
  #endif
}
