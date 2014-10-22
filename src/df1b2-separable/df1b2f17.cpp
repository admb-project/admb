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
#include <df1b2fun.h>

#ifndef _MSC_VER
  #include <unistd.h>
#endif
/**
 * Description not yet available.
 * \param
 */
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
#if defined (_MSC_VER)
  remove(filename);
#else
  unlink(filename);
#endif
}

/**
 * Description not yet available.
 * \param
 */
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
#if defined (_MSC_VER)
  remove(filename);
#else
  unlink(filename);
#endif
}
