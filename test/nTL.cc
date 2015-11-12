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

  TH1F* hnp00d = new TH1F("hnp00d","hnp00d",10,0,900000);
  TH1F* hnp01d = new TH1F("hnp01d","hnp01d",10,0,900000);
  TH1F* hnp10d = new TH1F("hnp10d","hnp10d",10,0,900000);
  TH1F* hnp11d = new TH1F("hnp11d","hnp11d",10,0,900000);


  t->Project("ht00","cleanAK4HT","( nTL==0 && Channel==0 && Lep1Pt>40 && Lep2Pt>30 && nConst >5 && ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1) ) && DilepMass>20 && cleanAK4HT>900)");
  t->Project("ht01","cleanAK4HT","( nTL==1 && Channel==0 && Lep1Pt>40 && Lep2Pt>30 && nConst >5 && ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1) ) && DilepMass>20 && cleanAK4HT>900)");
  t->Project("ht10","cleanAK4HT","( nTL==2 && Channel==0 && Lep1Pt>40 && Lep2Pt>30 && nConst >5 && ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1) ) && DilepMass>20 && cleanAK4HT>900)");
  t->Project("ht11","cleanAK4HT","( nTL==3 && Channel==0 && Lep1Pt>40 && Lep2Pt>30 && nConst >5 && ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1) ) && DilepMass>20 && cleanAK4HT>900)");
    t->Project("hnp00","cleanAK4HT","MCWeight*NPWeight*( nTL==0 && Channel==0 && Lep1Pt>40 && Lep2Pt>30 && nConst >5 && ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1) ) && DilepMass>20 && cleanAK4HT>900)");
  t->Project("hnp01","cleanAK4HT","MCWeight*NPWeight*( nTL==1 && Channel==0 && Lep1Pt>40 && Lep2Pt>30 && nConst >5 && ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1) ) && DilepMass>20 && cleanAK4HT>900)");
  t->Project("hnp10","cleanAK4HT","MCWeight*NPWeight*( nTL==2 && Channel==0 && Lep1Pt>40 && Lep2Pt>30 && nConst >5 && ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1) ) && DilepMass>20 && cleanAK4HT>900)");
  t->Project("hnp11","cleanAK4HT","MCWeight*NPWeight*( nTL==3 && Channel==0 && Lep1Pt>40 && Lep2Pt>30 && nConst >5 && ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1) ) && DilepMass>20 && cleanAK4HT>900)");

  hnp00d->AddBinContent(1,WeightOF_T00(0.7259,0.43,0.9311,0.049)*-1);
  hnp01d->AddBinContent(1,WeightOF_T01(0.7259,0.43,0.9311,0.049)*0);
  hnp10d->AddBinContent(1,WeightOF_T10(0.7259,0.43,0.9311,0.049)*0);
  hnp11d->AddBinContent(1,WeightOF_T11(0.7259,0.43,0.9311,0.049)*0);
  
  std::cout<<"N_t00: "<<ht00->Integral()<<std::endl;
  std::cout<<"N_t01: "<<ht01->Integral()<<std::endl;
  std::cout<<"N_t10: "<<ht10->Integral()<<std::endl;
  std::cout<<"N_t11: "<<ht11->Integral()<<std::endl<<std::endl;
  
  
  std::cout<<"N_np00: "<<hnp00->Integral()<<std::endl;
  std::cout<<"N_np01: "<<hnp01->Integral()<<std::endl;
  std::cout<<"N_np10: "<<hnp10->Integral()<<std::endl;
  std::cout<<"N_np11: "<<hnp11->Integral()<<std::endl;
  float sum = hnp10->Integral() + hnp00->Integral() + hnp01->Integral()+ hnp11->Integral();
  std::cout<<"sum of background contribution from tree: "<<sum<<std::endl<<std::endl;
  
  
  std::cout<<"N_np00d: "<<hnp00d->Integral()<<std::endl;
  std::cout<<"N_np01d: "<<hnp01d->Integral()<<std::endl;
  std::cout<<"N_np10d: "<<hnp10d->Integral()<<std::endl;
  std::cout<<"N_np11d: "<<hnp11d->Integral()<<std::endl;
  float sumd = hnp10d->Integral() + hnp00d->Integral() + hnp01d->Integral()+ hnp11d->Integral();
  std::cout<<"sum of background contribution from dummy: "<<sumd<<std::endl;



}
