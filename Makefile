CXX = g++
INCLUDES = -I/usr/include -I./include -I./fe-headers -I./usr/include/glm
CXXFLAGS = $(INCLUDES) -Wall -O2
LDFLAGS = -L./lib -lglfw3 -lglm -lglad

SRCS = $(wildcard src/*.cpp src/*.c)
OBJS = $(SRCS:src/%.cpp=obj/%.o)
OBJS := $(OBJS:src/%.c=obj/%.o)

all: bin/main

bin/main: $(OBJS)
	@mkdir -p bin
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/%.o: src/%.c
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf bin obj
