CC = g++

TARGET = lesson1

COMPILEFLAGS = -lalut -lopenal

$(TARGET): main.o
	$(CC) -o $(TARGET) main.o  $(COMPILEFLAGS)	

main.o: main.cpp
	$(CC) -c main.cpp -Wno-deprecated

clean:
	rm -f $(TARGET) main.o

