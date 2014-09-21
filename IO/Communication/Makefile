include ../../base.make

all: Email.o Net.o

Email.o: Email.h Email.cpp
	$(CC) $(CFLAGS) Email.cpp

Net.o: Net.h Net.cpp
	$(CC) $(CFLAGS) Net.cpp -lcurl