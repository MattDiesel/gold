
CC = g++
RM = del /Q /S

TARGET = a.exe
COMPILE_OPTIONS = -std=c++0x -Wall

DIRS := variant callstack util functions parser
SRCS := $(foreach d, $(DIRS), $(wildcard $(d)/*.cpp))
OBJS = $(SRCS:.cpp=.o)

test: $(OBJS)
	$(CC) $(COMPILE_OPTIONS) $(OBJS) tests\_test_functioncall.cpp -o $(TARGET)

%.o: %.cpp
	$(CC) $(COMPILE_OPTIONS) -c $<  -o $@

clean:
	$(RM) $(TARGET) *.o
