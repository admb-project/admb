/**
 * $Id$
 *
 * $Rev   ::                       $: Revision of last commit
 * $Author::                       $: Author of last commit
 * $Date  ::                       $: Date of last commit
 *
 * Author: David Fournier
 * Copyright (c) 2008 Regents of the University of California
 * 
 * License:
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "New Free BSD" license
 * 
 * Copyright (c)  2008 Regents of the University of California.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2.  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * 3.  Neither the name of the  University of California, Otter Research,
 * nor the ADMB Foundation nor the names of its contributors may be used
 * to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


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
