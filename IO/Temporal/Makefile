include ../../base.make

all: Ear.o FestVox.o SphinxEar.o

Ear.o: Ear.cpp
	$(CC) $(CFLAGS) Ear.cpp

FestVox.o: FestVox.cpp
	$(CC) $(CFLAGS) -I/usr/include/festival/ -I/usr/include/speech_tools/ FestVox.cpp

SphinxEar.o: SphinxEar.cpp
	$(CC) $(CFLAGS) -I/usr/include/sphinxbase -I/usr/include/pocketsphinx SphinxEar.cpp

