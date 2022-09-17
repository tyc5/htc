CC = g++-12
LDFLAGS = -std=c++20 -O3 -lm
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