#!/usr/bin/gawk -f
BEGIN {
  FS="[> <]"
  tplSection = "syn keyword tplSection FUNCTION"
  tplSection = tplSection" LOCAL_CALCS END_CALCS"
  dataType = ""
  paramType = ""
  tplType = ""
  VIM = "tpl.vim"

  print "\" ADModel Builder extentions to C++ context highlighting" > VIM
  print "\" created by vimsyntax.sh from "ARGV[1] >> VIM
  print "\"" >> VIM
  print "\" ----------------------------------------------------------------------------" >> VIM
  print "\" THE BEER-WARE LICENSE (Unknown Revision) http://en.wikipedia.org/wiki/Beerware:" >> VIM
  print "\" sibert@hawaii.edu wrote this file. As long as you retain this notice you" >> VIM
  print "\" can do whatever you want with this stuff. If you think this code as been" >> VIM
  print "\" useful in some way you send me a virtual beer. Better yet, please and consider" >> VIM
  print "\" making a contribution to admb-foundation.org." >> VIM
  print "\" Copyright (c) ADMB Foundation." >> VIM
  print "\" ----------------------------------------------------------------------------" >> VIM
  print "\"" >> VIM
  print "\" Import the C++ syntax to start with" >> VIM
  print "if version < 600" >> VIM
  print "  so <sfile>:p:h/c++.vim" >> VIM
  print "else" >> VIM
  print "  runtime! syntax/cpp.vim" >> VIM
  print "  unlet b:current_syntax" >> VIM
  print "end" >> VIM
  print "\"" >> VIM
}

{
  if ($1 != "s")
  {
    if ($2 == "DEFINE_DATA" && $3 != "^[")
    {
      dataType = dataType " " $3
    }
    else if ($2 == "DEFINE_PARAMETERS" && $3 != "^[")
    {
      paramType = paramType " " $3
    }
    else if (match($1, "^[A-Z].*_SECTION") > 0)
    {
       tplSection = tplSection " " $1
    }
  }
}

END{
  tmpType = dataType" "paramType
  split(tmpType,tmpTypeArray," ")
  nTmp = asort(tmpTypeArray)
  tplType = "syn keyword tplType "tmpTypeArray[1]

  i = 1
  j = 2
  while ((i < nTmp) && (j < nTmp))
  {
    if ((tmpTypeArray[j] == tmpTypeArray[i]) && (j < nTmp))
    {
      ++j
    }
    else
    {
      tplType = tplType" "tmpTypeArray[j]
      i = j
      ++j
    }
  }

  print tplSection >> VIM
  print tplType >> VIM

  print "\" Default highlighting" >> VIM
  print "if version >= 508 || !exists(\"did_tpl syntax_inits\")" >> VIM
  print "  if version < 508" >> VIM
  print "    let did_tpl_syntax_inits = 1" >> VIM
  print "    command -nargs=+ HiLink hi link <args>" >> VIM
  print "  else" >> VIM
  print "    command -nargs=+ HiLink hi def link <args>" >> VIM
  print "  endif" >> VIM

  print "  HiLink tplSection		Statement" >> VIM
  print "  HiLink tplType		Type" >> VIM
  print "  delcommand HiLink" >> VIM
  print "endif" >> VIM

  print "let b:current_syntax = \"tpl\"" >> VIM

  print "\"vim: ts=8" >> VIM
}
