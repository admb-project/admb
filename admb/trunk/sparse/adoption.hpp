#ifndef _ADOPTIONS_
#define _ADOPTIONS_
#include <adstring.hpp>

class command_line_option
{
  adstring option_flag;
  int num_arguments;
  adstring_array arguments;
  allocate(adstring& _option_flag,int_num_arguments,
}

class possible_option
{
  adstring_array option_flags;
  ivector _num_arguments;
  possible_option(adstring_array& _option_flags,ivector _num_arguments)
  {
    option_flags=_option_flags;
    num_arguments=_num_arguments;
  }
}

class command_line_options_list
{
  int num_options
  command_line_options * options;
  command_line_options_list(int argc, char * argv[],  
    possible_options& po)
  {
    int i=1;
    {
      adstring tmp=argv[i];
      if (tmp(1)!= '-')  // this identifies it as an option
      {
          cerr << "Unrecognized command line option " << tmp << endl;
          exit(1);
      }
      else
      {
        optno = match(tmp,po);  // does this option match an allowable one
        if (!optno)
        {
          cerr << "Unrecognized command line option " << tmp << endl;
          exit(1);
        }
        int no=po.num_arguments(optno);
        for (int j=1;j<=po.num_arguments;j++)
        {
          if (++i > argc)
          {
            cerr << "Not enough arguments passed to command line option "
                 << tmp << endl;
            exit(1);
          }
          else
          {
            adstring tmp1=argv[i];
            if (tmp1(i)= '-')  // this identifies it as an option
            {
              cerr << "Not enough arguments passed to command line option "
                 << tmp << endl;
              exit(1);
            }
        
 
      }   
    }
    
}



#endif
