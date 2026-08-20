.PHONY: all clean
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -fPIC -MMD -MP $(EXTRA_CXXFLAGS)

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)
TARGET_LIB = liblogger.so

all: $(TARGET_LIB)

$(TARGET_LIB) : $(OBJS)
	$(CXX) $(CXXFLAGS) -shared $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(DEPS) $(TARGET_LIB)


-include $(DEPS)

