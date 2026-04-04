CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra 
TARGET   := circular_buffer
SRC      := circular_buffer.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)