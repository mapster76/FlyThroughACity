CC = g++

TARGET = lesson1

COMPILEFLAGS = -lalut -lopenal

$(TARGET): player.o 
	$(CC) -o $(TARGET) player.o $(COMPILEFLAGS)	

player.o: player.cpp
	$(CC) -c player.cpp -Wno-deprecated

clean:
	rm -f $(TARGET) main.o

