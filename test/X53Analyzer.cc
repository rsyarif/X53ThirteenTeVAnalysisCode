#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <map>
#include <string>
#include <sstream> 
#include <algorithm>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TChain.h"

#include "../interface/TreeReader.h"
#include "JetAnalyzer.cc"
#include "GenAnalyzer.cc"
#include "../interface/TreeMaker.h"
#include "../plugins/Macros.cc"
#include "../plugins/EventFilterFromFile_MuonEG.cc"
#include "../plugins/EventFilterFromFile_DoubleMu.cc"
#include "../plugins/EventFilterFromFile_DoubleEG.cc"

std::vector<TLepton*> makeLeptons(std::vector<TMuon*>, std::vector<TElectron*>, float, std::string, std::string, bool);
std::vector<TLepton*> makeSSLeptons(std::vector<TLepton*>);
std::vector<TLepton*> makeOSLeptonsForDY(std::vector<TLepton*>);
bool checkSameSignLeptons(std::vector<TLepton*>);
bool checkOppositeSignLeptonsForDY(std::vector<TLepton*>);
int getNSSDLGen(std::vector<TGenParticle*>, int);
void printParticle(TGenParticle*);
void printParticle(TLepton*);
bool checkSecondaryZVeto(std::vector<TLepton*> leps, std::vector<TMuon*> muons, std::vector<TElectron*> electrons);
std::vector<TLepton*> pruneSSLep(std::vector<TLepton*> allLeps, std::vector<TLepton*> ssLeps);
bool sortByPt(TLepton* lep1, TLepton* lep2){return lep1->pt > lep2->pt;};

int main(int argc, char* argv[]){


  if(argc!=4) return 0;
  std::string argv1=argv[1];
  std::string elID = argv[2];
  std::string muID = argv[3];

  typedef std::map<std::string,std::string> StringMap;
  
  StringMap bg_samples, sig_samples,data_samples;
  bg_samples["TTJets"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_TTJets.root";
  bg_samples["TTbar"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_TTbar-powheg.root";
  bg_samples["TTbar_ext1"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_TTbar-powheg_ext_part1.root";
  bg_samples["TTbar_ext2"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_TTbar-powheg_ext_part2.root";
  bg_samples["TTW"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_TTW.root";
  bg_samples["TTZ"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_TTZ.root";
  bg_samples["TTWW"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_TTWW.root";
  bg_samples["WW"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_WW.root";
  bg_samples["WWW"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_WWW.root";
  bg_samples["WZ"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_WZ.root";
  bg_samples["ZZ"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_ZZ.root";
  bg_samples["WJets"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_WJets.root";
  bg_samples["DYJets"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_DYJets.root";
  bg_samples["WWZ"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_WWZ.root";
  bg_samples["WpWp"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_WpWp.root";

  //nonoPrompt versions
  bg_samples["NonPromptTTJets"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_TTJets.root";
  bg_samples["NonPromptWJets"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_WJets.root";
  bg_samples["NonPromptTTbar"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_TTbar-powheg.root";
  bg_samples["NonPromptTTbar_ext1"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_TTbar-powheg_ext_part1.root";
  bg_samples["NonPromptTTbar_ext2"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_TTbar-powheg_ext_part2.root";

  
  sig_samples["X53X53m700RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m700RH.root";
  sig_samples["X53X53m800RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m800RH.root";
  sig_samples["X53X53m900RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m900RH.root";
  //sig_samples["X53X53m1000RH"]="ljmet_X53X53m1000RH.root";
  sig_samples["X53X53m1000RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1000RH.root";
  sig_samples["X53X53m1100RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1100RH.root";
  sig_samples["X53X53m1200RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1200RH.root";
  sig_samples["X53X53m1300RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1300RH.root";
  sig_samples["X53X53m1400RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1400RH.root";
  sig_samples["X53X53m1500RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1500RH.root";
  sig_samples["X53X53m1600RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1600RH.root";
  sig_samples["X53X53m700LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m700LH.root";
  sig_samples["X53X53m800LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m800LH.root";
  sig_samples["X53X53m900LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m900LH.root";
  sig_samples["X53X53m1000LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1000LH.root";
  sig_samples["X53X53m1100LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1100LH.root";
  sig_samples["X53X53m1200LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1200LH.root";
  sig_samples["X53X53m1300LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1300LH.root";
  sig_samples["X53X53m1400LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1400LH.root";
  sig_samples["X53X53m1500LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1500LH.root";
  sig_samples["X53X53m1600LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1600LH.root";

  sig_samples["X53X53m700RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m700RH_Inc.root";
  sig_samples["X53X53m800RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m800RH_Inc.root";
  sig_samples["X53X53m900RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m900RH_Inc.root";
  sig_samples["X53X53m1000RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1000RH_Inc.root";
  sig_samples["X53X53m1100RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1100RH_Inc.root";
  sig_samples["X53X53m1200RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1200RH_Inc.root";
  sig_samples["X53X53m1300RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1300RH_Inc.root";
  sig_samples["X53X53m1400RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1400RH_Inc.root";
  sig_samples["X53X53m1500RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1500RH_Inc.root";
  sig_samples["X53X53m1600RH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1600RH_Inc.root";
  sig_samples["X53X53m700LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m700LH_Inc.root";
  sig_samples["X53X53m800LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m800LH_Inc.root";
  sig_samples["X53X53m900LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m900LH_Inc.root";
  sig_samples["X53X53m1000LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1000LH_Inc.root";
  sig_samples["X53X53m1100LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1100LH_Inc.root";
  sig_samples["X53X53m1200LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1200LH_Inc.root";
  sig_samples["X53X53m1300LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1300LH_Inc.root";
  sig_samples["X53X53m1400LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1400LH_Inc.root";
  sig_samples["X53X53m1500LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1500LH_Inc.root";
  sig_samples["X53X53m1600LH_Inc"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53X53m1600LH_Inc.root";

  
  sig_samples["X53Tm700RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-700_right.root";
  sig_samples["X53Tm800RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-800_right.root";
  sig_samples["X53Tm900RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-900_right.root";
  sig_samples["X53Tm1000RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1000_right.root";
  sig_samples["X53Tm1100RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1100_right.root";
  sig_samples["X53Tm1200RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1200_right.root";
  sig_samples["X53Tm1300RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1300_right.root";
  sig_samples["X53Tm1400RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1400_right.root";
  sig_samples["X53Tm1500RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1500_right.root";
  sig_samples["X53Tm1600RH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1600_right.root";
  sig_samples["X53Tm700LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-700_left.root";
  sig_samples["X53Tm800LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-800_left.root";
  sig_samples["X53Tm900LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-900_left.root";
  sig_samples["X53Tm1000LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1000_left.root";
  sig_samples["X53Tm1100LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1100_left.root";
  sig_samples["X53Tm1200LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1200_left.root";
  sig_samples["X53Tm1300LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1300_left.root";
  sig_samples["X53Tm1400LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1400_left.root";
  sig_samples["X53Tm1500LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1500_left.root";
  sig_samples["X53Tm1600LH"]="/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_X53TToAll_M-1600_left.root";

  //data samples
  data_samples["Data"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/PreApproval/ljmet_trees/ljmet_Data_All.root";
  data_samples["NonPromptData"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/PreApproval/ljmet_trees/ljmet_Data_All.root";
  data_samples["ChargeMisID"]="/eos/uscms/store/user/lpctlbsm/clint/Run2015D/PreApproval/ljmet_trees/ljmet_Data_All.root";

  bool signal=false;
  bool bg_mc=false;
  bool bg_np = false; //bool to run  using tight loose method to get non prompt background
  //bool bg_dd=false;
  bool data=false;

  //check usage
  bool correctusage=true;
  if(argc!=4 || ( bg_samples.find(argv[1])==bg_samples.end() && sig_samples.find(argv[1])==sig_samples.end() && data_samples.find(argv[1])==data_samples.end() && argv1!="NonPromptMC") ) correctusage=false;
  if(!correctusage){
    std::cout<<"Need to specify electron and muon ID as well as supply argument for sample name of one of the following"<<std::endl;
    std::cout<<std::endl<<"********** Background *********"<<std::endl;
    for(std::map<std::string,std::string>::iterator iter=bg_samples.begin(); iter!= bg_samples.end(); iter++){
      std::cout<<iter->first<<std::endl;
    }
    std::cout<<std::endl<<"********** Signal *********"<<std::endl;
    for(std::map<std::string,std::string>::iterator iter=sig_samples.begin(); iter!= sig_samples.end(); iter++){
      std::cout<<iter->first<<std::endl;
    }  
    std::cout<<"********* OR Specify \'NonPromptMC\' to run over MC using Data-Driven Method"<<std::endl;
    std::cout<<" Examples:\n       ./X53Analyzer.o TTJets CBTight CBMed\n       ./X53Analyzer.o NonPromptMC MVATight CBTight"<<std::endl;
    return 0;
  }

  if(bg_samples.find(argv[1])!=bg_samples.end()) bg_mc=true;
  if(sig_samples.find(argv[1])!=sig_samples.end()) signal=true;
  if(data_samples.find(argv[1])!=data_samples.end()) data=true;
  std::string sample = argv[1];
  if(sample.find("NonPrompt")!=std::string::npos) bg_np = true;
  
  //make TreeReader
  std::string filename;
  if(bg_mc) filename = bg_samples.find(argv[1])->second;
  if(signal) filename = sig_samples.find(argv[1])->second;
  if(data) filename = data_samples.find(argv[1])->second;
  if(bg_np)  std::cout<<"running NonPrompt on  file: "<<filename<<std::endl;
  else  std::cout<<"running RegularMethod  on  file: "<<filename<<std::endl;

  //make output file
  std::stringstream outnamestream;
  if(bg_np){
    outnamestream<<argv[1]<<"_Mu"<<muID<<"_El"<<elID<<".root";
  }
  else{
    outnamestream<<argv[1]<<"_Mu"<<muID<<"_El"<<elID<<".root";
  }
  std::string outname = outnamestream.str();
  TFile* fsig = new TFile(outname.c_str(),"RECREATE");

  TreeMaker* tm_ssdl = new TreeMaker();
  tm_ssdl->InitTree("tEvts_ssdl");
  TreeMaker* tm_sZVeto = new TreeMaker();
  tm_sZVeto->InitTree("tEvts_sZVeto");

  TreeReader* tr;
  tr = new TreeReader(filename.c_str(),!data);
  
  TTree* t=tr->tree;

  //histogram for cutflow
  TH1F* h_MuCutFlow = new TH1F("h_MuCutFlow","Cut Flow For Muons",13,0,13);

  //histogram for trigger studies
  TH1F* h_DoubleEle33Num = new TH1F("h_DoubleEle33Num","",60,0,600);
  TH1F* h_DoubleEle33_MWNum = new TH1F("h_DoubleEle33_MWNum","",60,0,600);
  TH1F* h_Ele27WP85Num = new TH1F("h_Ele27WP85Num","",60,0,600);
  TH1F* h_Mu30TkMu11Num = new TH1F("h_Mu30TkMu11Num","",60,0,600);
  TH1F* h_Mu40Num = new TH1F("h_Mu40Num","",60,0,600);
  TH1F* h_IsoTkMu24Num = new TH1F("h_IsoTkMu24Num","",60,0,600);
  TH1F* h_DoubleMu33NoFiltersNoVtxNum = new TH1F("h_DoubleMu33NoFiltersNoVtxNum","",60,0,600);
  TH1F* h_Mu23Ele12Num = new TH1F("h_Mu23Ele12Num","",60,0,600);
  TH1F* h_Mu8Ele23Num = new TH1F("h_Mu8Ele23Num","",60,0,600);
  TH1F* h_PFHT900Num = new TH1F("h_PFHT900Num","",60,0,600);
  TH1F* h_AK8PFJet360TrimMass30Num = new TH1F("h_AK8PFJet360TrimMass30Num","",60,0,600);

  TH1F* h_DoubleEle33Den = new TH1F("h_DoubleEle33Den","",60,0,600);
  TH1F* h_DoubleEle33_MWDen = new TH1F("h_DoubleEle33_MWDen","",60,0,600);
  TH1F* h_Ele27WP85Den = new TH1F("h_Ele27WP85Den","",60,0,600);
  TH1F* h_Mu30TkMu11Den = new TH1F("h_Mu30TkMu11Den","",60,0,600);
  TH1F* h_Mu40Den = new TH1F("h_Mu40Den","",60,0,600);
  TH1F* h_IsoTkMu24Den = new TH1F("h_IsoTkMu24Den","",60,0,600);
  TH1F* h_DoubleMu33NoFiltersNoVtxDen = new TH1F("h_DoubleMu33NoFiltersNoVtxDen","",60,0,600);
  TH1F* h_Mu23Ele12Den = new TH1F("h_Mu23Ele12Den","",60,0,600);
  TH1F* h_Mu8Ele23Den = new TH1F("h_Mu8Ele23Den","",60,0,600);
  TH1F* h_PFHT900Den = new TH1F("h_PFHT900Den","",60,0,600);
  TH1F* h_AK8PFJet360TrimMass30Den = new TH1F("h_AK8PFJet360TrimMass30Den","",60,0,600);

  //get vector of histograms for nonprompt
  std::vector<TH1F*> npHistos_all  = getNPHistos(-1);
  std::vector<TH1F*> npHistos_ee   = getNPHistos(0);
  std::vector<TH1F*> npHistos_emu  = getNPHistos(1);
  std::vector<TH1F*> npHistos_mumu = getNPHistos(2);

  //histogram for pdf uncertainties
  TH2F* hist_pdfHT = new TH2F("hist_pdfHT","PDF Weights",500,0,5,30,0,3000);
  //histogram for pdf uncertainties
  TH2F* hist_scaleHT = new TH2F("hist_scaleHT","MC Scale Uncertainties",500,0,5,30,0,3000);

  //load eta weights in:
  std::string cmidFilename = "ChargeMisID_Data_Run2015D_Electrons_"+elID+".root";
  TFile* eWfile = new TFile(cmidFilename.c_str());
  std::vector<float> etaWeights_lpt = getEtaWeights_lpt(eWfile);
  std::vector<float> etaWeights_hpt = getEtaWeights_hpt(eWfile);

  //load pileup hist
  TFile* fpu = new TFile("../plugins/MCPileup_scaled.root");
  TH1F* hpu = (TH1F*) fpu->Get("NumTrueHist");
  

  //get fake rate according to ID
  float muPromptRate;
  if(muID=="CBTight") muPromptRate=0.9396;
  else{ std::cout<<"Didn't pick a valid muon ID. Exiting..."<<std::endl; return 0;}

  //get electron fake rate
  float elPromptRate;
  if(elID=="CBTight" || elID=="CBTightRC") elPromptRate = 0.7259;
  else if(elID=="MVATightCC" || elID=="MVATightRC") elPromptRate = 0.8941;
  else if(elID=="MVATightNew" || elID=="MVATightNewRC") elPromptRate = 0.8618;
  else if(elID=="SUSYTight" || elID=="SUSYTightRC") elPromptRate = 0.7956;
  else{std::cout<<"Didn't pick a valid electron ID. Exiting..."<<std::endl; return 0;}

  //get fake rate according to ID
  float muFakeRate;
  if(muID=="CBTight") muFakeRate=0.347;
  else{ std::cout<<"Didn't pick a valid muon ID. Exiting..."<<std::endl; return 0;}

  //get electron fake rate
  float elFakeRate;
  if(elID=="CBTight" || elID=="CBTightRC") elFakeRate = 0.43;
  else if(elID=="MVATightCC" || elID=="MVATightRC") elFakeRate = 0.288;
  else if(elID=="MVATightNew" || elID=="MVATightNewRC") elFakeRate = 0.28;
  else if(elID=="SUSYTight" || elID=="SUSYTightRC") elFakeRate = 0.20;
  else{std::cout<<"Didn't pick a valid electron ID. Exiting..."<<std::endl; return 0;}

  //doGenPlots(fsig,t,tr);
  //cd back to main directory after making gen plots
  fsig->cd();

  int nEntries = t->GetEntries();

  int nMuMu=0;
  int nElMu=0;
  int nElEl=0;
  int nGenMuMu=0;
  int nGenElMu=0;
  int nGenElEl=0;

  //floats for trigger eff
  float nMu40=0;
  float nIsoTkMu24=0;
  float nMu30TkMu11=0;
  float nMu27TkMu8=0;
  float nEle27=0;
  float nDoubleEle33=0;
  float nEle17Ele12=0;
  float nMu30Ele30=0;
  float nMu17Ele12=0;
  float nMu8Ele17=0;
  float nMu23Ele12=0;
  float nMu8Ele23=0;
  float nMu30Ele30ORMu17Ele12ORMu8Ele17=0;




  for(int ient=0; ient<nEntries; ient++){

    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntries<<" events"<<std::endl;
    
    tr->GetEntry(ient);
    
    //weight for non prompt method
    float NPweight;
    int TL;
    //make vector of good Leptons change based on data/mc   
    std::vector<TLepton*> goodLeptons;
    if(data) goodLeptons = makeLeptons(tr->allMuons, tr->allElectrons,30.0,elID,muID,bg_np);
    else goodLeptons = makeLeptons(tr->allMuons, tr->allElectrons,30.0,elID,muID,bg_np);

    //reorder the leptons by pt to remove flavor ordering
    std::sort(goodLeptons.begin(),goodLeptons.end(),sortByPt);
    bool samesign;


    //get chargeMisID rate for DY and save DY events outside of Z-peak (71-111 GeV) with weights for chargeMisID
    bool zLeps = true;
    float weight;
    if(outname.find("DYJets")!=std::string::npos || outname.find("ChargeMisID")!=std::string::npos){
      
      samesign = checkOppositeSignLeptonsForDY(goodLeptons); //returns true if find opposite sign leptons not in mu-mu channel
      
    }
    //now that we have good leptons, if it's not DY sample just check for two with same-sign charge and assign weight of 1
    else{
      samesign = checkSameSignLeptons(goodLeptons);
      weight=1;
    }


    if(!zLeps || !samesign) continue;


    //now veto on bad events from met scanners
    bool badEvent = false;
    if(data){
      badEvent = EventFilterFromFile_DoubleEG(tr->run,tr->lumi,tr->event) || EventFilterFromFile_DoubleMu(tr->run,tr->lumi,tr->event) || EventFilterFromFile_MuonEG(tr->run,tr->lumi,tr->event);
    }
    if(badEvent) {std::cout<<"filtering bad event"<<std::endl;continue;}

    //now make vector of same-sign leptons, for DY make vector containing opposite sign leptons closest to Z mass
    std::vector<TLepton*> vSSLep;
    if(outname.find("DYJets")!=std::string::npos || outname.find("ChargeMisID")!=std::string::npos){      
      vSSLep = makeOSLeptonsForDY(goodLeptons);
    }
    else vSSLep = makeSSLeptons(goodLeptons);

    //dummy check to make sure the vector got filled properly
    assert(vSSLep.size() > 1);

    //now prune the goodleptons of the ssleptons
    std::vector<TLepton*> vNonSSLep = pruneSSLep(goodLeptons,vSSLep);
    //with vector now get weight for DY Events
    if(outname.find("DYJets")!=std::string::npos || outname.find("ChargeMisID")!=std::string::npos) {
      if( vSSLep.at(0)->pt >100 || vSSLep.at(1)->pt >100){ //high pt case
	weight = getEtaWeight(etaWeights_hpt,vSSLep);
      }
      else weight = getEtaWeight(etaWeights_lpt,vSSLep); //low pt case
    }

    //now get dilepton mass
    float dilepMass = (vSSLep.at(0)->lv + vSSLep.at(1)->lv).M();

    //quarkonia veto
    //if(dilepMass<=20) continue;

    float HT=0;
    HT+=vSSLep.at(0)->pt+vSSLep.at(1)->pt;
    for(unsigned int uijet=0; uijet<tr->allAK4Jets.size();uijet++){
      HT+=tr->allAK4Jets.at(uijet)->pt;
    }

    //get channel
    int nMu=0;
    if(vSSLep.at(0)->isMu) nMu++;
    if(vSSLep.at(1)->isMu) nMu++;

    //bools for channels
    bool mumu=false;
    bool elmu=false;
    bool elel=false;



    //ok at this point only have events with same-sign leptons, now let's do simple check to see how many of each channel we have:
    if(vSSLep.at(0)->isMu && vSSLep.at(1)->isMu){ nMuMu+=1; mumu=true;}
    else if( ( vSSLep.at(0)->isEl && vSSLep.at(1)->isMu) || (vSSLep.at(0)->isMu && vSSLep.at(1)->isEl)){ nElMu+=1; elmu=true;}
    else {nElEl+=1; elel=true;}

    //now veto on dielectron events coming from Z bosons
    //if(elel && (dilepMass>71.1 && dilepMass<111.1)) continue;

    //fill muon trigger histograms
    if(mumu){
      //HLTMu40 - check efficiency of leading lepton
      h_Mu40Den->Fill(vSSLep.at(0)->pt);
      if(tr->HLT_Mu40){
	h_Mu40Num->Fill(vSSLep.at(0)->pt);
	nMu40+=1;
      }
      //HLT_IsoTkMu24 - also check for leading lepton
      h_IsoTkMu24Den->Fill(vSSLep.at(0)->pt);
      if(tr->HLT_IsoTkMu24){
	h_IsoTkMu24Num->Fill(vSSLep.at(0)->pt);
	nIsoTkMu24+=1;
      }
      //HLT_Mu30TkMu11 - check for subleading lepton
      h_Mu30TkMu11Den->Fill(vSSLep.at(1)->pt);
      if(tr->HLT_Mu30TkMu11){
	h_Mu30TkMu11Num->Fill(vSSLep.at(1)->pt);
	nMu30TkMu11+=1;
      }
      if(tr->HLT_Mu27TkMu8) nMu27TkMu8+=1;
      //HLT_DoubleMu33NoFiltersNoVtx - check fo subleading lepton
      h_DoubleMu33NoFiltersNoVtxDen->Fill(vSSLep.at(1)->pt);
      if(tr->HLT_DoubleMu33NoFiltersNoVtx) h_DoubleMu33NoFiltersNoVtxNum->Fill(vSSLep.at(1)->pt);
    }
    //now electron trigger
    if(elel){
      //HLt_Ele27 - check vs leading lepton
      h_Ele27WP85Den->Fill(vSSLep.at(0)->pt);
      if(tr->HLT_Ele27WP85){
	h_Ele27WP85Num->Fill(vSSLep.at(0)->pt);
	nEle27+=1;
      }
      //HLT_DoubleEle33 - check vs subleading lepton
      h_DoubleEle33Den->Fill(vSSLep.at(1)->pt);
      if(tr->HLT_DoubleEle33){
	h_DoubleEle33Num->Fill(vSSLep.at(1)->pt);
	nDoubleEle33+=1;
      }
      //HLT_DoubleEle33_MW - check vs subleading lepton
      h_DoubleEle33_MWDen->Fill(vSSLep.at(1)->pt);
      if(tr->HLT_DoubleEle33_MW) h_DoubleEle33_MWNum->Fill(vSSLep.at(1)->pt);
      if(tr->HLT_Ele17Ele12) nEle17Ele12+=1;
    }

    //if cross channel
    if(elmu){
      if(tr->HLT_Mu30Ele30) nMu30Ele30+=1;
      if(tr->HLT_Mu17Ele12) nMu17Ele12+=1;
      if(tr->HLT_Mu8Ele17) nMu8Ele17+=1;
      if(tr->HLT_Mu23Ele12) nMu23Ele12+=1;
      if(tr->HLT_Mu8Ele23) nMu8Ele23+=1;
      //also get OR
      if( (tr->HLT_Mu17Ele12) || (tr->HLT_Mu8Ele17) )nMu30Ele30ORMu17Ele12ORMu8Ele17+=1;
      
    }

    //require OR of triggers but make each channel consistent
    bool skip = true;
    if(mumu && tr->HLT_Mu27TkMu8) skip =false;
    if(elmu && (tr->HLT_Mu8Ele17 || tr->HLT_Mu17Ele12)) skip = false;
    if(elel && tr->HLT_Ele17Ele12) skip = false;
    if(skip) continue;

    //get trigger scale factors
    float trigSF; 
    if(data) trigSF = 1.0;
    else trigSF = getTrigSF(vSSLep);

    //now get lepton ID Scale Factors
    float lepIDSF;
    if(data) lepIDSF = 1.0;
    else lepIDSF = getLepIDSF(vSSLep);
    float lepIsoSF;
    if(data) lepIsoSF = 1.0;
    else lepIsoSF = getLepIsoSF(vSSLep);

    //now need to calculate nonPropmtWeight
    if(!bg_np) {NPweight=1.0;TL=-1;}
    else{
      if(mumu){//muon channel
	if(vSSLep.at(0)->Tight && vSSLep.at(1)->Tight) {NPweight = WeightSF_T2(muPromptRate,muFakeRate); TL = 3;}//both tight
	else if(vSSLep.at(0)->Tight || vSSLep.at(1)->Tight) {NPweight = WeightSF_T1(muPromptRate,muFakeRate); TL=2;}//one tight
	else {NPweight = WeightSF_T0(muPromptRate,muFakeRate); TL=0;}//both loose
      }
      else if(elel){//electron channel

	if(vSSLep.at(0)->Tight && vSSLep.at(1)->Tight) {NPweight = WeightSF_T2(elPromptRate,elFakeRate); TL=3;}//both tight
	else if(vSSLep.at(0)->Tight || vSSLep.at(1)->Tight) {NPweight = WeightSF_T1(elPromptRate,elFakeRate); TL=1;}//one tight
	else {NPweight = WeightSF_T0(elPromptRate,elFakeRate); TL=0;}//both loose
      }
      else{ //cross channel
	if(vSSLep.at(0)->Tight && vSSLep.at(1)->Tight) {NPweight = WeightOF_T11(elPromptRate,elFakeRate,muPromptRate,muFakeRate); TL=3;} //both tight
	else if ( (vSSLep.at(0)->isEl && vSSLep.at(0)->Tight) || (vSSLep.at(1)->isEl && vSSLep.at(1)->Tight) )  {NPweight = WeightOF_T10(elPromptRate,elFakeRate,muPromptRate,muFakeRate);TL=2;} //if electron is tight, muon must be loose or we would be on line above so just see if either lepton is a tight electron
	else if ( (vSSLep.at(0)->isMu && vSSLep.at(0)->Tight) || (vSSLep.at(1)->isMu && vSSLep.at(1)->Tight) ) {NPweight = WeightOF_T01(elPromptRate,elFakeRate,muPromptRate,muFakeRate); TL=1;}//if muon is tight, el must be loose or we would be on tight-tight line so just check for tight muon
	else {NPweight = WeightOF_T00(elPromptRate,elFakeRate,muPromptRate,muFakeRate); TL=0;}//otherwise both are loose
      }
    }
      
    //get pileup weight;
    float puweight=-1;
    if(data) puweight=1;
    else{
      puweight = getPUWeight(hpu,(int)tr->nPU);
    }

    //fill tree for post ssdl cut since that is all that we've applied so far
    tm_ssdl->FillTree(vSSLep, tr->allAK4Jets, tr->cleanedAK4Jets, tr->simpleCleanedAK4Jets, HT, tr->MET, dilepMass,nMu,weight,vNonSSLep,tr->MCWeight,NPweight,TL,trigSF,lepIDSF,lepIsoSF,puweight);
    //since we have the two same-sign leptons, now make sure neither of them reconstructs with any other tight lepton in the event to form a Z
    bool secondaryZVeto = checkSecondaryZVeto(vSSLep,tr->looseMuons,tr->looseElectrons);
    if(secondaryZVeto) continue;
    //fill tree for post secondary z veto
    tm_sZVeto->FillTree(vSSLep, tr->allAK4Jets, tr->cleanedAK4Jets, tr->simpleCleanedAK4Jets, HT, tr->MET, dilepMass,nMu,weight,vNonSSLep,tr->MCWeight,NPweight,TL,trigSF,lepIDSF,lepIsoSF,puweight);


    float st = vSSLep.at(0)->pt + vSSLep.at(1)->pt;
    for(unsigned int j=0; j < vNonSSLep.size(); j++){
      st = st + vNonSSLep.at(j)->pt;
    }
    for(unsigned int j=0; j <tr->cleanedAK4Jets.size();j++){
      st = st + tr->cleanedAK4Jets.at(j)->pt;
    }
    //skip events in dielectron which reconstruct to z
    if(elel){
      if(dilepMass < 106 && dilepMass>76) continue;
    }

    //quarkonia veto
    if(!(dilepMass>20)) continue;

    if(vSSLep.at(0)->pt<40) continue; //skip events with leading lepton pt less than 40
    
    int nconst = tr->cleanedAK4Jets.size() + vNonSSLep.size();
    if(nconst<5) continue; //nconst cutl

    float mcweight;
    if(data) mcweight = 1;
    else{
      if(tr->MCWeight>0) mcweight=1.0;
      else mcweight=-1.0;
    }

    if(!data){
      //now fill ppdf weight histogram
      std::vector<double> pdfweights = (*tr->LHEWeights);
      std::vector<int> pdfweightIDs = (*tr->LHEWeightIDs);
      for(int i=0; i< pdfweightIDs.size(); i++){
	int ID = pdfweightIDs.at(i);
	if(ID==1002 || ID==1003 || ID==1004 || ID==1005 || ID==1007 || ID==1009){
	  hist_scaleHT->Fill(pdfweights.at(i),st);
	}
	if(!(ID>2000 && i<2101)) continue;
	hist_pdfHT->Fill(pdfweights.at(i),st);
      }
    }

    //now fill nonprompt histos for later use
    if(bg_np){

	if(TL==0) npHistos_all.at(0)->Fill(st,mcweight);
	if(TL==1) npHistos_all.at(1)->Fill(st,mcweight);
	if(TL==2) npHistos_all.at(2)->Fill(st,mcweight);
	if(TL==3) npHistos_all.at(3)->Fill(st,mcweight);
      
      if(elel){
	if(TL==0) npHistos_ee.at(0)->Fill(st,mcweight);
	if(TL==1) npHistos_ee.at(1)->Fill(st,mcweight);
	if(TL==2) npHistos_ee.at(2)->Fill(st,mcweight);
	if(TL==3) npHistos_ee.at(3)->Fill(st,mcweight);
      }
      if(elmu){
	if(TL==0) npHistos_emu.at(0)->Fill(st,mcweight);
	if(TL==1) npHistos_emu.at(1)->Fill(st,mcweight);
	if(TL==2) npHistos_emu.at(2)->Fill(st,mcweight);
	if(TL==3) npHistos_emu.at(3)->Fill(st,mcweight);
      }
      if(mumu){
	if(TL==0) npHistos_mumu.at(0)->Fill(st,mcweight);
	if(TL==1) npHistos_mumu.at(1)->Fill(st,mcweight);
	if(TL==2) npHistos_mumu.at(2)->Fill(st,mcweight);
	if(TL==3) npHistos_mumu.at(3)->Fill(st,mcweight);
      }
    }//end filling of nphistos

  }//end event loop

  //write the trees
  tm_ssdl->tree->Write();
  tm_sZVeto->tree->Write();

  //write the nonprompt histograms
  for(unsigned int j=0; j<4; j++){
    fsig->WriteTObject(npHistos_all.at(j));
    fsig->WriteTObject(npHistos_ee.at(j));
    fsig->WriteTObject(npHistos_emu.at(j));
    fsig->WriteTObject(npHistos_mumu.at(j));
  }
  fsig->WriteTObject(h_DoubleEle33Num); 
  fsig->WriteTObject(h_DoubleEle33_MWNum);
  fsig->WriteTObject(h_Ele27WP85Num); 
  fsig->WriteTObject(h_Mu30TkMu11Num); 
  fsig->WriteTObject(h_Mu40Num); 
  fsig->WriteTObject(h_IsoTkMu24Num); 
  fsig->WriteTObject(h_DoubleMu33NoFiltersNoVtxNum);
  //fsig->WriteTObject(h_Mu23Ele12Num);
  //fsig->WriteTObject(h_Mu8Ele23Num);
  //fsig->WriteTObject(h_PFHT900Num);
  //fsig->WriteTObject(h_AK8PFJet360TrimMass30Num);

  fsig->WriteTObject(h_DoubleEle33Den); 
  fsig->WriteTObject(h_DoubleEle33_MWDen);
  fsig->WriteTObject(h_Ele27WP85Den);
  fsig->WriteTObject(h_Mu30TkMu11Den);
  fsig->WriteTObject(h_Mu40Den);
  fsig->WriteTObject(h_IsoTkMu24Den);
  fsig->WriteTObject(h_DoubleMu33NoFiltersNoVtxDen);
  //fsig->WriteTObject(h_Mu23Ele12Den);
  //fsig->WriteTObject(h_Mu8Ele23Den);
  //fsig->WriteTObject(h_PFHT900Den);
  //fsig->WriteTObject(h_AK8PFJet360TrimMass30Den);
  
  fsig->WriteTObject(hist_pdfHT);
  fsig->WriteTObject(hist_scaleHT);

  fsig->Write();
  fsig->Close();

  std::cout<<"Number of Gen MuMu: "<<nGenMuMu<<std::endl;
  std::cout<<"Number of MuMu: "<<nMuMu<<std::endl;
  std::cout<<"Number of ElMu: "<<nElMu<<std::endl;
  std::cout<<"Number of ElEl: "<<nElEl<<std::endl;


  std::cout<<"Efficiency of Mu40 for MuMu: "<<nMu40/(nMuMu)<<std::endl;
  std::cout<<"Efficiency of Mu40 for MuMu+ElMu: "<<nMu40/(nMuMu + nElMu)<<std::endl;
  std::cout<<"Efficiency of IsoTkmu24 for MuMu: "<<nIsoTkMu24/(nMuMu)<<std::endl;
  std::cout<<"Efficiency of IsoTkmu24 for MuMu+ElMu: "<<nIsoTkMu24/(nMuMu+nElMu)<<std::endl;

  TH1F* hNMu30TkMu11Num = new TH1F("hNMu30TkMu11Num","",1,0,10000);
  TH1F* hNMu30TkMu11Den = new TH1F("hNMu30TkMu11Den","",1,0,10000);
  for(int j =0; j<nMu30TkMu11;j++) hNMu30TkMu11Num->Fill(j);
  for(int j =0; j<nMuMu;j++) hNMu30TkMu11Den->Fill(j);
  TGraphAsymmErrors* Mu30TkMu11Graph = new TGraphAsymmErrors(hNMu30TkMu11Num,hNMu30TkMu11Den);
  std::cout<<"Efficiency of Mu30TkMu11: "<<nMu30TkMu11/nMuMu<<" +"<<Mu30TkMu11Graph->GetErrorYhigh(0)<<" -"<<Mu30TkMu11Graph->GetErrorYlow(0)<<std::endl<<"\n";
  std::cout<<"Efficiency of Ele27 for ElEl: "<<nEle27/nElEl<<std::endl;
  std::cout<<"Efficiency of Ele27 for ElEl + ElMu: "<<nEle27/(nElMu +nElEl)<<std::endl;

  TH1F* hNMu27TkMu8Num = new TH1F("hNMu27TkMu8Num","",1,0,10000);
  TH1F* hNMu27TkMu8Den = new TH1F("hNMu27TkMu8Den","",1,0,10000);
  for(int j =0; j<nMu27TkMu8;j++) hNMu27TkMu8Num->Fill(j);
  for(int j =0; j<nMuMu;j++) hNMu27TkMu8Den->Fill(j);
  TGraphAsymmErrors* Mu27TkMu8Graph = new TGraphAsymmErrors(hNMu27TkMu8Num,hNMu27TkMu8Den);
  std::cout<<"Efficiency of Mu27TkMu8: "<<nMu27TkMu8/nMuMu<<" +"<<Mu27TkMu8Graph->GetErrorYhigh(0)<<" -"<<Mu27TkMu8Graph->GetErrorYlow(0)<<std::endl<<"\n";

  TH1F* hNDoubleEle33Num = new TH1F("hNDoubleEle33Num","",1,0,10000);
  TH1F* hNDoubleEle33Den = new TH1F("hNDoubleEle33Den","",1,0,10000);
  for(int j =0; j<nDoubleEle33;j++) hNDoubleEle33Num->Fill(j);
  for(int j =0; j<nElEl;j++) hNDoubleEle33Den->Fill(j);
  TGraphAsymmErrors* DoubleEle33Graph = new TGraphAsymmErrors(hNDoubleEle33Num,hNDoubleEle33Den);
  std::cout<<"Efficiency of DoubleEle33: "<<nDoubleEle33/nElEl<<" +"<<DoubleEle33Graph->GetErrorYhigh(0)<<" -"<<DoubleEle33Graph->GetErrorYlow(0)<<std::endl<<"\n";

  TH1F* hNEle17Ele12Num = new TH1F("hNEle17Ele12Num","",1,0,10000);
  TH1F* hNEle17Ele12Den = new TH1F("hNEle17Ele12Den","",1,0,10000);
  for(int j =0; j<nEle17Ele12;j++) hNEle17Ele12Num->Fill(j);
  for(int j =0; j<nElEl;j++) hNEle17Ele12Den->Fill(j);
  TGraphAsymmErrors* Ele17Ele12Graph = new TGraphAsymmErrors(hNEle17Ele12Num,hNEle17Ele12Den);
  std::cout<<"Efficiency of Ele17Ele12: "<<nEle17Ele12/nElEl<<" +"<<Ele17Ele12Graph->GetErrorYhigh(0)<<" -"<<Ele17Ele12Graph->GetErrorYlow(0)<<std::endl<<"\n";
 
  TH1F* hNMu30Ele30Num = new TH1F("hNMu30Ele30Num","",1,0,10000);
  TH1F* hNMu30Ele30Den = new TH1F("hNMu30Ele30Den","",1,0,10000);
  for(int j =0; j<nMu30Ele30;j++) hNMu30Ele30Num->Fill(j);
  for(int j =0; j<nElMu;j++) hNMu30Ele30Den->Fill(j);
  TGraphAsymmErrors* Mu30Ele30Graph = new TGraphAsymmErrors(hNMu30Ele30Num,hNMu30Ele30Den);
  std::cout<<"Efficiency of Mu30Ele30: "<<nMu30Ele30/nElMu<<" +"<<Mu30Ele30Graph->GetErrorYhigh(0)<<" -"<<Mu30Ele30Graph->GetErrorYlow(0)<<std::endl<<"\n";

  TH1F* hNMu8Ele17Num = new TH1F("hNMu8Ele17Num","",1,0,10000);
  TH1F* hNMu8Ele17Den = new TH1F("hNMu8Ele17Den","",1,0,10000);
  for(int j =0; j<nMu8Ele17;j++) hNMu8Ele17Num->Fill(j);
  for(int j =0; j<nElMu;j++) hNMu8Ele17Den->Fill(j);
  TGraphAsymmErrors* Mu8Ele17Graph = new TGraphAsymmErrors(hNMu8Ele17Num,hNMu8Ele17Den);
  std::cout<<"Efficiency of Mu8Ele17: "<<nMu8Ele17/nElMu<<" +"<<Mu8Ele17Graph->GetErrorYhigh(0)<<" -"<<Mu8Ele17Graph->GetErrorYlow(0)<<std::endl<<"\n";

  TH1F* hNMu8Ele23Num = new TH1F("hNMu8Ele23Num","",1,0,10000);
  TH1F* hNMu8Ele23Den = new TH1F("hNMu8Ele23Den","",1,0,10000);
  for(int j =0; j<nMu8Ele23;j++) hNMu8Ele23Num->Fill(j);
  for(int j =0; j<nElMu;j++) hNMu8Ele23Den->Fill(j);
  TGraphAsymmErrors* Mu8Ele23Graph = new TGraphAsymmErrors(hNMu8Ele23Num,hNMu8Ele23Den);
  std::cout<<"Efficiency of Mu8Ele23: "<<nMu8Ele23/nElMu<<" +"<<Mu8Ele23Graph->GetErrorYhigh(0)<<" -"<<Mu8Ele23Graph->GetErrorYlow(0)<<std::endl<<"\n";

  TH1F* hNMu17Ele12Num = new TH1F("hNMu17Ele12Num","",1,0,10000);
  TH1F* hNMu17Ele12Den = new TH1F("hNMu17Ele12Den","",1,0,10000);
  for(int j =0; j<nMu17Ele12;j++) hNMu17Ele12Num->Fill(j);
  for(int j =0; j<nElMu;j++) hNMu17Ele12Den->Fill(j);
  TGraphAsymmErrors* Mu17Ele12Graph = new TGraphAsymmErrors(hNMu17Ele12Num,hNMu17Ele12Den);
  std::cout<<"Efficiency of Mu17Ele12: "<<nMu17Ele12/nElMu<<" +"<<Mu17Ele12Graph->GetErrorYhigh(0)<<" -"<<Mu17Ele12Graph->GetErrorYlow(0)<<std::endl<<"\n";

  TH1F* hNMu23Ele12Num = new TH1F("hNMu23Ele12Num","",1,0,10000);
  TH1F* hNMu23Ele12Den = new TH1F("hNMu23Ele12Den","",1,0,10000);
  for(int j =0; j<nMu23Ele12;j++) hNMu23Ele12Num->Fill(j);
  for(int j =0; j<nElMu;j++) hNMu23Ele12Den->Fill(j);
  TGraphAsymmErrors* Mu23Ele12Graph = new TGraphAsymmErrors(hNMu23Ele12Num,hNMu23Ele12Den);
  std::cout<<"Efficiency of Mu23Ele12: "<<nMu23Ele12/nElMu<<" +"<<Mu23Ele12Graph->GetErrorYhigh(0)<<" -"<<Mu23Ele12Graph->GetErrorYlow(0)<<std::endl<<"\n";

  std::cout<<"Efficiency of Mu17Ele12 OR Mu8Ele17: "<<nMu30Ele30ORMu17Ele12ORMu8Ele17/nElMu<<std::endl;
}


std::vector<TLepton*> makeLeptons(std::vector<TMuon*> muons, std::vector<TElectron*> electrons, float ptCut, std::string elID, std::string muID, bool doFakes){

  std::vector<TLepton*> Leptons;

  //fill with  muons
  for(unsigned int uimu=0; uimu<muons.size(); uimu++){
    TMuon* imu = muons.at(uimu);
    TLepton* iLep = new TLepton(imu->pt,imu->eta,imu->phi,imu->energy,imu->charge);

    if(muID=="CBTight"){
      iLep->Tight=imu->cutBasedTight();
      iLep->Loose=imu->cutBasedLoose();
    }
    else if(muID=="CBLoose"){
      iLep->Tight=imu->cutBasedLoose();
      iLep->Loose=true; //in case 'loose ID' is specified as 'tight', take any muon as loose ID
    }
    iLep->isMu = true;
    iLep->isEl = false;
    //skip for smaller than pT cut
    if(iLep->pt<ptCut) continue;
    //now save based on ID requirments if 'normal' running then require tight, else save if loose
    if(!doFakes){
      if(iLep->Tight) Leptons.push_back(iLep);
    } 
    else{ //if doing fake estimate save if loose
      if(iLep->Loose) Leptons.push_back(iLep);
    }
  }
  
  
  //fill with  electrons
  for(unsigned int uiel=0; uiel<electrons.size(); uiel++){
    TElectron* iel = electrons.at(uiel);
    TLepton* iLep = new TLepton(iel->pt,iel->eta,iel->phi,iel->energy,iel->charge);
    iLep->isMu = false;
    iLep->isEl = true;
    if(elID=="CBTight"){
      iLep->Tight=iel->cutBasedTight25nsSpring15MC();
      iLep->Loose=iel->cutBasedLoose25nsSpring15MC();
    }
    else if(elID=="CBLoose"){
      iLep->Tight=iel->cutBasedLoose25nsSpring15MC();
      iLep->Loose=true;
    }
    if(elID=="CBTightRC"){
      iLep->Tight=iel->cutBasedTight25nsSpring15MCRC();
      iLep->Loose=iel->cutBasedLoose25nsSpring15MCRC();
    }
    else if(elID=="CBLooseRC"){
      iLep->Tight=iel->cutBasedLoose25nsSpring15MCRC();
      iLep->Loose=true;
    }
    else if(elID=="MVATight"){
      iLep->Tight=iel->mvaTightIso();
      iLep->Loose=iel->mvaLooseIso();
    }
    else if(elID=="MVATightNew"){
      iLep->Tight=iel->mvaTightNew();
      iLep->Loose=iel->mvaLooseNew();
    }
    else if(elID=="MVATightNewRC"){
      iLep->Tight=iel->mvaTightNewRC();
      iLep->Loose=iel->mvaLooseNewRC();
    }
    else if(elID=="MVATightNoIso"){
      iLep->Tight=iel->mvaTight();
      iLep->Loose=iel->mvaLoose();
    }
    else if(elID=="MVALoose"){
      iLep->Tight=iel->mvaLooseIso();
      iLep->Loose=true;
    }
    else if(elID=="MVALooseNoIso"){
      iLep->Tight=iel->mvaLoose();
      iLep->Loose=true;
    }
    else if(elID=="MVATightCC"){
      iLep->Tight=iel->mvaTightCCIso();
      iLep->Loose=iel->mvaLooseCCIso();
    }
    else if(elID=="MVATightCCNoIso"){
      iLep->Tight=iel->mvaTightCC();
      iLep->Loose=iel->mvaLooseCC();
    }
    else if(elID=="MVALooseCC"){
      iLep->Tight=iel->mvaLooseCCIso();
      iLep->Loose=true;
    }
    else if(elID=="MVALooseNoIso"){
      iLep->Tight=iel->mvaLoose();
      iLep->Loose=true;
    }  
    else if(elID=="MVATightRC"){
      iLep->Tight=iel->mvaTightRCIso();
      iLep->Loose=iel->mvaLooseRCIso();
    }
    else if(elID=="MVALooseRC"){
      iLep->Tight=iel->mvaLooseRCIso();
      iLep->Loose=true;
    }
    else if(elID=="SUSYTight"){
      iLep->Tight=iel->susyTight();
      iLep->Loose=iel->susyLoose();
    }
    else if(elID=="SUSYLoose"){
	iLep->Tight=iel->susyLoose();
	iLep->Loose=true;
    }
    else if(elID=="SUSYTightRC"){
      iLep->Tight=iel->susyTightRC();
      iLep->Loose=iel->susyLooseRC();
    }      
    if(iLep->pt<ptCut) continue;
    //now save based on elID requirments if 'normal' running then require tight, else save if loose
    if(!doFakes){
      if(iLep->Tight) Leptons.push_back(iLep);
    } 
    else{ //if doing fake estimate save if loose
      if(iLep->Loose) Leptons.push_back(iLep);
    }

 
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

bool checkOppositeSignLeptonsForDY(std::vector<TLepton*> leptons){

  bool outsidePeak=false;
  bool oppositeSign=false;

  float minDiff=99999;
  float pairMass=91.1;

  TLepton* Lep1=0;
  TLepton* Lep2=0;

  for(unsigned int uilep=0; uilep<leptons.size(); uilep++){
    TLepton* lep1 = leptons.at(uilep);
    for(unsigned int ujlep=uilep+1; ujlep<leptons.size(); ujlep++){
      TLepton* lep2 = leptons.at(ujlep);
      float m = (lep1->lv + lep2->lv).M();
      float diff = fabs(91.1 - m);
      if( diff< minDiff){
	minDiff=diff;
	pairMass=m;
	Lep1=lep1;
	Lep2=lep2;
      }
    }
  }

  if(minDiff!=99999){
    if(minDiff>15) outsidePeak=true;
    if(Lep1->charge != Lep2->charge) oppositeSign=true;
  }

  if(! oppositeSign ) return false;
  else if( Lep1->isMu && Lep2->isMu) return false; //don't allow mumu events to pass
  else return true;

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

std::vector<TLepton*> makeOSLeptonsForDY(std::vector<TLepton*> leptons){

  std::vector<TLepton*> vSSLep;
  float minDiff=99999;
  float pairMass=91.1;


  for(unsigned int uilep=0; uilep<leptons.size(); uilep++){
    TLepton* lep1 = leptons.at(uilep);
    for(unsigned int ujlep=uilep+1; ujlep<leptons.size(); ujlep++){
      TLepton* lep2 = leptons.at(ujlep);
      //if both are muons don't save pair
      if(lep1->isMu && lep2->isMu) continue;
      if(lep1->charge != lep2->charge){
	vSSLep.push_back(lep1);
	vSSLep.push_back(lep2);
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

bool checkSecondaryZVeto(std::vector<TLepton*> leps, std::vector<TMuon*> muons, std::vector<TElectron*> electrons){

  bool veto=false;
  float zmass=91.1;

  for(std::vector<TLepton*>::size_type ilep=0; ilep < leps.size(); ilep++){
    // get lepton
    TLepton* lep = leps.at(ilep);

    //if muon check to find mass w/ other muons
    if(lep->isMu){
      for(std::vector<TMuon*>::size_type imu=0; imu< muons.size(); imu++){
	//skip if loose lepton has pt <= 15 GeV
	if(muons.at(imu)->pt<=15) continue;

	//skip if looking at any of the SS leptons:
	bool skip=false;
	for(std::vector<TLepton*>::size_type jlep =0; jlep<leps.size(); jlep++){
	  if(leps.at(jlep)->pt==muons.at(imu)->pt && leps.at(jlep)->phi==muons.at(imu)->phi){skip=true; break;}
	}
	if(skip) continue; 

	float diff =  getPairMass(lep,muons.at(imu)) - zmass;
	if(fabs(diff) < 15){ veto=true; break;}
      }
    }
    //else check mass w/ other electrons
    else{
      for(std::vector<TElectron*>::size_type iel=0; iel< electrons.size(); iel++){
	//skip if loose electron pt <= 15 GeV
	if(electrons.at(iel)->pt <= 15) continue;

	//skip if looking at any of the SS leptons:
	bool skip=false;
	for(std::vector<TLepton*>::size_type jlep =0; jlep<leps.size(); jlep++){
	  if(leps.at(jlep)->pt==electrons.at(iel)->pt && leps.at(jlep)->phi==electrons.at(iel)->phi){skip=true; break;}
	}
	if(skip) continue; 

	float diff =  getPairMass(lep,electrons.at(iel)) - zmass;
	if(fabs(diff) < 15){ veto=true; break;}
      }
    }
  }

  return veto;

}


std::vector<TLepton*> pruneSSLep(std::vector<TLepton*> allLeps, std::vector<TLepton*> ssLeps){

  std::vector<TLepton*> nonSSLeps=allLeps;

  unsigned int remIndex=0;
  for(std::vector<TLepton*>::size_type ilep=0; ilep<nonSSLeps.size();ilep++){
    if( (nonSSLeps.at(ilep)->pt==ssLeps.at(0)->pt && nonSSLeps.at(ilep)->eta==ssLeps.at(0)->eta && nonSSLeps.at(ilep)->phi==ssLeps.at(0)->phi) || (nonSSLeps.at(ilep)->pt==ssLeps.at(1)->pt && nonSSLeps.at(ilep)->eta==ssLeps.at(1)->eta && nonSSLeps.at(ilep)->phi==ssLeps.at(1)->phi) ){
      nonSSLeps.erase(nonSSLeps.begin()+remIndex);
    }
    remIndex++;
  }

  return nonSSLeps;
}
