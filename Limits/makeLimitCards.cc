#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include <vector>
#include "TLorentzVector.h"
#include "TChain.h"
#include "../interface/TreeReader.h"
#include <stdio.h>
#include <assert.h>
#include <map>
#include <string>
#include <sstream> 
#include <fstream>
#include "../plugins/Macros.cc"

/* the point of this script is to produce a card file suitable for use with higgs combine tool or theta 
   It needs to take in three arguments: leading lepton pT shift, subleading lepton pT shift, HT shift
   where the default values are 30, 30, and 900 GeV (i.e. those of 2012 analysis) */
std::ofstream& printProcesses(std::ofstream& outfile, std::vector<CutClass*> vCSig, std::vector<CutClass*> vCBkg, int nmu);

int main(int argc, char* argv[]){

  //debug, set to true by hand until sure script is working
  bool debug_ = true;

  //check ot make sure enough arguments have been passed
  if(!argc==4){
    std::cout<<"Need to supply 3 arguments: lep1 pt shift, lep2 pt shift, and HT shift! Exiting....."<<std::endl;
    return 0;
  }

  //get arguments
  std::istringstream arg1(argv[1]);
  float lep1shift=0;
  if(!(arg1>>lep1shift)){ std::cout<<"Invalid number for leading lepton shift! Exiting..."<<std::endl; return 0;}
  else{arg1>>lep1shift;}
  std::istringstream arg2(argv[2]);
  float lep2shift=0;
  if(!(arg2>>lep2shift)){ std::cout<<"Invalid number for subleading lepton shift! Exiting..."<<std::endl; return 0;}
  else{arg2>>lep2shift;}
  std::istringstream arg3(argv[3]);
  float HTshift=0;
  if(!(arg3>>HTshift)){ std::cout<<"Invalid number for HT shift! Exiting..."<<std::endl; return 0;}
  else{arg1>>HTshift;}

  float lep1cut = 30.0 + lep1shift;
  float lep2cut = 30.0 + lep2shift;
  float HTcut = 900.0 + HTshift;

  std::cout<<"Now running with the following cuts: Leading lepton pT > "<<lep1cut<<" GeV; subLeading lepton pT > "<<lep2cut<<" GeV; HT > "<<HTcut<<" GeV."<<std::endl;

  //output file
  std::ofstream outfile;
  outfile.open("testcard.txt");

  //set desired lumi
  float lumi = 3.0; // fb^{-1}

  //first get our favorite vectors of samples
  std::vector<Sample*> vBkg = getBkgSampleVec("ssdl",lumi);
  std::vector<Sample*> vSig = getSigSampleVecForTable("ssdl",lumi);

  //now make cut string according to cuts specified:
  std::vector<std::string> vCutString;
  std::stringstream cutSStream;
  cutSStream<<" ChargeMisIDWeight * ( (Lep1Pt >"<<lep1cut<<") && (Lep2Pt > "<<lep2cut<<") && ( AK4HT > "<<HTcut<<") )";
  vCutString.push_back(cutSStream.str());

  if(debug_) std::cout<<"Cutstring is: "<<cutSStream.str()<<std::endl;

  //need to write for every channel, -1 means all channels combined
  for(int nmu=-1; nmu<3; nmu++){
    //get cut class vector for signal
    std::vector<CutClass*> vCutSig = getCutClassVector(vSig,vCutString,nmu);
    //get cut class vector for background
    std::vector<CutClass*> vCutBkg = getCutClassVector(vBkg,vCutString,nmu);
    printProcesses(outfile,vCutSig,vCutBkg, nmu);

  }

  return 0;
}

std::ofstream& printProcesses(std::ofstream &file, std::vector<CutClass*> vCSig, std::vector<CutClass*> vCBkg, int nmu){
  //write bin labels
  file<<"bin\t";
  int bin = nmu+1;
  for(std::vector<CutClass*>::size_type i =0; i<vCBkg.size()+1;i++){
    file<<bin<<" ";
  }
  file<<"\n";
  // write names
  file<<"process \t"<<vCSig.at(0)->samplename;
  for(std::vector<CutClass*>::size_type i =0; i< vCBkg.size(); i++){
    file<<" "<<(vCBkg.at(i)->samplename);
  }
  file<<"\n";
  //now write process numbers:
  file<<"process\t"<<(vCSig.at(0)->nEvents).at(0);
  for(std::vector<CutClass*>::size_type i =0; i< vCBkg.size(); i++){
    file<<" "<<(vCBkg.at(i)->nEvents).at(0);
  }
  file<<"\n";

  return file;

}
