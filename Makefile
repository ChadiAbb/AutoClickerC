# Variables
CC      = gcc
CFLAGS  = -Wall -Wextra -O2
TARGET  = autoclicker
SRCS    = src/main.c src/event_manager.c src/mouse_event.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all cleans
MAKEFLAGS += --silent

all:
	@echo "Availables Command :"
	@echo "  make build    : compile"
	@echo "  make run      : run the executable"
	@echo "  make clean    : remove .o and executable"

build: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run:
	if [ ! -f $(TARGET) ]; then \
		echo "Compile not done"; \
		exit 1; \
	fi
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	@echo Clean finished!