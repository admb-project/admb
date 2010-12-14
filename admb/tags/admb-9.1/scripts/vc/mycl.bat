cl -c /EHsc -DUSE_LAPLACE -DWIN32 -DOPT_LIB /Ox -D__MSVC32__=8 -I. -I"%MSSDK%"\include -I"%ADMB_HOME%"\include %1.cpp
