/**
 * $Id:   $
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



#if defined(__BORLANDC__ )
#  pragma interface
#endif
    class dvect_ptr_ptr
    {
      dvector ** m;
    };
    class dlink
    {
       double_and_int  di;
       dlink *       prev;
    public:  // comments
      dlink * previous();
      inline double_and_int * get_address()
      {
        return &di;
      } //access function

      //friend tempvar();
      //friend class prevariable;
      //friend class tempvar;
      friend class dlist;
      friend void gradcalc(int nvar,BOR_CONST dvector& g);
      friend void gradloop();
      friend double_and_int * gradnew();
    };

    class dlist
    {
      dlink * last;
      unsigned int last_offset;
      unsigned int nlinks;
      dlink ** dlink_addresses;

    public:
      dlist();  // constructor
      void check_list(void);  // check list integrity
     ~dlist();  // destructor
      dlink * create();     //create a new link 
      void free_remove(dlink * rem);
      dlink * append(dlink *);  // add a link
      dlink* dlist::last_remove();
      friend void gradcalc(int nvar,BOR_CONST dvector& g);
      friend void gradloop();
      friend void gradient_structure::restore_variables();
      friend void gradient_structure::save_variables();
      friend void gradient_structure::jacobcalc(int nvar,BOR_CONST dmatrix& jac);
      friend void gradient_structure::jacobcalc(int nvar,BOR_CONST ofstream& jac);
      friend void gradient_structure::jacobcalc(int nvar,BOR_CONST uostream& jac);
    };

    class indvar_offset_list;
    class grad_stack_entry
    {
    public:
      void (* func) (void);
      double * dep_addr;
      double * ind_addr1;
      double  mult1;
      double * ind_addr2;
      double  mult2;
    public:
      friend void gradcalc(int nvar,BOR_CONST dvector& g);
      friend void gradloop();
      friend void default_evaluation(void);
      friend class grad_stack;
      friend void gradient_structure::jacobcalc(int nvar,BOR_CONST dmatrix& jac);
    };

    class grad_stack
    {
      grad_stack_entry * true_ptr_first;
      grad_stack_entry * ptr_first;
      grad_stack_entry * ptr_last;
      long int length;
      long int true_length;
    public:
      grad_stack_entry * ptr;
    private:
      //lvector * table;
      // js
      int _GRADFILE_PTR; // should be int gradfile_handle;
      int _GRADFILE_PTR1; // should be int gradfile_handle;
      int _GRADFILE_PTR2; // should be int gradfile_handle;
      int _VARSSAV_PTR; // should be int gradfile_handle;
      char gradfile_name[61];
      char gradfile_name1[61];
      char gradfile_name2[61];
      char var_store_file_name[61];
      void create_gradfile();
      long end_pos;
      long end_pos1;
      long end_pos2;
      dmatrix * table;
    public:
      friend void gradcalc(int nvar,BOR_CONST dvector& g);
      friend void default_evaluation(void);
      friend void default_evaluation3ind(void);
      friend void default_evaluation4ind(void);
      friend void gradloop();
      ostream& operator  <<(grad_stack);
     void print();
      grad_stack();
     ~grad_stack();
      void write_grad_stack_buffer(void);
      inline void set_gradient_stack(void (* func) (void),
	 double * dep_addr,double * ind_addr1=NULL, double mult1=0,
	 double * ind_addr2=NULL, double mult2=0);

      inline void set_gradient_stack(void (* func) (void),
	 double * dep_addr,double * ind_addr1,double * ind_addr2);


      inline void set_gradient_stack0(void (* func)(void),
        double * dep_addr);

      inline void set_gradient_stack1(void (* func) (void),
	 double * dep_addr,double * ind_addr1);

      inline void set_gradient_stack2(void (* func) (void),
	 double * dep_addr,double * ind_addr1, double mult1);

      inline void set_gradient_stack4(void (* func) (void),
	 double * dep_addr,double * ind_addr1, double * ind_addr2);

      inline void set_gradient_stack(void (* func)(void),
        double * dep_addr,double * ind_addr1, double mult1, double * ind_addr2,
        double mult2,double * ind_addr3, double mult3,double * ind_addr4,
        double mult4);
    
      inline void set_gradient_stack(void (* func)(void),
        double * dep_addr,double * ind_addr1, double mult1, double * ind_addr2,
        double mult2,double * ind_addr3, double mult3);
    
      int read_grad_stack_buffer(long int& lpos);
      void set_gradient_stack(void (*ptr)(void));
      void set_gbuffer_pointers(void);
       //js
      void increment_current_gradfile_ptr(void);
      int decrement_current_gradfile_ptr(void);
      //void open_gradfile();
      //void close_gradfile();
      #ifndef __MSC__
	int& grad_stack::gradfile_handle();
      #else
	int grad_stack::gradfile_handle();
      #endif
      char* get_gradfile_name();
      friend class gradient_structure;
      //int get_ngradfiles();
    }; // end of grad_stack

    inline void grad_stack::set_gradient_stack(void (* func)(void),
      double * dep_addr,double * ind_addr1, double mult1, double * ind_addr2,
      double mult2)
    {
      #ifdef NO_DERIVS
	if (!gradient_structure::no_derivatives)
	{
      #endif
	  if (ptr > ptr_last)
	  {
	     // current buffer is full -- write it to disk and reset pointer
	     // and counter
	     this->write_grad_stack_buffer();
	  }
	  ptr->func = func;
	  ptr->dep_addr = dep_addr;
	  ptr->ind_addr1 = ind_addr1;
	  ptr->mult1=mult1;
	  ptr->ind_addr2 = ind_addr2;
	  ptr->mult2=mult2;
	  ptr++;
      #ifdef NO_DERIVS
	}
      #endif
    }

    inline void grad_stack::set_gradient_stack(void (* func)(void),
      double * dep_addr,double * ind_addr1, double mult1, double * ind_addr2,
      double mult2,double * ind_addr3, double mult3)
    {
      #ifdef NO_DERIVS
	if (!gradient_structure::no_derivatives)
	{
      #endif
	  if (ptr > ptr_last)
	  {
	     // current buffer is full -- write it to disk and reset pointer
	     // and counter
	     this->write_grad_stack_buffer();
	  }
	  ptr->func = NULL;
	  ptr->dep_addr = dep_addr;
	  ptr->ind_addr1 = ind_addr1;
	  ptr->mult1=mult1;
	  ptr->ind_addr2 = ind_addr2;
	  ptr->mult2=mult2;
	  ptr++;
	  if (ptr > ptr_last)
	  {
	     // current buffer is full -- write it to disk and reset pointer
	     // and counter
	     this->write_grad_stack_buffer();
	  }
	  ptr->func = func;
	  ptr->ind_addr1 = ind_addr3;
	  ptr->mult1=mult3;
	  ptr++;
      #ifdef NO_DERIVS
	}
      #endif
    }

    inline void grad_stack::set_gradient_stack(void (* func)(void),
      double * dep_addr,double * ind_addr1, double mult1, double * ind_addr2,
      double mult2,double * ind_addr3, double mult3,double * ind_addr4,
      double mult4)
    {
      #ifdef NO_DERIVS
	if (!gradient_structure::no_derivatives)
	{
      #endif
	  if (ptr > ptr_last)
	  {
	     // current buffer is full -- write it to disk and reset pointer
	     // and counter
	     this->write_grad_stack_buffer();
	  }
	  ptr->func = NULL;
	  ptr->dep_addr = dep_addr;
	  ptr->ind_addr1 = ind_addr1;
	  ptr->mult1=mult1;
	  ptr->ind_addr2 = ind_addr2;
	  ptr->mult2=mult2;
	  ptr++;
	  if (ptr > ptr_last)
	  {
	     // current buffer is full -- write it to disk and reset pointer
	     // and counter
	     this->write_grad_stack_buffer();
	  }
	  ptr->func = func;
	  ptr->ind_addr1 = ind_addr3;
	  ptr->mult1=mult3;
	  ptr->ind_addr2 = ind_addr4;
	  ptr->mult2=mult4;
	  ptr++;
      #ifdef NO_DERIVS
	}
      #endif
    }

    inline void grad_stack::set_gradient_stack(void (* func)(void),
      double * dep_addr,double * ind_addr1,double * ind_addr2)
    {
      #ifdef NO_DERIVS
	if (!gradient_structure::no_derivatives)
	{
      #endif
	  if (ptr > ptr_last)
	  {
	     // current buffer is full -- write it to disk and reset pointer
	     // and counter
	     this->write_grad_stack_buffer();
	  }
	  ptr->func = func;
	  ptr->dep_addr = dep_addr;
	  ptr->ind_addr1 = ind_addr1;
	  ptr->ind_addr2 = ind_addr2;
	  ptr++;
      #ifdef NO_DERIVS
	}
      #endif
    }

    inline void grad_stack::set_gradient_stack2(void (* func)(void),
      double * dep_addr,double * ind_addr1, double mult1)
    {
      #ifdef NO_DERIVS
        if (!gradient_structure::no_derivatives)
        {
      #endif
          if (ptr > ptr_last)
          {
             // current buffer is full -- write it to disk and reset pointer
             // and counter
             this->write_grad_stack_buffer();
          }
          ptr->func = func;
          ptr->dep_addr = dep_addr;
          ptr->ind_addr1 = ind_addr1;
          ptr->mult1=mult1;
          ptr++;
      #ifdef NO_DERIVS
        }
      #endif
    }

    inline void grad_stack::set_gradient_stack4(void (* func)(void),
      double * dep_addr,double * ind_addr1, double * ind_addr2)
    {
      #ifdef NO_DERIVS
	if (!gradient_structure::no_derivatives)
	{
      #endif
	  if (ptr > ptr_last)
	  {
	     // current buffer is full -- write it to disk and reset pointer
	     // and counter
	     this->write_grad_stack_buffer();
	  }
	  ptr->func = func;
	  ptr->dep_addr = dep_addr;
	  ptr->ind_addr1 = ind_addr1;
	  ptr->ind_addr2 = ind_addr2;
	  ptr++;
      #ifdef NO_DERIVS
	}
      #endif
    }



   /*
    inline void grad_stack::set_gradient_stack(void (* func)(void),
      double * dep_addr,double * ind_addr1, double mult1)
    {
      #ifdef NO_DERIVS
	if (!gradient_structure::no_derivatives)
	{
      #endif
	  if (ptr > ptr_last)
	  {
	     // current buffer is full -- write it to disk and reset pointer
	     // and counter
	     this->write_grad_stack_buffer();
	  }
	  ptr->func = func;
	  ptr->dep_addr = dep_addr;
	  ptr->ind_addr1 = ind_addr1;
	  ptr->mult1=mult1;
          ptr++;
      #ifdef NO_DERIVS
        }
      #endif
    }
    */

    inline void grad_stack::set_gradient_stack1(void (* func)(void),
      double * dep_addr,double * ind_addr1)
    {
      #ifdef NO_DERIVS
        if (!gradient_structure::no_derivatives)
        {
      #endif
          if (ptr > ptr_last)
          {
             // current buffer is full -- write it to disk and reset pointer
             // and counter
             this->write_grad_stack_buffer();
          }
          ptr->func = func;
          ptr->dep_addr = dep_addr;
          ptr->ind_addr1 = ind_addr1;
          ptr++;
      #ifdef NO_DERIVS
        }
      #endif
    }

   /*
    inline void grad_stack::set_gradient_stack(void (* func)(void),
      double * dep_addr,double * ind_addr1)
    {
      #ifdef NO_DERIVS
        if (!gradient_structure::no_derivatives)
        {
      #endif
          if (ptr > ptr_last)
          {
             // current buffer is full -- write it to disk and reset pointer
             // and counter
             this->write_grad_stack_buffer();
          }
          ptr->func = func;
          ptr->dep_addr = dep_addr;
          ptr->ind_addr1 = ind_addr1;
          ptr++;
      #ifdef NO_DERIVS
        }
      #endif
    }
   */

    inline void grad_stack::set_gradient_stack0(void (* func)(void),
      double * dep_addr)
    {
      #ifdef NO_DERIVS
        if (!gradient_structure::no_derivatives)
        {
      #endif
          if (ptr > ptr_last)
          {
             // current buffer is full -- write it to disk and reset pointer
             // and counter
             this->write_grad_stack_buffer();
          }
          ptr->func = func;
          ptr->dep_addr = dep_addr;
          ptr++;
      #ifdef NO_DERIVS
        }
      #endif
    }

   /*
    inline void grad_stack::set_gradient_stack(void (* func)(void),
      double * dep_addr)
    {
      #ifdef NO_DERIVS
        if (!gradient_structure::no_derivatives)
        {
      #endif
          if (ptr > ptr_last)
          {
             // current buffer is full -- write it to disk and reset pointer
             // and counter
             this->write_grad_stack_buffer();
          }
          ptr->func = func;
          ptr->dep_addr = dep_addr;
          ptr++;
      #ifdef NO_DERIVS
        }
      #endif
    }
*/
    inline void grad_stack::set_gradient_stack(void (*func)(void))
    {
      #ifdef NO_DERIVS
        if (!gradient_structure::no_derivatives)
        {
      #endif
          if (ptr > ptr_last)
          {
            // current buffer is full -- write it to disk and reset pointer
            // and counter
            this->write_grad_stack_buffer();
          }

          ptr->dep_addr = NULL;
          ptr->func = func;
          ptr->ind_addr2 = NULL ;// want to put a long int                                            //into the memory space of a double
          ptr->mult2=0;
          ptr++;
      #ifdef NO_DERIVS
        }
      #endif
    }

    class indvar_offset_list
    {
      int nvar; // The number of independent variables
      double **  address;
  
    public:
      friend class gradient_structure;
      inline double * get_address(BOR_CONST int& i) { return(address[i]);}
      void put_address(unsigned int& i, double * iaddress) 
      { 
        address[i] = iaddress;
        //  cerr << "In put_address i = " << i << "\n";
      }
    };

    void gradfree(dlink *);
