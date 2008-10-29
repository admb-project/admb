void * farptr_norm(void *);
long int farptr_tolong(void *) ;
#if (!defined(__ZTC__) || defined(DOS386))
  long int _farptr_tolong(void *);
#endif
void denormalize_ptr(void * , unsigned int byte_offset);
