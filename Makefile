#default targets depending on compiler
#DEBUG=yes

dist:
	$(MAKE) $(CXX)-dist DEBUG=$(DEBUG)
	@echo ADMB build dist completed.
	@echo Check README.txt for usage and installation information.
all:
	$(MAKE) $(CXX)-all DEBUG=$(DEBUG)
	@echo ADMB build all completed.
	@echo Check README.txt for usage and installation information.
core:
	$(MAKE) $(CXX)-core DEBUG=$(DEBUG)
	@echo ADMB build core completed.
debug:
	$(MAKE) $(CXX)-all DEBUG=yes
	@echo ADMB build debug completed.
contribs:
	$(MAKE) $(CXX)-contribs DEBUG=$(DEBUG)
	@echo ADMB build contribs completed.
test: verify
gtests:
	$(MAKE) $(CXX)-gtests DEBUG=$(DEBUG)
verify:
	$(MAKE) $(CXX)-verify DEBUG=$(DEBUG)
doc: $(CXX)-docs
shared: $(CXX)-shared
	$(MAKE) $(CXX)-shared DEBUG=$(DEBUG)
	@echo ADMB build shared completed.
install: $(CXX)-install
check: $(CXX)-check
	@echo "SHELL: $(SHELL)"
	@echo "PATH: $(PATH)"
	@echo "TERM: $(TERM)"
	@echo "MAKE: $(MAKE)"
	@echo "CXX: $(CXX)"
clean: $(CXX)-clean
coverage:
	$(MAKE) $(CXX)-coverage DEBUG=$(DEBUG)

help:
	@echo Read INSTALL.txt for installation help.

installer: zip

zip: $(CXX)-zip

#Microsoft Visual C++
cl: cl-all
cl-all:
	nmake /nologo cl-dist
	nmake /nologo cl-shared
	pushd src& nmake /nologo copy
cl-dist:
	nmake /nologo cl-contribs
cl-debug:
	pushd src& nmake /nologo DEBUG=!DEBUG! all
	pushd contrib& nmake /nologo DEBUG=yes all
cl-core:
	pushd src& nmake /nologo all
cl-contribs: cl-core
	pushd contrib& nmake /nologo all
cl-docs:
	pushd docs& nmake /nologo all
cl-gtests:
	pushd tests & nmake /nologo test-gtests
cl-verify:
	pushd tests& nmake /nologo verify
cl-shared:
	pushd src& nmake /nologo shared
	pushd contrib& nmake /nologo shared
cl-install:
	pushd src& nmake /nologo install
cl-check:
	pushd src& nmake /nologo check
cl-clean:
	pushd src& nmake /nologo clean
	pushd contrib& nmake /nologo clean
	pushd scripts& nmake /nologo clean
	pushd tests& nmake /nologo clean
	pushd examples& nmake /nologo clean
cl-zip:
	pushd src& nmake /nologo zip

#GNU
$(CXX): $(CXX)-all
$(CXX)-all:
	$(MAKE) $(CXX)-dist
	$(MAKE) $(CXX)-shared
	$(MAKE) --directory=src CC=$(CC) CXX=$(CXX) copy
$(CXX)-dist:
	$(MAKE) $(CXX)-core
	$(MAKE) $(CXX)-contribs
$(CXX)-debug:
	$(MAKE) $(CXX)-all DEBUG=yes
$(CXX)-core:
	$(MAKE) --directory=src CC=$(CC) CXX=$(CXX) all
$(CXX)-contribs: $(CXX)-core
	$(MAKE) --directory=contrib CC=$(CC) CXX=$(CXX) all
$(CXX)-docs:
	$(MAKE) --directory=docs CC=$(CC) CXX=$(CXX) all
$(CXX)-gtests:
	$(MAKE) --directory=tests CC=$(CC) CXX=$(CXX) unit-gtests
$(CXX)-coverage:
	$(MAKE) --directory=src CC=$(CC) CXX=$(CXX) SAFE_ONLY=yes dist
	$(MAKE) --directory=tests CC=$(CC) CXX=$(CXX) coverage
$(CXX)-verify:
	$(MAKE) --directory=tests CC=$(CC) CXX=$(CXX) verify
$(CXX)-shared:
	$(MAKE) --directory=src CC=$(CC) CXX=$(CXX) SHARED=-shared shared
	$(MAKE) --directory=contrib CC=$(CC) CXX=$(CXX) SHARED=-shared shared
$(CXX)-install:
	$(MAKE) --directory=src CC=$(CC) CXX=$(CXX) install
$(CXX)-check:
	$(MAKE) --directory=src CC=$(CC) CXX=$(CXX) check
$(CXX)-clean:
	$(MAKE) --directory=src CC=$(CC) CXX=$(CXX) clean
	$(MAKE) --directory=contrib CC=$(CC) CXX=$(CXX) clean
	$(MAKE) --directory=scripts CC=$(CC) CXX=$(CXX) clean
	$(MAKE) --directory=tests CC=$(CC) CXX=$(CXX) clean
	$(MAKE) --directory=examples CC=$(CC) CXX=$(CXX) clean
$(CXX)-zip:
	$(MAKE) --directory=src CC=$(CC) CXX=$(CXX) zip
