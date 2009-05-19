/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <df1b2fun.h>
fixed_smartlist::~fixed_smartlist()
{
  delete [] true_buffer;
  true_buffer=0;
  off_t pos=lseek(fp,0L,SEEK_END);
  int on1=-1;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-fsize"))>-1)
  {
    if (ad_comm::global_logfile)
    {
      *ad_comm::global_logfile << "size of file " << filename 
        << " = " << pos << endl;
    }
  }
  close(fp);
  #if defined ( __SUN__) ||  defined ( __GNU__)
   unlink(filename);
  #else
   remove(filename);
  #endif
}

fixed_smartlist2::~fixed_smartlist2()
{
  delete [] true_buffer;
  true_buffer=0;
  off_t pos=lseek(fp,0L,SEEK_END);
  int on1=-1;
  if ( (on1=option_match(ad_comm::argc,ad_comm::argv,"-fsize"))>-1)
  {
    if (ad_comm::global_logfile)
    {
      *ad_comm::global_logfile << "size of file " << filename 
        << " = " << pos << endl;
    }
  }
  close(fp);
  #if defined ( __SUN__) ||  defined ( __GNU__)
   unlink(filename);
  #else
   remove(filename);
  #endif
}

