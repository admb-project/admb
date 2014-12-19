ADMB_HOME=$(ADMB_HOME)
PATH=$(ADMB_HOME)\bin;$(PATH)

all: colfill

colfill: colfill.tpl
	admb colfill.tpl
	colfill -nohess

clean:
	del admodel.cov
	del admodel.dep
	del admodel.hes
	del eigv.rpt
	del colfill.bar
	del colfill.cor
	del colfill.cpp
	del colfill.eva
	del colfill.exe
	del colfill.htp
	del colfill.log
	del colfill.obj
	del colfill.par
	del colfill.std
	del fmin.log
	del variance
