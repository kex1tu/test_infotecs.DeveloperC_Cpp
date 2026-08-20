.PHONY: all clean test
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Wconversion -Wsign-conversion -pedantic -MMD -MP $(EXTRA_CXXFLAGS)
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o) utilities.o
DEPS = $(OBJS:.o=.d)

INCLUDES = -I. -I../logger/include -I../console_app/src
LDFLAGS = -L../logger -Wl,-rpath,'$$ORIGIN/../logger'
LDLIBS = -llogger -pthread

TEST_TARGETS = test_logger test_thread_safe_queue test_utilities

all: $(TEST_TARGETS)

test_logger: test_logger.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@
	
test_thread_safe_queue: test_thread_safe_queue.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

utilities.o: ../console_app/src/utilities.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

test_utilities: test_utilities.o utilities.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@
	
clean:
	rm -rf $(OBJS) $(DEPS) $(TEST_TARGETS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

RUN_PREFIX ?=

test: all
	$(RUN_PREFIX)./test_logger
	$(RUN_PREFIX)./test_thread_safe_queue
	$(RUN_PREFIX)./test_utilities


-include $(DEPS)

