all:
	cd linad99; MAKE "OPTIONS=/MD /EHsc" -f optmsc7.mak  all
	cd linad99; MAKE "OPTIONS=/MD /EHsc" -f safmsc7.mak  all
	cd tools99; MAKE "OPTIONS=/MD /EHsc" -f optmsc7.mak  all
	cd nh99; MAKE "OPTIONS=/MD /EHsc" -f optmsc7.mak  all

clean:
	cd linad99; MAKE -f optmsc7.mak  clean
	cd linad99; MAKE -f safmsc7.mak   clean
	cd tools99; MAKE -f optmsc7.mak   clean
	cd nh99; MAKE -f optmsc7.mak   clean

simpleall:
	cd linad99; MAKE  -f optmsc7.mak  all
	cd linad99; MAKE  -f safmsc7.mak  all
	cd tools99; MAKE  -f optmsc7.mak  all
	cd tools99; MAKE  -f safmsc7.mak  all
	cd nh99; MAKE  -f optmsc7.mak  all
	cd nh99; MAKE  -f safmsc7.mak  all

yukio-all:
	cd linad99; MAKE LIBNAME=ado32.lib  LIBPATH=yukio-msc7o DISKDIR=g:\msvc71-yukio "OPTIONS= -DUSE_ADPVM /MLd /G7 /arch:SSE2 /EHsc" -f optmsc7.mak  all
	cd tools99; MAKE LIBNAME=adto32.lib  LIBPATH=yukio-msc7o DISKDIR=g:\msvc71-yukio "OPTIONS= -DUSE_ADPVM /MLd /G7 /arch:SSE2 /EHsc" -f optmsc7.mak  all
	cd nh99; MAKE LIBNAME=admodo32.lib  LIBPATH=yukio-msc7o DISKDIR=g:\msvc71-yukio "OPTIONS= -DUSE_ADPVM /MLd /G7 /arch:SSE2 /EHsc" -f optmsc7.mak  all
	cd linad99; MAKE LIBNAME=ads32.lib  LIBPATH=yukio-msc7s DISKDIR=g:\msvc71-yukio "OPTIONS= -DUSE_ADPVM /DDEBUG /Od /EHsc /RTC1 /MLd /Zi /Fd$*.pdb " -f safmsc7.mak  all
	cd tools99; MAKE LIBNAME=adts32.lib  LIBPATH=yukio-msc7s DISKDIR=g:\msvc71-yukio "OPTIONS= -DUSE_ADPVM /DDEBUG /Od /EHsc /RTC1 /MLd /Zi /Fd$*.pdb " -f safmsc7.mak  all
	cd nh99; MAKE LIBNAME=admods32.lib  LIBPATH=yukio-msc7s DISKDIR=g:\msvc71-yukio "OPTIONS= -DUSE_ADPVM /DDEBUG /Od /EHsc /RTC1 /MLd /Zi /Fd\$*.pdb " -f safmsc7.mak  all

test-yukio:
	cd linad99; MAKE LIBNAME=ads32.lib  LIBPATH=yukio-msc7s DISKDIR=e:\msvc71-yukio "OPTIONS= -DUSE_ADPVM /DDEBUG /Od /EHsc /RTC1 /MLd /Zi /Fd\$*.pdb " -f safmsc7.mak  all

yukio-clean:
	cd linad99; MAKE LIBNAME=ado32.lib  LIBPATH=yukio-msc7o DISKDIR=e:\msvc71-yukio "OPTIONS= -DUSE_ADPVM /MLd /G7 /arch:SSE2 /EHsc" -f optmsc7.mak  clean
	cd tools99; MAKE LIBNAME=adto32.lib  LIBPATH=yukio-msc7o DISKDIR=e:\msvc71-yukio "OPTIONS= -DUSE_ADPVM /MLd /G7 /arch:SSE2 /EHsc" -f optmsc7.mak  clean
	cd nh99; MAKE LIBNAME=admodo32.lib  LIBPATH=yukio-msc7o DISKDIR=e:\msvc71-yukio "OPTIONS= -DUSE_ADPVM /MLd /G7 /arch:SSE2 /EHsc" -f optmsc7.mak  clean

	cd linad99; MAKE LIBNAME=ads32.lib  LIBPATH=yukio-msc7s DISKDIR=e:\msvc71-yukio "OPTIONS= -DUSE_ADPVM /DDEBUG /Od /EHsc /RTC1 /MLd /Zi /Fd$*.pdb " -f safmsc7.mak  clean
	cd tools99; MAKE LIBNAME=adts32.lib  LIBPATH=yukio-msc7s DISKDIR=e:\msvc71-yukio "OPTIONS= -DUSE_ADPVM /DDEBUG /Od /EHsc /RTC1 /MLd /Zi /Fd$*.pdb " -f safmsc7.mak  clean
	cd nh99; MAKE LIBNAME=admods32.lib  LIBPATH=yukio-msc7s DISKDIR=e:\msvc71-yukio "OPTIONS= -DUSE_ADPVM /DDEBUG /Od /EHsc /RTC1 /MLd /Zi /Fd\$*.pdb " -f safmsc7.mak  clean

