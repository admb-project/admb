.PHONY: rs196 mingw

rs196:
	cp -vf ../admb2r.cpp .
	admb -s $@ 
	-./$@

mingw:
	cp -vf ../admb2r.cpp .
	admb -s rs196
	-./rs196.exe

bcc:
	cp -vf ../admb2r.cpp .
	admb -s rs196
	rs196.exe

vc:
	cp -vf ../admb2r.cpp .
	admb -s rs196
	rs196.exe
