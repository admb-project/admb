flex <  remod11
sed -f sedflex lex.yy.c > tpl2rem.c
bcc32 -DWIN32 -v tpl2rem.c 
