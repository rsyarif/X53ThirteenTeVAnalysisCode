#include <stdio>
#include <iostream>
#include <vector.h>
#include <string.h>
#include "TString.h"

float getEvents(TTree* t,TString cut){
  float nEvents = t->Draw("Lep1Pt",cut);
  return nEvents;
}


void printLine(std::string sampleName, TString filename){


  TString nomcut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200";
  TString jesUpcut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleUp > 1200";
  TString jesDowncut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleDown > 1200";
  TString jerUpcut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearUp > 1200";
  TString jerDowncut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearDown > 1200";


  TFile* f = new TFile(filename);
  TTree* t = (TTree*) f->Get("tEvts_sZVeto");
  float nom = getEvents(t,nomcut);
  float jesup = getEvents(t,jesUpcut);
  float jesupPct = 100*(jesup-nom)/nom;
  float jesdown = getEvents(t,jesDowncut);
  float jesdownPct = 100*(jesdown-nom)/nom;
  float jerup = getEvents(t,jerUpcut);
  float jerupPct = 100*(jerup-nom)/nom;
  float jerdown = getEvents(t,jerDowncut);
  float jerdownPct = 100*(jerdown-nom)/nom;

  std::cout<<sample<<" | "<<nom<<" |  "<<jesupPct<<" |  "<<jesdownPct<<" |  "<<jerupPct<<" |  "<<jerdownPct<<std::endl;

  delete t; delete f;

}


void jetEnergySys(){

  //print top line
  std::cout<<" Sample | JES Up | JES Down | JER Up | JER Down"<<std::endl;
  printLine("TTZ","../../../test/TTZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("TTW","../../../test/TTW_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("TTH","../../../test/TTH_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("TTTT","../../../test/TTTT_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("WZ","../../../test/WZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("ZZ","../../../test/ZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("W+W+","../../../test/WpWp_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("WWZ","../../../test/WWZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("WZZ","../../../test/WZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("ZZZ","../../../test/ZZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");

  std::cout<<"***********************************************"<<std::endl;
  printLine("700 LH","../../../test/X53X53m700LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("700 RH","../../../test/X53X53m700RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("800 LH","../../../test/X53X53m800LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("800 RH","../../../test/X53X53m800RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("900 LH","../../../test/X53X53m900LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  printLine("900 RH","../../../test/X53X53m000RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
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
