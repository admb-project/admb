/*
 * $Id: df1b2f10.cpp 944 2011-01-12 22:48:46Z johnoel $
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <df1b2fun.h>

/**
 * Description not yet available.
 * \param
 */
void test_smartlist::reset(void)
{
  bptr=buffer; 
  eof_flag=0;
  /*off_t pos=*/lseek(fp,0L,SEEK_CUR);
  written_flag=0;
  end_saved=0;
}

void xxx_yyy(df1b2variable * tmp){;}

/**
 * Description not yet available.
 * \param
 */
test_smartlist::test_smartlist(void) 
{
  bufsize=0;
  buffer=0;
  true_buffer=0;
  buffend=0; 
  bptr=0;
  fp=-1;
}

/**
 * Description not yet available.
 * \param
 */
test_smartlist::test_smartlist(unsigned int _bufsize,const adstring& _filename) 
{
  allocate(_bufsize,_filename);
}

/**
 * Description not yet available.
 * \param
 */
void test_smartlist::allocate(unsigned int _bufsize,const adstring& _filename) 
{
  if (sizeof(char)>1)
  {
    cerr << "need to modify test_smartlist class for multibyte char" << endl;
    exit(1);
  }
  end_saved=0;
  eof_flag=0;
  noreadflag=0;
  written_flag=0;
  direction=0;
  bufsize=_bufsize;
  filename=_filename;
  //AD_ALLOCATE(true_buffer,char,bufsize+2*sizeof(double),df1b2_gradlist) 
  if ((true_buffer=new char[(bufsize+2)*sizeof(double) ])==0)
  {
    cerr << "Allocation error in df1b2_gradlist" << endl;
    ad_exit(1);
  }
  doubleptr=(double*)true_buffer;
  true_buffend=true_buffer+bufsize+2*sizeof(double)-1;
  buffer=true_buffer+sizeof(double);
  *(double*)(true_buffer)=5678.9;
  *(double*)(true_buffer+bufsize+sizeof(double))=9876.5;
  //buffend=true_buffer+bufsize-1+sizeof(double);
  buffend=true_buffer+bufsize-1;
  bptr=buffer;
  fp=open((char*)(filename), O_RDWR | O_CREAT | O_TRUNC |
                   O_BINARY, S_IREAD | S_IWRITE);
  if (fp == -1)
  {
    cerr << "Error trying to open file " << filename 
         << " in class test_smartlist " << endl;
    exit(1);
  }

  /*off_t pos=*/lseek(fp,0L,SEEK_CUR);
}

/**
 * Description not yet available.
 * \param
 */
void test_smartlist::write(int n)
{
  int nw=::write(fp,buffer,n);
  if (nw<n)
  {
    cerr << "Error writing to file " << filename << endl;
    ad_exit(1);
  }
}

/**
 * Description not yet available.
 * \param
 */
void test_smartlist::rewind(void)
{
  bptr=buffer;
  unsigned int nbytes=0;
  if (written_flag)
  {
    lseek(fp,0L,SEEK_SET);
    // get the record size
    ::read(fp,&nbytes,sizeof(int));
    if (nbytes>bufsize)
    {
      cerr << "Error -- record size in file seems to be larger than"
       " the buffer it was created from " << endl 
        << " buffer size is " << bufsize << " record size is supposedly "
        << nbytes << endl;
    }
    // now read the record into the buffer
    /*int nr=*/::read(fp,buffer,nbytes);
    //cout << "Number of bytes read " << nr << endl;
    // skip over file postion entry in file
    // so we are ready to read second record
    lseek(fp,long(sizeof(off_t)),SEEK_CUR);
  }
}

/**
 * Description not yet available.
 * \param
 */
void test_smartlist::initialize(void)
{
  end_saved=0;
  bptr=buffer;
  //int nbytes=0;
  written_flag=0;
  lseek(fp,0L,SEEK_SET);
  set_forward();
}

/**
 * Description not yet available.
 * \param
 */
void test_smartlist::check_buffer_size(int nsize)
{
  if ( bptr+nsize-1 > buffend)
  {
    if (df1b2variable::get_passnumber()==2 && !noreadflag )
    {
      read_buffer();
    }
    else
    {
      if ((unsigned int)nsize>bufsize)
      {
         cout << "Need to increase buffsize in list" << endl;
         exit(1);
      }
      write_buffer();
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void test_smartlist::restore_end(void)
{
  if (written_flag)
  {
    if (end_saved)
    {
      read_buffer();
      set_recend();
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void test_smartlist::save_end(void)
{
  if (written_flag)
  {
    if (!end_saved)
    {
      write_buffer();
      end_saved=1;
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void test_smartlist::write_buffer(void)
{
  int nbytes=adptr_diff(bptr,buffer);
  if (nbytes)
  {
    written_flag=1;
    // get the current file position
    off_t pos=lseek(fp,0L,SEEK_CUR);
  
    // write the size of the next record into the file
    ::write(fp,&nbytes,sizeof(int));
  
    // write the record into the file
    int nw=::write(fp,buffer,nbytes);
    //cout << "Number of bytes written " << nw << endl;
    //cout << "buffer value = "; 
    //for (int ii=0;ii<=25;ii++)
    //  cout << int (*(buffer+ii)) << " ";
    //cout << endl;
    if (nw<nbytes)
    {
      cerr << "Error writing to file " << filename << endl;
      ad_exit(1);
    }
    // reset the pointer to the beginning of the buffer
    bptr=buffer;
  
    // now write the previous file position into the file so we can back up
    // when we want to.
    ::write(fp,&pos,sizeof(off_t));
  
    //cout << lseek(fp,0L,SEEK_CUR) << endl;
  }
}

/**
 * Description not yet available.
 * \param
 */
void test_smartlist::read_buffer(void)
{
  off_t pos;
  unsigned int nbytes;
  if (!written_flag)
  {
    if (direction ==-1) 
      eof_flag=-1;
    else
      eof_flag=1;
  }
  else
  {
    if (direction ==-1) // we are going backwards
    {
      // offset of the begining of the record is at the end
      // of the record
      lseek(fp,long(-sizeof(off_t)),SEEK_CUR);
      read(fp,&pos,sizeof(off_t));
      // back up to the beginning of the record (plus record size) 
      lseek(fp,pos,SEEK_SET);
      //*(off_t*)(bptr)=lseek(fp,pos,SEEK_SET);
    }
    // get the record size
    ::read(fp,&nbytes,sizeof(int));
    if (nbytes>bufsize)
    {
      cerr << "Error -- record size in file seems to be larger than"
       " the buffer it was created from " << endl 
        << " buffer size is " << bufsize << " record size is supposedly "
        << nbytes << endl;
    }
    // now read the record into the buffer
    unsigned int nr=::read(fp,buffer,nbytes);
    if (nr != nbytes)
    {
      cerr << "Error reading -- should be " << nbytes << " got " << nr << endl;
      exit(1);
    }
   /*
    cout << "Number of bytes read " << nr << endl;
    cout << "buffer value = ";
    for (int ii=0;ii<=25;ii++)
      cout << int (*(buffer+ii)) << " ";
    cout << endl;
    */
    // reset the pointer to the beginning of the buffer
    bptr=buffer;
    recend=bptr+nbytes-1;
    if (direction ==-1) // we are going backwards
    {
      // backup the file pointer again
      lseek(fp,pos,SEEK_SET);
      // *(off_t*)(bptr)=lseek(fp,pos,SEEK_SET);
    }
    else  // we are going forward  
    {
      // skip over file postion entry in file
      lseek(fp,long(sizeof(off_t)),SEEK_CUR);
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void memcpy(const test_smartlist & _list,void * p,int nsize)
{
  ADUNCONST(test_smartlist,list)
  if ( list.bptr+nsize-1 > list.buffend)
  {
    cerr << " Trying to write outside list buffer" << endl;
    exit(1);
  }
  memcpy(list.bptr,p,nsize);
  list.bptr+=nsize;
}

/**
 * Description not yet available.
 * \param
 */
void memcpy(void * p,const test_smartlist & _list,int nsize)
{
  ADUNCONST(test_smartlist,list)
  if ( list.bptr+nsize-1 > list.buffend)
  {
    cerr << " Trying to write outside list buffer" << endl;
    exit(1);
  }
  memcpy(p,list.bptr,nsize);
  list.bptr+=nsize;
}

/**
 * Description not yet available.
 * \param
 */
void test_smartlist::operator -= (int n) 
{
  if (bptr-n<buffer)
  {
    if (bptr != buffer)
    {
      cerr << " Sanity error in test_smartlist::operator -= (int)" << endl;
      exit(1);
    }
    else
    {
      // get previous record from the file
      read_buffer();
      bptr=recend-n+1;
    }
  }
  else
  {
    bptr-=n;
  }
}

/**
 * Description not yet available.
 * \param
 */
void test_smartlist::operator += (int nsize) 
{
  if ( bptr+nsize-1 > buffend)
  {
    if (df1b2variable::get_passnumber()==2 && !noreadflag )
    {
      read_buffer();
    }
    else
    {
      if ((unsigned int)nsize>bufsize)
      {
         cout << "Need to increase buffsize in list" << endl;
         exit(1);
      }
      write_buffer();
    }
  }
  else
  {
    bptr+=nsize;
  }
}

/**
 * Description not yet available.
 * \param
 */
test_smartlist::~test_smartlist() 
{
  end_saved=0;
  eof_flag=0;
  noreadflag=0;
  written_flag=0;
  direction=0;
  bufsize=0;

  //delete true_buffer;
  delete [] true_buffer;
  true_buffer=0;
  true_buffend=0;
  buffer=0;
  buffend=0;
  bptr=0;
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
  fp=0;
  #if defined ( __SUN__) ||  defined ( __GNU__)
   unlink(filename);
  #else
   remove(filename);
  #endif
}

