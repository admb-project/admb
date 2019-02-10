
CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" amd64
nmake clean
pushd src & nmake CXX=cl CC=cl SAFE_ONLY=yes CXXFLAGS=/analyze objects
