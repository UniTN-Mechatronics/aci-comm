# Compiling
CC=gcc -O3
CXX=g++ -O3
INCPATH=-I/usr/include/ ../asctec
CFLAGS=-c -Wall -ansi -std=c99 
CXXFLAGS=-Wall -std=c++11 

OBJECTC=acic.o

# Linking
LIBS=-lm -lpthread

# Source & Target
CSOURCES=asctec/asctecCommIntf.c 
CXXSOURCES=main.cpp engine.cpp bus.cpp packet.cpp 

all: aci_engine

aci_engine: 
	$(MKDIR)
	$(CC) $(CSOURCES) $(CFLAGS) -o $(OBJECTC)
	$(CXX) $(CXXFLAGS) $(CXXSOURCES) $(OBJECTC) -o aci_engine


.PHONY: clean

clean: 	
	rm *.o
	rm aci_engine
	
