/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */
/**
 * \file
 * Description not yet available.
 */
#include <df1b2fun.h>
#define _FIVE_ 50  // must defien the macro SIX to be one greater than FIVE
#define _SIX_ 51
int df1b2variable::allocation_counter=0;
int df1b2variable::current_allocation_index=0;
const int df1b2variable::adpool_vectorsize=_FIVE_;
int df1b2variable::adpool_use_index[_SIX_];
adpool * df1b2variable::adpool_vector[_SIX_];

/**
 * Description not yet available.
 * \param
 */
void df1b2variable::increment_adpool_counter(void)
{
 adpool_counter++;
 if (adpool_counter>  _FIVE_ -2)
 {
   cerr << "need to increase adpool_counter" << endl;
   ad_exit(1);
 }
}

unsigned int df1b2variable::nvar_vector[_FIVE_];
int df1b2variable::pool_allocation_number[_FIVE_];

double initial_df1b2params::cobjfun=0.0;
int initial_df1b2params::separable_flag=0;
int initial_df1b2params::have_bounded_random_effects=0;
int initial_df1b2params::separable_calculation_type=0;
int df1b2variable::adpool_counter=0;
#if defined(__x86_64) || (defined(_MSC_VER) && defined(_M_X64))
lmatrix* initial_df1b2params::pointer_table=0;
#else
imatrix* initial_df1b2params::pointer_table=0;
#endif
class df1b2_gradlist;

df1b2_gradlist * f1b2gradlist = NULL;
df1b2_gradlist * localf1b2gradlist = 0;
df1b2_gradlist * globalf1b2gradlist = 0;

int df1b2variable::noallocate=0;

initial_df1b2params ** initial_df1b2params::varsptr
  =new P_INITIAL_DF1B2PARAMS[1000];
int initial_df1b2params::num_initial_df1b2params=0;         // array

int initial_df1b2params::num_initial_df1b2params_sav=0;         // array
initial_df1b2params ** initial_df1b2params::varsptr_sav=0;

int initial_df1b2params::current_phase=0;

int df1b2variable::adpool_stack_pointer=0;
const int df1b2variable::adpool_stack_size=50;
adpool * df1b2variable::adpool_stack[50];
unsigned int df1b2variable::adpool_nvar_stack[50];
