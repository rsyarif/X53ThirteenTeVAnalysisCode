#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <vector>
#include <string>
#include "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_3_0/src/AnalysisCode/ThirteenTeVX53/plugins/Sample.cc"

std::vector<Variable*> getVariableVec(){

  std::vector<Variable*> vVar;

  Variable* lep1pt = new Variable("Lep1Pt",60,0,600,"p_{T} (GeV)","N_{Events}");
  vVar.push_back(lep1pt);
  Variable* lep1eta = new Variable("Lep1Eta",25,-5,5,"#eta","N_{Events}");
  vVar.push_back(lep1eta);
  Variable* lep1phi = new Variable("Lep1Phi",20,-3.5,3.5,"#phi","N_{Events}");
  vVar.push_back(lep1phi);

  Variable* lep2pt = new Variable("Lep2Pt",60,0,600,"p_{T} (GeV)","N_{Events}");
  vVar.push_back(lep2pt);
  Variable* lep2eta = new Variable("Lep2Eta",25,-5,5,"#eta","N_{Events}");
  vVar.push_back(lep2eta);
  Variable* lep2phi = new Variable("Lep2Phi",20,-3.5,3.5,"#phi","N_{Events}");
  vVar.push_back(lep2phi);

  Variable* ak4jet1pt = new Variable("AK4Jet1Pt",60,0,600,"p_{T} (GeV)","N_{Events}");
  vVar.push_back(ak4jet1pt);
  Variable* ak4jet1eta = new Variable("AK4Jet1Eta",25,-5,5,"#eta","N_{Events}");
  vVar.push_back(ak4jet1eta);
  Variable* ak4jet1phi = new Variable("AK4Jet1Phi",20,-3.5,3.5,"#phi","N_{Events}");
  vVar.push_back(ak4jet1phi);

  Variable* ak4jet2pt = new Variable("AK4Jet2Pt",60,0,600,"p_{T} (GeV)","N_{Events}");
  vVar.push_back(ak4jet2pt);
  Variable* ak4jet2eta = new Variable("AK4Jet2Eta",25,-5,5,"#eta","N_{Events}");
  vVar.push_back(ak4jet2eta);
  Variable* ak4jet2phi = new Variable("AK4Jet2Phi",20,-3.5,3.5,"#phi","N_{Events}");
  vVar.push_back(ak4jet2phi);


  Variable* ak4ht = new Variable("AK4HT",60,0,3000,"H_{T} (GeV)","N_{Events}");
  vVar.push_back(ak4ht);
  Variable* nak4jets = new Variable("nAK4Jets",17,0,17,"N_{AK4 Jets}","N_{Events}");
  vVar.push_back(nak4jets);

  return vVar;

}

std::vector<Sample*> getSigSampleVec(std::string cut, float lumi){
  //make names vector
  std::vector<std::string> vSigNames;
  vSigNames.push_back("LH X53X53 M-700"); vSigNames.push_back("RH X53X53 M-700"); vSigNames.push_back("RH X53X53 M-1000"); vSigNames.push_back("LH X53X53 M-1000"); vSigNames.push_back("RH X53X53 M-1300"); vSigNames.push_back("RH X53X53 M-1300");
  //make x-sec vector - NEED TO FIX THESE VALUES************************************************
  std::vector<float> vXsec;
  //br is OR of either side decaying to ssdl. BR(ssdl) for one side = BR(W->enu) OR BR(W->munu) **2 where the square comes from AND requiring both to decay leptonically
  float BRssdl= 2*( pow((.1063 + .1071 + .1138),2));
  vXsec.push_back(0.442*BRssdl);vXsec.push_back(0.442*BRssdl);vXsec.push_back(0.0427*BRssdl);vXsec.push_back(0.0427*BRssdl);vXsec.push_back(0.00618*BRssdl);vXsec.push_back(0.00618*BRssdl);
  //make vector for number of events ran to get weight
  std::vector<int> vNEvts;
  vNEvts.push_back(19600);vNEvts.push_back(16200);vNEvts.push_back(16600);vNEvts.push_back(20000);vNEvts.push_back(18800);vNEvts.push_back(19000);
  

  //vector to hold weights
  std::vector<float> vWeights;
  for(std::vector<float>::size_type i=0; i<vXsec.size();i++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(i) / vNEvts.at(i) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  std::vector<Sample*> vSigSamples;

  TFile* x53x53700Rfile = new TFile("X53X53m700RH.root");
  Sample* x53x53m700R = new Sample(vSigNames.at(0),x53x53700Rfile,vWeights.at(0),vXsec.at(0),cut,kGreen,2);
  vSigSamples.push_back(x53x53m700R);
  TFile* x53x53700Lfile = new TFile("X53X53m700LH.root");
  Sample* x53x53m700L = new Sample(vSigNames.at(1),x53x53700Lfile,vWeights.at(1),vXsec.at(1),cut,kGreen,1);
  vSigSamples.push_back(x53x53m700L);

  TFile* x53x531000Rfile = new TFile("X53X53m1000RH.root");
  Sample* x53x53m1000R = new Sample(vSigNames.at(2),x53x531000Rfile,vWeights.at(2),vXsec.at(2),cut,kBlack,2);
  vSigSamples.push_back(x53x53m1000R);
  TFile* x53x531000Lfile = new TFile("X53X53m1000LH.root");
  Sample* x53x53m1000L = new Sample(vSigNames.at(3),x53x531000Lfile,vWeights.at(3),vXsec.at(3),cut,kBlack,1);
  vSigSamples.push_back(x53x53m1000L);

  TFile* x53x531300Rfile = new TFile("X53X53m1300RH.root");
  Sample* x53x53m1300R = new Sample(vSigNames.at(4),x53x531300Rfile,vWeights.at(4),vXsec.at(4),cut,kBlue,2);
  TFile* x53x531300Lfile = new TFile("X53X53m1300LH.root");
  Sample* x53x53m1300L = new Sample(vSigNames.at(5),x53x531300Lfile,vWeights.at(5),vXsec.at(5),cut,kBlue,1);

  return vSigSamples;

}


std::vector<Sample*> getBkgSampleVec(std::string cut, float lumi){  

   //setup info for list of samples, xsec and events run
  std::vector<std::string> vBkgNames;
  vBkgNames.push_back("TTbar");vBkgNames.push_back("TTZ");vBkgNames.push_back("WZ");vBkgNames.push_back("WJets");
  //make vector of x-sec (in pb)
  std::vector<float> vXsec;
  vXsec.push_back(    491.2);  vXsec.push_back(  2.232); vXsec.push_back(    1.634); vXsec.push_back(   3*50100);
  //make vector of actual number of events run
  std::vector<int> vNEvts;
  vNEvts.push_back( 2206600); vNEvts.push_back(249275);  vNEvts.push_back( 237484); vNEvts.push_back(   3828404);

  //now make vector to hold weights;
  std::vector<float> vWeights;
  for(std::vector<float>::size_type ui=0; ui<vXsec.size(); ui++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(ui) / vNEvts.at(ui) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  //now make samples and add to vector
  std::vector<Sample*> vSample;
  TFile* ttfile = new TFile("TTZ.root");
  Sample* ttSample = new Sample(vBkgNames.at(0),ttfile, vWeights.at(0),vXsec.at(0),cut,kRed+2);
  vSample.push_back(ttSample);
  TFile* ttZfile = new TFile("TTZ.root");
  Sample* ttZSample = new Sample(vBkgNames.at(1),ttZfile, vWeights.at(1),vXsec.at(1),cut,kYellow-2);
  vSample.push_back(ttZSample);
  TFile* wzfile = new TFile("WZ.root");
  Sample* wzSample = new Sample(vBkgNames.at(2),wzfile, vWeights.at(2),vXsec.at(2),cut,kBlue-3);
  vSample.push_back(wzSample);
  TFile* wjfile = new TFile("WJets.root");
  Sample* wjSample = new Sample(vBkgNames.at(3),wjfile, vWeights.at(3),vXsec.at(3),cut,kGreen+2);
  vSample.push_back(wjSample);

  return vSample;

}
