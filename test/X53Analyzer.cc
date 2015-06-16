#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include <vector>
#include "TLorentzVector.h"
#include "TChain.h"
#include "../interface/TreeReader.h"
#include <stdio.h>
#include "LeptonAnalyzer.cc"
#include "JetAnalyzer.cc"
#include "GenAnalyzer.cc"
#include "../interface/TreeMaker.h"
#include <assert.h>
#include <map>
#include <string>
#include <sstream> 

std::vector<TLepton*> makeLeptons(std::vector<TMuon*>, std::vector<TElectron*>);
std::vector<TLepton*> makeSSLeptons(std::vector<TLepton*>);
bool checkSameSignLeptons(std::vector<TLepton*>);
int getNSSDLGen(std::vector<TGenParticle*>, int);
void printParticle(TGenParticle*);
void printParticle(TLepton*);

int main(int argc, char* argv[]){

  typedef std::map<std::string,std::string> StringMap;
 
 StringMap bg_samples, sig_samples;
 bg_samples["TTbar"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_TTbar.root";
 bg_samples["TTW"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_TTW.root";
 bg_samples["TTZ"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_TTZ.root";
 bg_samples["TTWW"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_TTWW.root";
 bg_samples["WW"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_WW.root";
 bg_samples["WWW"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_WWW.root";
 bg_samples["WZ"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_WZ.root";
 bg_samples["ZZ"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_ZZ.root";
 bg_samples["WJets"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_WJets.root";
 
 
 sig_samples["X53X53m700RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-700_right.root";
 sig_samples["X53X53m800RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-800_right.root";
 sig_samples["X53X53m900RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-900_right.root";
 //sig_samples["X53X53m1000RH"]="ljmet_tree_X53X53ToAll_M-1000_right.root";
 sig_samples["X53X53m1000RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1000_right.root";
 sig_samples["X53X53m1100RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1100_right.root";
 sig_samples["X53X53m1200RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1200_right.root";
 sig_samples["X53X53m1300RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1300_right.root";
 sig_samples["X53X53m1400RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1400_right.root";
 sig_samples["X53X53m1500RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1500_right.root";
 sig_samples["X53X53m1600RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1600_right.root";
 sig_samples["X53X53m700LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-700_left.root";
 sig_samples["X53X53m800LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-800_left.root";
 sig_samples["X53X53m900LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-900_left.root";
 sig_samples["X53X53m1000LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1000_left.root";
 sig_samples["X53X53m1100LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1100_left.root";
 sig_samples["X53X53m1200LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1200_left.root";
 sig_samples["X53X53m1300LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1300_left.root";
 sig_samples["X53X53m1400LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1400_left.root";
 sig_samples["X53X53m1500LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1500_left.root";
 sig_samples["X53X53m1600LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53X53ToAll_M-1600_left.root";

 sig_samples["X53Tm700RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-700_right.root";
 sig_samples["X53Tm800RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-800_right.root";
 sig_samples["X53Tm900RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-900_right.root";
 sig_samples["X53Tm1000RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1000_right.root";
 sig_samples["X53Tm1100RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1100_right.root";
 sig_samples["X53Tm1200RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1200_right.root";
 sig_samples["X53Tm1300RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1300_right.root";
 sig_samples["X53Tm1400RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1400_right.root";
 sig_samples["X53Tm1500RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1500_right.root";
 sig_samples["X53Tm1600RH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1600_right.root";
 sig_samples["X53Tm700LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-700_left.root";
 sig_samples["X53Tm800LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-800_left.root";
 sig_samples["X53Tm900LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-900_left.root";
 sig_samples["X53Tm1000LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1000_left.root";
 sig_samples["X53Tm1100LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1100_left.root";
 sig_samples["X53Tm1200LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1200_left.root";
 sig_samples["X53Tm1300LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1300_left.root";
 sig_samples["X53Tm1400LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1400_left.root";
 sig_samples["X53Tm1500LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1500_left.root";
 sig_samples["X53Tm1600LH"]="/eos/uscms/store/user/lpctlbsm/clint/PHYS14/Inclusive_Decays/PU20/ljmet_trees/ljmet_tree_X53TToAll_M-1600_left.root";


  bool signal=false;
  bool bg_mc=false;
  bool bg_dd=false;
  bool data=false;

  //check usage
  bool correctusage=true;
  if(argc!=2 || ( bg_samples.find(argv[1])==bg_samples.end() && sig_samples.find(argv[1])==sig_samples.end()) ) correctusage=false;
  if(!correctusage){
    std::cout<<"Need to supply argument for sample name of one of the following"<<std::endl;
    std::cout<<std::endl<<"********** Background *********"<<std::endl;
    for(std::map<std::string,std::string>::iterator iter=bg_samples.begin(); iter!= bg_samples.end(); iter++){
      std::cout<<iter->first<<std::endl;
    }
    std::cout<<std::endl<<"********** Signal *********"<<std::endl;
    for(std::map<std::string,std::string>::iterator iter=sig_samples.begin(); iter!= sig_samples.end(); iter++){
      std::cout<<iter->first<<std::endl;
    }  
    return 0;
  }

  if(bg_samples.find(argv[1])!=bg_samples.end()) bg_mc=true;
  if(sig_samples.find(argv[1])!=sig_samples.end()) signal=true;

  //make TreeReader
  std::string filename;
  if(bg_mc) filename = bg_samples.find(argv[1])->second;
  if(signal) filename = sig_samples.find(argv[1])->second;
  std::cout<<"running file: "<<filename<<std::endl;
  //make output file
  std::stringstream outnamestream;
  outnamestream<<argv[1]<<".root";
  std::string outname = outnamestream.str();
  TFile* fsig = new TFile(outname.c_str(),"RECREATE");

  TreeMaker* tm = new TreeMaker();
  tm->InitTree("tEvts_ssdl");

  TreeReader* tr= new TreeReader(filename.c_str());
  TTree* t=tr->tree;


  TH1F* h_MuCutFlow = new TH1F("h_MuCutFlow","Cut Flow For Muons",13,0,13);



  doGenPlots(fsig,t,tr);
  //cd back to main directory after making gen plots
  fsig->cd();

  int nEntries = t->GetEntries();

  int nMuMu=0;
  int nElMu=0;
  int nElEl=0;
  int nGenMuMu=0;
  int nGenElMu=0;
  int nGenElEl=0;

  for(int ient=0; ient<nEntries; ient++){

    if(ient % 1000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;

    tr->GetEntry(ient);


    //bool GenSamesign=false;
    //std::vector<TGenParticle*> vSSGenLep;
    //get number of generated same-sign dilepton events gen particle collection (second parameter is number of muons to search for)
    nGenMuMu += getNSSDLGen(tr->genParticles, 2);
    nGenElMu += getNSSDLGen(tr->genParticles, 1);
    nGenElEl += getNSSDLGen(tr->genParticles, 0);

  


    //Muon CutFlow                                                                                                                                                                                               
    for(unsigned int uimu=0; uimu<tr->allMuons.size();uimu++){
      TMuon* imu = tr->allMuons.at(uimu);

      //run through gen particle collection:                                                                                                                                                                      
      float dR=999;
      for(unsigned int igen=0; igen<tr->genParticles.size(); igen++){
        //only run over muons from hard scattering                                                                                                     
        if(!( ( fabs(tr->genParticles.at(igen)->id)==13) && (tr->genParticles.at(igen)->status==23 || tr->genParticles.at(igen)->status==1)) ) continue;
        float drtemp = pow( pow( imu->eta - tr->genParticles.at(igen)->eta, 2 ) + pow( imu->phi - tr->genParticles.at(igen)->phi, 2), 0.5);
        if(drtemp < dR){
          dR = drtemp;
        }
      }

      //now check to make sure the muon is matched by requiring deltaR be les than 0.15                                                                                                                           
      if(dR >= 0.15) continue;

      if(imu->PFMuon) h_MuCutFlow->Fill(0.5,1);
      else continue;
      if(imu->Global || imu->Tracker) h_MuCutFlow->Fill(1.5,1);
      else continue;
      if(imu->Global) h_MuCutFlow->Fill(2.5,1);
      else continue;
      if(imu->pt>30) h_MuCutFlow->Fill(3.5,1);
      else continue;
      if(imu->eta < 2.4) h_MuCutFlow->Fill(4.5,1);
      else continue;
      if(imu->chi2<10) h_MuCutFlow->Fill(5.5,1);
      else continue;
      if(imu->dz < 0.5) h_MuCutFlow->Fill(6.5,1);
      else continue;
      if(imu->dxy < 0.2) h_MuCutFlow->Fill(7.5,1);
      else continue;
      if(imu->nValMuHits>=1) h_MuCutFlow->Fill(8.5,1);
      else continue;
      if(imu->nMatchedStations >=2) h_MuCutFlow->Fill(9.5,1);
      else continue;
      if(imu->nValPixelHits >=1) h_MuCutFlow->Fill(10.5,1);
      else continue;
      if(imu->nTrackerLayers > 5) h_MuCutFlow->Fill(11.5,1);
      else continue;
      if(imu->relIso < 0.2) h_MuCutFlow->Fill(12.5,1);
    }


    //make vector of good Leptons
    std::vector<TLepton*> goodLeptons = makeLeptons(tr->goodMuons, tr->goodElectrons);

    //now that we have good leptons check for two with same-sign charge
    bool samesign = checkSameSignLeptons(goodLeptons);

    if(!samesign) continue;

    std::vector<TLepton*> vSSLep = makeSSLeptons(goodLeptons);

    //dummy check to make sure the vector got filled properly
    assert(vSSLep.size() > 1);

    //now get dilepton mass
    float dilepMass = (vSSLep.at(0)->lv + vSSLep.at(1)->lv).M();

    float HT=0;
    for(unsigned int uijet=0; uijet<tr->allAK4Jets.size();uijet++){
      HT+=tr->allAK4Jets.at(uijet)->pt;
    }

    //get channel
    int nMu=0;
    if(vSSLep.at(0)->isMu) nMu++;
    if(vSSLep.at(1)->isMu) nMu++;


    tm->FillTree(vSSLep, tr->allAK4Jets, HT, tr->MET, dilepMass,nMu);

    //bools for channels
    bool mumu=false;
    bool elmu=false;
    bool elel=false;


    //ok at this point only have events with same-sign leptons, now let's do simple check to see how many of each channel we have:
    if(vSSLep.size()>=2){
      //std::cout<<"found same-sign dileptons"<<std::endl;
      //std::cout<<"Number of ssdl: "<<vSSLep.size()<<" Size of genparticles is: "<<tr->genParticles.size()<<std::endl;
      for(unsigned int ui=0; ui<tr->genParticles.size(); ui++){
	//printParticle(tr->genParticles.at(ui));
      }
      //std::cout<<"\n *** End Event *** \n"<<std::endl;
    }

    if(vSSLep.at(0)->isMu && vSSLep.at(1)->isMu){ nMuMu+=1; mumu=true;}
    else if( ( vSSLep.at(0)->isEl && vSSLep.at(1)->isMu) || (vSSLep.at(0)->isMu && vSSLep.at(1)->isEl)){ nElMu+=1; elmu=true;}
    else {nElEl+=1; elel=true;}

  }//end event loop

  //write the tree
  tm->tree->Write();


  //normalize cutflow to first bin                                                                                                                                                                                
  h_MuCutFlow->Scale( 1. / h_MuCutFlow->GetBinContent(1) );

  //set bin labels                                                                                                                                                                                                
  h_MuCutFlow->GetXaxis()->SetBinLabel(1,"All Loose Muons");
  h_MuCutFlow->GetXaxis()->SetBinLabel(2,"is GlobalMuon");
  h_MuCutFlow->GetXaxis()->SetBinLabel(3,"is PF Muon");
  h_MuCutFlow->GetXaxis()->SetBinLabel(4,"p_{T} >30");
  h_MuCutFlow->GetXaxis()->SetBinLabel(5,"#eta <2.4");
  h_MuCutFlow->GetXaxis()->SetBinLabel(6,"#chi^{2} <10");
  h_MuCutFlow->GetXaxis()->SetBinLabel(7,"dZ<0.5");
  h_MuCutFlow->GetXaxis()->SetBinLabel(8,"dXY<0.2");
  h_MuCutFlow->GetXaxis()->SetBinLabel(9,"N_{ValidMuHits}>=1");
  h_MuCutFlow->GetXaxis()->SetBinLabel(10,"N_{MatchStations}>=2");
  h_MuCutFlow->GetXaxis()->SetBinLabel(11,"N_{ValidPixHits}>=1");
  h_MuCutFlow->GetXaxis()->SetBinLabel(12,"N_{TrackerLayer}>5");
  h_MuCutFlow->GetXaxis()->SetBinLabel(13,"RelIso <0.2");




  fsig->Write();
  fsig->Close();

  std::cout<<"Number of Gen MuMu: "<<nGenMuMu<<std::endl;
  std::cout<<"Number of MuMu: "<<nMuMu<<std::endl;
  std::cout<<"Number of ElMu: "<<nElMu<<std::endl;
  std::cout<<"Number of ElEl: "<<nElEl<<std::endl;

}


std::vector<TLepton*> makeLeptons(std::vector<TMuon*> muons, std::vector<TElectron*> electrons){

  std::vector<TLepton*> Leptons;

  //fill with  muons
  for(unsigned int uimu=0; uimu<muons.size(); uimu++){
    TMuon* imu = muons.at(uimu);
    TLepton* iLep = new TLepton(imu->pt,imu->eta,imu->phi,imu->energy,imu->charge);
    iLep->isMu = true;
    iLep->isEl = false;
    Leptons.push_back(iLep);
 
  }
  
  //fill with  electrons
  for(unsigned int uiel=0; uiel<electrons.size(); uiel++){
    TElectron* iel = electrons.at(uiel);
    TLepton* iLep = new TLepton(iel->pt,iel->eta,iel->phi,iel->energy,iel->charge);
    iLep->isMu = false;
      iLep->isEl = true;
      Leptons.push_back(iLep);
 
  }
  
  return Leptons;

}

bool checkSameSignLeptons(std::vector<TLepton*> leptons){

  bool samesign=false;

  for(unsigned int uilep=0; uilep<leptons.size(); uilep++){
    for(unsigned int ujlep=uilep+1; ujlep<leptons.size(); ujlep++){
      if(leptons.at(uilep)->charge == leptons.at(ujlep)->charge){
	samesign=true;
      }
    }
  }

  return samesign;
  
}


std::vector<TLepton*> makeSSLeptons(std::vector<TLepton*> leptons){

  std::vector<TLepton*> vSSLep;

  for(unsigned int uilep=0; uilep<leptons.size(); uilep++){
    for(unsigned int ujlep=uilep+1; ujlep<leptons.size(); ujlep++){
      if(leptons.at(uilep)->charge == leptons.at(ujlep)->charge){
	
	vSSLep.push_back(leptons.at(uilep));
	vSSLep.push_back(leptons.at(ujlep));

      }
    }
  }

  return vSSLep;
  
}

int getNSSDLGen(std::vector<TGenParticle*> genParticles, int nMu){

  bool samesign;
 
  int flav1=-999;
  int flav2=-999;

  for(unsigned int uigen=0; uigen < genParticles.size(); uigen++){
    //only check particles from the hard scattering
    //if( genParticles.at(uigen)->status!=23) continue;
    //only check electrons and muons
    if( !( abs(genParticles.at(uigen)->id)==11 || abs(genParticles.at(uigen)->id)==13) ) continue;
    for(unsigned int ujgen=0;  ujgen < genParticles.size(); ujgen++){
      //only check particles from the hard scattering
    if( genParticles.at(ujgen)->status!=23) continue;
      if(ujgen==uigen) continue;
      //std::cout<<"flavor 1: "<<genParticles.at(uigen)->id<<" w/ charge: "<<genParticles.at(uigen)->charge<<" flavor 2: "<<genParticles.at(ujgen)->id<<" w/ charge: "<<genParticles.at(ujgen)->charge<<std::endl;
      //only check electrons and muons
      if( !( abs(genParticles.at(ujgen)->id)==11 || abs(genParticles.at(ujgen)->id)==13) ) continue;
      if( genParticles.at(uigen)->charge == genParticles.at(ujgen)->charge){
	samesign = true;
	flav1 = abs(genParticles.at(uigen)->id);
	flav2 = abs(genParticles.at(ujgen)->id);
      }
    }

  }

  //std::cout<<"\n *** End Event *** \n"<<std::endl;

  if(!samesign) return 0;

  if(nMu==2){
    if( flav1 ==13 && flav2==13) return 1;
    else return 0;
  }

  if(nMu==1){
    if( (flav1==11 && flav2==13) || (flav1==13 || flav2==11) ) return 1;
    else return 0;
  }


  if(nMu==0){
    if( flav1==11 && flav2==11) return 1;
    else return 0;
  }

  //in case none above 
  return 0;

}


void printParticle(TGenParticle* p){
	std::cout<<"genP id: "<<p->id<<" charge "<<p->charge<<" status: "<<p->status<<" pt: "<<p->pt<<" eta: "<<p->eta<<" phi: "<<p->phi<<std::endl;
}

void printParticle(TLepton* l){
	std::cout<<"charge "<<l->charge<<" pt: "<<l->pt<<" eta: "<<l->eta<<" phi: "<<l->phi<<std::endl;
}
