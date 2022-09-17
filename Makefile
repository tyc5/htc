CC = g++
LDFLAGS = -std=c++11 -O3 -lm
SOURCES = parser.cpp main.cpp
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = HTC
INCLUDES = parser.h

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o:  %.c  ${INCLUDES}
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.gch $(EXECUTABLE)