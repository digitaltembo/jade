CC=g++
CFLAGS=-g -c -Wall 

FESTINC = -I/usr/include/festival/ -I/usr/include/speech_tools/
FEST = -L/usr/lib/ -l Festival -L /usr/lib/speech_tools/lib/ -l estools -l estbase -l eststring

SPHINXINC = -I/usr/include/sphinxbase -I/usr/include/pocketsphinx 
SPHINX = -lpocketsphinx -lsphinxbase -lsphinxad

EAR= -lasound -lsndfile

CVINC=-I /usr/local/include/opencv
EYE=  -L /usr/local/lib -lopencv_core -lopencv_highgui
FACE= -L /usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect  

FACETRACKERFILES= FaceTracker.o CLM.o FCheck.o FDet.o IO.o Patch.o PAW.o PDM.o Tracker.o

THREAD = -lpthread

INC = $(SPHINXINC) $(FESTINC)
LIBS = $(SPHINX) $(FEST) $(EAR) -lX11 -lpng

all: jade

jade: jade.o Dict.o Trie.o LinkedList.o LinkedListTail.o Array.o BoolArray.o
	$(CC) -o jade jade.o Dict.o Trie.o LinkedList.o LinkedListTail.o Array.o BoolArray.o

test: test.o SphinxEar.o FestVox.o XComp.o Matrix.o Ear.o Terminal.o
	$(CC) $(INC) -o test test.o SphinxEar.o FestVox.o XComp.o Matrix.o Ear.o Terminal.o $(LIBS)

wordnet: WordNetTest.o
	$(CC) -o wordnet WordNetTest.o -l wordnet

FaceTrackTest:FaceTrackTest.o Eye.o FaceTracker.o TriangleImage.o FakeWebcam.o
	$(CC) $(CVINC) -o tests/Face FaceTrackTest.o Eye.o TriangleImage.o FakeWebcam.o $(FACETRACKERFILES) $(FACE)

CommandTest:CommandTest.o Command.o
	$(CC) -o tests/com CommandTest.o Command.o $(THREAD)

wordnet.o: wordnet.cpp
	$(CC) $(CFLAGS) wordnet.cpp -l wordnet

jade.o: jade.cpp
	$(CC) $(CFLAGS) jade.cpp 

test.o: test.cpp
	$(CC) $(CFLAGS) $(INC) test.cpp 

Dict.o: data_structures/Trie/Dict.cpp
	$(CC) $(CFLAGS) data_structures/Trie/Dict.cpp
	
Trie.o: data_structures/Trie/Trie.cpp
	$(CC) $(CFLAGS) data_structures/Trie/Trie.cpp

LinkedList.o: data_structures/List/LinkedList.cpp
	$(CC) $(CFLAGS) data_structures/List/LinkedList.cpp
	
LinkedListTail.o: data_structures/List/LinkedListTail.cpp
	$(CC) $(CFLAGS) data_structures/List/LinkedListTail.cpp

Array.o: data_structures/List/Array.cpp
	$(CC) $(CFLAGS) data_structures/List/Array.cpp

BoolArray.o: data_structures/BoolArray.cpp
	$(CC) $(CFLAGS) data_structures/BoolArray.cpp

Matrix.o: Matrix.cpp
	$(CC) $(CFLAGS) -fpermissive Matrix.cpp

Vec2D.o: data_structures/Vec2D.cpp
	$(CC) $(CFLAGS) data_structures/Vec2D.cpp

FestVox.o: IO/FestVox.cpp
	$(CC) $(CFLAGS) $(FESTINC) IO/Temoral/FestVox.cpp

SphinxEar.o: IO/SphinxEar.cpp
	$(CC) $(CFLAGS) $(SPHINXINC) IO/Temoral/SphinxEar.cpp 

XComp.o: IO/XComp.cpp
	$(CC) $(CFLAGS) IO/XComp.cpp

Ear.o: IO/Ear.cpp
	$(CC) $(CFLAGS) IO/Temoral/Ear.cpp

Eye.o: IO/Occipital/Eye.cpp
	$(CC) $(CFLAGS) $(EYEINC) IO/Occipital/Eye.cpp

Terminal.o: IO/Terminal.cpp
	$(CC) $(CFLAGS) IO/Terminal.cpp

FaceTrackTest.o: tests/FaceTrackTest.cpp
	$(CC) $(CFLAGS) $(FACEINC) tests/FaceTrackTest.cpp

FaceTracker.o: IO/Occipital/FaceTracker.cpp 
	$(CC) $(CFLAGS) $(FACEINC) IO/Occipital/FaceTracker.cpp
 
CLM.o: IO/Occipital/FaceTrackerFiles/CLM.cpp IO/Occipital/FaceTrackerFiles/CLM.h
	$(CC) $(CFLAGS) $(FACEINC) IO/Occipital/FaceTrackerFiles/CLM.cpp

FCheck.o: IO/Occipital/FaceTrackerFiles/FCheck.cpp IO/Occipital/FaceTrackerFiles/FCheck.h
	$(CC) $(CFLAGS) $(FACEINC) IO/Occipital/FaceTrackerFiles/FCheck.cpp

FDet.o: IO/Occipital/FaceTrackerFiles/FDet.cpp IO/Occipital/FaceTrackerFiles/FDet.h
	$(CC) $(CFLAGS) $(FACEINC) IO/Occipital/FaceTrackerFiles/FDet.cpp

IO.o: IO/Occipital/FaceTrackerFiles/IO.cpp IO/Occipital/FaceTrackerFiles/IO.h
	$(CC) $(CFLAGS) $(FACEINC) IO/Occipital/FaceTrackerFiles/IO.cpp

Patch.o: IO/Occipital/FaceTrackerFiles/Patch.cpp IO/Occipital/FaceTrackerFiles/Patch.h
	$(CC) $(CFLAGS) $(FACEINC) IO/Occipital/FaceTrackerFiles/Patch.cpp

PAW.o: IO/Occipital/FaceTrackerFiles/PAW.cpp IO/Occipital/FaceTrackerFiles/PAW.h
	$(CC) $(CFLAGS) $(FACEINC) IO/Occipital/FaceTrackerFiles/PAW.cpp

PDM.o: IO/Occipital/FaceTrackerFiles/PDM.cpp IO/Occipital/FaceTrackerFiles/PDM.h
	$(CC) $(CFLAGS) $(FACEINC) IO/Occipital/FaceTrackerFiles/PDM.cpp

Tracker.o: IO/Occipital/FaceTrackerFiles/Tracker.cpp IO/Occipital/FaceTrackerFiles/Tracker.h
	$(CC) $(CFLAGS) $(FACEINC) IO/Occipital/FaceTrackerFiles/Tracker.cpp

Command.o: IO/Command.cpp IO/Command.h
	$(CC) $(CFLAGS) IO/Command.cpp

CommandTest.o: tests/CommandTest.cpp
	$(CC) $(CFLAGS) tests/CommandTest.cpp

TriangleImage.o: tools/TriangleImage.cpp tools/TriangleImage.h
	$(CC) $(CFLAGS) $(EYEINC) tools/TriangleImage.cpp

FakeWebcam.o: IO/Occipital/FakeWebcam.cpp IO/Occipital/FakeWebcam.h
	$(CC) $(CFLAGS) IO/Occipital/FakeWebcam.cpp

CommunicationFiles:
	$(MAKE) -C IO/Communication

ComputerFiles:
	$(MAKE) -C IO/Computer

OccipitalFiles:
	$(MAKE) -C IO/Occipital

TemporalFiles:
	$(MAKE) -C IO/Temporal

clean:
	rm -rf *o jade