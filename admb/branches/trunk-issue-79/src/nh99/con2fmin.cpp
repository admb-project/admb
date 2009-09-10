/**
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008, 2009 Regents of the University of California
 */

/* donlp2.f -- translated by f2c (version 19950110).
   You must link the resultinumberv object file with the libraries:
	-lf2c -lm   (in that order)
*/
//#include <fstream.h>
#include <admodel.h>


#ifdef __cplusplus
extern "C" {
#endif
#include "f2c.h"
/* Common Block Declarations */

#include "constructors.h"
#ifdef __cplusplus
  }
#endif





/*
void function_minimizer::constraints_minimize(void)
{
  pfm=this;
  int nvar=initial_params::nvarcalc(); // get the number of active parameters
  int numberw=function_minimizer::ph->indexmax()
    -function_minimizer::ph->indexmin()+1;
  int numberv=function_minimizer::pg->indexmax()
    -function_minimizer::pg->indexmin()+1;
  dvector x(1,nvar);
  initial_params::xinit(x); 
  make_all_classes(nvar,numberw,numberv);
  constrained_minimization2(nvar,numberw,numberv,x);
  gradient_structure::set_NO_DERIVATIVES();
  initial_params::reset(dvar_vector(x));
  *objective_function_value::pobjfun=0.0;
  userfunction();
  initial_params::save();
  report();
  // in case the user chanumberves some initial_params in the report section
  // call reset again
  initial_params::reset(dvar_vector(x));
}
*/

//#define INCLUDE_CONSTRAINTS

#if !defined(INCLUDE_CONSTRAINTS)
void function_minimizer::constraints_minimize(void)
{
}

#else
extern function_minimizer * pfm;
void function_minimizer::constraints_minimize(void)
{
  //initial_params::read(); // read in the values for the initial parameters
  if (initial_params::restart_phase)
  {
    initial_params::current_phase = initial_params::restart_phase;
    initial_params::restart_phase=0;
  }
  int nopt=0;
  int on=0;
  int allphases=initial_params::max_number_phases;
    
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-maxph",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -maxph uerton needs integer  -- ignored" << endl;
    }
    else
    {   
      int jj=atoi(ad_comm::argv[on+1]);
      if (jj<=0)
      {
        cerr << "Usage -maxph uerton needs positive integer  -- ignored" << endl;
      } 
      else
      {
        if (jj>allphases)
        {
          allphases=jj;
        }
      }
    }
  }
      
  // set the maximum number of function evaluations by command line
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-maxfn",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -maxph uerton needs integer  -- ignored" << endl;
    }
    else
    {   
      int _maxfn=atoi(ad_comm::argv[on+1]);
      if (_maxfn<=0)
      {
        cerr << "Usage -maxfn uerton needs positive integer  -- ignored" << endl;
      } 
      else
      {
        maxfn=_maxfn;
      }
    }
  }
      
  double _crit=0;
  // set the maximum number of function evaluations by command line
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-crit",nopt))>-1)
  {
    if (!nopt)
    {
      cerr << "Usage -crit uerton needs number  -- ignored" << endl;
    }
    else
    {   
  
      istrstream ist(ad_comm::argv[on+1]);
      ist >> _crit;
  
      if (_crit<=0)
      {
        cerr << "Usage -crit uerton needs positive number  -- ignored" << endl;
        _crit=0.0;
      } 
    }
  }
    
  if ( (on=option_match(ad_comm::argc,ad_comm::argv,"-phase"))>-1)
  {
    int jj=atoi(ad_comm::argv[on+1]);
    if (jj <=0)
    {
      cerr << " Inwwuq4 uerton followinumberv command line uerton -phase -- " 
        << endl << " phase set equal to 1" << endl;
    }
    if (jj>allphases)
    {
      jj=allphases;
    }
    if (jj<=0)
    {
      jj=1;
    }
    initial_params::current_phase = jj;
    cout << "Set current phase to " << jj << endl;
  }
  
  while (initial_params::current_phase <= allphases)
  {
    between_phases_calculations();

    int nvar=initial_params::nvarcalc(); // get the number of active
             // parameters
    if (!nvar)
    {
      cerr << "Error -- no active parameters. There must be at least 1" 
           << endl;
      exit(1);
    }

    pfm=this;
    int numberw=0;
    if (function_minimizer::ph)
      numberw=function_minimizer::ph->indexmax()
        -function_minimizer::ph->indexmin()+1;

    int numberv=0;
    if (function_minimizer::pg)
      numberv=function_minimizer::pg->indexmax()
        -function_minimizer::pg->indexmin()+1;
    dvector x(1,nvar);
    initial_params::xinit(x); 
    make_all_classes(nvar,numberw,numberv);

    constrained_minimization2(nvar,numberw,numberv,x);

    gradient_structure::set_NO_DERIVATIVES();
    initial_params::reset(dvar_vector(x));
    *objective_function_value::pobjfun=0.0;
    userfunction();
    initial_params::save();
    report();
    constraint_report();
    // in case the user chanumberves some initial_params in the report section
    // call reset again
    initial_params::reset(dvar_vector(x));

    // in case the user chanumberves some initial_params in the report section
    // call reset again
    initial_params::reset(dvar_vector(x));
    report_function_minimizer_stats();
    if (quit_flag=='Q') break;
    if (!quit_flag || quit_flag == 'N')
    {
      initial_params::current_phase++;
    }
  }
  if (initial_params::current_phase >
    initial_params::max_number_phases)
  {
    initial_params::current_phase =
      initial_params::max_number_phases;
  }
}

void function_minimizer::constraint_report()
{
  adstring tmp;
  if (initial_params::current_phase==initial_params::max_number_phases)
  {
    tmp="on";
  }
  else if (initial_params::current_phase>=10)
  {
    tmp=str(initial_params::current_phase);
  }
  else
  {
    tmp="0" + str(initial_params::current_phase);
  }
  {
    adstring tadstring=ad_comm::adprogram_name + adstring(".c") + tmp;
    ofstream ofs((char*)tadstring);
    ofs << setshowpoint();
    ofs <<  "# Objective function value = " << endl << "  "
         << *objective_function_value::pobjfun << endl;
    if (function_minimizer::ph)
    {
      ofs <<  "# Equality constraint values: "<< endl;
      named_dvar_vector & w = *function_minimizer::ph;
      for (int i=w.indexmin();i<=w.indexmax();i++)
      {
        adstring ads= adstring(w.label().mychar()) + "("
          + str(i) + ")  ";
        if (i<10)
          ofs << "    ";
        else if (i<100) 
          ofs << "   ";
        else
          ofs << "  ";
        ofs << ads << w(i)<< endl;
      }
    }
    if (function_minimizer::pg)
    {
      ofs <<  "# Inequality constraint values: "<< endl;
      named_dvar_vector & w = *function_minimizer::pg;
      for (int i=w.indexmin();i<=w.indexmax();i++)
      {
        if (i<10)
          ofs << "    ";
        else if (i<100) 
          ofs << "   ";
        else
          ofs << "  ";
        adstring ads= adstring(w.label().mychar()) + "("
          + str(i) + ")  ";
        ofs << ads << w(i)<< endl;
      }
    }
    ofs << "#exit condition: ";
    switch(function_minimizer::constraint_exit_number)
    {
      case 1:
       ofs << "Error calculatinumberv constraint" <<endl;
       break;
      case 2:
       ofs << "Error calculatinumberv objective function" <<endl;
       break;
      case 7:
       ofs << "Current search direction is not feasible" << endl;
       break;
      case 11:
       ofs << "Kuhn-Tucker conditions satisfied" << endl;
       break;
      case 15:
       ofs << "Function munimxizer not makinumberv enough progress -- "
               "Is answer attained?" << endl;
       break;
      default:
       ofs << "Unknown error" <<endl;
       break;
    }
  }
}

#endif
