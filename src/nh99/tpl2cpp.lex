%option noyywrap

%{
  /**
   *
   * $Id: tpl2cpp.lex 945 2011-01-12 23:03:57Z johnoel $
   *
   * Author: David Fournier
   * Copyright (c) 2008-2012 Regents of the University of California
   */

  #define   MAX_TMP_STRING  501
  #define   MAX_USER_CLASSES  501
  #define   MAX_USER_CLASSNAME_LENGTH  251
  #define   MAX_PRIOR_CHECK  1000
  #define   MAX_LIKE_CHECK  2000
  #include <stdlib.h>
  #include <string.h>
  #include <stdio.h>
  #if defined(_WIN32)
  #include <io.h>  //fopen
  #endif
  #include <ctype.h> /* isalnum */
  char tmp_string[MAX_TMP_STRING];
  char tmp_string1[MAX_TMP_STRING];
  char tmp_string2[MAX_TMP_STRING];
  char tmp_string3[MAX_TMP_STRING];
  char tmp_string4[MAX_TMP_STRING];
  char tmp_string5[MAX_TMP_STRING];
  char objective_function_name_string[MAX_TMP_STRING];
  char reference_statements[MAX_USER_CLASSES][MAX_USER_CLASSNAME_LENGTH];

  char class_instances[MAX_USER_CLASSES][MAX_USER_CLASSNAME_LENGTH];
  char outcommand[100];
  char infile_name[1000];
  char infile_root[1000];
  char name_string[100];
  char outfile_name[1000];
  char headerfile_name[100];


  int  num_spargs=0;
  int  pvmslaves_defined=0;
  int splus_debug_flag=0;
  int enable_pad =0;
  int  spnumber_flag=0;
  int data_defined=0;
  int in_define_data=0;
  int debug_flag=0;
  int makedll=0;
  int makegaussdll=0;
  int no_userclass=0;
  int bound_flag=1;
  int num_user_classes=0;
  int final_defined=0;
  int top_of_main_defined=0;
  int globals_section_defined=0;
  int in_define_parameters=0;
  int talk_to_splus=0;
  int initialization_defined=0;

  int priors_defined=0;
  int prior_done_once=0;
  int likelihood_defined=0;
  int likelihood_done_once=0;
  int procedure_done=0;
  int likelihood_done=0;
  int priors_done=0;
  int prior_function_toggle=0;
  char prior_checker[MAX_PRIOR_CHECK][100];//container hold all parameters which being used for check the prior
  int prior_counter=0; //index for prior_checker
  int prior_found=0;
  char likelihood_checker[MAX_LIKE_CHECK][100];
  int likelihood_counter=0; //index for likelihood_checker
  int likelihood_found=0;

  int objective_function_defined=0;
  int report_defined=0;
  int preliminary_calcs_defined=0;
  int between_phases_defined=0;
  int needs_initialization=0;
  int errcopy=1;
  int params_defined=0;
  int runtime_defined=0;
  int procedure_defined=0;
  int in_procedure_def=0;
  int in_aux_proc=0;
  int nline=1;
  int have_likeprof=0;
  int num_paren=0;
  int nchar=0;
  int warn_unallocated=1;
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
  FILE * htop=NULL;
  FILE * fall=NULL;
  FILE * fhead=NULL;
  FILE * fglobals=NULL;
  FILE * ftopmain=NULL;
  void initialize(char *);
  char * before_part(char * d, char * s, char c);
  char * before_partb(char * d, char * s, char c);
  char * strict_after_part(char * d, char * s, char c);
  char * after_part(char * d, char * s, char c);
  char * after_partb(char * d, char * s, char c);
  char * strip_leading_blanks(char * d, char * s);
  char * strip_leading_blanks_and_tabs(char * d, char * s);

  int count_paren(int num_paren,char * yytext);
  void add_references_to_user_classes(FILE * fall);
  void call_destructors_for_user_classes(FILE * fall);
  void marker(void);
  void write_unallocated(const char *);

  void add_prior_to_objective(void);
  void add_likelihood_to_objective(void);
  void setup_for_prior_likelihood(void);
  void trim(char * a);
  int prior_check(char * parameter, char * prior);

  int filename_index;
  int filename_size;
%}

filename \"[^\"]*\"
filenamesingle \'[^\']*\'

name [a-z_A-Z]+(->)?[a-z_A-Z0-9]*

num_exp [a-z_A-Z0-9\+\-\*\/]+

index ([a-z_A-Z]+(->)?[a-z_A-Z0-9]*)|([a-z_A-Z0-9\+\-\*\/]+)

float_num_exp [a-z_A-Z0-9\.\+\-\*]+

prior_name [ \t(a-z_A-Z]+(->)?[ \ta-z_A-Z0-9(),.-]*
prior_def [ \t(a-z_A-Z0-9-]+(->)?[ \ta-z_A-Z0-9),.-]*

%s DEFINE_DATA DEFINE_PARAMETERS DEFINE_PROCS DEFINE_PROCS2 IN_DATA_DEF IN_PARAM_DEF
%s IN_NUMBER_DEF IN_NUMBER_DEF2 IN_SPNUMBER_DEF IN_VECTOR_DEF IN_VECTOR_VECTOR_DEF
%s IN_SPVECTOR_DEF IN_TABLE_DEF IN_FACTOR_DEF
%s IN_MATRIX_DEF IN_SPMATRIX_DEF IN_THREE_ARRAY_DEF IN_SPTHREE_ARRAY_DEF
%s IN_NAMED_NUMBER_DEF IN_NAMED_VECTOR_DEF IN_NAMED_MATRIX_DEF
%s IN_NAMED_THREE_ARRAY_DEF IN_NAMED_FOUR_ARRAY_DEF DEFINE_AUX_PROC
%s INIT_BOUNDED_NUMBER_DEF INIT_BOUNDED_VECTOR_DEF IN_BOUNDED_MATRIX_DEF
%s DEFINE_INITIALIZATION DEFINE_PRELIMINARY_CALCS INIT_BOUNDED_MATRIX_DEF
%s CONTINUE_PROTOTYPE_DEF DEFINE_RUNTIME IN_FOUR_ARRAY_DEF IN_LOCAL_CALCS
%s IN_GLOBALS_SECTION IN_TOP_SECTION INIT_BOUNDED_THREE_ARRAY_DEF
%s DEFINE_BETWEEN_PHASES IN_FIVE_ARRAY_DEF IN_SIX_ARRAY_DEF IN_SEVEN_ARRAY_DEF
%s IN_NAMED_FIVE_ARRAY_DEF IN_NAMED_SIX_ARRAY_DEF IN_NAMED_SEVEN_ARRAY_DEF
%s IN_SPBOUNDED_NUMBER_DEF INIT_SPBOUNDED_VECTOR_DEF IN_PVM_SLAVE_SECTION
%s DEFINE_PRIORS DEFINE_LIKELIHOOD DEFINE_PROCEDURE


%%

\/\/.*         /* ignore trailing comments */ ;
\/[\*]+.[\*]\/  /* ignore block comments */ ;
\r  /* ignore windows carriage return*/ ;

INITIALIZATION_SECTION  {

  /*
  if (!data_defined)
  {
    fprintf(stderr,"Error -- DATA_SECTION must be defined before"
      " INITIALIZATION_SECTION \n");
    exit(1);
  }
  if (initialization_defined)
  {
    fprintf(stderr,"%s","Error -- only one INTIALIZATION SECTION allowed\n");
    exit(1);
  }
  if (!params_defined)
  {
    fprintf(stderr,"Error -- INITIALIZATION_SECTION must be defined before"
      " PARAMETER_SECTION \n");
    exit(1);
  }
  else
  */
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
    fprintf(stderr,"Error -- PARAMETER_SECTION must be defined before"
      " REPORT_SECTION \n");
    exit(1);
  }
  if (report_defined)
  {
    fprintf(stderr,"%s","Error -- only one REPORT SECTION allowed\n");
    exit(1);
  }
  if (!params_defined)
  {
    fprintf(stderr,"Error -- PARAMETER_SECTION must be defined before"
      " REPORT_SECTION \n");
    exit(1);
  }
  else
  {
    BEGIN DEFINE_PROCS;
    report_defined=1;

    setup_for_prior_likelihood();

    fprintf(fall,"%s","}\n\nvoid model_parameters::report(const dvector& gradients)"
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
  if (final_defined)
  {
    fprintf(stderr,"%s","Error -- only one FINAL SECTION allowed\n");
    exit(1);
  }
  if (!params_defined)
  {
    fprintf(stderr,"Error -- PARAMETER_SECTION must be defined before"
      " FINAL_SECTION \n");
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
  if (runtime_defined)
  {
    fprintf(stderr,"%s","Error -- only one REPORT SECTION allowed\n");
    exit(1);
  }
  if (!params_defined)
  {
    fprintf(stderr,"Error -- PARAMETER_SECTION must be defined before"
      " RUNTIME_SECTION \n");
    exit(1);
  }
  else
  {
    BEGIN DEFINE_RUNTIME;
    runtime_defined=1;
    setup_for_prior_likelihood();
    fprintf(fall,"%s","}\n\nvoid model_parameters::set_runtime(void)"
      "\n{\n");
  }
                }

<DEFINE_RUNTIME>^" "*convergence_criteria" ".* {

    strip_leading_blanks(tmp_string1,yytext);
    after_part(tmp_string2,tmp_string1,' ');  // get 10  in x  10
    strip_leading_blanks(tmp_string1,tmp_string2);
    fprintf(fall,"%s","  dvector temp(\"{");
    fprintf(fall,"%s}\");\n", tmp_string1);
    fprintf(fall,"  convergence_criteria.allocate"
      "(temp.indexmin(),temp.indexmax());\n" );
    fprintf(fall,"  convergence_criteria=temp;\n");

                                  }

<DEFINE_RUNTIME>^" "*maximum_function_evaluations" ".* {

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

  if (!data_defined)
  {
    fprintf(stderr,"Error -- PARAMETER_SECTION must be defined before"
      " INITIALIZATION_SECTION \n");
    exit(1);
  }
  if (preliminary_calcs_defined)
  {
    fprintf(stderr,"%s","Error -- only one PRELIMINARY_CALCS_SECTION allowed\n");
    exit(1);
  }
  if (!params_defined)
  {
    fprintf(stderr,"Error -- PARAMETER_SECTION must be defined before"
      " PRELIMINARY_CALCS_SECTION\n");
    exit(1);
  }
  else
  {
    BEGIN DEFINE_PRELIMINARY_CALCS;
    preliminary_calcs_defined=1;

    setup_for_prior_likelihood();

    fprintf(fall,"%s","}\n\nvoid model_parameters::preliminary_calculations(void)"
      "\n{\n");
    fprintf(fall,"%s","\n#if defined(USE_ADPVM)\n");
    fprintf(fall,"%s","\n  admaster_slave_variable_interface(*this);\n");
    fprintf(fall,"%s","\n#endif\n");
  }
                }

<DEFINE_PRELIMINARY_CALCS>^[ \t].* { fprintf(fall,"%s\n",yytext); }

BETWEEN_PHASES_SECTION {

  if (between_phases_defined)
  {
    fprintf(stderr,"%s","Error -- only one BETWEEN_PHASES_SECTION allowed\n");
    exit(1);
  }
  else
  {
    BEGIN DEFINE_BETWEEN_PHASES;
    between_phases_defined=1;
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
  #if defined(USE_ADPVM)
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
    setup_for_prior_likelihood();
    fprintf(fall,"%s","}\n\nimatrix model_parameters::"
      "get_slave_assignments(void)\n{\n");
  }
  #endif
         }

<IN_PVM_SLAVE_SECTION>^[ \t].* { fprintf(fall,"%s\n",yytext); }

DATA_SECTION  {

  if (data_defined)
  {
    fprintf(stderr,"%s","Error -- only one data section allowed\n");
    exit(1);
  }
  else
  {
    char buff[1000];
#   if defined(_WIN32)
      char * FILE_ROOT = strupr(strdup(infile_root));
#   else
      char * FILE_ROOT = strdup(infile_root);
#  endif
    //if(!data_defined)
  BEGIN DEFINE_DATA;
    data_defined=1;
    in_define_data=1;
    filename_size = strlen(FILE_ROOT);
    filename_index = 0;
    while (filename_index < filename_size)
    {
      int c = (int)FILE_ROOT[filename_index];
      if (isalnum(c) == 0)
      {
        FILE_ROOT[filename_index] = '_';
      }
      filename_index++;
    }
    strcpy(buff,"#if !defined(_");
    strncat(buff,FILE_ROOT,100);
    strncat(buff,"_)\n#  define _" ,100);
    strncat(buff,FILE_ROOT,100);
    strncat(buff,"_\n\n",100);
    fprintf(fdat,"%s",buff);
    if (makedll)
    {
      fprintf(fall,"%s",
        "model_data::model_data(int argc,char * argv[],dll_args& ad_dll) : "
          "ad_comm(argc,argv)\n{\n");
      fprintf(fdat,"%s","class dll_args;\n");
    }
    else
    {

      fprintf(fall,"%s","model_data::model_data(int argc,char * argv[]) : "
        "ad_comm(argc,argv)\n{\n");
    }

    fprintf(fall, "%s", "  adstring tmpstring;\n"
                        "  tmpstring=adprogram_name + adstring(\".dat\");\n"
                        "  if (argc > 1)\n"
                        "  {\n"
                        "    int on=0;\n"
                        "    if ( (on=option_match(argc,argv,\"-ind\"))>-1)\n"
                        "    {\n"
                        "      if (on>argc-2 || argv[on+1][0] == '-')\n"
                        "      {\n"
                        "        cerr << \"Invalid input data command line option\"\n"
                        "                \" -- ignored\" << endl;\n"
                        "      }\n"
                        "      else\n"
                        "      {\n"
                        "        tmpstring = adstring(argv[on+1]);\n"
                        "      }\n"
                        "    }\n"
                        "  }\n"
                        "  global_datafile = new cifstream(tmpstring);\n"
                        "  if (!global_datafile)\n"
                        "  {\n"
                        "    cerr << \"Error: Unable to allocate global_datafile in model_data constructor.\";\n"
                        "    ad_exit(1);\n"
                        "  }\n"
                        "  if (!(*global_datafile))\n"
                        "  {\n"
                        "    delete global_datafile;\n"
                        "    global_datafile=NULL;\n"
                        "  }\n");

    fprintf(fdat,"%s","class model_data : public ad_comm{\n");
  }
                }

<DEFINE_DATA>^[ \t]*!!USER_CODE.* {
    strip_leading_blanks_and_tabs(tmp_string1,yytext);
    strcpy(tmp_string2,tmp_string1+11);
    fprintf(fall,"%s\n",tmp_string2);

    }

<DEFINE_DATA>^[ \t]*!!CLASS.* {              // start with !!CLASSbbclassname classinstance(xxx)
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

<DEFINE_DATA>^[ \t]*@@.* {              // start with !!CLASSbbclassname classinstance(xxx)
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

<DEFINE_DATA>^[ \t]*!!.* {
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

<DEFINE_DATA>pvm_int {

    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  pvm_int ");
                     }

<DEFINE_DATA>pvm_number {

    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  pvm_number ");
                     }

<DEFINE_DATA>init_number {
    likelihood_found=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  data_number ");
                     }

<DEFINE_DATA>init_xml_doc {
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  init_xml_doc ");
                     }

<DEFINE_DATA>friend_class {
    BEGIN IN_NAMED_NUMBER_DEF;
    fprintf(fdat,"%s","  friend class ");
                     }

<DEFINE_PARAMETERS>friend_class {
    BEGIN IN_NAMED_NUMBER_DEF;
    fprintf(fdat,"%s","  friend class ");
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

<DEFINE_DATA>init_3darray {
    likelihood_found=1;
    BEGIN IN_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  data_3array ");
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
    fprintf(fdat,"%s","  data_7array ");
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
    BEGIN IN_NAMED_SIX_ARRAY_DEF;
    fprintf(fdat,"%s","  d6_array ");
                     }

<DEFINE_DATA>7darray {
    likelihood_found=1;
    BEGIN IN_NAMED_SEVEN_ARRAY_DEF;
    fprintf(fdat,"%s","  d7_array ");
                     }

<IN_LOCAL_CALCS>^[ \t]END_CALCS |
<IN_LOCAL_CALCS>^[ \t]END_CALCULATIONS {

    if (in_define_data) BEGIN DEFINE_DATA;
    if (in_define_parameters) BEGIN DEFINE_PARAMETERS;

                  }

<IN_LOCAL_CALCS>^[ \t][^ \tE].* {
    fprintf(stderr,"%s","Error: In LOCAL_SECTION lines should be indented with two spaces or tabs.\n");
    fprintf(stderr,"Line %d:\n",nline);
    fprintf(stderr,"%s\n",yytext);
    fprintf(stderr,"^\n");
    exit(1);
}

<IN_LOCAL_CALCS>^[ \t][ \t].*       {
    fprintf(fall,"%s\n",yytext);
          }

<DEFINE_PARAMETERS>^[ \t]*!!CLASS.* {              // start with !!CLASSbbclassname classinstance(xxx)
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

<DEFINE_PARAMETERS>^[ \t]*!!USER_CODE.* {
    strip_leading_blanks_and_tabs(tmp_string1,yytext);
    strcpy(tmp_string2,tmp_string1+11);
    fprintf(fall,"%s\n",tmp_string2);

    }

<DEFINE_PARAMETERS>^[ \t]*!!.* {
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

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_number ");
                     }

<DEFINE_PARAMETERS>SPinit_bounded_number {

    talk_to_splus=1;
    BEGIN INIT_BOUNDED_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_bounded_number ");
                     }

<DEFINE_PARAMETERS>SPinit_vector {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_vector ");
                     }


<DEFINE_PARAMETERS>SPinit_bounded_vector {

    talk_to_splus=1;
    BEGIN INIT_BOUNDED_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_bounded_vector ");
                     }

<DEFINE_PARAMETERS>SPinit_matrix {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_matrix ");
                     }

<DEFINE_PARAMETERS>SPinit_bounded_matrix {

    talk_to_splus=1;
    BEGIN INIT_BOUNDED_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_bounded_matrix ");
                     }

<DEFINE_PARAMETERS>SPinit_3darray {

    talk_to_splus=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  SPparam_init_3array ");
                     }

<DEFINE_PARAMETERS>SPinit_bounded_3darray {

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
    spnumber_flag=1;
    BEGIN IN_SPNUMBER_DEF;
    fprintf(fdat,"%s","  dll_param_init_number ");
                     }



<DEFINE_PARAMETERS>splus_init_bounded_number |
<DEFINE_PARAMETERS>dll_init_bounded_number {
    spnumber_flag=1;
    BEGIN IN_SPBOUNDED_NUMBER_DEF;
    fprintf(fdat,"%s","  dll_param_init_bounded_number ");
                     }


<DEFINE_PARAMETERS>splus_number |
<DEFINE_PARAMETERS>dll_number {
    spnumber_flag=1;
    BEGIN IN_SPNUMBER_DEF;
    fprintf(fdat,"%s","  dll_param_number ");
                     }

<DEFINE_PARAMETERS>init_number {
    prior_found=1;
    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  param_init_number ");
                     }

<DEFINE_PARAMETERS>init_number_vector {
  prior_found=1;
    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_number_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_number {
  prior_found=1;
    BEGIN INIT_BOUNDED_NUMBER_DEF;
    fprintf(fdat,"%s","  param_init_bounded_number ");
                     }

<DEFINE_PARAMETERS>init_bounded_number_vector {
  prior_found=1;
    BEGIN INIT_BOUNDED_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_bounded_number_vector ");
                     }
<DEFINE_PARAMETERS>init_bounded_number_matrix {
    prior_found=1;
    BEGIN INIT_BOUNDED_MATRIX_DEF;
    fprintf(fdat,"%s","  param_init_bounded_number_matrix ");
                     }

<DEFINE_PARAMETERS>splus_init_vector |
<DEFINE_PARAMETERS>dll_init_vector {

    spnumber_flag=1;
    BEGIN IN_SPVECTOR_DEF;
    fprintf(fdat,"%s","  dll_param_init_vector ");
                     }

<DEFINE_PARAMETERS>splus_vector |
<DEFINE_PARAMETERS>dll_vector {

    spnumber_flag=1;
    BEGIN IN_SPVECTOR_DEF;
    fprintf(fdat,"%s","  dll_param_vector ");
                     }

<DEFINE_PARAMETERS>init_vector {
    prior_found=1;
    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_vector ");
                     }

<DEFINE_PARAMETERS>init_factor {

    BEGIN IN_FACTOR_DEF;
    fprintf(fdat,"%s","  param_init_vector ");
                     }

<DEFINE_PARAMETERS>init_vector_vector {
    prior_found=1;
    BEGIN IN_MATRIX_DEF;
    fprintf(fdat,"%s","  param_init_vector_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_dev_vector {
    prior_found=1;
    BEGIN INIT_BOUNDED_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_bounded_dev_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_vector {
  prior_found=1;
    BEGIN INIT_BOUNDED_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_bounded_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_vector_vector {
    prior_found=1;
    BEGIN INIT_BOUNDED_MATRIX_DEF;
    fprintf(fdat,"%s","  param_init_bounded_vector_vector ");
                     }

<DEFINE_PARAMETERS>splus_init_bounded_vector |
<DEFINE_PARAMETERS>dll_init_bounded_vector {

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

    spnumber_flag=1;
    BEGIN IN_SPMATRIX_DEF;
    fprintf(fdat,"%s","  dll_param_init_matrix ");
                     }

<DEFINE_PARAMETERS>init_matrix {
  prior_found=1;
    BEGIN IN_MATRIX_DEF;
    fprintf(fdat,"%s","  param_init_matrix ");
                     }

<DEFINE_PARAMETERS>init_matrix_vector {
  prior_found=1;
    BEGIN IN_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_matrix_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_matrix {
  prior_found=1;
    BEGIN INIT_BOUNDED_MATRIX_DEF;
    fprintf(fdat,"%s","  param_init_bounded_matrix ");
                     }

<DEFINE_PARAMETERS>init_bounded_matrix_vector {
  prior_found=1;
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

<DEFINE_DATA>init_3iarray {
  prior_found=1;
    BEGIN IN_THREE_ARRAY_DEF;
    fprintf(fdat,"%s"," data_3iarray ");
                     }

<DEFINE_PARAMETERS>init_3darray {
  prior_found=1;
    BEGIN IN_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_d3array ");
                     }

<DEFINE_DATA>init_4iarray {
  prior_found=1;
    BEGIN IN_FOUR_ARRAY_DEF;
    fprintf(fdat,"%s","  data_4iarray ");
                     }

<DEFINE_PARAMETERS>init_4darray {
  prior_found=1;
    BEGIN IN_FOUR_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_4array ");
                     }

<DEFINE_PARAMETERS>init_5darray {
  prior_found=1;
    BEGIN IN_FIVE_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_5array ");
                     }

<DEFINE_PARAMETERS>init_bounded_3darray {
  prior_found=1;
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

    fprintf(fdat,"%s",yytext);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"  %s",yytext);
    fprintf(fall,".allocate(\"%s\");\n",yytext);
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

    strcpy(objective_function_name_string,yytext);  // get objective function name

    fprintf(fdat,"%s",yytext);
    fprintf(fdat,"%s",";\n");
    fprintf(fall,"  %s",yytext);
    fprintf(fall,".allocate(\"%s\");\n",yytext);

    fprintf(fall,"%s","  prior_function_value.allocate(\"prior_function_value\");\n");
    fprintf(fall,"%s","  likelihood_function_value.allocate(\"likelihood_function_value\");\n");

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


<INIT_BOUNDED_NUMBER_DEF>({name}\({float_num_exp},{float_num_exp},{num_exp}\)) |
<INIT_BOUNDED_NUMBER_DEF>({name}\({name}\)) {


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

<IN_FACTOR_DEF>{name}\({name}\) {
    before_part(tmp_string,yytext,'(');  // get x in x(v)
    fprintf(fdat,"%s_levels;\n",tmp_string);
    fprintf(fdat,"  factor %s;\n",tmp_string);
    after_part(tmp_string1,yytext,'(');  // get (v in x(v)
    before_part(tmp_string2,tmp_string1,')');
    fprintf(fall,"  int %s_nlevels = count_factor",tmp_string);
    fprintf(fall,"%s);\n",tmp_string2);
    fprintf(fall,"  %s_levels.allocate(1,%s_nlevels,\"%s_levels\");\n",tmp_string,tmp_string,tmp_string);
    fprintf(fall,"  %s.allocate%s,%s_levels);\n",tmp_string,tmp_string2,tmp_string);
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


<IN_VECTOR_DEF>{name}\({num_exp},{num_exp}\) |
<IN_VECTOR_DEF>{name}\({num_exp},{name}\) |
<IN_VECTOR_DEF>{name}\({name},{num_exp}\) |
<IN_VECTOR_DEF>{name}\({name},{name}\) |
<IN_VECTOR_DEF>({name}\({name}\)) {

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
      if(prior_found) {
        if(prior_counter<MAX_PRIOR_CHECK) sprintf(prior_checker[prior_counter++],"%s",tmp_string);
        prior_found=0;
      }
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


<INIT_BOUNDED_VECTOR_DEF>{name}\({num_exp},{num_exp},{float_num_exp},{float_num_exp},{num_exp}\) |
<INIT_BOUNDED_VECTOR_DEF>{name}\({name}\) {

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
<IN_MATRIX_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) |
<IN_MATRIX_DEF>({name}\({name}\)) {

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
<IN_THREE_ARRAY_DEF>{name}\({index},{index},{index},{index},{index},{index}\)  {

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
<IN_NAMED_FOUR_ARRAY_DEF>{name} {
    if (warn_unallocated) write_unallocated("4darray()");

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
<IN_NAMED_FIVE_ARRAY_DEF>{name} {
    if (warn_unallocated) write_unallocated("5darray()");

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
  else
  {
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
    //if(!params_defined)
  BEGIN DEFINE_PARAMETERS;
    if (in_define_data)
    {
      fprintf(fall, "%s", "  if (global_datafile)\n"
                          "  {\n"
                          "    delete global_datafile;\n"
                          "    global_datafile = NULL;\n"
                          "  }\n");
      in_define_data=0;
    }
    in_define_parameters=1;
    params_defined=1;

    fprintf(fdat,"  ~model_data();\n");
    if (makedll)
      fprintf(fdat,
        "  model_data(int argc,char * argv[],dll_args&);\n  friend class model_parameters;\n");
    else
      fprintf(fdat,"  model_data(int argc,char * argv[]);\n  friend class model_parameters;\n");
    fprintf(fdat,"%s","};\n\nclass model_parameters : "
      "public model_data ,"
      "\n  public function_minimizer\n{\n");

    fprintf(fdat,"%s","public:\n");
    fprintf(fdat,"  ~model_parameters();\n");
//    fprintf(fdat,"%s","  void admaster_slave_variable_interface(void);\n");
    fprintf(fdat,"%s","  void preliminary_calculations(void);\n");
    fprintf(fdat,"%s","  void set_runtime(void);\n");
//    fprintf(fdat,"%s","  virtual void * mycast(void) {return (void*)this;}\n");

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
    fprintf(fdat,"%s","private:\n");
    fprintf(fdat,"%s","  dvariable adromb(dvariable(model_parameters::*f)(const dvariable&), double a, double b, int ns)\n"
                      "  {\n"
                      "    using namespace std::placeholders;\n"
                      "    _func func = std::bind(f, this, _1);\n"
                      "    return function_minimizer::adromb(func, a, b, ns);\n"
                      "  }\n");
    fprintf(fdat,"%s", "  ivector integer_control_flags;\n");
    fprintf(fdat,"%s", "  dvector double_control_flags;\n");

    if (makedll)
    {
      fprintf(fall,"%s","}\n\nmodel_parameters::model_parameters"
        "(int sz,int argc,char * argv[], dll_args& ad_dll) : "
        "\n model_data(argc,argv,ad_dll) , function_minimizer(sz)\n{\n");
    }
    else
    {
      fprintf(fall,"%s","}\n\nmodel_parameters::model_parameters"
        "(int sz,int argc,char * argv[]) : "
        "\n model_data(argc,argv) , function_minimizer(sz)\n{\n");
    }
    fprintf(fall,"%s", "  initializationfunction();\n");

                  }

PROCEDURE_SECTION {
    int i;
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
    /*
    if (likelihood_defined)
    {
      fprintf(stderr,"%s","Error -- PROCEDURE_SECTION must be defined before"
        " LIKELIHOOD_SECTION \n");
      exit(1);
    }
    */
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


   /* fprintf(fdat,"%s","};\n");*/
    fprintf(fall,"%s","}\n\nvoid model_parameters::userfunction(void)\n{\n");
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
    //setup_for_prior_likelihood();
    fprintf(fall,"%s","}\n\nvoid model_parameters::likelihoodfunction(void)" "\n{\n");
    fprintf(fall,"%s","  likelihood_function_value=0.0;\n");
    fprintf(fall,"%s","  dvariable tmp__like=0.0;\n");
  }
  }




FUNCTION[ ]*{name}[ ]*{name}\( {
    char c;
    int i = 0;
    tmp_string5[i] = '\0';
    while ((c = input()) != ')' && i < MAX_TMP_STRING - 1)
    {
      tmp_string5[i] = c;
      i++;
    }
    if (i >= MAX_TMP_STRING - 1) {
      fprintf(stderr,"Error -- Function parameter list has too many characters.");
      exit(1);
    }
    tmp_string5[i] = ')';
    tmp_string5[i + 1] = '\0';
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

    setup_for_prior_likelihood();

    fprintf(fall,"}\n\n%s ",tmp_string3);

    fprintf(fall,"model_parameters::%s%s\n{\n",tmp_string1,tmp_string5);

    fprintf(fdat," %s %s%s;\n",tmp_string3,tmp_string1,tmp_string5);

    add_references_to_user_classes(fall);

    in_aux_proc=1;
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


<DEFINE_PROCS>^[ \t].* { fprintf(fall,"%s\n",yytext); }


<DEFINE_AUX_PROC>^\ +{name}\ +{name}\(.*       {

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


<CONTINUE_PROTOTYPE_DEF>^\ .*       {

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

    setup_for_prior_likelihood();

    BEGIN IN_GLOBALS_SECTION;
    /*fglobals=fopen("xxglobal.tmp","w+");*/
    if (fglobals==NULL)
    {
      fprintf(stderr,"%s","Error trying to open file xxglobal.tmp\n");
    }

                }

<IN_GLOBALS_SECTION>^[ \t].* {

        fprintf(fglobals,"%s\n",yytext);
                              }

TOP_OF_MAIN_SECTION {

    *arglist_ptr='\0';
    if (top_of_main_defined) {
      fprintf(stderr,"Error -- there is more than 1 TOP_OF_MAIN_SECTION\n");
      exit(1);
    }
    top_of_main_defined=1;

    setup_for_prior_likelihood();

    BEGIN IN_TOP_SECTION;
    ftopmain=fopen("xxtopm.tmp","w+");
    if (ftopmain==NULL)
    {
      fprintf(stderr,"%s","Error trying to open file xxtopmn.tmp\n");
      exit(1);
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
          fprintf(ftopmain, "int __stdcall __declspec(dllexport) \n");
          fprintf(ftopmain, "#else\n");
          fprintf(ftopmain, "int \n");
          fprintf(ftopmain, "#endif\n");
        }
      }
      else
      {
        fprintf(ftopmain,"\nint main(int argc,char * argv[])\n{\n");
        fprintf(ftopmain,"    ad_set_new_handler();\n");
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

<IN_TOP_SECTION>^[ \t].* {

        fprintf(ftopmain,"%s\n",yytext);

                              }


<<EOF>> {

    setup_for_prior_likelihood();

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
    //if (!in_aux_proc)
    //if (in_aux_proc)
    {
     // fprintf(fall,"}\n");
    }

    if (!preliminary_calcs_defined)
    {
      fprintf(fall,"}\n");
      fprintf(fall,"\nvoid model_parameters::preliminary_calculations(void)"
        "{");
      fprintf(fall,"%s","\n#if defined(USE_ADPVM)\n");
      fprintf(fall,"%s","\n  admaster_slave_variable_interface(*this);\n");
      fprintf(fall,"%s","\n#endif\n");
    }

    fprintf(fall,"}\n");
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
          fprintf(ftopmain,"    ad_set_new_handler();\n");
          if (bound_flag) fprintf(ftopmain,"  ad_exit=&ad_boundf;\n");
          fprintf(ftopmain,"  %s",infile_root);
          fprintf(ftopmain,"(%s,dll_options);\n}\n",arglist1);
        }
        if (!splus_debug_flag)
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
            fprintf(ftopmain, "int __stdcall __declspec(dllexport) \n");
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
        fprintf(ftopmain,"    ad_set_new_handler();\n");
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
      fprintf(ftopmain,"  try {\n");

      if (!makegaussdll)
      {
        fprintf(ftopmain,"    char **argv=parse_dll_options((char*)\"%s\",argc,"
          "*dll_options);\n",infile_root);
      }
      else
      {
        fprintf(ftopmain,"    char **argv=parse_dll_options((char*)\"%s\",argc,"
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
    // The following settings for ARRAY_MEMBLOCK_SIZE used to be more complex.
    // for more info, see:
    // http://lists.admb-project.org/pipermail/developers/2012-April/000607.html
    // These defaults should probably be moved to gradstrc.cpp along with other
    // default settings, but I don't have the skills to do that right now.
    // - Ian Taylor, May 1, 2012

    fprintf(ftopmain,"#ifdef DEBUG\n");
    fprintf(ftopmain,"  #ifndef __SUNPRO_C\n");
    fprintf(ftopmain,"std::feclearexcept(FE_ALL_EXCEPT);\n");
    fprintf(ftopmain,"  #endif\n");
    fprintf(ftopmain,"  auto start = std::chrono::high_resolution_clock::now();\n");
    fprintf(ftopmain,"#endif\n");
    if (makedll)
    {
      fprintf(ftopmain,"    gradient_structure::set_YES_SAVE_VARIABLES_VALUES();\n"
        "    if (!arrmblsize) arrmblsize=15000000;\n"
        "    model_parameters mp(arrmblsize,argc,argv,ad_dll);\n"
        "    mp.iprint=10;\n");
    }
    else
    {
      fprintf(ftopmain,"    gradient_structure::set_YES_SAVE_VARIABLES_VALUES();\n"
        "    if (!arrmblsize) arrmblsize=15000000;\n"
        "    model_parameters mp(arrmblsize,argc,argv);\n"
        "    mp.iprint=10;\n");
    }

    fprintf(ftopmain,"    mp.preliminary_calculations();\n");
    fprintf(ftopmain,"    mp.computations(argc,argv);\n");

    fprintf(ftopmain,"#ifdef DEBUG\n");
    fprintf(ftopmain,"  std::cout << endl << argv[0] << \" elapsed time is \" << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count() << \" microseconds.\" << endl;\n");
    fprintf(ftopmain,"  #ifndef __SUNPRO_C\n");
    fprintf(ftopmain,"bool failedtest = false;\n");
    fprintf(ftopmain,"if (std::fetestexcept(FE_DIVBYZERO))\n");
    fprintf(ftopmain,"  { cerr << \"Error: Detected division by zero.\" << endl; failedtest = true; }\n");
    fprintf(ftopmain,"if (std::fetestexcept(FE_INVALID))\n");
    fprintf(ftopmain,"  { cerr << \"Error: Detected invalid argument.\" << endl; failedtest = true; }\n");
    fprintf(ftopmain,"if (std::fetestexcept(FE_OVERFLOW))\n");
    fprintf(ftopmain,"  { cerr << \"Error: Detected overflow.\" << endl; failedtest = true; }\n");
    fprintf(ftopmain,"if (std::fetestexcept(FE_UNDERFLOW))\n");
    fprintf(ftopmain,"  { cerr << \"Error: Detected underflow.\" << endl; }\n");
    fprintf(ftopmain,"if (failedtest) { std::abort(); } \n");
    fprintf(ftopmain,"  #endif\n");
    fprintf(ftopmain,"#endif\n");

    fprintf(htop,"#ifdef DEBUG\n");
    fprintf(htop,"  #include <chrono>\n");
    fprintf(htop,"#endif\n");
    fprintf(htop,"#include <admodel.h>\n");
    fprintf(htop,"#ifdef USE_ADMB_CONTRIBS\n");
    fprintf(htop,"#include <contrib.h>\n\n");
    if(enable_pad)
    {
      fprintf(htop,"#include <gdbprintlib.cpp>\n");
    }
    fprintf(htop,"#endif\n");

    if (bound_flag)
    {
      fprintf(htop,"  extern \"C\"  {\n");
      fprintf(htop,"    void ad_boundf(int i);\n  }\n");
    }


    if (talk_to_splus)
    {
      fprintf(htop,"#include <adsplus.h>\n\n");
    }

    if (makedll)
    {
      // df april 5 03 remove this when bug from cleanup_argv is found
      //fprintf(ftopmain,"    cleanup_argv(argc,&argv);\n");
      fprintf(ftopmain,"    ad_make_code_reentrant();\n");
      fprintf(ftopmain,"  }\n");

      fprintf(ftopmain,"  catch (spdll_exception spe){ \n");
      fprintf(ftopmain,"    if (ad_printf && spe.e) (*ad_printf)"
        " (\"abnormal exit from newtest\\n\");\n");
      fprintf(ftopmain,"  }\n");
      if (makegaussdll) fprintf(ftopmain,"  return 0;\n");
      fprintf(ftopmain,"}\n");
      fprintf(ftopmain,"}\n");
      fprintf(fdat,"%s","};\n");
      *conlist_ptr='\0';
      *arglist1_ptr='\0';
      *classlist_ptr='\0';
      fprintf(fdat,"\nclass dll_args\n{\npublic:\n%s",classlist);
      if (num_spargs)
        fprintf(fdat,"\n dll_args(%s) : %s{}\n",arglist,conlist);
      else
        fprintf(fdat,"\n dll_args()  {}\n");
    }
    else
    {
      fprintf(ftopmain,"    return 0;\n}\n");
    }
    fprintf(fdat,"\n};\n#endif\n");
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
    strcpy(outcommand,"copy /b xxglobal.tmp + xxhtop.tmp + header.tmp + xxalloc.tmp"
      " + xxtopm.tmp ");
#else
    strcpy(outcommand,"cat xxglobal.tmp xxhtop.tmp header.tmp xxalloc.tmp"
      " xxtopm.tmp > ");
#endif
    // strcpy(outcommand,"copy xxdata.tmp + header.tmp + xxalloc.tmp ");
    strcat(outcommand,outfile_name);
    errcopy=system(outcommand);


    if (!errcopy)
    {
      unlink("xxdata.tmp");
      unlink("xxhtop.tmp");
      unlink("xxglobal.tmp");
      unlink("xxtopm.tmp");
      unlink("xxalloc.tmp");
      unlink("header.tmp");
    }
    else
    {
      fprintf(stderr,"Error trying to create output file %s",
        outfile_name);
    }

    exit(0);
}
%%

int option_match(int argc,char * argv[], char * string);

unsigned _stklen = 16000;

int main(int argc, char * argv[])
{
  FILE * f1=NULL;
  int ioff=argc-1;
  int on=0;
  bound_flag=1;
  if ( (on=option_match(argc,argv,"-bounds"))>-1)
  {
    bound_flag=1;
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
    splus_debug_flag=0;
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
    strcpy(infile_root,infile_name);
    strcpy(outfile_name,argv[ioff]);
    strcpy(headerfile_name,argv[ioff]);
    strcat(infile_name,".tpl");
    strcat(outfile_name,".cpp");
    strcat(headerfile_name,".htp");
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
  fprintf(fglobals,"#ifdef DEBUG\n");
  fprintf(fglobals,"  #ifndef __SUNPRO_C\n");
  fprintf(fglobals,"    #include <cfenv>\n");
  fprintf(fglobals,"    #include <cstdlib>\n");
  fprintf(fglobals,"  #endif\n");
  fprintf(fglobals,"#endif\n");

  fdat=fopen(headerfile_name,"w+");
  if (fdat==NULL)
  {
    fprintf(stderr,"Error trying to open file %s\n",headerfile_name);
  }
  fall=fopen("xxalloc.tmp","w+");
  if (fall==NULL)
  {
    fprintf(stderr,"%s","Error trying to open file xxalloc.tmp\n");
  }
  fprintf(fall,"#include <%s>\n\n",headerfile_name);
  fhead=fopen("header.tmp","w+");
  if (fhead==NULL)
  {
    fprintf(stderr,"%s","Error trying to open file header.tmp\n");
  }
  yylex();
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
  size_t index = strlen(s);
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
    if (index >= ipos + 1)
    {
      index = index - ipos - 1;
      if (d[index] == 13)   // crtl M
        d[index] = '\0';
    }
  }
  return d;
}

char * strict_after_part(char * d, char * s, char c)
{
  int ipos=0;
  int i=0;
  int iflag=0;
  size_t index = strlen(s);
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
    if (index >= ipos + 1)
    {
      index = index - ipos - 1;
      if (d[index] == 13)   // crtl M
        d[index] = '\0';
    }
  }
  return d;
}



char * after_partb(char * d, char * s, char c)
{
  int ipos=0;
  int i=0;
  int iflag=0;
  size_t index = strlen(s);
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
    if (index >= ipos + 1)
    {
      index = index - ipos - 1;
      if (d[index] == 13)   // crtl M
        d[index] = '\0';
    }
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
    else if (s[i]!='\r')
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
    else if (s[i]!='\r')
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


  /* add prior to userfunctions from procedure_section,
  */
  void add_prior_to_objective(void)
  {
    prior_done_once=1;priors_done=1;
    procedure_done=1;
    fprintf(fdat,"  virtual void priorsfunction(void);\n");  //add to .htp file
    //fprintf(fall,"%s","  prior_function_value=0.0;\n");
      fprintf(fall,"%s","  priorsfunction();\n"); //append at the end of procedure section/userfunction()
      //fprintf(fall,"%s%s%s","  ",objective_function_name_string,"+=prior_function_value;\n");
  }



  /* add likelihood function value to userfunctions from procedure_section,
  */
  void add_likelihood_to_objective(void)
  {
    likelihood_done_once=1;likelihood_done=1;
    procedure_done=1;
    fprintf(fdat,"  virtual void likelihoodfunction(void);\n");  //add to .htp file
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
  if((procedure_defined)&&(!priors_defined)&&(!likelihood_defined))
  {
    //JCA
    if (!procedure_done)
    {
      fprintf(fall,"#ifdef DEBUG\n");
      fprintf(fall,"  std::cout << \"DEBUG: gradient stack total is \" << gradient_structure::GRAD_STACK1->total() << std::endl;;\n");
      fprintf(fall,"#endif\n");
    }
    procedure_done=1;
  }
  if((procedure_defined)&&(priors_defined)&&(!prior_done_once)) add_prior_to_objective();
  if((procedure_defined)&&(likelihood_defined)&&(!likelihood_done_once)) add_likelihood_to_objective();
  //if((priors_defined)&&(!prior_done_once)) add_prior_to_objective();
  //if((likelihood_defined)&&(!likelihood_done_once)) add_likelihood_to_objective();
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
