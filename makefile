PROJECTNAME=fellowship
VER=0.0.1

CPPC = g++
CC = gcc
LINK = gcc

SDLDIR = ../dep/SDL-1.2.15
TCODDIR = ../dep/libtcod-1.5.0

SOURCES_CPP = $(wildcard ./src/*.cpp) 
SOURCES_C = $(wildcard ./src/*.c) 
OBJECTS_CPP = $(addprefix ./obj/,$(notdir $(SOURCES_CPP:.cpp=.opp)))
OBJECTS_C = $(addprefix ./obj/,$(notdir $(SOURCES_C:.c=.o)))
TARGET = ./$(PROJECTNAME)-$(VER).exe

CFLAGS = -Iinclude -I$(SDLDIR)/include  -I$(TCODDIR)/include -Isrc -Wall
LDFLAGS = -Llib -L$(SDLDIR)/lib -L$(TCODDIR)/lib
LIBS = -ltcod-mingw -lSDL -mwindows -lm

default: $(TARGET)
	

obj/%.o: $(SOURCES_C)
	$(CC) -o $@ $(CFLAGS) -c $<

obj/%.opp: $(SOURCES_CPP)
	$(CPPC) -o $@ $(CFLAGS) -c $<

$(TARGET):$(OBJECTS_CPP) $(OBJECTS_C)
	$(CPPC) -o $(TARGET) $(LDFLAGS) $(OBJECTS_C) $(OBJECTS_CPP) $(LIBS)

clean:
	rm -f $(OBJECTS_CPP) $(OBJECTS_C)
	rm -f $(TARGET)

rebuild:clean default

re:clean default

