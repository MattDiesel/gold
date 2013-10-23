
CC = g++
RM = rm -f

TARGET = gold
COMPILE_OPTIONS = -std=c++0x -Wall

DIRS := variant callstack util functions parser
SRCS := $(sort $(foreach d, $(DIRS), $(wildcard $(d)/*.cpp)) functions/standardfuncsmap.cpp)
OBJS = $(SRCS:.cpp=.o)

GENMAP_FILES := math

$(OBJS): %.o : %.h

test: $(OBJS)
	$(CC) $(COMPILE_OPTIONS) $(OBJS) tests/_test_functioncall.cpp -o $(TARGET)

%.o: %.cpp
	$(CC) $(COMPILE_OPTIONS) -c $<  -o $@

clean:
	$(RM) $(OBJS) ./gold functions/standardfuncsmap.cpp



functions/standardfuncsmap.o: functions/standardfuncsmap.cpp

functions/standardfuncsmap.cpp: functions/genmap
	cd functions && ./genmap $(GENMAP_FILES) > standardfuncsmap.cpp

functions/genmap: functions/symbols_genmap/genmap.cpp
	$(CC) $(COMPILE_OPTIONS) functions/symbols_genmap/genmap.cpp -o functions/genmap
