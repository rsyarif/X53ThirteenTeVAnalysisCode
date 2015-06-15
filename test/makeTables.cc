#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "../plugins/Macros.cc"
#include "TFile.h"
#include "TTree.h"

std::string tableHeader(std::vector<std::string> vC, CutClass* c);
void printTable(TFile* outfile, std::vector<CutClass*> vCC, int nmu);

void makeTables(){

  //make output file
  std::ofstream outfile;
  outfile.open("table.txt");

  //set desired luminosity
  float lumi = 5.0; //fb^-1

  //get list of signal samples starting with ssdl cut
  std::vector<Sample*> vSig = getSigSampleVec("ssdl",lumi);

  //get vector of background samples
  std::vector<Sample*> vBkg = getBkgSampleVec("ssdl",lumi);

  //now get vector of cuts
  std::vector<string> vCutString = getCutString();

  for(size_t i =0; i<vCutString.size();i++){
    std::cout<<vCutString.at(i)<<std::endl;
  }

  for(int nmu=-1; nmu<3; nmu++){
    //now make a vector of cutClass for bkg
    std::vector<CutClass*> vCutBkg = getCutClassVector(vBkg,vCutString,nmu);
    //now make a vector of cutClass for sig
    std::vector<CutClass*> vCutSig = getCutClassVector(vSig,vCutString,nmu);
    //now print background table
    printTable(outfile,vCutBkg,nmu);

  }

  outfile.close();
}

std::string tableHeader(std::vector<std::string> vC, CutClass* cC){

  std::stringstream str;

  str<<"\\begin{table}\n"<<"\\centering\n"<<"\\begin{tabular}|";
  for(size_t i =0; i< (vC.size()+1); i++){
    str<<"c|";
  }
  str<<"\n";

  str<<"Sample";
  for(size_t i =0; i< (cC->cutname).size(); i++){
    str<<" & "<<(cC->cutname).at(i);
  }

  str<<"\\\\ \n";

  return str.str();
};

void printTable(TFile* outfile, std::vector<CutClass*> vCC,int nmu){

  //caption
  std::string caption;
  if(nmu==-1) caption = "Event Count for all channels combined";
  if(nmu==0) caption = "Event Count for di-electron channel";
  if(nmu==1) caption = "Event Count for electron-muon channel";
  if(nmu==2) caption = "Event Count for di-muon channel";

  outfile<<tableHeader(vCutString, vCC.at(0));  
  for(size_t i=0; i < vCC.size(); i++){
    outfile<<vCC.at(i)->samplename;
    for(size_t j =0; j < (vCC.at(i)->nEvents).size(); j++){
      outfile<<" & "<<(vCC.at(i)->nEvents).at(j);
    }
    outfile<<" \\\\"<<std::endl;
  }
  outfile<<"\\end{tabular} \n"<<"\\caption{"<<caption<<"}\n"<<" \\end{table} \n\n";

 
}
