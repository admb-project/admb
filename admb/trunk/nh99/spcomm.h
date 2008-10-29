
#ifndef __SPCOMM__
#define __SPCOMM__
#include <windows.h>
#include <windows.h>
#if defined (__BORLANDC__)
#  include <winnt.h>
#endif
#include <ddeml.h>
#include <admodel.h>

void printconnectstatus(int status);
void printInitializestatus(int status);



class DDEspclient
{
  static DWORD idInst;
  static DWORD sleeptime; 
  static HCONV cstatus;
  static UINT status;
public:
  DDEspclient(DWORD sleeptime=1000); 
  static HCONV get_cstatus(void){return cstatus;}
  static DWORD get_idInst(void){return idInst;}
  static DWORD get_sleeptime(void){return sleeptime;}

};

void SPreceive(BOR_CONST data_number& x,BOR_CONST adstring& name);

void SPreceive(BOR_CONST data_number& x);

void SPreceive(BOR_CONST dvariable& x,BOR_CONST adstring& name);

void SPreceive(BOR_CONST double& x,BOR_CONST adstring& name);

void SPreceive(BOR_CONST named_dvariable& x);

void SPreceive(BOR_CONST dvector& x,BOR_CONST adstring& name);

void SPreceive(BOR_CONST named_dvector& x);

void SPreceive(BOR_CONST named_dvar_matrix& x);

void SPreceive(BOR_CONST dvar_vector& x,BOR_CONST adstring& name);

void SPreceive(BOR_CONST named_dvar_vector& x);

void SPreceive(BOR_CONST named_dmatrix& x);

void SPreceive_double(BOR_CONST double& x,BOR_CONST adstring& name);

void SPreceive_double(BOR_CONST dmatrix& x,BOR_CONST adstring& name);

void SPsend(BOR_CONST dmatrix& x,BOR_CONST adstring& name);

void SPsend(BOR_CONST double& x,BOR_CONST adstring& name);

void SPsend(BOR_CONST dvector& x,BOR_CONST adstring& name);

void SPsend(BOR_CONST named_dvector& x);

void SPsend(BOR_CONST named_dvariable& x);

void SPsend(BOR_CONST named_dvar_vector& x);

void SPsend(BOR_CONST named_dvar_matrix& x);

void SPsend(BOR_CONST named_dmatrix& x);

void SPexecute( LPBYTE  cbuff,HCONV cstatus);


void SPsend_char(char * pch,HCONV cstatus);



/*
class DDEspclient
{
  static DWORD idInst;
  static DWORD sleeptime; 
  static HCONV cstatus;
  static UINT status;
public:
  DDEspclient(DWORD sleeptime=1000); 
  static HCONV get_cstatus(void){return cstatus;}
  static DWORD get_idInst(void){return idInst;}
  static DWORD get_sleeptime(void){return sleeptime;}

};

HDDEDATA SPreceive(BOR_CONST dvector& x,BOR_CONST adstring& name);

HDDEDATA SPreceive(BOR_CONST named_dvector& x);

HDDEDATA SPreceive(BOR_CONST named_dvar_matrix& x);

HDDEDATA SPreceive(BOR_CONST named_dmatrix& x);

HDDEDATA SPreceive_double(BOR_CONST double& x,BOR_CONST adstring& name);


HDDEDATA SPsend(BOR_CONST dvector& x,BOR_CONST adstring& name);

HDDEDATA SPsend(BOR_CONST named_dvector& x);

HDDEDATA SPsend(BOR_CONST named_dvar_matrix& x);

HDDEDATA SPsend(BOR_CONST named_dmatrix& x);

HDDEDATA SPexecute( LPBYTE  cbuff,HCONV cstatus);


HDDEDATA SPsend_char(char * pch,HCONV cstatus);
*/

#endif
