CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra 
TARGET   := binary_search_sort
SRC      := binary_search_sort.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)