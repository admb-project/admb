.PHONY: testadmb2r mingw

testadmb2r:
	cp -vf ../admb2r.cpp .
	admb -s $@
	./$@

mingw:
	cp -vf ../admb2r.cpp .
	admb.bat -s testadmb2r
	testadmb2r.exe

bcc:
	cp -vf ../admb2r.cpp .
	admb -s testadmb2r
	testadmb2r.exe

vc:
	copy ..\admb2r.cpp .
	admb -s testadmb2r
	testadmb2r.exe
