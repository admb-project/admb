/**
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
/**
Change the global_parfile stream using file s.
Returns the current streampos of existing open file,
else returns 0.

\param input_file new input file.
\param off change to this offset if file exists.
*/
streampos ad_comm::change_pinfile_name(
  const adstring& input_file,
  const streampos& offset)
{
  streampos tmp = 0;
  if (ad_comm::global_parfile)
  {
    tmp = ad_comm::global_parfile->tellg();
    delete ad_comm::global_parfile;
    ad_comm::global_parfile = NULL;
  }
  global_parfile = new cifstream(input_file);
  if (!(global_parfile && global_parfile->good()))
  {
    cerr << "Error trying to open parameter input file " <<  input_file << endl;

    delete global_parfile;
    global_parfile = NULL;
    ad_exit(1);
  }
  if (offset)
  {
    ad_comm::global_parfile->seekg(offset);
  }
  return tmp;
}
