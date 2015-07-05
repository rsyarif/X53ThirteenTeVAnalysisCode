CXX=g++

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

ROOTIL      = $(ROOTCFLAGS) $(ROOTLIBS)

LIBS        = libObjects.so

PWD         = $(shell pwd)

TOOLDIR     = $(PWD)/tools

T53Analyzer:
	$(CXX) $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o X53Analyzer.o X53Analyzer.cc


Plotter:
	$(CXX) $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o makePlots.o makePlots.cc

PromptRate:
	$(CXX) $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o PromptRate.o PromptRate.cc

