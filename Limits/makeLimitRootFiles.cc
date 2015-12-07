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
  float lumi = 2.11; // fb^{-1}

  //first get our favorite vectors of samples
  std::vector<Sample*> vBkg = getBkgSampleVec("sZVeto",lumi,"MVATightRC","CBTight");
  std::vector<Sample*> vSig = getInclusiveSigSampleVecForTable("sZVeto",lumi,"MVATightRC","CBTight");
  Sample* dataSample = getDataSample("sZVeto","MVATightRC","CBTight");
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
  cutSStream<<" ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1)) && (DilepMass>20) && (nConst>="<<nConst<<" ) && (Lep1Pt >"<<lep1cut<<") && (Lep2Pt > "<<lep2cut<<") && ( cleanAK4HT > "<<HTcut<<")";

  vCutString.push_back(cutSStream.str());

  if(debug_) std::cout<<"Cutstring is: "<<cutSStream.str()<<std::endl;

  //write file header:
  if(nMu>=0)  outfile<<"imax 1\n";
  else   outfile<<"imax 3\n";
  outfile<<"jmax 12\n";
  outfile<<"kmax 10\n"; //currently have 10 systematics

  //output root file
  std::stringstream rootfilename;
  rootfilename<<"Limits_M"<<mass<<"_"<<chirality<<"_Ch_"<<channel<<"_LL"<<lep1cut<<"_SL"<<lep2cut<<"_HT"<<HTcut<<"_nConst"<<nConst;
  if(theta) rootfilename<<"_theta.root";

  TFile* fout = new TFile((rootfilename.str()).c_str(),"RECREATE");

  //write observed
  TH1F* all_DATA = new TH1F("All_DATA","",1,0,1);
  TH1F* elel_DATA = new TH1F("elel_DATA","",1,0,1);
  TH1F* elmu_DATA = new TH1F("elmu_DATA","",1,0,1);
  TH1F* mumu_DATA = new TH1F("mumu_DATA","",1,0,1);

  CutClass* cutData = makeCutClass(dataSample,vCutString,-1);
  int nData = (cutData->nEvents).at(0);
  CutClass* cutData0 = makeCutClass(dataSample,vCutString,0);
  int nData0 = (cutData0->nEvents).at(0);
  CutClass* cutData1 = makeCutClass(dataSample,vCutString,1);
  int nData1 = (cutData1->nEvents).at(0);
  CutClass* cutData2 = makeCutClass(dataSample,vCutString,2);
  int nData2 = (cutData2->nEvents).at(0);
  
  
  for(int i=0; i<nData; i++){
    all_DATA->Fill(0.5);
  }
  for(int i=0; i<nData0; i++){
    elel_DATA->Fill(0.5);
  }
  for(int i=0; i<nData1; i++){
    mumu_DATA->Fill(0.5);
  }
  for(int i=0; i<nData2; i++){
    mumu_DATA->Fill(0.5);
  }


  fout->WriteTObject(all_DATA);
  fout->WriteTObject(elel_DATA);
  fout->WriteTObject(elmu_DATA);
  fout->WriteTObject(mumu_DATA);


  //get cut class for signal
  CutClass* cutSig_all = makeCutClass(sigSample,vCutString,-1);
  CutClass* cutSig_elel = makeCutClass(sigSample,vCutString,0);
  CutClass* cutSig_elmu = makeCutClass(sigSample,vCutString,1);
  CutClass* cutSig_mumu = makeCutClass(sigSample,vCutString,2);

  //histos for signal
  TH1F* All_sig = new TH1F("All_sig","",1,0,1);
  float all_sig = cutSig_all->nEvents.at(0) / cSig->xsec;
  float errAll_sig = cutSig_all->vErr.at(0);
  All_sig->SetBinContent(1,all_sig); All_sig->SetBinError(1,errAll_sig);

  TH1F* elel_sig = new TH1F("elel_sig","",1,0,1);
  float elel_sig = cutSig_elel->nEvents.at(0) / cSig->xsec;
  float errElel_sig = cutSig_elel->vErr.at(0);
  elel_sig->SetBinContent(1,elel_sig); elel_sig->SetBinError(1,errElel_sig);

  TH1F* elmu_sig = new TH1F("elmu_sig","",1,0,1);
  float elmu_sig = cutSig_elmu->nEvents.at(0) / cSig->xsec;
  float errElmu_sig = cutSig_elmu->vErr.at(0);
  elmu_sig->SetBinContent(1,elmu_sig); elmu_sig->SetBinError(1,errElmu_sig);

  TH1F* mumu_sig = new TH1F("mumu_sig","",1,0,1);
  float mumu_sig = cutSig_mumu->nEvents.at(0) / cSig->xsec;
  float errMumu_sig = cutSig_mumu->vErr.at(0);
  mumu_sig->SetBinContent(1,mumu_sig); mumu_sig->SetBinError(1,errMumu_sig);

  fout->WriteTObject(all_sig);
  fout->WriteTObject(elel_sig);
  fout->WriteTObject(elmu_sig);
  fout->WriteTObject(mumu_sig);


  if(theta) file<<std::setprecision(4)<<(1.0/cSig->xsec)*(cSig->nEvents).at(0)<<" ";
  else file<<std::setprecision(4)<<(cSig->nEvents).at(0)<<" ";
  for(std::vector<CutClass*>::size_type i =0; i< vCBkg.size(); i++){
    if((vCBkg.at(i)->nEvents).at(0)==0)    file<<"0.001 ";
    else file<<std::setprecision(3)<<(vCBkg.at(i)->nEvents).at(0)<<" ";
  }

  //get cut class vector for background
  std::vector<CutClass*> vCutBkg_all  = getCutClassVector(vBkg,vCutString,-1);
  std::vector<CutClass*> vCutBkg_elel = getCutClassVector(vBkg,vCutString,0);
  std::vector<CutClass*> vCutBkg_elmu = getCutClassVector(vBkg,vCutString,1);
  std::vector<CutClass*> vCutBkg_mumu = getCutClassVector(vBkg,vCutString,2);

  printEvents(outfile,cutSig,vCutBkg, nMu,theta);

  

  //write systematics - ALL BUT LEPTON ID/ISO/TRIG DONE IN THETA NOW
  outfile<<"\n\n"<<"------------\n";
  std::stringstream fakerate;
  fakerate<<"- - - - - - - - - - - 1.50 -";
  if(nMu>=0){
    outfile<<"FakeRate lnN "<<fakerate.str()<<"\n";
  }
  else{
    outfile<<"FakeRate lnN "<<fakerate.str()<<" "<<fakerate.str()<<" "<<fakerate.str()<<"\n";
  }

  std::stringstream chargemisid;
  chargemisid<<"- - - - - - - - - - - - 1.30";
  if(nMu>=0){
    outfile<<"ChargeMisID lnN "<<chargemisid.str()<<"\n";
  }
  else{
    outfile<<"ChargeMisID lnN "<<chargemisid.str()<<" "<<chargemisid.str()<<" "<<chargemisid.str()<<"\n";
  }

  std::stringstream qcdScale;
  qcdScale<<"- 1.12 1.20 1.14 1.50 1.12 1.12 1.50 1.50 1.50 1.50 - -";
  if(nMu>=0){
    outfile<<"MCNorm lnN "<<qcdScale.str()<<"\n";
  }
  else{
    outfile<<"MCNorm lnN "<<qcdScale.str()<<" "<<qcdScale.str()<<" "<<qcdScale.str()<<"\n";
  }
  std::stringstream jes;
  jes<<"1.03 1.04 1.03 1.08 1.06 1.05 1.04 1.04 1.04 1.06 1.06 - -";
  if(nMu>=0){
    outfile<<"JES lnN "<<jes.str()<<"\n";
  }
  else{
    outfile<<"JES lnN "<<jes.str()<<" "<<jes.str()<<" "<<jes.str()<<"\n";
  }

  std::stringstream jer;
  jer<<"1.01 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";
  if(nMu>=0){
    outfile<<"JER lnN "<<jer.str()<<"\n";
  }
  else{
    outfile<<"JER lnN "<<jer.str()<<" "<<jer.str()<<" "<<jer.str()<<"\n";
  }

  std::stringstream pileup;
  pileup<<"1.01 1.06 1.06 1.06 1.06 1.06 1.06 1.06 1.06 1.06 1.06 - -";
  if(nMu>=0){
    outfile<<"Pileup lnN "<<pileup.str()<<"\n";
  }
  else{
    outfile<<"Pileup lnN "<<pileup.str()<<" "<<pileup.str()<<" "<<pileup.str()<<"\n";
  }

  std::stringstream lumisys;
  lumisys<<"1.12 1.12 1.12 1.12 1.12 1.12 1.12 1.12 1.12 1.12 1.12 - -";
  if(nMu>=0){
    outfile<<"LUMISYS lnN "<<lumisys.str()<<"\n";
  }
  else{
    outfile<<"LUMISYS lnN "<<lumisys.str()<<" "<<lumisys.str()<<" "<<lumisys.str()<<"\n";
  }
  
  std::stringstream lepID_el;
  if(nMu==0) {lepID_el<<"LepIDEl lnN 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -\n"; outfile<<lepID_el.str();}
  if(nMu==1) {lepID_el<<"LepIDEl lnN 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -\n"; outfile<<lepID_el.str();}
  if(nMu==-1){lepID_el<<"LepIDEl lnN 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - - 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 - - - - - - - - - - - - - - - \n";outfile<<lepID_el.str();}

  std::stringstream lepID_mu;
  if(nMu==2) {lepID_mu<<"LepIDMu lnN 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -\n"; outfile<<lepID_mu.str();}
  if(nMu==1) {lepID_mu<<"LepIDMu lnN 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -\n"; outfile<<lepID_mu.str();}
  if(nMu==-1){lepID_mu<<"LepIDMu lnN - - - - - - - - - - - - - 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 - - 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - - \n";outfile<<lepID_mu.str();}

  std::stringstream lepISO_el;
  if(nMu==0) {lepISO_el<<"LepISOEl lnN 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -\n"; outfile<<lepISO_el.str();}
  if(nMu==1) {lepISO_el<<"LepISOEl lnN 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -\n"; outfile<<lepISO_el.str();}
  if(nMu==-1){lepISO_el<<"LepISOEl lnN 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - - 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 - - - - - - - - - - - - - - - \n";outfile<<lepISO_el.str();}

  std::stringstream lepISO_mu;
  if(nMu==2) {lepISO_mu<<"LepISOMu lnN 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -\n"; outfile<<lepISO_mu.str();}
  if(nMu==1) {lepISO_mu<<"LepISOMu lnN 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -\n"; outfile<<lepISO_mu.str();}
  if(nMu==-1){lepISO_mu<<"LepISOMu lnN - - - - - - - - - - - - - 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 - - 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - - \n";outfile<<lepISO_mu.str();}

 std::stringstream lepTrig_el;
  if(nMu==0) {lepTrig_el<<"LepTrigEl lnN 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 - -\n"; outfile<<lepTrig_el.str();}
  if(nMu==-1){lepTrig_el<<"LepTrigEl lnN 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n";outfile<<lepTrig_el.str();}

  std::stringstream lepTrig_emu;
  if(nMu==1) {lepTrig_emu<<"LepTrigEmu lnN 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 - -\n"; outfile<<lepTrig_emu.str();}
  if(nMu==-1){lepTrig_emu<<"LepTrigEmu lnN - - - - - - - - - - - - - 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 - - - - - - - - - - - - - - - \n";outfile<<lepTrig_emu.str();}

  std::stringstream lepTrig_mu;
  if(nMu==2) {lepTrig_mu<<"LepTrigMu lnN 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 - -\n"; outfile<<lepTrig_mu.str();}
  if(nMu==-1){lepTrig_mu<<"LepTrigMu lnN - - - - - - - - - - - - - 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 - - 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 1.03 - - \n";outfile<<lepTrig_mu.str();}



  // std::stringstream lepISO;
  //lepISO<< "1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";
  /*if(nMu==0) lepISO<<"1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";
  else if(nMu==1) lepISO<<"1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";
  else if (nMu==2)lepISO<<"1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";
  else lepISO<<"1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -"<<" 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -"<<" 1.02 1.02 1.02 1.02 1.02 1.02 1.02 - -";*/

  /*  if(nMu>=0) outfile<<"LepISO lnN "<<lepISO.str()<<"\n";
  else  outfile<<"LepISO lnN "<<lepISO.str()<<" "<<lepISO.str()<<" "<<lepISO.str()<<"\n";
  

  std::stringstream Trig;
  Trig<<"1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -";
 /*if(nMu==0) Trig<<"1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -";
  else if(nMu==1) Trig<<"1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -";
  else if (nMu==2)Trig<<"1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -";
  else Trig<<"1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -"<<" 1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -"<<" 1.01 1.01 1.01 1.01 1.01 1.01 1.01 - -";

  if(nMu>=0) outfile<<"Trig lnN "<<Trig.str()<<"\n";
  else  outfile<<"Trig lnN "<<Trig.str()<<" "<<Trig.str()<<" "<<Trig.str()<<"\n";*/
  return 0;
}

std::ofstream& printLabels(std::ofstream &file, CutClass* cSig, std:: vector<CutClass*> vCBkg,int nmu, std::string channel){
  std::string label;
  if(nmu==-1) label = "All";
  else if(nmu==0) label = "ee";
  else if(nmu==1) label = "emu";
  else if(nmu==2) label = "mumu";
  for(std::vector<CutClass*>::size_type i =0; i<vCBkg.size()+1;i++){
    file<<label<<" ";
  }

  return file;
}

std::ofstream& printProcessNames(std::ofstream &file, CutClass* cSig, std::vector<CutClass*> vCBkg, int nmu){

  file<<"sig ";
  for(std::vector<CutClass*>::size_type i =0; i< vCBkg.size(); i++){
    if (vCBkg.at(i)->samplename=="WW-mpi") file<<"WWmpi ";
    else file<<(vCBkg.at(i)->samplename)<<" ";
  }
  return file;

}

std::ofstream& printProcessIndex(std::ofstream &file, CutClass* cSig, std::vector<CutClass*> vCBkg, int nmu){

  file<<"0"<<" ";
  for(std::vector<CutClass*>::size_type i =0; i< vCBkg.size(); i++){
    int j=i+1;
    file<<j<<" ";
  }
  return file;

}

std::ofstream& printEvents(std::ofstream &file, CutClass* cSig, std::vector<CutClass*> vCBkg, int nmu, bool theta){
  //set precision
  int old_prec = std::cout.precision();
  //now write process numbers, if using theta scale signal yield to 1pb xsec:
  //std::cout<<"sample: "<<cSig->samplename<<" and events: "<<cSig->nEvents.at(0)<<" and xsec: "<<cSig->xsec<<std::endl;
  if(theta) file<<std::setprecision(4)<<(1.0/cSig->xsec)*(cSig->nEvents).at(0)<<" ";
  else file<<std::setprecision(4)<<(cSig->nEvents).at(0)<<" ";
  for(std::vector<CutClass*>::size_type i =0; i< vCBkg.size(); i++){
    if((vCBkg.at(i)->nEvents).at(0)==0)    file<<"0.001 ";
    else file<<std::setprecision(3)<<(vCBkg.at(i)->nEvents).at(0)<<" ";
  }
  std::cout<<std::setprecision(old_prec);
  return file;
}
