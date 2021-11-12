#include "model_parameters.h"
#include "sdv.h"

int main(int argc,char * argv[])
{
#ifdef DEBUG
  auto start = std::chrono::high_resolution_clock::now();
  #ifndef __SUNPRO_C
    std::feclearexcept(FE_ALL_EXCEPT);
  #endif
#endif

  ad_set_new_handler();
  ad_exit=&ad_boundf;

  long int arrmblsize = 4000000L;
  gradient_structure::set_GRADSTACK_BUFFER_SIZE(300000);
  gradient_structure::set_CMPDIF_BUFFER_SIZE(20000);
  gradient_structure::set_MAX_NVAR_OFFSET(50850);
  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

  if (!arrmblsize) arrmblsize=150000;
  df1b2variable::noallocate=1;
  df1b2variable::pool = new adpool();
  initial_df1b2params::varsptr = new P_INITIAL_DF1B2PARAMS[1000];
  {
    model_parameters mp(arrmblsize,argc,argv);
    df1b2_parameters model;
    mp.model = &model;

    mp.iprint=10;

    function_minimizer::random_effects_flag=1;
    df1b2variable::noallocate=0;
    mp.preliminary_calculations();
    initial_df1b2params::separable_flag=1;
    mp.computations(argc,argv);
  }
  delete [] init_df1b2variable::list;
  init_df1b2variable::list = NULL;
  delete [] initial_df1b2params::varsptr;
  initial_df1b2params::varsptr = NULL;
  delete df1b2variable::pool;
  df1b2variable::pool = NULL;

#ifdef DEBUG
  std::cout << endl << argv[0] << " elapsed time is " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() << " microseconds." << endl;
  #ifndef __SUNPRO_C
  bool failedtest = false;
  if (std::fetestexcept(FE_DIVBYZERO))
    { cerr << "Error: Detected division by zero." << endl; failedtest = true; }
  if (std::fetestexcept(FE_INVALID))
    { cerr << "Error: Detected invalid argument." << endl; failedtest = true; }
  if (std::fetestexcept(FE_OVERFLOW))
    { cerr << "Error: Detected overflow." << endl; failedtest = true; }
  if (std::fetestexcept(FE_UNDERFLOW))
    { cerr << "Error: Detected underflow." << endl; }
  if (failedtest) { std::abort(); } 
  #endif
#endif

    return 0;
}
