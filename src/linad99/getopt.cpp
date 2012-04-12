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
#include <admodel.h>

/**
 * Description not yet available.
 * \param
 */
int get_option_number(const char * option_name,const char * error_message,
  int& option_value)
{
  int on1;
  int nopt;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,option_name,nopt))>-1)
  {
    if (!nopt)
    {
      if (ad_printf)
        (*ad_printf)("%s\n",error_message);
      else
        cerr << error_message << endl;
      on1=-1;
    }
    else
    {   
      option_value=atoi(ad_comm::argv[on1+1]);
    }
  }
  return on1;
}
