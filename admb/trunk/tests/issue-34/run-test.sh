cp -v ../../examples/admb/simple/simple.tpl simple_hypen.tpl
cp -v ../../examples/admb/simple/simple.tpl simple-hypen.tpl
cp -v ../../examples/admb/simple/simple.dat simple_hypen.dat
cp -v ../../examples/admb/simple/simple.dat simple-hypen.dat

PATH=.:$ADMB_HOME/bin:$PATH

tpl2cpp simple_hypen
tpl2cpp simple-hypen

if test "`diff simple_hypen.htp simple-hypen.htp | wc -l`" -ne "0"  ; then
  printf "ERROR: Test failed."
fi

mygcco simple_hypen
mygcco simple-hypen

simple_hypen
simple-hypen

