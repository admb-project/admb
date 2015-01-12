



CC = ztc

CFLAGS = -c -mx -f -DOPT_LIB -DUSE_GFX_GRAPHICS -I.;l:\\linad94x;e:\\tools94





.SUFFIXES: .obj .cpp 



include objects.lst



all :  $(OBJ0)  $(OBJ1)



$(OBJ0): %.obj: %.cpp

	$(CC) $(CFLAGS) -o$*  $*.cpp





