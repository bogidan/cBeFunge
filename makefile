PROJECTNAME=cBeFunge
VER=0.0.1

CC = gcc
LINK = gcc

SOURCES_C = $(wildcard ./src/*.c) 
OBJECTS_C = $(addprefix ./obj/,$(notdir $(SOURCES_C:.c=.o)))
TARGET = ./$(PROJECTNAME)-$(VER).exe

CFLAGS = -Iinclude -Isrc -Wall
LDFLAGS = -Llib
LIBS = -lpdcurses -lm

default: $(TARGET)
	
obj/%.o: $(SOURCES_C)
	$(CC) -o $@ $(CFLAGS) -c $<

$(TARGET): $(OBJECTS_C)
	$(CC) -o $(TARGET) $(LDFLAGS) $(OBJECTS_C) $(LIBS)

clean:
	rm -f $(OBJECTS_C)
	rm -f $(TARGET)

rebuild:clean default

re:clean default

