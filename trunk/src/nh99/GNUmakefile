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

tpl2cpp.c: tpl2cpp.lex
	flex -w $<
	sed -f sedflex lex.yy.c > $@

$(PREFIX_OBJ)model7.obj: model7.cpp
ifdef ADMB_CONFIGURE
	$(CXX) -DADMB_CONFIGURE="${ADMB_CONFIGURE}" $(CXXFLAGS) model7.cpp -o $(PREFIX_OBJ)model7.obj
else
	$(CXX) $(CXXFLAGS) model7.cpp -o $(PREFIX_OBJ)model7.obj
endif

$(PREFIX_OBJ)%.obj: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<
