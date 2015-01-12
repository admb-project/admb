%option noyywrap

%{
  /**
   * $Id$
   *
   * Author: David Fournier
   * Copyright (c) 2008-2011 Regents of the University of California
   */

  #define   MAX_TMP_STRING  501
  #define   MAX_USER_CLASSES  501
  #define   MAX_USER_CLASSNAME_LENGTH  251
  #include <stdlib.h>
  #include <string.h>
  #include <stdio.h>
  #if defined(_WIN32)
  #  include <io.h>  fopen
  #endif
  char tmp_string[MAX_TMP_STRING];
  char tmp_string1[MAX_TMP_STRING];
  char tmp_string2[MAX_TMP_STRING];
  char tmp_string3[MAX_TMP_STRING];
  char tmp_string4[MAX_TMP_STRING];
  char tmp_string5[MAX_TMP_STRING];
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
  int  splus_debug_flag=0;
  int  spnumber_flag=0;
  int data_defined=0;
  int in_define_data=0;
  int debug_flag=0;
  int makedll=0;
  int makegaussdll=0;
  int no_userclass=0;
  int bound_flag=1;
  int  num_user_classes=0;
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
  char uuu_xxx[80]={"Copyright (c) 2008-2011 Regents of the University of California"};
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

  int filename_index;
  int filename_size;
%}

name [a-z_A-Z]+(->)?[a-z_A-Z0-9]*

num_exp [a-z_A-Z0-9\+\-\*\/]+

index ([a-z_A-Z]+(->)?[a-z_A-Z0-9]*)|([a-z_A-Z0-9\+\-\*\/]+)

float_num_exp [a-z_A-Z0-9\.\+\-\*]+

%s DEFINE_DATA DEFINE_PARAMETERS DEFINE_PROCS IN_DATA_DEF IN_PARAM_DEF
%s IN_NUMBER_DEF IN_SPNUMBER_DEF IN_VECTOR_DEF IN_VECTOR_VECTOR_DEF 
%s IN_SPVECTOR_DEF 
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
%%
;             /* ignore semi colons */ ;
[ \t]+        /* ignore blanks */  ;
\/\/.*$         /* ignore trailing comments */ ;

\n    { nline++; }
\r    { ; }

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
    fprintf(fall,"%s","}\n\nvoid model_parameters::report()"
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
    fprintf(fall,"%s","}\n\nvoid model_parameters::final_calcs()"
      "\n{\n");
  }
                }


RUNTIME_SECTION  {

  in_aux_proc=0;
  if (!data_defined)
  {
    fprintf(stderr,"Error -- DATA_SECTION must be defined before"
      " REPORT_SECTION \n");
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
    fprintf(fall,"%s","}\n\nvoid model_parameters::preliminary_calculations(void)"
      "\n{\n");
    fprintf(fall,"%s","\n  admaster_slave_variable_interface(*this);\n");
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
    char buff[1000];
#   if defined(_WIN32)
      char * FILE_ROOT = strupr(strdup(infile_root));
#   else
      char * FILE_ROOT = strdup(infile_root);
#  endif
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
    fprintf(fdat,"%s","class model_data : public ad_comm{\n");
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

<DEFINE_DATA>pvm_int {

    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  pvm_int ");
                     }

<DEFINE_DATA>pvm_number {

    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  pvm_number ");
                     }

<DEFINE_DATA>init_number {

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

    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  data_vector ");
                     }

<DEFINE_DATA>init_ivector {

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

    BEGIN IN_MATRIX_DEF;
    fprintf(fdat,"%s","  data_matrix ");
                     }

<DEFINE_DATA>init_3darray {

    BEGIN IN_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  data_3array ");
                     }


<DEFINE_DATA>init_4darray {

    BEGIN IN_FOUR_ARRAY_DEF;
    fprintf(fdat,"%s","  data_4array ");
                     }

<DEFINE_DATA>init_5darray {

    BEGIN IN_FIVE_ARRAY_DEF;
    fprintf(fdat,"%s","  data_5array ");
                     }


<DEFINE_DATA>init_6darray {

    BEGIN IN_SIX_ARRAY_DEF;
    fprintf(fdat,"%s","  data_6array ");
                     }


<DEFINE_DATA>init_7darray {

    BEGIN IN_SEVEN_ARRAY_DEF;
    fprintf(fdat,"%s","  data_4array ");
                     }


<DEFINE_DATA>number {

    BEGIN IN_NAMED_NUMBER_DEF;
    fprintf(fdat,"%s","  double ");

                     }

<DEFINE_DATA>int {

    BEGIN IN_NAMED_NUMBER_DEF;
    fprintf(fdat,"%s","  int ");
                     }

<DEFINE_DATA>vector {

    BEGIN IN_NAMED_VECTOR_DEF;
    fprintf(fdat,"%s","  dvector ");
                     }

<DEFINE_DATA>ivector {

    BEGIN IN_NAMED_VECTOR_DEF;
    fprintf(fdat,"%s","  ivector ");
                     }

<DEFINE_DATA>matrix {

    BEGIN IN_NAMED_MATRIX_DEF;
    fprintf(fdat,"%s","  dmatrix ");
                     }

<DEFINE_DATA>imatrix {

    BEGIN IN_NAMED_MATRIX_DEF;
    fprintf(fdat,"%s","  imatrix ");
                     }

<DEFINE_DATA>3darray {

    BEGIN IN_NAMED_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  d3_array ");
                     }

<DEFINE_DATA>4darray {

    BEGIN IN_NAMED_FOUR_ARRAY_DEF;
    fprintf(fdat,"%s","  d4_array ");
                     }

<DEFINE_DATA>5darray {

    BEGIN IN_NAMED_FIVE_ARRAY_DEF;
    fprintf(fdat,"%s","  d5_array ");
                     }

<DEFINE_DATA>6darray {

    BEGIN IN_NAMED_FIVE_ARRAY_DEF;
    fprintf(fdat,"%s","  d6_array ");
                     }

<DEFINE_DATA>7darray {

    BEGIN IN_NAMED_FIVE_ARRAY_DEF;
    fprintf(fdat,"%s","  d7_array ");
                     }

<IN_LOCAL_CALCS>^[ \t]END_CALCS | 
<IN_LOCAL_CALCS>^[ \t]END_CALCULATIONS {

    if (in_define_data) BEGIN DEFINE_DATA;
    if (in_define_parameters) BEGIN DEFINE_PARAMETERS;
      
                  }

<IN_LOCAL_CALCS>^[ \t][^ \tE].*$ {
    fprintf(stderr,"%s","Error: In LOCAL_SECTION lines should be indented with two spaces or tabs.\n");
    fprintf(stderr,"Line %d:\n",nline);
    fprintf(stderr,"%s\n",yytext);
    fprintf(stderr,"^\n");
    exit(1);
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

    if(objective_function_defined++)
    {
      fprintf(stderr,"%s %d %s","Error in line",nline,"\n");
      fprintf(stderr,"only one instance of objective_function_value" 
                     " may be declared\n");
      exit(1);
    }
    BEGIN IN_NUMBER_DEF;
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

    BEGIN IN_NUMBER_DEF;
    fprintf(fdat,"%s","  param_init_number ");
                     }

<DEFINE_PARAMETERS>init_number_vector {

    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_number_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_number {

    BEGIN INIT_BOUNDED_NUMBER_DEF;
    fprintf(fdat,"%s","  param_init_bounded_number ");
                     }

<DEFINE_PARAMETERS>init_bounded_number_vector {

    BEGIN INIT_BOUNDED_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_bounded_number_vector ");
                     }
<DEFINE_PARAMETERS>init_bounded_number_matrix {

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

    BEGIN IN_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_vector ");
                     }

<DEFINE_PARAMETERS>init_vector_vector {

    BEGIN IN_MATRIX_DEF;
    fprintf(fdat,"%s","  param_init_vector_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_dev_vector {

    BEGIN INIT_BOUNDED_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_bounded_dev_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_vector {

    BEGIN INIT_BOUNDED_VECTOR_DEF;
    fprintf(fdat,"%s","  param_init_bounded_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_vector_vector {

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

    BEGIN IN_MATRIX_DEF;
    fprintf(fdat,"%s","  param_init_matrix ");
                     }

<DEFINE_PARAMETERS>init_matrix_vector {

    BEGIN IN_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_matrix_vector ");
                     }

<DEFINE_PARAMETERS>init_bounded_matrix {

    BEGIN INIT_BOUNDED_MATRIX_DEF;
    fprintf(fdat,"%s","  param_init_bounded_matrix ");
                     }

<DEFINE_PARAMETERS>init_bounded_matrix_vector {

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

    BEGIN IN_THREE_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_d3array ");
                     }

<DEFINE_PARAMETERS>init_4darray {

    BEGIN IN_FOUR_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_4array ");
                     }

<DEFINE_PARAMETERS>init_5darray {

    BEGIN IN_FIVE_ARRAY_DEF;
    fprintf(fdat,"%s","  param_init_5array ");
                     }

<DEFINE_PARAMETERS>init_bounded_3darray {

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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
<IN_THREE_ARRAY_DEF>{name}\({index},{index},{index},{index},{index},{index}\) |
<IN_THREE_ARRAY_DEF>{name}\({num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp},{num_exp}\) {

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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
      BEGIN DEFINE_DATA;
    }
    else
    {
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
      BEGIN DEFINE_DATA;
    }
    else
    {
      BEGIN DEFINE_PARAMETERS;
    }
                            }



.  {
  fprintf(stderr,"%s %d %s","Error in line",nline,"while reading\n");
  fprintf(stderr,"%s\n",yytext);
  exit(1);
     }

PARAMETER_SECTION {
    if (!data_defined)
    {
      fprintf(stderr,"Error DATA_SECTION must be defined before"
        " PARAMETER SECTION\n");
      exit(1);
    }
    BEGIN DEFINE_PARAMETERS;
    in_define_data=0;
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
    fprintf(fdat,"%s","private:\n");
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
    if (!objective_function_defined)
    {
      fprintf(stderr,"Error -- You must define an object of type objective"
        "_function_value in the\nPARAMETER SECTION"
        "and assign the approriate value to it in the\nPROCEDURE_SECTION");
      exit(1);
    }
    BEGIN DEFINE_PROCS;
    procedure_defined=1;
    in_procedure_def=1;
    in_define_parameters=0;

    if (makedll)
    {
      fprintf(fdat,"public:\n  virtual void userfunction(void);\n"
        "  virtual void report(void);\n" // define this to get a report
        "  virtual void final_calcs(void);\n" 
        "  model_parameters(int sz,int argc, char * argv[],"
        " dll_args& ad_dll);\n");
    }
    else	
    {
      fprintf(fdat,"public:\n  virtual void userfunction(void);\n"
        "  virtual void report(void);\n" // define this to get a report
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
    fprintf(fall,"%s","}\n\nvoid model_parameters::userfunction(void)"
      "\n{\n");
    add_references_to_user_classes(fall);  
                  }


FUNCTION[ ]*{name}[ ]*{name}\( {
    char c;
    int i = 0; 
    tmp_string5[i] = '\0';
    while ((c = input()) != ')' || i >= MAX_TMP_STRING - 1)
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
        fprintf(ftopmain,"\n#if !defined(__MSVC32__)"
           "\n#  define __declspec(x)"
           "\n#endif\n");

        fprintf(ftopmain,"\n#if !defined(__BORLANDC__)"
           "\n#  define _export"
           "\n#else"
           "\n#  define _export __stdcall"
           "\n#endif\n");
        if (!makegaussdll)
          fprintf(ftopmain,"\n__declspec(dllexport) void _export ");
        else
          fprintf(ftopmain,"\n__declspec(dllexport) int _export ");
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

<IN_TOP_SECTION>^[ \t].*$ { 

        fprintf(ftopmain,"%s\n",yytext);

                              }


<<EOF>> {

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
      fprintf(fall,"%s","\n  admaster_slave_variable_interface(*this);\n");
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
      fprintf(fall,"\nvoid model_parameters::report(void)"
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
          fprintf(ftopmain,"\n#if !defined(__MSVC32__)"
            "\n#  define __declspec(x)"
            "\n#endif\n");
      
          fprintf(ftopmain,"\n#if !defined(__BORLANDC__)"
            "\n#  define _export"
           "\n#else"
           "\n#  define _export __stdcall"
            "\n#endif\n");
	    
          if (!makegaussdll)
            fprintf(ftopmain,"\n__declspec(dllexport) void _export ");
          else
            fprintf(ftopmain,"\n__declspec(dllexport) int _export ");
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
        fprintf(ftopmain,"    char **argv=parse_dll_options(\"%s\",argc,"
          "*dll_options);\n",infile_root);
      }
      else
      {
        fprintf(ftopmain,"    char **argv=parse_dll_options(\"%s\",argc,"
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
        "  #if defined(__GNUDOS__) || defined(DOS386) || defined(__DPMI32__) "
        " || \\\n"
        "     defined(__MSVC32__)\n"
        "      if (!arrmblsize) arrmblsize=150000;\n"
        "  #else\n"
        "      if (!arrmblsize) arrmblsize=25000;\n"
        "  #endif\n"
        "    model_parameters mp(arrmblsize,argc,argv,ad_dll);\n"
        "    mp.iprint=10;\n");
    }	
    else
    {
      fprintf(ftopmain,"    gradient_structure::set_YES_SAVE_VARIABLES_VALUES();\n"
        "  #if defined(__GNUDOS__) || defined(DOS386) || defined(__DPMI32__) "
        " || \\\n"
        "     defined(__MSVC32__)\n"
        "      if (!arrmblsize) arrmblsize=150000;\n"
        "  #else\n"
        "      if (!arrmblsize) arrmblsize=25000;\n"
        "  #endif\n"
        "    model_parameters mp(arrmblsize,argc,argv);\n"
        "    mp.iprint=10;\n");
    }	
    

     fprintf(ftopmain,"    mp.preliminary_calculations();\n");

     fprintf(ftopmain,"    mp.computations(argc,argv);\n");

    fprintf(htop,"#include <admodel.h>\n\n");
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
    splus_debug_flag=1;
  }  
  if ( (on=option_match(argc,argv,"-no_pad"))>-1)
  {
    no_userclass=1;
  }  
  if (argc>1)
  {
    strcpy(infile_name,argv[ioff]);
    strcpy(infile_root,infile_name);
    strcpy(outfile_name,argv[ioff]);
    strcpy(headerfile_name,argv[ioff]);
    strcat(infile_name,".tpl");
    strcat(outfile_name,".cpp");
    strcat(headerfile_name,".htp");
    if (debug_flag) fprintf(stderr,"Trying to open file %s for input\n");
    yyin=fopen(infile_name,"r");
    if (!yyin)
    {
      fprintf(stderr,"Error trying to open input file %s\n",
        infile_name);
      exit(1);
    }
    if (debug_flag) fprintf(stderr,"Opened file %s for input\n");
    if (makedll) 
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
  else
  {
    strcpy(infile_name,"admodel.tpl");
    strcpy(outfile_name,"admodel.cpp");
    if (debug_flag) fprintf(stderr,"Trying to open file %s for input\n");
    yyin=fopen(infile_name,"r");
    if (!yyin)
    {
      fprintf(stderr,"Error trying to open default input file %s\n",
        infile_name);
      exit(1);
    }
    if (debug_flag) fprintf(stderr,"Opened file %s for input\n");
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
    if (strlen(s)-ipos-1 >= 0)
    {
      if (d[strlen(s)-ipos-1] == 13)   // crtl M
        d[strlen(s)-ipos-1] = '\0';
    }
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
    if (strlen(s)-ipos-1 >= 0)
    {
      if (d[strlen(s)-ipos-1] == 13)   // crtl M
        d[strlen(s)-ipos-1] = '\0';
    }
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
    if (strlen(s)-ipos-1 >= 0)
    {
      if (d[strlen(s)-ipos-1] == 13)   // crtl M
        d[strlen(s)-ipos-1] = '\0';
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
