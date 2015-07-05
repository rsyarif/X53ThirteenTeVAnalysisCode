#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_3_0/src/AnalysisCode/ThirteenTeVX53/plugins/Sample.cc"
#include "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_3_0/src/AnalysisCode/ThirteenTeVX53/plugins/CutClass.cc"
#include "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_3_0/src/AnalysisCode/ThirteenTeVX53/interface/TreeReader.h"
#include "TGraphAsymmErrors.h"

std::vector<Variable*> getVariableVec(){

  std::vector<Variable*> vVar;

  Variable* lep1pt = new Variable("Lep1Pt",60,0,600,"Leading Lepton p_{T} (GeV)","N_{Events}");
  vVar.push_back(lep1pt);
  Variable* lep1eta = new Variable("Lep1Eta",25,-5,5,"Leading Lepton #eta","N_{Events}");
  vVar.push_back(lep1eta);
  Variable* lep1phi = new Variable("Lep1Phi",20,-3.5,3.5,"Leading Lepton #phi","N_{Events}");
  vVar.push_back(lep1phi);

  Variable* lep2pt = new Variable("Lep2Pt",60,0,600,"subLeading Lepton p_{T} (GeV)","N_{Events}");
  vVar.push_back(lep2pt);
  Variable* lep2eta = new Variable("Lep2Eta",25,-5,5,"subLeading Lepton #eta","N_{Events}");
  vVar.push_back(lep2eta);
  Variable* lep2phi = new Variable("Lep2Phi",20,-3.5,3.5,"subLeading Lepton #phi","N_{Events}");
  vVar.push_back(lep2phi);

  Variable* ak4jet1pt = new Variable("AK4Jet1Pt",60,0,600,"Leading Jet p_{T} (GeV)","N_{Events}");
  vVar.push_back(ak4jet1pt);
  Variable* ak4jet1eta = new Variable("AK4Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
  vVar.push_back(ak4jet1eta);
  Variable* ak4jet1phi = new Variable("AK4Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
  vVar.push_back(ak4jet1phi);

  Variable* ak4jet2pt = new Variable("AK4Jet2Pt",60,0,600,"subLeading Jet p_{T} (GeV)","N_{Events}");
  vVar.push_back(ak4jet2pt);
  Variable* ak4jet2eta = new Variable("AK4Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
  vVar.push_back(ak4jet2eta);
  Variable* ak4jet2phi = new Variable("AK4Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
  vVar.push_back(ak4jet2phi);


  Variable* ak4ht = new Variable("AK4HT",60,0,3000,"AK4 H_{T} (GeV)","N_{Events}");
  vVar.push_back(ak4ht);
  Variable* nak4jets = new Variable("nAK4Jets",17,0,17,"N_{AK4 Jets}","N_{Events}");
  vVar.push_back(nak4jets);

  //cleaned jet variables
  Variable* cleanak4jet1pt = new Variable("cleanAK4Jet1Pt",60,0,600,"Leading Jet p_{T} (GeV)","N_{Events}");
  vVar.push_back(cleanak4jet1pt);
  Variable* cleanak4jet1eta = new Variable("cleanAK4Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
  vVar.push_back(cleanak4jet1eta);
  Variable* cleanak4jet1phi = new Variable("cleanAK4Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
  vVar.push_back(cleanak4jet1phi);

  Variable* cleanak4jet2pt = new Variable("cleanAK4Jet2Pt",60,0,600,"subLeading Jet p_{T} (GeV)","N_{Events}");
  vVar.push_back(cleanak4jet2pt);
  Variable* cleanak4jet2eta = new Variable("cleanAK4Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
  vVar.push_back(cleanak4jet2eta);
  Variable* cleanak4jet2phi = new Variable("cleanAK4Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
  vVar.push_back(cleanak4jet2phi);


  Variable* cleanak4ht = new Variable("cleanAK4HT",60,0,3000,"cleanAK4 H_{T} (GeV)","N_{Events}");
  vVar.push_back(cleanak4ht);
  Variable* ncleanak4jets = new Variable("nCleanAK4Jets",17,0,17,"N_{cleanAK4 Jets}","N_{Events}");
  vVar.push_back(ncleanak4jets);





  Variable* met = new Variable("MET",60,0,600,"MET (GeV)", "N_{Events}");
  vVar.push_back(met);
  Variable* dilepMass = new Variable("DilepMass",60,0,600,"Dilepton Mass (GeV)", "N_{Events}");
  vVar.push_back(dilepMass);
  return vVar;

}

std::vector<Sample*> getSigSampleVec(std::string cut, float lumi){
  //make names vector
  std::vector<std::string> vSigNames;
  vSigNames.push_back("LH_X53X53_M-700"); vSigNames.push_back("RH_X53X53_M-700"); vSigNames.push_back("RH_X53X53_M-1000"); vSigNames.push_back("LH_X53X53_M-1000"); vSigNames.push_back("RH_X53X53_M-1300"); vSigNames.push_back("RH_X53X53_M-1300");
  //make x-sec vector - NEED TO FIX THESE VALUES************************************************
  std::vector<float> vXsec;
  //br is OR of either side decaying to ssdl. BR(ssdl) for one side = BR(W->enu) OR BR(W->munu) **2 where the square comes from AND requiring both to decay leptonically
  float BRssdl= 2*( pow((.1063 + .1071 + .1138),2));
  //FOR RUNNING ON INCLUSIVE DON'T APPLY BR TO SSDL!!
  //vXsec.push_back(0.442*BRssdl);vXsec.push_back(0.442*BRssdl);vXsec.push_back(0.0427*BRssdl);vXsec.push_back(0.0427*BRssdl);vXsec.push_back(0.00618*BRssdl);vXsec.push_back(0.00618*BRssdl);
  vXsec.push_back(0.442);vXsec.push_back(0.442);vXsec.push_back(0.0427);vXsec.push_back(0.0427);vXsec.push_back(0.00618);vXsec.push_back(0.00618);
  //make vector for number of events ran to get weight
  std::vector<int> vNEvts;
  vNEvts.push_back(19600);vNEvts.push_back(16200);vNEvts.push_back(16600);vNEvts.push_back(20000);vNEvts.push_back(18800);vNEvts.push_back(19000);
  

  //vector to hold weights
  std::vector<float> vWeights;
  for(std::vector<float>::size_type i=0; i<vXsec.size();i++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(i) / vNEvts.at(i) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  std::vector<Sample*> vSigSamples;

  TFile* x53x53700Rfile = new TFile("X53X53m700RH.root");
  Sample* x53x53m700R = new Sample(vSigNames.at(0),x53x53700Rfile,vWeights.at(0),vXsec.at(0),cut,kGreen,2);
  vSigSamples.push_back(x53x53m700R);
  TFile* x53x53700Lfile = new TFile("X53X53m700LH.root");
  Sample* x53x53m700L = new Sample(vSigNames.at(1),x53x53700Lfile,vWeights.at(1),vXsec.at(1),cut,kGreen,1);
  vSigSamples.push_back(x53x53m700L);

  TFile* x53x531000Rfile = new TFile("X53X53m1000RH.root");
  Sample* x53x53m1000R = new Sample(vSigNames.at(2),x53x531000Rfile,vWeights.at(2),vXsec.at(2),cut,kCyan,2);
  vSigSamples.push_back(x53x53m1000R);
  TFile* x53x531000Lfile = new TFile("X53X53m1000LH.root");
  Sample* x53x53m1000L = new Sample(vSigNames.at(3),x53x531000Lfile,vWeights.at(3),vXsec.at(3),cut,kCyan,1);
  vSigSamples.push_back(x53x53m1000L);

  TFile* x53x531300Rfile = new TFile("X53X53m1300RH.root");
  Sample* x53x53m1300R = new Sample(vSigNames.at(4),x53x531300Rfile,vWeights.at(4),vXsec.at(4),cut,kBlue,2);
  TFile* x53x531300Lfile = new TFile("X53X53m1300LH.root");
  Sample* x53x53m1300L = new Sample(vSigNames.at(5),x53x531300Lfile,vWeights.at(5),vXsec.at(5),cut,kBlue,1);

  return vSigSamples;

}


std::vector<Sample*> getBkgSampleVec(std::string cut, float lumi){  

   //setup info for list of samples, xsec and events run
  std::vector<std::string> vBkgNames;
  vBkgNames.push_back("TTbar");vBkgNames.push_back("TTZ");vBkgNames.push_back("TTW");vBkgNames.push_back("WZ");vBkgNames.push_back("WJets");vBkgNames.push_back("DYJets");vBkgNames.push_back("ZZ");
  //make vector of x-sec (in pb)
  std::vector<float> vXsec;
  vXsec.push_back(    831.76 );  vXsec.push_back(  2.232); vXsec.push_back(    1.152);  vXsec.push_back(  1.599); vXsec.push_back( 61526.7); vXsec.push_back( 6025.2);vXsec.push_back( 0.1853);
  //make vector of actual number of events run
  std::vector<int> vNEvts;
  vNEvts.push_back( 2206600); vNEvts.push_back(  249275); vNEvts.push_back(   246521); vNEvts.push_back( 237484); vNEvts.push_back(3828404); vNEvts.push_back(1366703);vNEvts.push_back(1958600);

  //now make vector to hold weights;
  std::vector<float> vWeights;
  for(std::vector<float>::size_type ui=0; ui<vXsec.size(); ui++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(ui) / vNEvts.at(ui) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  //now make samples and add to vector
  std::vector<Sample*> vSample;
  TFile* ttfile = new TFile("TTZ.root");
  Sample* ttSample = new Sample(vBkgNames.at(0),ttfile, vWeights.at(0),vXsec.at(0),cut,kRed+2);
  vSample.push_back(ttSample);
  TFile* ttZfile = new TFile("TTZ.root");
  Sample* ttZSample = new Sample(vBkgNames.at(1),ttZfile, vWeights.at(1),vXsec.at(1),cut,kRed);
  vSample.push_back(ttZSample);
  TFile* ttwfile = new TFile("TTW.root");
  Sample* ttwSample = new Sample(vBkgNames.at(2),ttwfile, vWeights.at(2),vXsec.at(2),cut,kYellow-2);
  vSample.push_back(ttwSample);
  TFile* wzfile = new TFile("WZ.root");
  Sample* wzSample = new Sample(vBkgNames.at(3),wzfile, vWeights.at(3),vXsec.at(3),cut,kBlue-3);
  vSample.push_back(wzSample);
  TFile* wjfile = new TFile("WJets.root");
  Sample* wjSample = new Sample(vBkgNames.at(4),wjfile, vWeights.at(4),vXsec.at(4),cut,kGreen+2);
  vSample.push_back(wjSample);
  TFile* dyjfile = new TFile("DYJets.root");
  Sample* dyjSample = new Sample(vBkgNames.at(5),dyjfile, vWeights.at(5),vXsec.at(5),cut,kMagenta+2);
  std::cout<<"weight for DY is: "<<vWeights.at(5)<<std::endl;
  //vSample.push_back(dyjSample);
  TFile* zzjfile = new TFile("ZZ.root");
  Sample* zzjSample = new Sample(vBkgNames.at(6),zzjfile, vWeights.at(6),vXsec.at(6),cut,kOrange+1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(zzjSample);

  return vSample;

}


std::vector<std::string> getCutString(){

  std::vector<std::string> vString;

  //Z-veto
  std::string zv = "(DilepMass < 71 || DilepMass >111)";
  vString.push_back(zv);
  //Leading Lep pT
  std::string lep1pt = "("+zv+"&& Lep1Pt > 50)" ;
  vString.push_back(lep1pt);
  //SubLeadingLep pT
  std::string lep2pt = "("+lep1pt+"&& Lep2Pt > 40)" ;
  vString.push_back(lep2pt);
  //Leading Jet pT
  std::string jet1pt = "("+lep2pt+"&& AK4Jet1Pt > 200)";
  vString.push_back(jet1pt);
  //SubLeading Jet Pt
  std::string jet2pt = "("+jet1pt+"&& AK4Jet2Pt > 150)";
  vString.push_back(jet2pt);
  //HT cut
  std::string htcut = "("+jet2pt+"&& AK4HT > 900)";
  vString.push_back(htcut);
  return vString;
}

float getNumberEvents(Sample* s, std::string cut,int nMu){

  TTree* t = s->tree;
  TH1F* hdummy = new TH1F("hdummy","hdummy",100,0,10000);
  //make cut string based on channel, should always be outside of parantheses for other cuts so a simply && should work also apply chargeMisIDWeight
  std::stringstream channel;
  if(nMu>=0)  channel<<"&& (Channel =="<<nMu<<")";
  else  channel<<"";

  std::string cutstring= "ChargeMisIDWeight * ( "+cut+channel.str()+")";

  //draw the last variable to cut on just to be safe though it shouldn't matter
  t->Project("hdummy","AK4HT",cutstring.c_str());
  float nEvts = hdummy->Integral();
  //std::cout<<"Sample: "<<s->name<<" and cut: "<<cutstring<<" unweighted events: "<<nEvts<<" weight: "<<s->weight<<std::endl;
  //now weight properly
  nEvts = nEvts * s->weight;
  delete hdummy;
  return nEvts;
};

std::string getPrettyCutString(std::string cut){

  //find the positions of && in the cut string
  std::vector<size_t> positions; // holds all the positions that sub occurs within str

  size_t pos = cut.find("&&", 0);
  while(pos != std::string::npos)
    {
      positions.push_back(pos);
      pos = cut.find("&&",pos+1);
    }

  //now take the last of them since what we want is the cut applied to the right of the last &&
  if(positions.size()==0) return "Z Veto";
  size_t last = positions.at(positions.size()-1);
  size_t length = cut.size() - last; //should give number of characters remaining in string
  length = length -3; //decrement by one to ignor final ')'
  
  std::string prettyString(cut, last+2, length);
  
  return prettyString;

};


CutClass* makeCutClass(Sample* s, std::vector<std::string> vCuts,int nMu)
{


  std::vector<float> vEvts;
  std::vector<std::string> vCutsPretty;

  for(size_t j=0; j < vCuts.size(); j++){
    
    //get number of events and save to vector - IMPORTANT TO DO THIS WITH THE FULL CUT STRING AND NOT A PRETTY VERSION
    float n = getNumberEvents(s, vCuts.at(j), nMu);
    vEvts.push_back(n);
    //now trim the cuts string to write prettily
    
    std::string cutPretty = getPrettyCutString(vCuts.at(j));
    vCutsPretty.push_back(cutPretty);
  }

  CutClass* c = new CutClass(s->name,vCutsPretty,vEvts);
  return c;

};


std::vector<CutClass*> getCutClassVector(std::vector<Sample*> vS, std::vector<std::string> vCuts, int nMu){

  std::vector<CutClass*> vCC;

  for(size_t i =0; i < vS.size(); i++){
    CutClass* c = makeCutClass(vS.at(i),vCuts,nMu);
    vCC.push_back(c);
  }

  return vCC;

};


std::vector<float> getEtaWeights(TreeReader* tr, TTree* t, TFile* outfile){

  std::vector<float> etaWeights;

  //float xbins[9] = {-2.5,-2.1,-1.5,-0.9,0,0.9,1.5,2.1,2.5};

  TH1F* h_ss = new TH1F("h_ss","",15,-3,3);
  TH1F* h_all = new TH1F("h_all","",15,-3,3);
  TH1F* h_PairMass = new TH1F("h_PairMass","",50,50,150);
  int nEntries=t->GetEntries();



  for(int ient=0; ient<nEntries; ient++){

    float mindiff=9999;
    float pairmass=-9999;
    TElectron* El1;
    TElectron* El2;

    tr->GetEntry(ient);
    //run over good electrons and find pair closest to Z Mass
    for(size_t i=0; i< tr->goodElectrons.size(); i++){
      TElectron* el1 = tr->goodElectrons.at(i);
      for(size_t j=i+1; j<tr->goodElectrons.size(); j++){
	TElectron* el2 = tr->goodElectrons.at(j);
	float mass = (el1->lv + el2->lv).M();
	
	if( fabs( 91.1 - mass) < mindiff){
	  mindiff=fabs(91.1 - mass);
	  El1=el1;
	  El2=el2;
	  pairmass=mass;	  
	}

      }
      
    }

    bool inPeak=false;
    if(mindiff<20) inPeak=true; //also implies that a pair was found since requires min diff to be reset;
    //std::cout<<"size of goodEls: "<<tr->goodElectrons.size()<<"El 1 eta: "<<El1->eta<<" El2 eta: "<<El2->eta<<" mass: "<<pairmass<<" mindiff: "<<mindiff<<std::endl;
    
    h_PairMass->Fill(pairmass);
    if(!inPeak) continue;

    if(El1->charge == El2->charge){
      h_ss->Fill(El1->eta);
      h_ss->Fill(El2->eta);
    }

    h_all->Fill(El1->eta);
    h_all->Fill(El2->eta);


  }//end event loop

  outfile->WriteTObject(h_PairMass);
  outfile->WriteTObject(h_ss);
  outfile->WriteTObject(h_all);
  //scale by 1/2
  h_all->Sumw2();
  h_ss->Sumw2();
  h_ss->Scale(0.5);


  TGraphAsymmErrors* chargeMisIDgraph = new TGraphAsymmErrors(h_ss,h_all);

  outfile->WriteTObject(chargeMisIDgraph);

  for(size_t i=0; i< chargeMisIDgraph->GetN(); i++){
    etaWeights.push_back(chargeMisIDgraph->GetY()[i]);
    std::cout<<"Weight is: "<<chargeMisIDgraph->GetY()[i]<<std::endl;
  }

  std::cout<<"size of etaWeights: "<<etaWeights.size()<<std::endl;

  return etaWeights;

}

float getEtaWeight(std::vector<float> etaWeights, std::vector<TLepton*> leptons){

  float weight1=1;
  float weight2=1;
  TLepton* Lep1=leptons.at(0);
  TLepton* Lep2=leptons.at(1);

  if(Lep1->isEl){
    if(Lep1->eta<-2.6) weight1 = 0;//no electrons greater than 2.6
    else if(Lep1->eta<-2.2) weight1 = weight1*etaWeights.at(0);
    else if(Lep1->eta<-1.8) weight1 = weight1*etaWeights.at(1);
    else if(Lep1->eta<-1.4) weight1 = weight1*etaWeights.at(2);
    else if(Lep1->eta< -1.0) weight1 = weight1*etaWeights.at(3);
    else if(Lep1->eta< -0.6) weight1 = weight1*etaWeights.at(4);
    else if(Lep1->eta< -0.2) weight1 = weight1*etaWeights.at(5);
    else if(Lep1->eta< 0.2) weight1 = weight1*etaWeights.at(6);
    else if(Lep1->eta< 0.6) weight1 = weight1*etaWeights.at(7);
    else if(Lep1->eta< 1.0) weight1 = weight1*etaWeights.at(8);
    else if(Lep1->eta< 1.4) weight1 = weight1*etaWeights.at(9);
    else if(Lep1->eta< 1.8) weight1 = weight1*etaWeights.at(10);
    else if(Lep1->eta< 2.2) weight1 = weight1*etaWeights.at(11);
    else if(Lep1->eta< 2.6) weight1 = weight1*etaWeights.at(12);
    else if(Lep1->eta< 3.0) weight1 = 0; //no electrons w/ eta greater than 2.6

  }

  if(Lep2->isEl){
    if(Lep2->eta<-2.6) weight2 = 0;//no electrons outside eta 2.6
    else if(Lep2->eta<-2.2) weight2 = weight2*etaWeights.at(0);
    else if(Lep2->eta<-1.8) weight2 = weight2*etaWeights.at(1);
    else if(Lep2->eta<-1.4) weight2 = weight2*etaWeights.at(2);
    else if(Lep2->eta< -1.0) weight2 = weight2*etaWeights.at(3);
    else if(Lep2->eta< -0.6) weight2 = weight2*etaWeights.at(4);
    else if(Lep2->eta< -0.2) weight2 = weight2*etaWeights.at(5);
    else if(Lep2->eta< 0.2) weight2 = weight2*etaWeights.at(6);
    else if(Lep2->eta< 0.6) weight2 = weight2*etaWeights.at(7);
    else if(Lep2->eta< 1.0) weight2 = weight2*etaWeights.at(8);
    else if(Lep2->eta< 1.4) weight2 = weight2*etaWeights.at(9);
    else if(Lep2->eta< 1.8) weight2 = weight2*etaWeights.at(10);
    else if(Lep2->eta< 2.2) weight2 = weight2*etaWeights.at(11);
    else if(Lep2->eta< 2.6) weight2 = weight2*etaWeights.at(12);
    else if(Lep2->eta< 3.0) weight2 = 0; //no electrons outside eta 2.6
  }


  float weight=1;
  if(Lep1->isEl && Lep2->isEl) weight = weight1 + weight2 - weight1*weight2;
  else if( (Lep1->isEl && !Lep2->isEl) || (!Lep1->isEl && Lep2->isEl) ){
    if(Lep1->isEl) weight = weight1;
    else weight = weight2;
  }


  return weight;

}

//  LocalWords:  dyjSample
