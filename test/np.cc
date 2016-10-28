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
  

  std::string nt00cut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > 900 && nTL==0)";
  std::string nt01cut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > 900 && nTL==1)";
  std::string nt10cut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > 900 && nTL==2)";
  std::string nt11cut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > 900 && nTL==3)";
  std::string nbkgcut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > 900)";

  std::string nt00noHTcut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nCleanAK4Jets > 1) && nTL==0)";
  std::string nt01noHTcut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nCleanAK4Jets > 1) && nTL==1)";
  std::string nt10noHTcut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nCleanAK4Jets > 1) && nTL==2)";
  std::string nt11noHTcut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nCleanAK4Jets > 1) && nTL==3)";
  std::string nbkgnoHTcut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nCleanAK4Jets > 1))";

  TH1F* h_nt00_ee = new TH1F("h_nt00_ee","H_{T}^{Lep} NonPrompt Check EE; H_{T}^{Lep} (GeV);Events",25,0,3000);
  TH1F* h_nt01_ee = new TH1F("h_nt01_ee","H_{T}^{Lep} NonPrompt Check EE; H_{T}^{Lep} (GeV);Events",25,0,3000);

  TH1F* hel_nt00_emu = new TH1F("hel_nt00_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (leading electron) (GeV);Events",25,0,3000);
  TH1F* hel_nt01_emu = new TH1F("hel_nt01_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (leading electron) (GeV);Events",25,0,3000);
  TH1F* hel_nt10_emu = new TH1F("hel_nt10_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (leading electron) (GeV);Events",25,0,3000);

  TH1F* h_nt00_emu = new TH1F("h_nt00_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (GeV);Events",25,0,3000);
  TH1F* h_nt01_emu = new TH1F("h_nt01_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (GeV);Events",25,0,3000);
  TH1F* h_nt10_emu = new TH1F("h_nt10_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (GeV);Events",25,0,3000);

  TH1F* hmu_nt00_emu = new TH1F("hmu_nt00_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (leading muon) (GeV);Events",25,0,3000);
  TH1F* hmu_nt01_emu = new TH1F("hmu_nt01_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (leading muon) (GeV);Events",25,0,3000);
  TH1F* hmu_nt10_emu = new TH1F("hmu_nt10_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (leading muon) (GeV);Events",25,0,3000);

  TH1F* h_nt00_mumu = new TH1F("h_nt00_mumu","H_{T}^{Lep} NonPrompt Check MuMu; H_{T}^{Lep} (GeV);Events",25,0,3000);
  TH1F* h_nt10_mumu = new TH1F("h_nt10_mumu","H_{T}^{Lep} NonPrompt Check MuMu; H_{T}^{Lep} (GeV);Events",25,0,3000);


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

    if(i==0){
      std::string chan_nt00cut = "("+nt00noHTcut+") && Channel==0";
      t->Project("h_nt00_ee","cleanAK4HT",chan_nt00cut.c_str());
      std::string chan_nt01cut = "("+nt01noHTcut+") && Channel==0";
      t->Project("h_nt01_ee","cleanAK4HT",chan_nt01cut.c_str());
    }
    else if(i==1){
      std::string chan_nt00cut = "("+nt00noHTcut+") && Channel==1";
      t->Project("h_nt00_emu","cleanAK4HT",chan_nt00cut.c_str());
      std::string chan_nt01cut = "("+nt01noHTcut+") && Channel==1";
      t->Project("h_nt01_emu","cleanAK4HT",chan_nt01cut.c_str());
      std::string chan_nt10cut = "("+nt10noHTcut+") && Channel==1";
      t->Project("h_nt10_emu","cleanAK4HT",chan_nt10cut.c_str());

      std::string chan_nt00cut_el = "("+nt00noHTcut+") && Channel==1 && Lep1Flavor==0";
      t->Project("hel_nt00_emu","cleanAK4HT",chan_nt00cut_el.c_str());
      std::string chan_nt01cut_el = "("+nt01noHTcut+") && Channel==1 && Lep1Flavor==0";
      t->Project("hel_nt01_emu","cleanAK4HT",chan_nt01cut_el.c_str());
      std::string chan_nt10cut_el = "("+nt10noHTcut+") && Channel==1 && Lep1Flavor==0";
      t->Project("hel_nt10_emu","cleanAK4HT",chan_nt10cut_el.c_str());

      std::string chan_nt00cut_mu = "("+nt00noHTcut+") && Channel==1 && Lep1Flavor==1";
      t->Project("hmu_nt00_emu","cleanAK4HT",chan_nt00cut_mu.c_str());
      std::string chan_nt01cut_mu = "("+nt01noHTcut+") && Channel==1 && Lep1Flavor==1";
      t->Project("hmu_nt01_emu","cleanAK4HT",chan_nt01cut_mu.c_str());
      std::string chan_nt10cut_mu = "("+nt10noHTcut+") && Channel==1 && Lep1Flavor==1";
      t->Project("hmu_nt10_emu","cleanAK4HT",chan_nt10cut_mu.c_str());


    }
    else if(i==2){
      std::string chan_nt00cut = "("+nt00noHTcut+") && Channel==2";
      t->Project("h_nt00_mumu","cleanAK4HT",chan_nt00cut.c_str());
      std::string chan_nt10cut = "("+nt10noHTcut+") && Channel==2";
      t->Project("h_nt10_mumu","cleanAK4HT",chan_nt10cut.c_str());
    }
  }
  gStyle->SetOptStat(kFALSE);  
  TCanvas* c = new TCanvas();
  c->SetLogy();
  TLegend* leg_ee = new TLegend(0.5,0.5,0.9,0.9);
  leg_ee->SetFillStyle(0);
  leg_ee->SetBorderSize(0);
  h_nt00_ee->SetMarkerStyle(20);
  h_nt00_ee->SetMarkerColor(kBlue);
  h_nt00_ee->SetLineColor(kBlue);
  h_nt00_ee->GetYaxis()->SetRangeUser(0.01,10100);
  h_nt00_ee->Draw("phist");
  h_nt01_ee->Draw("hist same");
  leg_ee->AddEntry("h_nt00_ee","Loose-Loose","p");
  leg_ee->AddEntry("h_nt01_ee","Tight-Loose","l");
  leg_ee->Draw("same");
  c->Print("NPBackground_ee.pdf");


  TLegend* leg_emu = new TLegend(0.5,0.5,0.9,0.9);
  leg_emu->SetFillStyle(0);
  leg_emu->SetBorderSize(0);
  h_nt00_emu->SetMarkerStyle(20);
  h_nt00_emu->SetMarkerColor(kBlue);
  h_nt00_emu->SetLineColor(kBlue);
  h_nt00_emu->GetYaxis()->SetRangeUser(0.01,10100);
  h_nt00_emu->Draw("phist");
  h_nt01_emu->Draw("hist same");
  h_nt10_emu->SetLineColor(kRed);
  h_nt10_emu->Draw("hist same");
  leg_emu->AddEntry("h_nt00_emu","Loose-Loose","p");
  leg_emu->AddEntry("h_nt01_emu","Tight El - Loose Mu","l");
  leg_emu->AddEntry("h_nt10_emu","Loose El - Tight Mu","l");
  leg_emu->Draw("same");
  c->Print("NPBackground_emu.pdf");


  TLegend* legel_emu = new TLegend(0.5,0.5,0.9,0.9);
  legel_emu->SetFillStyle(0);
  legel_emu->SetBorderSize(0);
  hel_nt00_emu->SetMarkerStyle(20);
  hel_nt00_emu->SetMarkerColor(kBlue);
  hel_nt00_emu->SetLineColor(kBlue);
  hel_nt00_emu->GetYaxis()->SetRangeUser(0.01,10100);
  hel_nt00_emu->Draw("phist");
  hel_nt01_emu->Draw("hist same");
  hel_nt10_emu->SetLineColor(kRed);
  hel_nt10_emu->Draw("hist same");
  legel_emu->AddEntry("hel_nt00_emu","Loose-Loose","p");
  legel_emu->AddEntry("hel_nt01_emu","Tight El - Loose Mu","l");
  legel_emu->AddEntry("hel_nt10_emu","Loose El - Tight Mu","l");
  legel_emu->Draw("same");
  c->Print("NPBackground_emu_LeadingElectron.pdf");


  TLegend* legmu_emu = new TLegend(0.5,0.5,0.9,0.9);
  legmu_emu->SetFillStyle(0);
  legmu_emu->SetBorderSize(0);
  hmu_nt00_emu->SetMarkerStyle(20);
  hmu_nt00_emu->SetMarkerColor(kBlue);
  hmu_nt00_emu->SetLineColor(kBlue);
  hmu_nt00_emu->GetYaxis()->SetRangeUser(0.01,10100);
  hmu_nt00_emu->Draw("phist");
  hmu_nt01_emu->Draw("hist same");
  hmu_nt10_emu->SetLineColor(kRed);
  hmu_nt10_emu->Draw("hist same");
  legmu_emu->AddEntry("hmu_nt00_emu","Loose-Loose","p");
  legmu_emu->AddEntry("hmu_nt01_emu","Tight El - Loose Mu","l");
  legmu_emu->AddEntry("hmu_nt10_emu","Loose El - Tight Mu","l");
  legmu_emu->Draw("same");
  c->Print("NPBackground_emu_LeadingMuon.pdf");

  TLegend* leg_mumu = new TLegend(0.5,0.5,0.9,0.9);
  leg_mumu->SetFillStyle(0);
  leg_mumu->SetBorderSize(0);
  h_nt00_mumu->SetMarkerStyle(20);
  h_nt00_mumu->SetMarkerColor(kBlue);
  h_nt00_mumu->SetLineColor(kBlue);
  h_nt00_mumu->GetYaxis()->SetRangeUser(0.01,10100);
  h_nt00_mumu->Draw("phist");
  h_nt10_mumu->Draw("hist same");
  leg_mumu->AddEntry("h_nt00_mumu","Loose-Loose","p");
  leg_mumu->AddEntry("h_nt10_mumu","Tight-Loose","l");
  leg_mumu->Draw("same");
  c->Print("NPBackground_mumu.pdf");

}
