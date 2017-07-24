CXX=g++

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

ROOTIL      = $(ROOTCFLAGS) $(ROOTLIBS)

LIBS        = libObjects.so

PWD         = $(shell pwd)

TOOLDIR     = $(PWD)/../

T53Analyzer:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o X53Analyzer.o X53Analyzer.cc
HighHTCheck:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o HighHTCheck.o HighHTCheck.cc


Plotter:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o makePlots.o makePlots.cc

PromptRate:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o PromptRate.o PromptRate.cc

FakeRate:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o FakeRate.o FakeRate.cc

FakeRate_ModifiedLepPt:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o FakeRate_ModifiedLepPt.o FakeRate_ModifiedLepPt.cc

ChargeMisID:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o ChargeMisID.o ChargeMisID.cc

IsoAnalyzer:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o IsoAnalyzer.o IsoAnalyzer.cc

LeptonAnalyzer:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o LeptonAnalyzer.o LeptonAnalyzer.cc

Systematics_ChargeMisID:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o Systematics_ChargeMisID.o Systematics_ChargeMisID.cc

Systematics_TTJets_FakeRate:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o Systematics_TTJets_FakeRate.o Systematics_TTJets_FakeRate.cc

Systematics_NonPromptClosureTest:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o Systematics_NonPromptClosureTest.o Systematics_NonPromptClosureTest.cc
nPV_histmaker:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o nPV_histmaker.o nPV_histmaker.cc

CrossChecks_IPTest:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o CrossChecks_IPTest.o CrossChecks_IPTest.cc
Systematics_ClosureTestByFlavor:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o Systematics_ClosureTestByFlavor.o Systematics_ClosureTestByFlavor.cc
Sys_SignalPDF:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o Sys_SignalPDF.o Sys_SignalPDF.cc
CrossCheck_FakeRate:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o CrossCheck_FakeRate.o CrossCheck_FakeRate.cc
CrossCheck_DuplicateEvents:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o CrossCheck_DuplicateEvents.o CrossCheck_DuplicateEvents.cc
CrossCheck_ChargeMisID:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o CrossCheck_ChargeMisID.o CrossCheck_ChargeMisID.cc
CrossCheck_ChargeMisIDYields:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o CrossCheck_ChargeMisIDYields.o CrossCheck_ChargeMisIDYields.cc

MuonOverlapCheck:
	$(CXX) -g -DDEBUG $(ROOTIL) -L$(PWD)/../lib -I$(TOOLDIR) -lObjects -lz -O2 -Wall -o MuonOverlapCheck.o MuonOverlapCheck.cc