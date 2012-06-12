/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2011 Regents of the University of California 
 */
#include "fvar.hpp"
#ifdef __ZTC__
  #include <iostream.hpp>
#endif

#ifdef __TURBOC__
  #pragma hdrstop
  #pragma options -h-
  #include <iostream.h>
#endif
#include <stdlib.h>

int num_free_obj=0;
extern char demo_capacity[];
extern char please_buy[];
extern char otter_address1[];
extern char otter_address2[];
extern char otter_address3[];
extern char otter_address4[];
extern char otter_address5[];
int ad_kill_flag=0;

/**
 * Description not yet available.
 * \param
 */
arr_link::arr_link()
{
  prev=NULL;
  next=NULL;
  free_prev=NULL;
  free_next=NULL;
  status=0;
  // free_list_status=0;
  size=0;
  offset=0;
}

/**
 * Description not yet available.
 * \param
 */
void arr_free_remove(arr_link * tmp)
{
  num_free_obj--;
  // if this is the last free object reset list pointer
  if (!tmp->free_next) 
  {
    gradient_structure::ARR_LIST1->free_last=tmp->free_prev;
  }
  // This routine removes the link pointed to by tmp
  if (tmp->free_next)  // Make the one after it point to tmp->prev
  {
    tmp->free_next->free_prev = tmp->free_prev;
  }

  if (tmp->free_prev)  // Make the one before it point to tmp->next
  {
    tmp->free_prev->free_next = tmp->free_next;
  }
}
    
/**
 * Description not yet available.
 * \param
 */
void arr_free_add(arr_link * tmp)
{
  num_free_obj++;
  // This routine adds the link pointed to by tmp to  the end of the free list
  tmp->free_prev = gradient_structure::ARR_LIST1->free_last;
  gradient_structure::ARR_LIST1->free_last=tmp;
  tmp->free_next = NULL;
  if (tmp->free_prev) tmp->free_prev->free_next = tmp;
}

/**
 * Description not yet available.
 * \param
 */
double_and_int * arr_new(unsigned int sz)
{
  if (!gradient_structure::instances)
  {
    cerr << "Error -- you are trying to create a dvar_vector object"
            " when there is " << endl << "no object of type"
            " gradient_structure in scope " << endl;
    ad_exit(1);
  }

  char * temp_ptr;

  // this routine allocated a block of memory of sizeof(double)*sz bytes
  // for the gradients of an array or matrix of prevariables 

  arr_link * tmp = gradient_structure::ARR_LIST1->free_last;

  unsigned int bytes_needed=sizeof(double_and_int)*sz;
  int ss=0;
  if (ss)
  {
    double_and_int * tt=0;
    return tt;
  }

  while (tmp)
  {
    if (tmp->size >= bytes_needed)
    {
      // if the free block within 20 bytes of the size you want
      // simply mark it occupied and return it

      if (tmp->size <= bytes_needed + 50)
      {
        tmp->status = 1;
        // remove tmp from the free list
        arr_free_remove(tmp);
        
	temp_ptr = gradient_structure::ARRAY_MEMBLOCK_BASE + tmp->offset;

	(* (arr_link **) (temp_ptr)) = tmp; //put the address
					  //tmp into the location pointed to
					  //by temp_ptr
	return  (double_and_int *) (temp_ptr);
      }
      else
      {
	// otherwise split up this memory block and return
	// the part you need

	arr_link * tmp1 = new arr_link;
        gradient_structure::ARR_LIST1->number_arr_links += 1;

        // put the new link tmp1-> into the list BEFORE tmp->

        tmp1->prev=tmp->prev;

        if(tmp1->prev)
        {
          tmp1->prev->next=tmp1;
        }

        tmp1->next=tmp;
        tmp->prev=tmp1;

        // get the size of the new link and mark it free

        tmp1->size=bytes_needed;
	tmp1->status=1;
        tmp1->offset=tmp->offset;

        tmp->offset+=bytes_needed;
	tmp->size-=bytes_needed;

	temp_ptr = gradient_structure::ARRAY_MEMBLOCK_BASE + tmp1->offset;

	(* (arr_link **) (temp_ptr )) = tmp1; //put the address
					 //pointed to by
					 // tmp1 into the location pointed to
					 //by temp_ptr
	return  (double_and_int *) (temp_ptr);
      }
    }
    tmp=tmp->free_prev;
  }
  // couldn't find a free block large enough
  // make a new block

  tmp = new arr_link;
  if (tmp==0)
  {
    cerr << "Error allocating new arr_link" << endl;
    ad_exit(1);
  }

  gradient_structure::ARR_LIST1->number_arr_links  += 1;

  tmp->prev = gradient_structure::ARR_LIST1->last; // the new block point back 
                                                 // at the previous last block

  if (gradient_structure::ARR_LIST1->last)
  {
    gradient_structure::ARR_LIST1->last->next = tmp; // the previous last 
                                                  // block point forward to tmp
  }                             
  gradient_structure::ARR_LIST1->last = tmp;         // tmp is the new last block

  tmp->next = 0;

  tmp->status = 1;

  tmp->offset = gradient_structure::ARR_LIST1->last_offset;

  gradient_structure::ARR_LIST1->last_offset += bytes_needed;

  if (gradient_structure::ARR_LIST1->last_offset>
    (unsigned int)gradient_structure::max_last_offset )
  {
    gradient_structure::max_last_offset=
      gradient_structure::ARR_LIST1->last_offset;
  }

  if (gradient_structure::ARR_LIST1->last_offset > gradient_structure::ARR_LIST1->max_last_offset)
  {
    gradient_structure::ARR_LIST1->max_last_offset=gradient_structure::ARR_LIST1->last_offset;
  }

  if( gradient_structure::ARR_LIST1->last_offset >=gradient_structure::ARRAY_MEMBLOCK_SIZE)
  {
#if defined(AD_DEMO)
    cout << "demo capacity exceeded" << endl;
#endif
    cout << gradient_structure::ARR_LIST1->last_offset <<">="
	     <<  gradient_structure::ARRAY_MEMBLOCK_SIZE <<"\n";
#if !defined(AD_DEMO)
    cout << " No memory for dvar_vectors\n"
	 << " Need to increase ARRAY_MEMBLOCK_SIZE parameter\n"
      "In gradient_structure declaration\n";
#else
    cout << demo_capacity << endl;
    cout << please_buy << endl;
    cout << otter_address1 << endl;
    cout << otter_address2 << endl;
    cout << otter_address3 << endl;
    cout << otter_address4 << endl;
    cout << otter_address5 << endl;
#endif
    //throw gradient_structure::arrmemblerr();
    ad_exit(1);
  }

  tmp->size = bytes_needed;

  temp_ptr = gradient_structure::ARRAY_MEMBLOCK_BASE + tmp->offset;

  (*(arr_link **) (temp_ptr )) = tmp; //put the address 
                                   // tmp into the location pointed to
                                   //by temp_ptr
         
//  return  (double_and_int *) (temp_ptr+sizeof(double_and_int));
  return  (double_and_int *) (temp_ptr);

}

/**
 * Description not yet available.
 * \param
 */
void arr_free(double_and_int * varr)
{
  // This routines frees up a memory block and
  // consolidates the free blocks if possible
  //cout<< "calling arr_free\n";
  char * temp_ptr;
  arr_link * ptr;

  temp_ptr = (char *) varr;

  //temp=sizeof(double_and_int);
//  ptr = *(arr_link **) (temp_ptr-temp);
  ptr = *(arr_link **) (temp_ptr);

  //mark this block free

  ptr->status = 0;
 // cout <<"Marking arr_link with adress  "<<farptr_tolong(ptr)<<"free\n";

  // if there is a block after this add this one to the free list 
  if (ptr->next) arr_free_add(ptr);
  
  if (!ptr->next)  // Is this the last link?
  {
    // Check to see if ptr->prev is free and should be deleted as well
    // ... but first check to see if ptr is first block in list
    // which will be indicated by ptr->prev being a NULL pointer
    if (ptr->prev && !ptr->prev->status)
    {
      // delete ptr->prev
      gradient_structure::ARR_LIST1->last = ptr->prev->prev; 
      //if (gradient_structure::ARR_LIST1->last ==0) 
       // cout << "gradient_structure::ARR_LIST1->last =0 " << endl;

      gradient_structure::ARR_LIST1->last_offset -= ptr->size + ptr->prev->size;
      arr_free_remove(ptr->prev);
      arr_remove(&(ptr->prev));
    }
    else
    {
      gradient_structure::ARR_LIST1->last = ptr->prev; 
      //if (gradient_structure::ARR_LIST1->last ==0) 
       // cout << "gradient_structure::ARR_LIST1->last =0 " << endl;
      gradient_structure::ARR_LIST1->last_offset -= ptr->size;
    }
    arr_remove(&ptr);
  }
  else
  {
     // There is another link after this one?

    if (!ptr->next->status) // If yes is it free?
    {
      // add its memory capacity to the present one and delete it

      ptr->size += ptr->next->size;

      arr_free_remove(ptr->next);
      arr_remove(&ptr->next);

    }    
  
    if (ptr->prev)  // Is there another link before this one?
    {
      if (!ptr->prev->status) // If yes is it free?
      {
        // we will keep ptr->prev and add ptr to it

        ptr->prev->size += ptr->size;
        arr_free_remove(ptr);
        arr_remove(&ptr);
      }    
    }
  }
}

/**
 * Description not yet available.
 * \param
 */
void check_derivative_values(const char * _s)
{
  char * s = (char *) _s;
  //char label[20];
  save_identifier_string(s);
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(df_check_derivative_values);
}

/**
 * Description not yet available.
 * \param
 */
void check_derivative_values(const char * _s,int i)
{
  char * s = (char *) _s;
  //char label[20];
  save_identifier_string(s);
  save_int_value(i);
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(df_check_derivative_values_indexed);
}

void df_print_identifier_string(void);

/**
 * Description not yet available.
 * \param
 */
void insert_identifier_string(const char * _s)
{
  char * s = (char *) _s;
  save_identifier_string(s);
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(df_print_identifier_string);
}

/**
 * Description not yet available.
 * \param
 */
void check_derivative_values_break(const char * _s,int i,int b)
{
  char * s = (char *) _s;
  //char label[20];
  save_identifier_string(s);
  save_int_value(i);
  save_int_value(b);
  gradient_structure::GRAD_STACK1->
    set_gradient_stack(df_check_derivative_values_indexed_break);
}

void  rrkludge(double * temp_ptr){;}

/**
 * Description not yet available.
 * \param
 */
void df_check_derivative_values(void)
{
  //char label[20];
  adstring str=get_string_marker();
  double * temp_ptr = gradient_structure::get_ARRAY_MEMBLOCK_BASE();
  unsigned long int max_last_offset = 
    gradient_structure::ARR_LIST1->get_max_last_offset();
     unsigned int size = sizeof(double_and_int );

  int icount=0;
  int exit_flag=0;
  cout << str << endl;
  unsigned int i;
  for (i=0 ; i< (max_last_offset/size) ; i++ )
  {
    if (fabs(temp_ptr[i])>1.e+8) 
    {
      if (ad_kill_flag) exit_flag=1;
      icount++;
      cout << i << " " << temp_ptr[i] << endl; 
      if (icount>10) 
      {
         break;
      }
    }
  }

  icount=0;
  for (i=0; i<gradient_structure::GRAD_LIST->nlinks; i++)
  {
    if (* (double*) (gradient_structure::GRAD_LIST->dlink_addresses[i])
      > 1.e+8) 
    {
      icount++;
       cout << "dlist " << i << " " << setscientific() <<
         * (double*) (gradient_structure::GRAD_LIST->dlink_addresses[i])
          << endl;
      if (icount>10) 
      {
        if (ad_kill_flag) exit_flag=1;
        break;
      }
    }
  }
  if (exit_flag) exit(1);
}

//extern  ofstream gradlog;

/**
 * Description not yet available.
 * \param
 */
void df_print_identifier_string(void)
{
  adstring str=get_string_marker();
  cout << "GS = " << str << endl;
  //gradlog << "GS = " << str << endl;
}

/**
 * Description not yet available.
 * \param
 */
void df_check_derivative_values_indexed(void)
{
  //char label[20];
  int index=restore_int_value();
  adstring str=get_string_marker();
  double * temp_ptr = gradient_structure::get_ARRAY_MEMBLOCK_BASE();
  unsigned long int max_last_offset = 
    gradient_structure::ARR_LIST1->get_max_last_offset();
     unsigned int size = sizeof(double_and_int );

  int icount=0;
  int exit_flag=0;
  cout << str << " index = " << index << endl;
  unsigned int i;
  for (i=0 ; i< (max_last_offset/size) ; i++ )
  {
    if (fabs(temp_ptr[i])>1.e+8) 
    {
      if (ad_kill_flag) exit_flag=1;
      icount++;
      cout << i << " " << setscientific() << temp_ptr[i] << endl; 
      if (icount>10) break;
    }
  }

  icount=0;
  for (i=0; i<gradient_structure::GRAD_LIST->nlinks; i++)
  {
    if (* (double*) (gradient_structure::GRAD_LIST->dlink_addresses[i])
      > 1.e+8) 
    {
      icount++;
      if (ad_kill_flag) exit_flag=1;
       cout << "dlist " << i << " " << setscientific() <<
         * (double*) (gradient_structure::GRAD_LIST->dlink_addresses[i])
          << endl;
      if (icount>10) 
      {
         break;
      }
    }
  }
  if (exit_flag) exit(1);
}

/**
 * Description not yet available.
 * \param
 */
void df_check_derivative_values_indexed_break(void)
{
  //char label[20];
  int b=restore_int_value();
  int index=restore_int_value();
  adstring str=get_string_marker();
  double * temp_ptr = gradient_structure::get_ARRAY_MEMBLOCK_BASE();
  unsigned long int max_last_offset = 
    gradient_structure::ARR_LIST1->get_max_last_offset();
     unsigned int size = sizeof(double_and_int );

  if (index<=b)
  {
    cout << "break condition" << endl;
  }
  int icount=0;
  int exit_flag=0;
  cout << str << " index = " << index << endl;
  unsigned int i;
  for (i=0 ; i< (max_last_offset/size) ; i++ )
  {
    if (fabs(temp_ptr[i])>1.e+8) 
    {
      if (ad_kill_flag) exit_flag=1;
      icount++;
      cout << i << " " << temp_ptr[i] << endl; 
      if (icount>10) break;
    }
  }

  icount=0;
  for (i=0; i<gradient_structure::GRAD_LIST->nlinks; i++)
  {
    if (* (double*) (gradient_structure::GRAD_LIST->dlink_addresses[i])
      > 1.e+8) 
    {
      icount++;
      if (ad_kill_flag) exit_flag=1;
       cout << "dlist " << i << " " << 
         * (double*) (gradient_structure::GRAD_LIST->dlink_addresses[i])
          << endl;
      if (icount>10) 
      {
         break;
      }
    }
  }
  if (exit_flag) exit(1);
}

/**
 * Description not yet available.
 * \param
 */
void arr_remove(arr_link ** pptr)
{
  arr_link * tmp = *pptr;
  // This routine removes the link pointed to by tmp
  if (tmp->next)  // Make the one after it point to tmp->prev
  {
    tmp->next->prev = tmp->prev;
  }

  if (tmp->prev)  // Make the one before it point to tmp->next
  {
    tmp->prev->next = tmp->next;
  }

  if (tmp == NULL)
  {
    cout <<" Error -- tried to delete NULL arr_link in arr_remove\n";
    ad_exit(23);
  }
  else
  {
#ifdef DIAG
#ifdef __ZTC__
      cout <<"Deleting an arr_link with adress  "<<_farptr_tolong(tmp)<<"\n";
#else
      cout <<"Deleting an arr_link with adress  "<<farptr_tolong(tmp)<<"\n";
#endif
#endif
    delete tmp;
    tmp=NULL;
  }
  gradient_structure::ARR_LIST1->number_arr_links -= 1;
  //cout <<  "after delete number_arr_links = "<<  gradient_structure::ARR_LIST1->number_arr_links <<"\n";
}
