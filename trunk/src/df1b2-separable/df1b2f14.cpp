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
#include <cassert>

#ifdef _MSC_VER
typedef int ssize_t;
#endif

/**
 * Description not yet available.
 * \param
 */
fixed_smartlist2::fixed_smartlist2(void)
{
  nentries=0;
  end_saved=0;
  eof_flag=0;
  noreadflag=0;
  written_flag=0;
  direction=0;
  bufsize=0;
  true_buffer=0;
  true_buffend=0;
  buffer=0;
  buffend=0;
  bptr=buffer;
}

/**
 * Description not yet available.
 * \param
 */
fixed_smartlist2::fixed_smartlist2(unsigned int _bufsize,
  const adstring& _filename)
{
  allocate(_bufsize,_filename);
}

/**
 * Description not yet available.
 * \param
 */
void fixed_smartlist2::allocate(unsigned int _bufsize,
  const adstring& _filename)
{
  nentries=_bufsize/sizeof(int);
  end_saved=0;
  eof_flag=0;
  noreadflag=0;
  written_flag=0;
  direction=0;
  bufsize=_bufsize;
  filename=_filename;
  AD_ALLOCATE(true_buffer,int,nentries+2,df1b2_gradlist)
  doubleptr=(double*)true_buffer;
  true_buffend=true_buffer+nentries+1;
  buffer=true_buffer+1;
  buffend=true_buffend-1;
  bptr=buffer;
  *true_buffer=5678;
  *true_buffend=9999;
  fp=open((char*)(filename), O_RDWR | O_CREAT | O_TRUNC |
                   O_BINARY, S_IREAD | S_IWRITE);
  if (fp == -1)
  {
    cerr << "Error trying to open file " << filename
         << " in class fixed_smartlist2 " << endl;
    ad_exit(1);
  }

  /*off_t pos=*/lseek(fp,0L,SEEK_CUR);
}

/**
 * Description not yet available.
 * \param
 */
void fixed_smartlist2::write(int n)
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
void fixed_smartlist2::rewind(void)
{
  bptr=buffer;
  unsigned int nbytes=0;
  eof_flag=0;
  if (written_flag)
  {
    lseek(fp,0L,SEEK_SET);
    // get the record size
    ssize_t ret = ::read(fp,&nbytes,sizeof(int));
    //assert(ret == -1);
    if (nbytes>bufsize)
    {
      cerr << "Error -- record size in file seems to be larger than"
       " the buffer it was created from " << endl
        << " buffer size is " << bufsize << " record size is supposedly "
        << nbytes << endl;
      ad_exit(1);
    }
    // now read the record into the buffer
    ret = ::read(fp,buffer,nbytes);
    //assert(ret == -1);
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
void fixed_smartlist2::initialize(void)
{
  end_saved=0;
  eof_flag=0;
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
void fixed_smartlist2::check_buffer_size(int nsize)
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
void fixed_smartlist2::restore_end(void)
{
  if (written_flag)
  {
    if (end_saved)
    {
      /*off_t ipos=*/lseek(fp,endof_file_ptr,SEEK_SET);
      read_buffer();
      set_recend();
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void fixed_smartlist2::save_end(void)
{
  if (written_flag)
  {
    if (!end_saved)
    {
      write_buffer_one_less();
      end_saved=1;
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void fixed_smartlist2::write_buffer_one_less(void)
{
  int nbytes=adptr_diff(bptr,buffer);
  if (nbytes)
  {
    written_flag=1;
    // get the current file position
    off_t pos=lseek(fp,0L,SEEK_CUR);

    // write the size of the next record into the file
    ssize_t ret = ::write(fp,&nbytes,sizeof(int));
    assert(ret != -1);

    // write the record into the file
    int nw=::write(fp,buffer,nbytes);
    //cout << "Number of bytes written " << nw
     //    << " bptr value =  " << bptr << endl;
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
    ret = ::write(fp,&pos,sizeof(off_t));
    assert(ret != -1);

    endof_file_ptr=lseek(fp,0L,SEEK_CUR);

    //cout << lseek(fp,0L,SEEK_CUR) << endl;
  }
}

/**
 * Description not yet available.
 * \param
 */
void fixed_smartlist2::write_buffer(void)
{
  int nbytes=adptr_diff(bptr+1,buffer);
  if (nbytes)
  {
    written_flag=1;
    // get the current file position
    off_t pos=lseek(fp,0L,SEEK_CUR);

    // write the size of the next record into the file
    ssize_t ret = ::write(fp,&nbytes,sizeof(int));
    assert(ret != -1);

    // write the record into the file
    ret = ::write(fp,buffer,nbytes);
    assert(ret != -1);
    //cout << "Number of bytes written " << ret 
     //    << " bptr value =  " << bptr << endl;
    //for (int ii=0;ii<=25;ii++)
    //  cout << int (*(buffer+ii)) << " ";
    //cout << endl;
    if (ret < nbytes)
    {
      cerr << "Error writing to file " << filename << endl;
      ad_exit(1);
    }
    // reset the pointer to the beginning of the buffer
    bptr=buffer;

    // now write the previous file position into the file so we can back up
    // when we want to.
    ret = ::write(fp,&pos,sizeof(off_t));
    assert(ret != -1);

    endof_file_ptr=lseek(fp,0L,SEEK_CUR);

    //cout << lseek(fp,0L,SEEK_CUR) << endl;
  }
}

/**
 * Description not yet available.
 * \param
 */
void fixed_smartlist2::read_buffer(void)
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
      off_t ipos=lseek(fp,0L,SEEK_CUR);
      if (ipos ==0)
      {
        eof_flag=-1;
        return;
      }
      // offset of the begining of the record is at the end
      // of the record
      lseek(fp,long(-sizeof(off_t)),SEEK_CUR);
      ssize_t ret = read(fp,&pos,sizeof(off_t));
      assert(ret != -1);
      // back up to the beginning of the record (plus record size)
      lseek(fp,pos,SEEK_SET);
      //*(off_t*)(bptr)=lseek(fp,pos,SEEK_SET);
    }
    // get the record size
    ssize_t ret = ::read(fp,&nbytes,sizeof(int));
    assert(ret != -1);
    if (nbytes>bufsize)
    {
      cerr << "Error -- record size in file seems to be larger than"
       " the buffer it was created from " << endl
        << " buffer size is " << bufsize << " record size is supposedly "
        << nbytes << endl;
      ad_exit(1);
    }
    // now read the record into the buffer
    ssize_t nr=::read(fp,buffer,nbytes);
    assert(nr != -1);
    if ((unsigned int)nr != nbytes)
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
    int ns=nbytes/sizeof(int);
    recend=bptr+ns-1;
    //cout << "Number of bytes read " << nr
     //    << "  recend value = " << recend << endl;
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
void memcpy(const fixed_smartlist2 & _list,void * p,int nsize)
{
  ADUNCONST(fixed_smartlist2,list)
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
void memcpy(void * p,const fixed_smartlist2 & _list,int nsize)
{
  ADUNCONST(fixed_smartlist2,list)
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
void fixed_smartlist2::operator -= (int n)
{
  if (bptr-n<buffer)
  {
    if (bptr != buffer)
    {
      cerr << " Sanity error in fixed_smartlist2::operator -= (int)" << endl;
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
void fixed_smartlist2::operator -- (void)
{
  if (bptr-1<buffer)
  {
    if (bptr != buffer)
    {
      cerr << " Sanity error in fixed_smartlist2::operator -= (int)" << endl;
      exit(1);
    }
    else
    {
      // get previous record from the file
      read_buffer();
      //bptr=recend+1;
      bptr=recend;
    }
  }
  else
  {
    bptr--;
  }
}

/**
 * Description not yet available.
 * \param
 */
void fixed_smartlist2::operator += (int nsize)
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
void fixed_smartlist2::operator ++ (void)
{
  if ( bptr==buffend)
  {
    if (df1b2variable::get_passnumber()==2 && !noreadflag )
    {
      read_buffer();
    }
    else
    {
      write_buffer();
    }
  }
  else
  {
    bptr++;
  }
}

/**
 * Description not yet available.
 * \param
 */
void fixed_smartlist2::read_file(void)
{
  //rewind the file
  off_t pos=lseek(fp,0L,SEEK_SET);
  int nbytes=0;
  char buffer[50000];
  int offset=0;
  fixed_list_entry * b= (fixed_list_entry*) &(buffer[0]);
  cout << b << endl;
  int nw=0;
  do
  {
    nw=::read(fp,&nbytes,sizeof(int));
    nw=::read(fp,buffer+offset,nbytes);
    offset+=nbytes;
    ::read(fp,&pos,sizeof(off_t));
  }
  while(nw);
}
