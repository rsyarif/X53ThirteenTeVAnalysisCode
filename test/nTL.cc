#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "../plugins/Macros.cc"

void nTL(){

  //TFile* f = new TFile("NonPromptTTJets_MuCBTight_ElMVATightRC.root");
  TFile* f = new TFile("NonPromptData_MuCBTight_ElSUSYTightRC.root");
  TTree* t = (TTree*) f->Get("tEvts_sZVeto");
  TH1F* ht00 = new TH1F("ht00","ht00",10,0,90000);
  TH1F* ht01= new TH1F("ht01","ht01",10,0,90000);
  TH1F* ht10= new TH1F("ht10","ht10",10,0,90000);
  TH1F* ht11= new TH1F("ht11","ht11",10,0,90000);

  TH1F* hnp00 = new TH1F("hnp00","hnp00",10,0,90000);
  TH1F* hnp01= new TH1F("hnp01","hnp01",10,0,90000);
  TH1F* hnp10= new TH1F("hnp10","hnp10",10,0,90000);
  TH1F* hnp11= new TH1F("hnp11","hnp11",10,0,90000);


  t->Project("ht00","cleanAK4HT","( nTL==0 && Channel==0 && Lep1Pt>40 && Lep2Pt>30 && nConst >5 && ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1) ) && DilepMass>20 && cleanAK4HT>1200)");
  t->Project("ht01","cleanAK4HT","( nTL==1 && Channel==0 && Lep1Pt>40 && Lep2Pt>30 && nConst >5 && ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1) ) && DilepMass>20 && cleanAK4HT>1200)");
  t->Project("ht10","cleanAK4HT","( nTL==2 && Channel==0 && Lep1Pt>40 && Lep2Pt>30 && nConst >5 && ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1) ) && DilepMass>20 && cleanAK4HT>1200)");
  t->Project("ht11","cleanAK4HT","( nTL==3 && Channel==0 && Lep1Pt>40 && Lep2Pt>30 && nConst >5 && ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1) ) && DilepMass>20 && cleanAK4HT>1200)");

  
  std::cout<<"N_t00: "<<ht00->Integral()<<std::endl;
  std::cout<<"N_t01: "<<ht01->Integral()<<std::endl;
  std::cout<<"N_t10: "<<ht10->Integral()<<std::endl;
  std::cout<<"N_t11: "<<ht11->Integral()<<std::endl<<std::endl;
  
  



}
