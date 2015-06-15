#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "../plugins/Macros.cc"
#include "TFile.h"
#include "TTree.h"

std::string tableHeader(std::vector<std::string> vC, CutClass* c);
std::stringstream printTable(std::vector<CutClass*> vCC, std::vector<std::string> vCS, int nmu,bool sig);

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

  bool Bkg=false;
  bool Sig=true;

  for(int nmu=-1; nmu<3; nmu++){
    //now make a vector of cutClass for bkg
    std::vector<CutClass*> vCutBkg = getCutClassVector(vBkg,vCutString,nmu);
    //now make a vector of cutClass for sig
    std::vector<CutClass*> vCutSig = getCutClassVector(vSig,vCutString,nmu);
    //now print background table
    outfile<<(printTable(vCutBkg,vCutString,nmu,Bkg)).str();
    outfile<<(printTable(vCutSig,vCutString,nmu,Sig)).str();

  }

  outfile.close();
}

std::string tableHeader(std::vector<std::string> vC, CutClass* cC){

  std::stringstream str;

  str<<"\\begin{table}\n"<<"\\centering\n"<<"\\begin{tabular}{|";
  for(size_t i =0; i< (vC.size()+1); i++){
    str<<"c|";
  }
  str<<"}\n\\hline\\hline\n";

  str<<"Sample";
  for(size_t i =0; i< (cC->cutname).size(); i++){
    str<<" & "<<(cC->cutname).at(i);
  }

  str<<"\\\\ \n";

  return str.str();
};

std::stringstream printTable(std::vector<CutClass*> vCC, std::vector<std::string> vCS, int nmu,bool sig){

  std::stringstream tablestring;

  //caption
  std::string caption;
  if(sig){
    if(nmu==-1) caption = "Expected Number of Signal Events vs. Analysis Cut for all channels combined";
    if(nmu==0) caption = "Expected Number of Signal Events vs. Analysis Cut for di-electron channel";
    if(nmu==1) caption = "Expected Number of Signal Events vs. Analysis Cut for electron-muon channel";
    if(nmu==2) caption = "Expected Number of Signal Events vs. Analysis Cut for di-muon channel";
  }
  else{
    if(nmu==-1) caption = "Expected Number of Background Events vs. Analysis Cut for all channels combined";
    if(nmu==0) caption = "Expected Number of Background Events vs. Analysis Cut for di-electron channel";
    if(nmu==1) caption = "Expected Number of Background Events vs. Analysis Cut for electron-muon channel";
    if(nmu==2) caption = "Expected Number of Background Events vs. Analysis Cut for di-muon channel";
  }


  //label
  std::string label;
  if(sig){
    if(nmu==-1) label = "\\label{tab:ExpSigEvtsAll}";
    if(nmu==0) label = "\\label{tab:ExpSigEvtsElEl}";
    if(nmu==1) label = "\\label{tab:ExpSigEvtsElMu}";
    if(nmu==2) label = "\\label{tab:ExpSigEvtsMuMu}";
  }
  else{
    if(nmu==-1) label = "\\label{tab:ExpBkgEvtsAll}";
    if(nmu==0) label = "\\label{tab:ExpBkgEvtsElEl}";
    if(nmu==1) label = "\\label{tab:ExpBkgEvtsElMu}";
    if(nmu==2) label = "\\label{tab:ExpBkgEvtsMuMu}";
  }

  tablestring<<tableHeader(vCS, vCC.at(0)); tablestring<<"\\hline \n";
  for(size_t i=0; i < vCC.size(); i++){
    tablestring<<vCC.at(i)->samplename;
    for(size_t j =0; j < (vCC.at(i)->nEvents).size(); j++){
      tablestring<<" & "<<(vCC.at(i)->nEvents).at(j);
    }
    tablestring<<" \\\\"<<std::endl;
  }
  tablestring<<"\\hline \n\\end{tabular} \n"<<"\\caption{"<<caption<<"}\n"<<label<<'\n'<<"\\end{table} \n\n";

  return tablestring;
 
}
