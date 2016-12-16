# Compiling
CC=gcc -O1 -pthread
CXX=g++ -O1 -pthread
INCPATH=-Iinclude -Iasctec
SRCPATH=src/
SRCPATHASCTEC=asctec/
CFLAGS=-c -ansi -std=c99 -fPIC
CXXFLAGS=-Wall -std=c++11

# Aci C object
OBJECTC=acic.o
OBJECTCXX=

# Linking
LIBS=-lm

# Source
CSOURCES=$(SRCPATHASCTEC)asctecCommIntf.c
CXXSOURCES=$(SRCPATH)engine.cpp $(SRCPATH)bus.cpp $(SRCPATH)map_var_cmd.cpp $(SRCPATH)aci_comm_uav.cpp

all: aci_engine
shared: acic
	$(CXX) $(CXXFLAGS) $(INCPATH) $(CXXSOURCES) $(OBJECTC) $(OBJECTCXX) $(LIBS) -fPIC -shared -o lib_aci.so

.PHONY: force-all
.PHONY: force
.PHONY: bbb

bbb: bbb_aci_engine

force-all: clobber all

force: clean all

bbb: bbb_deploy_aci_engine clobber

acic:
	$(CC) $(CSOURCES) $(CFLAGS) -o $(OBJECTC)

aci_engine: acic
	$(CXX) $(CXXFLAGS) $(INCPATH) main.cpp  $(CXXSOURCES) $(OBJECTC) $(OBJECTCXX) $(LIBS) -o aci_engine

bbb_aci_engine:
	bbbxc arm-linux-gnueabihf-gcc -O1 -pthread $(CSOURCES) $(CFLAGS) -o $(OBJECTC)
	bbbxc arm-linux-gnueabihf-g++ -O1 -pthread $(CXXFLAGS) $(INCPATH) $(CXXSOURCES) $(OBJECTC) $(OBJECTCXX) $(LIBS) -o aci_engine

bbb_deploy_aci_engine: bbb_aci_engine
	scp aci_engine debian@pelican-bbb.local:/tmp/aci_engine

.PHONY: clean
.PHONY: clobber

clobber: clean-c clean

clean: clean-cxx
	rm -f aci_engine

clean-c:
	rm -f $(OBJECTC)

clean-cxx:
	rm -f $(OBJECTCC)
