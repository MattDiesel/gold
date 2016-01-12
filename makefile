
CC = g++

ifdef ComSpec
	RM = del /F /Q
    SL2=\\
    CMDSEP=;
	TARGET = gold.exe
else
	RM = rm -f
    SL2=/
    CMDSEP=&
	TARGET = gold
endif
SL=$(strip $(SL2))

COMPILE_OPTIONS = -std=c++0x -Wall

FUNCSMAP = functions$(SL)standardfuncsmap.cpp
FUNCSMAP_O = $(FUNCSMAP:.cpp=.o)
GENMAP_CC = functions$(SL)symbols_genmap$(SL)genmap.cpp


GENMAP_FILES := math
DIRS := variant callstack util functions parser


SRCS_NN := $(sort $(foreach d, $(DIRS), $(wildcard $(d)/*.cpp)) $(FUNCSMAP))

ifdef ComSpec
	SRCS = $(subst /,$(SL),$(SRCS_NN))
	GENMAP = functions$(SL)genmap.exe
else
	SRCS = SRCS_NN
	GENMAP = functions$(SL)genmap
endif

OBJS = $(SRCS:.cpp=.o)



$(OBJS): %.o : %.h

test: $(OBJS)
	echo $(OBJS)
	$(CC) $(COMPILE_OPTIONS) $(OBJS) tests$(SL)_test_variant.cpp -o $(TARGET)

%.o: %.cpp
	$(CC) $(COMPILE_OPTIONS) -c $<  -o $@

clean:
	$(RM) $(OBJS) $(TARGET) $(FUNCSMAP) $(FUNCSMAP_O)



$(FUNCSMAP_O): $(FUNCSMAP)

$(FUNCSMAP): $(GENMAP)
	$(GENMAP) $(GENMAP_FILES) > $(FUNCSMAP)

$(GENMAP):
	$(CC) $(COMPILE_OPTIONS) $(GENMAP_CC) -o $(GENMAP)
