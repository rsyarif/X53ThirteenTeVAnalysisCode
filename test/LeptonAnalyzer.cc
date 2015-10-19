#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include <vector>
#include "TLorentzVector.h"
#include "TChain.h"
#include "TDirectory.h"
#include "../interface/TreeReader.h"
#include <stdio.h>
#include <assert.h>
#include <map>
#include <string>
#include "TString.h"

const double M_EL = 0.000510998928; //Mass of electron in GeV
const double M_MU = 0.1056583715;   //Mass of muon in GeV
const double M_Z  = 91.1876;        //Mass of Z boson
const double dM   = 15;             //Size of window around Z

bool matchToGenLep(TMuon* mu, std::vector<TGenParticle*> genParticles);
bool matchToGenLep(TElectron* el, std::vector<TGenParticle*> genParticles);
void doMuCutFlow(TH1F*& h, TMuon* mu);
void doElCutFlow_Barrel(TH1F*& h, TElectron* el);
void doElCutFlow_Endcap(TH1F*& h, TElectron* el);
TGenParticle* getMatchedGenParticle(TElectron* el, std::vector<TGenParticle*> genParticles);

int main(int argc, char* argv[]){

  //read in arguments
  std::string argv1(argv[1]);
  bool data;
  if(argv1.find("Data")!=std::string::npos) data=true;
  else data=false;

  std::string chirality(argv[2]);
  std::string mass(argv[3]);


  TString filename;

  std::string filename;
  if(data) filename = "/eos/uscms/store/user/lpctlbsm/clint/Run2015D/Oct15v2/ljmet_trees/ljmet_Data_All.root";
  else filename = "/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/Oct15v2/ljmet_trees/ljmet_X53X53m"+mass+chirality+".root";

  //load in tree reader
  TreeReader* tr = new TreeReader(filename.c_str(),!data);

  TTree* t = tr->tree;

  int nEntries = t->GetEntries();

  //counter for number of loose muons
  float nLooseMuons=0;

  //outfile
  std::string outname;
  if(data)outname="LeptonEfficiency_Signal_Data_Run2015D.root"; 
  else outname="LeptonEfficiency_Signal_MC_"+mass+"_"+chirality+".root"; 
  TFile* fout = new TFile(outname.c_str(),"RECREATE");

  //setup histograms for muons
  TH1F* h_MuCutFlow = new TH1F("h_MuCutFlow","Muon Cut Flow",13,0,13);
  TH1F* hPtNum_Mu = new TH1F("hPtNum_Mu","p_{T} of Tight Muons",60,0,600);
  TH1F* hPtDen_Mu = new TH1F("hPtDen_Mu","p_{T} of Loose Muons",60,0,600);
  TH1F* hEtaNum_Mu = new TH1F("hEtaNum_Mu","#eta of Tight Muons",15,-3,3);
  TH1F* hEtaDen_Mu = new TH1F("hEtaDen_Mu","#eta of Loose Muons",15,-3,3);

  //setup histograms for electrons
  TH1F* h_ElCutFlow_Barrel = new TH1F("h_ElCutFlow_Barrel","Electron Cut Flow",14,0,14);
  TH1F* h_ElCutFlow_Endcap = new TH1F("h_ElCutFlow_Endcap","Electron Cut Flow",14,0,14);

  TH1F* hPtNumCBIDL_El = new TH1F("hPtNumCBIDL_El","p_{T} of cutBasedLoose Electrons",60,0,600);
  TH1F* hPtNumCBIDT_El = new TH1F("hPtNumCBIDT_El","p_{T} of cutBasedTight Electrons",60,0,600);
  TH1F* hPtNumMVAIDL_El = new TH1F("hPtNumMVAIDL_El","p_{T} of MVA Loose Electrons",60,0,600);
  TH1F* hPtNumMVAIDL_CC_El = new TH1F("hPtNumMVAIDL_CC_El","p_{T} of MVA Loose CC Electrons",60,0,600);
  TH1F* hPtNumMVAIDT_El = new TH1F("hPtNumMVAIDT_El","p_{T} of MVA Tight Electrons",60,0,600);
  TH1F* hPtNumMVAIDT_CC_El = new TH1F("hPtNumMVAIDT_CC_El","p_{T} of MVA Tight CC Electrons",60,0,600);

  TH1F* hPtNumMVAIDLIso_El = new TH1F("hPtNumMVAIDLIso_El","p_{T} of MVA Loose + Iso Electrons",60,0,600);
  TH1F* hPtNumMVAIDLIso_CC_El = new TH1F("hPtNumMVAIDLIso_CC_El","p_{T} of MVA Loose + Iso CC Electrons",60,0,600);
  TH1F* hPtNumMVAIDTIso_El = new TH1F("hPtNumMVAIDTIso_El","p_{T} of MVA Tight + Iso Electrons",60,0,600);
  TH1F* hPtNumMVAIDTIso_CC_El = new TH1F("hPtNumMVAIDTIso_CC_El","p_{T} of MVA Tight + Iso CC Electrons",60,0,600);

  TH1F* hPtDen_El = new TH1F("hPtDen_El","p_{T} of All Electrons",60,0,600);

  TH1F* hEtaNumCBIDL_El = new TH1F("hEtaNumCBIDL_El","#eta of cutBasedLoose Electrons",15,-3,3);
  TH1F* hEtaNumCBIDT_El = new TH1F("hEtaNumCBIDT_El","#eta of cutBasedTight Electrons",15,-3,3);
  TH1F* hEtaNumMVAIDL_El = new TH1F("hEtaNumMVAIDL_El","#eta of mva Loose Electrons",15,-3,3);
  TH1F* hEtaNumMVAIDL_CC_El = new TH1F("hEtaNumMVAIDL_CC_El","#eta of mva Loose CC Electrons",15,-3,3);
  TH1F* hEtaNumMVAIDT_El = new TH1F("hEtaNumMVAIDT_El","#eta of mva Tight Electrons",15,-3,3);
  TH1F* hEtaNumMVAIDT_CC_El = new TH1F("hEtaNumMVAIDT_CC_El","#eta of mva Tight CC Electrons",15,-3,3);

  TH1F* hEtaNumMVAIDLIso_El = new TH1F("hEtaNumMVAIDLIso_El","#eta of mva Loose + Iso Electrons",15,-3,3);
  TH1F* hEtaNumMVAIDLIso_CC_El = new TH1F("hEtaNumMVAIDLIso_CC_El","#eta of mva Loose + Iso CC Electrons",15,-3,3);
  TH1F* hEtaNumMVAIDTIso_El = new TH1F("hEtaNumMVAIDTIso_El","#eta of mva Tight + Iso Electrons",15,-3,3);
  TH1F* hEtaNumMVAIDTIso_CC_El = new TH1F("hEtaNumMVAIDTIso_CC_El","#eta of mva Tight + Iso CC Electrons",15,-3,3);

  TH1F* hEtaDen_El = new TH1F("hEtaDen_El","#eta of All Electrons",15,-3,3);

  //histograms for charge checks
  TH1F* h_relGsf_PtNum = new TH1F("h_relGsf_PtNum"," GSF relative agreement",60,0,600);
  TH1F* h_relGsf_PtDen = new TH1F("h_relGsf_PtDen"," GSF relative agreement",60,0,600);
  TH1F* h_relCtf_PtNum = new TH1F("h_relCtf_PtNum"," GSF relative agreement",60,0,600);
  TH1F* h_relCtf_PtDen = new TH1F("h_relCtf_PtDen"," GSF relative agreement",60,0,600);
  TH1F* h_relScPix_PtNum = new TH1F("h_relScPix_PtNum"," GSF relative agreement",60,0,600);
  TH1F* h_relScPix_PtDen = new TH1F("h_relScPix_PtDen"," GSF relative agreement",60,0,600);

  TH1F* h_relGsf_EtaNum = new TH1F("h_relGsf_EtaNum"," GSF relative agreement",15,-3,3);
  TH1F* h_relGsf_EtaDen = new TH1F("h_relGsf_EtaDen"," GSF relative agreement",15,-3,3);
  TH1F* h_relCtf_EtaNum = new TH1F("h_relCtf_EtaNum"," GSF relative agreement",15,-3,3);
  TH1F* h_relCtf_EtaDen = new TH1F("h_relCtf_EtaDen"," GSF relative agreement",15,-3,3);
  TH1F* h_relScPix_EtaNum = new TH1F("h_relScPix_EtaNum"," GSF relative agreement",15,-3,3);
  TH1F* h_relScPix_EtaDen = new TH1F("h_relScPix_EtaDen"," GSF relative agreement",15,-3,3);

  TH1F* h_accGsf_PtNum = new TH1F("h_accGsf_PtNum"," GSF relative agreement",60,0,600);
  TH1F* h_accGsf_PtDen = new TH1F("h_accGsf_PtDen"," GSF relative agreement",60,0,600);
  TH1F* h_accCtf_PtNum = new TH1F("h_accCtf_PtNum"," GSF relative agreement",60,0,600);
  TH1F* h_accCtf_PtDen = new TH1F("h_accCtf_PtDen"," GSF relative agreement",60,0,600);
  TH1F* h_accScPix_PtNum = new TH1F("h_accScPix_PtNum"," GSF relative agreement",60,0,600);
  TH1F* h_accScPix_PtDen = new TH1F("h_accScPix_PtDen"," GSF relative agreement",60,0,600);

  TH1F* h_accGsf_EtaNum = new TH1F("h_accGsf_EtaNum"," GSF relative agreement",15,-3,3);
  TH1F* h_accGsf_EtaDen = new TH1F("h_accGsf_EtaDen"," GSF relative agreement",15,-3,3);
  TH1F* h_accCtf_EtaNum = new TH1F("h_accCtf_EtaNum"," GSF relative agreement",15,-3,3);
  TH1F* h_accCtf_EtaDen = new TH1F("h_accCtf_EtaDen"," GSF relative agreement",15,-3,3);
  TH1F* h_accScPix_EtaNum = new TH1F("h_accScPix_EtaNum"," GSF relative agreement",15,-3,3);
  TH1F* h_accScPix_EtaDen = new TH1F("h_accScPix_EtaDen"," GSF relative agreement",15,-3,3);

  //histograms for charge checks
  TH1F* h_relGsf_PtNum = new TH1F("h_relGsf_PtNum"," GSF relative agreement",60,0,600);
  TH1F* h_relGsf_PtDen = new TH1F("h_relGsf_PtDen"," GSF relative agreement",60,0,600);
  TH1F* h_relCtf_PtNum = new TH1F("h_relCtf_PtNum"," GSF relative agreement",60,0,600);
  TH1F* h_relCtf_PtDen = new TH1F("h_relCtf_PtDen"," GSF relative agreement",60,0,600);
  TH1F* h_relScPix_PtNum = new TH1F("h_relScPix_PtNum"," GSF relative agreement",60,0,600);
  TH1F* h_relScPix_PtDen = new TH1F("h_relScPix_PtDen"," GSF relative agreement",60,0,600);

  TH1F* h_relGsf_EtaNum = new TH1F("h_relGsf_EtaNum"," GSF relative agreement",15,-3,3);
  TH1F* h_relGsf_EtaDen = new TH1F("h_relGsf_EtaDen"," GSF relative agreement",15,-3,3);
  TH1F* h_relCtf_EtaNum = new TH1F("h_relCtf_EtaNum"," GSF relative agreement",15,-3,3);
  TH1F* h_relCtf_EtaDen = new TH1F("h_relCtf_EtaDen"," GSF relative agreement",15,-3,3);
  TH1F* h_relScPix_EtaNum = new TH1F("h_relScPix_EtaNum"," GSF relative agreement",15,-3,3);
  TH1F* h_relScPix_EtaDen = new TH1F("h_relScPix_EtaDen"," GSF relative agreement",15,-3,3);

  TH1F* h_accGsf_PtNum = new TH1F("h_accGsf_PtNum"," GSF relative agreement",60,0,600);
  TH1F* h_accGsf_PtDen = new TH1F("h_accGsf_PtDen"," GSF relative agreement",60,0,600);
  TH1F* h_accCtf_PtNum = new TH1F("h_accCtf_PtNum"," GSF relative agreement",60,0,600);
  TH1F* h_accCtf_PtDen = new TH1F("h_accCtf_PtDen"," GSF relative agreement",60,0,600);
  TH1F* h_accScPix_PtNum = new TH1F("h_accScPix_PtNum"," GSF relative agreement",60,0,600);
  TH1F* h_accScPix_PtDen = new TH1F("h_accScPix_PtDen"," GSF relative agreement",60,0,600);

  TH1F* h_accGsf_EtaNum = new TH1F("h_accGsf_EtaNum"," GSF relative agreement",15,-3,3);
  TH1F* h_accGsf_EtaDen = new TH1F("h_accGsf_EtaDen"," GSF relative agreement",15,-3,3);
  TH1F* h_accCtf_EtaNum = new TH1F("h_accCtf_EtaNum"," GSF relative agreement",15,-3,3);
  TH1F* h_accCtf_EtaDen = new TH1F("h_accCtf_EtaDen"," GSF relative agreement",15,-3,3);
  TH1F* h_accScPix_EtaNum = new TH1F("h_accScPix_EtaNum"," GSF relative agreement",15,-3,3);
  TH1F* h_accScPix_EtaDen = new TH1F("h_accScPix_EtaDen"," GSF relative agreement",15,-3,3);


  //event loop
  for(int ient = 0; ient < nEntries; ient++){
    if(ient % 1000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;
    tr->GetEntry(ient);
    
    //only do muon cut flow if either cross trigger of one of muon triggers fired
    bool MuTrigFire = false;
    if( tr->HLT_Mu8Ele23 || tr->HLT_Mu23Ele12 || tr->HLT_Mu8Ele17 || tr->HLT_Mu17Ele12 || tr->HLT_Mu30Ele30 || tr->HLT_Mu27TkMu8 || tr->HLT_Mu30TkMu11 || tr->HLT_Mu40TkMu11) MuTrigFire=true;

    if(MuTrigFire){
      for(std::vector<TMuon*>::size_type i=0; i<tr->looseMuons.size();i++){
	//increment to total number of loose muons so we can scale hist correctly at the end
	nLooseMuons+=1;
	//get muon
	TMuon* imu = tr->looseMuons.at(i);
	//if MC match to gen lepton
	bool matched =false;
	if(data) matched = true;
	else{
	  matched = matchToGenLep(imu,tr->genParticles);
	}
	if(!matched) continue;
	//make pt and eta efficiency plots
	hPtDen_Mu->Fill(imu->pt);
	hEtaDen_Mu->Fill(imu->eta);
	if(imu->cutBasedTight()){
	  hPtNum_Mu->Fill(imu->pt);
	  hEtaNum_Mu->Fill(imu->eta);
	}
	//now do cutflow
	doMuCutFlow(h_MuCutFlow, imu);
      }
    }//end check of muon trigger firing

    //only do electron cuts if electron trigger fired
    bool ElTrigFire = false;
    if( tr->HLT_Mu8Ele23 || tr->HLT_Mu23Ele12 || tr->HLT_Mu8Ele17 || tr->HLT_Mu17Ele12 || tr->HLT_Mu30Ele30 || tr->HLT_DoubleEle33 || tr->HLT_Ele17Ele12) ElTrigFire=true;

    if(ElTrigFire){
      //loop for cutBasedID
      for(std::vector<TElectron*>::size_type i=0; i< tr->allElectrons.size(); i++){
	
	//get electron
	TElectron* iel = tr->allElectrons.at(i);
	//if MC match to gen lepton
	bool matched =false;
	if(data) matched = true;
	else{
	  matched = matchToGenLep(iel,tr->genParticles);
	}
	if(!matched) continue;
	//fill denominator histograms
	hPtDen_El->Fill(iel->pt);
	hEtaDen_El->Fill(iel->eta);

	//check if loose and fill numerator
	if(iel->cutBasedLoose25nsSpring15MC()){
	  hPtNumCBIDL_El->Fill(iel->pt);
	  hEtaNumCBIDL_El->Fill(iel->eta);
	}

	//check if tight and fill numerator
	if(iel->cutBasedTight25nsSpring15MC()){
	  hPtNumCBIDT_El->Fill(iel->pt);
	  hEtaNumCBIDT_El->Fill(iel->eta);
	}
	//check if loose and fill numerator
	if(iel->mvaLoose()){
	  hPtNumMVAIDL_El->Fill(iel->pt);
	  hEtaNumMVAIDL_El->Fill(iel->eta);
	}
	if(iel->mvaLoose() && !(iel->chargeConsistency <1)){
	  hPtNumMVAIDL_CC_El->Fill(iel->pt);
	  hEtaNumMVAIDL_CC_El->Fill(iel->eta);
	}
	//check if loose and fill numerator
	if(iel->mvaLooseIso()){
	  hPtNumMVAIDLIso_El->Fill(iel->pt);
	  hEtaNumMVAIDLIso_El->Fill(iel->eta);
	}
	if(iel->mvaLooseIso() && !(iel->chargeConsistency <1)){
	  hPtNumMVAIDLIso_CC_El->Fill(iel->pt);
	  hEtaNumMVAIDLIso_CC_El->Fill(iel->eta);
	}


	//check if tight and fill numerator
	if(iel->mvaTight()){
	  hPtNumMVAIDT_El->Fill(iel->pt);
	  hEtaNumMVAIDT_El->Fill(iel->eta);
	}

	//check if tight and fill numerator
	if(iel->mvaTight() && !(iel->chargeConsistency<1)){
	  hPtNumMVAIDT_CC_El->Fill(iel->pt);
	  hEtaNumMVAIDT_CC_El->Fill(iel->eta);
	}


	//check if tight and fill numerator
	if(iel->mvaTightIso()){
	  hPtNumMVAIDTIso_El->Fill(iel->pt);
	  hEtaNumMVAIDTIso_El->Fill(iel->eta);
	}

	//check if tight and fill numerator
	if(iel->mvaTight() && !(iel->chargeConsistency<1)){
	  hPtNumMVAIDTIso_CC_El->Fill(iel->pt);
	  hEtaNumMVAIDTIso_CC_El->Fill(iel->eta);
	}

	//now do cut flow for electrons
	if(fabs(iel->eta)<=1.479) doElCutFlow_Barrel(h_ElCutFlow_Barrel,iel);
	else doElCutFlow_Endcap(h_ElCutFlow_Endcap,iel);

      }//end loop over loose electrons for cut based id

    }// end el trig check

    //now check charge info for electrons
    for(std::vector<TLepton*>::size_type i =0; i<tr->allElectrons.size(); i++){

      TElectron* iel = tr->allElectrons.at(i);

      bool matched = matchToGenLep(iel,tr->genParticles);
      if(!matched) continue;
      //get gen particle matched to reco electron
      TGenParticle* gP = getMatchedGenParticle(iel,tr->genParticles);

      //make bools for majority agreement - i.e. 2 out of 3 methods
      bool gsfctfCons = iel->gsfCharge==iel->ctfCharge ? true : false;
      bool gsfscpixCons = iel->gsfCharge==iel->scpixCharge ? true : false;
      bool ctfscpixCons = iel->ctfCharge==iel->scpixCharge ? true : false;


      //get relative agreement of scpix charge
      if(gsfctfCons){
	h_relScPix_PtDen->Fill(iel->pt);
	h_relScPix_EtaDen->Fill(iel->eta);
	if(! (iel->chargeConsistency<1)){//if fully consistent means scpix charge agrees with other two
	  h_relScPix_PtNum->Fill(iel->pt);
	  h_relScPix_EtaNum->Fill(iel->eta);
	}
      }

      //get relative agreement of ctf charge
      if(gsfscpixCons){
	h_relCtf_PtDen->Fill(iel->pt);
	h_relCtf_EtaDen->Fill(iel->eta);
	if(! (iel->chargeConsistency<1)){//if fully consistent means ctf charge agrees with other two
	  h_relCtf_PtNum->Fill(iel->pt);
	  h_relCtf_EtaNum->Fill(iel->eta);
	}
      }

      //get relative agreement of gsf charge
      if(ctfscpixCons){
	h_relGsf_PtDen->Fill(iel->pt);
	h_relGsf_EtaDen->Fill(iel->eta);
	if(! (iel->chargeConsistency<1)){//if fully consistent means gsf charge agrees with other two
	  h_relGsf_PtNum->Fill(iel->pt);
	  h_relGsf_EtaNum->Fill(iel->eta);
	}
      }

      //now check accuracy of each method
      h_accGsf_PtDen->Fill(iel->pt);
      h_accGsf_EtaDen->Fill(iel->eta);
      if(gP->charge == iel->gsfCharge) {h_accGsf_PtNum->Fill(iel->pt);h_accGsf_EtaNum->Fill(iel->eta);}
      h_accCtf_PtDen->Fill(iel->pt);
      h_accCtf_EtaDen->Fill(iel->eta);
      if(gP->charge == iel->ctfCharge){ h_accCtf_PtNum->Fill(iel->pt); h_accCtf_EtaNum->Fill(iel->eta);}
      h_accScPix_PtDen->Fill(iel->pt);
      h_accScPix_EtaDen->Fill(iel->eta);
      if(gP->charge == iel->scpixCharge){ h_accScPix_PtNum->Fill(iel->pt); h_accScPix_EtaNum->Fill(iel->eta);}

      
    }//end loop over electrons


  }//end event loop
  
  //scale cutflow diagrams
  h_MuCutFlow->Scale( 1.0 / h_MuCutFlow->GetBinContent(1));
  h_ElCutFlow_Barrel->Scale( 1.0 / h_ElCutFlow_Barrel->GetBinContent(1));
  h_ElCutFlow_Endcap->Scale( 1.0 / h_ElCutFlow_Endcap->GetBinContent(1));

  //write out bin labels
  h_MuCutFlow->GetXaxis()->SetBinLabel(1,"All");
  h_MuCutFlow->GetXaxis()->SetBinLabel(2,"p_{T} > 30");
  h_MuCutFlow->GetXaxis()->SetBinLabel(3,"#eta <2.4");
  h_MuCutFlow->GetXaxis()->SetBinLabel(4,"Global");
  h_MuCutFlow->GetXaxis()->SetBinLabel(5,"#Chi^{2}<10");
  h_MuCutFlow->GetXaxis()->SetBinLabel(6,"dZ<0.5");
  h_MuCutFlow->GetXaxis()->SetBinLabel(7,"dXY <0.2");
  h_MuCutFlow->GetXaxis()->SetBinLabel(8,"nValHits >0");
  h_MuCutFlow->GetXaxis()->SetBinLabel(9,"nMatched Stations >1");
  h_MuCutFlow->GetXaxis()->SetBinLabel(10,"nValPixHits > 0");
  h_MuCutFlow->GetXaxis()->SetBinLabel(11,"nTrackLayers > 5");
  h_MuCutFlow->GetXaxis()->SetBinLabel(12,"RelIso <0.2");
  h_MuCutFlow->GetXaxis()->SetBinLabel(13,"p_{T} > 40 ");

  //bin labels for electrons
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(1,"All");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(2,"p_{T} > 30");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(3,"#eta < 2.4");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(4,"sigmaIetaIeta < 0.0101");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(5,"dEta < 0.00926");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(6,"dPhi<0.0336");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(7,"H/E<0.0597");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(8,"1/E - 1/P < 0.012");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(9,"d0 < 0.0111");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(10,"dZ < 0.0466");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(11,"mHits <= 2");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(12,"conversionVeto");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(13,"relIso < 0.0354");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(14,"chargeConsistent");
  h_ElCutFlow_Barrel->GetXaxis()->SetBinLabel(15,"p_{T} > 40");
  //endcap
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(1,"All");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(2,"p_{T} > 30");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(3,"#eta < 2.4");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(4,"sigmaIetaIeta < 0.0279");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(5,"dEta < 0.00724");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(6,"dPhi < 0.0918");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(7,"H/E < 0.0615");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(8,"1/E - 1/P < 0.00999");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(9,"d0 < 0.0351");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(10,"dZ < 0.417");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(11,"mHits <= 1");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(12,"conversionVeto");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(13,"relIso < 0.0646");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(14,"chargeConsistent");
  h_ElCutFlow_Endcap->GetXaxis()->SetBinLabel(15,"p_{T} > 40");


  //print out efficiency
  std::cout<<"Efficiency for >30 GeV Loose Muons from "<<mass<<" GeV X53 becoming tight: "<<h_MuCutFlow->GetBinContent(12)<<std::endl;
  std::cout<<"Efficiency for >40 GeV Loose Muons from "<<mass<<" GeV X53 becoming tight: "<<h_MuCutFlow->GetBinContent(13)<<std::endl;
  //print out efficiency
  std::cout<<"Barrel Efficiency for >30 GeV Loose Electrons from "<<mass<<" GeV X53 becoming tight: "<<h_ElCutFlow_Barrel->GetBinContent(13)<<std::endl;
  std::cout<<"Barrel Efficiency for >40 GeV Loose Electrons from "<<mass<<" GeV X53 becoming tight: "<<h_ElCutFlow_Barrel->GetBinContent(14)<<std::endl;
  std::cout<<"Endcap Efficiency for >30 GeV Loose Electrons from "<<mass<<" GeV X53 becoming tight: "<<h_ElCutFlow_Endcap->GetBinContent(13)<<std::endl;
  std::cout<<"Endcap Efficiency for >40 GeV Loose Electrons from "<<mass<<" GeV X53 becoming tight: "<<h_ElCutFlow_Endcap->GetBinContent(14)<<std::endl;

  fout->cd();
  //append muon histograms
  /*  fout->Append(h_MuCutFlow);
  fout->Append(hPtNum_Mu);
  fout->Append(hPtDen_Mu);
  fout->Append(hEtaNum_Mu);
  fout->Append(hEtaDen_Mu);
  //append electron histograms
  fout->Append(h_ElCutFlow_Barrel);
  fout->Append(h_ElCutFlow_Endcap);
  fout->Append(hPtNumCBIDL_El);
  fout->Append(hEtaNumCBIDL_El);
  fout->Append(hPtNumCBIDT_El);
  fout->Append(hEtaNumCBIDT_El);
  fout->Append(hPtNumMVAIDL_El);
  fout->Append(hEtaNumMVAIDL_El);
  fout->Append(hPtNumMVAIDL_CC_El);
  fout->Append(hEtaNumMVAIDL_CC_El);
  fout->Append(hPtNumMVAIDT_El);
  fout->Append(hEtaNumMVAIDT_El);
  fout->Append(hPtNumMVAIDT_CC_El);
  fout->Append(hEtaNumMVAIDT_CC_El);

  fout->Append(hPtNumMVAIDLIso_El);
  fout->Append(hEtaNumMVAIDLIso_El);
  fout->Append(hPtNumMVAIDLIso_CC_El);
  fout->Append(hEtaNumMVAIDLIso_CC_El);
  fout->Append(hPtNumMVAIDTIso_El);
  fout->Append(hEtaNumMVAIDTIso_El);
  fout->Append(hPtNumMVAIDTIso_CC_El);
  fout->Append(hEtaNumMVAIDTIso_CC_El);

  fout->Append(hPtDen_El);
  fout->Append(hEtaDen_El);*/
  std::cout<<"finished appending"<<std::endl;
  fout->Write();
  std::cout<<"wrote file"<<std::endl;
  fout->Close();
  std::cout<<"closed file"<<std::endl;
  delete fout;
  return 0;
}
 
void doMuCutFlow(TH1F*& hist, TMuon* mu){

  //increment first bin so that it represents 'null' cut
  hist->AddBinContent(1);

  if(mu->pt<30)                return;
  else hist->AddBinContent(2);
  if(mu->eta>2.4)              return;
  else hist->AddBinContent(3);
  if(!mu->Global)              return;
  else hist->AddBinContent(4);
  if(mu->chi2 > 10)            return;
  else hist->AddBinContent(5);
  if(mu->dz > 0.5)             return;
  else hist->AddBinContent(6);
  if(mu->dxy > 0.2)            return;
  else hist->AddBinContent(7);
  if(mu->nValMuHits < 1)       return;
  else hist->AddBinContent(8);
  if(mu->nMatchedStations < 2) return;
  else hist->AddBinContent(9);
  if(mu->nValPixelHits < 1)    return;
  else hist->AddBinContent(10);
  if(mu->nTrackerLayers < 6)   return;
  else hist->AddBinContent(11);
  if(mu->relIso > 0.2)         return;
  else hist->AddBinContent(12);
  if(mu->pt<40)                return;
  else hist->AddBinContent(13);
}

void doElCutFlow_Barrel(TH1F*& hist, TElectron* el){

  //increment first bin so that it represents 'null' cut
  hist->AddBinContent(1);

  if(el->pt<30) return;
  else hist->AddBinContent(2);

  if(el->eta>2.4) return;
  else hist->AddBinContent(3);

  if(el->sigmaIetaIeta >= 0.0101)  return;
  else hist->AddBinContent(4);

  if(fabs(el->dEta) >= 0.00926)    return;
  else hist->AddBinContent(5);

  if(fabs(el->dPhi) >= 0.0336)     return;
  else hist->AddBinContent(6);

  if(el->hOverE >= 0.0597)         return;
  else hist->AddBinContent(7);

  if(el->ooEmooP >= 0.012)         return;
  else hist->AddBinContent(8);

  if(fabs(el->d0) >= 0.0111)       return;
  else hist->AddBinContent(9);

  if(fabs(el->dZ) >= 0.0466)       return;
  else hist->AddBinContent(10);

  if(el->mHits > 2)                return;
  else hist->AddBinContent(11);

  if(!el->passConversion)          return;
  else hist->AddBinContent(12);

  if(el->relIsoEA > 0.0354)        return;
  else hist->AddBinContent(13);

  if(el->chargeConsistency < 1)    return;
  else hist->AddBinContent(14);

  if(el->pt<40)                   return;
  else hist->AddBinContent(15);
}

void doElCutFlow_Endcap(TH1F*& hist, TElectron* el){

  //increment first bin so that it represents 'null' cut
  hist->AddBinContent(1);

  if(el->pt<30) return;
  else hist->AddBinContent(2);

  if(el->eta>2.4) return;
  else hist->AddBinContent(3);

  if(el->sigmaIetaIeta >= 0.0279)  return;
  else  hist->AddBinContent(4);

  if(fabs(el->dEta) >= 0.00724)    return;
  else  hist->AddBinContent(5);

  if(fabs(el->dPhi) >= 0.0918)     return;
  else  hist->AddBinContent(6);

  if(el->hOverE >= 0.0615)         return;
  else  hist->AddBinContent(7);

  if(el->ooEmooP >= 0.00999)       return;
  else  hist->AddBinContent(8);

  if(fabs(el->d0) >= 0.0351)       return;
  else  hist->AddBinContent(9);

  if(fabs(el->dZ) >= 0.417)        return;
  else  hist->AddBinContent(10);

  if(el->mHits > 1)                return;
  else  hist->AddBinContent(11);

  if(!el->passConversion)          return;
  else  hist->AddBinContent(12);

  if(el->relIsoEA >= 0.0646)       return; 
  else  hist->AddBinContent(13);

  if(el->chargeConsistency < 1)    return;
  else  hist->AddBinContent(14);

  if(el->pt<40)                   return;
  else hist->AddBinContent(15);;

}

bool matchToGenLep(TMuon* mu, std::vector<TGenParticle*> genParticles){

  float dR=999;
  //run through gen particle collection:
  for(unsigned int igen=0; igen<genParticles.size(); igen++){
    TGenParticle* genParticle = genParticles.at(igen);
    //only run over muons from hard scattering
    if( ! (fabs(genParticle->id)==13) ) continue;
    if( ! (genParticle->status==23 || genParticle->status==1) ) continue;

    float drtemp = pow( pow( mu->eta - genParticle->eta, 2 ) + pow( mu->phi - genParticle->phi, 2), 0.5);
    if(drtemp < dR){
      dR = drtemp;
    }
  }

  //now we have a min deltaR between our muon and all muons from hard scattering, if it is less than 0.15 let's consider it matched
  if(dR <0.1) return true;
  else return false;
  
}


bool matchToGenLep(TElectron* el, std::vector<TGenParticle*> genParticles){

  float dR=999;
  //run through gen particle collection:
  for(unsigned int igen=0; igen<genParticles.size(); igen++){
    TGenParticle* genParticle = genParticles.at(igen);
    //only run over electrons from hard scattering
    if( ! (fabs(genParticle->id)==11) ) continue;
    if( ! (genParticle->status==23 || genParticle->status==1) ) continue;

    float drtemp = pow( pow( el->eta - genParticle->eta, 2 ) + pow( el->phi - genParticle->phi, 2), 0.5);
    if(drtemp < dR){
      dR = drtemp;
    }
  }

  //now we have a min deltaR between our electron and all electrons from hard scattering, if it is less than 0.15 let's consider it matched
  if(dR <0.1) return true;
  else return false;
  
}
    
TGenParticle* getMatchedGenParticle(TElectron* el, std::vector<TGenParticle*> genParticles){


  TGenParticle* gp=0;


  float dR=999;
  //run through gen particle collection:
  for(unsigned int igen=0; igen<genParticles.size(); igen++){
    TGenParticle* genParticle = genParticles.at(igen);
    //only run over electrons from hard scattering
    if( ! (fabs(genParticle->id)==11) ) continue;
    if( ! (genParticle->status==23 || genParticle->status==1) ) continue;

    float drtemp = pow( pow( el->eta - genParticle->eta, 2 ) + pow( el->phi - genParticle->phi, 2), 0.5);
    if(drtemp < dR){
      dR = drtemp;
      gp=genParticle;
    }
  }

  return gp;
}
