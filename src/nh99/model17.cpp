/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <admodel.h>

/**
Change the global_datafile stream using file input_file.
Returns the current streampos of existing open file,
else returns 0.

\param input_file new input data file.
\param off change to this offset if file exists.
*/
streampos ad_comm::change_datafile_name(
  const adstring& input_file,
  const streampos& offset)
{
  streampos tmp = 0;
  if(ad_comm::global_datafile)
  {
    tmp = ad_comm::global_datafile->tellg();
    delete ad_comm::global_datafile;
    ad_comm::global_datafile = NULL;
  }
  adstring tmpstring;
  if (ad_comm::wd_flag)
    tmpstring += ad_comm::working_directory_path + input_file;
  else
    tmpstring = input_file;
  global_datafile = new cifstream(tmpstring);
  if (!(global_datafile && global_datafile->good()))
  {
    cerr << "Error trying to open data input file " <<  input_file  << endl;
    delete global_datafile;
    global_datafile = NULL;
    ad_exit(1);
  }
  if (offset)
  {
    ad_comm::global_datafile->seekg(offset);
  }
  return tmp;
}
/**
Change the global_parfile stream using input_file.
Returns the current streampos of existing open file,
else returns 0.

\param input_file new input par file.
\param offset change to this offset if file exists.
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
