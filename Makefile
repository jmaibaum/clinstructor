INSTALLPATH=/usr/local/bin

CC=cc
CFLAGS=-Wall
LDFLAGS=-Wall
VPATH=src/
SOURCES=main.c parse-hex.c cpu-2650.c os-timer.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=clinstructor

ifeq ($(WIN),y)
   CROSS=i686-pc-mingw32-
   CC=gcc
   EXECUTABLE:=$(EXECUTABLE).exe
   ARCH=win
else
   ARCH=posix
endif
VPATH:=$(VPATH) src/$(ARCH)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CROSS)$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CROSS)$(CC) $(CFLAGS) -I src/$(ARCH) -c $< -o $@

.PHONY: clean cleanexe cleanobj cleanmisc win install

clean: cleanexe cleanobj cleanmisc

cleanexe:
	rm -rf $(EXECUTABLE) $(EXECUTABLE).exe

cleanobj:
	rm -rf *.o

cleanmisc:
	rm -rf *~


# Cross compile for Windows: make win
# If you're looking for a cross compiler for Windows designed to
# run on any Unix sytem (Linux, Mac OS X, *BSD...): http://mxe.cc
win:
	make clean		# Drop any *NIX object files
	make WIN=y		# Cross compile for Windows

install:
	install $(EXECUTABLE) $(INSTALLPATH)
