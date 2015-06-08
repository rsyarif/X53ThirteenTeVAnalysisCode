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


std::map<std::string, std::map<float,float> > makeBkgSampleVector();
std::map<std::string, float> makeBkgLumiWeights( std::map<std::string, std::map<float,float> > vBkg, float lumi);
std::vector<Sample*> getSampleVec(std::map<std::string, float> vBkg, std::string cut);

void DrawAndSave(std::string s, std::vector<Sample*> vBkg);
TCanvas DrawCanvas(std::string variable, std::vector<Sample*> vBkg);
  
void makePlots(){
  
  //make list of backgrounds and x-sec, and number of events actually used
  std::map<std::string,std::map<float,float> > vBkgMap = makeBkgSampleVector();
 
  //make weights based on lumi desired:
  float lumi = 5.0; //fb^-1
  std::map<std::string,float> vBkgLumiWeights = makeBkgLumiWeights(vBkgMap,lumi);

  std::vector<Sample*> vBkgSamples = getSampleVec(vBkgLumiWeights, "ssdl");

  DrawAndSave("Lep1Pt",vBkgSamples);
  DrawAndSave("Lep2Pt",vBkgSamples);
  DrawAndSave("HT",vBkgSamples);


}


std::map<std::string,std::map<float, float> > makeBkgSampleVector(){
  
  std::map<std::string, std::map<float, float> > vec;

  vec["TTbar"][491.2]=2206600;
  vec["TTZ"][2.232]=249275;
  vec["WZ"][1.634]=237484;
  vec["WJets"][50100]=3828404;

  return vec;

  //number of events actually processed:
  //ttbar: 2206600
  //ttz: 249275
  //WZ: 237484
  //WJets: 3828404
  //ttW: 246521

}

std::map<std::string, float> makeBkgLumiWeights( std::map<std::string, std::map<float,float> > bkgmap, float lumi){
  std::map<std::string, float> map;

  for( std::map<std::string, std::map<float,float> >::iterator iter = bkgmap.begin(); iter!=bkgmap.end(); iter++){
    std::cout<<iter->first<<std::endl;
    //there is only ever one entry for the stored map pointed to by the string, so just get the first element of it via begin() function
    float weight = (lumi * ((iter->second).begin())->first)/ ( ((iter->second).begin())->second);
    map.insert(std::pair<std::string,float>(iter->first,weight));
  }
  return map;
}

 std::vector<Sample*> getSampleVec(std::map<std::string, float > vBkg, std::string cut){

  std::vector<Sample*> vSample;

  //int for color iteration
  int i =0;
  for(std::map<std::string,float>::iterator iter=vBkg.begin(); iter!=vBkg.end(); iter++){
    std::string filename = iter->first+".root";
    TFile* f = new TFile(filename.c_str());
    //TTree* t = (TTree*)f->Get("tEvts_ssdl");
    int color = i*4+300;
    Sample* s = new Sample(iter->first,f,iter->second,color,cut);

    vSample.push_back(s);
    i++;
  }

  return vSample;

}


void DrawAndSave(std::string variable, std::vector<Sample*> vBkg){

  TCanvas c1 = DrawCanvas(variable, vBkg);

  std::string pdfname = variable+"_"+(vBkg[0]->cutname)+".pdf";

  c1.Print(pdfname.c_str());
  

}

TCanvas DrawCanvas(std::string variable, std::vector<Sample*> vBkg){

  TCanvas c;

  THStack tStack;

  for(unsigned int ui=0; ui<vBkg.size(); ui++){
    Sample* s = vBkg.at(ui);
    TH1F* h = new TH1F("h",variable.c_str(),50,0,2000);
    TTree* t = s->tree;
    std::string drawstring = variable+">>h";
    t->Draw(drawstring.c_str());
    //scale by weight
    h->Scale(s->weight);
    h->SetFillColor(s->color);
    tStack.Add(h);
  }

  tStack.Draw();

  return c;

}
