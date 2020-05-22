BINOUT := beepmania
LIBS := curses
GCC = g++
CFLAGS = -O2 -Wall
COMMONSRCS=$(wildcard *.cpp)
COMMONOBJS=$(patsubst %.cpp,%.o,$(COMMONSRCS))
SOURCE := $(wildcard ./*.cpp)  
OBJS := $(patsubst %.cpp,%.o,$(SOURCE))

all:$(BINOUT)

$(BINOUT): $(OBJS) $(COMMONOBJS)
	    $(GCC) $(CFLAGS) -o $@ $^ $(addprefix -l,$(LIBS)) 
%.o:%.cpp %.hpp
	    $(GCC) $(CFLAGS) -c $< -o $@
clean :  
	    rm -rf $(COMMONOBJS) $(OBJS) $(BINOUT)
