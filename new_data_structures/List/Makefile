include ../../base.make

all: Command.o FileSystem.o Terminal.o XComp.o

FileSystem.o: FileSystem.cpp FileSystem.h
        $(CC) $(CFLAGS) FileSystem.cpp

Command.o: Command.cpp Command.h
        $(CC) $(CFLAGS) Command.cpp

Terminal.o: Terminal.cpp
        $(CC) $(CFLAGS) Terminal.cpp

XComp.o: XComp.cpp
        $(CC) $(CFLAGS) XComp.cpp