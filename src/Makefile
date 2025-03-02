CC=g++
CFLAGS=-Wall -Wextra -std=c++17
TARGET=simple_num
SRCS = simple_num.cpp

all: $(TARGET) install clean

install: $(TARGET)
	mkdir -p ../usr/bin
	cp $(TARGET) ../usr/bin/

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) 

clean:
	rm -f $(TARGET)

check-deps:
	@which g++ > /dev/null || (echo "g++ not installed!" && exit 1)
	@which make > /dev/null || (echo "make not installed!" && exit 1)
