CXX=g++

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

ROOTIL      = $(ROOTCFLAGS) $(ROOTLIBS)

LIBS        = libObjects.so

PWD         = $(shell pwd)

TOOLDIR     = $(PWD)/tools

makeLimitCards:
	$(CXX) $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o makeLimitCards.o makeLimitCards.cc

makeLimitCards_Combined:
	$(CXX) $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o makeLimitCards_Combined.o makeLimitCards_Combined.cc

makeLimitCards_MCVar:
	$(CXX) $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o makeLimitCards_MCVar.o makeLimitCards_MCVar.cc

makeLimitRootFiles:
	$(CXX) $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o makeLimitRootFiles.o makeLimitRootFiles.cc


