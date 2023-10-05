all: copy pella-xml simple xpella run

run:
	./pella-xml
	./simple
	./xpella

simple: simple.tpl ADMB_XMLDoc.obj model_xml.obj
	CXXFLAGS=-I/usr/include/libxml2 LDFLAGS=-lxml2 ../../admb simple.tpl ADMB_XMLDoc.obj model_xml.obj

xpella: xpella.tpl ADMB_XMLDoc.obj model_xml.obj
	CXXFLAGS=-I/usr/include/libxml2 LDFLAGS=-lxml2 ../../admb xpella.tpl ADMB_XMLDoc.obj model_xml.obj

pella-xml: pella-xml.tpl ADMB_XMLDoc.obj model_xml.obj
	CXXFLAGS=-I/usr/include/libxml2 LDFLAGS=-lxml2 ../../admb pella-xml.tpl ADMB_XMLDoc.obj model_xml.obj

ADMB_XMLDoc.obj: ADMB_XMLDoc.cpp ADMB_XMLDoc.h
	CXXFLAGS=-I/usr/include/libxml2 ../../admb -c ADMB_XMLDoc.cpp

model_xml.obj: model_xml.cpp ADMB_XMLDoc.h
	CXXFLAGS=-I/usr/include/libxml2 ../../admb -c model_xml.cpp

copy:
	cp admodel.h ../../build/dist/include/admodel.h

clean:
	@rm -vf ADMB_XMLDoc.obj
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf eigv.rpt
	@rm -vf fmin.log
	@rm -vf mcmc_bio.csv
	@rm -vf mcmc_par.csv
	@rm -vf model_xml.obj
	@rm -vf pella-xml
	@rm -vf pella-xml.bar
	@rm -vf pella-xml.cor
	@rm -vf pella-xml.cpp
	@rm -vf pella-xml.eva
	@rm -vf pella-xml.htp
	@rm -vf pella-xml.log
	@rm -vf pella-xml.obj
	@rm -vf pella-xml.par
	@rm -vf pella-xml.rep
	@rm -vf pella-xml.std
	@rm -vf pella-xml.x00
	@rm -vf pella-xml.x01
	@rm -vf simple
	@rm -vf simple.bar
	@rm -vf simple.cor
	@rm -vf simple.cpp
	@rm -vf simple.eva
	@rm -vf simple.htp
	@rm -vf simple.log
	@rm -vf simple.obj
	@rm -vf simple.par
	@rm -vf simple.rep
	@rm -vf simple.std
	@rm -vf simple.x00
	@rm -vf simple.x01
	@rm -vf trace.log
	@rm -vf variance
	@rm -vf xpella
	@rm -vf xpella.bar
	@rm -vf xpella.cor
	@rm -vf xpella.cpp
	@rm -vf xpella.eva
	@rm -vf xpella.htp
	@rm -vf xpella.log
	@rm -vf xpella.obj
	@rm -vf xpella.par
	@rm -vf xpella.rep
	@rm -vf xpella.std
	@rm -vf xpella.x00
	@rm -vf xpella.x01
