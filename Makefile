CXX = g++
CXXFLAGS = -std=c++14 -lstdc++
BIN = morse
SRC = $(wildcard *.cpp)
OBJS = $(SRC:%.cpp=%.o)

%.o: %.c $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(BIN) $(OBJS)
