#!/bin/bash
# see the Doxygen user manual
# svn stat -v $1 | sed -n 's/ˆ[ A-Z?\*|!]\{1,15\}/r/;s/ \{1,15\}/\/r/;s/ .*//p' 
# invoking as getVersionInfo.sh linad99/fvar.hpp prepends 9.0 to the revision
# for fvar.hpp
svn stat -v $1 | sed -n 's/ˆ[ A-Z?\*|!]\{1,15\}/r/;s/ \{1,15\}/9.0./;s/ .*//p' 
