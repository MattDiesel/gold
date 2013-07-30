
CC = g++
RM = del /Q /S

TARGET = a.exe
COMPILE_OPTIONS = -std=c++0x -Wall

DIRS := variant callstack util functions parser
SRCS := $(sort $(foreach d, $(DIRS), $(wildcard $(d)/*.cpp)) functions/standardfuncsmap.cpp)
OBJS = $(SRCS:.cpp=.o)

GENMAP_FILES := math

$(OBJS): %.o : %.h

test: $(OBJS)
	$(CC) $(COMPILE_OPTIONS) $(OBJS) tests\_test_functioncall.cpp -o $(TARGET)

%.o: %.cpp
	$(CC) $(COMPILE_OPTIONS) -c $<  -o $@

clean:
	$(RM) *.o *.exe functions\standardfuncsmap.cpp



functions/standardfuncsmap.o: functions/standardfuncsmap.cpp

functions/standardfuncsmap.cpp: functions\genmap.exe $(foreach f, $(GENMAP_FILES), functions\$(f).h)
	cd functions && genmap.exe $(GENMAP_FILES) > standardfuncsmap.cpp

functions\genmap.exe: functions\symbols_genmap\genmap.cpp
	$(CC) $(COMPILE_OPTIONS) functions\symbols_genmap\genmap.cpp -o functions\genmap.exe
