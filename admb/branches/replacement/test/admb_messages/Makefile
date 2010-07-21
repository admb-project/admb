all: clean run

run: test_admb_messages
	./test_admb_messages

test_admb_messages: test_admb_messages.o
	export ADMB_HOME=/Users/johnoel/Desktop/admb-trunk3/build/admb-macos10.6.3-xcode3.2.2-64bit/dist; export PATH=/Users/johnoel/Desktop/admb-trunk3/build/admb-macos10.6.3-xcode3.2.2-64bit/dist/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS="-L/usr/local/gtest-1.5.0/lib -lgtest" adlink ${OPTIONS} test_admb_messages

test_admb_messages.o: test_admb_messages.cpp
	export ADMB_HOME=/Users/johnoel/Desktop/admb-trunk3/build/admb-macos10.6.3-xcode3.2.2-64bit/dist; export PATH=/Users/johnoel/Desktop/admb-trunk3/build/admb-macos10.6.3-xcode3.2.2-64bit/dist/bin:${PATH}; CXXFLAGS=-I/usr/local/gtest-1.5.0/include LDFLAGS="-L/usr/local/gtest-1.5.0/lib -lgtest" adcomp ${OPTIONS} test_admb_messages

clean:
	@rm -vf test_admb_messages.o
	@rm -vf test_admb_messages

check:
	cd ../../src; grep -r --exclude=*.svn-base cerr * > ../test/admb_messages/current-cerr.txt; cd ../test/admb_messages
