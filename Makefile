CXX = g++
LDFLAGS = -std=c++2a -O3 -lm
SOURCES = partial_order.cpp corner_link.cpp parser.cpp main.cpp
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = HTC
INCLUDES = partial_order.h corner_link.h parser.h

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

%.o:  %.c  ${INCLUDES}
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.gch $(EXECUTABLE)