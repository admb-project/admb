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

thread_local gradient_structure* gradient_structure::_instance = nullptr;

/// Allocate array of gradient_structure instances with size elements.
void gradient_structure::create(const unsigned int size)
{
  gradients_size = size + 1;
  gradients = new gradient_structure*[gradients_size];
  for (int id = 1; id <= gradients_size; ++id)
  {
    gradients[id] = new gradient_structure(10000L, id);
  }
  gradients[0] = _instance;
}
/// Get current instance of gradient_structure.
gradient_structure* gradient_structure::get()
{
  return _instance;
}
/// Set _instance of gradient_structure from instances with id.
gradient_structure* gradient_structure::set(const unsigned int id)
{
#ifdef DEBUG
  assert(id <= gradients_size);
#endif
  _instance = gradients[id];
  return _instance;
}
/// Delete gradient_structure instances.
void gradient_structure::clean()
{
  if (gradients != nullptr)
  {
    for (int id = 1; id <= gradients_size; ++id)
    {
      if (gradients[id] != nullptr)
      {
        delete gradients[id];
        gradients[id] = nullptr;
      }
    }
    gradients[0] = nullptr;

    delete [] gradients;
    gradients = nullptr;
  }
  gradients_size = 0;
}
