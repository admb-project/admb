.ONESHELL:
ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
SHELL = cmd
endif
ifeq ($(OS),Windows_NT)
EXT=.sh
endif

ifeq ($(SHELL),cmd)
all: $(addprefix $(CONTRIB_OBJS_DIR)\saflp-contrib-, $(OBJECTS)) $(addprefix $(CONTRIB_OBJS_DIR)\optlp-contrib-, $(OBJECTS))

$(CONTRIB_OBJS_DIR)\saflp-contrib-%.obj: %.cpp
	..\..\admb -c $(OPTION) $<
	copy $(basename $<).obj $@

$(CONTRIB_OBJS_DIR)\optlp-contrib-%.obj: %.cpp
	..\..\admb -c -f $(OPTION) $<
	copy $(basename $<).obj $@
else
all: $(addprefix $(CONTRIB_OBJS_DIR)/saflp-contrib-, $(OBJECTS)) $(addprefix $(CONTRIB_OBJS_DIR)/optlp-contrib-, $(OBJECTS))

$(CONTRIB_OBJS_DIR)/saflp-contrib-%.obj: %.cpp
	../../admb$(EXT) -c $(OPTION) $<
	cp $(basename $<).obj $@

$(CONTRIB_OBJS_DIR)/optlp-contrib-%.obj: %.cpp
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
	del /Q $(OBJECTS)
else
	@rm -vf $(OBJECTS)
endif
