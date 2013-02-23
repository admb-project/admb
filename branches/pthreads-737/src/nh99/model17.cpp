/*
 * $Id: model17.cpp 542 2012-07-10 21:04:06Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
#include <admodel.h>

streampos ad_comm::change_datafile_name(const adstring& s,
  const streampos& off)
{
  streampos tmp=0;
  if(ad_comm::global_datafile)
  {
    tmp=ad_comm::global_datafile->tellg();
    delete ad_comm::global_datafile;
  }
  adstring tmpstring;
  if (ad_comm::wd_flag)
    tmpstring += ad_comm::working_directory_path + s;
  else
    tmpstring=s;
  global_datafile= new cifstream(tmpstring);
  if ( (!global_datafile) || !(*global_datafile))
  {
    cerr << "Error trying to open data input file " <<  s << endl;
    delete global_datafile;
    global_datafile=NULL;
    exit(1);
  }
  if (off)
  {
    ad_comm::global_datafile->seekg(off);
  }
  return tmp;
}

streampos ad_comm::change_pinfile_name(const adstring& s,
  const streampos& off)
{
  streampos tmp=0;
  if(ad_comm::global_parfile)
  {
    tmp=ad_comm::global_parfile->tellg();
    delete ad_comm::global_parfile;
  }
  global_parfile= new cifstream(s);
  if ( (!global_parfile) || !(*global_parfile))
  {
    cerr << "Error trying to open parameter input file " <<  s << endl;
    delete global_parfile;
    global_parfile=NULL;
    exit(1);
  }
  if (off)
  {
    ad_comm::global_parfile->seekg(off);
  }
  return tmp;
}
