ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifeq ($(findstring sh.exe,$(shell where sh.exe 2>&1 | findstr sh.exe)),sh.exe)
      EXT=.sh
    else
      SHELL=cmd
      CMDSHELL=cmd
    endif
  endif
endif

ifndef CONTRIB_OBJS_DIR
CONTRIB_OBJS_DIR=.
endif

ifeq ($(CMDSHELL),cmd)
SAFE_PREFIX=$(CONTRIB_OBJS_DIR)\saflp-contrib-
OPT_PREFIX=$(CONTRIB_OBJS_DIR)\optlp-contrib-
else
SAFE_PREFIX=$(CONTRIB_OBJS_DIR)/saflp-contrib-
OPT_PREFIX=$(CONTRIB_OBJS_DIR)/optlp-contrib-
endif

ifeq ($(SAFE_ONLY),yes)
all: $(addprefix $(SAFE_PREFIX), $(OBJECTS))
else
all: $(addprefix $(SAFE_PREFIX), $(OBJECTS)) $(addprefix $(OPT_PREFIX), $(OBJECTS))
endif

$(SAFE_PREFIX)%.obj: %.cpp
ifeq ($(CMDSHELL),cmd)
	..\..\admb.cmd -c $(OPTION) -o "$@" $<
else
	../../admb$(EXT) -c $(OPTION) -o $@ $<
endif

$(OPT_PREFIX)%.obj: %.cpp
ifeq ($(CMDSHELL),cmd)
	..\..\admb.cmd -c -f $(OPTION) -o "$@" $<
else
	../../admb$(EXT) -c -f $(OPTION) -o $@ $<
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
