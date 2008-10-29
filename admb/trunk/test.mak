LIBPATH =  testlib

library_directory:
	if ! -d ${LIBPATH} \
	then mkdir ${LIBPATH} \
	fi

