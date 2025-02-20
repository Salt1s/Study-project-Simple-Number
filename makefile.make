CC=g++
CFLAGS=Wall -Wextra -std=c++17
TARGET=simple_num

all: $(TARGET)

$(TARGET): simple_num.cpp
	$(CC) $(CFLAGS) -o $(TARGET) simple_num.cpp

clean:
	rm -f $(TARGET)
