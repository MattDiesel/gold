
CC = g++

ifdef ComSpec
	RM = del /F /Q
    SL2=\\
    CMDSEP=&&
	TARGET = gold.exe
else
	RM = rm -f
    SL2=/
    CMDSEP=&
	TARGET = gold
endif
SL=$(strip $(SL2))

COMPILE_OPTIONS = -std=c++0x -Wall

FUNCSMAP_F = standardfuncsmap.cpp
FUNCSMAP = functions$(SL)$(FUNCSMAP_F)
FUNCSMAP_O = $(FUNCSMAP:.cpp=.o)
GENMAP_CC = functions$(SL)symbols_genmap$(SL)genmap.cpp


GENMAP_FILES := math
DIRS := variant callstack util functions parser


SRCS_NN := $(foreach d, $(DIRS), $(wildcard $(d)/*.cpp))

ifdef ComSpec
	SRCS = $(sort $(subst /,$(SL),$(SRCS_NN)) $(FUNCSMAP))
	GENMAP_F = genmap.exe
else
	SRCS = $(sort SRCS_NN $(FUNCSMAP))
	GENMAP_F = genmap
endif

GENMAP = functions$(SL)$(GENMAP_F)
OBJS = $(SRCS:.cpp=.o)



$(OBJS): %.o : %.h

test: $(OBJS)
	$(CC) $(COMPILE_OPTIONS) $(OBJS) tests$(SL)_test_variant.cpp -o $(TARGET)

%.o: %.cpp
	$(CC) $(COMPILE_OPTIONS) -c $<  -o $@

clean:
	$(RM) $(OBJS) $(TARGET) $(FUNCSMAP) $(FUNCSMAP_O)

veryclean:
	$(RM) $(OBJS) $(TARGET) $(FUNCSMAP) $(FUNCSMAP_O) $(GENMAP)



$(FUNCSMAP_O): $(FUNCSMAP)

$(FUNCSMAP): $(GENMAP)
	cd functions $(CMDSEP) $(GENMAP_F) $(GENMAP_FILES) > $(FUNCSMAP_F)

$(GENMAP):
	$(CC) $(COMPILE_OPTIONS) $(GENMAP_CC) -o $(GENMAP)
