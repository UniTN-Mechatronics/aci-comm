# Compiling
CC=gcc -O1 -pthread
CXX=g++ -O1 -pthread
INCPATH=-Iinclude -Iasctec
SRCPATH=src/
SRCPATHASCTEC=asctec/
CFLAGS=-c -ansi -std=c99
CXXFLAGS=-Wall -std=c++11

# Aci C object
OBJECTC=acic.o
OBJECTCXX=

# Linking
LIBS=-lm

# Source
CSOURCES=$(SRCPATHASCTEC)asctecCommIntf.c
CXXSOURCES=main.cpp $(SRCPATH)engine.cpp $(SRCPATH)bus.cpp $(SRCPATH)packet.cpp $(SRCPATH)map_var_cmd.cpp $(SRCPATH)aci_comm_uav.cpp

all: aci_engine

.PHONY: force-all
.PHONY: force

force-all: clobber all

force: clean all

aci_engine:
	$(CC) $(CSOURCES) $(CFLAGS) -o $(OBJECTC)
	$(CXX) $(CXXFLAGS) $(INCPATH) $(CXXSOURCES) $(OBJECTC) $(OBJECTCXX) $(LIBS) -o aci_engine

.PHONY: clean
.PHONY: clobber

clobber: clean-c clean

clean: clean-cxx
	rm -f aci_engine

clean-c:
	rm -f $(OBJECTC)

clean-cxx:
	rm -f $(OBJECTCC)
