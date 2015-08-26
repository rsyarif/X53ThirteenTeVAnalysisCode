#include <iostream>
#include <iomanip>
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
std::ofstream& printProcessNames(std::ofstream& outfile, CutClass* cSig, std::vector<CutClass*> vCBkg, int nmu);
std::ofstream& printLabels(std::ofstream &file, CutClass* cSig, std:: vector<CutClass*> vCBkg, int nmu, std::string channel);
std::ofstream& printEvents(std::ofstream &file, CutClass* cSig, std::vector<CutClass*> vCBkg, int nmu);
std::ofstream& printProcessIndex(std::ofstream &file, CutClass* cSig, std::vector<CutClass*> vCBkg, int nmu);

int main(int argc, char* argv[]){

  //debug, set to true by hand until sure script is working
  bool debug_ = true;

  //check ot make sure enough arguments have been passed
  if(!argc==6){
    std::cout<<"Need to supply 5 arguments: X53 Mass, Chirality, nMu, lep1 pt shift, lep2 pt shift, and HT shift! Exiting....."<<std::endl;
    return 0;
  }

  //get arguments
  std::istringstream arg1(argv[1]);
  float mass=0;
  if(!(arg1>>mass)){ std::cout<<"Invalid number for X53 mass! Exiting..."<<std::endl; return 0;}
  else{arg1>>mass;}
  std::string chirality(argv[2]);
  if( chirality.find("RH")==std::string::npos && chirality.find("LH")==std::string::npos) {std::cout<<"Invalid chirality choice! Choose either \'RH\' or \'LH\'. Exiting...."<<std::endl; return 0;}
  std::istringstream arg3(argv[3]);
  int nMu=-1; //defaults to all channels
  if(!(arg3>>nMu)){ std::cout<<"Invalid number for channel! Specify number of muons (-1 means all channels) Exiting..."<<std::endl; return 0;}
  else{arg3>>nMu;}
  std::istringstream arg4(argv[4]);
  float lep1shift=0;
  if(!(arg4>>lep1shift)){ std::cout<<"Invalid number for leading lepton shift! Exiting..."<<std::endl; return 0;}
  else{arg4>>lep1shift;}
  std::istringstream arg5(argv[5]);
  float lep2shift=0;
  if(!(arg5>>lep2shift)){ std::cout<<"Invalid number for subleading lepton shift! Exiting..."<<std::endl; return 0;}
  else{arg5>>lep2shift;}
  std::istringstream arg6(argv[6]);
  float HTshift=0;
  if(!(arg6>>HTshift)){ std::cout<<"Invalid number for HT shift! Exiting..."<<std::endl; return 0;}
  else{arg6>>HTshift;}

  float lep1cut = 30.0 + lep1shift;
  float lep2cut = 30.0 + lep2shift;
  float HTcut = 900.0 + HTshift;

  std::string channel="";
  if(nMu==-1) channel = "All";
  else if(nMu==0) channel = "ee";
  else if(nMu==1) channel = "emu";
  else if(nMu==2) channel = "mumu";
  else{ std::cout<<"Picked invalid channel! Exiting..."<<std::endl; return 0;}

  std::cout<<"Now running for "<<mass<<" "<<chirality<<" X53"<<" in channel "<<channel<<" and the following cuts: Leading lepton pT > "<<lep1cut<<" GeV; subLeading lepton pT > "<<lep2cut<<" GeV; HT > "<<HTcut<<" GeV."<<std::endl;

  //output file
  std::stringstream filename;
  filename<<"card_M"<<mass<<"_"<<chirality<<"_Ch_"<<channel<<"_LL"<<lep1cut<<"_SL"<<lep2cut<<"_HT"<<HTcut<<".txt";
  std::string fstring = filename.str();
  std::ofstream outfile;
  outfile.open(fstring);

  //set desired lumi
  float lumi = 3.0; // fb^{-1}

  //first get our favorite vectors of samples
  std::vector<Sample*> vBkg = getBkgSampleVec("ssdl",lumi);
  std::vector<Sample*> vSig = getSigSampleVecForTable("ssdl",lumi);
  //now get only the signal one we care about, should be enough to ensure that both mass and chirality are present in name;
  Sample* sigSample=0;
  //convert mass to string...probably a better way exists
  std::stringstream mss; mss<<mass;
  std::string mstring = mss.str();
  for(std::vector<Sample*>::size_type i=0; i< vSig.size(); i++){
    if( vSig.at(i)->name.find(mstring)!=std::string::npos && vSig.at(i)->name.find(chirality)!=std::string::npos){
      sigSample = vSig.at(i);
      break;
    }
  }

  //make sure we got the sig sample correctly
  if(!sigSample){std::cout<<"Couldn't find the signal sample to use! Exiting....."<<std::endl; return 0;}

  //check to make sure we got the right one
  if(debug_) std::cout<<"Samples name is: "<<sigSample->name<<std::endl;

  //now make cut string according to cuts specified:
  std::vector<std::string> vCutString;
  std::stringstream cutSStream;
  cutSStream<<" ChargeMisIDWeight * ( (Lep1Pt >"<<lep1cut<<") && (Lep2Pt > "<<lep2cut<<") && ( AK4HT > "<<HTcut<<") )";
  vCutString.push_back(cutSStream.str());

  if(debug_) std::cout<<"Cutstring is: "<<cutSStream.str()<<std::endl;

  //write file header:
  outfile<<"imax 1\n";
  outfile<<"jmax 7\n";
  outfile<<"kmax 1\n"; //dummy for flat systematic on background uncertainty

  //write observed - FOW NOW DUMMY
  outfile<<"------------\n"<<"bin 1\n"<<"observation 0\n"<<"------------\n\n";
  //need to write for every channel, -1 means all channels combined
  outfile<<"\n";
  //write bin labels
  outfile<<"bin \t\t";

  //get cut class for signal
  CutClass* cutSig = makeCutClass(sigSample,vCutString,nMu);
  //get cut class vector for background
  std::vector<CutClass*> vCutBkg = getCutClassVector(vBkg,vCutString,nMu);
  printLabels(outfile,cutSig,vCutBkg, nMu, channel);
  
  // write names
  outfile<<"\nprocess \t";
  printProcessNames(outfile,cutSig,vCutBkg, nMu);
  
  //write indices
  outfile<<"\nprocess \t";
  printProcessIndex(outfile,cutSig,vCutBkg, nMu);
  
  // write events
  outfile<<"\n"<<"rate \t\t";
  printEvents(outfile,cutSig,vCutBkg, nMu);

  

  //write systematics - DUMMY
  outfile<<"\n\n"<<"------------\n"<<"dummy \t lnN \t - 1.20 1.20 1.20 1.20 1.20 1.20 1.20\n";

  return 0;
}

std::ofstream& printLabels(std::ofstream &file, CutClass* cSig, std:: vector<CutClass*> vCBkg,int nmu, std::string channel){

  for(std::vector<CutClass*>::size_type i =0; i<vCBkg.size()+1;i++){
    file<<channel<<"\t";
  }

  return file;
}

std::ofstream& printProcessNames(std::ofstream &file, CutClass* cSig, std::vector<CutClass*> vCBkg, int nmu){

  file<<"sig\t";
  for(std::vector<CutClass*>::size_type i =0; i< vCBkg.size(); i++){
    file<<(vCBkg.at(i)->samplename)<<"\t";
  }
  return file;

}

std::ofstream& printProcessIndex(std::ofstream &file, CutClass* cSig, std::vector<CutClass*> vCBkg, int nmu){

  file<<"0"<<"\t";
  for(std::vector<CutClass*>::size_type i =0; i< vCBkg.size(); i++){
    int j=i+1;
    file<<j<<"\t";
  }
  return file;

}

std::ofstream& printEvents(std::ofstream &file, CutClass* cSig, std::vector<CutClass*> vCBkg, int nmu){
  //set precision
  int old_prec = std::cout.precision();
  //now write process numbers:
  file<<std::setprecision(4)<<(cSig->nEvents).at(0)<<"\t";
  for(std::vector<CutClass*>::size_type i =0; i< vCBkg.size(); i++){
    file<<std::setprecision(3)<<(vCBkg.at(i)->nEvents).at(0)<<"\t";
  }
  std::cout<<std::setprecision(old_prec);
  return file;
}
