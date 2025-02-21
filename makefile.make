CC=g++
CFLAGS=Wall -Wextra -std=c++17
TARGET=simple_num

all: $(TARGET)

$(TARGET): simple_num.cpp
	$(CC) $(CFLAGS) -o $(TARGET) simple_num.cpp

clean:
	rm -f $(TARGET)
check-deps:
	@which g++ > /dev/null || (echo "g++ not installed!" && exit 1)
	@which make > /dev/null || (echo "make not installed!" && exit 1)
