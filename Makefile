# Compiling
CC=gcc -O3
CXX=g++ -O3
INCPATH=-Iinclude -Iasctec
SRCPATH=src/
SRCPATHASCTEC=asctec/
CFLAGS=-c -Wall -ansi -std=c99 
CXXFLAGS=-Wall -std=c++11 

OBJECTC=acic.o

# Linking
LIBS=-lm -lpthread

# Source & Target
CSOURCES=$(SRCPATHASCTEC)asctecCommIntf.c 
CXXSOURCES=main.cpp $(SRCPATH)engine.cpp $(SRCPATH)bus.cpp $(SRCPATH)packet.cpp 

all: aci_engine

aci_engine: 
	$(MKDIR)
	$(CC) $(CSOURCES) $(CFLAGS) -o $(OBJECTC)
	$(CXX) $(CXXFLAGS) $(INCPATH) $(CXXSOURCES) $(OBJECTC) $(LIBS) -o aci_engine


.PHONY: clean

clean: 	
	rm *.o
	rm aci_engine
	
