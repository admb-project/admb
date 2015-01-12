bcc:
	cd Example1
	make bcc
	cd ..
	cd Example-GM
	make bcc
	cd ..

gcc:
	make --directory Example1
	@# make --directory Example2
	make --directory Example-GM

vc:
	cd Example1 && nmake vc
	@REM cd Example2 && nmake vc
	cd Example-GM && nmake vc

mingw:
	make --directory Example1 mingw
	make --directory Example-GM mingw
