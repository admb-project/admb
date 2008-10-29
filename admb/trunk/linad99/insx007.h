    class arr_link;
    class arr_list
    {
      arr_link * last;
      arr_link * free_last;
      unsigned long int last_offset;
      unsigned long int max_last_offset;
      long int number_arr_links;
      friend class arr_link;
  
    public:
    
      arr_list(void)
      {
        last = 0;
        free_last = 0;
        last_offset = 0;
        max_last_offset = 0;
        number_arr_links = 0;
      }
      unsigned long int get_last_offset() { return last_offset;}
      unsigned long int get_number_arr_links(){ return(number_arr_links);}
      unsigned long int get_max_last_offset() { return (max_last_offset);}
      void reset_max_last_offset() {max_last_offset=0;}
      friend double_and_int * arr_new(unsigned int);
      friend void arr_free(double_and_int *);
      friend void arr_remove(arr_link **);
      friend void arr_free_list_remove(arr_link **);
      friend void arr_free_add(arr_link *);
      friend void arr_free_remove(arr_link *);
    };
  
    class arr_link
    {
       arr_link *          prev;
       arr_link *          next;
       arr_link *          free_prev;
       arr_link *          free_next;
       unsigned int        status;
       // unsigned int     free_list_status;
       unsigned int        size;
       unsigned long int   offset;
     public:
       arr_link();
    
       friend double_and_int * arr_new(unsigned int);
       friend void arr_free(double_and_int *);
       friend void arr_remove(arr_link **);
       friend void arr_free_remove(arr_link *);
       friend void arr_free_add(arr_link *);
    };
