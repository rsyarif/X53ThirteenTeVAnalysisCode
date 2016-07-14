#include <iostream>
#include <sstream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include <utility>

float getNEvents(TTree* t, int nMu, std::string cut, bool weight){
  
  std::stringstream channel;
  if(nMu>=0)  channel<<"&& (Channel =="<<nMu<<")";
  else  channel<<"";
  
  std::string cutstring;
  if(weight) cutstring = "NPWeight*( "+cut+channel.str()+")";
  else cutstring =  " ( "+cut+channel.str()+")";
  
  TH1F* hdummy = new TH1F("hdummy","dummy",100,0,10000);
  t->Project("hdummy","cleanAK4HT",cutstring.c_str());
  
  float nEvts = hdummy->Integral(1,hdummy->GetNbinsX()+1);
  double_t err;
  hdummy->IntegralAndError(1,hdummy->GetNbinsX()+1,err);
  
  return nEvts;
};

void np(){

  TFile* f = new TFile("NonPromptData_MuCBTightMiniIso_ElMVATightRC.root");
  TTree* t = (TTree*) f->Get("tEvts_sZVeto");
  

  std::string nt00cut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > 1100 && nTL==0)";
  std::string nt01cut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > 1100 && nTL==1)";
  std::string nt10cut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > 1100 && nTL==2)";
  std::string nt11cut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > 1100 && nTL==3)";
  std::string nbkgcut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > 1100)";
  bool noweight=false;
  bool weight=true;
  for(int i=-1; i<3;i++){
    float nt00 = getNEvents(t,i,nt00cut,noweight);
    float nt01 = getNEvents(t,i,nt01cut,noweight);
    float nt10 = getNEvents(t,i,nt10cut,noweight);
    float nt11 = getNEvents(t,i,nt11cut,noweight);
    float nbkg = getNEvents(t,i,nbkgcut,weight);
    std::cout<<"**************************"<<std::endl;
    std::cout<<"Channel: "<<i<<std::endl;
    std::cout<<"nt00: "<<nt00<<std::endl;
    std::cout<<"nt01: "<<nt01<<std::endl;
    std::cout<<"nt10: "<<nt10<<std::endl;
    //std::cout<<"nt11: "<<nt11<<std::endl; - BLINDED FOR NOW
    std::cout<<"nt11: XX"<<std::endl;
    std::cout<<"total bkg: "<<nbkg<<std::endl;
  }


}
