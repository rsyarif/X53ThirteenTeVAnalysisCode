#include <iostream>
#include <iomanip> 
#include <vector>
#include <string>
#include "TString.h"

float getEvents(TTree* t,TString cut){
  TH1F* h = new TH1F("h","h",1,0,1000000);
  t->Project("h","Lep1Pt",cut);  
  float nEvents = h->Integral();
  delete h;

  return nEvents;
}


void printLine(std::string sample, TString filename){


  TString nomcut =    "PUWeight * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
  TString puUpcut =   "PUWeightUp * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT> 1200)";
  TString puDowncut = "PUWeightDown * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";


  TFile* f = new TFile(filename);
  TTree* t = (TTree*) f->Get("tEvts_sZVeto");
  float nom = getEvents(t,nomcut);
  float puup = getEvents(t,puUpcut);
  float puupPct = 100*(puup-nom)/nom;
  float pudown = getEvents(t,puDowncut);
  float pudownPct = 100*(pudown-nom)/nom;
  std::cout<<setprecision(2);
  std::cout<<sample<<" |  "<<puupPct<<" |  "<<pudownPct<<std::endl;

  delete t; delete f;

}


void pileupSys(){

  //print top line
  std::cout<<" Sample | PU Up | PU Down"<<std::endl;
  printLine("TTZ ","../../../test/TTZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("TTW ","../../../test/TTW_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("TTH ","../../../test/TTH_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("TTTT","../../../test/TTTT_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("WZ  ","../../../test/WZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("ZZ  ","../../../test/ZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("W+W+","../../../test/WpWp_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("WWZ ","../../../test/WWZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("WZZ ","../../../test/WZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("ZZZ ","../../../test/ZZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");

  std::cout<<"***********************************************"<<std::endl;
  printLine("700 LH","../../../test/X53X53m700LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("700 RH","../../../test/X53X53m700RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("800 LH","../../../test/X53X53m800LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("800 RH","../../../test/X53X53m800RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("900 LH","../../../test/X53X53m900LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("900 RH","../../../test/X53X53m900RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("1000 LH","../../../test/X53X53m1000LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("1000 RH","../../../test/X53X53m1000RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("1100 LH","../../../test/X53X53m1100LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("1100 RH","../../../test/X53X53m1100RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("1200 LH","../../../test/X53X53m1200LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("1200 RH","../../../test/X53X53m1200RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("1300 LH","../../../test/X53X53m1300LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("1300 RH","../../../test/X53X53m1300RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("1400 LH","../../../test/X53X53m1400LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("1400 RH","../../../test/X53X53m1400RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("1500 LH","../../../test/X53X53m1500LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("1500 RH","../../../test/X53X53m1500RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
}
