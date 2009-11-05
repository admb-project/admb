all:
	make --directory Example1
	@# make --directory Example2
	make --directory Example-GM

vc:
	cd Example1 && nmake vc
	@REM cd Example2 && nmake vc
	cd Example-GM && nmake vc

bcc:
	cd Example1 && make bcc
	@REM cd Example2 && make bcc
	cd Example-GM && make bcc

mingw:
	make --directory Example1 mingw
	@REM make --directory Example2 mingw
	make --directory Example-GM mingw
