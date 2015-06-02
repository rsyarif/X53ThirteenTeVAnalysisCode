#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include <vector>
#include <string>
#include <map>

std::map<std::string, std::map<float,float> > makeBkgSampleVector();
std::map<std::string, float> makeBkgLumiWeights(std::map<string< std::map<float,float> > bkgmap, float lumi);

void makePlots.cc(){

  //make list of backgrounds and x-sec, and number of events actually used
  std::map<std::string,std::map<float,float> > vBkgSamples = makeBkgSampleVector();
 
  //make weights based on lumi desired:
  float lumi = 5.0; //fb^-1
  std::map<std::string,float> vBkgLumiWeights = makeBkgLumiWeights(vBkgSamples,lumi);




}


std::map<std::string,std::map<float, float> > makeBkgSampleVector(){
  
  std::map<std::string, std::map<float, float> > vec;

  vec.["TTbar"][491.2]=2206600;
  vec["TTZ"][2.232]=249275;
  vec.["WZ"][1.634]=237484;
  vec.["WJets"][50100]=3828404;

  return vec;

  //number of events actually processed:
  //ttbar: 2206600
  //ttz: 249275
  //WZ: 237484
  //WJets: 3828404
  //ttW: 246521

}

std::map<std::string, float> makeBkgLumiWeights(std::map<string< std::map<float,float> > bkgmap, float lumi){
  std::map<std::string, float> map;

  for(std::map<std::string,std::map<float,float>::iterator iter=bkgmap.begin(); iter!=bkgmap.end(); iter++){
    float weight = (lumi * (iter->second)->first)/ ( (iter->second)->second);
    map.insert(std::pair<std::string,float>(iter->first,weight);
  }

}
