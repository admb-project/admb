/**
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
#include <df1b2fun.h>
#ifdef DEBUG
  #include <cassert>
#endif

#ifdef _MSC_VER
  #ifdef _M_X64
  typedef __int64 ssize_t;
  #else
  typedef int ssize_t;
  #endif
#else
  #include <unistd.h>
#endif

/**
 * Description not yet available.
 * \param
 */
void fixed_smartlist::reset(void)
{
  end_saved=0;
  bptr=buffer;
  eof_flag=0;
  //off_t pos=lseek(fp,0L,SEEK_CUR);
  endof_file_ptr=lseek(fp,0L,SEEK_SET);
  written_flag=0;
}

/**
Default constructor
*/
fixed_smartlist::fixed_smartlist()
{
  nentries=0;
  bufsize=0;
  buffer=0;
  true_buffer=0;
  buffend=0;
  bptr=0;
  fp=-1;
}

/**
Constructor
*/
fixed_smartlist::fixed_smartlist(const size_t _bufsize,
  const adstring& _filename):
  endof_file_ptr(-1),
  recend(NULL),
  sbptr(NULL)
{
  allocate(_bufsize,_filename);
}
void fixed_smartlist::allocate(const size_t _bufsize,const adstring& _filename)
{
  nentries=_bufsize/sizeof(fixed_list_entry);
  end_saved=0;
  eof_flag=0;
  noreadflag=0;
  written_flag=0;
  direction=0;
  bufsize=_bufsize;
  filename=_filename;
  AD_ALLOCATE(true_buffer,fixed_list_entry,nentries+2,df1b2_gradlist)
  memset(true_buffer, 0, sizeof(fixed_list_entry) * (nentries + 2));
  doubleptr=(double*)true_buffer;
  true_buffend=true_buffer+nentries+1;
  buffer=true_buffer+1;
  buffend=true_buffend-2;
  bptr=buffer;
  true_buffer->numbytes=5678;
  //int(true_buffer->pf)=1234;
  true_buffend->numbytes=9999;
  //int(true_buffend->pf)=6666;
#ifdef _MSC_VER
  fp=open((char*)(filename), O_RDWR | O_CREAT | O_TRUNC |
                   O_BINARY, S_IREAD | S_IWRITE);
#else
  fp=open((char*)(filename), O_RDWR | O_CREAT | O_TRUNC |
                   O_BINARY, S_IRUSR | S_IWUSR);
#endif
  if (fp < 0)
  {
    cerr << "Error trying to open file " << filename
         << " in class fixed_smartlist " << endl;
    ad_exit(1);
  }
#ifdef DEBUG
  else
  {
    off_t pos=lseek(fp, 0L, SEEK_CUR);
  }
#endif
}

/**
\todo Need test case
*/
void fixed_smartlist::write(const size_t n)
{
#if defined(__MINGW64__) || (defined(_WIN64) && defined(_MSC_VER))
  #ifdef DEBUG
  assert(n <= UINT_MAX);
  #endif
  ssize_t nw = ::write(fp,buffer,static_cast<unsigned int>(n));
#else
  ssize_t nw = ::write(fp, buffer, n);
#endif
  if (nw <= -1 || (size_t)nw != n)
  {
    cerr << "Error writing to file " << filename << endl;
    ad_exit(1);
  }
}

/**
Rewind buffer
*/
void fixed_smartlist::rewind(void)
{
  bptr=buffer;
  eof_flag=0;
  if (written_flag)
  {
    lseek(fp,0L,SEEK_SET);
    // get the record size
    unsigned int nbytes=0;
    [[maybe_unused]] ssize_t ret = ::read(fp,&nbytes,sizeof(unsigned int));
#ifdef DEBUG
    assert(ret != -1);
#endif
    if (nbytes > bufsize)
    {
      cerr << "Error -- record size in file seems to be larger than"
       " the buffer it was created from " << endl
        << " buffer size is " << bufsize << " record size is supposedly "
        << nbytes << endl;
      ad_exit(1);
    }
    // now read the record into the buffer
    ret = ::read(fp,buffer,nbytes);
#ifdef DEBUG
    assert(ret != -1);
#endif

    // skip over file postion entry in file
    // so we are ready to read second record
    ret = lseek(fp, (off_t)sizeof(off_t), SEEK_CUR);
#ifdef DEBUG
    assert(ret >= 0);
#endif
  }
}

/**
 * Description not yet available.
 * \param
 */
void fixed_smartlist::initialize(void)
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
void fixed_smartlist::check_buffer_size(const size_t nsize)
{
  if ( bptr+nsize-1 > buffend)
  {
    if (df1b2variable::get_passnumber()==2 && !noreadflag )
    {
      read_buffer();
    }
    else
    {
      if (nsize>bufsize)
      {
         cout << "Need to increase buffsize in list" << endl;
         ad_exit(1);
      }
      write_buffer();
    }
  }
}
/**
Restore end
*/
void fixed_smartlist::restore_end(void)
{
  if (written_flag)
  {
    if (end_saved)
    {
      [[maybe_unused]] off_t ret = lseek(fp, 0L, SEEK_END);
#ifdef DEBUG
      assert(ret >= 0);
#endif
      ret = lseek(fp, endof_file_ptr, SEEK_SET);
#ifdef DEBUG
      assert(ret >= 0);
#endif
      read_buffer();
      set_recend();
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void fixed_smartlist::save_end(void)
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
void fixed_smartlist::write_buffer_one_less(void)
{
  int _nbytes=adptr_diff(bptr,buffer);
  if (_nbytes > 0)
  {
    const unsigned int nbytes = (unsigned int)_nbytes;

    written_flag=1;
    // get the current file position
    off_t pos=lseek(fp,0L,SEEK_CUR);

    // write the size of the next record into the file
    [[maybe_unused]] ssize_t ret = ::write(fp, &nbytes, sizeof(unsigned int));
#ifdef DEBUG
    assert(ret != -1);
#endif

    // write the record into the file
    [[maybe_unused]] ssize_t nw = ::write(fp,buffer,nbytes);
#ifdef DEBUG
    assert(nw != -1);
#endif
    if ((size_t)nw < nbytes)
    {
      cerr << "Error writing to file " << filename << endl;
      ad_exit(1);
    }
    // reset the pointer to the beginning of the buffer
    bptr=buffer;

    // now write the previous file position into the file so we can back up
    // when we want to.
    ret = ::write(fp,&pos,sizeof(off_t));
#ifdef DEBUG
    assert(ret != -1);
#endif

    endof_file_ptr=lseek(fp,0L,SEEK_CUR);
    //cout << lseek(fp,0L,SEEK_CUR) << endl;
  }
}

/**
 * Description not yet available.
 * \param
 */
void fixed_smartlist::write_buffer(void)
{
  int _nbytes=adptr_diff(bptr+1,buffer);
  if (_nbytes > 0)
  {
    unsigned int nbytes = (unsigned int)_nbytes;
    if (nbytes > bufsize)
    {
      cerr << "n bytes > bufsize in "
        "fixed_smartlist::write_buffer(void) this can't happen!" << endl;
    }
    written_flag=1;
    // get the current file position
    off_t pos=lseek(fp,0L,SEEK_CUR);

    // write the size of the next record into the file
    [[maybe_unused]] ssize_t ret = ::write(fp,&nbytes,sizeof(unsigned int));
#ifdef DEBUG
    assert(ret != -1);
#endif

    // write the record into the file
    [[maybe_unused]] ssize_t nw=::write(fp,buffer,nbytes);
#ifdef DEBUG
    assert(nw != -1);
#endif
    if ((size_t)nw < nbytes)
    {
      cerr << "Error writing to file " << filename << endl;
      ad_exit(1);
    }
    // reset the pointer to the beginning of the buffer
    bptr=buffer;

    // now write the previous file position into the file so we can back up
    // when we want to.
    ret = ::write(fp,&pos,sizeof(off_t));
#ifdef DEBUG
    assert(ret != -1);
#endif

    endof_file_ptr=lseek(fp,0L,SEEK_CUR);
    //cout << lseek(fp,0L,SEEK_CUR) << endl;
  }
}

/**
 * Description not yet available.
 * \param
 */
void fixed_smartlist::read_buffer(void)
{
  if (!written_flag)
  {
    if (direction ==-1)
      eof_flag=-1;
    else
      eof_flag=1;
  }
  else
  {
    off_t pos = 0;
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
      lseek(fp,-((off_t)sizeof(off_t)),SEEK_CUR);
      [[maybe_unused]] ssize_t ret = read(fp,&pos,sizeof(off_t));
#ifdef DEBUG
      assert(ret != -1);
#endif
      // back up to the beginning of the record (plus record size)
      lseek(fp,pos,SEEK_SET);
      //*(off_t*)(bptr)=lseek(fp,pos,SEEK_SET);
    }
    // get the record size
    unsigned int nbytes = 0;
    [[maybe_unused]] ssize_t result = ::read(fp,&nbytes,sizeof(unsigned int));
#ifdef DEBUG
    assert(result != -1);
#endif
    if (nbytes > bufsize)
    {
      cerr << "Error -- record size in file seems to be larger than"
       " the buffer it was created from " << endl
        << " buffer size is " << bufsize << " record size is supposedly "
        << nbytes << endl;
      ad_exit(1);
    }
    // now read the record into the buffer
    [[maybe_unused]] ssize_t nr = ::read(fp,buffer,nbytes);
#ifdef DEBUG
    assert(nr != -1);
#endif
    if ((size_t)nr != nbytes)
    {
      cerr << "Error reading -- should be " << nbytes << " got " << nr << endl;
      ad_exit(1);
    }

    // reset the pointer to the beginning of the buffer
    bptr=buffer;
    int ns=nbytes/(int)sizeof(fixed_list_entry);
    recend=bptr+ns-1;
    //cout << "Number of bytes read " << nr
     //    << "  recend value = " << recend << endl;
    if (direction ==-1) // we are going backwards
    {
      // backup the file pointer again
      [[maybe_unused]] off_t ret = lseek(fp, pos, SEEK_SET);
#ifdef DEBUG
      assert(ret >= 0);
#endif
      // *(off_t*)(bptr)=lseek(fp,pos,SEEK_SET);
    }
    else  // we are going forward
    {
      // skip over file postion entry in file
      [[maybe_unused]] off_t ret = lseek(fp, (off_t)sizeof(off_t), SEEK_CUR);
#ifdef DEBUG
      assert(ret >= 0);
#endif
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void memcpy(const fixed_smartlist& _list, void* p, const size_t nsize)
{
  ADUNCONST(fixed_smartlist,list)
  if (list.bptr+nsize-1 > list.buffend)
  {
    cerr << " Trying to write outside list buffer" << endl;
    ad_exit(1);
  }
  memcpy(list.bptr,p,nsize);
  list.bptr+=nsize;
}

/**
 * Description not yet available.
 * \param
 */
void memcpy(void* p, const fixed_smartlist& _list, const size_t nsize)
{
  ADUNCONST(fixed_smartlist,list)
  if (list.bptr+nsize-1 > list.buffend)
  {
    cerr << " Trying to write outside list buffer" << endl;
    ad_exit(1);
  }
  memcpy(p,list.bptr,nsize);
  list.bptr+=nsize;
}

void fixed_smartlist::operator -= (int n)
{
  if (bptr-n<buffer)
  {
    if (bptr != buffer)
    {
      cerr << " Sanity error in fixed_smartlist::operator -= (int)" << endl;
      ad_exit(1);
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
void fixed_smartlist::operator -- (void)
{
  if (bptr-1<buffer)
  {
    if (bptr != buffer)
    {
      cerr << " Sanity error in fixed_smartlist::operator -= (int)" << endl;
      ad_exit(1);
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

void fixed_smartlist::operator += (int nsize)
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
        ad_exit(1);
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
void fixed_smartlist::operator ++ (void)
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
\todo Need test case
*/
void fixed_smartlist::read_file(void)
{
  //rewind the file
  off_t pos=lseek(fp,0L,SEEK_SET);
  char local_buffer[50000];
  int offset=0;
  fixed_list_entry * b= (fixed_list_entry*) &(local_buffer[0]);
  cout << b << endl;
  ssize_t nw = 0;
  do
  {
    unsigned int nbytes=0;
    nw = ::read(fp,&nbytes,sizeof(unsigned int));
    if (nw != -1)
    {
      nw = ::read(fp, local_buffer + offset, (size_t)nbytes);
      if (nw != -1)
      {
        offset+=nbytes;
        nw = ::read(fp, &pos, sizeof(off_t));
      }
    }
  }
  while(nw);
}
