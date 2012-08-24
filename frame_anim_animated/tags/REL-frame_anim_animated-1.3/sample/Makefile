################################################################################
# This Makefile has been build with soe.
# File built on Sun Sep 27 23:15:18 2009
################################################################################
TOOLCHAIN=g++
EXE=sample
DFLAGS=
OFLAGS=
CFLAGS=-framework OpenGL -framework sfml-system -framework sfml-window -framework sfml-graphics -I../src/ -I../../../pausableclock/tags/REL-pausableclock-1.3/src/ -arch i386
all : $(EXE)
clean :
	rm -f *.o
mrproper : clean
	rm -f $(EXE)
$(EXE) : main.cpp.o ../src/animated.cpp.o ../src/frame.cpp.o 
	$(TOOLCHAIN) -o $(EXE) main.cpp.o ../src/animated.cpp.o ../src/frame.cpp.o $(DFLAGS) $(PFLAGS) $(CFLAGS) $(OFLAGS) 
main.cpp.o : main.cpp
	$(TOOLCHAIN) -o main.cpp.o -c main.cpp $(DFLAGS) $(PFLAGS) $(CFLAGS) $(OFLAGS) 
../src/animated.cpp.o : ../src/animated.cpp
	$(TOOLCHAIN) -o ../src/animated.cpp.o -c ../src/animated.cpp $(DFLAGS) $(PFLAGS) $(CFLAGS) $(OFLAGS) 
../src/frame.cpp.o : ../src/frame.cpp
	$(TOOLCHAIN) -o ../src/frame.cpp.o -c ../src/frame.cpp $(DFLAGS) $(PFLAGS) $(CFLAGS) $(OFLAGS) 
