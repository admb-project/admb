#include <iostream>
#include <vector>
#include <thread>
using std::vector;
using std::thread;

#include <gtest/gtest.h>

#define main simple
#include <simple.cpp>
#undef main

class tests_threaded: public ::testing::Test 
{
protected:
  tests_threaded() {
  }
  virtual ~tests_threaded() {
  }
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
public:
  static __thread int line;
  static __thread dvariable* variable;
};
__thread int tests_threaded::line = -1;
__thread dvariable* tests_threaded::variable = nullptr;

int simple(int argc, char* argv[]);
void hello_world()
{
}
TEST(tests_threaded, hello_world)
{
  std::thread t(hello_world);
  t.join();
}
TEST(tests_threaded, simple_hess_routine_threaded)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 20;
  std::thread t[n];
  for (int i = 0; i < n; i++)
  {
    t[i] = std::thread([](){
      ASSERT_EQ(-1, tests_threaded::line);
      ASSERT_EQ(nullptr, tests_threaded::variable);
      tests_threaded::line = 2;
    });
  }
  for (int i = 0; i < n; i++)
  {
    t[i].join();
  }
}
TEST(tests_threaded, dlink_constructor_destructor)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

  dlink link;
  ASSERT_EQ(link.previous(), nullptr);
}
TEST(tests_threaded, dlist_create)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

  dlist lst;

  dlink* lstlink = lst.create();
  if (lstlink == nullptr)
  {
    FAIL(); 
  }
  ASSERT_EQ(lst.check_list(), 0);
}
TEST(tests_threaded, dlist_append)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

  dlist lst;

  dlink* lstlink = lst.create();
  if (lstlink == nullptr)
  {
    FAIL(); 
  }
  ASSERT_EQ(lst.check_list(), 0);

  dlink link;
  lst.append(&link);
  ASSERT_EQ(lst.check_list(), 1);
}
double_and_int* gradnew();
void gradfree(dlink* v);
TEST(tests_threaded, gradnew)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

  ASSERT_EQ(gradient_structure::GRAD_LIST, nullptr);

  initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;
  model_parameters mp(arrmblsize,argc,argv);


  ASSERT_NE(gradient_structure::GRAD_LIST, nullptr);

  dlink* link = gradient_structure::GRAD_LIST->create();
  ASSERT_NE(link, nullptr);
  ASSERT_EQ(link->previous(), nullptr);
  ASSERT_EQ(gradient_structure::GRAD_LIST->check_list(), 0);

  gradfree(link);
  ASSERT_NE(link, nullptr);
  //link was appended to the grad_list
  ASSERT_EQ(gradient_structure::GRAD_LIST->check_list(), 1);
  ASSERT_EQ(link->previous(), nullptr);

  dlink* link2 = gradient_structure::GRAD_LIST->create();
  gradfree(link2);
  ASSERT_EQ(gradient_structure::GRAD_LIST->check_list(), 2);
  //insert after the head
  ASSERT_NE(link2->previous(), nullptr);
  ASSERT_EQ(link->previous(), nullptr);

  double_and_int* di = gradnew();
  ASSERT_NE(di, nullptr);
  ASSERT_EQ(gradient_structure::GRAD_LIST->check_list(), 1);
  //pull node after head
  ASSERT_EQ((dlink*)di, link2);

  double_and_int* di2 = gradnew();
  ASSERT_NE(di2, nullptr);
  ASSERT_EQ(gradient_structure::GRAD_LIST->check_list(), 0);
  ASSERT_EQ((dlink*)di2, link);

  delete initial_params::varsptr;
  initial_params::varsptr = nullptr;
}
TEST(tests_threaded, dvariable)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);

  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;
  model_parameters mp(arrmblsize,argc,argv);

  dvariable variable;

  delete initial_params::varsptr;
  initial_params::varsptr = nullptr;
}
TEST(tests_threaded, threaded_ad_comm_constructor)
{
  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };

  const int n = 10;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(0, ad_comm::time_flag);
      ASSERT_EQ(0, ad_comm::bandwidth);
      ASSERT_EQ(0, ad_comm::print_hess_and_exit_flag);
      ASSERT_EQ(0, ad_comm::no_pvm_flag);
      ASSERT_EQ(0, ad_comm::no_atlas_flag);
      ASSERT_EQ(0, ad_comm::no_ln_det_choleski_flag);
      ASSERT_EQ(nullptr, ad_comm::ptm);
      ASSERT_EQ(nullptr, ad_comm::ptm1);
      ASSERT_EQ(nullptr, ad_comm::pvm_manager);
      ASSERT_EQ(nullptr, ad_comm::pthreads_manager);
      ASSERT_EQ(nullptr, ad_comm::subdir);
      ASSERT_EQ(nullptr, ad_comm::global_datafile);
      ASSERT_EQ(nullptr, ad_comm::global_parfile);
      ASSERT_EQ(nullptr, ad_comm::global_savefile);
      ASSERT_EQ(nullptr, ad_comm::global_logfile);
      ASSERT_EQ(nullptr, ad_comm::global_bsavefile);
      ASSERT_EQ(nullptr, ad_comm::global_bparfile);
      ASSERT_EQ(nullptr, ad_comm::adprogram_name);
      ASSERT_EQ(nullptr, ad_comm::working_directory_path);
      //ASSERT_EQ(ad_comm::option_flags[10];
      ASSERT_EQ(0, ad_comm::wd_flag);
      ASSERT_EQ('\\', ad_comm::directory_prefix);
      ASSERT_EQ(0, ad_comm::argc);
      ASSERT_EQ(nullptr, ad_comm::argv);

      ad_comm ac(argc, argv);

      ASSERT_EQ(0, ad_comm::time_flag);
      ASSERT_EQ(0, ad_comm::bandwidth);
      ASSERT_EQ(0, ad_comm::print_hess_and_exit_flag);
      ASSERT_EQ(0, ad_comm::no_pvm_flag);
      ASSERT_EQ(0, ad_comm::no_atlas_flag);
      ASSERT_EQ(0, ad_comm::no_ln_det_choleski_flag);
      ASSERT_EQ(nullptr, ad_comm::ptm);
      ASSERT_EQ(nullptr, ad_comm::ptm1);
      ASSERT_EQ(nullptr, ad_comm::pvm_manager);
      ASSERT_EQ(nullptr, ad_comm::pthreads_manager);
      ASSERT_EQ(nullptr, ad_comm::subdir);
      ASSERT_NE(nullptr, ad_comm::global_datafile);//<--
      ASSERT_EQ(nullptr, ad_comm::global_parfile);
      ASSERT_EQ(nullptr, ad_comm::global_savefile);
      ASSERT_NE(nullptr, ad_comm::global_logfile);//<--
      ASSERT_EQ(nullptr, ad_comm::global_bsavefile);
      ASSERT_EQ(nullptr, ad_comm::global_bparfile);
      ASSERT_NE(nullptr, ad_comm::adprogram_name);
      ASSERT_EQ(nullptr, ad_comm::working_directory_path);
      //ASSERT_EQ(ad_comm::option_flags[10];
      ASSERT_EQ(0, ad_comm::wd_flag);
      ASSERT_EQ('/', ad_comm::directory_prefix);//<--
      ASSERT_EQ(1, ad_comm::argc);//<--
      ASSERT_NE(nullptr, ad_comm::argv);//<--
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }

  ASSERT_EQ(0, ad_comm::time_flag);
  ASSERT_EQ(0, ad_comm::bandwidth);
  ASSERT_EQ(0, ad_comm::print_hess_and_exit_flag);
  ASSERT_EQ(0, ad_comm::no_pvm_flag);
  ASSERT_EQ(0, ad_comm::no_atlas_flag);
  ASSERT_EQ(0, ad_comm::no_ln_det_choleski_flag);
  ASSERT_EQ(nullptr, ad_comm::ptm);
  ASSERT_EQ(nullptr, ad_comm::ptm1);
  ASSERT_EQ(nullptr, ad_comm::pvm_manager);
  ASSERT_EQ(nullptr, ad_comm::pthreads_manager);
  ASSERT_EQ(nullptr, ad_comm::subdir);
  ASSERT_EQ(nullptr, ad_comm::global_datafile);
  ASSERT_EQ(nullptr, ad_comm::global_parfile);
  ASSERT_EQ(nullptr, ad_comm::global_savefile);
  ASSERT_EQ(nullptr, ad_comm::global_logfile);
  ASSERT_EQ(nullptr, ad_comm::global_bsavefile);
  ASSERT_EQ(nullptr, ad_comm::global_bparfile);
  ASSERT_EQ(nullptr, ad_comm::adprogram_name);
  ASSERT_EQ(nullptr, ad_comm::working_directory_path);
  //ASSERT_EQ(ad_comm::option_flags[10];
  ASSERT_EQ(0, ad_comm::wd_flag);
  ASSERT_EQ('/', ad_comm::directory_prefix);
  ASSERT_EQ(0, ad_comm::argc);
  ASSERT_EQ(nullptr, ad_comm::argv);
}
TEST(tests_threaded, threaded_gradient_structure_constructor)
{
  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };

  const int n = 10;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(4000000L, gradient_structure::GRADSTACK_BUFFER_SIZE);
      ASSERT_EQ(140000000L, gradient_structure::CMPDIF_BUFFER_SIZE);
      ASSERT_EQ(0, gradient_structure::instances);
      ASSERT_EQ(nullptr, gradient_structure::fp);
      ASSERT_EQ(nullptr, gradient_structure::GRAD_LIST);
      ASSERT_EQ(0, gradient_structure::save_var_flag);
      ASSERT_EQ(0, gradient_structure::save_var_file_flag);
      ASSERT_EQ(5000, gradient_structure::MAX_DLINKS);
      ASSERT_EQ(2000, gradient_structure::NUM_DEPENDENT_VARIABLES);
      ASSERT_EQ(0, gradient_structure::NVAR);
      ASSERT_EQ(0, gradient_structure::TOTAL_BYTES);
      ASSERT_EQ(0, gradient_structure::PREVIOUS_TOTAL_BYTES);
      ASSERT_EQ(0, gradient_structure::USE_FOR_HESSIAN);
      ASSERT_EQ(25, gradient_structure::NUM_RETURN_ARRAYS);
      ASSERT_EQ(0L, gradient_structure::ARRAY_MEMBLOCK_SIZE);
      ASSERT_EQ(5000, gradient_structure::MAX_NVAR_OFFSET);
      ASSERT_EQ(70, gradient_structure::RETURN_ARRAYS_SIZE);
      ASSERT_EQ(0, gradient_structure::max_last_offset);
      ASSERT_EQ(0, gradient_structure::Hybrid_bounded_flag);
      ASSERT_EQ(nullptr, gradient_structure::RETURN_ARRAYS);
      ASSERT_EQ(nullptr, gradient_structure::RETURN_PTR_CONTAINER);
      ASSERT_EQ(nullptr, gradient_structure::ARRAY_MEMBLOCK_BASE);
      ASSERT_EQ(nullptr, gradient_structure::ARRAY_MEMBLOCK_BASEA);
      ASSERT_EQ(nullptr, gradient_structure::ARRAY_MEMBLOCK_SAVE);
      ASSERT_EQ(nullptr, gradient_structure::variables_save);
      ASSERT_EQ(nullptr, gradient_structure::INDVAR_LIST);
      ASSERT_EQ(nullptr, gradient_structure::DEPVARS_INFO);
      ASSERT_EQ(nullptr, gradient_structure::hessian_ptr);
      ASSERT_EQ(nullptr, gradient_structure::GRAD_STACK1);
      ASSERT_EQ(nullptr, gradient_structure::RETURN_PTR);
      ASSERT_EQ(nullptr, gradient_structure::MIN_RETURN);
      ASSERT_EQ(nullptr, gradient_structure::MAX_RETURN);
      ASSERT_EQ(nullptr, gradient_structure::ARR_LIST1);
      ASSERT_EQ(nullptr, gradient_structure::ARR_FREE_LIST1);
      ASSERT_EQ(0, gradient_structure::no_derivatives);
      ASSERT_EQ(0, gradient_structure::RETURN_ARRAYS_PTR);

      ad_comm ac(argc, argv);
      gradient_structure gs;

      ASSERT_EQ(4000000L, gradient_structure::GRADSTACK_BUFFER_SIZE);
      ASSERT_EQ(140000000L, gradient_structure::CMPDIF_BUFFER_SIZE);
      ASSERT_EQ(1, gradient_structure::instances);
      ASSERT_NE(nullptr, gradient_structure::fp);
      ASSERT_NE(nullptr, gradient_structure::GRAD_LIST);
      ASSERT_EQ(0, gradient_structure::save_var_flag);
      ASSERT_EQ(0, gradient_structure::save_var_file_flag);
      ASSERT_EQ(5000, gradient_structure::MAX_DLINKS);
      ASSERT_EQ(2000, gradient_structure::NUM_DEPENDENT_VARIABLES);
      ASSERT_EQ(0, gradient_structure::NVAR);
      ASSERT_EQ(0, gradient_structure::TOTAL_BYTES);
      ASSERT_EQ(0, gradient_structure::PREVIOUS_TOTAL_BYTES);
      ASSERT_EQ(0, gradient_structure::USE_FOR_HESSIAN);
      ASSERT_EQ(25, gradient_structure::NUM_RETURN_ARRAYS);
      ASSERT_EQ(100000L, gradient_structure::ARRAY_MEMBLOCK_SIZE);
      ASSERT_EQ(5000, gradient_structure::MAX_NVAR_OFFSET);
      ASSERT_EQ(70, gradient_structure::RETURN_ARRAYS_SIZE);
      ASSERT_EQ(0, gradient_structure::max_last_offset);
      ASSERT_EQ(0, gradient_structure::Hybrid_bounded_flag);
      ASSERT_NE(nullptr, gradient_structure::RETURN_ARRAYS);
      ASSERT_NE(nullptr, gradient_structure::RETURN_PTR_CONTAINER);
      ASSERT_NE(nullptr, gradient_structure::ARRAY_MEMBLOCK_BASE);
      ASSERT_EQ(nullptr, gradient_structure::ARRAY_MEMBLOCK_BASEA);
      ASSERT_EQ(nullptr, gradient_structure::ARRAY_MEMBLOCK_SAVE);
      ASSERT_EQ(nullptr, gradient_structure::variables_save);
      ASSERT_NE(nullptr, gradient_structure::INDVAR_LIST);
      ASSERT_NE(nullptr, gradient_structure::DEPVARS_INFO);
      ASSERT_NE(nullptr, gradient_structure::hessian_ptr);
      ASSERT_NE(nullptr, gradient_structure::GRAD_STACK1);
      ASSERT_NE(nullptr, gradient_structure::RETURN_PTR);
      ASSERT_NE(nullptr, gradient_structure::MIN_RETURN);
      ASSERT_NE(nullptr, gradient_structure::MAX_RETURN);
      ASSERT_NE(nullptr, gradient_structure::ARR_LIST1);
      ASSERT_EQ(nullptr, gradient_structure::ARR_FREE_LIST1);
      ASSERT_EQ(0, gradient_structure::no_derivatives);
      ASSERT_EQ(0, gradient_structure::RETURN_ARRAYS_PTR);
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
}
TEST(tests_threaded, threaded_function_minimizer_constructor)
{
  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };

  const int n = 1;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(0, function_minimizer::bad_step_flag);
      ASSERT_EQ(0, function_minimizer::likeprof_flag);
      ASSERT_EQ(0, function_minimizer::first_hessian_flag);
      ASSERT_EQ(0, function_minimizer::test_trust_flag);
      ASSERT_EQ(0, function_minimizer::random_effects_flag);
      ASSERT_EQ(0, function_minimizer::negative_eigenvalue_flag);
      ASSERT_EQ(0, function_minimizer::inner_opt_flag);
      ASSERT_EQ(nullptr, function_minimizer::ph);
      ASSERT_EQ(nullptr, function_minimizer::pg);
      ASSERT_EQ(nullptr, function_minimizer::convergence_criteria);
      ASSERT_EQ(nullptr, function_minimizer::maximum_function_evaluations);
      ASSERT_EQ(0, function_minimizer::sd_flag);
      ASSERT_EQ(nullptr, function_minimizer::user_data_file);
      ASSERT_EQ(nullptr, function_minimizer::user_par_file);
      ASSERT_EQ(0, function_minimizer::have_constraints);
      ASSERT_EQ(0, function_minimizer::constraint_exit_number);

      ad_comm ac(argc, argv);
      function_minimizer fm;

      ASSERT_EQ(0, function_minimizer::bad_step_flag);
      ASSERT_EQ(0, function_minimizer::likeprof_flag);
      ASSERT_EQ(0, function_minimizer::first_hessian_flag);
      ASSERT_EQ(0, function_minimizer::test_trust_flag);
      ASSERT_EQ(0, function_minimizer::random_effects_flag);
      ASSERT_EQ(0, function_minimizer::negative_eigenvalue_flag);
      ASSERT_EQ(0, function_minimizer::inner_opt_flag);
      ASSERT_EQ(nullptr, function_minimizer::ph);
      ASSERT_EQ(nullptr, function_minimizer::pg);
      ASSERT_EQ(nullptr, function_minimizer::convergence_criteria);
      ASSERT_EQ(nullptr, function_minimizer::maximum_function_evaluations);
      ASSERT_EQ(0, function_minimizer::sd_flag);
      ASSERT_EQ(nullptr, function_minimizer::user_data_file);
      ASSERT_EQ(nullptr, function_minimizer::user_par_file);
      ASSERT_EQ(0, function_minimizer::have_constraints);
      ASSERT_EQ(0, function_minimizer::constraint_exit_number);
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
}
TEST(tests_threaded, threaded_model_parameters_constructor)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 10;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);

      model_parameters mp(arrmblsize,argc,argv);
      ASSERT_NE(nullptr, initial_params::varsptr);

      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
TEST(tests_threaded, threaded_model_parameters_preliminary_calculations)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 10;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);

      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      ASSERT_NE(nullptr, initial_params::varsptr);

      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
TEST(tests_threaded, threaded_model_parameters_nvarcalc)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 10;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      ASSERT_EQ(0, initial_params::straight_through_flag);
      ASSERT_EQ(0, initial_params::num_initial_params);
      ASSERT_EQ(250, initial_params::max_num_initial_params);
      ASSERT_EQ(1, initial_params::max_number_phases);
      ASSERT_EQ(1, initial_params::current_phase);
      ASSERT_EQ(0, initial_params::restart_phase);
      ASSERT_EQ(0, initial_params::sd_phase);
      ASSERT_EQ(0, initial_params::mc_phase);
      ASSERT_EQ(0, initial_params::mceval_phase);
      ASSERT_EQ(0, initial_params::num_active_initial_params);

      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      ASSERT_EQ(2, initial_params::nvarcalc());

      ASSERT_EQ(0, initial_params::straight_through_flag);
      ASSERT_EQ(0, initial_params::straight_through_flag);
      ASSERT_EQ(2, initial_params::num_initial_params);
      ASSERT_EQ(250, initial_params::max_num_initial_params);
      ASSERT_EQ(1, initial_params::max_number_phases);
      ASSERT_EQ(1, initial_params::current_phase);
      ASSERT_EQ(0, initial_params::restart_phase);
      ASSERT_EQ(0, initial_params::sd_phase);
      ASSERT_EQ(0, initial_params::mc_phase);
      ASSERT_EQ(0, initial_params::mceval_phase);
      ASSERT_EQ(0, initial_params::num_active_initial_params);

      ASSERT_NE(nullptr, initial_params::varsptr);
      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;

    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
TEST(tests_threaded, threaded_model_parameters_xinit)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 10;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);

      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();

      const int nvar = initial_params::nvarcalc();

      independent_variables x(1, nvar);
      initial_params::xinit(x);

      ASSERT_NE(nullptr, initial_params::varsptr);

      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
TEST(tests_threaded, threaded_model_parameters_computations_nohess)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 2;
  char* argv[] = { (char*)"simple/simple", "-nohess" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 10;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      mp.computations(argc,argv);

      ASSERT_NE(nullptr, initial_params::varsptr);
      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;

    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
TEST(tests_threaded, threaded_model_parameters_computations)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 1;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      mp.computations(argc, argv);
      ASSERT_NE(nullptr, initial_params::varsptr);
      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
TEST(tests_threaded, threaded_model_parameters_computations_void)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 10;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      mp.computations();
      ASSERT_NE(nullptr, initial_params::varsptr);
      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
void ludcmp_det(const dmatrix& _a, const ivector& _indx, const double& _d);
TEST(tests_threaded, ludcmp_det)
{
  dmatrix a(1, 2, 1, 2);
  a(1, 1) = 102.797;
  a(1, 2) = 17.5507;
  a(2, 1) = 17.5507; 
  a(2, 2) = 5.0145;
 
  ivector indx(1, 2);
  indx(1) = -132446344;
  indx(2) = 53;
 
  double d = 0;
  ludcmp_det(a, indx, d);
}
TEST(tests_threaded, threaded_model_parameters_computations1)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 1;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      mp.computations1(argc, argv);
      ASSERT_NE(nullptr, initial_params::varsptr);
      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
TEST(tests_threaded, simple_hess_routine_noparallel)
{
  int argc = 1;
  char* argv[] = { "simple/simple" };
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  if (!arrmblsize) arrmblsize=15000000;

  initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);

  model_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;
  mp.preliminary_calculations();
  mp.hess_routine_noparallel();

  delete initial_params::varsptr;
  initial_params::varsptr = nullptr;
}
TEST(tests_threaded, simple_hess_routine)
{
  int argc = 1;
  char* argv[] = { "simple/simple" };
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
  if (!arrmblsize) arrmblsize=15000000;

  initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);

  model_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;
  mp.preliminary_calculations();
  mp.hess_routine();

  delete initial_params::varsptr;
  initial_params::varsptr = nullptr;
}
TEST(tests_threaded, threaded_model_parameters_hess_routine_noparallel)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 10;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      //mp.computations(argc, argv);
      mp.hess_routine_noparallel();
      ASSERT_NE(nullptr, initial_params::varsptr);
      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
TEST(tests_threaded, threaded_model_parameters_hess_routine)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 10;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      //mp.computations(argc, argv);
      mp.hess_routine();
      ASSERT_NE(nullptr, initial_params::varsptr);
      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
TEST(tests_threaded, simple)
{
  initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
  char* argv[] = { "simple/simple" };
  simple(1, argv);
  delete initial_params::varsptr;
  initial_params::varsptr = nullptr;
}
TEST(tests_threaded, simple_computations)
{
  int argc = 1;
  char* argv[] = { "simple/simple" };
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

  initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);

  if (!arrmblsize) arrmblsize=15000000;
  model_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;
  mp.preliminary_calculations();
  mp.computations(argc,argv);

  delete initial_params::varsptr;
  initial_params::varsptr = nullptr;
}
TEST(tests_threaded, simple_computations1)
{
  int argc = 1;
  char* argv[] = { "simple/simple" };
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

  initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);

  if (!arrmblsize) arrmblsize=15000000;
  model_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;
  mp.preliminary_calculations();
  mp.computations1(argc,argv);

  delete initial_params::varsptr;
  initial_params::varsptr = nullptr;
}
TEST(tests_threaded, simple_hess_inv)
{
  int argc = 1;
  char* argv[] = { "simple/simple" };
  ad_set_new_handler();
  ad_exit=&ad_boundf;
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

  initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);

  if (!arrmblsize) arrmblsize=15000000;
  model_parameters mp(arrmblsize,argc,argv);
  mp.iprint=10;
  mp.preliminary_calculations();
  mp.minimize();
  mp.hess_routine_noparallel();
  mp.depvars_routine();
  mp.hess_inv();

  delete initial_params::varsptr;
  initial_params::varsptr = nullptr;
}
TEST(tests_threaded, threaded_model_parameters_hess_inv)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 1;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      mp.minimize();
      mp.hess_routine_noparallel();
      mp.depvars_routine();
      mp.hess_inv();
      ASSERT_NE(nullptr, initial_params::varsptr);
      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
TEST(tests_threaded, threaded_model_parameters_hess_inv10)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 2;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      mp.minimize();
      mp.hess_routine_noparallel();
      mp.depvars_routine();
      mp.hess_inv();
      ASSERT_NE(nullptr, initial_params::varsptr);
      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
TEST(tests_threaded, threaded_objective_function_value)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 2;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){

      ASSERT_EQ(nullptr, objective_function_value::pobjfun);
      ASSERT_EQ(0, objective_function_value::fun_without_pen);
      ASSERT_EQ(0, objective_function_value::gmax);

      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      mp.computations1(argc, argv);

      ASSERT_NE(nullptr, objective_function_value::pobjfun);
      ASSERT_EQ(0, objective_function_value::fun_without_pen);
      ASSERT_NE(0, objective_function_value::gmax);

      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
}
TEST(tests_threaded, threaded_pre_userfunction)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 2;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){

      ASSERT_EQ(nullptr, objective_function_value::pobjfun);
      ASSERT_EQ(0, objective_function_value::fun_without_pen);
      ASSERT_EQ(0, objective_function_value::gmax);

      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();

      const int nvar = initial_params::nvarcalc();
      independent_variables x(1,nvar);
      initial_params::xinit(x);
      dvector g(1, nvar);
      g.initialize();

      dvariable vf = initial_params::reset(dvar_vector(x));
      *objective_function_value::pobjfun = 0.0;
      mp.pre_userfunction();
      double f = value(vf);
      gradcalc(nvar,g);

      ASSERT_NE(nullptr, objective_function_value::pobjfun);
      ASSERT_EQ(0, objective_function_value::fun_without_pen);
      ASSERT_EQ(0, objective_function_value::gmax);

      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
}
TEST(tests_threaded, threaded_static_likeprof_params)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 1;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){

      //ASSERT_EQ(nullptr, *likeprof_params::likeprofptr);
      ASSERT_EQ(0, likeprof_params::num_likeprof_params);

      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      mp.computations(argc,argv);

      ASSERT_EQ(0, likeprof_params::num_likeprof_params);
      //ASSERT_EQ(nullptr, *likeprof_params::likeprofptr);

      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
}
TEST(tests_threaded, threaded_static_stddev_params)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 1;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){

      //ASSERT_EQ(nullptr, stddev_params::stddev_number_ptr);
      //ASSERT_EQ(nullptr, stddev_params::stddevptr);
      ASSERT_EQ(0, stddev_params::num_stddev_params);
      ASSERT_EQ(0, stddev_params::num_stddev_number_params);

      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      mp.computations(argc,argv);

      //ASSERT_EQ(nullptr, stddev_params::stddev_number_ptr);
      //ASSERT_EQ(nullptr, stddev_params::stddevptr);
      ASSERT_EQ(0, stddev_params::num_stddev_params);
      ASSERT_EQ(0, stddev_params::num_stddev_number_params);

      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
}
TEST(tests_threaded, threaded_static_xpool)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  //int argc = 1;
  //char* argv[] = { (char*)"simple/simple" };
  int argc = 2;
  char* argv[] = { (char*)"simple/simple", "-nohess" };
  if (!arrmblsize) arrmblsize=15000000;

  const int n = 10;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, vector_shape::xpool);
      //ASSERT_EQ(nullptr, ts_vector_shapex::xpool);
      ASSERT_EQ(nullptr, vector_shapex::xpool);
      ASSERT_EQ(nullptr, arr_link::xpool);

      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      model_parameters mp(arrmblsize,argc,argv);
      mp.iprint=10;
      mp.preliminary_calculations();
      mp.computations(argc,argv);

      ASSERT_NE(nullptr, vector_shape::xpool);
      //ASSERT_EQ(nullptr, ts_vector_shapex::xpool);
      ASSERT_NE(nullptr, vector_shapex::xpool);
      ASSERT_NE(nullptr, arr_link::xpool);

      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
}
TEST(tests_threaded, threaded_simple_nohess)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 2;
  char* argv[] = { (char*)"simple/simple", "-nohess" };

  const int n = 10;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      simple(argc, argv);
      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
TEST(tests_threaded, threaded_simple)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  int argc = 1;
  char* argv[] = { (char*)"simple/simple" };

  const int n = 10;
  vector<thread> threads;
  for (int i = 0; i < n; i++)
  {
    threads.push_back(thread([&argc, &argv](){
      ASSERT_EQ(nullptr, initial_params::varsptr);
      gradient_structure::set_NO_DERIVATIVES();
      gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
      initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
      simple(argc, argv);
      delete initial_params::varsptr;
      initial_params::varsptr = nullptr;
    }));
  }
  for (auto& thread: threads)
  {
    thread.join();
  }
  ASSERT_EQ(nullptr, initial_params::varsptr);
}
TEST(tests_threaded, simple5)
{
  char* argv[] = { "simple/simple" };
  for (int i = 0; i < 5; i++)
  {
    initial_params::varsptr = new adlist_ptr(initial_params::max_num_initial_params);
    simple(1, argv);
    delete initial_params::varsptr;
    initial_params::varsptr = nullptr;
  }
}
int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
