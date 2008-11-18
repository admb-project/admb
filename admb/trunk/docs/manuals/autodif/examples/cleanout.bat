cd \auto_doc\examples
find . -name '*.obj' -print -exec rm {} \;
find . -name '*.bak' -print -exec rm {} \;
find . -name '*.sym' -print -exec rm {} \;
find . -name '*.map' -print -exec rm {} \;
find . -name '*.exe' -print -exec rm {} \;
find . -name '*.tmp' -print -exec rm {} \;
find . -name '*.o' -print -exec rm {} \;
find . -name '*.s' -print -exec rm {} \;
find . -name 'a\.out' -print -exec rm {} \;
