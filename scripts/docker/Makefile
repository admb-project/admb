#Note: In Docker Desktop, must switch build container to linux or windows mode.

ifeq ($(OS),Windows_NT)
  ifndef TERM
    ISCMDSHELL=yes
    TARGET=windows
  endif
endif

ifndef TARGET
TARGET=linux
endif

all:
	$(MAKE) $(TARGET)
	$(MAKE) docs
	
$(TARGET):
	$(MAKE) --directory=admb-$(TARGET)


run:
	$(MAKE) --directory=admb-$(TARGET) run

console:
	$(MAKE) --directory=admb-$(TARGET) console

docs:
	$(MAKE) readme.html
	$(MAKE) quickstart-windows.html
	$(MAKE) quickstart-unix.html

readme.html: readme.md
ifneq ($(ISCMDSHELL),yes)
	cat html/begin.html>$@
	cat html/admarkdown.css>>$@
	cat html/begin2.html>>$@
	python3 -m markdown readme.md >>$@
	cat html/end.html>>$@
endif

quickstart-windows.html: quickstart-windows.md
ifneq ($(ISCMDSHELL),yes)
	cat html/begin.html>$@
	cat html/admarkdown.css>>$@
	cat html/begin2.html>>$@
	python3 -m markdown quickstart-windows.md >>$@
	cat html/end.html>>$@
endif

quickstart-unix.html: quickstart-unix.md
ifneq ($(ISCMDSHELL),yes)
	cat html/begin.html>$@
	cat html/admarkdown.css>>$@
	cat html/begin2.html>>$@
	python3 -m markdown quickstart-unix.md >>$@
	cat html/end.html>>$@
endif

clean:
ifeq ($(OS),Windows_NT)
	$(MAKE) --directory admb-windows clean
endif
	$(MAKE) --directory admb-linux clean

ifeq ($(ISCMDSHELL),yes)
	if exist readme.html del readme.html
	if exist quickstart-unix.html del quickstart-unix.html
	if exist quickstart-windows.html del quickstart-windows.html
else
	rm -vf readme.html
	rm -vf quickstart-unix.html
	rm -vf quickstart-windows.html
endif

clean-docker:
	-docker container rm `docker container ps --quiet --all`
	-docker image rm `docker image ls --quiet --all`
	-docker builder prune --all --force
