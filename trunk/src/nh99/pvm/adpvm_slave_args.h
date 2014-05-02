
/**
 * Description not yet available.
 * \param
 */
class adpvm_slave_args
{
  char ** argv;
  int num_args;
  ivector length_args;
public:
  int counter;
  char * operator () (int);
  operator char ** ();
  void operator -- (void);
  adpvm_slave_args(int num_args,int len_args);
  adpvm_slave_args(int num_args,const ivector& len_args);
  ~adpvm_slave_args();
  int get_num_args(void);
};

void strcpy(const adpvm_slave_args& a,const char * s);

