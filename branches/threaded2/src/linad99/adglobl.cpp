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
#include <admodel.h>
#include <thread>

__thread int initial_params::straight_through_flag = 0;
 __ADMBTHREAD__ int  adpthreads_manager::slave_number=0;

__thread int ad_comm::time_flag = 0;
__thread int ad_comm::bandwidth = 0;
__thread int ad_comm::print_hess_and_exit_flag = 0;
__thread int ad_comm::no_pvm_flag = 0;
__thread int ad_comm::no_atlas_flag = 0;
__thread int ad_comm::no_ln_det_choleski_flag = 0;
__thread adtimer* ad_comm::ptm = nullptr;
__thread adtimer* ad_comm::ptm1 = nullptr;
__thread adpvm_manager* ad_comm::pvm_manager = nullptr;
__thread adpthreads_manager* ad_comm::pthreads_manager = nullptr;
__thread adstring* ad_comm::subdir = nullptr;
__thread cifstream* ad_comm::global_datafile = nullptr;
__thread cifstream* ad_comm::global_parfile = nullptr;
__thread ofstream* ad_comm::global_savefile = nullptr;
__thread ofstream* ad_comm::global_logfile = nullptr;
__thread uostream* ad_comm::global_bsavefile = nullptr;
__thread uistream* ad_comm::global_bparfile = nullptr;
__thread adstring* ad_comm::adprogram_name;
__thread adstring* ad_comm::working_directory_path;
__thread char ad_comm::option_flags[10];
__thread unsigned int ad_comm::wd_flag = 0;
__thread unsigned char ad_comm::directory_prefix = '\\';
__thread int ad_comm::argc = 0;
__thread char** ad_comm::argv = nullptr;
