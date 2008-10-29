
class ad_sbuffer 
{
public:
  adstring file_name;
  char *        buff;
  unsigned int  buff_end;
  unsigned int  buff_size;
  union {
     unsigned int  offset;
     char fourb[sizeof(unsigned int)];
  };
  unsigned int  toffset;
  char          cmpdif_file_name[81];
  int           file_ptr;
  ad_sbuffer(unsigned long int,const char * filename);
  ~ad_sbuffer();
  void write_cmpdif_stack_buffer(void);
  void read_cmpdif_stack_buffer(long int& lpos);
  void fwrite(void* s,const size_t num_bytes);
  void fread(void* s,const size_t num_bytes);
  void fwrite( double);
  void fwrite(const int&);
  void fread(const int&);
  void fread(const double&);
};

