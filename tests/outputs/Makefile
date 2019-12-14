all:
	$(MAKE) check-rtools
	$(MAKE) check-rtools-redhat

check-rtools-vc: outputs-windows10_rtools35b.txt outputs-windows10_vs16.txt
	./outputs-diff.sh outputs-windows10_rtools35b.txt outputs-windows10_vs16.txt


check-rtools-redhat: outputs-windows10_rtools35b.txt outputs-redhat7_gcc.txt
	./outputs-diff.sh outputs-windows10_rtools35b.txt outputs-redhat7_gcc.txt

check-rtools: outputs-windows10_rtools35b.txt outputs-windows10_rtools40.txt
	./outputs-diff.sh outputs-windows10_rtools35b.txt outputs-windows10_rtools40.txt

outputs-windows10_rtools35.txt:
	wget http://buildbot.admb-project.org/outputs/outputs-windows10_rtools35.txt

outputs-windows10_rtools40.txt:
	wget http://buildbot.admb-project.org/outputs/outputs-windows10_rtools40.txt

outputs-windows10_rtools35b.txt: outputs-windows10_rtools35.txt
	cat outputs-windows10_rtools35.txt | sed 's/e-0/e-/g' | sed 's/e+0/e+/g' > outputs-windows10_rtools35b.txt
