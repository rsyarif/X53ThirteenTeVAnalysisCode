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
#include "../plugins/Macros.cc"

/* the point of this script is to produce a card file suitable for use with higgs combine tool or theta 
   It needs to take in three arguments: leading lepton pT shift, subleading lepton pT shift, HT shift
   where the default values are 30, 30, and 900 GeV (i.e. those of 2012 analysis) */

int main(int argc, char* argv[]){

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


  return 0;
}
