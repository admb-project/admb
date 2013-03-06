/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California 
 */
/**
 * \file
 * Description not yet available.
 */
#include <admodel.h>

/**
  Checks if the program has been invoked with a particular command line argument ("string"). 
  \param argc Number of command line arguments (as in all C programs)
  \param argv Array  (of length argc) of command line arguments (as in all C programs)
  \param string Should be one of the possible command line arguments to an ADMB program.  
  \return An index into "argv" where the match with "string" is obtained. In case of no match, the value "-1" is returned.
 */

 int option_match(int argc,char * argv[],const char * string)
 {
   int rval=-1;
   for (int i=0;i<argc;i++)
   {
     if (!strcmp(argv[i],string))
     {
       rval=i;
       break;
     }
   }
   return rval;
 }

/**
 * Description not yet available.
 * \param
 */
 int option_match(char * _s,const char * string)
 {
   adstring ss=_s;
   char * s=(char*)ss;
   int rval=-1;
   int i=1;
   char * p;
   p=strtok(s," ");
   do {
     if (!strcmp(p,string))
     {
       rval=i;
       break;
     }
     i++;
     p=strtok('\0'," ");
   }
   while (p);
   return rval;
 }

/**
 * Description not yet available.
 * \param
 */
int option_match(char *_s, const char *string, const int& _nopt)
 {
   adstring ss=_s;
   char * s=(char*)ss;
   int& nopt = (int&) _nopt;
   int rval=-1;
   int i=1;
   nopt=0;
   char * p;
   p=strtok(s," ");
   do {
     if (!strcmp(p,string))
     {
       rval=i;
       break;
     }
     p=strtok('\0'," ");
     i++;
   }
   while (p);
   do 
   {
     p=strtok('\0'," ");
     if (!p) break;
     if (p[0] == '-') break;
     nopt++;
   }
   while(1);
   return rval;
 }

/**
  Checks if the program has been invoked with a particular command line argument ("string"). If so, counts the number of arguments ("nopt") to this command line option. For example if the program has been invoked with the command line option "-ind FILE", then nopt=1.
  \param argc Number of command line arguments (as in all C programs)
  \param argv Array  (of length argc) of command line arguments (as in all C programs)
  \param string Should be one of the possible command line arguments to an ADMB program.  
  \param nopt On return holds the number arguments/options associated with "string".
  \return An index into "argv" where the match with "string" is obtained. In case of no match, the value "-1" is returned.
 */
int option_match(int argc, char *argv[],const char *string, const int& _nopt)
 {
   int& nopt = (int&) _nopt;
   int rval=-1;
   int i;
   nopt=0;
   for (i=0;i<argc;i++)
   {
     if (!strcmp(argv[i],string))
     {
       rval=i;
       break;
     }
   }
   for (i=rval+1;i<argc;i++)
   {
     if (argv[i][0] == '-') break;
     nopt++;
   }
   return rval;
 }
