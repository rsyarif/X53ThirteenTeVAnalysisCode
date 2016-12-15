#include <stdio.h>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TLatex.h"

using namespace std;

float getPromptRate(TTree* t,float looseMiniIsoCut,float tightMiniIsoCut){
  string cutstring = Form("LepIsTight == 1 && LepMiniIso < %f",tightMiniIsoCut);
  string loosecut = Form("LepMiniIso < %f",looseMiniIsoCut);
  float nPass = t->Draw("LepPt",cutstring.c_str());
  float nTot = t->Draw("LepPt",loosecut.c_str());
  float pr;
  if(nTot==0) pr=0;
  else pr = nPass/nTot;
  return pr;
}

void pr(){

  TFile* fEle = new TFile("PromptRate_Data_Run2015D_Electrons_MVATightRC_SortByPhi.root");
  TTree* tEle = (TTree*) fEle->Get("FakeRate");
  TGraph* gEle = new TGraph(40);
  for(int i =1; i<41; i++){
    float cut = 0.01*i;
    float fakerate = getPromptRate(tEle,0.4,cut);
    gEle->SetPoint(i,cut,fakerate);
    std::cout<<"Electron Prompt Rate for miniIso cut < "<<cut<<" is: "<<fakerate<<std::endl;
  }

  gEle->SetMarkerStyle(22);
  gEle->SetMarkerColor(kBlue);
  gEle->SetTitle("Electron Prompt Rate vs MiniIsolation Requirement;I_{mini} Requirement;Prompt Rate");
  TCanvas* c = new TCanvas();
  gEle->Draw("apl");
  c->Print("ElectronPromptRate-vs-MiniIso.pdf");


  TFile* fMu = new TFile("PromptRate_Data_Run2015D_Muons_CBTightMiniIso_SortByPhi.root");
  TTree* tMu = (TTree*) fMu->Get("FakeRate");
  TGraph* gMu = new TGraph(41);
  for(int i =1; i<41; i++){
    float cut = 0.01*i;
    float promptrate = getPromptRate(tMu,0.4,cut);
    gMu->SetPoint(i,cut,promptrate);
    std::cout<<"Muon Prompt Rate for miniIso cut < "<<cut<<" is: "<<promptrate<<std::endl;
  }

  gMu->SetMarkerStyle(22);
  gMu->SetMarkerColor(kBlue);
  gMu->SetTitle("Muon Prompt Rate vs MiniIsolation Requirement;I_{mini} Requirement;Prompt Rate");
  TCanvas* c1 = new TCanvas();
  gMu->Draw("apl");
  c1->Print("MuonPromptRate-vs-MiniIso.pdf");



}
