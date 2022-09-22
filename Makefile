CXX = g++
LDFLAGS = -std=c++2a -O3 -lm
SOURCES = corner_link.cpp parser.cpp main.cpp
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = HTC
INCLUDES = corner_link.h parser.h

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

%.o:  %.c  ${INCLUDES}
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.gch $(EXECUTABLE)