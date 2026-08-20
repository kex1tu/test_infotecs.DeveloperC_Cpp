.PHONY: all clean
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Wconversion -Wsign-conversion -pedantic -MMD -MP $(EXTRA_CXXFLAGS)
INCLUDES = -Isrc -I../logger/include

LDFLAGS = -L../logger -Wl,-rpath,'$$ORIGIN/../logger'
LDLIBS = -llogger -pthread

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

TARGET_APP = console_app

all: $(TARGET_APP)

$(TARGET_APP) : $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS)  -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS) $(DEPS) $(TARGET_APP)

-include $(DEPS)
