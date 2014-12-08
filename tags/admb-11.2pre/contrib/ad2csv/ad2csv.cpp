//==============================================================================
// Program: ad2csv
// Purpose: Convert ADMB binary file to comma separated values on stdout
// Notes:   Adapted from readbin.cpp in ADMB manual with minor changes:
//            (1) Converts file without user intervention
//            (2) CSV lines do not end with a comma
//          Binary files in ADMB include .cov, .hes, and .psv
//          To build the ad2csv executable: 'admb ad2csv.cpp main.cpp'
// History: 2012-03-16 arnima added build instructions
//          2012-03-13 arnima added -s and -t options
//          2011-11-03 arnima fixed stream construction bug affecting GCC
//          2003-08-30 arnima simplified UI and output
//          1993-01-01 davef created
//==============================================================================
#include "fvar.hpp"

void writeLine(dvector& line, adstring sep);

int ad2csv(int argc, char** argv)
{
  int i = 0;  // line in binary file
  int p = 0;  // number of parameters in binary file
  adstring filename;
  adstring sep;

  // 1  Parse args
  if(argc==1 || adstring(argv[1])=="-help" || adstring(argv[1])=="--help")
  {
    cout << "Usage: ad2csv [-s] [-t] file\n"
         << "Convert ADMB binary file to comma separated values\n\n"
         << "  -s  space separated\n"
         << "  -t  tab separated" << endl;
    return 0;
  }
  else if(argc==3 && adstring(argv[1])=="-s")
  {
    filename = argv[2];
    sep = " ";
  }
  else if(argc==3 && adstring(argv[1])=="-t")
  {
    filename = argv[2];
    sep = "\t";
  }
  else
  {
    filename = argv[1];
    sep = ",";
  }

  // 2  Check input file
  uistream mystream(filename);
  if(!mystream)
  {
    cerr << "Failed to open binary input file " << filename << endl;
    return 1;
  }
  mystream >> p;
  if(!mystream)
  {
    cerr << "Number of parameters not found at beginning of file "
         << filename << endl;
    return 1;
  }
  if(p <= 0)
  {
    cerr << "Invalid number of parameters (" << p
         << ") specified at beginning of file " << filename << endl;
    return 1;
  }

  // 3  Write to stdout
  dvector line(1, p);
  mystream >> line;
  while(!mystream.eof())
  {
    if(!mystream)
    {
      cerr << "Unable to read line " << i << " in file " << filename << endl;
      return 1;
    }
    writeLine(line, sep);
    mystream >> line;
    i++;
  }

  return 0;
}

void writeLine(dvector& line, adstring sep)
// Write comma-separated values to stdout
{
  int first = line.indexmin();
  int last  = line.indexmax();
  for(int j=first; j<=last-1; j++)
    cout << line(j) << sep;
  cout << line(last) << endl;  // no separator after last value
}
