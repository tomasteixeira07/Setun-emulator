CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -MMD -MP
SANITIZERS = -fsanitize=address,undefined

TARGET = emulator
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(SANITIZERS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SANITIZERS) -c $< -o $@

-include $(OBJS:.o=.d)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) *.d

.PHONY: run clean