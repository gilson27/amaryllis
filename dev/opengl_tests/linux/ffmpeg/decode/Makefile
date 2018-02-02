FFMPEG_LIBS=    libavdevice                        \
                libavformat                        \
                libavfilter                        \
                libavcodec                         \
                libswresample                      \
                libswscale                         \
                libavutil

PKG_CFG_LIBS = ""

TARGET = install
LIBS = -lm
CC = gcc
CFLAGS += -O2 -g -O0
CFLAGS := $(shell pkg-config --cflags $(PKG_CFG_LIBS)) $(CFLAGS)
LDLIBS := $(shell pkg-config --libs $(PKG_CFG_LIBS)) $(LDLIBS)

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS) $(CC) $(CFLAGS) -c $< -o $@

install: $(CC) $(OBJECTS) $(LIBS) $(LDLIBS) -o out
.PRECIOUS: $(TARGET) $(OBJECTS)



clean: -rm -f *.o $(TARGET)

