.ONESHELL:
ifeq ($(OS),Windows_NT)
  ifneq ($(findstring sh.exe,$(shell where sh.exe)),sh.exe)
    CMDSHELL=cmd
  else
    EXT=.sh
  endif
endif

ifeq ($(CMDSHELL),cmd)
  ifeq ($(SAFE_ONLY),yes)
all: $(addprefix $(CONTRIB_OBJS_DIR)-saflp-, $(OBJECTS))
  else
all: $(addprefix $(CONTRIB_OBJS_DIR)-saflp-, $(OBJECTS)) $(addprefix $(CONTRIB_OBJS_DIR)-optlp-, $(OBJECTS))
  endif

$(CONTRIB_OBJS_DIR)-saflp-%.obj: %.cpp
	..\..\admb.cmd -c $(OPTION) $<
	copy $(basename $<).obj "$@"

$(CONTRIB_OBJS_DIR)-optlp-%.obj: %.cpp
	..\..\admb.cmd -c -f $(OPTION) $<
	copy $(basename $<).obj "$@"
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
ifeq ($(CMDSHELL),cmd)
	for %%a in ($(HEADERS)) do copy %%a $(CONTRIB_INCLUDE)
else
	cp $(HEADERS) $(CONTRIB_INCLUDE)
endif

test:
ifeq ($(CMDSHELL),cmd)
	$(MAKE) --directory=tests
endif

clean:
ifeq ($(CMDSHELL),cmd)
	del /Q $(OBJECTS) 2>nul
else
	@rm -vf $(OBJECTS)
endif
