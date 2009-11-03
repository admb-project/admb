.PHONY: gm_menhaden

gm_menhaden:
	cp -vf ../admb2r.cpp .
	dos2unix $@.tpl
	dos2unix $@.dat
	admb -s $@
	./$@
