all: clean run

run: test_admb_messages
	./test_admb_messages

test_admb_messages: test_admb_messages.o
	export ADMB_HOME=/Users/johnoel/Desktop/admb-trunk3/build/admb-macos10.6.3-xcode3.2.2-64bit/dist; export PATH=/Users/johnoel/Desktop/admb-trunk3/build/admb-macos10.6.3-xcode3.2.2-64bit/dist/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS="-L/usr/local/gtest-1.5.0/lib -lgtest" adlink test_admb_messages

test_admb_messages.o: test_admb_messages.cpp admb_messages.h
	export ADMB_HOME=/Users/johnoel/Desktop/admb-trunk3/build/admb-macos10.6.3-xcode3.2.2-64bit/dist; export PATH=/Users/johnoel/Desktop/admb-trunk3/build/admb-macos10.6.3-xcode3.2.2-64bit/dist/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS="-L/usr/local/gtest-1.5.0/lib -lgtest" adcomp test_admb_messages

clean:
	@rm -vf test_admb_messages.o
	@rm -vf test_admb_messages
