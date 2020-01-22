.ONESHELL:

ifeq ($(OS),Windows_NT)
  ifneq ($(findstring sh.exe,$(shell where sh.exe)),sh.exe)
    CMDSHELL=cmd
  else
    EXT=.sh
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
	..\..\admb.cmd -c $(OPTION) $<
	copy $(basename $<).obj "$@"
else
	../../admb$(EXT) -c $(OPTION) $<
	cp $(basename $<).obj $@
endif

$(OPT_PREFIX)%.obj: %.cpp
ifeq ($(CMDSHELL),cmd)
	..\..\admb.cmd -c -f $(OPTION) $<
	copy $(basename $<).obj "$@"
else
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
