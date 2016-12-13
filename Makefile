# Compiling
CC=gcc -O1
CXX=g++ -O1
INCPATH=-Iinclude -Iasctec
SRCPATH=src/
SRCPATHASCTEC=asctec/
CFLAGS=-c -ansi -std=c99 
CXXFLAGS=-Wall -std=c++11 

# Aci C object
OBJECTC=acic.o

# Linking
LIBS=-lm -pthread

# Source
CSOURCES=$(SRCPATHASCTEC)asctecCommIntf.c 
CXXSOURCES=main.cpp $(SRCPATH)engine.cpp $(SRCPATH)bus.cpp $(SRCPATH)packet.cpp $(SRCPATH)map_var_cmd.cpp $(SRCPATH)aci_comm_uav.cpp 

all: aci_engine

aci_engine: 
	$(CC) $(CSOURCES) $(CFLAGS) -o $(OBJECTC)
	$(CXX) $(CXXFLAGS) $(INCPATH) $(CXXSOURCES) $(OBJECTC) $(LIBS) -o aci_engine

.PHONY: clean

clean: 	
	rm *.o
	rm aci_engine
	
