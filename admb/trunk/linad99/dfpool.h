
#if !defined(__DF_POOL__)
#define  __DF_POOL__ 
#include <fvar.hpp>
extern void * pchecker;
//#define __CHECK_MEMORY__
class link;

class dfpool
{
  int dfpool_vector_flag;
public:
  int nvar;
  int& on_dfpool_vector(void) {return dfpool_vector_flag;}
  char * last_chunk;
  struct link { link * next; };
  int num_allocated;
  int num_chunks;
  int nelem;
  unsigned size;
  link * head;
  double * first;
  dfpool(dfpool&);  // copy protection
  void operator = (dfpool&); // copy protection
  void grow(void);
#if defined(__CHECK_MEMORY__)
  int maxchunks;
  char * minaddress[100];
  char * maxaddress[100];
  int * pvalues;
  int nalloc;
#endif
public:
  void clean(void);
  dfpool(unsigned);
  void set_size(unsigned);
  dfpool(void);
 ~dfpool();
  void * alloc(void);
  void free(void * b);
  void deallocate(void);
#if defined(__CHECK_MEMORY__)
  int bad(link * p);
  int badaddress(link * p);
  void sanity_check(void);
  void sanity_check(void *);
  void sanity_check2(void);
  void write_pointers(int m,int max);
#endif
};

class tsdfpool : public dfpool
{
public:
  tsdfpool(int n);
  void * alloc(void);
  void free(void * b);
};

#endif //defined(__DF_POOL__)
