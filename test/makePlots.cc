#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "THStack.h"
//#include "../plugins/Sample.cc"
#include "../plugins/SetTDRStyle.cc"
//#include "../plugins/Variable.cc"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TROOT.h"
#include "../plugins/Macros.cc"
#include "TGraphAsymmErrors.h"


void DrawAndSave(Variable* Var, std::vector<Sample*> vBkg, std::vector<Sample*> vSig, TFile* outfile, int nMu=-1, int cutIndex=0);
void DrawTriggerEff(Sample* s, TFile* outfile);
void DrawChargeMisIDGraph(TFile* outfile);

void makePlots(){

  //make output file
  TFile* fout = new TFile("plots.root","RECREATE");

  //set TDRStyle
  setTDRStyle();
  
 
  //desired lumi:
  float lumi = 3.0; //fb^-1  
  std::vector<Variable*> vVariables = getVariableVec();

  std::vector<Sample*> vBkgSamples = getBkgSampleVec("sZVeto", lumi);
  std::vector<Sample*> vSigSamples = getSigSampleVec("sZVeto", lumi);


  for(int j=0; j <3; j++){
    for(std::vector<Variable*>::size_type i=0; i<vVariables.size();i++){
      //    std::vector<TH1F*> vBkgHist = getHistVector(v);
      DrawAndSave(vVariables.at(i),vBkgSamples,vSigSamples, fout,-1,j);
      DrawAndSave(vVariables.at(i),vBkgSamples,vSigSamples, fout,0),j;
      DrawAndSave(vVariables.at(i),vBkgSamples,vSigSamples, fout,1,j);
      DrawAndSave(vVariables.at(i),vBkgSamples,vSigSamples, fout,2,j);
      gROOT->Reset();
    }
  }
  //trigger plots - only for signal
  for(size_t i=0; i<vSigSamples.size();i++){
    DrawTriggerEff(vSigSamples.at(i),fout);
  }

  //get graph of chargemisID
  DrawChargeMisIDGraph(fout);

  fout->Close();

}



void DrawAndSave(Variable* var, std::vector<Sample*> vBkg, std::vector<Sample*> vSig, TFile* outfile, int nMu, int cutIndex){

  TCanvas* c1 = new TCanvas("c1","c1");

  c1->SetLogy();

  std::stringstream cutstring;
  if(nMu>=0){
    if(cutIndex==0){cutstring<<"(( ChargeMisIDWeight) * MCWeight * NPWeight * (Channel=="<<nMu<<") )";}
    else if(cutIndex==1){cutstring<<"(( ChargeMisIDWeight) * MCWeight * NPWeight *(Channel=="<<nMu<<" && DilepMass >20 &&  ((Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==2){cutstring<<"(( ChargeMisIDWeight) * MCWeight * NPWeight *(Channel=="<<nMu<<" && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=-) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
  }
  else {
    if(cutIndex==0){cutstring<<"(( ChargeMisIDWeight) * MCWeight * NPWeight * (Channel>=0 && ((Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ))";}
    else if(cutIndex==1){cutstring<<"(( ChargeMisIDWeight) * MCWeight * NPWeight *(Channel>=0 && DilepMass >20 && ((Channel!=-) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==2){cutstring<<"(( ChargeMisIDWeight) * MCWeight * NPWeight *(Channel>=0 && DilepMass >20 && nCleanAK4Jets > 1 && (Channel!=-) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
  }

  THStack* tStack = new THStack("tStack","");
  TLegend* leg = new TLegend(0.65,0.6,0.9,0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  for(std::vector<Sample*>::size_type uk=0; uk<vBkg.size(); uk++){

    //vBkg.at(uk)->setHist(var);
    Sample* s = vBkg.at(uk);
    TH1F* h = new TH1F("h",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
    TTree* t = s->tree;
    t->Project("h",(var->name).c_str(),(cutstring.str()).c_str());
    //scale by weight
    h->Scale(s->weight);
    //aesthetics
    h->SetFillColor(s->color);
    h->GetXaxis()->SetTitle(var->Xaxis.c_str());
    h->GetYaxis()->SetTitle(var->Yaxis.c_str());
    //add to legend
    leg->AddEntry(h,(vBkg.at(uk)->name).c_str(),"f");
    assert(h);
    tStack->Add(h);
    

  }

 

  tStack->Draw("HIST");
  tStack->GetXaxis()->SetTitle(var->Xaxis.c_str());
  tStack->GetXaxis()->CenterTitle();
  //tStack->GetXaxis()->SetTitleSize(0.015);
  tStack->GetYaxis()->SetTitle(var->Yaxis.c_str());
  tStack->GetYaxis()->CenterTitle();
  //tStack->GetYaxis()->SetRangeUser(0.008,100000);
  tStack->SetMaximum(15 * tStack->GetMaximum());
  tStack->SetMinimum(0.008);
  tStack->Draw("HIST");
  //tStack->GetYaxis()->SetTitleSize(0.015);
  c1->RedrawAxis();
  c1->Update();


  //draw signal:
  for(std::vector<Sample*>::size_type i1=0;i1<vSig.size();i1++){

    Sample* s = vSig.at(i1);
    TH1F* h = new TH1F("h",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
    TTree* t = s->tree;

    t->Project("h",(var->name).c_str(),(cutstring.str()).c_str());
    //scale by weight
    h->Scale(s->weight);
    //aesthetics
    h->SetFillStyle(0);
    h->SetLineColor(s->color);
    h->SetLineWidth(2);
    h->SetLineStyle(s->linestyle);
    h->GetXaxis()->SetTitle(var->Xaxis.c_str());
    h->GetYaxis()->SetTitle(var->Yaxis.c_str());
    //add to legend
    leg->AddEntry(h,(vSig.at(i1)->name).c_str(),"l");
    //assert(h);
    //tStack->Add(h);

    h->Draw("same");

  }

 

  TLatex* cmstex = new TLatex();
  cmstex->SetNDC();
  cmstex->SetTextSize(0.04);
  TLatex* lumitex = new TLatex();
  lumitex->SetNDC();
  lumitex->SetTextSize(0.04);

  //draw legend, cms and lumi
  leg->Draw("same");

  //draw latex
  cmstex->DrawLatex(0.15,0.96,"CMS Simulation Preliminary");
  lumitex->DrawLatex(0.65,0.96,"0.59 fb^{-1} (13 TeV)");

  //draw latex for channels
  TLatex* chantex = new TLatex();
  chantex->SetNDC();
  chantex->SetTextSize(0.04);
  if(nMu==-1) chantex->DrawLatex(0.25,0.8,"All Channels");
  if(nMu==0) chantex->DrawLatex(0.25,0.8,"#bf{ee}");
  if(nMu==1) chantex->DrawLatex(0.25,0.8,"#bf{e#mu}");
  if(nMu==2) chantex->DrawLatex(0.25,0.8,"#bf{#mu#mu}");

  //rename plots by channel
  std::string channel;
  if(nMu==-1) channel="All";
  if(nMu==0) channel="ElEl";
  if(nMu==1) channel="ElMu";
  if(nMu==2) channel="MuMu";
  std::string cutname;
  if(cutIndex==0) cutname =  "sZVeto";
  if(cutIndex==1) cutname =  "QuarkoniaVeto";
  if(cutIndex==2) cutname =  "TwoJets";
  std::string pdfname = "./plots/"+(var->name)+"_"+(vBkg[0]->cutname)+"_"+channel+"_"+cutname+".pdf";
  std::string pngname = "./plots/"+(var->name)+"_"+(vBkg[0]->cutname)+"_"+channel+"_"+cutname+".png";

  c1->Print(pdfname.c_str());
  c1->Print(pngname.c_str());
  outfile->WriteTObject(c1);
  delete c1;
  delete cmstex;
  delete lumitex;
}

void DrawTriggerEff(Sample* s, TFile* outfile){

  std::vector<std::string> vTrigNames;
  vTrigNames.push_back("DoubleEle33");
  vTrigNames.push_back("DoubleEle33_MW");
  vTrigNames.push_back("Ele27WP85");
  vTrigNames.push_back("Mu30TkMu11");
  vTrigNames.push_back("Mu40");
  vTrigNames.push_back("IsoTkMu24");
  vTrigNames.push_back("DoubleMu33NoFiltersNoVtx");
  //vTrigNames.push_back("Mu33Ele12");
  //vTrigNames.push_back("Mu8Ele23");
  //vTrigNames.push_back("PFHT900");
  //vTrigNames.push_back("AK8PFJet360TrimMass30");

  for(size_t j=0; j<vTrigNames.size();j++){    
    std::string hDenName="h_"+vTrigNames.at(j)+"Den";
    std::string hNumName="h_"+vTrigNames.at(j)+"Num";
    TH1F* hDen = (TH1F*) (s->file)->Get(hDenName.c_str());
    TH1F* hNum = (TH1F*) (s->file)->Get(hNumName.c_str());
    TGraphAsymmErrors * g = new TGraphAsymmErrors(hNum,hDen);
    TCanvas* c2 = new TCanvas();

    std::string title = "Efficiency of HLT_"+vTrigNames.at(j);
    g->SetTitle(title.c_str());
    g->GetYaxis()->SetTitle("Eff");
    g->GetXaxis()->SetTitle("p_{T} GeV");

    g->Draw("apl");

    std::string pdfname = "plots/TrigEff_"+s->name+"HLT_"+vTrigNames.at(j)+"_LooseIDLepJetCleaning.pdf";
    std::string pngname = "plots/TrigEff_"+s->name+"HLT_"+vTrigNames.at(j)+"_LooseIDLepJetCleaning.png";
    c2->Print(pdfname.c_str());
    c2->Print(pngname.c_str());

    outfile->WriteTObject(c2);
    delete c2;
    delete g;
    
  }

}


void DrawChargeMisIDGraph(TFile* outfile){
  TFile* f = new TFile("ChargeMisID_Data_Electrons.root");
  TGraphAsymmErrors* chargeMisIDGraph = (TGraphAsymmErrors*) f->Get("divide_etaNumHist_by_etaDenHist");

  chargeMisIDGraph->SetTitle("Electron Charge MisID Rate");

  chargeMisIDGraph->GetYaxis()->SetTitle("Charge MisID Rate");
  chargeMisIDGraph->GetXaxis()->SetTitle("Electron #eta");

  TCanvas c3;

  chargeMisIDGraph->Draw("apl");
  chargeMisIDGraph->GetYaxis()->SetLabelSize(0.02);
  c3.Print("plots/ElectronChargeMisID_LooseIDLepJetCleaning.pdf");
  c3.Print("plots/ElectronChargeMisID_LooseIDLepJetCleaning.png");

  outfile->Append(chargeMisIDGraph);
  outfile->Write();
}
