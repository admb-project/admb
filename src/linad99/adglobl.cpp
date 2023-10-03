/**
@file
@author David Fournier
@copyright Copyright (c) 2008-2020 Regents of the University of California

@brief Global and static types for ad_comm, initial_params and objective_function_values classes.
*/

#ifdef DEBUG
  #include <cassert>
#endif
#include <admodel.h>

 int initial_params::straight_through_flag=0;
 unsigned char ad_comm::directory_prefix='\\';
 unsigned int ad_comm::wd_flag=0;
 int ad_comm::bandwidth=0;

#if defined(USE_ADPVM)
adpvm_manager* ad_comm::pvm_manager = NULL;
#endif

 adstring ad_comm::subdir;

THREAD cifstream* ad_comm::global_datafile = nullptr;
THREAD cifstream* ad_comm::global_parfile = nullptr;
THREAD ofstream* ad_comm::global_logfile = nullptr;

THREAD_LOCAL uistream* ad_comm::global_bparfile = nullptr;
THREAD_LOCAL adstring ad_comm::adprogram_name;
 adstring ad_comm::working_directory_path;
 char ad_comm::option_flags[10];
THREAD_LOCAL int ad_comm::argc = 0;
 int ad_comm::no_pvm_flag=0;
 int ad_comm::no_atlas_flag=0;
 int ad_comm::print_hess_and_exit_flag;
 int ad_comm::no_ln_det_choleski_flag=0;
THREAD_LOCAL char** ad_comm::argv = nullptr;
THREAD_LOCAL double objective_function_value::fun_without_pen = 0.0;

int function_minimizer::output_flag = defaults::output;

THREAD_LOCAL DF_FILE* gradient_structure::fp = nullptr;
THREAD_LOCAL gradient_structure* gradient_structure::_instance = nullptr;
THREAD_LOCAL grad_stack* gradient_structure::GRAD_STACK1 = nullptr;

std::ostream& get_output_stream()
{
  if (function_minimizer::output_flag < 2 && ad_comm::global_logfile)
  {
    return *ad_comm::global_logfile;
  }
  return std::cout;
}
