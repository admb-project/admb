all:
	- scp df1b2-separable/*.h df1b2-separable/*.hpp \
            linad99/*.h linad99/*.hpp \
            nh99/*.h nh99/*.hpp  \
            tools99/*.h tools99/*.hpp \
           root@192.168.1.1:/home/skaug/include_dir
	- scp nh99/tpl2cpp.exe  \
            /cygdrive/g/bin/adverifier.dll \
            /cygdrive/g/bin/libeay32.dll \
            /cygdrive/g/bin/openssl.dll /cygdrive/g/bin/ssleay32.dll \
            df1b2-separable/sed*  \
            df1b2-separable/tpl2rem.exe  \
            nh99/tpl2cpp.exe  \
            /cygdrive/l/openssl-stuff/demotpl2cpp.exe \
            /cygdrive/l/openssl-stuff/demotpl2rem.exe \
           root@192.168.1.1:/home/skaug/bin_dir
