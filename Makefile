CC = clang
CFLAGS = -lncurses -lm -I./include/ \
		 -fsanitize=address,undefined -g -Wall -Wextra
SOURCES = ./src/*.c
TARGET = tdio

all: $(TARGET)

$(TARGET):
	$(CC) $(SOURCES) $(CFLAGS) -o $(TARGET)

debug: $(TARGET)
	mkdir -p logs
	ASAN_OPTIONS=log_path=logs/asan.log ./$(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)