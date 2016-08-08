all: gamm1 testgamm
	./gamm1
	./testgamm

gamm1: gamm1.cpp
	../../admb gamm1.cpp

testgamm: testgamm.cpp
	../../admb testgamm.cpp

clean:
	$(RM) fmin.log gamm1 gamm1.obj testgamm testgamm.obj
