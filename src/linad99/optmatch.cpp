/*
 * $Id$
 *
 * Author: David Fournier
 * Copyright (c) 2008-2012 Regents of the University of California
 */

/**
\file
option_match utilities used for parsing command line arguments.
*/
#include <adstring.hpp>

/**
Checks if the program has been invoked with a particular command line argument
("string").
\param argc Number of command line arguments (as in all C programs)
\param argv Array  (of length argc) of command line arguments (as in all C
programs)
\param option Should be one of the possible command line arguments to an ADMB
program.
\return An index into "argv" where the match with "string" is obtained. In case
of no match, the value "-1" is returned.
*/
int option_match(int argc, char* argv[], const char* option)
{
  int match = -1;
  if (argv)
  {
    for (int i = 0; i < argc; i++)
    {
      const char* argvi = argv[i];
      if (argvi && !strcmp(argvi, option))
      {
        return i;
      }
    }
  }
  return match;
}
/**
 * Description not yet available.
 * \param
 */
int option_match(char* _s, const char* option)
{
  adstring ss = _s;
  char* s = (char*)ss;
  int rval = -1;
  int i = 1;
  char* p = strtok(s," ");
  do {
    if (!strcmp(p, option))
    {
      rval = i;
      break;
    }
    i++;
    p = strtok(NULL, " ");
  }
  while (p);

  return rval;
}
/**
 * Description not yet available.
 * \param
 */
int option_match(char* _s, const char* option, const int& _nopt)
{
  adstring ss = _s;
  char* s = (char*)ss;
  int& nopt = (int&)_nopt;
  int rval = -1;
  int i = 1;
  nopt = 0;
  char* p = strtok(s," ");
  do {
    if (!strcmp(p, option))
    {
      rval = i;
      break;
    }
    p = strtok(NULL, " ");
    i++;
  }
  while (p);

  bool found = false;
  do
  {
    p = strtok(NULL, " ");
    if (!p) break;
    if (p[0] == '-')
      found = true;
    nopt++;
  }
  while(!found);

  return rval;
}
/**
Checks if the program has been invoked with a particular command line argument
("string"). If so, counts the number of arguments ("nopt") to this command line
option. For example if the program has been invoked with the command line option
"-ind FILE", then nopt=1.

\param argc Number of command line arguments (as in all C programs)
\param argv Array  (of length argc) of command line arguments (as in all C programs)
\param option Should be one of the possible command line arguments to an ADMB
program.
\param nopt On return holds the number arguments/options associated with "string".
\return An index into "argv" where the match with "string" is obtained. In case
of no match, the value "-1" is returned.
*/
int option_match(int argc, char *argv[], const char *option, const int& _nopt)
{
  int match = -1;

  int& nopt = (int&)_nopt;
  nopt=0;

  int i = option_match(argc, argv, option);
  if (i >= 0)
  {
    match = i;

    for (int j = i + 1; j < argc; j++)
    {
      if (argv[j][0] == '-') break;
      nopt++;
    }
  }

  return match;
}
