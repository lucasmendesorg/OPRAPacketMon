CXX = g++
RM = rm -Rf
CXXFLAGS = -O3 -Wall -Wstrict-aliasing=0 -I. -std=c++0x
LDFLAGS = -lpthread
OBJS = main.o CPusherThread.o CProcessorThread.o
AOUT = OPRAPacketMon

all: $(OBJS)
	$(CXX) -o $(AOUT) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(AOUT)
