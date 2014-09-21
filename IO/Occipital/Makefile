include ../../base.make

all: Eye.o FaceTracker.o FaceTrackerMake FakeWebcam.o OCR.o ZipReader.o \
     SimpleDisplay.o

Eye.o: Eye.cpp Eye.h
	$(CC) $(CFLAGS) -I /usr/local/include/opencv Eye.cpp

FaceTrackerMake:
	$(MAKE) -C FaceTrackerFiles

FaceTracker.o: FaceTracker.cpp  FaceTracker.h
	$(CC) $(CFLAGS) FaceTracker.cpp

FakeWebcam.o: FakeWebcam.cpp FakeWebcam.h
	$(CC) $(CFLAGS) FakeWebcam.cpp

OCR.o: OCR.cpp OCR.h
	$(CC) $(CFLAGS) OCR.cpp

ZipReader.o: ZipReader.cpp ZipReader.h
	$(CC) $(CFLAGS) ZipReader.cpp

SimpleDisplay.o: SimpleDisplay.cpp SimpleDisplay.h
	$(CC) $(CFLAGS) SimpleDisplay.cpp