#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "../plugins/Macros.cc"
#include "TFile.h"
#include "TTree.h"

std::string tableHeader(std::vector<std::string> vC, CutClass* c);

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

  //now make a vector of cutClass for bkg
  std::vector<CutClass*> vCutBkg = getCutClassVector(vBkg,vCutString);

  //now make a vector of cutClass for sig
  std::vector<CutClass*> vCutSig = getCutClassVector(vSig,vCutString);

  //now print background table
  outfile<<tableHeader(vCutString, vCutBkg.at(0));  
  for(size_t i=0; i < vCutBkg.size(); i++){
    outfile<<vCutBkg.at(i)->samplename;
    for(size_t j =0; j < (vCutBkg.at(i)->nEvents).size(); j++){
      outfile<<" & "<<(vCutBkg.at(i)->nEvents).at(j);
    }
    outfile<<" \\\\"<<std::endl;
  }
  outfile<<"\\end{tabular} \n \\end{table}";
  outfile.close();
}

std::string tableHeader(std::vector<std::string> vC, CutClass* cC){

  std::stringstream str;

  str<<"\\begin{table}\n"<<"\\begin{tabular}|";
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
