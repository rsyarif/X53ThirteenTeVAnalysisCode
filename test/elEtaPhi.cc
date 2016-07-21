#include <iostream>
#include <sstream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include <utility>

namespace mymath {
  double deltaPhi(double phi1,double phi2)
  {
    double result = phi1 - phi2;
    while (result > TMath::Pi()) result -= 2*TMath::Pi();
    while (result <= -TMath::Pi()) result += 2*TMath::Pi();
    return result;
  }
  double deltaR(double eta1,double phi1,double eta2,double phi2)
  {
    double deta = eta1 - eta2;
    double dphi = deltaPhi(phi1, phi2);
    return std::sqrt(deta*deta + dphi*dphi);
  }
}

void elEtaPhi(){

  TFile* f = new TFile("DataElEl_MuCBTightMiniIso_ElMVATightRC.root");
  TTree* t = (TTree*) f->Get("tEvts_sZVeto");
  gStyle->SetOptStat(kFALSE);

  std::string cut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nCleanAK4Jets >=2)&& cleanAK4HT > 800 && Channel==0)";


  TH2F * h1 = new TH2F("h1","#eta vs #phi for leading electrons in high HT events",21,-3.5,3.5,60,-5,5);
  t->Project("h1","Lep1Eta:Lep1Phi",cut.c_str());
  
  TH2F * h2 = new TH2F("h2","#eta vs #phi for subleading electrons in high HT events",21,-3.5,3.5,60,-5,5);
  t->Project("h2","Lep2Eta:Lep2Phi",cut.c_str());

  TH2F * hj1 = new TH2F("hj1","#eta vs #phi for leading jets in high HT events",21,-3.5,3.5,60,-5,5);
  t->Project("hj1","cleanAK4Jet1Eta:cleanAK4Jet1Phi",cut.c_str());

  TH2F * hj2 = new TH2F("hj2","#eta vs #phi for subleading jets in high HT events",21,-3.5,3.5,60,-5,5);
  t->Project("hj2","cleanAK4Jet2Eta:cleanAK4Jet2Phi",cut.c_str());

  TH1F* hej11phi = new TH1F("hej11phi","#Delta_{#phi} between leading electron and leading jet",200,-3.5,3.5);
  t->Project("hej11phi","Lep1Phi-cleanAK4Jet1Phi",cut.c_str());

  TH1F* hej12phi = new TH1F("hej12phi","#Delta_{#phi} between leading electron and subleading jet",200,-3.5,3.5);
  t->Project("hej12phi","Lep1Phi-cleanAK4Jet2Phi",cut.c_str());

  TH1F* hej21phi = new TH1F("hej21phi","#Delta_{#phi} between subleading electron and leading jet",200,-3.5,3.5);
  t->Project("hej21phi","Lep2Phi-cleanAK4Jet1Phi",cut.c_str());

  TH1F* hej22phi = new TH1F("hej22phi","#Delta_{#phi} between subleading electron and subleading jet",200,-3.5,3.5);
  t->Project("hej22phi","Lep2Phi-cleanAK4Jet2Phi",cut.c_str());

  TH1F* hej11eta = new TH1F("hej11eta","#Delta_{#eta} between leading electron and leading jet",200,-3.5,3.5);
  t->Project("hej11eta","Lep1Eta-cleanAK4Jet1Eta",cut.c_str());

  TH1F* hej12eta = new TH1F("hej12eta","#Delta_{#eta} between leading electron and subleading jet",200,-3.5,3.5);
  t->Project("hej12eta","Lep1Eta-cleanAK4Jet2Eta",cut.c_str());

  TH1F* hej21eta = new TH1F("hej21eta","#Delta_{#eta} between subleading electron and leading jet",200,-3.5,3.5);
  t->Project("hej21eta","Lep2Eta-cleanAK4Jet1Eta",cut.c_str());

  TH1F* hej22eta = new TH1F("hej22eta","#Delta_{#eta} between subleading electron and subleading jet",200,-3.5,3.5);
  t->Project("hej22eta","Lep2Eta-cleanAK4Jet2Eta",cut.c_str());

  TH1F* hdrej11 = new TH1F("hdrej11","deltaR leading electron leading jet",500,0,5);
  t->Project("hdrej11","mymath::deltaR(Lep1Eta,Lep1Phi,cleanAK4Jet1Eta,cleanAK4Jet1Phi)",cut.c_str());

  TH1F* hdrej11_nocuts = new TH1F("hdrej11_nocuts","deltaR leading electron leading jet",500,0,5);
  t->Project("hdrej11_nocuts","mymath::deltaR(Lep1Eta,Lep1Phi,cleanAK4Jet1Eta,cleanAK4Jet1Phi)","Channel==0");

  TH1F* hdrmj11_nocuts = new TH1F("hdrmj11_nocuts","deltaR leading electron leading jet",500,0,5);
  t->Project("hdrmj11_nocuts","mymath::deltaR(Lep1Eta,Lep1Phi,cleanAK4Jet1Eta,cleanAK4Jet1Phi)","Channel==2");


  TH1F* he1eta = new TH1F("he1eta","",200,-2.5,2.5);
  t->Project("he1eta","Lep1Eta",cut.c_str());
  TH1F* he2eta = new TH1F("he2eta","",200,-2.5,2.5);
  t->Project("he2eta","Lep2Eta",cut.c_str());
  TH1F* hj1eta = new TH1F("hj1eta","",200,-2.5,2.5);
  t->Project("hj1eta","cleanAK4Jet1Eta",cut.c_str());
  TH1F* hj2eta = new TH1F("hj2eta","",200,-2.5,2.5);
  t->Project("hj2eta","cleanAK4Jet2Eta",cut.c_str());

  h1->GetXaxis()->SetTitle("#phi");
  h2->GetXaxis()->SetTitle("#phi");
  h1->GetYaxis()->SetTitle("#eta");
  h2->GetYaxis()->SetTitle("#eta");

  TCanvas* c = new TCanvas();

  h1->Draw("colz");
  c->Print("LeadingElectron_EtaVPhi_elel.pdf");

  h2->Draw("colz");
  c->Print("SubLeadingElectron_EtaVPhi_elel.pdf");

  h1->Add(h2);
  h1->Draw("colz");
  c->Print("AllElectrons_EtaVPhi_elel.pdf");

  hj1->Draw("colz");
  c->Print("LeadingJet_EtaVPhi_elel.pdf");

  hj2->Draw("colz");
  c->Print("SubLeadingJet_EtaVPhi_elel.pdf");

  hj1->Add(hj2);
  hj1->Draw("colz");
  c->Print("AllJets_EtaVPhi_elel.pdf");


  hej11phi->Draw();
  c->Print("DeltaPhi_Lep1Jet1_elel.pdf");

  hej12phi->Draw();
  c->Print("DeltaPhi_Lep1Jet2_elel.pdf");

  hej21phi->Draw();
  c->Print("DeltaPhi_Lep2Jet1_elel.pdf");

  hej22phi->Draw();
  c->Print("DeltaPhi_Lep2Jet2_elel.pdf");


  hej11eta->Draw();
  c->Print("DeltaEta_Lep1Jet1_elel.pdf");

  hej12eta->Draw();
  c->Print("DeltaEta_Lep1Jet2_elel.pdf");

  hej21eta->Draw();
  c->Print("DeltaEta_Lep2Jet1_elel.pdf");

  hej22eta->Draw();
  c->Print("DeltaEta_Lep2Jet2_elel.pdf");

  he1eta->SetLineColor(kBlack);
  he1eta->Draw();
  he2eta->SetLineColor(kBlue);
  //he2eta->Draw("same");
  hj1eta->SetLineColor(kRed);
  hj2eta->SetLineColor(kOrange);
  hj1eta->Draw("same");
  //hj2eta->Draw("same");
  c->Print("EtaDists_ElJet_elel.pdf");

  c->SetLogy();
  hdrej11->Draw();
  c->Print("DeltaR_LeadingElLeadingJet_elel.pdf");
  hdrej11_nocuts->Draw();
  c->Print("DeltaR_LeadingElLeadingJet_nocuts_elel.pdf");

  hdrmj11_nocuts->Draw();
  c->Print("DeltaR_LeadingMuLeadingJet_nocuts_elel.pdf");

}
