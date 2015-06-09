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
#include "TCanvas.h"



std::vector<Sample*> getSampleVec(std::string cut,float lumi);

void DrawAndSave(std::string s, std::vector<Sample*> vBkg);
//TCanvas* DrawCanvas(std::string variable, std::vector<Sample*> vBkg);
  
void makePlots(){
  
 
  //desired lumi:
  float lumi = 5.0; //fb^-1


  std::vector<Sample*> vBkgSamples = getSampleVec("ssdl", lumi);

  DrawAndSave("Lep1Pt",vBkgSamples);
  DrawAndSave("Lep2Pt",vBkgSamples);
  DrawAndSave("AK4HT",vBkgSamples);


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
    vWeights.push_back( lumi * ( vXsec.at(ui) / vNEvts.at(ui) ) );
  }


  //for(unsigned int ui=0; ui<vBkgNames.size(); ui++){
  //std::cout<<"Number: "<<ui<<" Name: "<<vBkgNames.at(ui)<<" xsec: "<<vXsec.at(ui)<<" weight: "<<vWeights.at(ui)<<std::endl;
  //}

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


/*void DrawAndSave(std::string variable, std::vector<Sample*> vBkg){

  TCanvas * c1 = DrawCanvas(variable, vBkg);  

  }*/

void DrawAndSave(std::string variable, std::vector<Sample*> vBkg){

  TCanvas* c1 = new TCanvas("c1","c1");

  c1->SetLogy();

  THStack* tStack = new THStack("tStack","");

  for(unsigned int uk=0; uk<vBkg.size(); uk++){
    Sample* s = vBkg.at(uk);
    TH1F* h = new TH1F("h",variable.c_str(),50,0,2000);
    TTree* t = s->tree;
    //std::string drawstring = variable+">>h";
    //std::cout<<"drawstring is: "<<drawstring<<std::endl;
    //t->Draw(drawstring.c_str());
    t->Project("h",variable.c_str());
    //scale by weight
    h->Scale(s->weight);
    h->SetFillColor(s->color);
    std::cout<<"mean of: "<<variable<<" in sample "<<vBkg.at(uk)->name<<" is: "<<h->GetMean()<<std::endl;
    assert(h);
    tStack->Add(h);
    //delete h;
  }

  std::cout<<"about to draw tstack"<<std::endl;
  tStack->Draw("HIST");
  c1->Update();
  std::cout<<"drew tstack"<<std::endl;

  std::string pdfname = variable+"_"+(vBkg[0]->cutname)+".pdf";
  std::cout<<"pdfname: "<<pdfname<<std::endl;
  c1->Print(pdfname.c_str());
  delete c1;

}
