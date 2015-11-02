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
std::ofstream& printEvents(std::ofstream &file, CutClass* cSig, std::vector<CutClass*> vCBkg, int nmu, bool theta);
std::ofstream& printProcessIndex(std::ofstream &file, CutClass* cSig, std::vector<CutClass*> vCBkg, int nmu);

int main(int argc, char* argv[]){

  //debug, set to true by hand until sure script is working
  bool debug_ = true;

  //check ot make sure enough arguments have been passed
  if(!argc==7){
    std::cout<<"Need to supply 7 arguments: X53 Mass, Chirality, nMu, lep1 pt shift, lep2 pt shift, HT shift, nConst, and theta/higgs! Exiting....."<<std::endl;
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
  std::istringstream arg7(argv[7]);
  int nConst=0;
  if(!(arg7>>nConst)){ std::cout<<"Invalid number for Number of Constituents! "<<arg7.str()<<" Exiting..."<<std::endl; return 0;}
  else{arg7>>nConst;}

  bool theta=false; //default to making higgs cards
  std::string tool(argv[8]);
  if(tool.find("theta")!=std::string::npos) theta=true;

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
  filename<<"card_M"<<mass<<"_"<<chirality<<"_Ch_"<<channel<<"_LL"<<lep1cut<<"_SL"<<lep2cut<<"_HT"<<HTcut<<"_nConst"<<nConst;
  if(theta) filename<<"_theta.txt";
  else filename<<"_higgs.txt";
  std::string fstring = filename.str();
  std::ofstream outfile;
  outfile.open(fstring);

  //set desired lumi
  float lumi = 1.28; // fb^{-1}

  //first get our favorite vectors of samples
  std::vector<Sample*> vBkg = getBkgSampleVec("sZVeto",lumi,"MVATightRC","CBTight");
  std::vector<Sample*> vSig = getSigSampleVecForTable("sZVeto",lumi,"MVATightRC","CBTight");
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
  cutSStream<<" ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1)) && (DilepMass>20) && (nConst>="<<nConst<<" ) && (Lep1Pt >"<<lep1cut<<") && (Lep2Pt > "<<lep2cut<<") && ( cleanAK4HT > "<<HTcut<<")";
  //cutSStream<<" ( (Channel!=-0) ||(DilepMass<76.1 || DilepMass >106.1)) && (DilepMass>20)  && (Lep1Pt >"<<lep1cut<<") && (Lep2Pt > "<<lep2cut<<") && ( AK4HT > "<<HTcut<<")";
  vCutString.push_back(cutSStream.str());

  if(debug_) std::cout<<"Cutstring is: "<<cutSStream.str()<<std::endl;

  //write file header:
  if(nMu>=0)  outfile<<"imax 1\n";
  else   outfile<<"imax 3\n";
  outfile<<"jmax 7\n";
  outfile<<"kmax 7\n"; //currently have 3 systematics

  //write observed - FOW NOW DUMMY
  if(nMu>0) outfile<<"------------\n"<<"bin "<<channel<<"\n"<<"observation 0\n"<<"------------\n\n";
  else outfile<<"------------\n"<<"bin ee emu mumu\n"<<"observation 0 0 0\n"<<"------------\n\n";
  outfile<<"\n";
  //write bin labels
  outfile<<"bin \t\t";

  if(nMu>0){
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
    printEvents(outfile,cutSig,vCutBkg, nMu,theta);
  }
  else{
    for(int nmu=0; nmu<3;nmu++){
      //get cut class for signal
      CutClass* cutSig = makeCutClass(sigSample,vCutString,nmu);
      //get cut class vector for background
      std::vector<CutClass*> vCutBkg = getCutClassVector(vBkg,vCutString,nmu);
      printLabels(outfile,cutSig,vCutBkg, nmu, channel);
    }
    
    // write names
    outfile<<"\nprocess \t";
    for(int nmu=0; nmu<3;nmu++){
      //get cut class for signal
      CutClass* cutSig = makeCutClass(sigSample,vCutString,nmu);
      //get cut class vector for background
      std::vector<CutClass*> vCutBkg = getCutClassVector(vBkg,vCutString,nmu);
      printProcessNames(outfile,cutSig,vCutBkg, nmu);
    }

    //write indices
    outfile<<"\nprocess \t";
    for(int nmu=0; nmu<3;nmu++){
      //get cut class for signal
      CutClass* cutSig = makeCutClass(sigSample,vCutString,nmu);
      //get cut class vector for background
      std::vector<CutClass*> vCutBkg = getCutClassVector(vBkg,vCutString,nmu);
      printProcessIndex(outfile,cutSig,vCutBkg, nmu);
    }

    // write events
    outfile<<"\n"<<"rate \t\t";
    for(int nmu=0; nmu<3;nmu++){
      //get cut class for signal
      CutClass* cutSig = makeCutClass(sigSample,vCutString,nmu);
      //get cut class vector for background
      std::vector<CutClass*> vCutBkg = getCutClassVector(vBkg,vCutString,nmu);
      printEvents(outfile,cutSig,vCutBkg, nmu,theta);
    }

  }
  

  //write systematics
  outfile<<"\n\n"<<"------------\n";
  std::stringstream fakerate;
  fakerate<<"- - - - - - - 1.50 -";
  if(nMu>0){
    outfile<<"FakeRate lnN "<<fakerate.str()<<"\n";
  }
  else{
    outfile<<"FakeRate lnN "<<fakerate.str()<<" "<<fakerate.str()<<" "<<fakerate.str()<<"\n";
  }

  std::stringstream qcdScale;
  qcdScale<<"- 1.12 1.135 1.50 1.50 1.50 1.50 - -";
  if(nMu>0){
    outfile<<"MCNorm lnN "<<qcdScale.str()<<"\n";
  }
  else{
    outfile<<"QCDNorm lnN "<<qcdScale.str()<<" "<<qcdScale.str()<<" "<<qcdScale.str()<<"\n";
  }
  std::stringstream jes;
  jes<<"- 1.04 1.03 1.05 1.04 1.04 1.04 - -";
  if(nMu>0){
    outfile<<"JES lnN "<<jes.str()<<"\n";
  }
  else{
    outfile<<"JES lnN "<<jes.str()<<" "<<jes.str()<<" "<<jes.str()<<"\n";
  }
  std::stringstream chargemisid;
  chargemisid<<"- - - - - - - - 1.20";
  if(nMu>0){
    outfile<<"ChargeMisID lnN "<<chargemisid.str()<<"\n";
  }
  else{
    outfile<<"ChargeMisID lnN "<<chargemisid.str()<<" "<<chargemisid.str()<<" "<<chargemisid.str()<<"\n";
  }

  std::stringstream lumisys;
  lumisys<<"1.12 1.12 1.12 1.12 1.12 1.12 1.12 - -";
  if(nMu>0){
    outfile<<"LUMISYS lnN "<<lumisys.str()<<"\n";
  }
  else{
    outfile<<"LUMISYS lnN "<<lumisys.str()<<" "<<lumisys.str()<<" "<<lumisys.str()<<"\n";
  }

  std::stringstream lepID;
  if(nMu==0) lepID<<"1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";
  else if(nMu==1) lepID<<"1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";
  else if (nMu==2)lepID<<"1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";
  else lepID<<"1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -"<<" 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -"<<" 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";
  outfile<<"LepID lnN "<<lepID.str()<<"\n";
  
  std::stringstream lepISO;
  if(nMu==0) lepISO<<"1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";
  else if(nMu==1) lepISO<<"1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";
  else if (nMu==2)lepISO<<"1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";
  else lepISO<<"1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -"<<" 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -"<<" 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";

  outfile<<"LepISO lnN "<<lepISO.str()<<"\n";
  

  std::stringstream Trig;
  if(nMu==0) Trig<<"1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -";
  else if(nMu==1) Trig<<"1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -";
  else if (nMu==2)Trig<<"1.05 1.05 1.05 1.05 1.05 1.05 1.05 - -";
  else Trig<<"1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -"<<" 1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -"<<" 1.05 1.05 1.05 1.05 1.05 1.05 1.05 - -";

  outfile<<"Trig lnN "<<Trig.str()<<"\n";
  
  return 0;
}

std::ofstream& printLabels(std::ofstream &file, CutClass* cSig, std:: vector<CutClass*> vCBkg,int nmu, std::string channel){
  std::string label;
  if(nmu==-1) label = "All";
  else if(nmu==0) label = "ee";
  else if(nmu==1) label = "emu";
  else if(nmu==2) label = "mumu";
  for(std::vector<CutClass*>::size_type i =0; i<vCBkg.size()+1;i++){
    file<<label<<"\t";
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

std::ofstream& printEvents(std::ofstream &file, CutClass* cSig, std::vector<CutClass*> vCBkg, int nmu, bool theta){
  //set precision
  int old_prec = std::cout.precision();
  //now write process numbers, if using theta scale signal yield to 1pb xsec:
  if(theta) file<<std::setprecision(4)<<(1.0/cSig->xsec)*(cSig->nEvents).at(0)<<"\t";
  else file<<std::setprecision(4)<<(cSig->nEvents).at(0)<<"\t";
  for(std::vector<CutClass*>::size_type i =0; i< vCBkg.size(); i++){
    if((vCBkg.at(i)->nEvents).at(0)==0)    file<<"0.001\t";
    else file<<std::setprecision(3)<<(vCBkg.at(i)->nEvents).at(0)<<"\t";
  }
  std::cout<<std::setprecision(old_prec);
  return file;
}
