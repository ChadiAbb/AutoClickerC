# Variables
CC      = gcc
CFLAGS  = -Wall -Wextra -O2
TARGET  = autoclicker
SRCS    = src/main.c src/event_manager.c src/mouse_event.c
OBJDIR  = build
OBJS    = $(SRCS:src/%.c=$(OBJDIR)/%.o)

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

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

run:
	if [ ! -f $(TARGET) ]; then \
		echo "Compile not done"; \
		exit 1; \
	fi
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo Clean finished!