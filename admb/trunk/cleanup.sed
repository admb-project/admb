# remove unwanted svn property fields and reformat comment block
# delete lines containing HOME_VERSION
1s/\*\*/*/
/^  \*$/d
/^  \* \$Rev/d
/^  \* \$Author/d
/^  \* \$Date/d
s/^  \* \$Id/ \* \$Id/
s/^  \* Author/ \* Author/
s/^  \* Copyright/ \* Copyright/
s/^  \*\// \*\//
/HOME_VERSION/d
# we should consider keeping this file as a record of what was done
# old changes could be commented out and new ones added
