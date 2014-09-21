include ../../base.make

all: Command.o FileSystem.o Terminal.o XComp.o

FileSystem.o: FileSystem.cpp FileSystem.h
	$(CC) $(CFLAGS) FileSystem.cpp

Command.o: Command.cpp Command.h
	$(CC) $(CFLAGS) Command.cpp

Terminal.o: Terminal.cpp Terminal.h
	$(CC) $(CFLAGS) Terminal.cpp

XComp.o: XComp.cpp XComp.h ../../new_data_structures/Image/Img.h ../../new_data_structures/Image/Img.cpp
	$(CC) $(CFLAGS) XComp.cpp ../../new_data_structures/Image/Img.cpp

XWindow.o: XWindow.cpp XWindow.h
	$(CC) $(CFLAGS) XWindow.cpp