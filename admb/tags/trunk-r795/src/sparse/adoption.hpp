/**
 * $Id$
 *
 * $Rev   ::                       $: Revision of last commit
 * $Author::                       $: Author of last commit
 * $Date  ::                       $: Date of last commit
 *
 * Author: David Fournier
 * Copyright (c) 2008 Regents of the University of California
 * 
 * License:
 *
 * ADModelbuilder and associated libraries and documentations are
 * provided under the general terms of the "New BSD" license
 * 
 * Copyright (c)  2008 Regents of the University of California.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2.  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * 3.  Neither the name of the  University of California, Otter Research,
 * nor the ADMB Foundation nor the names of its contributors may be used
 * to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


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
