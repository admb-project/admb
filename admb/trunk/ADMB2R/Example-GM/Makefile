.PHONY: gm_menhaden mingw

gm_menhaden:
	cp -vf ../admb2r.cpp .
	admb -s $@
	./$@

mingw:
	cp -vf ../admb2r.cpp .
	admb -s gm_menhaden
	./gm_menhaden.exe
