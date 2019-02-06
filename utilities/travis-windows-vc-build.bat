
CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" amd64
nmake CXX=cl CC=cl clean dist test
