CXX=g++

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

ROOTIL      = $(ROOTCFLAGS) $(ROOTLIBS)

LIBS        = libObjects.so

PWD         = $(shell pwd)

TOOLDIR     = $(PWD)/tools

T53Analyzer:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o X53Analyzer.o X53Analyzer.cc


Plotter:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o makePlots.o makePlots.cc

PromptRate:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o PromptRate.o PromptRate.cc

FakeRate:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o FakeRate.o FakeRate.cc

ChargeMisID:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o ChargeMisID.o ChargeMisID.cc

IsoAnalyzer:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o IsoAnalyzer.o IsoAnalyzer.cc

LeptonAnalyzer:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o LeptonAnalyzer.o LeptonAnalyzer.cc

