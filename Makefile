CXX = g++
INCLUDES = -I/usr/include -I/usr/include/glm -I./include -I./fe-headers
CXXFLAGS = $(INCLUDES) -Wall -O2
LDFLAGS = -L./lib -lglfw3 -lglm -lglad

SRCS = $(wildcard src/*.cpp src/*.c)
OBJS = $(SRCS:src/%.cpp=obj/%.o)
OBJS := $(OBJS:src/%.c=obj/%.o)

all: bin/main

bin/main: $(OBJS)
	@mkdir -p bin obj
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf bin obj
