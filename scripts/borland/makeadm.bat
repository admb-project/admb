tpl2cpp %1
bcc32 -O2 -5 -H -DDOS386;OPT_LIB -I. -f %1.cpp admod32.lib orl32.lib ado32.lib
