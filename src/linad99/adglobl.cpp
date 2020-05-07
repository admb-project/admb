/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Global and static types for ad_comm, initial_params and objective_function_values classes.
*/

#include <admodel.h>

 int initial_params::straight_through_flag=0;
 unsigned char ad_comm::directory_prefix='\\';
 unsigned int ad_comm::wd_flag=0;
 adtimer * ad_comm::ptm=0;
 adtimer * ad_comm::ptm1=0;
 int ad_comm::bandwidth=0;

#if defined(USE_ADPVM)
adpvm_manager* ad_comm::pvm_manager = NULL;
#endif

 int ad_comm::time_flag=0;
 adstring ad_comm::subdir;
 cifstream * ad_comm::global_datafile=NULL;
 cifstream * ad_comm::global_parfile=NULL;
 ofstream *  ad_comm::global_logfile=NULL;
 uistream *  ad_comm::global_bparfile=NULL;
 adstring ad_comm::adprogram_name;
 adstring ad_comm::working_directory_path;
 char ad_comm::option_flags[10];
 int ad_comm::argc=0;
 int ad_comm::no_pvm_flag=0;
 int ad_comm::no_atlas_flag=0;
 int ad_comm::print_hess_and_exit_flag;
 int ad_comm::no_ln_det_choleski_flag=0;
 char ** ad_comm::argv=NULL;
 double objective_function_value::fun_without_pen=0;
