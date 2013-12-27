CC = c++
CCFLAG = -Wall
OBJECTS = FConfigReader.o drv.o
INCLUDES = -I.

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o test

FConfigReader.o: FConfigReader.cpp FConfigReader.h
	$(CC) $(CFLAGS) $(INCLUDES) -c FConfigReader.cpp
drv.o: drv.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c drv.cpp

clean:
	rm -f *.o *~

