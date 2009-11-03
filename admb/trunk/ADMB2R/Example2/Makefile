.PHONY: rs196

rs196:
	cp -vf ../admb2r.cpp .
	dos2unix $@.dat
	dos2unix $@.tpl
	admb -s $@ 
	-./$@
