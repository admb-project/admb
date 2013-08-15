/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <windows.h>
#include <windows.h>
#include <winnt.h>
#include <ddeml.h>

#include <math.h>
#include <stdlib.h>
#include <spcomm.h>
#include <fvar.hpp>
//#include <admoddde.h>
//#include <ddesp.h>


DWORD DDEspclient::idInst=0;
DWORD DDEspclient::sleeptime=0;
HCONV DDEspclient::cstatus=NULL;
UINT  DDEspclient::status=0;

void check_when_finished(void);
void open_the_file(ifstream*& pifs, const int& waitflag, const int& numwaits);
void open_the_file_when_finished(ifstream*& pifs, const int& waitflag, const int& numwaits);

# if defined(STUPID_DDL_FUNCTIONS)
HDDEDATA CALLBACK mycallback(       //DdeCallback(
         UINT  uType,   // transaction type
         UINT  uFmt,    // clipboard data format
	 HCONV  hconv,	// handle of the conversation
	 HSZ  hsz1,     // handle of a string
	 HSZ  hsz2,     // handle of a string
	 HDDEDATA  hdata,	// handle of a global memory object
	 DWORD  dwData1,	// transaction-specific data
	 DWORD  dwData2 	// transaction-specific data
);


DDEspclient::DDEspclient(DWORD _sleeptime)
{
  status=DdeInitialize(&idInst, mycallback,CBF_FAIL_EXECUTES |
    CBF_SKIP_ALLNOTIFICATIONS,0);
  HSZ  hszService=DdeCreateStringHandle(idInst,"SPLUS", CP_WINANSI);
  HSZ  hszTopic=DdeCreateStringHandle(idInst,"SCommand", CP_WINANSI);

  if (status !=DMLERR_NO_ERROR)
  {
    printInitializestatus(status);
    cstatus=NULL;
  }
  else
  {
    cstatus=DdeConnect(idInst,hszService,hszTopic, NULL);
  }
}


void SPsend(const double& x, const adstring& name)
{
  ofstream ofs("c:\\tmp.spl");

  adstring command = name + adstring(" <- scan(\"c:\\\\tmp.spl\")");

  ofs << x;
  ofs << endl;
  ofs.close();
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  check_when_finished();
}

void SPsend(const dvector& x, const adstring& name)
{
  ofstream ofs("c:\\tmp.spl");

  adstring command = name + adstring(" <- scan(\"c:\\\\tmp.spl\")");

  ofs << x;
  ofs << endl;
  ofs.close();
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  check_when_finished();
}

void SPsend(const named_dmatrix& _x)
{
  ADUNCONST(named_dmatrix,x)
  SPsend(x,adstring(x.label().mychar()));
}


void SPsend(const named_dvar_matrix& _x)
{
  ADUNCONST(named_dvar_matrix,x)
  SPsend(value(x),adstring(x.label().mychar()));
}

void SPsend(const named_dvariable& _x)
{
  ADUNCONST(named_dvariable,x)
  SPsend(value(x),adstring(x.label().mychar()));
}


void SPsend(const dmatrix& x, const adstring& name)
{
  int i1=x.rowmin();
  int ncol=x(i1).indexmax()-x(i1).indexmin()+1;
  ofstream ofs("c:\\tmp.spl");

  adstring command = name + adstring(" <- matrix(scan(\"c:\\\\tmp.spl\")"
   ",byrow=T,ncol=") + str(ncol) + adstring(")");

  ofs << x;
  ofs << endl;
  ofs.close();
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  check_when_finished();
}

void SPreceive(const dvector& _x, const adstring& name)
{
  ADUNCONST(dvector,x)

  //adstring command = name + adstring(" <- scan(\"c:\\\\tmp.spl\")");
  // tell splus to send the size of the vector
  adstring command = adstring(" write(length(") + name
    + adstring("),\"c:\\\\tmp.spl\")");
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(200);
  // now send the vector
  command = adstring(" write(") + name
    + adstring(",\"c:\\\\tmp.spl\",append=T)");
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(200);


  ifstream * pifs=NULL;
  int waitflag=0;
  int numwaits=0;
  do
  {
    open_the_file_when_finished(pifs,waitflag,numwaits);
  }
  while (waitflag && numwaits<5);

  if (pifs && !(!(*pifs)) )
  {
    int n;
    (*pifs) >> n;

    // check to see if this object is allocated;
    if (!x)
    {
      x.allocate(1,n);
      (*pifs) >> x;
    }
    else
    {
      if ( (x.indexmax()-x.indexmin()+1) != n)
      {
        cerr << "Error allocated dvector of the wrong size in"
           "SPreceive(const dvector& x, const adstring& name)";
      }
      else
      {
        (*pifs) >> x;
      }
    }
  }
  else
  {
    cerr << " couldn't read from splus temporary file" << endl;
  }
  // now delete the temporary file
  if (pifs)
  {
    delete pifs;
    pifs=NULL;
  }
  //DeleteFile("c:\\tmp.spl");
}

void SPreceive(const named_dvector& _x)
{
  ADUNCONST(named_dvector,x)
  SPreceive(x,adstring(x.label().mychar()));
}

void SPreceive(const named_dvar_vector& _x)
{
  ADUNCONST(named_dvar_vector,x)
  SPreceive(x,adstring(x.label().mychar()));
}

void SPreceive(const dvar_vector& _x,const adstring& name)
{
  ADUNCONST(dvar_vector,x)

  //adstring command = name + adstring(" <- scan(\"c:\\\\tmp.spl\")");
  // tell splus to send the size of the vector
  adstring command = adstring(" write(length(") + name
    + adstring("),\"c:\\\\tmp.spl\")");
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(200);
  // now send the vector
  command = adstring(" write(") + name
    + adstring(",\"c:\\\\tmp.spl\",append=T)");
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(200);


  ifstream * pifs=NULL;
  int waitflag=0;
  int numwaits=0;
  do
  {
    open_the_file_when_finished(pifs,waitflag,numwaits);
  }
  while (waitflag && numwaits<5);

  if (pifs && !(!(*pifs)) )
  {
    int n;
    (*pifs) >> n;

    // check to see if this object is allocated;
    if (!x)
    {
      x.allocate(1,n);
      (*pifs) >> x;
    }
    else
    {
      if ( (x.indexmax()-x.indexmin()+1) != n)
      {
        cerr << "Error allocated dvector of the wrong size in"
           "SPreceive(const dvector& x,const adstring& name)";
      }
      else
      {
        (*pifs) >> x;
      }
    }
  }
  else
  {
    cerr << " couldn't read from splus temporary file" << endl;
  }
  // now delete the temporary file
  if (pifs)
  {
    delete pifs;
    pifs=NULL;
  }
  //DeleteFile("c:\\tmp.spl");
}

void SPreceive(const dmatrix& _x, const adstring& name);
void SPreceive(const named_dmatrix& _x)
{
  ADUNCONST(named_dmatrix,x)
  SPreceive(x,adstring(x.label().mychar()));
}

void SPreceive(const dmatrix& _x, const adstring& name)
{
  ADUNCONST(dmatrix,x)

  // tell splus to send the number of rows in the matrix
  adstring command = adstring(" write(nrow(") + name
    + adstring("),\"c:\\\\tmp.spl\")");

  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(200);

  // tell splus to send the number of columns in the matrix
  command = adstring(" write(ncol(") + name
    + adstring("),\"c:\\\\tmp.spl\",append=T)");

  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(200);

  // now send the matrix
  command = adstring(" write(t(") + name
    + adstring("),\"c:\\\\tmp.spl\", append=T)");

  //command = adstring(" write(t(") + name
  //  + adstring("),\"c:\\\\tmp.spl\",ncol=ncol(") + name
  //  + adstring("),append=T)");
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(200);

  ifstream * pifs=NULL;
  int waitflag=0;
  int numwaits=0;
  do
  {
    open_the_file_when_finished(pifs,waitflag,numwaits);
  }
  while (waitflag && numwaits<5);

  if (pifs && !(!(*pifs)) )
  {
    int nrows;
    int ncols;
    (*pifs) >> nrows;
    (*pifs) >> ncols;

    // check to see if this object is allocated;
    if (!x)
    {
      x.allocate(1,nrows,1,ncols);
      if (!(*pifs))
      {
        cerr << "Error state before reading dmatrix from temporary file"
             << endl;
      }
      (*pifs) >> x;
    }
    else
    {
      int r1=x.rowmin();
      if ( ((x.rowmax()-x.rowmin()+1) != nrows) ||
         ( (x(r1).indexmax()-x(r1).indexmin()+1) != ncols) )
      {
        cerr << "Error --  allocated dimatrix is  the wrong size in"
           "SPreceive(const dvector& x, const adstring& name)";
      }
      else
      {
        (*pifs) >> x;
      }
    }
  }
  else
  {
    cerr << " couldn't read from splus temporary file" << endl;
  }
  // now delete the temporary file
  if (pifs)
  {
    delete pifs;
    pifs=NULL;
  }
  DeleteFile("c:\\tmp.spl");
}

void SPreceive(const dvar_matrix& x, const adstring& name);

void SPreceive(const named_dvar_matrix& _x)
{
  ADUNCONST(named_dvar_matrix,x)
  SPreceive(x,adstring(x.label().mychar()));
}

void SPreceive(const dvar_matrix& _x, const adstring& name)
{
  ADUNCONST(dvar_matrix,x)

  // tell splus to send the number of rows in the matrix
  adstring command = adstring(" write(nrow(") + name
    + adstring("),\"c:\\\\tmp.spl\")");

  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(200);

  // tell splus to send the number of columns in the matrix
  command = adstring(" write(ncol(") + name
    + adstring("),\"c:\\\\tmp.spl\",append=T)");

  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(200);

  // now send the matrix
  command = adstring(" write(t(") + name
    + adstring("),\"c:\\\\tmp.spl\", append=T)");

  //command = adstring(" write(t(") + name
  //  + adstring("),\"c:\\\\tmp.spl\",ncol=ncol(") + name
  //  + adstring("),append=T)");
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(200);

  ifstream * pifs=NULL;
  int waitflag=0;
  int numwaits=0;
  do
  {
    open_the_file_when_finished(pifs,waitflag,numwaits);
  }
  while (waitflag && numwaits<5);

  if (pifs && !(!(*pifs)) )
  {
    int nrows;
    int ncols;
    (*pifs) >> nrows;
    (*pifs) >> ncols;

    // check to see if this object is allocated;
    if (!x)
    {
      x.allocate(1,nrows,1,ncols);
      if (!(*pifs))
      {
        cerr << "Error state before reading dmatrix from temporary file"
             << endl;
      }
      (*pifs) >> x;
    }
    else
    {
      int r1=x.rowmin();
      if ( ((x.rowmax()-x.rowmin()+1) != nrows) ||
         ( (x(r1).indexmax()-x(r1).indexmin()+1) != ncols) )
      {
        cerr << "Error --  allocated dimatrix is  the wrong size in"
           "SPreceive(const dvector& x, const adstring& name)";
      }
      else
      {
        (*pifs) >> x;
      }
    }
  }
  else
  {
    cerr << " couldn't read from splus temporary file" << endl;
  }
  // now delete the temporary file
  if (pifs)
  {
    delete pifs;
    pifs=NULL;
  }
  DeleteFile("c:\\tmp.spl");
}

void SPreceive(const named_dvariable& _x)
{
  ADUNCONST(named_dvariable,x)
  SPreceive(value(x),adstring(x.label().mychar()));
}

void SPreceive(const data_number& _x)
{
  ADUNCONST(data_number,x)
  SPreceive(x.value(),adstring(x.label().mychar()));
}

void SPreceive(const dvariable& x, const adstring& name)
{
  SPreceive(value(x),name);
}

void SPreceive(const double& x, const adstring& name)
{

  //adstring command = name + adstring(" <- scan(\"c:\\\\tmp.spl\")");
  // tell splus to send the size of the vector
  adstring command = adstring(" write(") + name
    + adstring(",\"c:\\\\tmp.spl\")");

  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(500);
  // now send the vector
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(500);

  ifstream * pifs=NULL;
  int waitflag=0;
  int numwaits=0;
  do
  {
    open_the_file_when_finished(pifs,waitflag,numwaits);
  }
  while (waitflag && numwaits<5);

  if (pifs && !(!(*pifs)) )
  {
    (*pifs) >> (double&)x;
  }
  else
  {
    cerr << " couldn't read from splus temporary file" << endl;
  }
  // now delete the temporary file
  if (pifs)
  {
    delete pifs;
    pifs=NULL;
  }
  DeleteFile("c:\\tmp.spl");
}

void SPsend(const named_dvector& _x)
{
  ADUNCONST(named_dvector,x)
  SPsend(x,adstring(x.label().mychar()));
}

void SPsend(const named_dvar_vector& _x)
{
  ADUNCONST(named_dvar_vector,x)
   SPsend(value(x),adstring(x.label().mychar()));
}

void SPplot(const dvector& x, const adstring& name)
{

  ofstream ofs("c:\\tmp.spl");

  adstring command = name + adstring(" <- scan(\"c:\\\\tmp.spl\")");

  ofs << x;
  ofs << endl;
  ofs.close();
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(500);
  command = adstring("win3(\"spadcln\",multi=T,minimized=T)");
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(500);
  command = adstring("plot(") + name + adstring(")");
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  Sleep(500);
}

void SPplot(const named_dvector& _x)
{
  ADUNCONST(named_dvector,x)
  SPplot(x,adstring(x.label().mychar()));
}

void printInitializestatus(int status)
{
  char str1[]=" Error in DdeInitialize() error type is ";
  switch(status)
  {
  case DMLERR_NO_ERROR:
    cerr << " DdeInitialize() was successful" << endl;
    break;
  case DMLERR_DLL_USAGE:
    cerr << str1 << "DMLERR_DLL_USAGE" << endl;
    break;
  case DMLERR_INVALIDPARAMETER:
    cerr << str1 << "DMLERR_INVALIDPARAMETER" << endl;
    break;
  case DMLERR_SYS_ERROR:
    cerr << str1 << "DMLERR_SYS_ERROR"  << endl;
    break;
  default:
    cerr << str1 << "Error is unidentified" << endl;
    break;
  }
}

void SPexecute( LPBYTE  cbuff, // address of data to pass to server
  HCONV   cstatus  /* handle of conversation */ )
{

  DWORD  dwResult=0; // address of transaction result

  DdeClientTransaction(
	 cbuff,	// address of data to pass to server
	 strlen((const char *)cbuff)+1,	// length of data
	 cstatus,	// handle of conversation
	 NULL,	// handle of item name string
	 0,	// clipboard data format
	 XTYP_EXECUTE,	// transaction type
	 1000, //TIMEOUT_ASYNC,	// time-out duration
	 &dwResult 	// address of transaction result
	);
}


HDDEDATA CALLBACK mycallback(       //DdeCallback(
	 UINT  uType,	// transaction type
	 UINT  uFmt,	// clipboard data format
	 HCONV  hconv,	// handle of the conversation
	 HSZ  hsz1,	// handle of a string
	 HSZ  hsz2,	// handle of a string
	 HDDEDATA  hdata,	// handle of a global memory object
	 DWORD  dwData1,	// transaction-specific data
	 DWORD  dwData2 	// transaction-specific data
	)

{
  return (HDDEDATA) NULL;
}

#endif // # if defined(STUPID_DDL_FUNCTIONS)

void check_when_finished(void)
{
  // tell us when splus is finished writing the matrix
  DeleteFile("c:\\tmp1.spl");

  adstring command = adstring(" write(1,\"c:\\\\tmp1.spl\")");

  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  int nn=0;
  int numwaits=0;
  int waitflag=0;
  ifstream * pifs=NULL;
  do
  {
    pifs=new ifstream("c:\\tmp1.spl");
    if ((!pifs) || (!(*pifs)) )
    {
      //cout << "Error opening semaphore file ... will retry " << endl;
      waitflag=1;
      numwaits++;
      Sleep(500);
      if (pifs)
      {
        delete pifs;
        pifs=NULL;
      }
    }
    else
    {
      waitflag=0;
    }
  }
  while (waitflag==1);
  if (pifs)
  {
    delete pifs;
    pifs=NULL;
  }
  DeleteFile("c:\\tmp1.spl");
}

void open_the_file_when_finished(ifstream*& pifs, const int& _waitflag, const int& _numwaits)
{
  int& waitflag=(int&) _waitflag;
  int& numwaits=(int&) _numwaits;
  // tell us when splus is finished writing the matrix
  DeleteFile("c:\\tmp1.spl");
  adstring command = adstring(" write(1,\"c:\\\\tmp1.spl\")");
  SPexecute((unsigned char*)command,DDEspclient::get_cstatus());
  int nn=0;
  do
  {
    pifs=new ifstream("c:\\tmp1.spl");
    //(*pifs) >> nn;
    if ((!pifs) || (!(*pifs)) )
    {
      //cout << "Error opening semaphore file ... will retry " << endl;
      waitflag=1;
      numwaits++;
      Sleep(1000*numwaits);
      if (pifs)
      {
        delete pifs;
        pifs=NULL;
      }
    }
    else
    {
      waitflag=0;
    }
  }
  while (waitflag==1);
  if (pifs)
  {
    delete pifs;
    pifs=NULL;
  }
  DeleteFile("c:\\tmp1.spl");
  pifs=new ifstream("c:\\tmp.spl");
  if ((!pifs) || (!(*pifs)) )
  {
    cout << "Eror opening file ... will retry " << endl;
    waitflag=1;
    numwaits++;
    Sleep(500);
    if (pifs)
    {
      delete pifs;
      pifs=NULL;
    }
  }
  else
  {
    waitflag=0;
  }
}

void open_the_file(ifstream*& pifs, const int& _waitflag, const int& _numwaits)
{
  int& waitflag=(int&) _waitflag;
  int& numwaits=(int&) _numwaits;
  int nn=0;
  do
  {
    pifs=new ifstream("c:\\tmp1.spl");
    //(*pifs) >> nn;
    if ((!pifs) || (!(*pifs)) )
    {
      //cout << "Error opening semaphore file ... will retry " << endl;
      waitflag=1;
      numwaits++;
      Sleep(1000*numwaits);
      if (pifs)
      {
        delete pifs;
        pifs=NULL;
      }
    }
    else
    {
      waitflag=0;
    }
  }
  while (waitflag==1);
  if (pifs)
  {
    delete pifs;
    pifs=NULL;
  }
  DeleteFile("c:\\tmp1.spl");
  pifs=new ifstream("c:\\tmp.spl");
  if ((!pifs) || (!(*pifs)) )
  {
    cout << "Eror opening file ... will retry " << endl;
    waitflag=1;
    numwaits++;
    Sleep(500);
    if (pifs)
    {
      delete pifs;
      pifs=NULL;
    }
  }
  else
  {
    waitflag=0;
  }
}
