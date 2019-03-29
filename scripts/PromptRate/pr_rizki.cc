#include <stdio.h>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TLatex.h"
#include "TGraphAsymmErrors.h"
using namespace std;

TGraphAsymmErrors* getEtaGraph(TTree* t, float looseMiniIsoCut,float tightMiniIsoCut,bool mu){

  string cutstring = Form("LepIsTight == 1 && LepMiniIso < %f",tightMiniIsoCut);
  string loosecut = Form("LepMiniIso < %f",looseMiniIsoCut);
  float muEtabins[11]{-2.4,-2.1,-1.2,-0.9,-0.4,0.0,0.4,0.9,1.2,2.1,2.4};
  float elEtabins[11]={-2.4,-1.566,-1.4442,-0.8,-0.4,0.0,0.4,0.8,1.4442,1.566,2.4};
  TH1F* num;
  TH1F* den;
  if(mu) {num = new TH1F("num","",10,muEtabins);den = new TH1F("den","",10,muEtabins);}
  else {num = new TH1F("num","",10,elEtabins);den = new TH1F("den","",10,elEtabins);}
  t->Project("num","LepEta",cutstring.c_str());
  t->Project("den","LepEta",loosecut.c_str());

  TGraphAsymmErrors* g = new TGraphAsymmErrors(num,den);
  delete num; delete den;
  return g;
}

TGraphAsymmErrors* getPtGraph(TTree* t, float looseMiniIsoCut,float tightMiniIsoCut){

  string cutstring = Form("LepIsTight == 1 && LepMiniIso < %f",tightMiniIsoCut);
  string loosecut = Form("LepMiniIso < %f",looseMiniIsoCut);
  float ptbins[15] = {30,40,50,60,70,80,90,100,125,150,200,300,400,500,1000};
  TH1F* num = new TH1F("num","PromptRate",14,ptbins);  
  TH1F* den = new TH1F("den","den",14,ptbins);
  t->Project("num","LepPt",cutstring.c_str());
  t->Project("den","LepPt",loosecut.c_str());

  TGraphAsymmErrors* g = new TGraphAsymmErrors(num,den);
  delete num; delete den;
  return g;
}


std::pair<float,float> getPromptRate(TTree* t,float looseMiniIsoCut,float tightMiniIsoCut){
  string cutstring = Form("LepIsTight == 1 && LepMiniIso < %f",tightMiniIsoCut);
  string loosecut = Form("LepMiniIso < %f",looseMiniIsoCut);
  TH1F* num = new TH1F("num","",1,0,10000);
  TH1F* den = new TH1F("den","",1,0,10000);
  t->Project("num","LepPt",cutstring.c_str());
  t->Project("den","LepPt",loosecut.c_str());
  TGraphAsymmErrors* g = new TGraphAsymmErrors(num,den);  
  float pr = g->GetY()[0];
  float err = g->GetErrorY(0);
  std::pair<float,float> pair;
  pair.first = pr;
  pair.second = err;
  delete den; delete num;
  return pair;
}

void pr_rizki(){
  std::string elID = "MVA2017TightRC";
  std::string trig = "IsoTrigs";
//   std::string trig = "noIsoTrigs";
  
  bool doEl = true;
  bool doMu = false;
  
  std::vector<TString> eras; eras.push_back("2017B");eras.push_back("2017C");eras.push_back("2017D");eras.push_back("2017E");eras.push_back("2017F");eras.push_back("All");

  for(unsigned int i=0; i < eras.size(); i++){

    TString era = eras.at(i);
    std::cout<<"working on era: "<<era<<std::endl;

    //make output file to save graph
    TFile* fout = new TFile("PromptRate_Graph_"+era+"_"+elID+"_"+trig+".root","RECREATE");

    TFile* fEle = new TFile("../../test/PromptRate_"+trig+"/PromptRate_Data_"+era+"_Electrons_"+elID+"_SortByPhi.root");
    TTree* tEle = (TTree*) fEle->Get("FakeRate");
    TGraphErrors* gEle = new TGraphErrors(40);
    gEle->SetName("ElectronPromptRate");
    for(int i =1; i<41; i++){
      float cut = 0.01*i;
      std::pair<float,float> rateAndErr = getPromptRate(tEle,0.4,cut);
      float fakerate = rateAndErr.first;
      float err = rateAndErr.second;
      gEle->SetPoint(i,cut,fakerate);
      gEle->SetPointError(i,0.,err);
      //std::cout<<"Electron Prompt Rate for miniIso cut < "<<cut<<" is: "<<fakerate<<std::endl;
    }
    
    gEle->SetMarkerStyle(22);
    gEle->SetMarkerColor(kBlue);
    gEle->SetTitle("Electron Prompt Rate vs MiniIsolation Requirement;I_{mini} Requirement;Prompt Rate");
    TCanvas* c = new TCanvas();
    gEle->Draw("apl");
    c->Print("ElectronPromptRate-vs-MiniIso_"+era+"_"+elID+"_"+trig+".pdf");

    //getEtagraphs for 0.1 cut
    TGraphAsymmErrors* gEtaEl = getEtaGraph(tEle,0.4,0.1,false);
    //get pT graphs for 0.1 cut
    TGraphAsymmErrors* gPtEl = getPtGraph(tEle,0.4,0.1);
    
    //save graphs
    fout->WriteTObject(gEle);
    fout->WriteTObject(gEtaEl,"ElectronEtaPromptRate");
    fout->WriteTObject(gPtEl,"ElectronPtPromptRate");

    TFile* fMu = new TFile("../../test/PromptRate_"+trig+"/PromptRate_Data_"+era+"_Muons_CBTightMiniIso_SortByPhi.root");
    TTree* tMu = (TTree*) fMu->Get("FakeRate");
    TGraphErrors* gMu = new TGraphErrors(41);
    gMu->SetName("MuonPromptRate");
    for(int i =1; i<41; i++){
      float cut = 0.01*i;
      std::pair<float,float> rateAndErr = getPromptRate(tMu,0.4,cut);
      float fakerate = rateAndErr.first;
      float err = rateAndErr.second;
      gMu->SetPoint(i,cut,fakerate);
      gMu->SetPointError(i,0.,err);
      //std::cout<<"Muon Prompt Rate for miniIso cut < "<<cut<<" is: "<<promptrate<<std::endl;
    }
    
    gMu->SetMarkerStyle(22);
    gMu->SetMarkerColor(kBlue);
    gMu->SetTitle("Muon Prompt Rate vs MiniIsolation Requirement;I_{mini} Requirement;Prompt Rate");
    TCanvas* c1 = new TCanvas();
    gMu->Draw("apl");
    c1->Print("MuonPromptRate-vs-MiniIso_"+era+"_"+trig+".pdf");

    //getEtagraphs for 0.1 cut
    TGraphAsymmErrors* gEtaMu = getEtaGraph(tMu,0.4,0.1,true);
    //get pT graphs for 0.1 cut
    TGraphAsymmErrors* gPtMu = getPtGraph(tMu,0.4,0.1);

    //save graphs
    fout->WriteTObject(gMu);
    fout->WriteTObject(gEtaMu,"MuonEtaPromptRate");
    fout->WriteTObject(gPtMu,"MuonPtPromptRate");

    fout->Close();
  }

}
