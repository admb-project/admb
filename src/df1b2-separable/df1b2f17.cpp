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
Destructor
*/
fixed_smartlist::~fixed_smartlist()
{
  if (true_buffer)
  {
    delete [] true_buffer;
    true_buffer = NULL;
  }
  int on1 = -1;
  if ((on1 = option_match(ad_comm::argc, ad_comm::argv, "-fsize")) > -1)
  {
    if (ad_comm::global_logfile)
    {
      off_t pos = lseek(fp, 0L, SEEK_END);
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
Destructor
*/
fixed_smartlist2::~fixed_smartlist2()
{
  if (true_buffer)
  {
    delete [] true_buffer;
    true_buffer = NULL;
  }
  int on1 = -1;
  if ((on1 = option_match(ad_comm::argc, ad_comm::argv, "-fsize")) > -1)
  {
    if (ad_comm::global_logfile)
    {
      off_t pos = lseek(fp, 0L, SEEK_END);
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
