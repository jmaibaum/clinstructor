CC=cc
CFLAGS=-Wall -c
LDFLAGS=-Wall
VPATH=src/
SOURCES=main.c parse-hex.c cpu-2650.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=clinstructor

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean cleanexe cleanobj cleanmisc

clean: cleanexe cleanobj cleanmisc

cleanexe:
	rm -rf $(EXECUTABLE)

cleanobj:
	rm -rf *.o

cleanmisc:
	rm -rf *~
