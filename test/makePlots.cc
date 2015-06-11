#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include <vector>
#include <string>
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

void DrawAndSave(Variable* Var, std::vector<Sample*> vBkg, std::vector<Sample*> vSig, TFile* outfile);
  
void makePlots(){

  //make output file
  TFile* fout = new TFile("plots.root","RECREATE");

  //set TDRStyle
  setTDRStyle();
  
 
  //desired lumi:
  float lumi = 5.0; //fb^-1  
  std::vector<Variable*> vVariables = getVariableVec();

  std::vector<Sample*> vBkgSamples = getBkgSampleVec("ssdl", lumi);
  std::vector<Sample*> vSigSamples = getSigSampleVec("ssdl", lumi);


  for(std::vector<Variable*>::size_type i=0; i<vVariables.size();i++){
    //    std::vector<TH1F*> vBkgHist = getHistVector(v);
    DrawAndSave(vVariables.at(i),vBkgSamples,vSigSamples, fout);
    gROOT->Reset();
  }

  fout->Close();

}



void DrawAndSave(Variable* var, std::vector<Sample*> vBkg, std::vector<Sample*> vSig, TFile* outfile){

  TCanvas* c1 = new TCanvas("c1","c1");

  c1->SetLogy();


  THStack* tStack = new THStack("tStack","");
  TLegend* leg = new TLegend(0.65,0.6,0.9,0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  for(std::vector<Sample*>::size_type uk=0; uk<vBkg.size(); uk++){

    //vBkg.at(uk)->setHist(var);
    Sample* s = vBkg.at(uk);
    TH1F* h = new TH1F("h",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
    TTree* t = s->tree;
    //std::string drawstring = variable+">>h";
    //std::cout<<"drawstring is: "<<drawstring<<std::endl;
    //t->Draw(drawstring.c_str());
    t->Project("h",(var->name).c_str());
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
    
    //add to legend
    //leg->AddEntry(vBkg.at(uk)->hist,(vBkg.at(uk)->name).c_str(),"f");
    //assert(vBkg.at(uk)->hist);
    //tStack->Add(vBkg.at(uk)->hist);
    //std::cout<<"mean is: "<<vBkg.at(uk)->hist->GetMean()<<std::endl;
  }

  std::cout<<"********************** Finished making stack for variable "<<var->name<<" *************** "<<std::endl;

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
  //std::cout<<"updated the tcanvas "<<std::endl;

  //draw signal:
  for(std::vector<Sample*>::size_type i1=0;i1<vSig.size();i1++){

    Sample* s = vSig.at(i1);
    TH1F* h = new TH1F("h",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
    TTree* t = s->tree;
    //std::string drawstring = variable+">>h";
    //std::cout<<"drawstring is: "<<drawstring<<std::endl;
    //t->Draw(drawstring.c_str());
    t->Project("h",(var->name).c_str());
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

  std::cout<<" ********** Finished making signal hists *************"<<std::endl;

  TLatex* cmstex = new TLatex();
  cmstex->SetNDC();
  cmstex->SetTextSize(0.04);
  TLatex* lumitex = new TLatex();
  lumitex->SetNDC();
  lumitex->SetTextSize(0.04);

  //draw legend, cms and lumi
  leg->Draw("same");
  std::cout<<"drew legend"<<std::endl;
  cmstex->DrawLatex(0.15,0.96,"CMS Simulation Preliminary");
  std::cout<<"drew cms tex"<<std::endl;
  lumitex->DrawLatex(0.65,0.96,"5.0 fb^{-1} (13 TeV)");
  std::cout<<"drew lumitex"<<std::endl;
  std::string pdfname = "./plots/"+(var->name)+"_"+(vBkg[0]->cutname)+".pdf";
  std::string pngname = "./plots/"+(var->name)+"_"+(vBkg[0]->cutname)+".png";

  c1->Print(pdfname.c_str());
  c1->Print(pngname.c_str());
  outfile->WriteTObject(c1);
  delete c1;
  delete cmstex;
  delete lumitex;
}

