/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California 
 */
#include <fvar.hpp>

#ifdef __TURBOC__
  #pragma hdrstop
  #include <iostream.h>
#endif

#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#include <string.h>
extern ofstream clogf;


void report_gradstack_flag(void)
{
  verify_identifier_string("stack");
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  int num_bytes;
  gradient_structure::get_fp()->fread(&num_bytes,sizeof(int));
  char str1[100];
  str1[0]='\0';
  gradient_structure::get_fp()->fread(str1,num_bytes);
  cout << "in report_gradstack_flag  " << str1 << endl;
}

static void report_gradstack_flag2(void)
{
  verify_identifier_string("stack");
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  int num_bytes;
  gradient_structure::get_fp()->fread(&num_bytes,sizeof(int));
  char str1[100];
  str1[0]='\0';
  gradient_structure::get_fp()->fread(str1,num_bytes);
  int i,j;
  gradient_structure::get_fp()->fread(&j,sizeof(int));
  gradient_structure::get_fp()->fread(&i,sizeof(int));
  cout << "in report_gradstack_flag  " << str1 << endl;
  if (i==3 && j==91)
    cout << "HERE" << endl;
}


void set_gradstack_flag(char* str)
{
#if defined(CHK_ID_STRING)
  int wsize=sizeof(char);
  int length=strlen(str);
  gradient_structure::get_fp()->fwrite(str,length);
  gradient_structure::get_fp()->fwrite(&length,sizeof(int));
  gradient_structure::GRAD_STACK1-> 
    set_gradient_stack(report_gradstack_flag);
  save_identifier_string("stack");
#endif
}
void set_gradstack_flag(char* _str,int i,int j)
{
#if defined(CHK_ID_STRING)
  adstring ads=_str;
  ads+=" ";
  ads+=str(i);
  ads+=" ";
  ads+=str(j);
  int wsize=sizeof(char);
  char * str=(char*)(ads);
  int length=strlen(str);
  gradient_structure::get_fp()->fwrite(&i,sizeof(int));
  gradient_structure::get_fp()->fwrite(&j,sizeof(int));
  gradient_structure::get_fp()->fwrite(str,length);
  gradient_structure::get_fp()->fwrite(&length,sizeof(int));
  gradient_structure::GRAD_STACK1-> 
    set_gradient_stack(report_gradstack_flag2);
  save_identifier_string("stack");
#endif
}
void verify_identifier_string(char* str1)
{
#if defined(CHK_ID_STRING)
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  long int num_bytes=strlen(str1);
  char str[10];
  str[num_bytes]='\0';
  gradient_structure::get_fp()->fread(str,num_bytes);
  //clogf << "in verify_id_string " << str1 << endl;
  if(strcmp(str1,str))
  {
    cerr << "Error reading stack identifer for " << str1 << endl;
    ad_exit(1);
  }
#endif
}

adstring get_string_marker(void)
{
  adstring str1;
#if defined(CHK_ID_STRING)
  // Back up the stream and read the number of bytes written in the
  // ``write function'' corresponding to this ``read function''
  long int num_bytes=5;
  char str[10];
  str[num_bytes]='\0';
  gradient_structure::get_fp()->fread(str,num_bytes);
  //clogf << "in verify_id_string " << str1 << endl;
  str1=str;
#endif
 return str1;
}

void ivector::save_ivector_position(void) _CONST
{
  // saves the size and address information for a ivector
  unsigned wsize=sizeof(ivector_position);
  ivector_position tmp(*this);
  gradient_structure::get_fp()->fwrite(&tmp,wsize);
}

void dvar_vector::save_dvar_vector_position(void) _CONST
{
  // saves the size and address information for a dvar_vector
  unsigned wsize=sizeof(dvar_vector_position);
  dvar_vector_position tmp(*this);
  gradient_structure::get_fp()->fwrite(&tmp,size_t(wsize));
}

void save_ad_pointer(void * p) 
{
  // saves the size and address information for a dvar_vector
  unsigned wsize=sizeof(void *);
  gradient_structure::get_fp()->fwrite(&p,size_t(wsize));
}

void * restore_ad_pointer(void)
{
  void * p=0;
  // saves the size and address information for a dvar_vector
  unsigned wsize=sizeof(void *);
  gradient_structure::get_fp()->fread(&p,size_t(wsize));
  return p;
}

