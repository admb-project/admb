%option noyywrap

%{
  #define   MAX_TMP_STRING 2000
  #define   MAX_USER_CLASSES  450
  #define   MAX_USER_CLASSNAME_LENGTH  181
  #define   MAX_PRIOR_CHECK  1000
  #define   MAX_LIKE_CHECK  2000
  #include <stdlib.h>
  #include <string.h>
  #include <stdio.h>
  #include <ctype.h>
  #if defined(_WIN32)
  #include <io.h>  /* fopen */
  #endif
  char tmp_string[MAX_TMP_STRING];
  char tmp_string1[MAX_TMP_STRING];
  char tmp_string2[MAX_TMP_STRING];
  char tmp_string3[MAX_TMP_STRING];
  char tmp_string4[MAX_TMP_STRING];
  char reference_statements[MAX_USER_CLASSES][MAX_USER_CLASSNAME_LENGTH];
  char class_instances[MAX_USER_CLASSES][MAX_USER_CLASSNAME_LENGTH];
  char outcommand[350];
  char outcommand2[250];
  char outcommand3[250];
  char outcommand3a[250];
  char outcommand3b[250];
  char outcommand4[250];
  char outcommand5[250];
  char outcommand5b[250];
  char outcommand6[250];
  char outcommand7[250];
  char outcommand8[250];
  char * dirpath;
  char infile_name[1000];
  char infile_root[1000];
  char name_string[150];
  char outfile_name[1000];
  char headerfile_name[125];
  char deffile_name[125];
  char headerfile_name2[125];
  int  verbosemode=0;
  int  num_spargs=0;
  int in_objective_function_value_flag=0;
  int  pvmslaves_defined=0;
  int  splus_debug_flag=0;
  int enable_pad = 0;
  int  spnumber_flag=0;
  int random_effects_flag=0;
  int data_defined=0;
  int in_define_data=0;
  int need_prior_globals=0;
  int debug_flag=0;
  int makedll=0;
  int makegaussdll=0;
  int no_userclass=0;
  int bound_flag=0;
  int in_normal_prior_flag=0;
  int num_user_classes=0;
  int have_separable_function=0;
  int final_defined=0;
  int top_of_main_defined=0;
  int globals_section_defined=0;
  int in_define_parameters=0;
  int talk_to_splus=0;
  int initialization_defined=0;
  int objective_function_defined=0;
  int report_defined=0;
  int preliminary_calcs_defined=0;
  int between_phases_defined=0;
  int needs_initialization=0;
  int quadratic_prior_flag=0;
  int quadratic_classprint_flag=0;
  int errcopy=0;
  int params_defined=0;
  int runtime_defined=0;
  int procedure_defined=0;
  int in_procedure_def=0;
  int class_append_flag=0;
  int in_aux_proc=0;
  int in_funnel_proc=0;
  int nline=1;
  int have_likeprof=0;
  int num_paren=0;
  int nchar=0;
  int warn_unallocated=1;
  int have_classcode_tmp=0;

  int priors_defined=0;
  int prior_done_once=0;
  int likelihood_defined=0;
  int likelihood_done_once=0;
  int procedure_done=0;
  int likelihood_done=0;
  int priors_done=0;
  int prior_function_toggle=0;
  char objective_function_name_string[MAX_TMP_STRING];
  char prior_checker[MAX_PRIOR_CHECK][100];//container hold all parameters which being used for check the prior
  int prior_counter=0; //index for prior_checker
  int prior_found=0;
  char likelihood_checker[MAX_LIKE_CHECK][100];
  int likelihood_counter=0; //index for likelihood_checker
  int likelihood_found=0;

  char *  conlist_ptr;
  char conlist[6000];
  char *  classlist_ptr;
  char classlist[6000];
  char *  arglist1_ptr;
  char arglist1[4000];
  char *  arglist_ptr;
  char arglist[4000];
  char uuu_xxx[80]={"Copyright (c) 2008-2012 Regents of the University of California"};
  FILE * fdat=NULL;
  FILE * fdat1=NULL;
  FILE * htop=NULL;
  FILE * fall=NULL;
  FILE * fhead=NULL;
  FILE * fglobals=NULL;
  FILE * ftopmain=NULL;
  FILE * fs=NULL;
  FILE * fs1=NULL;
  void write_getindex_stuff(char *str);
  void initialize(char *);
  char * before_part(char * d, char * s, char c);
  char * before_partb(char * d, char * s, char c);
  char * strict_after_part(char * d, char * s, char c);
  char * after_part(char * d, char * s, char c);
  char * after_partb(char * d, char * s, char c);
  char * strip_leading_blanks(char * d, char * s);
  char * strip_leading_blanks_and_tabs(char * d, char * s);
  void check_random_effects_ordering(void);
  int count_paren(int num_paren,char * yytext);
  void add_references_to_user_classes(FILE * fall);
  void write_funnel_end(void);
  void call_destructors_for_user_classes(FILE * fall);
  void marker(void);
  void write_unallocated(const char *);
  void print_quadratic_random_effect_penalty_class(char *text);

  void add_prior_to_objective(void);
  void add_likelihood_to_objective(void);
  void setup_for_prior_likelihood(void);
  void trim(char * a);
  int prior_check(char * parameter, char * prior);

%}

filename \"[^\"]*\"

filenamesingle \'[^\']*\'

name [a-z_A-Z]+(->)?[a-z_A-Z0-9]*

num_exp [a-z_A-Z0-9\+\-\*\/]+

index ([a-z_A-Z]+(->)?[a-z_A-Z0-9]*)|([a-z_A-Z0-9\+\-\*\/]+)

float_num_exp [a-z_A-Z0-9\.\+\-\*]+

prior_name [ \t(a-z_A-Z]+(->)?[ \ta-z_A-Z0-9(),.-]*
prior_def [ \t(a-z_A-Z0-9-]+(->)?[ \ta-z_A-Z0-9),.-]*

%s DEFINE_DATA DEFINE_PARAMETERS DEFINE_PROCS IN_DATA_DEF IN_PARAM_DEF
%s IN_NUMBER_DEF IN_SPNUMBER_DEF IN_VECTOR_DEF IN_VECTOR_VECTOR_DEF
%s IN_SPVECTOR_DEF
%s IN_MATRIX_DEF IN_TABLE_DEF IN_SPMATRIX_DEF IN_THREE_ARRAY_DEF IN_SPTHREE_ARRAY_DEF
%s IN_NAMED_NUMBER_DEF IN_NAMED_VECTOR_DEF IN_NAMED_MATRIX_DEF
%s IN_NAMED_THREE_ARRAY_DEF IN_NAMED_FOUR_ARRAY_DEF DEFINE_AUX_PROC
%s INIT_BOUNDED_NUMBER_DEF INIT_BOUNDED_VECTOR_DEF IN_BOUNDED_MATRIX_DEF
%s DEFINE_INITIALIZATION DEFINE_PRELIMINARY_CALCS INIT_BOUNDED_MATRIX_DEF
%s CONTINUE_PROTOTYPE_DEF DEFINE_RUNTIME IN_FOUR_ARRAY_DEF IN_LOCAL_CALCS
%s IN_GLOBALS_SECTION IN_TOP_SECTION INIT_BOUNDED_THREE_ARRAY_DEF
%s DEFINE_BETWEEN_PHASES IN_FIVE_ARRAY_DEF IN_SIX_ARRAY_DEF IN_SEVEN_ARRAY_DEF
%s IN_NAMED_FIVE_ARRAY_DEF IN_NAMED_SIX_ARRAY_DEF IN_NAMED_SEVEN_ARRAY_DEF
%s IN_SPBOUNDED_NUMBER_DEF INIT_SPBOUNDED_VECTOR_DEF IN_PVM_SLAVE_SECTION
%s DEFINE_PRIORS DEFINE_LIKELIHOOD DEFINE_PROCEDURE IN_NUMBER_DEF2
%%

\/\/.*$         /* ignore trailing comments */ ;
\/[\*]+.[\*]\/  /* ignore block comments */ ;
\r    { ; }

INITIALIZATION_SECTION  {

  if (!data_defined)
  {
    fprintf(stderr,"Error -- DATA_SECTION must be defined before"
      " INITIALIZATION_SECTION \n");
    exit(1);
  }
  if (params_defined)
  {
    fprintf(stderr,"Error -- INITIALIZATION_SECTION must be defined before"
      " PARAMETER_SECTION for random effect model\n");
    exit(1);
  }

  if (initialization_defined)
  {
    fprintf(stderr,"%s","Error -- only one INTIALIZATION SECTION allowed\n");
    exit(1);
  }
  else
  {
    BEGIN DEFINE_INITIALIZATION;
    initialization_defined=1;
    fprintf(fall,"%s","}\n\nvoid model_parameters::initializationfunction(void)"
      "\n{\n");
  }
                }

REPORT_SECTION  {

  in_aux_proc=0;
  if (!data_defined)
  {
    fprintf(stderr,"Error -- DATA_SECTION must be defined before"
      " REPORT_SECTION \n");
    exit(1);
  }
  if (!params_defined)
  {
    fprintf(stderr,"Error -- PARAMETER_SECTION must be defined before"
      " REPORT_SECTION \n");
    exit(1);
  }
  if (!preliminary_calcs_defined && runtime_defined)
  {
    fprintf(stderr,"%s","Error -- REPORT_SECTION must be defined before RUNTIME_SECTION \n");
    exit(1);
  }
  if (final_defined)
  {
    fprintf(stderr,"%s","Error -- REPORT_SECTION must be defined before FINAL_SECTION\n");
    exit(1);
  }

  if (report_defined)
  {
    fprintf(stderr,"%s","Error -- only one REPORT SECTION allowed\n");
    exit(1);
  }
  else
  {
    BEGIN DEFINE_PROCS;
    report_defined=1;
    write_funnel_end();
    setup_for_prior_likelihood();
    fprintf(fall,"}\n");
    //if (!preliminary_calcs_defined)
    {
      fclose(fall);
      fall=fopen("xxalloc4.tmp","w+");
      if (fall==NULL)
      {
        fprintf(stderr,"%s","Error trying to open file xxalloc4.tmp\n");
      }
    }
    fprintf(fall,"%s","\nvoid model_parameters::report(const dvector& gradients)"
      "\n{\n");
    fprintf(fall," adstring ad_tmp=initial_params::get_reportfile_name();\n");
    fprintf(fall,"  ofstream report((char*)"
                 "(adprogram_name + ad_tmp));\n");
    fprintf(fall,"  if (!report)\n"
                 "  {\n    cerr << \"error trying to open report file\" "
                 " << adprogram_name << \".rep\";\n    return;\n  }\n");
  }
                }

FINAL_SECTION  {

  in_aux_proc=0;
  if (!data_defined)
  {
    fprintf(stderr,"Error -- DATA_SECTION must be defined before"
      " FINAL_SECTION \n");
    exit(1);
  }
  if (!params_defined)
  {
    fprintf(stderr,"Error -- PARAMETER_SECTION must be defined before"
      " FINAL_SECTION \n");
    exit(1);
  }

  if (final_defined)
  {
    fprintf(stderr,"%s","Error -- only one FINAL SECTION allowed\n");
    exit(1);
  }
  else
  {
    BEGIN DEFINE_PROCS;
    final_defined=1;
    setup_for_prior_likelihood();

    fprintf(fall,"%s","}\n\nvoid model_parameters::final_calcs()"
      "\n{\n");
  }
                }


RUNTIME_SECTION  {

  in_aux_proc=0;
  if (!data_defined)
  {
    fprintf(stderr,"Error -- DATA_SECTION must be defined before"
      " RUNTIME_SECTION \n");
    exit(1);
  }
  if (!params_defined)
  {
    fprintf(stderr,"Error -- PARAMETER_SECTION must be defined before"
      " RUNTIME_SECTION \n");
    exit(1);
  }

  if (runtime_defined)
  {
    fprintf(stderr,"%s","Error -- only one REPORT SECTION allowed\n");
    exit(1);
  }
  else
  {
    BEGIN DEFINE_RUNTIME;
    runtime_defined=1;
    write_funnel_end();
    setup_for_prior_likelihood();
    fprintf(fall,"%s","}\n\nvoid model_parameters::set_runtime(void)"
      "\n{\n");
  }
                }

<DEFINE_RUNTIME>^" "*convergence_criteria" ".*$ {

    strip_leading_blanks(tmp_string1,yytext);
    after_part(tmp_string2,tmp_string1,' ');  // get 10  in x  10
    strip_leading_blanks(tmp_string1,tmp_string2);
    fprintf(fall,"%s","  dvector temp(\"{");
    fprintf(fall,"%s}\");\n", tmp_string1);
    fprintf(fall,"  convergence_criteria.allocate"
      "(temp.indexmin(),temp.indexmax());\n" );
    fprintf(fall,"  convergence_criteria=temp;\n");

                                  }

<DEFINE_RUNTIME>^" "*maximum_function_evaluations" ".*$ {

    strip_leading_blanks(tmp_string1,yytext);
    after_part(tmp_string2,tmp_string1,' ');  // get 10  in x  10
    strip_leading_blanks(tmp_string1,tmp_string2);
    fprintf(fall,"%s","  dvector temp1(\"{");
    fprintf(fall,"%s}\");\n", tmp_string1);
    fprintf(fall,"  maximum_function_evaluations.allocate"
      "(temp1.indexmin(),temp1.indexmax());\n" );
    fprintf(fall,"  maximum_function_evaluations=temp1;\n");

                                  }


PRELIMINARY_CALCULATIONS_SECTION  |
PRELIMINARY_CALCS_SECTION  {

#  if defined(ADMB_REDEMO)
    printf("Error -- you can not use the PRELIMINARY_CALCS_SECTION"
      "\n in the random effects model at present. Use LOCAL_CALCS instead\n");
    exit(1);
#  endif
    //preliminary_calcs_defined=1;
    //write_funnel_end();
  if (!data_defined)
  {
    fprintf(stderr,"Error -- DATA_SECTION must be defined before"
      " PRELIMINARY_CALCS_SECTION \n");
    exit(1);
  }
  if (!params_defined)
  {
    fprintf(stderr,"Error -- PARAMETER_SECTION must be defined before"
      " PRELIMINARY_CALCS_SECTION\n");
    exit(1);
  }

  if (runtime_defined)
  {
    fprintf(stderr,"%s","Error -- PRELIMINARY_CALCS_SECTION must be defined before RUNTIME_SECTION \n");
    exit(1);
  }

  if (preliminary_calcs_defined)
  {
    fprintf(stderr,"%s","Error -- only one PRELIMINARY_CALCS_SECTION allowed\n");
    exit(1);
  }
  else
  {
    BEGIN DEFINE_PRELIMINARY_CALCS;
    preliminary_calcs_defined=1;
    write_funnel_end();
    setup_for_prior_likelihood();

    fprintf(fall,"}\n");
    //if (!report_defined)
    {
      fclose(fall);
      fall=fopen("xxalloc5.tmp","w+");
      if (fall==NULL)
      {
        fprintf(stderr,"%s","Error trying to open file xxalloc5.tmp\n");
      }
    }
    fprintf(fall,"%s","\nvoid model_parameters::preliminary_calculations(void) \n{\n");
    fprintf(fall,"%s","\n  #if defined(USE_ADPVM)\n");
    fprintf(fall,"%s","\n  admaster_slave_variable_interface(*this);\n");
    fprintf(fall,"%s","\n  #endif\n");
  }
                }

<DEFINE_PRELIMINARY_CALCS>^" ".* {fprintf(fall,"%s\n",yytext);}

BETWEEN_PHASES_SECTION {
  if (report_defined)
  {
    fprintf(stderr,"%s","Error -- BETWEEN_PHASES_SECTION must be defined before REPORT SECTION\n");
    exit(1);
  }

  if (between_phases_defined)
  {
    fprintf(stderr,"%s","Error -- only one BETWEEN_PHASES_SECTION allowed\n");
    exit(1);
  }
  else
  {
    BEGIN DEFINE_BETWEEN_PHASES;
    between_phases_defined=1;
    write_funnel_end();
    setup_for_prior_likelihood();

    fprintf(fall,"%s","}\n\nvoid model_parameters::between_phases_calculations(void)"
      "\n{\n");
    fprintf(fdat,"%s","  void between_phases_calculations(void);\n");
  }
                }

<DEFINE_BETWEEN_PHASES>^" ".* {fprintf(fall,"%s\n",yytext);}


<DEFINE_INITIALIZATION>{name}[ ]+{float_num_exp} {


    before_part(tmp_string,yytext,' ');  // get x in x 10
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".set_initial_value(");
    after_part(tmp_string1,yytext,' ');  // get 10  in x  10
    strip_leading_blanks(tmp_string2,tmp_string1);
    fprintf(fall,"%s);\n",tmp_string2);

                            }

SLAVE_SECTION  {

  if (pvmslaves_defined)
  {
    fprintf(stderr,"%s","Error -- only one pvm slave section allowed\n");
    exit(1);
  }
  else
  {
    BEGIN IN_PVM_SLAVE_SECTION;
    pvmslaves_defined=1;
    fprintf(fdat,"  virtual imatrix get_slave_assignments(void);\n");
    write_funnel_end();
    setup_for_prior_likelihood();

    fprintf(fall,"%s","}\n\nimatrix model_parameters::"
      "get_slave_assignments(void)\n{\n");
  }

         }

<IN_PVM_SLAVE_SECTION>^[ \t].*$ { fprintf(fall,"%s\n",yytext); }

DATA_SECTION  {

  if (data_defined)
  {
    fprintf(stderr,"%s","Error -- only one data section allowed\n");
    exit(1);
  }
  else
  {
    if(!data_defined) BEGIN DEFINE_DATA;
    data_defined=1;
    in_define_data=1;
    if (makedll)
    {
      fprintf(fall,"%s","model_data::model_data(int argc,char * argv[],dll_args& ad_dll) : "
        "ad_comm(argc,argv)\n{\n");
      fprintf(fdat,"%s","class dll_args;\n");
    }
    else
    {

      fprintf(fall,"%s","model_data::model_data(int argc,char * argv[]) : "
        "ad_comm(argc,argv)\n{\n");
    }
    fprintf(fdat,"%s","#define SEPFUN1\n");
    fprintf(fdat,"%s","#define SEPFUN3\n");
    fprintf(fdat,"%s","#define SEPFUN4\n");

    fprintf(fdat,"%s","class model_data : public ad_comm{\n"
       "  public:\n");
  }
                }

<DEFINE_DATA>^[ \t]*!!USER_CODE.*$ {
    strip_leading_blanks_and_tabs(tmp_string1,yytext);
    strcpy(tmp_string2,tmp_string1+11);
    fprintf(fall,"%s\n",tmp_string2);

    }

<DEFINE_DATA>^[ \t]*!!CLASS.*$ {              // start with !!CLASSbbclassname classinstance(xxx)
    num_user_classes++;
    strip_leading_blanks_and_tabs(tmp_string1,yytext);
    strcpy(tmp_string2,tmp_string1+7);  // now bbclassname classinstance(xxx)
    strip_leading_blanks(tmp_string1,tmp_string2); // now classname classinstance(xxx)
    initialize(tmp_string);
    before_part(tmp_string,tmp_string1,'('); // now classname classinstance in tmp_string
    if (!strlen(tmp_string))
    {
      strcpy(tmp_string,tmp_string1);
    }
    //fprintf(fdat,"%s;\n",tmp_string);
    before_partb(tmp_string2,tmp_string,' '); // now classname in tmp_string2

    after_partb(tmp_string3,tmp_string,' ');  // now bbclassinstance in tmp_string3
    strip_leading_blanks(tmp_string4,tmp_string3);// now classinstance in tmp_string4
    fprintf(fdat,"  %s * ",tmp_string2);
    fprintf(fdat,"  pad_%s;\n",tmp_string4);

    fprintf(fall,"  pad_%s = new ",tmp_string4);
    fprintf(fall,"%s",tmp_string2);
    initialize(tmp_string3);
    after_partb(tmp_string3,tmp_string1,'(');  // now xxx) in tmp_string3
    if (strlen(tmp_string3))
    {
      fprintf(fall,"(%s",tmp_string3);
    }
    fprintf(fall,";\n");
    strcpy(reference_statements[num_user_classes-1],tmp_string2);
    strcat(reference_statements[num_user_classes-1],"& ");
    strcat(reference_statements[num_user_classes-1],tmp_string4);
    strcat(reference_statements[num_user_classes-1],"= *pad_");
    strcat(reference_statements[num_user_classes-1],tmp_string4);
    //strcat(reference_statements[num_user_classes-1],";");
    strcpy(class_instances[num_user_classes-1],tmp_string4);

  }

<DEFINE_DATA>^[ \t]*@@.*$ {              // start with !!CLASSbbclassname classinstance(xxx)
    strip_leading_blanks_and_tabs(tmp_string1,yytext);
    printf("ddd\n");
    strcpy(tmp_string2,tmp_string1+2);  // now bbclassname classinstance(xxx)
    strip_leading_blanks(tmp_string1,tmp_string2); // now classname classinstance(xxx)
    initialize(tmp_string);
    before_part(tmp_string,tmp_string1,'('); // now classname classinstance in tmp_string
    if (!strlen(tmp_string))
    {
      strcpy(tmp_string,tmp_string1);
    }
    //fprintf(fdat,"%s;\n",tmp_string);
    before_partb(tmp_string2,tmp_string,' '); // now classname in tmp_string2

    after_partb(tmp_string3,tmp_string,' ');  // now bbclassinstance in tmp_string3
    strip_leading_blanks(tmp_string4,tmp_string3);// now classinstance in tmp_string4
    fprintf(fdat,"  %s ",tmp_string2);
    fprintf(fdat,"  %s;\n",tmp_string4);

    fprintf(fall,"  %s * tmp_%s = new ",tmp_string2,tmp_string4);
    fprintf(fall,"%s",tmp_string2);


    initialize(tmp_string3);
    after_partb(tmp_string3,tmp_string1,'(');  // now xxx) in tmp_string3
    if (strlen(tmp_string3))
    {
      fprintf(fall,"(%s",tmp_string3);
    }
    fprintf(fall,";\n");
    fprintf(fall,"  memcpy(cbuf,(char*)(&%s),sizeof(%s));\n",
      tmp_string4,tmp_string2);
    fprintf(fall,"  memcpy((char*)(&%s),(char*)(tmp_%s),sizeof(%s));\n",
      tmp_string4,tmp_string4,tmp_string2);
    fprintf(fall,"  memcpy((char*)(tmp_%s),buf,sizeof(%s));\n",
      tmp_string4,tmp_string2);
    fprintf(fall,"  delete tmp_%s;\n",tmp_string4);
    fprintf(fall,"  tmp_%s=NULL;\n",tmp_string4);


  }

<DEFINE_DATA>^[ \t]*!!.*$ {
    strip_leading_blanks_and_tabs(tmp_string1,yytext);
    strcpy(tmp_string2,tmp_string1+2);
    fprintf(fall,"%s\n",tmp_string2);

    }



<DEFINE_DATA>^[ \t]*LOCAL_CALCULATIONS |
<DEFINE_DATA>^[ \t]*LOCAL_CALCS |
<DEFINE_DATA>^[ \t]*LOC_CALCULATIONS |
<DEFINE_DATA>^[ \t]*LOC_CALCS  {

    BEGIN IN_LOCAL_CALCS;

        }

<DEFINE_DATA>init_number {
    likelihood_found=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  data_number ");
                     }

<DEFINE_DATA>init_adstring {

    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  init_adstring ");
                     }

<DEFINE_DATA>init_line_adstring {

    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  init_line_adstring ");
                     }

<DEFINE_DATA>init_int {
    likelihood_found=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  data_int ");
                     }

<DEFINE_DATA>splus_number |
<DEFINE_DATA>dll_init_number |
<DEFINE_DATA>dll_number {
    spnumber_flag=1;
    BEGIN IN_SPNUMBER_DEF;
    fprintf(fdat,"%s","  dll_data_number ");
                     }

<DEFINE_DATA>splus_int |
<DEFINE_DATA>dll_init_int |
<DEFINE_DATA>dll_int {

    BEGIN IN_SPNUMBER_DEF;
    fprintf(fdat,"%s","  dll_data_int ");
                     }

<DEFINE_DATA>splus_adstring |
<DEFINE_DATA>dll_adstring {
    spnumber_flag=2;

    BEGIN IN_SPNUMBER_DEF;
    fprintf(fdat,"%s","  dll_named_adstring ");
                     }

<DEFINE_DATA>splus_vector |
<DEFINE_DATA>dll_init_vector |
<DEFINE_DATA>dll_vector {
    spnumber_flag=1;

    BEGIN IN_SPVECTOR_DEF;
    fprintf(fdat,"%s","  dll_data_vector ");
                     }

<DEFINE_DATA>init_vector {
    likelihood_found=1;
    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  data_vector ");
                     }

<DEFINE_DATA>init_ivector {
    likelihood_found=1;
    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  data_ivector ");
                     }

<DEFINE_DATA>splus_matrix |
<DEFINE_DATA>dll_init_matrix |
<DEFINE_DATA>dll_matrix {

    spnumber_flag=1;
    BEGIN IN_SPMATRIX_DEF;
    fprintf(fdat,"%s","  dll_data_matrix ");
                     }

<DEFINE_DATA>splus_imatrix |
<DEFINE_DATA>dll_init_imatrix |
<DEFINE_DATA>dll_imatrix {

    //spnumber_flag=1;
    BEGIN IN_SPMATRIX_DEF;
    fprintf(fdat,"%s","  dll_data_imatrix ");
                     }

<DEFINE_DATA>init_imatrix {
    likelihood_found=1;
    //spnumber_flag=1;
    BEGIN IN_MATRIX_DEF;
    fprintf(fdat,"%s","  data_imatrix ");
                     }

<DEFINE_DATA>splus_3darray |
<DEFINE_DATA>dll_init_3darray |
<DEFINE_DATA>dll_3darray {

    spnumber_flag=1;
    BEGIN IN_SPTHREE_ARRAY_DEF;
    fprintf(fdat,"%s","  dll_data_3array ");
                     }

<DEFINE_DATA>init_matrix {
    likelihood_found=1;
    BEGIN IN_MATRIX_DEF;
    fprintf(fdat,"%s","  data_matrix ");
                     }

<DEFINE_DATA>init_table {
    likelihood_found=1;
    BEGIN IN_TABLE_DEF;
    fprintf(fdat,"%s","  data_matrix ");
                     }

<DEFINE_DATA>init_3iarray {
  prior_found=1;
    BEGIN IN_THREE_ARRAY_DEF;
    fprintf(fdat,"%s"," data_3iarray ");
                     }

<DEFINE_DATA>init_3darray {
    likelihood_found=1;
    BEGIN IN_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  data_3array ");
                     }

<DEFINE_DATA>init_4iarray {
  prior_found=1;
    BEGIN IN_FOUR_ARRAY_DEF;
    fprintf(fdat,"%s","  data_4iarray ");
                     }

<DEFINE_DATA>init_4darray {
    likelihood_found=1;
    BEGIN IN_FOUR_ARRAY_DEF;
    fprintf(fdat,"%s","  data_4array ");
                     }

<DEFINE_DATA>init_5darray {
    likelihood_found=1;
    BEGIN IN_FIVE_ARRAY_DEF;
    fprintf(fdat,"%s","  data_5array ");
                     }


<DEFINE_DATA>init_6darray {
    likelihood_found=1;
    BEGIN IN_SIX_ARRAY_DEF;
    fprintf(fdat,"%s","  data_6array ");
                     }


<DEFINE_DATA>init_7darray {
    likelihood_found=1;
    BEGIN IN_SEVEN_ARRAY_DEF;
    fprintf(fdat,"%s","  data_4array ");
                     }


<DEFINE_DATA>number {
    likelihood_found=1;
    BEGIN IN_NAMED_NUMBER_DEF;
    fprintf(fdat,"%s","  double ");

                     }

<DEFINE_DATA>int {
    likelihood_found=1;
    BEGIN IN_NAMED_NUMBER_DEF;
    fprintf(fdat,"%s","  int ");
                     }

<DEFINE_DATA>vector {
    likelihood_found=1;
    BEGIN IN_NAMED_VECTOR_DEF;
    fprintf(fdat,"%s","  dvector ");
                     }

<DEFINE_DATA>ivector {
    likelihood_found=1;
    BEGIN IN_NAMED_VECTOR_DEF;
    fprintf(fdat,"%s","  ivector ");
                     }

<DEFINE_DATA>matrix {
    likelihood_found=1;
    BEGIN IN_NAMED_MATRIX_DEF;
    fprintf(fdat,"%s","  dmatrix ");
                     }

<DEFINE_DATA>imatrix {
    likelihood_found=1;
    BEGIN IN_NAMED_MATRIX_DEF;
    fprintf(fdat,"%s","  imatrix ");
                     }

<DEFINE_DATA>3iarray {
    likelihood_found=1;
    BEGIN IN_NAMED_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  i3_array ");
                     }

<DEFINE_DATA>3darray {
    likelihood_found=1;
    BEGIN IN_NAMED_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  d3_array ");
                     }

<DEFINE_DATA>4iarray {
    likelihood_found=1;
    BEGIN IN_NAMED_FOUR_ARRAY_DEF;
    fprintf(fdat,"%s","  i4_array ");
                     }

<DEFINE_DATA>4darray {
    likelihood_found=1;
    BEGIN IN_NAMED_FOUR_ARRAY_DEF;
    fprintf(fdat,"%s","  d4_array ");
                     }

<DEFINE_DATA>5darray {
    likelihood_found=1;
    BEGIN IN_NAMED_FIVE_ARRAY_DEF;
    fprintf(fdat,"%s","  d5_array ");
                     }

<DEFINE_DATA>6darray {
    likelihood_found=1;
    BEGIN IN_NAMED_FIVE_ARRAY_DEF;
    fprintf(fdat,"%s","  d6_array ");
                     }

<DEFINE_DATA>7darray {
    likelihood_found=1;
    BEGIN IN_NAMED_FIVE_ARRAY_DEF;
    fprintf(fdat,"%s","  d7_array ");
                     }

<IN_LOCAL_CALCS>^[ \t]END_CALCS |
<IN_LOCAL_CALCS>^[ \t]END_CALCULATIONS {

    if (in_define_data) BEGIN DEFINE_DATA;
    if (in_define_parameters) BEGIN DEFINE_PARAMETERS;

                  }

<IN_LOCAL_CALCS>^[ \t][ \t].*$       {
    fprintf(fall,"%s\n",yytext);
          }

<DEFINE_PARAMETERS>^[ \t]*!!CLASS.*$ {              // start with !!CLASSbbclassname classinstance(xxx)
    num_user_classes++;
    strip_leading_blanks_and_tabs(tmp_string1,yytext);
    strcpy(tmp_string2,tmp_string1+7);  // now bbclassname classinstance(xxx)
    strip_leading_blanks(tmp_string1,tmp_string2); // now classname classinstance(xxx)
    initialize(tmp_string);
    before_part(tmp_string,tmp_string1,'('); // now classname classinstance in tmp_string
    if (!strlen(tmp_string))
    {
      strcpy(tmp_string,tmp_string1);
    }
    //fprintf(fdat,"%s;\n",tmp_string);
    before_partb(tmp_string2,tmp_string,' '); // now classname in tmp_string2

    after_partb(tmp_string3,tmp_string,' ');  // now bbclassinstance in tmp_string3
    strip_leading_blanks(tmp_string4,tmp_string3);// now classinstance in tmp_string4
    fprintf(fdat,"  %s * ",tmp_string2);
    fprintf(fdat,"  pad_%s;\n",tmp_string4);

    fprintf(fall,"  pad_%s = new ",tmp_string4);
    fprintf(fall,"%s",tmp_string2);
    initialize(tmp_string3);
    after_partb(tmp_string3,tmp_string1,'(');  // now xxx) in tmp_string3
    if (strlen(tmp_string3))
    {
      fprintf(fall,"(%s",tmp_string3);
    }
    fprintf(fall,";\n");
    strcpy(reference_statements[num_user_classes-1],tmp_string2);
    strcat(reference_statements[num_user_classes-1],"& ");
    strcat(reference_statements[num_user_classes-1],tmp_string4);
    strcat(reference_statements[num_user_classes-1],"= *pad_");
    strcat(reference_statements[num_user_classes-1],tmp_string4);
    //strcat(reference_statements[num_user_classes-1],";");
    strcpy(class_instances[num_user_classes-1],tmp_string4);

  }

<DEFINE_PARAMETERS>^[ \t]*!!USER_CODE.*$ {
    strip_leading_blanks_and_tabs(tmp_string1,yytext);
    strcpy(tmp_string2,tmp_string1+11);
    fprintf(fall,"%s\n",tmp_string2);

    }

<DEFINE_PARAMETERS>^[ \t]*!!.*$ {
    strip_leading_blanks_and_tabs(tmp_string1,yytext);
    strcpy(tmp_string2,tmp_string1+2);
    fprintf(fall,"%s\n",tmp_string2);

    }

<DEFINE_PARAMETERS>^[ \t]*LOCAL_CALCULATIONS |
<DEFINE_PARAMETERS>^[ \t]*LOCAL_CALCS |
<DEFINE_PARAMETERS>^[ \t]*LOC_CALCULATIONS |
<DEFINE_PARAMETERS>^[ \t]*LOC_CALCS  {

    BEGIN IN_LOCAL_CALCS;

        }

<DEFINE_PARAMETERS>number {

    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  param_number ");
    needs_initialization=1;
                    }

<DEFINE_PARAMETERS>objective_function_value {

    in_objective_function_value_flag=1;
    if(objective_function_defined++)
    {
      fprintf(stderr,"%s %d %s","Error in line",nline,"\n");
      fprintf(stderr,"only one instance of objective_function_value"
                     " may be declared\n");
      exit(1);
    }
    BEGIN IN_NUMBER_DEF2;
    fprintf(fdat,"%s","  param_number prior_function_value;\n");
    fprintf(fdat,"%s","  param_number likelihood_function_value;\n");
    fprintf(fdat,"%s","  objective_function_value ");
                     }

<DEFINE_PARAMETERS>sdreport_number {

    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  param_stddev_number ");
                     }

<DEFINE_PARAMETERS>likeprof_number {

    have_likeprof=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  param_likeprof_number ");
                     }

<DEFINE_PARAMETERS>init_int {
	prior_found=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  param_init_int ");
                     }

<DEFINE_PARAMETERS>equality_constraint_vector {

    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  equality_constraint_vector ");
    needs_initialization=1;
                     }
<DEFINE_PARAMETERS>inequality_constraint_vector {

    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  inequality_constraint_vector ");
    needs_initialization=1;
                     }

<DEFINE_PARAMETERS>vector {

    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  param_vector ");
    needs_initialization=1;
                     }

<DEFINE_PARAMETERS>constant_quadratic_penalty {

    BEGIN IN_NUMBER_DEF;
    //BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  constant_quadratic_re_penalty ");
    //needs_initialization=1;
      quadratic_prior_flag=1;
                     }

<DEFINE_PARAMETERS>quadratic_penalty {

    BEGIN IN_NUMBER_DEF;
    //BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  df_normal_prior_");
    //needs_initialization=1;
      quadratic_classprint_flag=3;
      quadratic_prior_flag=1;
                     }

<DEFINE_PARAMETERS>normal_prior |
<DEFINE_PARAMETERS>gaussian_prior {

    BEGIN IN_NUMBER_DEF;
    //BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  df_normal_prior_");
    //needs_initialization=1;
      quadratic_prior_flag=1;
      quadratic_classprint_flag=2;
      need_prior_globals=1;
                     }

<DEFINE_PARAMETERS>quadratic_prior {

    BEGIN IN_NUMBER_DEF;
    //BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  quadratic_prior ");
    //needs_initialization=1;
      quadratic_prior_flag=1;
                     }

<DEFINE_PARAMETERS>sdreport_vector {

    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  param_stddev_vector ");
                     }

<DEFINE_PARAMETERS>matrix {

    BEGIN IN_MATRIX_DEF;
    fprintf(fdat,"%s","  param_matrix ");
    needs_initialization=1;
                     }


<DEFINE_PARAMETERS>sdreport_matrix {

    BEGIN IN_MATRIX_DEF;
    fprintf(fdat,"%s","  param_stddev_matrix ");
                     }

<DEFINE_PARAMETERS>3darray {

    BEGIN IN_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  param_3array ");
    needs_initialization=1;
                     }


<DEFINE_PARAMETERS>4darray {

    BEGIN IN_FOUR_ARRAY_DEF;
    fprintf(fdat,"%s","  param_4array ");
    needs_initialization=1;
                     }

<DEFINE_PARAMETERS>5darray {

    BEGIN IN_FIVE_ARRAY_DEF;
    fprintf(fdat,"%s","  param_5array ");
    needs_initialization=1;
                     }

<DEFINE_PARAMETERS>6darray {

    BEGIN IN_SIX_ARRAY_DEF;
    fprintf(fdat,"%s","  param_6array ");
    needs_initialization=1;
                     }

<DEFINE_PARAMETERS>7darray {

    BEGIN IN_SEVEN_ARRAY_DEF;
    fprintf(fdat,"%s","  param_7array ");
    needs_initialization=1;
                     }


<DEFINE_PARAMETERS>SPinit_number {

    check_random_effects_ordering();
    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_number ");
                     }

<DEFINE_PARAMETERS>SPinit_bounded_number {

    check_random_effects_ordering();
    talk_to_splus=1;
    BEGIN INIT_BOUNDED_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_bounded_number ");
                     }

<DEFINE_PARAMETERS>SPinit_vector {

    check_random_effects_ordering();
    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_vector ");
                     }


<DEFINE_PARAMETERS>SPinit_bounded_vector {

    check_random_effects_ordering();
    talk_to_splus=1;
    BEGIN INIT_BOUNDED_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_bounded_vector ");
                     }

<DEFINE_PARAMETERS>SPinit_matrix {

    check_random_effects_ordering();
    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_matrix ");
                     }

<DEFINE_PARAMETERS>SPinit_bounded_matrix {

    check_random_effects_ordering();
    talk_to_splus=1;
    BEGIN INIT_BOUNDED_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_bounded_matrix ");
                     }

<DEFINE_PARAMETERS>SPinit_3darray {

    check_random_effects_ordering();
    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_3array ");
                     }

<DEFINE_PARAMETERS>SPinit_bounded_3darray {

    check_random_effects_ordering();
    talk_to_splus=1;
    BEGIN INIT_BOUNDED_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_bounded_d3array ");
                     }


<DEFINE_DATA>SPinit_number {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPdata_number ");
                     }

<DEFINE_DATA>SPinit_int {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPdata_int ");
                     }

<DEFINE_DATA>SPinit_vector {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPdata_vector ");
                     }

<DEFINE_DATA>SPinit_ivector {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPdata_ivector ");
                     }

<DEFINE_DATA>SPinit_matrix {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPdata_matrix ");
                     }

<DEFINE_DATA>SPinit_imatrix {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPdata_imatrix ");
                     }

<DEFINE_DATA>SPinit_3darray {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPdata_3array ");
                     }

<DEFINE_DATA>SPinit_4darray {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPdata_4array ");
                     }
<DEFINE_DATA>SPnumber {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPnamed_number ");
                     }

<DEFINE_DATA>SPint {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPnamed_int ");
                     }

<DEFINE_DATA>SPvector {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPnamed_dvector ");
                     }

<DEFINE_DATA>SPivector {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPnamed_ivector ");
                     }

<DEFINE_DATA>SPmatrix {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPnamed_dmatrix ");
                     }


<DEFINE_PARAMETERS>splus_init_number |
<DEFINE_PARAMETERS>dll_init_number {
    check_random_effects_ordering();
    spnumber_flag=1;
    BEGIN IN_SPNUMBER_DEF;
    fprintf(fdat,"%s","  dll_param_init_number ");
                     }



<DEFINE_PARAMETERS>splus_init_bounded_number |
<DEFINE_PARAMETERS>dll_init_bounded_number {
    check_random_effects_ordering();
    spnumber_flag=1;
    BEGIN IN_SPBOUNDED_NUMBER_DEF;
    fprintf(fdat,"%s","  dll_param_init_bounded_number ");
                     }


<DEFINE_PARAMETERS>splus_number |
<DEFINE_PARAMETERS>dll_number {
    check_random_effects_ordering();
    spnumber_flag=1;
    BEGIN IN_SPNUMBER_DEF;
    fprintf(fdat,"%s","  dll_param_number ");
                     }

<DEFINE_PARAMETERS>init_number {
    check_random_effects_ordering();
	prior_found=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  param_init_number ");
                     }

<DEFINE_PARAMETERS>init_number_vector {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_number_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_number {
    prior_found=1;
    check_random_effects_ordering();
    BEGIN INIT_BOUNDED_NUMBER_DEF;
    fprintf(fdat,"%s","  param_init_bounded_number ");
                     }

<DEFINE_PARAMETERS>init_bounded_number_vector {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN INIT_BOUNDED_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_bounded_number_vector ");
                     }

<DEFINE_PARAMETERS>splus_init_vector |
<DEFINE_PARAMETERS>dll_init_vector {

    check_random_effects_ordering();
    spnumber_flag=1;
    BEGIN IN_SPVECTOR_DEF;
    fprintf(fdat,"%s","  dll_param_init_vector ");
                     }

<DEFINE_PARAMETERS>splus_vector |
<DEFINE_PARAMETERS>dll_vector {

    check_random_effects_ordering();
    spnumber_flag=1;
    BEGIN IN_SPVECTOR_DEF;
    fprintf(fdat,"%s","  dll_param_vector ");
                     }

<DEFINE_PARAMETERS>init_vector {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_vector ");
                     }

<DEFINE_PARAMETERS>random_effects_vector {
	prior_found=1;
    random_effects_flag=1;
    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  random_effects_vector ");
                     }

<DEFINE_PARAMETERS>dll_random_effects_vector {

    spnumber_flag=1;
    random_effects_flag=1;
    BEGIN IN_SPVECTOR_DEF;
    fprintf(fdat,"%s","  dll_param_vector ");
                     }






<DEFINE_PARAMETERS>random_effects_bounded_vector {
	prior_found=1;
    random_effects_flag=1;
    BEGIN INIT_BOUNDED_VECTOR_DEF;
    fprintf(fdat,"%s","  random_effects_bounded_vector ");
                     }

<DEFINE_PARAMETERS>init_vector_vector {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN IN_MATRIX_DEF;
    fprintf(fdat,"%s","  param_init_vector_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_dev_vector {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN INIT_BOUNDED_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_bounded_dev_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_vector {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN INIT_BOUNDED_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_bounded_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_vector_vector {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN INIT_BOUNDED_MATRIX_DEF;
    fprintf(fdat,"%s","  param_init_bounded_vector_vector ");
                     }

<DEFINE_PARAMETERS>splus_init_bounded_vector |
<DEFINE_PARAMETERS>dll_init_bounded_vector {

    check_random_effects_ordering();
    spnumber_flag=1;
    BEGIN INIT_SPBOUNDED_VECTOR_DEF;
    fprintf(fdat,"%s","  dll_param_init_bounded_vector ");
                     }

<DEFINE_PARAMETERS>splus_matrix |
<DEFINE_PARAMETERS>dll_matrix {

    spnumber_flag=1;
    BEGIN IN_SPMATRIX_DEF;
    fprintf(fdat,"%s","  dll_param_matrix ");
                     }

<DEFINE_PARAMETERS>splus_init_matrix |
<DEFINE_PARAMETERS>dll_init_matrix {

    check_random_effects_ordering();
    spnumber_flag=1;
    BEGIN IN_SPMATRIX_DEF;
    fprintf(fdat,"%s","  dll_param_init_matrix ");
                     }

<DEFINE_PARAMETERS>init_matrix {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN IN_MATRIX_DEF;
    fprintf(fdat,"%s","  param_init_matrix ");
                     }

<DEFINE_PARAMETERS>random_effects_matrix {
	prior_found=1;
    random_effects_flag=1;
    BEGIN IN_MATRIX_DEF;
    fprintf(fdat,"%s","  random_effects_matrix ");
                     }

<DEFINE_PARAMETERS>random_effects_bounded_matrix {
	prior_found=1;
    random_effects_flag=1;
    BEGIN INIT_BOUNDED_MATRIX_DEF;
    fprintf(fdat,"%s","  random_effects_bounded_matrix ");
                     }

<DEFINE_PARAMETERS>init_matrix_vector {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN IN_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_matrix_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_matrix {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN INIT_BOUNDED_MATRIX_DEF;
    fprintf(fdat,"%s","  param_init_bounded_matrix ");
                     }

<DEFINE_PARAMETERS>init_bounded_matrix_vector {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN INIT_BOUNDED_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_bounded_matrix_vector ");
                     }

<DEFINE_PARAMETERS>splus_init_3darray |
<DEFINE_PARAMETERS>dll_init_3darray {

    spnumber_flag=1;
    BEGIN IN_SPTHREE_ARRAY_DEF;
    fprintf(fdat,"%s","  dll_param_init_d3array ");
                     }

<DEFINE_PARAMETERS>splus_3darray |
<DEFINE_PARAMETERS>dll_3darray {

    spnumber_flag=1;
    BEGIN IN_SPTHREE_ARRAY_DEF;
    fprintf(fdat,"%s","  dll_param_d3array ");
                     }

<DEFINE_PARAMETERS>init_3darray {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN IN_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_d3array ");
                     }

<DEFINE_PARAMETERS>init_4darray {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN IN_FOUR_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_4array ");
                     }

<DEFINE_PARAMETERS>init_5darray {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN IN_FIVE_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_5array ");
                     }

<DEFINE_PARAMETERS>init_bounded_3darray {
	prior_found=1;
    check_random_effects_ordering();
    BEGIN INIT_BOUNDED_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_bounded_d3array ");
                     }


<DEFINE_PARAMETERS>SPnumber {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPnamed_dvariable ");
                     }

<DEFINE_PARAMETERS>SPvector {

    talk_to_splus=1;
    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  SPnamed_dvar_vector ");
                     }

<DEFINE_PARAMETERS>SPmatrix {

    talk_to_splus=1;
    BEGIN IN_MATRIX_DEF;
    fprintf(fdat,"%s","  SPnamed_dvar_matrix ");
                     }

<IN_SPNUMBER_DEF>{name} {
    num_spargs++;
    if (spnumber_flag==1)
    {
      strcpy(name_string,"double *");
    }
    else if (spnumber_flag==2)
    {
      strcpy(name_string,"char **");
    }
    else
    {
      strcpy(name_string,"int *");
    }
    spnumber_flag=0;

    nchar=sprintf(classlist_ptr,"  %s%s;\n",name_string,yytext);
    classlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(conlist_ptr,",%s(_%s)",yytext,yytext);
    else
      nchar=sprintf(conlist_ptr," %s(_%s)",yytext,yytext);
    conlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist_ptr,",%s_%s",name_string,yytext);
    else
      nchar=sprintf(arglist_ptr,"%s_%s",name_string,yytext);
    arglist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist1_ptr,",_%s",yytext);
    else
      nchar=sprintf(arglist1_ptr,"_%s",yytext);
    arglist1_ptr+=nchar;

    fprintf(fdat,"%s",yytext);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"  %s",yytext);
    fprintf(fall,".allocate(ad_dll.%s,\"%s\");\n",yytext,yytext);

    if (needs_initialization)
    {
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"  %s",yytext);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      printf("IN_SP_NUMBER_DEF %s\n",yytext);
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_SPNUMBER_DEF>({name}\({num_exp}\)) {

    num_spargs++;
    if (spnumber_flag==1)
    {
      strcpy(name_string,"double *");
    }
    else if (spnumber_flag==2)
    {
      strcpy(name_string,"char **");
    }
    else
    {
      strcpy(name_string,"int *");
    }
    spnumber_flag=0;

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    nchar=sprintf(classlist_ptr,"  %s%s;\n",name_string,tmp_string);
    classlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(conlist_ptr,",%s(_%s)",tmp_string,tmp_string);
    else
      nchar=sprintf(conlist_ptr," %s(_%s)",tmp_string,tmp_string);
    conlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist_ptr,",%s_%s",name_string,tmp_string);
    else
      nchar=sprintf(arglist_ptr,"%s_%s",name_string,tmp_string);
    arglist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist1_ptr,",_%s",tmp_string);
    else
      nchar=sprintf(arglist1_ptr,"_%s",tmp_string);
    arglist1_ptr+=nchar;

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    marker();
    fprintf(fall,"%s",".allocate(ad_dll.");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    strict_after_part(tmp_string3,tmp_string2,'(');  // get x in x(1,4)
    fprintf(fall,"%s,%s,\"%s\")",tmp_string,tmp_string3,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }

                            }


<IN_NUMBER_DEF>{name} {

    if (quadratic_classprint_flag)
    {
      fprintf(fdat,"%s ",yytext);
     /*
      fprintf(fdat,"public:\n  void evaluate_%s(void);\nprivate:\n",yytext);
     */
      print_quadratic_random_effect_penalty_class(yytext);
    }
    else
    {
      fprintf(fdat," ");
    }

    fprintf(fdat,"%s",yytext);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"  %s",yytext);
    fprintf(fall,".allocate(\"%s\");",yytext);
    if (in_objective_function_value_flag)
    {
      fprintf(fall,"  /* ADOBJECTIVEFUNCTION */");
        in_objective_function_value_flag=0;
    }
    fprintf(fall,"\n");

    if (needs_initialization)
    {
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"  %s",yytext);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",yytext);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      //printf("IN_NUMBER_DEF %s\n",yytext);
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",yytext);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_NUMBER_DEF2>{name} {

    if (quadratic_classprint_flag)
    {
      fprintf(fdat,"%s ",yytext);
     /*
      fprintf(fdat,"public:\n  void evaluate_%s(void);\nprivate:\n",yytext);
     */
      print_quadratic_random_effect_penalty_class(yytext);
    }
    else
    {
      fprintf(fdat," ");
    }

    fprintf(fdat,"%s",yytext);
    fprintf(fdat,"%s",";\n");

    strcpy(objective_function_name_string,yytext);  // get objective function name
    fprintf(fall,"%s","  prior_function_value.allocate(\"prior_function_value\");\n");
    fprintf(fall,"%s","  likelihood_function_value.allocate(\"likelihood_function_value\");\n");

    fprintf(fall,"  %s",yytext);
    fprintf(fall,".allocate(\"%s\");",yytext);
    if (in_objective_function_value_flag)
    {
      fprintf(fall,"  /* ADOBJECTIVEFUNCTION */");
        in_objective_function_value_flag=0;
    }
    fprintf(fall,"\n");

    if (needs_initialization)
    {
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"  %s",yytext);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      //printf("IN_NUMBER_DEF %s\n",yytext);
      BEGIN DEFINE_PARAMETERS;
    }
                            }



<IN_NAMED_NUMBER_DEF>{name} {

    fprintf(fdat,"%s",yytext);
    fprintf(fdat,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",yytext);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_NUMBER_DEF>({name}\({num_exp}\)) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    if (quadratic_classprint_flag)
    {
      fprintf(fdat,"%s ",tmp_string);
      fprintf(fdat," ");
      fprintf(fdat,"%s;\n",tmp_string);
     /*
      fprintf(fdat,"public:\n  void evaluate_%s(void);\nprivate:\n",tmp_string);
     */
      print_quadratic_random_effect_penalty_class(tmp_string);
    }
    else
    {
      fprintf(fdat," ");
      fprintf(fdat,"%s;\n",tmp_string);
    }


    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    /*fprintf(fdat,"%s",";\n");*/
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }

                            }


<INIT_BOUNDED_NUMBER_DEF>({name}\({float_num_exp},{float_num_exp},{num_exp}\)) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }

                            }



<IN_SPBOUNDED_NUMBER_DEF>({name}\({float_num_exp},{float_num_exp},{num_exp}\)) |
<IN_SPBOUNDED_NUMBER_DEF>({name}\({float_num_exp},{float_num_exp}\)) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    //fprintf(fall,"%s",".allocate");
    fprintf(fall,".allocate(ad_dll.%s,",tmp_string);
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2+1,tmp_string);


    num_spargs++;
    if (spnumber_flag==1)
    {
      strcpy(name_string,"double *");
    }
    else if (spnumber_flag==2)
    {
      strcpy(name_string,"char **");
    }
    else
    {
      strcpy(name_string,"int *");
    }
    spnumber_flag=0;

    nchar=sprintf(classlist_ptr,"  %s%s;\n",name_string,tmp_string);
    classlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(conlist_ptr,",%s(_%s)",tmp_string,tmp_string);
    else
      nchar=sprintf(conlist_ptr," %s(_%s)",tmp_string,tmp_string);
    conlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist_ptr,",%s_%s",name_string,tmp_string);
    else
      nchar=sprintf(arglist_ptr,"%s_%s",name_string,tmp_string);
    arglist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist1_ptr,",_%s",tmp_string);
    else
      nchar=sprintf(arglist1_ptr,"_%s",tmp_string);
    arglist1_ptr+=nchar;



    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }

                            }







<INIT_BOUNDED_NUMBER_DEF>({name}\({float_num_exp},{float_num_exp}\)) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }

                            }


<IN_VECTOR_DEF>{name}\({num_exp},{num_exp}\) |
<IN_VECTOR_DEF>{name}\({num_exp},{name}\) |
<IN_VECTOR_DEF>{name}\({name},{num_exp}\) |
<IN_VECTOR_DEF>{name}\({name},{name}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";");
    if (quadratic_prior_flag)
    {
      fprintf(fdat,"   /* deleteXquadraticXprior */ ");
      fprintf(fall,"   /* deleteXquadraticXprior */ ");
      quadratic_prior_flag=0;
    }
    fprintf(fdat,"%s","\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_VECTOR_DEF>{name} {

    strcpy(tmp_string,yytext);  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    //after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    //before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"(\"%s\")",tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      /*
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      */
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_VECTOR_DEF>{name}\({num_exp},{num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_SPVECTOR_DEF>{name}\({num_exp},{num_exp}\) |
<IN_SPVECTOR_DEF>{name}\({num_exp},{num_exp},{num_exp}\) {

    //fprintf(fall,".allocate(ad_dll.%s,\"%s\");\n",yytext,yytext);

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    //fprintf(fall,"%s",".allocate");
    fprintf(fall,".allocate(ad_dll.%s,",tmp_string);
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2+1,tmp_string);


// ****************************************************************

    num_spargs++;
    if (spnumber_flag==1)
    {
      strcpy(name_string,"double *");
    }
    else if (spnumber_flag==2)
    {
      strcpy(name_string,"char **");
    }
    else
    {
      strcpy(name_string,"int *");
    }
    spnumber_flag=0;

    nchar=sprintf(classlist_ptr,"  %s%s;\n",name_string,tmp_string);
    classlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(conlist_ptr,",%s(_%s)",tmp_string,tmp_string);
    else
      nchar=sprintf(conlist_ptr," %s(_%s)",tmp_string,tmp_string);
    conlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist_ptr,",%s_%s",name_string,tmp_string);
    else
      nchar=sprintf(arglist_ptr,"%s_%s",name_string,tmp_string);
    arglist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist1_ptr,",_%s",tmp_string);
    else
      nchar=sprintf(arglist1_ptr,"_%s",tmp_string);
    arglist1_ptr+=nchar;

// ****************************************************************




    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<INIT_SPBOUNDED_VECTOR_DEF>{name}\({num_exp},{num_exp},{float_num_exp},{float_num_exp}\) |
<INIT_SPBOUNDED_VECTOR_DEF>{name}\({num_exp},{num_exp},{float_num_exp},{float_num_exp},{num_exp}\) {

    //fprintf(fall,".allocate(ad_dll.%s,\"%s\");\n",yytext,yytext);

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    //fprintf(fall,"%s",".allocate");
    fprintf(fall,".allocate(ad_dll.%s,",tmp_string);
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2+1,tmp_string);


// ****************************************************************

    num_spargs++;
    if (spnumber_flag==1)
    {
      strcpy(name_string,"double *");
    }
    else if (spnumber_flag==2)
    {
      strcpy(name_string,"char **");
    }
    else
    {
      strcpy(name_string,"int *");
    }
    spnumber_flag=0;

    nchar=sprintf(classlist_ptr,"  %s%s;\n",name_string,tmp_string);
    classlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(conlist_ptr,",%s(_%s)",tmp_string,tmp_string);
    else
      nchar=sprintf(conlist_ptr," %s(_%s)",tmp_string,tmp_string);
    conlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist_ptr,",%s_%s",name_string,tmp_string);
    else
      nchar=sprintf(arglist_ptr,"%s_%s",name_string,tmp_string);
    arglist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist1_ptr,",_%s",tmp_string);
    else
      nchar=sprintf(arglist1_ptr,"_%s",tmp_string);
    arglist1_ptr+=nchar;

// ****************************************************************




    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }


<IN_NAMED_VECTOR_DEF>{name}\({num_exp},{num_exp}\) |
<IN_NAMED_VECTOR_DEF>{name}\({num_exp},{name}\) |
<IN_NAMED_VECTOR_DEF>{name}\({name},{num_exp}\) |
<IN_NAMED_VECTOR_DEF>{name}\({name},{name}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s)",tmp_string2);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }


<IN_NAMED_VECTOR_DEF>{name} {

    if (warn_unallocated) write_unallocated("vector()");
    strcpy(tmp_string,yytext);  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate()");
    //fprintf(fall,"(\"%s\")",tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }


<INIT_BOUNDED_VECTOR_DEF>{name}\({num_exp},{num_exp},{float_num_exp},{float_num_exp}\)    {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }


<INIT_BOUNDED_VECTOR_DEF>{name}\({num_exp},{num_exp},{float_num_exp},{float_num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_MATRIX_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp}\) |
<IN_MATRIX_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_MATRIX_DEF>{name}\({num_exp},{num_exp}\) {

    if (warn_unallocated) write_unallocated("matrix(ix,iy)");
    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      /*
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      */
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_MATRIX_DEF>{name} {

    if (warn_unallocated) write_unallocated("matrix()");
    strcpy(tmp_string,yytext);  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    fprintf(fall,"(\"%s\")",tmp_string);
    //before_part(tmp_string2,tmp_string1,')');
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      /*
      XXXX
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
      */
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }


<IN_TABLE_DEF>{name}\({filename}\) {

    before_part(tmp_string,yytext,'(');  // get A in A("mat.tab")

    fprintf(fdat,"%s",tmp_string);
    fprintf(fdat,"%s",";\n");

    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,".allocate(0,-1,0,-1,\"%s\");\n",tmp_string);
    after_part(tmp_string1,yytext,'\"');
    fprintf(fall,"  dmatrix %s_tmp((adstring)%s;\n",tmp_string,tmp_string1);
    fprintf(fall,"  %s = %s_tmp;\n",tmp_string,tmp_string);
    if (needs_initialization)
    {
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_TABLE_DEF>{name}\({filenamesingle}\) {
    fprintf(stderr,"%s %d %s","Error in line",nline,"while reading (use double instead of single quotes)\n");
    exit(1);
                            }

<IN_TABLE_DEF>{name} {
    fprintf(fdat,"%s",yytext);
    fprintf(fdat,"%s",";\n");

    fprintf(fall,"  %s",yytext);
    fprintf(fall,".allocate(0,-1,0,-1,\"%s\");\n",yytext);
    fprintf(fall,"  adstring datname;\n");
    fprintf(fall,"  if(option_match(argc,argv,\"-ind\") > -1){ \n");
    fprintf(fall,"    datname = argv[option_match(argc,argv,\"-ind\") + 1];\n");
    fprintf(fall,"  }else{\n");
    fprintf(fall,"    datname = \"%s.dat\";\n",infile_root);
    fprintf(fall,"  }\n");
    fprintf(fall,"  dmatrix %s_tmp(datname);\n",yytext);
    fprintf(fall,"  %s = %s_tmp;\n",yytext,yytext);

    if (needs_initialization)
    {
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",yytext);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }


<IN_TABLE_DEF>{name}\({name}\) {
    before_part(tmp_string,yytext,'(');  // get A in A(str1)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fdat,"%s",";\n");

    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,".allocate(0,-1,0,-1,\"%s\");\n",tmp_string);

    strict_after_part(tmp_string1, yytext,'(');
    fprintf(fall,"  dmatrix %s_tmp((adstring)%s;\n",tmp_string,tmp_string1);
    fprintf(fall,"  %s = %s_tmp;\n",tmp_string,tmp_string);
    if (needs_initialization)
    {
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }




<IN_SPMATRIX_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp}\) |
<IN_SPMATRIX_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    //fprintf(fall,"%s",".allocate");
    fprintf(fall,".allocate(ad_dll.%s,",tmp_string);
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2+1,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
// ****************************************************************

    num_spargs++;
    if (spnumber_flag==1)
    {
      strcpy(name_string,"double *");
    }
    else if (spnumber_flag==2)
    {
      strcpy(name_string,"char **");
    }
    else
    {
      strcpy(name_string,"int *");
    }
    spnumber_flag=0;

    nchar=sprintf(classlist_ptr,"  %s%s;\n",name_string,tmp_string);
    classlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(conlist_ptr,",%s(_%s)",tmp_string,tmp_string);
    else
      nchar=sprintf(conlist_ptr," %s(_%s)",tmp_string,tmp_string);
    conlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist_ptr,",%s_%s",name_string,tmp_string);
    else
      nchar=sprintf(arglist_ptr,"%s_%s",name_string,tmp_string);
    arglist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist1_ptr,",_%s",tmp_string);
    else
      nchar=sprintf(arglist1_ptr,"_%s",tmp_string);
    arglist1_ptr+=nchar;

// ****************************************************************
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }


<IN_THREE_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) |
<IN_THREE_ARRAY_DEF>{name}\({index},{index},{index},{index},{index},{index},{index}\) |
<IN_THREE_ARRAY_DEF>{name}\({index},{index},{index},{index},{index},{index}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_THREE_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp}\) |
<IN_THREE_ARRAY_DEF>{name}\({num_exp},{num_exp}\) {

    if (warn_unallocated) write_unallocated("3darray(ix,iy)");
    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      /*
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      */
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_THREE_ARRAY_DEF>{name} {

    if (warn_unallocated) write_unallocated("3darray()");
    strcpy(tmp_string,yytext);  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    //after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    //before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"(\"%s\")",tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      /*
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      */
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_SPTHREE_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) |
<IN_SPTHREE_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    //fprintf(fall,"%s",".allocate");
    fprintf(fall,".allocate(ad_dll.%s,",tmp_string);
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2+1,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
// ****************************************************************

    num_spargs++;
    if (spnumber_flag==1)
    {
      strcpy(name_string,"double *");
    }
    else if (spnumber_flag==2)
    {
      strcpy(name_string,"char **");
    }
    else
    {
      strcpy(name_string,"int *");
    }
    spnumber_flag=0;

    nchar=sprintf(classlist_ptr,"  %s%s;\n",name_string,tmp_string);
    classlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(conlist_ptr,",%s(_%s)",tmp_string,tmp_string);
    else
      nchar=sprintf(conlist_ptr," %s(_%s)",tmp_string,tmp_string);
    conlist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist_ptr,",%s_%s",name_string,tmp_string);
    else
      nchar=sprintf(arglist_ptr,"%s_%s",name_string,tmp_string);
    arglist_ptr+=nchar;

    if (num_spargs>1)
      nchar=sprintf(arglist1_ptr,",_%s",tmp_string);
    else
      nchar=sprintf(arglist1_ptr,"_%s",tmp_string);
    arglist1_ptr+=nchar;

// ****************************************************************
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_FOUR_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_FOUR_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) |
<IN_FOUR_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp}\) |
<IN_FOUR_ARRAY_DEF>{name}\({num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      /*
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      */
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_FOUR_ARRAY_DEF>{name} {

    strcpy(tmp_string,yytext);  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    //after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    //before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"(\"%s\")",tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      /*
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      */
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_FIVE_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_SIX_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_SEVEN_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (needs_initialization)
    {
      before_part(tmp_string,yytext,'(');
      fprintf(fall,"  #ifndef NO_AD_INITIALIZE\n");
      fprintf(fall,"    %s",tmp_string);
      fprintf(fall,".initialize();\n");
      fprintf(fall,"  #endif\n");
      needs_initialization=0;
    }
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }



<IN_NAMED_MATRIX_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s)",tmp_string2);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_NAMED_MATRIX_DEF>{name}\({num_exp},{num_exp}\) {
    if (warn_unallocated) write_unallocated("matrix(i1,i2)");

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s)",tmp_string2);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_NAMED_MATRIX_DEF>{name} {
    if (warn_unallocated) write_unallocated("matrix()");

    strcpy(tmp_string,yytext);  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate()");
    //after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    //before_part(tmp_string2,tmp_string1,')');
    //fprintf(fall,"%s)",tmp_string2);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<INIT_BOUNDED_MATRIX_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{float_num_exp},{float_num_exp}\)    {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
			    }


<INIT_BOUNDED_MATRIX_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{float_num_exp},{float_num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<INIT_BOUNDED_THREE_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{float_num_exp},{float_num_exp}\)    {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
			    }


<INIT_BOUNDED_THREE_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{float_num_exp},{float_num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s,\"%s\")",tmp_string2,tmp_string);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      BEGIN DEFINE_DATA;
    }
    else
    {
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_NAMED_THREE_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) |
<IN_NAMED_THREE_ARRAY_DEF>{name}\({num_exp},{name},{num_exp},{num_exp},{num_exp},{num_exp}\) |
<IN_NAMED_THREE_ARRAY_DEF>{name}\({index},{index},{index},{index},{index},{index}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s)",tmp_string2);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_NAMED_THREE_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp}\) {
    if (warn_unallocated) write_unallocated("3darray(i1,i2,j1,j2)");

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s)",tmp_string2);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_NAMED_THREE_ARRAY_DEF>{name}\({num_exp},{num_exp}\) {
    if (warn_unallocated) write_unallocated("3darray(i1,i2)");

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s)",tmp_string2);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_NAMED_THREE_ARRAY_DEF>{name} {
    if (warn_unallocated) write_unallocated("3darray()");

    strcpy(tmp_string,yytext);  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s)",tmp_string2);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_NAMED_FOUR_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s)",tmp_string2);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_NAMED_FIVE_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s)",tmp_string2);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_NAMED_SIX_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s)",tmp_string2);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }

<IN_NAMED_SIX_ARRAY_DEF>{name} {
    if (warn_unallocated) write_unallocated("6darray()");

    strcpy(tmp_string,yytext);  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate()");
    //fprintf(fall,"%s",".allocate");
    //after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    //before_part(tmp_string2,tmp_string1,')');
    //fprintf(fall,"%s)",tmp_string2);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
  }

<IN_NAMED_SEVEN_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) {

    before_part(tmp_string,yytext,'(');  // get x in x(1,4)
    fprintf(fdat,"%s",tmp_string);
    fprintf(fall,"  %s",tmp_string);
    fprintf(fall,"%s",".allocate");
    after_part(tmp_string1,yytext,'(');  // get x in x(1,4)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"%s)",tmp_string2);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"%s",";\n");
    if (!params_defined)
    {
      if(likelihood_found) {
        if(likelihood_counter<MAX_LIKE_CHECK) sprintf(likelihood_checker[likelihood_counter++],"%s",tmp_string);
        likelihood_found=0;
      }
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }


<DEFINE_PRIORS>{prior_name}[ \t]*[~][ \t]*{prior_def} {    //for priors_section
    before_part(tmp_string,yytext,'~');  // get x in x~10, parameter name
    strict_after_part(tmp_string1,yytext,'~');  // get 10  in x~10
    before_part(tmp_string2,tmp_string1,'(');   //function name
    strict_after_part(tmp_string3,tmp_string1,'(');  //function input arg.
    //printf("%s\n %s \t %s \t %s \t %s",yytext,tmp_string,tmp_string1,tmp_string2,tmp_string3);

    trim(tmp_string2); //function name
    //strcpy(tmp_string4,"prior_");
    //strcat(tmp_string4,tmp_string2); //define prior_** in priors.cpp file, should be neg.log.likelihood.form
    trim(tmp_string); trim(tmp_string3);

    {
      int i=0; //check if the prior variable from init_ parameter section
      while(prior_check(prior_checker[i],tmp_string)!=0){
      //printf(" idx %d tot %d, prior %s, parameter %s\n",i,prior_counter, tmp_string,prior_checker[i]);
        if(i == (prior_counter-1)){//still not found for the last one
          printf("Warning: Prior ( %s ) is not defined on a parameter\n",tmp_string);
          break;
        }
        i++;
      }
    }

    if(prior_function_toggle==0)
    { //left side of ~ go to first argument in function argu. list
      fprintf(fall,"  tmp__prior=%s(%s,%s ;\n",tmp_string2,tmp_string,tmp_string3);
      fprintf(fall,"  prior_function_value+=tmp__prior;\n ");
      fprintf(fall,"%s%s%s","  ",objective_function_name_string,"+=tmp__prior");
    }
    else
    { //left side of ~ go to the last argument in function argu. list
      before_partb(tmp_string4,tmp_string3,')');
      fprintf(fall,"  tmp__prior=%s(%s,%s);\n",tmp_string2,tmp_string4,tmp_string);
      fprintf(fall,"  prior_function_value+=tmp__prior;\n ");
      fprintf(fall,"%s%s%s","  ",objective_function_name_string,"+=tmp__prior");
    }
                   }



<DEFINE_LIKELIHOOD>{prior_name}[ \t]*[~][ \t]*{prior_def} { //for likelihood_section
    before_part(tmp_string,yytext,'~');  // get x in x~10, parameter name
    strict_after_part(tmp_string1,yytext,'~');  // get 10  in x~10
    before_part(tmp_string2,tmp_string1,'(');   //function name
    strict_after_part(tmp_string3,tmp_string1,'(');  //function input arg.

    trim(tmp_string2); //function name
    //strcat(like_str,tmp_string2); //define like_** in priors.cpp file, should be neg.log.likelihood.form
    trim(tmp_string); trim(tmp_string3);

    {
      int i=0; //check if the likelihood variable from data section
      while(prior_check(likelihood_checker[i],tmp_string)!=0){
        //printf(" idx %d tot %d, %s, %s\n",i,likelihood_counter, tmp_string,likelihood_checker[i]);
        if(i == (likelihood_counter-1)){//still not found for the last one
          printf("Warning: likelihood ( %s ) is not defined on a data_section variable\n",tmp_string);
          break;
        }
        i++;
      }
    }

    if(prior_function_toggle==0)
    { //left side of ~ go to first argument in function argu. list
      fprintf(fall,"  tmp__like=%s(%s,%s ;\n",tmp_string2,tmp_string,tmp_string3);
      fprintf(fall,"  likelihood_function_value+=tmp__like;\n ");
      fprintf(fall,"%s%s%s","  ",objective_function_name_string,"+=tmp__like");
    }
    else
    { //left side of ~ go to the last argument in function argu. list
      before_partb(tmp_string4,tmp_string3,')');
      fprintf(fall,"  tmp__like=%s(%s,%s);\n",tmp_string2,tmp_string4,tmp_string);
      fprintf(fall,"  likelihood_function_value+=tmp__like;\n ");
      fprintf(fall,"%s%s%s","  ",objective_function_name_string,"+=tmp__like");
    }
                   }


<DEFINE_PROCEDURE>{prior_name}[ \t]*[~][ \t]*{prior_def} {    //for procedure_section
    before_part(tmp_string,yytext,'~');  // get x in x~10, parameter name
    strict_after_part(tmp_string1,yytext,'~');  // get 10  in x~10
    before_part(tmp_string2,tmp_string1,'(');   //function name
    strict_after_part(tmp_string3,tmp_string1,'(');  //function input arg.

    trim(tmp_string2);  //function name, should be neg.log.likelihood.form
    trim(tmp_string); trim(tmp_string3);
    if(prior_function_toggle==0)
    { //left side of ~ go to first argument in function argu. list
      fprintf(fall,"  %s +=%s(%s,%s",objective_function_name_string,tmp_string2,tmp_string,tmp_string3);
    }
    else
    { //left side of ~ go to the last argument in function argu. list
      before_partb(tmp_string4,tmp_string3,')');
      fprintf(fall,"  %s +=%s(%s,%s)",objective_function_name_string,tmp_string2,tmp_string4,tmp_string);
    }
                   }




; {
  if(priors_defined && (!priors_done)){
   	fprintf(fall,"%s",yytext);
	BEGIN DEFINE_PRIORS;
  }
  if(likelihood_defined && (!likelihood_done)){
   	if(priors_defined) priors_done=1; //turn off prior
   	fprintf(fall,"%s",yytext);
	BEGIN DEFINE_LIKELIHOOD;
  }
  /*
  if(procedure_defined && (!procedure_done)){
   	if(priors_defined) priors_done=1;
   	if(likelihood_defined) likelihood_done=1;
   	fprintf(fall,"%s",yytext);
	BEGIN DEFINE_PROCEDURE;
  }
  */
  //;             /* ignore semi colons */ ;
  }


[ \t]+ {
  if(priors_defined && (!priors_done)){
   	fprintf(fall,"%s",yytext);
	BEGIN DEFINE_PRIORS;
  }
  if(likelihood_defined && (!likelihood_done)){
   	priors_done=1;
   	fprintf(fall,"%s",yytext);
	BEGIN DEFINE_LIKELIHOOD;
  }
  /*
  if(procedure_defined && (!procedure_done)){
   	priors_done=1;likelihood_done=1;
   	fprintf(fall,"%s",yytext);
	BEGIN DEFINE_PROCEDURE;
  }
  */
  //[ \t]+        /* ignore blanks */  ;
  }


\n {
  if(priors_defined && (!priors_done)){
   	fprintf(fall,"%s",yytext);
	BEGIN DEFINE_PRIORS;
  }
  if(likelihood_defined && (!likelihood_done)){
   	priors_done=1;
   	fprintf(fall,"%s",yytext);
	BEGIN DEFINE_LIKELIHOOD;
  }
  /*
  if(procedure_defined && (!procedure_done)){
   	priors_done=1;likelihood_done=1;
   	fprintf(fall,"%s",yytext);
	BEGIN DEFINE_PROCEDURE;
  }
  */
  nline++;
  }



. {
  if(priors_defined && (!priors_done)){
   	fprintf(fall,"%s",yytext);
	BEGIN DEFINE_PRIORS;
  }
  else if(likelihood_defined && (!likelihood_done)){
   	priors_done=1;
   	fprintf(fall,"%s",yytext);
	BEGIN DEFINE_LIKELIHOOD;
  }
  /*
  else if(procedure_defined && (!procedure_done)){
   	priors_done=1;likelihood_done=1;
   	fprintf(fall,"%s",yytext);
	BEGIN DEFINE_PROCEDURE;
  }
  */
  else{
	fprintf(stderr,"%s %d %s","Error in line",nline,"while reading\n");
	fprintf(stderr,"%s\n",yytext);
	exit(1);
  }
  }




PARAMETER_SECTION {
    if (!data_defined)
    {
      fprintf(stderr,"Error DATA_SECTION must be defined before"
        " PARAMETER SECTION\n");
      exit(1);
    }
    if(!params_defined) BEGIN DEFINE_PARAMETERS;
    in_define_data=0;
    in_define_parameters=1;
    params_defined=1;

    fprintf(fdat,"  ~model_data();\n");
    if (makedll)
      fprintf(fdat,"  model_data(int argc,char * argv[],dll_args&);\n  friend class model_parameters;\n");
    else
      fprintf(fdat,"  model_data(int argc,char * argv[]);\n  friend class model_parameters;\n");
    fprintf(fdat,"%s","};\n\nclass model_parameters : "
      "public model_data ,"
      "\n  public function_minimizer\n{\n");
    fprintf(fdat,"%s","public:\n");
    fprintf(fdat,"%s","  friend class df1b2_pre_parameters;\n"); //add by liu
    fprintf(fdat,"%s","  friend class df1b2_parameters;\n");  //add by liu

    fprintf(fdat,"  static model_parameters * model_parameters_ptr;\n"
      "  static model_parameters * get_model_parameters_ptr(void)\n"
      "  {\n"
      "    return model_parameters_ptr;\n"
      "  }\n");

    fprintf(fdat,"  ~model_parameters();\n");
//    fprintf(fdat,"%s","  void admaster_slave_variable_interface(void);\n");
    fprintf(fdat,"%s","  void preliminary_calculations(void);\n");
    fprintf(fdat,"%s","  void set_runtime(void);\n");
    fprintf(fdat,"%s","  virtual void * mycast(void) {return (void*)this;}\n");

    fprintf(fdat,"%s", "  static int mc_phase(void)\n"
      "  {\n    return initial_params::mc_phase;\n  }\n");

    fprintf(fdat,"%s", "  static int mceval_phase(void)\n"
      "  {\n    return initial_params::mceval_phase;\n  }\n");

    fprintf(fdat,"%s", "  static int sd_phase(void)\n"
      "  {\n    return initial_params::sd_phase;\n  }\n");

   fprintf(fdat,"%s", "  static int current_phase(void)\n"
      "  {\n    return initial_params::current_phase;\n  }\n");
    fprintf(fdat,"%s", "  static int last_phase(void)\n"
      "  {\n    return (initial_params::current_phase\n"
      "      >=initial_params::max_number_phases);\n  }\n");
   fprintf(fdat,"%s", "  static prevariable current_feval(void)\n"
      "  {\n    return *objective_function_value::pobjfun;\n  }\n");

   /*
    if (random_effects_flag)
    {

      fprintf(fdat,"%s", "  void AD_uf_inner(const dvector& x,"
        "const dvar_vector& u);\n"
        "  void AD_uf_outer(const dvar_vector& x,"
        "const dvar_vector& u);\n");
    }
    */

    fprintf(fdat,"%s","private:\n");
    fprintf(fdat,"%s", "  ivector integer_control_flags;\n");
    fprintf(fdat,"%s", "  void begin_df1b2_funnel(void);\n");
    fprintf(fdat,"%s", "  void end_df1b2_funnel(void);\n");

    fprintf(fdat,"%s", "  dvector double_control_flags;\n");
    fclose(fdat);
    fdat=fopen("tfile2","w+");
    if (fdat==NULL)
    {
      fprintf(stderr,"Error trying to open file tfile2\n");
    }

    if (makedll)
    {
      fprintf(fall,"%s","}\n\nmodel_parameters::model_parameters"
        "(int sz,int argc,char * argv[], dll_args& ad_dll) : "
        "\n model_data(argc,argv,ad_dll) , function_minimizer(sz)\n{\n");
  //        "\n ad_comm(argc,argv), model_data(ad_dll) , function_minimizer(sz)\n{\n");
    }
    else
    {
      fprintf(fall,"%s","}\n\nmodel_parameters::model_parameters"
        "(int sz,int argc,char * argv[]) : "
        "\n model_data(argc,argv) , function_minimizer(sz)\n{\n");
    }
    fprintf(fall,"%s", "  model_parameters_ptr=this;\n");
    fprintf(fall,"%s", "  initializationfunction();\n");
    fclose(fall);
    fall=fopen("xxalloc2.tmp","w+");
    if (fall==NULL)
    {
      fprintf(stderr,"%s","Error trying to open file xxalloc2.tmp\n");
    }

                  }

PROCEDURE_SECTION {

    /* int i; */

    if (!data_defined)
    {
      fprintf(stderr,"Error -- DATA_SECTION must be defined before"
        " PROCEDURE SECTION\n OR PARAMETER SECTION\n");
      exit(1);
    }
    if (!params_defined)
    {
      fprintf(stderr,"Error -- PARAMETER_SECTION must be defined before"
        " PROCEDURE SECTION\n");
      exit(1);
    }

    if (!objective_function_defined)
    {
      fprintf(stderr,"Error -- You must define an object of type objective"
        "_function_value in the\nPARAMETER SECTION"
        "and assign the approriate value to it in the\nPROCEDURE_SECTION");
      exit(1);
    }
    BEGIN DEFINE_PROCS;
    //BEGIN DEFINE_PROCEDURE;
    procedure_defined=1;
    in_procedure_def=1;
    in_define_parameters=0;

    fclose(fdat);
    fdat=fopen("tfile3","w+");
    if (fdat==NULL)
    {
      fprintf(stderr,"Error trying to open file tfile3\n");
    }

    if (makedll)
    {
      fprintf(fdat,"public:\n  virtual void userfunction(void);\n"
        "  virtual void report(const dvector& gradients);\n" // define this to get a report
        "  virtual void final_calcs(void);\n"
        "  model_parameters(int sz,int argc, char * argv[],"
        " dll_args& ad_dll);\n");
    }
    else
    {
      fprintf(fdat,"public:\n  virtual void userfunction(void);\n"
        "  virtual void report(const dvector& gradients);\n" // define this to get a report
        "  virtual void final_calcs(void);\n"
        "  model_parameters(int sz,int argc, char * argv[]);\n");
    }
    if(!initialization_defined)
    {
      fprintf(fdat,"  virtual void initializationfunction(void){}\n");
    }
    else
    {
      fprintf(fdat,"  virtual void initializationfunction(void);\n");
    }

    if (random_effects_flag)
    {

      fprintf(fdat,"%s", "  virtual void AD_uf_inner(void){pre_userfunction();}\n"
        "  virtual void AD_uf_outer(void){pre_userfunction();}\n"
        /*"  virtual void user_function(const init_df1b2vector& x,"
        "df1b2variable& f){;}\n" */
        "  virtual void user_function(void){;}\n"
        "  virtual void allocate(void){;}\n");
    }
    fclose(fdat);
    fdat=fopen("tfile4","w+");
    if (fdat==NULL)
    {
      fprintf(stderr,"Error trying to open file tfile\n");
    }

   /* fprintf(fdat,"%s","};\n");*/
    fprintf(fall,"%s","}\n");
    fclose(fall);
    fall=fopen("xxalloc3.tmp","w+");
    if (fall==NULL)
    {
      fprintf(stderr,"%s","Error trying to open file xxalloc3.tmp\n");
    }
    fprintf(fall,"%s","void model_parameters::userfunction(void)"
      "\n{\n");
    fprintf(fall,"  %s%s",objective_function_name_string," =0.0;\n");

    add_references_to_user_classes(fall);
                  }


PRIORS_SECTION |
PRIOR_SECTION {
  if (!data_defined)
  {
    fprintf(stderr,"Error -- DATA_SECTION must be defined before"
      " PRIORS_SECTION \n");
    exit(1);
  }
  if (!params_defined)
  {
    fprintf(stderr,"Error -- PARAMETER_SECTION must be defined before"
      " PRIORS_SECTION \n");
    exit(1);
  }
  if (preliminary_calcs_defined)
  {
    fprintf(stderr,"%s","Error -- PRIORS_SECTION must be defined before PRELIMINARY_CALCS_SECTION\n");
    exit(1);
  }
  if (likelihood_defined)
  {
    fprintf(stderr,"%s","Error -- PRIORS_SECTION must be defined before"
      " LIKELIHOOD_SECTION \n");
	  exit(1);
  }
  if (procedure_defined)
  {
    fprintf(stderr,"Error -- PRIOR_SECTION must be defined before"
      " PROCEDURE_SECTION \n");
    exit(1);
  }
  if (priors_defined)
  {
    fprintf(stderr,"%s","Error -- only one PRIORS_SECTION allowed\n");
    exit(1);
  }
  else
  {
    BEGIN DEFINE_PRIORS;
    priors_defined=1;

    /* //don't know why the following block not working, add by liu
    fprintf(fall,"%s","}\n");
    fclose(fall);
    fall=fopen("xxalloc3.tmp","w+");
    if (fall==NULL)
    {
      fprintf(stderr,"%s","Error trying to open file xxalloc2.tmp\n");
    }
    fprintf(fall,"%s","\nvoid model_parameters::priorsfunction(void)" "\n{\n");
    */

    fprintf(fall,"%s","}\n\nvoid model_parameters::priorsfunction(void)" "\n{\n");
    fprintf(fall,"%s","  prior_function_value=0.0;\n");
    fprintf(fall,"%s","  dvariable tmp__prior=0.0;\n");
  }
  }



LIKELIHOODS_SECTION |
LIKELIHOOD_SECTION {
  if (!data_defined)
  {
    fprintf(stderr,"Error -- DATA_SECTION must be defined before"
      " PRIORS_SECTION \n");
    exit(1);
  }
  if (!params_defined)
  {
    fprintf(stderr,"Error -- PARAMETER_SECTION must be defined before"
      " PRIORS_SECTION \n");
    exit(1);
  }
  if (preliminary_calcs_defined)
  {
    fprintf(stderr,"%s","Error -- LIKELIHOOD_SECTION must be defined before PRELIMINARY_CALCS_SECTION\n");
    exit(1);
  }
  if (procedure_defined)
  {
    fprintf(stderr,"Error -- LIKELIHOOD_SECTION must be defined before"
      " PROCEDURE_SECTION \n");
    exit(1);
  }
  if (likelihood_defined)
  {
    fprintf(stderr,"%s","Error -- only one LIKELIHOOD_SECTION allowed\n");
    exit(1);
  }
  else
  {
    BEGIN DEFINE_LIKELIHOOD;
    likelihood_defined=1;

    /* //don't know why the following block not working, add by liu
    fprintf(fall,"%s","}\n");
    fclose(fall);
    fall=fopen("xxalloc3.tmp","w+");
    if (fall==NULL)
    {
      fprintf(stderr,"%s","Error trying to open file xxalloc2.tmp\n");
    }
    fprintf(fall,"%s","\nvoid model_parameters::likelihoodfunction(void)" "\n{\n");
    */

    fprintf(fall,"%s","}\n\nvoid model_parameters::likelihoodfunction(void)" "\n{\n");
    fprintf(fall,"%s","  likelihood_function_value=0.0;\n");
    fprintf(fall,"%s","  dvariable tmp__like=0.0;\n");
  }
  }





FUNCTION[ ]*{name}[ ]*{name}\(.*\) {
    if (!in_procedure_def)
    {
      fprintf(stderr,"Error -- FUNCTION must be used within the"
        " PROCEDURE SECTION\n");
      exit(1);
    }

    after_part(tmp_string1,yytext,' ');  // get function name
    strip_leading_blanks(tmp_string2,tmp_string1);
    before_part(tmp_string3,tmp_string2,' ');
    after_part(tmp_string4,tmp_string2,' ');  // get function name
    strip_leading_blanks(tmp_string1,tmp_string4);
    write_funnel_end();
    setup_for_prior_likelihood();

    fprintf(fall,"}\n\n%s ",tmp_string3);
    fprintf(fall,"model_parameters::%s\n{\n",tmp_string1);
    fprintf(fdat," %s %s;\n",tmp_string3,tmp_string1);
    add_references_to_user_classes(fall);
    in_aux_proc=1;
    BEGIN DEFINE_PROCS;
                              }



SEPARABLE_FUNCTION[ ]*{name}[ ]*{name}\(.*\) {
    if (!in_procedure_def)
    {
      fprintf(stderr,"Error -- SEPARABLE_FUNCTION must be used within the"
        " PROCEDURE SECTION\n");
      exit(1);
    }

    after_part(tmp_string1,yytext,' ');  // get function name
    strip_leading_blanks(tmp_string2,tmp_string1);
    before_part(tmp_string3,tmp_string2,' ');
    after_part(tmp_string4,tmp_string2,' ');  // get function name
    strip_leading_blanks(tmp_string1,tmp_string4);
    write_funnel_end();
    setup_for_prior_likelihood();

    fprintf(fall,"}\n\n%s SEPFUN1  ",tmp_string3);
    fprintf(fall,"model_parameters::%s\n{\n  "
      "begin_df1b2_funnel();\n" ,tmp_string1);
    fprintf(fdat,"SEPFUN3 %s %s;\n",tmp_string3,tmp_string1);
    add_references_to_user_classes(fall);
    in_aux_proc=1;
    in_funnel_proc=1;
    have_separable_function=1;
    BEGIN DEFINE_PROCS;
                              }


NESTED_FUNCTION[ ]*{name}[ ]*{name}\(.*\) {
    if (!in_procedure_def)
    {
      fprintf(stderr,"Error -- NESTED_SEPARABLE_FUNCTION must be used"
        " within the PROCEDURE SECTION\n");
      exit(1);
    }

    printf(" %s \n",yytext);
    after_part(tmp_string1,yytext,' ');  // get function name
    strip_leading_blanks(tmp_string2,tmp_string1);
    before_part(tmp_string3,tmp_string2,' ');
    after_part(tmp_string4,tmp_string2,' ');  // get function name
    strip_leading_blanks(tmp_string1,tmp_string4);
    write_funnel_end();
    setup_for_prior_likelihood();

    fprintf(fall,"}\n\n%s SEPFUN4  ",tmp_string3);
    fprintf(fall,"model_parameters::%s\n{\n  "
      "lapprox->begin_separable_call_stuff();\n" ,tmp_string1);

    //fprintf(fall,"model_parameters::%s\n{\n  ",tmp_string1);
    //fprintf(fdat,"SEPFUN3 %s %s;\n",tmp_string3,tmp_string1);
    fprintf(fdat,"SEPFUN4 %s %s;\n",tmp_string3,tmp_string1);
    //fprintf(fall," PPPPPP\n");
    write_getindex_stuff(tmp_string1);
    add_references_to_user_classes(fall);
    in_aux_proc=1;
    in_funnel_proc=2;
    have_separable_function=1;
    BEGIN DEFINE_PROCS;
                              }


NORMAL_PRIOR_FUNCTION[ ]*{name}[ ]*{name}\(.*\) |
QUADRATIC_PENALTY_FUNCTION[ ]*{name}[ ]*{name}\(.*\) {
    if (!in_procedure_def)
    {
      fprintf(stderr,"Error -- FUNCTION must be used within the"
        " PROCEDURE SECTION\n");
      exit(1);
    }

    after_part(tmp_string1,yytext,' ');  // get function name
    strip_leading_blanks(tmp_string2,tmp_string1);
    before_part(tmp_string3,tmp_string2,' ');
    after_part(tmp_string4,tmp_string2,' ');  // get function name
    strip_leading_blanks(tmp_string1,tmp_string4);
    write_funnel_end();
    setup_for_prior_likelihood();

    fprintf(fall,"}\n\n%s SEPFUN1  ",tmp_string3);
    fprintf(fall,"model_parameters::%s\n{\n  "
      "begin_df1b2_funnel();\n" ,tmp_string1);
    fprintf(fdat,"SEPFUN3 %s %s;\n",tmp_string3,tmp_string1);
    add_references_to_user_classes(fall);
    in_aux_proc=1;
    in_funnel_proc=1;
    //have_separable_function=1;
    in_normal_prior_flag=1;
    BEGIN DEFINE_PROCS;
                              }

QUADPRIOR_FUNCTION[ ]*{name}[ ]*{name}\(.*\) {
    if (!in_procedure_def)
    {
      fprintf(stderr,"Error -- FUNCTION must be used within the"
        " PROCEDURE SECTION\n");
      exit(1);
    }

    after_part(tmp_string1,yytext,' ');  // get function name
    strip_leading_blanks(tmp_string2,tmp_string1);
    before_part(tmp_string3,tmp_string2,' ');
    after_part(tmp_string4,tmp_string2,' ');  // get function name
    strip_leading_blanks(tmp_string1,tmp_string4);
    write_funnel_end();
    setup_for_prior_likelihood();

    fprintf(fall,"}\n\n%s SEPFUN1  ",tmp_string3);
    fprintf(fall,"model_parameters::%s\n{\n"
      "  setup_quadprior_calcs();\n"
      "  begin_df1b2_funnel();\n" ,tmp_string1);
    fprintf(fdat,"SEPFUN3 %s %s;\n",tmp_string3,tmp_string1);
    add_references_to_user_classes(fall);
    in_aux_proc=1;
    in_funnel_proc=1;
    have_separable_function=1;
    BEGIN DEFINE_PROCS;
                              }


FUNCTION[ ]*{name} {
    if (!in_procedure_def)
    {
      fprintf(stderr,"Error -- FUNCTION must be used within the"
        " PROCEDURE SECTION\n");
      exit(1);
    }

    after_partb(tmp_string1,yytext,' ');  // get function name
    write_funnel_end();
    setup_for_prior_likelihood();

    fprintf(fall,"}\n\nvoid model_parameters::%s(void)\n{\n",tmp_string1);
    fprintf(fdat,"  void %s(void);\n",tmp_string1);

    add_references_to_user_classes(fall);

    in_aux_proc=1;
    BEGIN DEFINE_PROCS;
   /*  BEGIN DEFINE_AUX_PROC; */
                              }

FUNCTION_DECLARATION[ ]*{name}[ ]*{name}\(.*\) |
[ ]FUNCTION_DECLARATION[ ]*{name}[ ]*{name}\(.*\) {
    if (!in_procedure_def)
    {
      fprintf(stderr,"Error -- FUNCTION_DECLARATION  must be used within the"
        " PROCEDURE SECTION\n");
      exit(1);
    }

    after_part(tmp_string1,yytext,' ');  // get function name
    strip_leading_blanks(tmp_string2,tmp_string1);
    before_part(tmp_string3,tmp_string2,' ');
    after_part(tmp_string4,tmp_string2,' ');  // get function name
    strip_leading_blanks(tmp_string1,tmp_string4);
    //fprintf(fall,"}\n\n%s ",tmp_string3);
    //fprintf(fall,"model_parameters::%s\n{\n",tmp_string1);
    fprintf(fdat," %s %s;\n",tmp_string3,tmp_string1);
    add_references_to_user_classes(fall);
    in_aux_proc=1;
    BEGIN DEFINE_PROCS;
                              }


FUNCTION_DECLARATION[ ]*{name} |
[ ]FUNCTION_DECLARATION[ ]*{name} {
    if (!in_procedure_def)
    {
      fprintf(stderr,"Error -- FUNCTION_DECLARATION must be used within the"
        " PROCEDURE SECTION\n");
      exit(1);
    }

    after_partb(tmp_string1,yytext,' ');  // get function name
    //fprintf(fall,"}\n\nvoid model_parameters::%s(void)\n{\n",tmp_string1);
    fprintf(fdat,"  void %s(void);\n",tmp_string1);

    add_references_to_user_classes(fall);

    in_aux_proc=1;
    BEGIN DEFINE_PROCS;
   /*  BEGIN DEFINE_AUX_PROC; */
                              }


<DEFINE_PROCS>^[ \t].*$ {
   fprintf(fall,"%s\n",yytext);
           }



<DEFINE_AUX_PROC>^\ +{name}\ +{name}\(.*$       {

   fprintf(fall,"  %s\n",yytext);
   num_paren=count_paren(num_paren,yytext);
   printf("in define_aux_procs num_paren = %d\n",num_paren);
   if (num_paren==0)
   {
     fprintf(fhead,"%s;\n\n",yytext);
     BEGIN DEFINE_PROCS;
   }
   else
   {
     fprintf(fhead,"%s\n",yytext);
     BEGIN CONTINUE_PROTOTYPE_DEF;
   }
                              }


<CONTINUE_PROTOTYPE_DEF>^\ .*$       {

   fprintf(fall,"  %s\n",yytext);
   num_paren=count_paren(num_paren,yytext);
   printf("in continue_prorotoype_def num_paren = %d\n",num_paren);
   if (num_paren==0)
   {
     fprintf(fhead,"%s;\n\n",yytext);
     BEGIN DEFINE_PROCS;
   }
   else
   {
     fprintf(fhead,"%s\n",yytext);
   }
                              }


GLOBALS_SECTION {

    if (globals_section_defined) {
      fprintf(stderr,"Error -- there is more than 1 GLOBALS_SECTION\n");
      exit(1);
    }
    globals_section_defined=1;
    BEGIN IN_GLOBALS_SECTION;
    /*fglobals=fopen("xxglobal.tmp","w+");*/
    if (fglobals==NULL)
    {
      fprintf(stderr,"%s","Error trying to open file xxglobal.tmp\n");
    }

                }

<IN_GLOBALS_SECTION>^[ \t].*$ {

        fprintf(fglobals,"%s\n",yytext);

                              }

TOP_OF_MAIN_SECTION {

    *arglist_ptr='\0';
    if (top_of_main_defined) {
      fprintf(stderr,"Error -- there is more than 1 TOP_OF_MAIN_SECTION\n");
      exit(1);
    }
    top_of_main_defined=1;
    BEGIN IN_TOP_SECTION;
    ftopmain=fopen("xxtopm.tmp","w+");
    if (ftopmain==NULL)
    {
      fprintf(stderr,"%s","Error trying to open file xxtopmn.tmp\n");
      exit(1);
    }
    if (need_prior_globals==1)
    {
      //fprintf(ftopmain,"  df1b2_parameters * df1b2_parameters::df1b2_parameters_ptr=0;\n");
      //fprintf(ftopmain,"  model_parameters * model_parameters::model_parameters_ptr=0;\n");
      need_prior_globals=0;
    }
    fprintf(ftopmain,"  long int arrmblsize=0;\n");
    if (makedll) fprintf(ftopmain,"extern \"C\" {\n");
    if (splus_debug_flag)
    {
      if (!makegaussdll)
        fprintf(ftopmain,"\nvoid ");
      else
        fprintf(ftopmain,"\nint ");

      fprintf(ftopmain,"%s",infile_root);
      if (!makegaussdll)
        fprintf(ftopmain,"(%s,char ** dll_options);\n\n",arglist);
      else
        fprintf(ftopmain,"(%s,char * dll_options);\n\n",arglist);

      fprintf(ftopmain,"\nint main(int argc,char * argv[])\n{\n");
      fprintf(ftopmain,"  %s",infile_root);
      fprintf(ftopmain,"    ad_set_new_handler();\n");
      if (bound_flag) fprintf(ftopmain,"    ad_exit=&ad_boundf;\n");
      fprintf(ftopmain,"(%s,dll_options);\n}\n",arglist1);
    }
    if (!splus_debug_flag)
    {
      if (makedll)
      {
        if (!makegaussdll)
        {
          fprintf(ftopmain, "#ifdef _WIN32\n");
          fprintf(ftopmain, "void __stdcall __declspec(dllexport) \n");
          fprintf(ftopmain, "#else\n");
          fprintf(ftopmain, "void \n");
          fprintf(ftopmain, "#endif\n");
        }
        else
        {
          fprintf(ftopmain, "#ifdef _WIN32\n");
          fprintf(ftopmain,"\nint __stdcall __declspec(dllexport) ");
          fprintf(ftopmain, "#else\n");
          fprintf(ftopmain, "int \n");
          fprintf(ftopmain, "#endif\n");
        }
      }
      else
      {
        fprintf(ftopmain,"\nint main(int argc,char * argv[])\n{\n");
        fprintf(ftopmain,"  ad_set_new_handler();\n");
        if (bound_flag) fprintf(ftopmain,"  ad_exit=&ad_boundf;\n");
      }
    }
    else
    {
      fprintf(ftopmain,"\nvoid ");
    }
    if (makedll)
    {
      fprintf(ftopmain,"%s",infile_root);
      if (num_spargs)
      {
        if (!makegaussdll)
          fprintf(ftopmain,"(%s,char ** dll_options)\n{\n",arglist);
        else
          fprintf(ftopmain,"(%s,char * dll_options)\n{\n",arglist);
      }
      else
      {
        if (!makegaussdll)
          fprintf(ftopmain,"(%schar ** dll_options)\n{\n",arglist);
        else
          fprintf(ftopmain,"(%schar * dll_options)\n{\n",arglist);
      }
    }

                }

<IN_TOP_SECTION>^[ \t].*$ {

        fprintf(ftopmain,"%s\n",yytext);

                              }


<<EOF>>           {

    if (!data_defined)
    {
      fprintf(stderr,"Error -- Reached end-of-file without the DATA_SECTION"
        " being defined\n");
      exit(1);
    }
    if (!params_defined)
    {
      fprintf(stderr,"Error -- Reached end-of-file without the PARAMETER_SECTION"
        " being defined\n");
      exit(1);
    }
    if (!procedure_defined)
    {
      fprintf(stderr,"Error -- Reached end-of-file without the"
        " PROCEDURE_SECTION being defined\n");
      exit(1);
    }
    write_funnel_end();
    setup_for_prior_likelihood();
    //if (!in_aux_proc)
    //if (in_aux_proc)
    {
     // fprintf(fall,"}\n");
    }

    fprintf(fall,"}\n");
    fclose(fall);
    fall=fopen("xxalloc6.tmp","w+");
    if (fall==NULL)
    {
      fprintf(stderr,"%s","Error trying to open file xxalloc6.tmp\n");
    }
    if (!preliminary_calcs_defined)
    {
      fprintf(fall,"\nvoid model_parameters::preliminary_calculations(void)"
        "{");
      fprintf(fall,"%s","\n  #if defined(USE_ADPVM)\n");
      fprintf(fall,"%s","\n  admaster_slave_variable_interface(*this);\n");
      fprintf(fall,"%s","\n  #endif\n");
      fprintf(fall,"%s","\n}\n");
    }

    fprintf(fall,"\nmodel_data::~model_data()\n"
      "{");
    fprintf(fall,"}\n");
    fprintf(fall,"\nmodel_parameters::~model_parameters()\n"
      "{");
    call_destructors_for_user_classes(fall);

    if (!report_defined)
    {
      fprintf(fall,"}\n");
      fprintf(fall,"\nvoid model_parameters::report(const dvector& gradients)"
        "{");
    }

    if (!final_defined)
    {
      fprintf(fall,"}\n");
      fprintf(fall,"\nvoid model_parameters::final_calcs(void)"
        "{");
    }

    if (!runtime_defined)
    {
      fprintf(fall,"}\n");
      fprintf(fall,"%s","\nvoid model_parameters::set_runtime(void)"
        "{");
    }

    fprintf(fall,"}\n");
    fprintf(fall,"\n#ifdef _BORLANDC_\n"
                 "  extern unsigned _stklen=10000U;\n#endif\n\n");
    fprintf(fall,"\n#ifdef __ZTC__\n"
                 "  extern unsigned int _stack=10000U;\n#endif\n\n");

    if (!ftopmain)
    {
      ftopmain=fopen("xxtopm.tmp","w+");
      if (ftopmain==NULL)
      {
        fprintf(stderr,"%s","Error trying to open file xxtopmn.tmp\n");
        exit(1);
      }
      fprintf(ftopmain,"  long int arrmblsize=0;\n");
      // **********************************************************************
      // **********************************************************************
      if (makedll)
      {
        fprintf(ftopmain,"extern \"C\" {\n");
        //fprintf(ftopmain,"\nint main(int argc,char * argv[])\n{\n");
        if (splus_debug_flag)
        {
          if (!makegaussdll)
            fprintf(ftopmain,"\nvoid ");
          else
            fprintf(ftopmain,"\nint ");

          fprintf(ftopmain,"%s",infile_root);
          if (!makegaussdll)
            fprintf(ftopmain,"(%s,char ** dll_options);\n\n",arglist);
          else
            fprintf(ftopmain,"(%s,char * dll_options);\n\n",arglist);

          fprintf(ftopmain,"\nint main(int argc,char * argv[])\n{\n");
          fprintf(ftopmain,"  ad_set_new_handler();\n");
          if (bound_flag) fprintf(ftopmain,"  ad_exit=&ad_boundf;\n");
          fprintf(ftopmain,"  %s",infile_root);
          fprintf(ftopmain,"(%s,dll_options);\n}\n",arglist1);
        }
        if (!splus_debug_flag)
        {
          if (!makegaussdll)
          {
            fprintf(ftopmain, "#ifdef _WIN32\n");
            fprintf(ftopmain,"\nvoid __stdcall __declspec(dllexport) ");
            fprintf(ftopmain, "#else\n");
            fprintf(ftopmain, "void \n");
            fprintf(ftopmain, "#endif\n");
          }
          else
          {
            fprintf(ftopmain, "#ifdef _WIN32\n");
            fprintf(ftopmain,"\nint __stdcall __declspec(dllexport) ");
            fprintf(ftopmain, "#else\n");
            fprintf(ftopmain, "int \n");
            fprintf(ftopmain, "#endif\n");
          }
        }
        else
        {
          if (!makegaussdll)
            fprintf(ftopmain,"\nvoid ");
          else
            fprintf(ftopmain,"\nint ");
        }
        fprintf(ftopmain,"%s",infile_root);
        if (num_spargs)
        {
          if (!makegaussdll)
            fprintf(ftopmain,"(%s,char ** dll_options)\n{\n",arglist);
          else
            fprintf(ftopmain,"(%s,char * dll_options)\n{\n",arglist);
        }
        else
        {
          if (!makegaussdll)
            fprintf(ftopmain,"(%schar ** dll_options)\n{\n",arglist);
          else
            fprintf(ftopmain,"(%schar * dll_options)\n{\n",arglist);
        }

      }
      else
      {
        fprintf(ftopmain,"\nint main(int argc,char * argv[])\n{\n");
        fprintf(ftopmain,"  ad_set_new_handler();\n");
        if (bound_flag) fprintf(ftopmain,"  ad_exit=&ad_boundf;\n");
      }
      // **********************************************************************
      // **********************************************************************

    }
    if (talk_to_splus)
    {
      fprintf(ftopmain,"  DDEspclient ddesc;\n");
    }

    if (makedll)
    {
      if (makegaussdll)
      {
        fprintf(ftopmain,"  AD_gaussflag=1;\n");
      }
      fprintf(ftopmain,"  int argc=1;\n");
      fprintf(ftopmain,"  char **argv=0;\n");
      fprintf(ftopmain,"  try {\n");

      if (!makegaussdll)
      {
        fprintf(ftopmain,"    argv=parse_dll_options((char*)\"%s\",argc,"
          "*dll_options);\n",infile_root);
      }
      else
      {
        fprintf(ftopmain,"    argv=parse_dll_options((char*)\"%s\",argc,"
          "dll_options);\n", infile_root);
      }
      fprintf(ftopmain,"    do_dll_housekeeping(argc,argv);\n");
      //fprintf(ftopmain,"    strcpy(argv[0],\"%s\");\n",infile_root);
      //fprintf(ftopmain,"    strcat(argv[0],\".exe\");\n");

      if (num_spargs)
        fprintf(ftopmain,"    dll_args ad_dll(%s);\n",arglist1);
      else
        fprintf(ftopmain,"    dll_args ad_dll;\n");
    }
    fprintf(ftopmain,"    gradient_structure::set_NO_DERIVATIVES();\n");
    // **********************************************************************
    // **********************************************************************

    if (makedll)
    {
      fprintf(ftopmain,"    gradient_structure::set_YES_SAVE_VARIABLES_VALUES();\n"
        "      if (!arrmblsize) arrmblsize=150000;\n");

      if (!random_effects_flag)
      {
        fprintf(ftopmain,"    model_parameters mp(arrmblsize,argc,argv,ad_dll);\n"
          "    mp.iprint=10;\n");
      }
      else
      {
        fprintf(ftopmain,"    df1b2variable::noallocate=1;\n");
        fprintf(ftopmain,"    df1b2_parameters mp(arrmblsize,argc,argv,ad_dll);\n"
          "    mp.iprint=10;\n");
      }

    }
    else
    {
      fprintf(ftopmain,"    gradient_structure::set_YES_SAVE_VARIABLES_VALUES();\n"
        "      if (!arrmblsize) arrmblsize=150000;\n");
      if (!random_effects_flag)
      {
       fprintf(ftopmain,"    model_parameters mp(arrmblsize,argc,argv);\n"
         "    mp.iprint=10;\n");
      }
      else
      {
       fprintf(ftopmain,"    df1b2variable::noallocate=1;\n");
       fprintf(ftopmain,"    df1b2_parameters mp(arrmblsize,argc,argv);\n"
         "    mp.iprint=10;\n");
      }
    }


     if (random_effects_flag)
     {
       fprintf(ftopmain,"%s",
         "\n    function_minimizer::random_effects_flag=1;\n");
       fprintf(ftopmain,"    df1b2variable::noallocate=0;\n");
     }

     fprintf(ftopmain,"    mp.preliminary_calculations();\n");

     if (have_separable_function)
       fprintf(ftopmain,"    initial_df1b2params::separable_flag=1;\n");

     fprintf(ftopmain,"    mp.computations(argc,argv);\n");

    fprintf(htop,"#include <admodel.h>\n");
    fprintf(htop,"#include <contrib.h>\n\n");
    if (random_effects_flag)
    {
      fprintf(htop,"#include <df1b2fun.h>\n\n");
      fprintf(htop,"#include <adrndeff.h>\n\n");
    }

    if (bound_flag)
    {
      fprintf(htop,"  extern \"C\"  {\n");
      fprintf(htop,"    void ad_boundf(int i);\n  }\n");
    }

    if (talk_to_splus)
    {
      fprintf(htop,"#include <adsplus.h>\n\n");
    }

    if(enable_pad){
      fprintf(htop,"#include <gdbprintlib.cpp>\n\n");
    }

    if (makedll)
    {
      // make a definition file
      FILE * fd=0;
      char deffile_name[125];
      strcpy(deffile_name,infile_root);
      strcat(deffile_name,".def");
      fd=fopen("deffile_name","w");
      if (!fd)
      {
        fprintf(stderr,"Error opining file %s\n",deffile_name);
      }
      else
      {
        fprintf(fd,"LIBRARY %s\n",infile_root);
        fprintf(fd,"EXPORTS\n     %s\n",infile_root);
      }
    }

    if (makedll)
    {
      fprintf(ftopmain,"    ad_make_code_reentrant();\n");
      fprintf(ftopmain,"  }\n");

      fprintf(ftopmain,"  catch (spdll_exception spe){ \n");
      fprintf(ftopmain,"    if (ad_printf && spe.e) (*ad_printf)"
        " (\"abnormal exit from newtest\\n\");\n");
      fprintf(ftopmain,"  }\n");
      fprintf(ftopmain,"  cleanup_argv(argc,&argv);\n");
      if (makegaussdll) fprintf(ftopmain,"  return 0;\n");
      fprintf(ftopmain,"}\n");
      fprintf(ftopmain,"}\n");
      fprintf(fdat,"%s","};\n");
      *conlist_ptr='\0';
      *arglist1_ptr='\0';
      *classlist_ptr='\0';
      fprintf(fdat1,"\nclass dll_args\n{\npublic:\n%s",classlist);
      if (num_spargs)
        fprintf(fdat1,"\n dll_args(%s) : %s{}\n",arglist,conlist);
      else
        fprintf(fdat1,"\n dll_args()  {}\n");
      fprintf(fdat1,"\n};\n");
    }
    else
    {
      fprintf(ftopmain,"    return 0;\n}\n");
      fprintf(fdat,"\n};\n");
    }
    if (fdat1)
    {
      fclose(fdat1);
      fdat1=0;
    }
    //fprintf(fdat,"\n};\n");
    if (bound_flag)
    {
      fprintf(ftopmain,"\nextern \"C\"  {\n");
      fprintf(ftopmain,"  void ad_boundf(int i)\n  {\n");
      fprintf(ftopmain,"    /* so we can stop here */\n");
      fprintf(ftopmain,"    exit(i);\n  }\n}\n");
    }

    fclose(fhead);
    fclose(htop);
    fclose(fglobals);
    fclose(ftopmain);
    fclose(fdat);
    fclose(fall);

#if defined(_WIN32)
    strcpy(outcommand,"copy xxglobal.tmp + xxhtop.tmp + header.tmp "
     "+ xxalloc1.tmp + xxalloc2.tmp + xxalloc3.tmp");
    if (report_defined)
    {
      strcat(outcommand," + xxalloc4.tmp ");
    }
    if (preliminary_calcs_defined)
    {
      strcat(outcommand," + xxalloc5.tmp ");
    }
    strcat(outcommand, " + xxtopm.tmp + xxalloc6.tmp ");

    strcpy(outcommand2,"copy tfile1 + tfile2 + tfile3 +tfile4 ");


    strcpy(outcommand3a,"sed -n -f ");
    strcat(outcommand3a,dirpath);
    if (makedll==0)
      strcat(outcommand3a,"seddf1b3 tfile2 >> ");
    else
      strcat(outcommand3a,"seddf1b3dll tfile2 >> ");

    strcpy(outcommand3b,"sed -n -f ");
    strcat(outcommand3b,dirpath);
    strcat(outcommand3b,"seddf1b4 tfile4 >> ");

    strcpy(outcommand3,"sed -f ");
    strcat(outcommand3,dirpath);
    if (makedll==0)
      strcat(outcommand3,"seddf1b2 tfile2 >> ");
    else
      strcat(outcommand3,"seddf1b2dll tfile2 >> ");

    // !!!!! DF may 1 03 Is this right?
    // this
    // strcpy(outcommand6,"cat tfile4 >> ");
    // changed to
    strcpy(outcommand6,"sed -f ");
    strcat(outcommand6,dirpath);
    strcat(outcommand6,"sedf1b2d tfile4 >> ");


    strcpy(outcommand4,"sed -f ");
    strcat(outcommand4,dirpath);
    strcat(outcommand4,"sedf1b2a xxalloc3.tmp >> ");

    strcpy(outcommand5,"sed -f ");
    strcat(outcommand5,dirpath);
    strcat(outcommand5,"sedf1b2c xxalloc2.tmp >> ");
    strcpy(outcommand5b,"sed -f ");
    strcat(outcommand5b,dirpath);
    strcat(outcommand5b,"sedf1b2c2 xxalloc2.tmp >> ");
    strcpy(outcommand8,"sed -e \"  \"  tfile5 >> ");

#else
    strcpy(outcommand,"cat xxglobal.tmp   xxhtop.tmp   header.tmp "
     "  xxalloc1.tmp   xxalloc2.tmp   xxalloc3.tmp ");
    if (report_defined)
    {
      strcat(outcommand," xxalloc4.tmp");
    }
    if (preliminary_calcs_defined)
    {
      strcat(outcommand," xxalloc5.tmp");
    }
    strcat(outcommand, "  xxtopm.tmp    xxalloc6.tmp > ");

    strcpy(outcommand2,"cat tfile1  tfile2 tfile3 tfile4 > ");

    strcpy(outcommand3a,"sed -n -f ");
    strcat(outcommand3a,dirpath);
    if (makedll==0)
      strcat(outcommand3a,"seddf1b3 tfile2 >> ");
    else
      strcat(outcommand3a,"seddf1b3dll tfile2 >> ");

    strcpy(outcommand3b,"sed -n -f ");
    strcat(outcommand3b,dirpath);
    strcat(outcommand3b,"seddf1b4 tfile4 >> ");

    strcpy(outcommand3,"sed -f ");
    strcat(outcommand3,dirpath);
    if (makedll==0)
      strcat(outcommand3,"seddf1b2 tfile2 >> ");
    else
      strcat(outcommand3,"seddf1b2dll tfile2 >> ");

    // !!!!! DF may 1 03 Is this right?
    // this
    // strcpy(outcommand6,"cat tfile4 >> ");
    // changed to
    strcpy(outcommand6,"sed -f ");
    strcat(outcommand6,dirpath);
    strcat(outcommand6,"sedf1b2d tfile4 >> ");


    strcpy(outcommand4,"sed -f ");
    strcat(outcommand4,dirpath);
    strcat(outcommand4,"sedf1b2a xxalloc3.tmp >> ");

    strcpy(outcommand5,"sed -f ");
    strcat(outcommand5,dirpath);
    strcat(outcommand5,"sedf1b2c xxalloc2.tmp >> ");
    strcpy(outcommand5b,"sed -f ");
    strcat(outcommand5b,dirpath);
    strcat(outcommand5b,"sedf1b2c2 xxalloc2.tmp >> ");

    strcpy(outcommand8,"sed -e \"  \"  tfile5 >> ");

    //strcpy(outcommand,"cat xxglobal.tmp xxhtop.tmp header.tmp
    //  xxalloc1.tmp xxalloc2.tmp xxalloc3.tmp xxalloc4.tmp xxalloc6.tmp "
    //  " xxtopm.tmp > ");
#endif
    // strcpy(outcommand,"copy xxdata.tmp + header.tmp + xxalloc.tmp ");
    strcat(outcommand,outfile_name);
    if (verbosemode)
      printf("\n%s\n",outcommand);
    errcopy=system(outcommand);
    if (errcopy)
    {
      fprintf(stderr,"Error executing command %s\n",
        outcommand);
    }
    strcat(outcommand2,headerfile_name);

    if (verbosemode)
      printf("\n%s\n",outcommand2);
    errcopy=system(outcommand2);
    if (errcopy)
    {
      fprintf(stderr,"Error executing command %s\n",
        outcommand2);
    }

    if (random_effects_flag)
    {
      strcpy(outcommand7, " sed -e \" \" ");
      strcat(outcommand7,headerfile_name);
      strcat(outcommand7," >>  classdef.tmp");
      if (verbosemode)
        printf("\n%s\n",outcommand7);
      errcopy=system(outcommand7);
      if (errcopy)
      {
        fprintf(stderr,"Error executing command %s\n",
          outcommand7);
      }
    }

    if (random_effects_flag)
    {
      strcpy(outcommand7, " sed -e \" \" ");
      strcat(outcommand7," classdef.tmp > ");
      strcat(outcommand7,headerfile_name);
      if (verbosemode)
        printf("\n%s\n",outcommand7);
      errcopy=system(outcommand7);
      if (errcopy)
      {
        fprintf(stderr,"Error executing command %s\n",
          outcommand7);
      }
    }

    if (random_effects_flag  && have_classcode_tmp)
    {
      strcpy(outcommand7, " sed -e \" \" ");
      strcat(outcommand7," classcode.tmp >> ");
      strcat(outcommand7,outfile_name);
      if (verbosemode)
        printf("\n%s\n",outcommand7);
      errcopy=system(outcommand7);
      if (errcopy)
      {
        fprintf(stderr,"Error executing command %s\n",
          outcommand7);
      }
    }

    strcat(outcommand3a,headerfile_name);
    if (verbosemode)
      printf("\n%s\n",outcommand3a);
    errcopy=system(outcommand3a);
    if (errcopy)
    {
      fprintf(stderr,"Error executing command %s\n",
        outcommand3a);
    }

    strcat(outcommand3b,headerfile_name);
    if (verbosemode)
      printf("\n%s\n",outcommand3b);
    errcopy=system(outcommand3b);
    if (errcopy)
    {
      fprintf(stderr,"Error executing command %s\n",
        outcommand3b);
    }

    strcat(outcommand3,headerfile_name);
    if (verbosemode)
      printf("\n%s\n",outcommand3);
    errcopy=system(outcommand3);
    if (errcopy)
    {
      fprintf(stderr,"Error executing command %s\n",
        outcommand3);
    }

    strcat(outcommand6,headerfile_name);
    if (verbosemode)
      printf("\n%s\n",outcommand6);
    errcopy=system(outcommand6);
    if (errcopy)
    {
      fprintf(stderr,"Error executing command %s\n",
        outcommand6);
    }
    strcat(outcommand4,outfile_name);
    if (verbosemode)
      printf("\n%s\n",outcommand4);
    errcopy=system(outcommand4);
    if (errcopy)
    {
      fprintf(stderr,"Error executing command %s\n",
        outcommand4);
    }

    strcat(outcommand5b,outfile_name);
    if (verbosemode)
      printf("\n%s\n",outcommand5b);
    errcopy=system(outcommand5b);
    if (errcopy)
    {
      fprintf(stderr,"Error executing command %s\n",
        outcommand5b);
    }
    strcat(outcommand5,outfile_name);
    if (verbosemode)
      printf("\n%s\n",outcommand5);
    errcopy=system(outcommand5);
    if (errcopy)
    {
      fprintf(stderr,"Error executing command %s\n",
        outcommand5);
    }

    if (makedll)
    {
      strcat(outcommand8,headerfile_name);
      if (verbosemode)
        printf("\n%s\n",outcommand8);
      errcopy=system(outcommand8);
      if (errcopy)
      {
        fprintf(stderr,"Error executing command %s\n",
          outcommand8);
      }
    }
    if (!errcopy)
    {
        unlink("classdef.tmp");
        unlink("xxdata.tmp");
        unlink("xxhtop.tmp");
        unlink("xxhtopm.tmp");
        unlink("xxglobal.tmp");
        unlink("xxtopm.tmp");
        unlink("xxalloc.tmp");
        unlink("xxalloc1.tmp");
        unlink("xxalloc2.tmp");
        unlink("xxalloc3.tmp");
        unlink("xxalloc4.tmp");
        unlink("xxalloc5.tmp");
        unlink("xxalloc6.tmp");
        unlink("header.tmp");
        unlink("tfile1");
        unlink("tfile2");
        unlink("tfile3");
        unlink("tfile4");
        if (makedll)
        {
          unlink("tfile5");
        }
    }
    else
    {
      fprintf(stderr,"Error trying to create output file %s\n",
        outfile_name);
    }
    if (!random_effects_flag)
    {
      fprintf(stderr,"%s"," WARNING !!! No random effects vector defined "
        "in this TPL file\n");
    }
    exit(0);
                  }


%%

int check_for_blanks(const char * s)
{
  int bflag=0;
  int i;
  for (i=0;i<strlen(s);i++)
  {
    if (s[i]==' ')
    {
      bflag=1;
      break;
    }
  }
  return bflag;
}

int option_match(int argc,char * argv[], char * string);

unsigned _stklen = 16000;
char * get_directory_name(const char * s)
{
  char * path;
  char quote[]="\"";
  char eol[]="\0";
  int bflag=0;
  int i,j;
  char* path1=getenv("ADMB_HOME");
  /* char sed_file_separator='/'; */
#if defined(_WIN32)
  char file_separator='\\';
  char file_separator_string[]="\\";
#else
  char file_separator='/';
  char file_separator_string[]="/";
#endif
  if (path1 == NULL)
  {
    //ADMB_HOME contains sed scripts needed for parsers.
    printf("ADMB_HOME environment string is not set\n");
    exit(1);
/*
    len=strlen(s);
    for (i=1;i<=len;i++)
    {
      if (s[len-i]==file_separator) break;
    }
    path = (char*) malloc(sizeof(char*)*(len-i+2));
    for (j=0;j<=len-i;j++)
    {
      path[j]=s[j];
    }
    path[len-i+1]=0;
*/
  }
  else
  {
    bflag=check_for_blanks(path1);
    size_t len = strlen(path1);
    path = (char*)malloc((len + 9) * sizeof(char*));
    if (path1[len-1]==file_separator)
    {
      if (bflag==0)
      {
        strcpy(path,path1);
      }
      else
      {
        strcpy(path,quote);
        strcat(path,path1);
        strcat(path,file_separator_string);
        strcat(path,quote);
        len+=2;
      }
      strcat(path,"bin");
      strcat(path, file_separator_string);
      strcat(path, eol);
    }
    else
    {
      if (bflag==0)
      {
        strcpy(path,path1);
      }
      else
      {
        strcpy(path,quote);
        strcat(path,path1);
        strcat(path,quote);
        len+=2;
      }
      path[len]=file_separator;
      path[len+1]=0;
      strcat(path,"bin");
      path[len+4]=file_separator;
      path[len+5]=0;
    }
  }
  return path;
}

void check_random_effects_ordering(void)
{
  if (random_effects_flag==1)
  {
    fprintf(stderr,"Error in PARAMETER_SECTION at line");
    fprintf(stderr," %d \n",nline);
    fprintf(stderr,"Random effects objects must be declared after all other"
       " initial objects.\n");
    exit(1);
  }
}

int main(int argc, char * argv[])
{
  FILE * f1=NULL;
  int ioff=argc-1;
  int on=0;
  dirpath= get_directory_name(argv[0]);
  if (verbosemode)
    printf(" dirpath = %s\n",dirpath);
  //printf(" PATH= %s\n",getenv("PATH"));
  //if ( (on=option_match(argc,argv,"-bounds"))>-1)
  {
    bound_flag=1;
  }
  if ( (on=option_match(argc,argv,"-v"))>-1)
  {
    verbosemode=1;
  }
  if ( (on=option_match(argc,argv,"-dll"))>-1)
  {
    makedll=1;
  }
  if ( (on=option_match(argc,argv,"-gaussdll"))>-1)
  {
    makedll=1;
    makegaussdll=1;
  }
  if ( (on=option_match(argc,argv,"-debug"))>-1)
  {
    splus_debug_flag = 0;
    enable_pad = 1;
  }
  if ( (on=option_match(argc,argv,"-no_pad"))>-1)
  {
    no_userclass=1;
  }
  if (argc>1)
  {
    size_t len = strlen(argv[ioff]);
    if (len + 5 > 1000)
    {
      fprintf(stderr,"Error:%s exceeds sizeof infile_name[1000].\n", argv[ioff]);
      exit(1);
    }
    if (len + 5 > 125)
    {
      fprintf(stderr,"Error:%s exceeds sizeof deffile_name[1000].\n", argv[ioff]);
      exit(1);
    }
    strcpy(infile_name,argv[ioff]);
    strcpy(deffile_name,argv[ioff]);
    strcpy(infile_root,infile_name);
    strcpy(outfile_name,argv[ioff]);
    strcpy(headerfile_name,argv[ioff]);
    strcpy(headerfile_name2,argv[ioff]);
    strcat(infile_name,".tpl");
    strcat(outfile_name,".cpp");
    strcat(headerfile_name,".htp");
    strcat(deffile_name,".def");
    strcat(headerfile_name2,"2.htp");
    if (debug_flag) fprintf(stderr,"Trying to open file %s for input\n", infile_name);
    yyin=fopen(infile_name,"r");
    if (!yyin)
    {
      fprintf(stderr,"Error trying to open input file %s\n",
        infile_name);
      exit(1);
    }
    if (debug_flag) fprintf(stderr,"Opened file %s for input\n", infile_name);
    if (makedll)
    {
      if (len + 5 > MAX_TMP_STRING)
      {
        fprintf(stderr,"Error:%s exceeds MAX_TMP_STRING.\n", argv[ioff]);
        exit(1);
      }
      else
      {
        strcpy(tmp_string1,argv[ioff]);
        strcat(tmp_string1,".def");
        f1=fopen(tmp_string1,"w");
        fprintf(f1,"LIBRARY %s\n\n",argv[ioff]);
        fprintf(f1,"EXPORTS\n");
        fprintf(f1,"\t%s\n",argv[ioff]);
        fclose(f1);
        f1=NULL;
      }
    }
  }
  else
  {
    strcpy(infile_name,"admodel.tpl");
    strcpy(outfile_name,"admodel.cpp");
    if (debug_flag) fprintf(stderr,"Trying to open file %s for input\n", infile_name);
    yyin=fopen(infile_name,"r");
    if (!yyin)
    {
      fprintf(stderr,"Error trying to open default input file %s\n",
        infile_name);
      exit(1);
    }
    if (debug_flag) fprintf(stderr,"Opened file %s for input\n", infile_name);
  }
  conlist_ptr=&(conlist[0]);
  classlist_ptr=&(classlist[0]);
  arglist_ptr=&(arglist[0]);
  arglist1_ptr=&(arglist1[0]);


  htop=fopen("xxhtop.tmp","w+");
  if (htop==NULL)
  {
    fprintf(stderr,"Error trying to open file %s\n","xxhtop.tmp");
  }
  fglobals=fopen("xxglobal.tmp","w+");
  if (fglobals==NULL)
  {
    fprintf(stderr,"Error trying to open file %s\n","xxglobal.tmp");
  }
  //fdat=fopen(headerfile_name,"w+");
  fdat=fopen("tfile1","w+");
  if (fdat==NULL)
  {
    fprintf(stderr,"Error trying to open file tfile1\n");
  }
  if (makedll)
  {
    fdat1=fopen("tfile5","w+");
    if (fdat1==NULL)
    {
      fprintf(stderr,"Error trying to open file tfile1\n");
    }
  }
  fall=fopen("xxalloc1.tmp","w+");
  if (fall==NULL)
  {
    fprintf(stderr,"%s","Error trying to open file xxalloc1.tmp\n");
  }
  fprintf(fall,"#include <%s>\n\n",headerfile_name);
  fprintf(fall,"  df1b2_parameters * df1b2_parameters::df1b2_parameters_ptr=0;\n");
  fprintf(fall,"  model_parameters * model_parameters::model_parameters_ptr=0;\n");
  fhead=fopen("header.tmp","w+");
  if (fhead==NULL)
  {
    fprintf(stderr,"%s","Error trying to open file header.tmp\n");
  }
  yylex();
  if (fs)
  {
    fclose(fs);
    fs=0;
  }
  return 0;
}

char * before_part(char * d, char * s, char c)
{
  int ipos=0;
  int i=0;
  int iflag=0;
  if (strlen(s) > MAX_TMP_STRING)
  {
    fprintf(stderr,"%s","string passed to before_part is too long\n");
    exit(1);
  }
  for (i=0;i<strlen(s);i++)
  {
    if (s[i]==c)
    {
      ipos=i;
      iflag=1;
      break;
    }
  }
  if (ipos)
  {
    for (i=0;i<ipos;i++)
    {
      d[i]=s[i];
    }
    d[ipos]='\0';
  }
  return d;
}

char * before_partb(char * d, char * s, char c)
{
  int ipos=0;
  int i=0;
  int iflag=0;
  if (strlen(s) > MAX_TMP_STRING)
  {
    fprintf(stderr,"%s","string passed to before_part is too long\n");
    exit(1);
  }
  for (i=strlen(s)-1;i>=1;i--)
  {
    if (s[i]==c)
    {
      ipos=i;
      iflag=1;
      break;
    }
  }
  if (ipos)
  {
    for (i=0;i<ipos;i++)
    {
      d[i]=s[i];
    }
    d[ipos]='\0';
  }
  return d;
}

char * after_part(char * d, char * s, char c)
{
  int ipos=0;
  int i=0;
  int iflag=0;
  if (strlen(s) > MAX_TMP_STRING)
  {
    fprintf(stderr,"%s","string passed to before_part is too long\n");
    exit(1);
  }
  for (i=0;i<strlen(s);i++)
  {
    if (s[i]==c)
    {
      ipos=i;
      iflag=1;
      break;
    }
  }
  if(iflag)
  {
    for (i=ipos;i<strlen(s);i++)
    {
      d[i-ipos]=s[i];
    }
    d[strlen(s)-ipos]='\0';
  }
  return d;
}

char * strict_after_part(char * d, char * s, char c)
{
  int ipos=0;
  int i=0;
  int iflag=0;
  if (strlen(s) > MAX_TMP_STRING)
  {
    fprintf(stderr,"%s","string passed to before_part is too long\n");
    exit(1);
  }
  for (i=0;i<strlen(s);i++)
  {
    if (s[i]==c)
    {
      ipos=i;
      iflag=1;
      break;
    }
  }
  if(iflag)
  {
    for (i=ipos+1;i<strlen(s);i++)
    {
      d[i-ipos-1]=s[i];
    }
    d[strlen(s)-ipos-1]='\0';
  }
  return d;
}
char * after_partb(char * d, char * s, char c)
{
  int ipos=0;
  int i=0;
  int iflag=0;
  if (strlen(s) > MAX_TMP_STRING)
  {
    fprintf(stderr,"%s","string passed to before_part is too long\n");
    exit(1);
  }
  for (i=strlen(s)-1;i>=0;i--)
  {
    if (s[i]==c)
    {
      ipos=i+1;
      iflag=1;
      break;
    }
  }
  if(iflag)
  {
    for (i=ipos;i<strlen(s);i++)
    {
      d[i-ipos]=s[i];
    }
    d[strlen(s)-ipos]='\0';
  }
  else
  {
    d[0]='\0';
  }
  return d;
}

char * strip_leading_blanks(char * d, char * s)
{
  int start_flag=0;
  int j=0;
  int i=0;
  if (strlen(s) > MAX_TMP_STRING)
  {
    fprintf(stderr,"%s","string passed to before_part is too long\n");
    exit(1);
  }
  for (i=0;i<strlen(s);i++)
  {
    if (!start_flag)
    {
      if (s[i]!=' ')
      {
        start_flag=1;
        d[j++]=s[i];
      }
    }
    else
    {
      d[j++]=s[i];
    }
  }
  d[j]='\0';
  return d;
}

char * strip_leading_blanks_and_tabs(char * d, char * s)
{
  int start_flag=0;
  int j=0;
  int i=0;
  if (strlen(s) > MAX_TMP_STRING)
  {
    fprintf(stderr,"%s","string passed to before_part is too long\n");
    exit(1);
  }
  for (i=0;i<strlen(s);i++)
  {
    if (!start_flag)
    {
      if (s[i]!=' ' && s[i]!='\t')
      {
        start_flag=1;
        d[j++]=s[i];
      }
    }
    else
    {
      d[j++]=s[i];
    }
  }
  d[j]='\0';
  return d;
}

int count_paren(int num_paren,char * yytext)
{
  int i;
  for (i=0;i<=strlen(yytext);i++)
  {
    if (yytext[i]=='(')
    {
      num_paren++;
    }
    if (yytext[i]==')')
    {
      num_paren--;
    }
  }
  return num_paren;
}

void add_references_to_user_classes(FILE * fall)
{
  int i;
  if (!no_userclass)
  {
    if (num_user_classes)
    {
      for (i=0;i<=num_user_classes-1;i++)
        fprintf(fall,"  %s;\n",reference_statements[i]);
    }
  }
}

void call_destructors_for_user_classes(FILE * fall)
{
  int i;
  if (num_user_classes)
  {
    fprintf(fall,"\n");
    for (i=0;i<=num_user_classes-1;i++)
    {
      fprintf(fall,"  delete pad_%s;\n",class_instances[i]);
      fprintf(fall,"  pad_%s = NULL;\n",class_instances[i]);
    }
  }
}
void initialize(char *s)
{
  s[0]='\0';
}

void marker(void){;}

 void write_funnel_end(void)
 {
   switch (in_funnel_proc)
   {
   case 0:
     break;
   case 1:
     fprintf(fall,"  end_df1b2_funnel();\n");
     break;
   case 2:
     fprintf(fall,"  lapprox->end_separable_call_stuff();\n");
     break;
   default:
      fprintf(stderr,"illegal value for in_funnel_proc\n");
      exit(1);
   }
   in_funnel_proc=0;
 }

 int option_match(int argc,char * argv[], char * string)
 {
   int rval=-1;
   int i=0;
   for (i=0;i<argc;i++)
   {
     if (!strcmp(argv[i],string))
     {
       rval=i;
       break;
     }
   }
   return rval;
 }

 void write_unallocated(const char * t)
 {
   fprintf(stderr,"warning -- creating unallocated %s at line %d\n",t,
     nline);
 }
void  get_next_argument(char * buffer,char * arg)
{
  int ii;
  int len;
  char * tptr;
  char * ptr;
  char * argend;
  char * argbegin;
  arg[0]='\0';
  len=strlen(buffer);
  if (len==0)
    return;
  ptr=buffer+len-1;
  while(*ptr == ' ')
  {
    if (ptr<=buffer) break;
    ptr--;
  }
  argend=ptr;
  while(*ptr !=' ' && *ptr != '&')
  {
    if (ptr<=buffer) break;
    ptr--;
  }
  argbegin=ptr+1;
  ii=0;
  for (tptr=argbegin;tptr<=argend;tptr++)
  {
    arg[ii++]=*tptr;
    if (ii>1000)
    {
      printf("Overflow error in get_next_argument\n");
      exit(1);
    }
  }
  arg[ii]='\0';
  while(*ptr !=',' && *ptr != '(')
  {
    if (ptr<=buffer) break;
    ptr--;
  }
  *ptr='\0';
}
void write_getindex_stuff(char *str)
{
  /* char * argptr; */
  int paren_level=0;
  char * last_paren;
  char * first_paren;
  char buffer[10001];
  char function_arg[1001];
  printf(" %s \n",str);
  first_paren=strchr(str,'(');
  if (first_paren==0)
  {
    printf("Error in write_getindex_stuff\n");
    exit(1);
  }
  strncpy(buffer,first_paren+1,10000);
  last_paren=strrchr(buffer,')');
  if (last_paren==0)
  {
    printf("Error in write_getindex_stuff\n");
    exit(1);
  }
  else
  {
    *(last_paren)='\0';
    paren_level=1;
  }
  do
  {
    get_next_argument(buffer,&(function_arg[0]));
    if (strlen(function_arg)==0) break;
    fprintf(fall,"  ADMB_getcallindex(%s);\n",function_arg);
  }
  while(1);
  // XNESTED
}

void print_quadratic_random_effect_penalty_class(char *text)
{
  if (class_append_flag==0)
  {
    if(fs==0)
    {
      fs=fopen("classdef.tmp","w+");
    }

    if(fs1==0)
    {
      fs1=fopen("classcode.tmp","w+");
      have_classcode_tmp=1;
    }
  }
  else
  {
    if(fs==0)
    {
      fs=fopen("classdef.tmp","a+");
    }

    if(fs1==0)
    {
      fs1=fopen("classcode.tmp","a+");
      have_classcode_tmp=1;
    }
  }

  if (quadratic_classprint_flag==1)
  {
    fprintf(fs,"AAA\n");

    fprintf(fs,"\nclass df1b2quadratic_re_penalty_%s : "
      "public df1b2quadratic_re_penalty\n"
    "{\n"
    "public:\n"
    "  void get_Lxu(dmatrix& M);\n"
    "  void get_cM(void);\n"
    "  void operator = (const df1b2matrix & M)\n"
    "  {\n"
    "    df1b2quadratic_re_penalty::operator = (M);\n"
    "  }\n"
    "};\n",text);
    fprintf(fs,"\nclass quadratic_re_penalty_%s : "
      "public quadratic_re_penalty\n"
    "{\n"
    "public:\n"
    "  void get_cM(void);\n"
    "  void operator = (const dvar_matrix & M)\n"
    "  {\n"
    "    quadratic_re_penalty::operator = (M);\n"
    "  }\n"
    "};\n",text);
  }
  if (quadratic_classprint_flag==2)
  {
    if (in_normal_prior_flag==1)
    {
      fprintf(fs,"\nclass df1b2_normal_prior_%s : ",text);
      //in_normal_prior_flag=0;
    }
    else
    {
      fprintf(fs,"\nclass df1b2_normal_prior_%s : ",text);
      //fprintf(fs,"\nclass df1b2quadratic_re_penalty_%s : ",text);
    }
    fprintf(fs,"public df1b2quadratic_re_penalty\n"
    "{\n"
    "public:\n"
    "  void get_Lxu(dmatrix& M);\n"
    "  df1b2_normal_prior_%s(){old_style_flag=0;}\n"
    "  void get_cM(void);\n"
    "  void operator = (const df1b2matrix & M)\n"
    "  {\n"
    "    df1b2quadratic_re_penalty::operator = (M);\n"
    "  }\n"
    "};\n",text);
    fprintf(fs,"\nclass df_normal_prior_%s : "
      "public quadratic_re_penalty\n"
    "{\n"
    "public:\n"
    "  df_normal_prior_%s(){old_style_flag=0;}\n"
    "  void get_cM(void);\n"
    "  void operator = (const dvar_matrix & M)\n"
    "  {\n"
    "    quadratic_re_penalty::operator = (M);\n"
    "  }\n"
    "};\n",text,text);


    /*
     fprintf(fs1,"\nvoid df1b2quadratic_re_penalty_%s::get_Lxu(dmatrix& LXU)\n"
    */
    fprintf(fs1,"\nvoid df1b2_normal_prior_%s::get_Lxu(dmatrix& LXU)\n"
    "{\n"
     "  df1b2_parameters * mp=\n"
     "    df1b2_parameters::get_df1b2_parameters_ptr();\n"
     "  mp->evaluate_M();\n"
     "  int rmin=Lxu->indexmin();\n"
     "  int rmax=Lxu->indexmin();\n"
     "  int cmin=1;\n"
     "  int cmax=(*Lxu)(rmin).indexmax();\n"
     "  if (cmax != LXU.indexmax())\n"
     "  {\n"
     "    cerr << \"Shape error in get_Lxu\" << endl;\n"
     "    ad_exit(1);\n"
     "  }\n"
     "  \n"
     "  for (int i=rmin;i<=rmax;i++)\n"
     "  {\n"
     "    int row = (int)((*Lxu)(i,0));\n"
     "    for (int j=cmin;j<=cmax;j++)\n"
     "    {\n"
     "      LXU(j,row)+=(*Lxu)(i,j);\n"
     "    }\n"
     "  }\n"
     "}\n",text);
     fprintf(fs1,"\nvoid df_normal_prior_%s::get_cM(void)\n"
     "{\n"
     "  model_parameters * mp=\n"
     "    model_parameters::get_model_parameters_ptr();\n"
     "  mp->evaluate_M();\n"
     "}\n",text);
  }

  if (quadratic_classprint_flag==3)
  {
    if (in_normal_prior_flag==1)
    {
      fprintf(fs,"\nclass df1b2_normal_prior_%s : ",text);
      //in_normal_prior_flag=0;
    }
    else
    {
      fprintf(fs,"\nclass df1b2_normal_prior_%s : ",text);
      //fprintf(fs,"\nclass df1b2quadratic_re_penalty_%s : ",text);
    }
    fprintf(fs,"public df1b2quadratic_re_penalty\n"
    "{\n"
    "public:\n"
    "  void get_Lxu(dmatrix& M);\n"
    "  df1b2_normal_prior_%s(){old_style_flag=2;}\n"
    "  void get_cM(void);\n"
    "  void operator = (const df1b2matrix & M)\n"
    "  {\n"
    "    df1b2quadratic_re_penalty::operator = (M);\n"
    "  }\n"
    "};\n",text);
    fprintf(fs,"\nclass df_normal_prior_%s : "
      "public quadratic_re_penalty\n"
    "{\n"
    "public:\n"
    "  df_normal_prior_%s(){old_style_flag=2;}\n"
    "  void get_cM(void);\n"
    "  void operator = (const dvar_matrix & M)\n"
    "  {\n"
    "    quadratic_re_penalty::operator = (M);\n"
    "  }\n"
    "};\n",text,text);


    /*
     fprintf(fs1,"\nvoid df1b2quadratic_re_penalty_%s::get_Lxu(dmatrix& LXU)\n"
    */
    fprintf(fs1,"\nvoid df1b2_normal_prior_%s::get_Lxu(dmatrix& LXU)\n"
    "{\n"
     "  df1b2_parameters * mp=\n"
     "    df1b2_parameters::get_df1b2_parameters_ptr();\n"
     "  mp->evaluate_M();\n"
     "  int rmin=Lxu->indexmin();\n"
     "  int rmax=Lxu->indexmin();\n"
     "  int cmin=1;\n"
     "  int cmax=(*Lxu)(rmin).indexmax();\n"
     "  if (cmax != LXU.indexmax())\n"
     "  {\n"
     "    cerr << \"Shape error in get_Lxu\" << endl;\n"
     "    ad_exit(1);\n"
     "  }\n"
     "  \n"
     "  for (int i=rmin;i<=rmax;i++)\n"
     "  {\n"
     "    int row=(*Lxu)(i,0);\n"
     "    for (int j=cmin;j<=cmax;j++)\n"
     "    {\n"
     "      LXU(j,row)+=(*Lxu)(i,j);\n"
     "    }\n"
     "  }\n"
     "}\n",text);
     fprintf(fs1,"\nvoid df_normal_prior_%s::get_cM(void)\n"
     "{\n"
     "  model_parameters * mp=\n"
     "    model_parameters::get_model_parameters_ptr();\n"
     "  mp->evaluate_M();\n"
     "}\n",text);
  }

  quadratic_classprint_flag=0;

  if (fs)
  {
    fclose(fs);
  }
  fs=0;
  if (fs1)
  {
    fclose(fs1);
  }
  fs1=0;
  class_append_flag=1;
}

  /* add prior to userfunctions from procedure_section,
  */
  void add_prior_to_objective(void)
  {
	  prior_done_once=1;priors_done=1;
	  procedure_done=1;
	  fprintf(fdat,"  void priorsfunction(void);\n");  //add to .htp file
	  //fprintf(fall,"%s","  prior_function_value=0.0;\n");
      fprintf(fall,"%s","  priorsfunction();\n");
      //fprintf(fall,"%s%s%s","  ",objective_function_name_string,"+=prior_function_value;\n");
  }



  /* add likelihood function value to userfunctions from procedure_section,
  */
  void add_likelihood_to_objective(void)
  {
	  likelihood_done_once=1;likelihood_done=1;
	  procedure_done=1;
	  fprintf(fdat,"  void likelihoodfunction(void);\n");  //add to .htp file
	  //fprintf(fall,"%s","  likelihood_function_value=0.0;\n");
      fprintf(fall,"%s","  likelihoodfunction();\n");
      //fprintf(fall,"%s%s%s","  ",objective_function_name_string,"+=likelihood_function_value;\n");
  }



  /* reset some control variable for prior and likelihood section, this will be repeated on multiple other sections,
  * so we organize them as a function
  */
  void setup_for_prior_likelihood(void)
  {
	if(priors_defined) priors_done=1;
	if(likelihood_defined) likelihood_done=1;
	if((procedure_defined)&&(!priors_defined)&&(!likelihood_defined)) procedure_done=1;
	if((procedure_defined)&&(priors_defined)&&(!prior_done_once)) add_prior_to_objective();
	if((procedure_defined)&&(likelihood_defined)&&(!likelihood_done_once)) add_likelihood_to_objective();
  }


 /* strip off the leading and trailing spaces from an input string, call it by trim(istring),
    istring still use the same memory address, but the values being changed due to removed spaces,
    used to compare the function name for prior_section
 */
 void trim(char * a)
 {
	  size_t walker = strlen ( a );
    //printf ( "Before: |%s|\n\n", a );

    /* Trim trailing spaces */
    while ( walker > 0 && isspace ( a[walker - 1] ) )
      --walker;
    a[walker] = '\0';

    //printf ( "Trailing: |%s|\n\n", a );

    /* Trim leading spaces */
    walker = strspn ( a, " \t\n\v" );
    memmove ( a, a + walker, strlen ( a + walker ) + 1 );
 }



 /* check the prior from parameter lists or not, if found it, return 0, ow return 1
    not care about the position,
    it looks complicate because the prior has wider pattern than parameter,
    such as for parameter a, we may get -log(a), or a(i) for its prior, so we need to tell if
    this prior come from parameter a,
 */
 int prior_check(char * parameter, char * prior)
 {
   if(strlen(parameter)==strlen(prior))
     return strcmp(parameter,prior); //0 is founded
   else if (strlen(parameter)<strlen(prior))
   {
     int i=0;
     int j=0;
     int cnt=0;
     int start_flag=0;
     for(i=0;i<strlen(prior);i++)
     {
       //printf("%d,%s,%s\n",i,parameter, prior);
       if(prior[i]==parameter[j]) { //found match
         cnt++;
         if(i==0) start_flag=1;
         if(cnt<strlen(parameter)) j++;
         //printf("* i=%d, cnt=%d, j=%d , flag=%d \n",i,cnt, j,start_flag);
         if(i==(strlen(prior)-1) && cnt==strlen(parameter) && start_flag)//only return for the last found match
           return 0; //found it
       }
       else{ //not match
         if(cnt==strlen(parameter)) {//take care for special character for not matched one
           if(!isalnum(prior[i]) && start_flag)  return 0; //found it
         }
         if(!isalnum(prior[i])) start_flag=1;
         else start_flag=0;
         cnt=0;j=0;
         //printf("** i=%d, cnt=%d, j=%d , flag=%d \n",i,cnt, j,start_flag);
       }
       if(i==(strlen(prior)-1) && cnt<strlen(parameter)) return 1; //until the end still not found
     } //end for loop
   }
   return 1; //not found
 }
