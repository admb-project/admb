.ONESHELL:
ifeq ($(OS),Windows_NT)
EXT=.sh
ifneq ("$(shell echo %PATH%)","%PATH%")
SHELL=cmd
endif
endif

ifeq ($(SHELL),cmd)
  ifeq ($(SAFE_ONLY),yes)
all: $(addprefix $(CONTRIB_OBJS_DIR)-saflp-, $(OBJECTS))
  else
all: $(addprefix $(CONTRIB_OBJS_DIR)-saflp-, $(OBJECTS)) $(addprefix $(CONTRIB_OBJS_DIR)-optlp-, $(OBJECTS))
  endif

$(CONTRIB_OBJS_DIR)-saflp-%.obj: %.cpp
	..\..\admb.cmd -c $(OPTION) $<
	copy $(basename $<).obj $@

$(CONTRIB_OBJS_DIR)-optlp-%.obj: %.cpp
	..\..\admb.cmd -c -f $(OPTION) $<
	copy $(basename $<).obj $@
else
  ifeq ($(SAFE_ONLY),yes)
all: $(addprefix $(CONTRIB_OBJS_DIR)-saflp-, $(OBJECTS))
  else
all: $(addprefix $(CONTRIB_OBJS_DIR)-saflp-, $(OBJECTS)) $(addprefix $(CONTRIB_OBJS_DIR)-optlp-, $(OBJECTS))
  endif

$(CONTRIB_OBJS_DIR)-saflp-%.obj: %.cpp
	../../admb$(EXT) -c $(OPTION) $<
	cp $(basename $<).obj $@

$(CONTRIB_OBJS_DIR)-optlp-%.obj: %.cpp
	../../admb$(EXT) -c -f $(OPTION) $<
	cp $(basename $<).obj $@
endif

includes:
ifeq ($(SHELL),cmd)
	for %%a in ($(HEADERS)) do copy %%a $(CONTRIB_INCLUDE)
else
	cp $(HEADERS) $(CONTRIB_INCLUDE)
endif

test:
ifneq ($(SHELL),cmd)
	$(MAKE) --directory=tests
endif

clean:
ifeq ($(SHELL),cmd)
	del /Q $(OBJECTS) 2>nul
else
	@rm -vf $(OBJECTS)
endif
