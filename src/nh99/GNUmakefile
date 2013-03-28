include objects.lst

ifeq ("$(CXX)","CC")
OBJECTS = $(filter-out dfqromb.obj, $(OBJ0)) $(OBJ1) $(OBJ2) $(OBJ3)
else
OBJECTS = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3)
endif


all: $(addprefix $(PREFIX_OBJ), $(OBJECTS)) $(DISKDIR)/bin/tpl2cpp

$(DISKDIR)/bin/tpl2cpp: tpl2cpp.c
ifeq ("$(CC)","cc")
	$(CC) -o $@ $<
else
	$(CC) $(CFLAGS) -Wno-format -o $@ $<
endif

tpl2cpp.c: lex.yy.c
	if [ "`cat $^ | wc -l`" -ne 0 ]; then sed -f sedflex $^ > $@; else rm -vf $@; fi
	if [ ! -f $@ ]; then cp -vf tpl2rem-unixflex.c $@; fi
lex.yy.c: tpl2cpp.lex
	if [ `command -v flex` ]; then flex -v -w $^; else rm -vf $@; fi
	if [ ! -f $@ ]; then touch $@; fi

$(PREFIX_OBJ)banner.obj: banner.cpp
	$(CXX) -c $(CXXFLAGS) -DADMB_VERSION=$(shell cat ../../VERSION) -DADMB_REVISION=$(shell test -e ../../REVISION && cat ../../REVISION) -o $@ $^

$(PREFIX_OBJ)model7.obj: model7.cpp
ifdef ADMB_CONFIGURE
	$(CXX) -c -DADMB_CONFIGURE="${ADMB_CONFIGURE}" $(CXXFLAGS) -o $@ $^
else
	$(CXX) -c $(CXXFLAGS) -o $@ $^
endif

$(PREFIX_OBJ)%.obj: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<
