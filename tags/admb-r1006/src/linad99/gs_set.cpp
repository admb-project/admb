/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include "fvar.hpp"
#ifdef __TURBOC__
  #pragma hdrstop
#endif
#include <limits.h>
char demo_capacity[]={"You have exceeded the capacity of this demonstration version of AD Model Builder"};
char please_buy[]= {"Please use open source version from:"};
char otter_address1[]={" http://www.admb-project.org/"};
char otter_address2[]={" http://www.admb-project.org/"};
char otter_address3[]={" http://www.admb-project.org/"};
char otter_address4[]={" users@admb-project.org"};
char otter_address5[]={" http://www.admb-project.org/"};
char cannot_set[]=" You can not reset the number of independent variables in the Demonstration version";

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::check_set_error(const char* variable_name)
{
  if (instances > 0)
  {
    cerr << "Error -- variable '" << variable_name <<"' must be set before\n"
            "declaration of gradient_structure object.\n";
    ad_exit(1);
  }
}

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::set_RETURN_ARRAYS_SIZE(int i)
{
  RETURN_ARRAYS_SIZE=i;
}

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::set_NUM_RETURN_ARRAYS(int i)
{
  check_set_error("NUM_RETURN_ARRAYS");
  NUM_RETURN_ARRAYS = i;
}

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::set_ARRAY_MEMBLOCK_SIZE(unsigned long i)
{
  cerr << " This is not the way to set the ARRAY_MEMBLOCK_SIZE -- sorry\n"
    " You set it by declaring the number of bytes you want in the\n";
  cerr << " declaration  gradient_structure gs(num_bytes)\n"
  " in your program .. the default value is 100000L\n";
  ad_exit(1);
  check_set_error("ARRAY_MEMBLOCK_SIZE");
}

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::set_CMPDIF_BUFFER_SIZE(long long int i)
{
  if ( (unsigned long int) (LLONG_MAX) < (unsigned long int)i)
  {
    long long  int max_size=LLONG_MAX;

    cerr << "\n\n It appears that the size you are setting for "
      "the\n CMPDIF_BUFFER is > " <<  LLONG_MAX <<
      "This appears\n to be an error. The maximum size argument ";
    cerr << "for the function\n"
      "--- gradient_structure::set_CMPDIF_BUFFER_SIZE(long long int i) ---\n"
      "should probably be  " << max_size << endl;
  }
  check_set_error("CMPDIF_BUFFER_SIZE");
  CMPDIF_BUFFER_SIZE = i;
}

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::set_GRADSTACK_BUFFER_SIZE(long long int i)
{
  long long int gs_size=(long long int) (sizeof(grad_stack_entry));

  if ( (unsigned long int) (LLONG_MAX) < gs_size *i)
  {
    unsigned int max_size=LLONG_MAX/gs_size;

    cerr << "\n\n It appears that the size you are setting for "
      "the\n GRADSTACK_BUFFER is > " << LLONG_MAX <<
      "This appears\n to be an error. The maximum size argument ";
    cerr << "for the function\n"
      "--- gradient_structure::set_GRADSTACK_BUFFER_SIZE(long long int i) ---\n"
      "should probably be  " << max_size << endl;
    cerr << "LLONG_MAX = " << (unsigned long int) (LLONG_MAX) << endl; 
    cerr << " i = " << i << endl; 
    cerr << " gs_size = " << gs_size << endl; 
    cerr << " i*gs_size = " << i*gs_size << endl; 
  
  }
  check_set_error("GRADSTACK_BUFFER_SIZE");
  GRADSTACK_BUFFER_SIZE = i;
}

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::set_MAX_NVAR_OFFSET(unsigned int i)
{
  check_set_error("MAX_NVAR_OFFSET");
  MAX_NVAR_OFFSET = i;
}

/**
 * Description not yet available.
 * \param
 */
void gradient_structure::set_MAX_DLINKS(int i)
{
  check_set_error("MAX_DLINKS");
#if !defined(AD_DEMO)
  MAX_DLINKS = i;
#endif
}
