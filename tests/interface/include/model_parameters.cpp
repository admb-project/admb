#include "model_parameters.h"

extern "C"  {
  void ad_boundf(int i)
  {
    /* so we can stop here */
    exit(i);
  }
}

model_parameters::model_parameters(int sz, int argc,char * argv[]) :
 ad_comm(argc,argv), function_minimizer(sz)
{
  ad_set_new_handler();
  ad_exit=&ad_boundf;

  gradient_structure::set_NO_DERIVATIVES();
  gradient_structure::set_YES_SAVE_VARIABLES_VALUES();

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

  initializationfunction();

  gradient_structure::set_YES_DERIVATIVES();
}

model_parameters::~model_parameters()
{
  if (global_datafile)
  {
    delete global_datafile;
    global_datafile = NULL;
  }
}
