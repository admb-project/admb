SHELL=/bin/bash
all:
	rm -f bhplfine
	../../../admb bhplfine
	./bhplfine -lprof
	cmp -s loga_pl.plt old/loga_pl.plt; RETVAL=$$?;if [ $$RETVAL -eq 0 ]; then echo "OK"; else echo "NOT OK"; fi
	cmp -s logb_pl.plt old/logb_pl.plt; RETVAL=$$?;if [ $$RETVAL -eq 0 ]; then echo "OK"; else echo "NOT OK"; fi
clean: 
	rm -f *.{cov,dep,hes,bar,cor,cpp,eva,htp,log,obj,par,prf,std,rpt,plt} *~ variance bhplfine dgs2 diags
