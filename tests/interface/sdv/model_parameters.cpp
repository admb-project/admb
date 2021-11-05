
#include "model_parameters.h"

model_parameters* model_parameters::model_parameters_ptr = nullptr;

model_parameters::model_parameters(int sz,int argc,char * argv[]):
 ad_comm(argc,argv) , function_minimizer(sz)
{
  adstring tmpstring;
  tmpstring=adprogram_name + adstring(".dat");
  if (argc > 1)
  {
    int on=0;
    if ( (on=option_match(argc,argv,"-ind"))>-1)
    {
      if (on>argc-2 || argv[on+1][0] == '-')
      {
        cerr << "Invalid input data command line option"
                " -- ignored" << endl;
      }
      else
      {
        tmpstring = adstring(argv[on+1]);
      }
    }
  }
  global_datafile = new cifstream(tmpstring);
  if (!global_datafile)
  {
    cerr << "Error: Unable to allocate global_datafile in model_data constructor.";
    ad_exit(1);
  }
  if (!(*global_datafile))
  {
    delete global_datafile;
    global_datafile=NULL;
  }
  /*
  if (global_datafile)
  {
    delete global_datafile;
    global_datafile = NULL;
  }
  */
  model_parameters_ptr=this;
  initializationfunction();
}


void model_parameters::report(const dvector& gradients)
{
 adstring ad_tmp=initial_params::get_reportfile_name();
  ofstream report((char*)(adprogram_name + ad_tmp));
  if (!report)
  {
    cerr << "error trying to open report file"  << adprogram_name << ".rep";
    return;
  }
}

void model_parameters::preliminary_calculations(void)
{

  #if defined(USE_ADPVM)

  admaster_slave_variable_interface(*this);

  #endif
  cout << setprecision(4);
}

extern "C"  {
  void ad_boundf(int i)
  {
    /* so we can stop here */
    exit(i);
  }
}

void model_parameters::begin_df1b2_funnel(void)
{
  if (lapprox)
  {
    {
      begin_funnel_stuff();
    }
  }
}

void model_parameters::end_df1b2_funnel(void)
{
  if (lapprox)
  {
    end_df1b2_funnel_stuff();
  }
}

void model_parameters::setup_quadprior_calcs(void)
{
  df1b2_gradlist::set_no_derivatives();
  quadratic_prior::in_qp_calculations=1;
}

void model_parameters::begin_df1b2_funnel2(void)
{
  (*re_objective_function_value::pobjfun)=0;
  other_separable_stuff_begin();
  f1b2gradlist->reset();
  if (!quadratic_prior::in_qp_calculations)
  {
    df1b2_gradlist::set_yes_derivatives();
  }
  funnel_init_var::allocate_all();
}

void model_parameters::end_df1b2_funnel2(void)
{
  lapprox->do_separable_stuff();
  other_separable_stuff_end();
  funnel_init_var::deallocate_all();
}
