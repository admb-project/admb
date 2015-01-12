#!/bin/bash
# see the Doxygen user manual, FILE VERSION FILTER tag
# svn stat -v $1 | sed -n 's/ˆ[ A-Z?\*|!]\{1,15\}/r/;s/ \{1,15\}/\/r/;s/ .*//p' 
# invoking as getVersionInfo.sh linad99/fvar.hpp prepends 10.0 to the revision
# for fvar.hpp
svn stat -v $1 | sed -n 's/ˆ[ A-Z?\*|!]\{1,15\}/r/;s/ \{1,15\}/10.0./;s/ .*//p' 
