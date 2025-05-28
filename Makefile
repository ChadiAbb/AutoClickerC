# Variables
CC      = gcc
CFLAGS  = -Wall -Wextra -O2
TARGET  = autoclicker
SRCS    = src/main.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	del /Q $(OBJS) $(TARGET).exe