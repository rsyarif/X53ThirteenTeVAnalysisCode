#include <stdio.h>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TLatex.h"

using namespace std;

float getFakeRate(TTree* t,float looseMiniIsoCut,float tightMiniIsoCut){
  string cutstring = Form("LepIsTight == 1 && LepMiniIso < %f",tightMiniIsoCut);
  string loosecut = Form("LepMiniIso < %f",looseMiniIsoCut);
  float nPass = t->Draw("LepPt",cutstring.c_str());
  float nTot = t->Draw("LepPt",loosecut.c_str());
  float fr;
  if(nTot==0) fr=0;
  else fr = nPass/nTot;
  return fr;
}

void fr(){

  TFile* fEle = new TFile("FakeRate_Data_Electrons_MVATightRC_modifiedLepPt.root");
  TTree* tEle = (TTree*) fEle->Get("FakeRate");
  TGraph* gEle = new TGraph(40);
  for(int i =1; i<41; i++){
    float cut = 0.01*i;
    float fakerate = getFakeRate(tEle,0.4,cut);
    gEle->SetPoint(i,cut,fakerate);
    std::cout<<"Electron Fake Rate for miniIso cut < "<<cut<<" is: "<<fakerate<<std::endl;
  }

  gEle->SetMarkerStyle(22);
  gEle->SetMarkerColor(kBlue);
  gEle->SetTitle("Electron Fake Rate vs MiniIsolation Requirement;I_{mini} Requirement;Fake Rate");
  TCanvas* c = new TCanvas();
  gEle->Draw("apl");
  c->Print("ElectronFakeRate-vs-MiniIso.pdf");


  TFile* fMu = new TFile("FakeRate_Data_Muons_CBTightMiniIso_modifiedLepPt.root");
  TTree* tMu = (TTree*) fMu->Get("FakeRate");
  TGraph* gMu = new TGraph(41);
  for(int i =1; i<41; i++){
    float cut = 0.01*i;
    float fakerate = getFakeRate(tMu,0.4,cut);
    gMu->SetPoint(i,cut,fakerate);
    std::cout<<"Muon Fake Rate for miniIso cut < "<<cut<<" is: "<<fakerate<<std::endl;
  }

  gMu->SetMarkerStyle(22);
  gMu->SetMarkerColor(kBlue);
  gMu->SetTitle("Muon Fake Rate vs MiniIsolation Requirement;I_{mini} Requirement;Fake Rate");
  TCanvas* c1 = new TCanvas();
  gMu->Draw("apl");
  c1->Print("MuonFakeRate-vs-MiniIso.pdf");



}
