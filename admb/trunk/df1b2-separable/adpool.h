#if !defined(__AD_POOL__)
#define  __AD_POOL__ 
#include <fvar.hpp>
extern void * pchecker;
//#define __CHECK_MEMORY__

class adpool
{
  static int num_adpools;
  int adpool_vector_flag;
public:
  int depth_check(void);
  int nvar;
  int& on_adpool_vector(void) {return adpool_vector_flag;}
  char * last_chunk;
  struct link { link * next; };
  int num_allocated;
  int num_chunks;
  int nelem;
  unsigned size;
  link * head;
  double * first;
  adpool(adpool&);  // copy protection
  void operator = (adpool&); // copy protection
  void grow(void);
#if defined(__CHECK_MEMORY__)
  int maxchunks;
  char * minaddress[2000];
  char * maxaddress[2000];
  int * pvalues;
  int nalloc;
#endif
public:
  void clean(void);
  adpool(unsigned);
  void set_size(unsigned);
  adpool(void);
 ~adpool();
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

#endif //defined(__AD_POOL__)
