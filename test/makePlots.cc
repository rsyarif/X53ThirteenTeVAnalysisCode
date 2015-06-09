#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include <vector>
#include <string>
#include <map>
#include "THStack.h"
#include "../plugins/Sample.cc"
#include "../plugins/SetTDRStyle.cc"
#include "../plugins/Variable.cc"
#include "TCanvas.h"
#include "TLegend.h"


std::vector<Sample*> getSampleVec(std::string cut,float lumi);
std::vector<Variable*> getVariableVec();
void DrawAndSave(Variable* Var, std::vector<Sample*> vBkg);
//TCanvas* DrawCanvas(std::string variable, std::vector<Sample*> vBkg);
  
void makePlots(){

  //set TDRStyle
  setTDRStyle();
  
 
  //desired lumi:
  float lumi = 5.0; //fb^-1


  std::vector<Sample*> vBkgSamples = getSampleVec("ssdl", lumi);
  std::vector<Variable*> vVariables = getVariableVec();

  for(unsigned int i=0; i<vVariables.size();i++){
    DrawAndSave(vVariables.at(i),vBkgSamples);
  }


}

std::vector<Sample*> getSampleVec(std::string cut, float lumi){

  

   //setup info for list of samples, xsec and events run
  std::vector<std::string> vBkgNames;
  vBkgNames.push_back("TTbar");vBkgNames.push_back("TTZ");vBkgNames.push_back("WZ");vBkgNames.push_back("WJets");
  //make vector of x-sec (in pb)
  std::vector<float> vXsec;
  vXsec.push_back(    491.2);  vXsec.push_back(  2.232); vXsec.push_back(    1.634); vXsec.push_back(   3*50100);
  //make vector of actual number of events run
  std::vector<int> vNEvts;
  vNEvts.push_back( 2206600); vNEvts.push_back(249275);  vNEvts.push_back( 237484); vNEvts.push_back(   3828404);

  //now make vector to hold weights;
  std::vector<float> vWeights;
  for(unsigned int ui=0; ui<vXsec.size(); ui++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(ui) / vNEvts.at(ui) ) ); //factor of 1000 to convert lumi to pb^-1
  }


  std::vector<Sample*> vSample;
  TFile* ttfile = new TFile("TTZ.root");
  Sample* ttSample = new Sample(vBkgNames.at(0),ttfile, vWeights.at(0),vXsec.at(0),cut,kRed+2);
  vSample.push_back(ttSample);
  TFile* ttZfile = new TFile("TTZ.root");
  Sample* ttZSample = new Sample(vBkgNames.at(1),ttZfile, vWeights.at(1),vXsec.at(1),cut,kYellow-2);
  vSample.push_back(ttZSample);
  TFile* wzfile = new TFile("WZ.root");
  Sample* wzSample = new Sample(vBkgNames.at(2),wzfile, vWeights.at(2),vXsec.at(2),cut,kBlue-3);
  vSample.push_back(wzSample);
  TFile* wjfile = new TFile("WJets.root");
  Sample* wjSample = new Sample(vBkgNames.at(3),wjfile, vWeights.at(3),vXsec.at(3),cut,kGreen+2);
  vSample.push_back(wjSample);



  return vSample;

}

std::vector<Variable*> getVariableVec(){

  std::vector<Variable*> vVar;

  Variable* lep1pt = new Variable("Lep1Pt",60,0,600);
  vVar.push_back(lep1pt);
  Variable* lep2pt = new Variable("Lep2Pt",60,0,600);
  vVar.push_back(lep2pt);
  Variable* ak4ht = new Variable("AK4HT",60,0,3000);
  vVar.push_back(ak4ht);
  Variable* nak4jets = new Variable("nAK4Jets",15,0,15);
  vVar.push_back(nak4jets);

  return vVar;

}


void DrawAndSave(Variable* var, std::vector<Sample*> vBkg){

  TCanvas* c1 = new TCanvas("c1","c1");

  c1->SetLogy();

  THStack* tStack = new THStack("tStack","");
  TLegend* leg = new TLegend(0.65,0.6,0.9,0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  for(unsigned int uk=0; uk<vBkg.size(); uk++){
    Sample* s = vBkg.at(uk);
    TH1F* h = new TH1F("h",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
    TTree* t = s->tree;
    //std::string drawstring = variable+">>h";
    //std::cout<<"drawstring is: "<<drawstring<<std::endl;
    //t->Draw(drawstring.c_str());
    t->Project("h",(var->name).c_str());
    //scale by weight
    h->Scale(s->weight);
    h->SetFillColor(s->color);
    //add to legend
    leg->AddEntry(h,(vBkg.at(uk)->name).c_str(),"f");
    assert(h);
    tStack->Add(h);

  }


  tStack->Draw("HIST");
  c1->Update();

  leg->Draw("same");

  std::string pdfname = (var->name)+"_"+(vBkg[0]->cutname)+".pdf";

  c1->Print(pdfname.c_str());
  delete c1;

}

