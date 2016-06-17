#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include "THStack.h"
//#include "../plugins/Sample.cc"
#include "../plugins/SetTDRStyle.cc"
//#include "../plugins/Variable.cc"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TROOT.h"
#include "../plugins/Macros.cc"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"

//eaxample usage:
//root -b -q -l 'makePlots_forPAS.cc("MVATightRC","CBTight")' 

void DrawAndSave(Variable* Var, std::vector<Sample*> vBkg, std::vector<Sample*> vSig, Sample* dataSample, TFile* outfile, std::string elID, std::string muID, int nMu=-1, int cutIndex=0);
void DrawTriggerEff(Sample* s, TFile* outfile);
void DrawChargeMisIDGraph(TFile* outfile, std::string elID);
TH1F* getPullPlot(TH1F* hData, THStack * h, Variable* var, TH1F* h_err);
      
void makePlots_forPAS(std::string elID, std::string muID){

  //make output file
  TFile* fout = new TFile("plots_forPAS.root","RECREATE");

  //set TDRStyle
  setTDRStyle();
  
 
  //desired lumi:
  float lumi = 2.32; //fb^-1  
  std::vector<Variable*> vVariables = getVariableVec();

  std::vector<Sample*> vBkgSamples = getBkgSampleVec("sZVeto", lumi, elID, muID);
  std::vector<Sample*> vSigSamples = getInclusiveSigSampleVecForTable("sZVeto", lumi, elID, muID);
  Sample* dataSample = getDataSample("sZVeto",elID,muID);

  for(int j=2; j <3; j++){
    for(std::vector<Variable*>::size_type i=0; i<vVariables.size();i++){
      //    std::vector<TH1F*> vBkgHist = getHistVector(v);
      DrawAndSave(vVariables.at(i),vBkgSamples,vSigSamples,dataSample, fout,elID,muID,-1,j);
      DrawAndSave(vVariables.at(i),vBkgSamples,vSigSamples,dataSample, fout,elID,muID,0,j);
      DrawAndSave(vVariables.at(i),vBkgSamples,vSigSamples,dataSample, fout,elID,muID,1,j);
      DrawAndSave(vVariables.at(i),vBkgSamples,vSigSamples,dataSample, fout,elID,muID,2,j);
      gROOT->Reset();
    }
  }
  //trigger plots - only for signal
  for(size_t i=0; i<vSigSamples.size();i++){
    //DrawTriggerEff(vSigSamples.at(i),fout);
  }

  //get graph of chargemisID
  DrawChargeMisIDGraph(fout,elID);
  fout->Write();
  fout->Close();

}



void DrawAndSave(Variable* var, std::vector<Sample*> vBkg, std::vector<Sample*> vSig,Sample* dataSample, TFile* outfile, std::string elID, std::string muID, int nMu, int cutIndex){

  TCanvas* c1 = new TCanvas("c1","c1");
  
  c1->SetLogy();

  //make tpads
  TPad* pad1 = new TPad("pad1","pad1",0.01,0.30,1,1);
  TPad* pad2 = new TPad("pad2","pad2",0.01,0.,1,0.30);

  pad1->SetTopMargin(0.07);
  pad1->SetLogy();
  pad2->SetTopMargin(0.0);
  pad1->SetBottomMargin(0.0);
  pad2->SetBottomMargin(0.4);
  pad1->Draw();
  pad2->Draw();
  //cd to top pad for drawing
  pad1->cd();
  std::stringstream cutstring;
  if(nMu>=0){
    if(cutIndex==0){cutstring<<"( PUWeight * trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight * (Channel=="<<nMu<<") )";}
    else if(cutIndex==1){cutstring<<"( PUWeight * trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel=="<<nMu<<"  && DilepMass >20 &&  ((Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==2){cutstring<<"( PUWeight * trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel=="<<nMu<<"  && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==3){cutstring<<"( PUWeight * trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel=="<<nMu<<"  && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && nConst >=5 ) )";}
    else if(cutIndex==4){cutstring<<"( PUWeight * trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel=="<<nMu<<"  && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && nConst >=5  && Lep1Pt > 100) )";}
  }
  else {
    if(cutIndex==0){cutstring<<"( PUWeight * trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight * (Channel>=0 && ((Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==1){cutstring<<"( PUWeight * trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel>=0 && DilepMass >20 && ((Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==2){cutstring<<"( PUWeight * trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel>=0 && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==3){cutstring<<"( PUWeight * trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel>=0 && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && nConst >=5 ) )";}
    else if(cutIndex==4){cutstring<<"( PUWeight * trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel>=0 && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && nConst >=5 && Lep1Pt > 100 ) )";}
  }

  THStack* tStack = new THStack("tStack","");
  TLegend* leg = new TLegend(0.65,0.6,0.9,0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  //stupid bins for hT
  double htbins[21] = {0,120,270,420,570,720,870,1020,1170,1320,1470,1620,1770,1920,2070,2220,2370,2520,2670,2820,2970};
  int nhtbins=20;
  TH1F* h_err;
  TH1F* h_np;
  TH1F* h_npf;
  TH1F* h_cmid;
  TH1F* h_ttz;
  TH1F* h_ttw;
  TH1F* h_tth ;
  TH1F* h_tttt ;
  TH1F* h_wz ;
  TH1F* h_zz;
  TH1F* h_wwz;
  TH1F* h_wzz ;
  TH1F* h_zzz ;
  TH1F* h_wpwp ;
  TH1F* h_bos ;
  TH1F* h_ttX ;

  if(var->name=="dummycleanAK4HT"){
    //histogram for weights
     h_err = new TH1F("h_err",(var->name).c_str(),nhtbins,htbins);
     h_np = new TH1F("h_np",(var->name).c_str(),nhtbins,htbins);
     h_npf = new TH1F("h_npf",(var->name).c_str(),nhtbins,htbins);
     h_cmid = new TH1F("h_cmid",(var->name).c_str(),nhtbins,htbins);
     h_ttz = new TH1F("h_ttz",(var->name).c_str(),nhtbins,htbins);
     h_ttw = new TH1F("h_ttz",(var->name).c_str(),nhtbins,htbins);
     h_tth = new TH1F("h_tth",(var->name).c_str(),nhtbins,htbins);
     h_tttt = new TH1F("h_tttt",(var->name).c_str(),nhtbins,htbins);
     h_wz = new TH1F("h_wz",(var->name).c_str(),nhtbins,htbins);
     h_zz = new TH1F("h_zz",(var->name).c_str(),nhtbins,htbins);
     h_wwz = new TH1F("h_wwz",(var->name).c_str(),nhtbins,htbins);
     h_wzz = new TH1F("h_wzz",(var->name).c_str(),nhtbins,htbins);
     h_zzz = new TH1F("h_zzz",(var->name).c_str(),nhtbins,htbins);
     h_wpwp = new TH1F("h_wpwp",(var->name).c_str(),nhtbins,htbins);
     h_bos = new TH1F("h_wpwp",(var->name).c_str(),nhtbins,htbins);
     h_ttX = new TH1F("h_bos",(var->name).c_str(),nhtbins,htbins);
  }
  else{
     h_err = new TH1F("h_err",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_np = new TH1F("h_np",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_npf = new TH1F("h_npf",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_cmid = new TH1F("h_cmid",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_ttz = new TH1F("h_ttz",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_ttw = new TH1F("h_ttz",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_tth = new TH1F("h_tth",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_tttt = new TH1F("h_tttt",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_wz = new TH1F("h_wz",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_zz = new TH1F("h_zz",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_wwz = new TH1F("h_wwz",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_wzz = new TH1F("h_wzz",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_zzz = new TH1F("h_zzz",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_wpwp = new TH1F("h_wpwp",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_bos = new TH1F("h_wpwp",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
     h_ttX = new TH1F("h_bos",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
    
  }

  //*******Now fill in THStack
  float lastbin = 0;
  for(std::vector<Sample*>::size_type uk=0; uk<vBkg.size(); uk++){

    //vBkg.at(uk)->setHist(var);
    Sample* s = vBkg.at(uk);
    s->setHist(var,(cutstring.str()).c_str());
    TH1F* h;
    if(var->name=="dummycleanAK4HT"){
      h = new TH1F("h",(var->name).c_str(),nhtbins, htbins);
    }
    else{
      h = new TH1F("h",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
    }
    h->Sumw2();
    TTree* t = s->tree;
    t->Project("h",(var->name).c_str(),(cutstring.str()).c_str());

    //set negative nonprompt bins to zero - less than or equal to set overflow bin to zero
    //if(s->name=="NonPrompt"){
    for(int hbin=0; hbin <= h->GetNbinsX(); hbin++){
      if(h->GetBinContent(hbin+1)<0) h->SetBinContent(hbin+1,0);
    }
      //}

    //scale by weight - don't scale for data
    //skip non prompt if using data non prompt
    if( ( (s->name).find("NonPrompt")!=std::string::npos) && ((s->name).find("TT")==std::string::npos) ) { }
    //skip charge misID
    else if( (s->name).find("ChargeMisID")!=std::string::npos) {}
    else  {
      h->Scale(s->weight);
    }
   
    //add overflow to last bin
    float ovf =  (h)->GetBinContent( (h)->GetNbinsX()+1) + (h)->GetBinContent( (h)->GetNbinsX()) ;
    (h)->SetBinContent( (h)->GetNbinsX(),ovf);
    lastbin = lastbin + ovf;
    std::cout<<"lastbin: "<<lastbin<<" and current overflow for sample "<<s->name<<" is: "<<ovf<<std::endl;

    if(s->name=="TTZ") h_ttz->Add(h);
    if(s->name=="TTW") h_ttw->Add(h);
    if(s->name=="TTH") h_tth->Add(h);
    if(s->name=="TTTT") h_tttt->Add(h);
    if(s->name=="WZ") h_wz->Add(h);
    if(s->name=="ZZ") h_zz->Add(h);
    if(s->name=="WWZ") h_wwz->Add(h);
    if(s->name=="WZZ") h_wzz->Add(h);
    if(s->name=="ZZZ") h_zzz->Add(h);
    if(s->name=="WpWp") h_wpwp->Add(h);
    if(s->name=="ChargeMisID")h_cmid->Add(h);
    //add to error hist
    h_err->Add(h);
    //aesthetics
    h->SetFillColor(s->color);
    h->GetXaxis()->SetTitle(var->Xaxis.c_str());
    h->GetYaxis()->SetTitle(var->Yaxis.c_str());
    //add to legend
    if(s->name=="TTZ") h_ttX->Add(h);
    else if(s->name=="TTW") h_ttX->Add(h);
    else if(s->name=="TTH") h_ttX->Add(h);
    else if(s->name=="TTTT") h_ttX->Add(h);
    else if(s->name=="WZ") h_bos->Add(h);
    else if(s->name=="ZZ") h_bos->Add(h);
    else if(s->name=="WWZ") h_bos->Add(h);
    else if(s->name=="WZZ") h_bos->Add(h);
    else if(s->name=="ZZZ") h_bos->Add(h);
    else if(s->name=="WpWp") h_bos->Add(h);
    else if(s->name=="NonPrompt") h_npf->Add(h);
    //else std::cout<<"sample "<<s->name<<" not added!!!"<<std::endl;
    assert(h);
    //tStack->Add(h);
    

  }

  //add to tStack
  h_bos->SetFillColor(kGreen+3);
  tStack->Add(h_bos);
  leg->AddEntry(h_bos,"Di/Tri-Boson","f");
  h_ttX->SetFillColor(kYellow-3);
  tStack->Add(h_ttX);
  leg->AddEntry(h_ttX,"TT + X","f");

  h_cmid->SetFillColor(kAzure+6);
  tStack->Add(h_cmid);
  leg->AddEntry(h_cmid,"ChargeMisID","f");

  h_npf->SetFillColor(kGray);
  tStack->Add(h_npf);
  leg->AddEntry(h_npf, "NonPrompt", "f");
  

  //make errors
  std::vector<float> errs;
  for(unsigned int ibin=1; ibin<= h_npf->GetNbinsX(); ibin++){
    //check bin contents vs error hist - just doing this here since looping over bins anyway
    std::cout<<"Bin: "<<ibin<<" err hist content: "<<h_err->GetBinContent(ibin)<<" summed bkg: "<<(h_ttX->GetBinContent(ibin)+h_bos->GetBinContent(ibin)+h_cmid->GetBinContent(ibin)+h_npf->GetBinContent(ibin))<<" NP bkg: "<<h_npf->GetBinContent(ibin)<<" CMID: "<<h_cmid->GetBinContent(ibin)<<" TTX: "<<h_ttX->GetBinContent(ibin)<<" BOSON: "<<h_bos->GetBinContent(ibin)<<std::endl;
    //nonprompt
    float etemp = pow(h_npf->GetBinError(ibin),2); //stat
    etemp = etemp + pow( 0.5*h_npf->GetBinContent(ibin),2);//sys
    //chargemisID
    etemp = etemp + pow(h_cmid->GetBinError(ibin),2);//stat
    etemp = etemp + pow(0.3*h_cmid->GetBinContent(ibin),2);//sys
    //TTZ
    etemp = etemp + pow(h_ttz->GetBinError(ibin),2);//stat
    etemp = etemp + pow(0.11*h_ttz->GetBinContent(ibin),2); //MC
    etemp = etemp + pow(0.02*h_ttz->GetBinContent(ibin),2); //JES
    etemp = etemp + pow(0.02*h_ttz->GetBinContent(ibin),2); //JER
    etemp = etemp + pow(0.027*h_ttz->GetBinContent(ibin),2); //lumi
    etemp = etemp + pow(0.06*h_ttz->GetBinContent(ibin),2); //pileup
    etemp = etemp + pow(0.03*h_ttz->GetBinContent(ibin),2); //trigger
    etemp = etemp + 2*pow(0.02*h_ttz->GetBinContent(ibin),2); //id plus iso
    //TTW
    etemp = etemp + pow(0.18*h_ttw->GetBinContent(ibin),2); //MC
    etemp = etemp + pow(0.04*h_ttw->GetBinContent(ibin),2); //JES
    etemp = etemp + pow(0.02*h_ttw->GetBinContent(ibin),2); //JER
    etemp = etemp + pow(0.027*h_ttw->GetBinContent(ibin),2); //lumi
    etemp = etemp + pow(0.06*h_ttw->GetBinContent(ibin),2); //pileup
    etemp = etemp + pow(0.03*h_ttw->GetBinContent(ibin),2); //trigger
    etemp = etemp + 2*pow(0.02*h_ttw->GetBinContent(ibin),2); //id plus iso
    //TTH
    etemp = etemp + pow(0.12*h_tth->GetBinContent(ibin),2); //MC
    etemp = etemp + pow(0.04*h_tth->GetBinContent(ibin),2); //JES
    etemp = etemp + pow(0.02*h_tth->GetBinContent(ibin),2); //JER
    etemp = etemp + pow(0.027*h_tth->GetBinContent(ibin),2); //lumi
    etemp = etemp + pow(0.06*h_tth->GetBinContent(ibin),2); //pileup
    etemp = etemp + pow(0.03*h_tth->GetBinContent(ibin),2); //trigger
    etemp = etemp + 2*pow(0.02*h_tth->GetBinContent(ibin),2); //id plus iso
    //TTTT
    etemp = etemp + pow(0.5*h_tttt->GetBinContent(ibin),2); //MC
    etemp = etemp + pow(0.03*h_tttt->GetBinContent(ibin),2); //JES
    etemp = etemp + pow(0.02*h_tttt->GetBinContent(ibin),2); //JER
    etemp = etemp + pow(0.027*h_tttt->GetBinContent(ibin),2); //lumi
    etemp = etemp + pow(0.06*h_tttt->GetBinContent(ibin),2); //pileup
    etemp = etemp + pow(0.03*h_tttt->GetBinContent(ibin),2); //trigger
    etemp = etemp + 2*pow(0.02*h_tttt->GetBinContent(ibin),2); //id plus iso
    //WZ
    etemp = etemp + pow(0.12*h_wz->GetBinContent(ibin),2); //MC
    etemp = etemp + pow(0.08*h_wz->GetBinContent(ibin),2); //JES
    etemp = etemp + pow(0.02*h_wz->GetBinContent(ibin),2); //JER
    etemp = etemp + pow(0.027*h_wz->GetBinContent(ibin),2); //lumi
    etemp = etemp + pow(0.06*h_wz->GetBinContent(ibin),2); //pileup
    etemp = etemp + pow(0.03*h_wz->GetBinContent(ibin),2); //trigger
    etemp = etemp + 2*pow(0.02*h_wz->GetBinContent(ibin),2); //id plus iso
    //ZZ
    etemp = etemp + pow(0.12*h_zz->GetBinContent(ibin),2); //MC
    etemp = etemp + pow(0.05*h_zz->GetBinContent(ibin),2); //JES
    etemp = etemp + pow(0.02*h_zz->GetBinContent(ibin),2); //JER
    etemp = etemp + pow(0.027*h_zz->GetBinContent(ibin),2); //lumi
    etemp = etemp + pow(0.06*h_zz->GetBinContent(ibin),2); //pileup
    etemp = etemp + pow(0.03*h_zz->GetBinContent(ibin),2); //trigger
    etemp = etemp + 2*pow(0.02*h_zz->GetBinContent(ibin),2); //id plus iso
    //WPWP
    etemp = etemp + pow(0.50*h_wpwp->GetBinContent(ibin),2); //MC
    etemp = etemp + pow(0.05*h_wpwp->GetBinContent(ibin),2); //JES
    etemp = etemp + pow(0.02*h_wpwp->GetBinContent(ibin),2); //JER
    etemp = etemp + pow(0.027*h_wpwp->GetBinContent(ibin),2); //lumi
    etemp = etemp + pow(0.06*h_wpwp->GetBinContent(ibin),2); //pileup
    etemp = etemp + pow(0.03*h_wpwp->GetBinContent(ibin),2); //trigger
    etemp = etemp + 2*pow(0.02*h_wpwp->GetBinContent(ibin),2); //id plus iso
    //WWZ
    etemp = etemp + pow(0.50*h_wwz->GetBinContent(ibin),2); //MC
    etemp = etemp + pow(0.07*h_wwz->GetBinContent(ibin),2); //JES
    etemp = etemp + pow(0.02*h_wwz->GetBinContent(ibin),2); //JER
    etemp = etemp + pow(0.027*h_wwz->GetBinContent(ibin),2); //lumi
    etemp = etemp + pow(0.06*h_wwz->GetBinContent(ibin),2); //pileup
    etemp = etemp + pow(0.03*h_wwz->GetBinContent(ibin),2); //trigger
    etemp = etemp + 2*pow(0.02*h_wwz->GetBinContent(ibin),2); //id plus iso
    //WZZ
    etemp = etemp + pow(0.50*h_wzz->GetBinContent(ibin),2); //MC
    etemp = etemp + pow(0.06*h_wzz->GetBinContent(ibin),2); //JES
    etemp = etemp + pow(0.02*h_wzz->GetBinContent(ibin),2); //JER
    etemp = etemp + pow(0.027*h_wzz->GetBinContent(ibin),2); //lumi
    etemp = etemp + pow(0.06*h_wzz->GetBinContent(ibin),2); //pileup
    etemp = etemp + pow(0.03*h_wzz->GetBinContent(ibin),2); //trigger
    etemp = etemp + 2*pow(0.02*h_wzz->GetBinContent(ibin),2); //id plus iso
    //ZZZ
    etemp = etemp + pow(0.50*h_zzz->GetBinContent(ibin),2); //MC
    etemp = etemp + pow(0.06*h_zzz->GetBinContent(ibin),2); //JES
    etemp = etemp + pow(0.02*h_zzz->GetBinContent(ibin),2); //JER
    etemp = etemp + pow(0.027*h_zzz->GetBinContent(ibin),2); //lumi
    etemp = etemp + pow(0.06*h_zzz->GetBinContent(ibin),2); //pileup
    etemp = etemp + pow(0.03*h_zzz->GetBinContent(ibin),2); //trigger
    etemp = etemp + 2*pow(0.02*h_zzz->GetBinContent(ibin),2); //id plus iso


    etemp = pow(etemp,0.5);
    h_err->SetBinError(ibin,etemp);
    errs.push_back(etemp);
  }

  //now set err bin to have overflow content
  //h_err->SetBinContent(h_err->GetNbinsX(),lastbin);
  
  tStack->Draw("HIST");
  tStack->GetXaxis()->SetTitle(var->Xaxis.c_str());
  tStack->GetXaxis()->CenterTitle();
  //tStack->GetXaxis()->SetTitleSize(0.015);
  tStack->GetYaxis()->SetTitle(var->Yaxis.c_str());
  tStack->GetYaxis()->CenterTitle();
  //tStack->GetYaxis()->SetRangeUser(0.008,100000);
  tStack->SetMaximum(15 * tStack->GetMaximum());
  tStack->SetMinimum(0.008);
  tStack->Draw("HIST");
  //tStack->GetYaxis()->SetTitleSize(0.015);
  c1->RedrawAxis();
  c1->Update();
  //draw errors
  h_err->SetFillStyle(3344);
  h_err->SetFillColor(1);
  h_err->Draw("SAME E2");
  if(var->name=="cleanAK4HT"){
    for(unsigned int jb=1; jb<=h_err->GetNbinsX(); jb++){
      float totbkg = h_npf->GetBinContent(jb) + h_cmid->GetBinContent(jb) + h_ttw->GetBinContent(jb) + h_ttz->GetBinContent(jb) + h_wz->GetBinContent(jb) + h_wpwp->GetBinContent(jb) + h_zz->GetBinContent(jb)+h_wwz->GetBinContent(jb) + h_tth->GetBinContent(jb) + h_tttt->GetBinContent(jb) + h_wzz->GetBinContent(jb) + h_zzz->GetBinContent(jb);
    float stacktot = ( (TH1F*)(tStack->GetStack()->Last()))->GetBinContent(jb);
    std::cout<<"bin: "<<jb<<"stack: "<<stacktot<<" bkg tot: "<<totbkg<<" total in h_err: "<<h_err->GetBinContent(jb)<<" np tot: "<<h_npf->GetBinContent(jb)<<" cmid tot: "<<h_cmid->GetBinContent(jb)<<" error: "<<h_err->GetBinError(jb)<<std::endl;
      //std::cout<<"bin: "<<jb<<" error on fancy way: "<<h_np->GetBinError(jb)<<" error on standard way: "<<h_npf->GetBinError(jb)<<" fancy content: "<<h_np->GetBinContent(jb)<<" reg content: "<<h_npf->GetBinContent(jb)<<std::endl;
    }
  }
  //draw signal:
  for(std::vector<Sample*>::size_type i1=0;i1<vSig.size();i1++){
    
    Sample* s = vSig.at(i1);
    if(s->name.find("700")==std::string::npos) continue;
    TH1F* h = new TH1F("h",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
    TTree* t = s->tree;

    t->Project("h",(var->name).c_str(),(cutstring.str()).c_str());
    float ovf =  (h)->GetBinContent( (h)->GetNbinsX()+1) + (h)->GetBinContent( (h)->GetNbinsX()) ;
    (h)->SetBinContent( (h)->GetNbinsX(),ovf);
    //scale by weight
    h->Scale(s->weight);
    //aesthetics
    h->SetFillStyle(0);
    h->SetLineColor(s->color);
    h->SetLineWidth(2);
    h->SetLineStyle(s->linestyle);
    h->GetXaxis()->SetTitle(var->Xaxis.c_str());
    h->GetYaxis()->SetTitle(var->Yaxis.c_str());
    //add to legend
    leg->AddEntry(h,(vSig.at(i1)->name).c_str(),"l");
    //assert(h);
    //tStack->Add(h);

    h->Draw("hist same");

  }

  //Draw data
  TH1F* hData = new TH1F("hData",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
  TTree* tData = dataSample->tree;
  tData->Project("hData",(var->name).c_str(),(cutstring.str()).c_str());
  float ovf_d =  (hData)->GetBinContent( (hData)->GetNbinsX()+1) + (hData)->GetBinContent( (hData)->GetNbinsX()) ;
  (hData)->SetBinContent( (hData)->GetNbinsX(),ovf_d);
  TGraphAsymmErrors* gData = new TGraphAsymmErrors(hData);
  gData->SetMarkerStyle(20);
  for(unsigned int ig = 0; ig < gData->GetN(); ig++){
    int N = gData->GetY()[ig];
    if(N==0){
      //double L =  (N==0) ? 0  : (ROOT::Math::gamma_quantile((1.0-0.6827)/2,N,1.));
      //double U =  ROOT::Math::gamma_quantile_c((1.0-0.6827)/2,N+1,1) ;
      //gData->SetPointEYlow(ig, N-L);
      //gData->SetPointEYhigh(ig, U-N);
    }
    else{
      //gData->SetPointError(ig,0,gData->GetEY()[ig]);
    }
    gData->SetPointEXlow(ig,0);
    gData->SetPointEXhigh(ig,0);
  }
  gData->Draw("pesame");

  leg->AddEntry(gData,"Data","p");

  //latex
  TLatex* cmstex = new TLatex();
  cmstex->SetNDC();
  cmstex->SetTextSize(0.04);
  TLatex* lumitex = new TLatex();
  lumitex->SetNDC();
  lumitex->SetTextSize(0.04);

  //draw legend, cms and lumi
  leg->Draw("same");

  //draw latex
  cmstex->DrawLatex(0.15,0.96,"CMS Preliminary");
  lumitex->DrawLatex(0.65,0.96,"2.3 fb^{-1} (13 TeV)");

  //draw latex for channels
  TLatex* chantex = new TLatex();
  chantex->SetNDC();
  chantex->SetTextSize(0.04);
  if(nMu==-1) chantex->DrawLatex(0.25,0.8,"All Channels");
  if(nMu==0) chantex->DrawLatex(0.25,0.8,"#bf{ee}");
  if(nMu==1) chantex->DrawLatex(0.25,0.8,"#bf{e#mu}");
  if(nMu==2) chantex->DrawLatex(0.25,0.8,"#bf{#mu#mu}");


  //now draw pull plot
  pad2->cd();
  TH1F* hpull = getPullPlot(hData, tStack, var, h_err);
  hpull->Draw("HIST");
  //This changes the range of the X axis                                                                                                                                                                     
  TAxis* axis = hpull->GetXaxis();
  //ChangeAxisRange(title[i], hpull->GetXaxis());
  hpull->GetXaxis()->SetLabelSize(0.15);
  float xmin = hpull->GetBinLowEdge(axis->GetFirst());
  float xmax = hpull->GetBinLowEdge(axis->GetLast()+1);
  TLine* baseline = new TLine(xmin,0,xmax,0);
  TLine* plus2line = new TLine(xmin,2,xmax,2);
  TLine* minus2line = new TLine(xmin,-2,xmax,-2);
  baseline->SetLineColor(kBlack);
  baseline->SetLineStyle(2);
  plus2line->SetLineStyle(2);
  minus2line->SetLineStyle(2);
  baseline->Draw();
  plus2line->Draw();
  minus2line->Draw();
  //pad->RedrawAxis();                                                                                                                                                                                       
  c1->Update();

  //rename plots by channel
  std::string channel;
  if(nMu==-1) channel="All";
  if(nMu==0) channel="ElEl";
  if(nMu==1) channel="ElMu";
  if(nMu==2) channel="MuMu";
  std::string cutname;
  if(cutIndex==0) cutname =  "sZVeto";
  if(cutIndex==1) cutname =  "QuarkoniaAndElElZVeto";
  if(cutIndex==2) cutname =  "TwoJets";
  if(cutIndex==3) cutname =  "nConstituents";
  if(cutIndex==4) cutname =  "LeadingLepPt100";
  std::string pdfname = "./plots_forPAS/"+(var->name)+"_"+(vBkg[0]->cutname)+"_"+channel+"_"+cutname+"_Mu"+muID+"_El"+elID+".pdf";
  std::string pngname = "./plots_forPAS/"+(var->name)+"_"+(vBkg[0]->cutname)+"_"+channel+"_"+cutname+"_Mu"+muID+"_El"+elID+".png";

  c1->Print(pdfname.c_str());
  c1->Print(pngname.c_str());
  outfile->WriteTObject(c1);
  delete c1;
  delete cmstex;
  delete lumitex;
}

void DrawTriggerEff(Sample* s, TFile* outfile){

  std::vector<std::string> vTrigNames;
  vTrigNames.push_back("DoubleEle33");
  vTrigNames.push_back("DoubleEle33_MW");
  vTrigNames.push_back("Ele27WP85");
  vTrigNames.push_back("Mu30TkMu11");
  vTrigNames.push_back("Mu40");
  vTrigNames.push_back("IsoTkMu24");
  vTrigNames.push_back("DoubleMu33NoFiltersNoVtx");
  //vTrigNames.push_back("Mu33Ele12");
  //vTrigNames.push_back("Mu8Ele23");
  //vTrigNames.push_back("PFHT900");
  //vTrigNames.push_back("AK8PFJet360TrimMass30");

  for(size_t j=0; j<vTrigNames.size();j++){    
    std::string hDenName="h_"+vTrigNames.at(j)+"Den";
    std::string hNumName="h_"+vTrigNames.at(j)+"Num";
    TH1F* hDen = (TH1F*) (s->file)->Get(hDenName.c_str());
    TH1F* hNum = (TH1F*) (s->file)->Get(hNumName.c_str());
    TGraphAsymmErrors * g = new TGraphAsymmErrors(hNum,hDen);
    TCanvas* c2 = new TCanvas();

    std::string title = "Efficiency of HLT_"+vTrigNames.at(j);
    g->SetTitle(title.c_str());
    g->GetYaxis()->SetTitle("Eff");
    g->GetXaxis()->SetTitle("p_{T} GeV");

    g->Draw("apl");

    std::string pdfname = "plots/TrigEff_"+s->name+"HLT_"+vTrigNames.at(j)+".pdf";
    std::string pngname = "plots/TrigEff_"+s->name+"HLT_"+vTrigNames.at(j)+".png";
    c2->Print(pdfname.c_str());
    c2->Print(pngname.c_str());

    outfile->WriteTObject(c2);
    delete c2;
    delete g;
    
  }

}


void DrawChargeMisIDGraph(TFile* outfile,std::string elID){
  std::string filename = "ChargeMisID_Data_Run2015D_Electrons_"+elID+".root";
  TFile* f = new TFile(filename.c_str());
  //TGraphAsymmErrors* chargeMisIDGraph = (TGraphAsymmErrors*) f->Get("divide_etaNumHist_by_etaDenHist");
  TH1F* chargeMisIDGraph = (TH1F*) f->Get("etaNumHist");
  TH1F* h2 = (TH1F*) f->Get("etaDenHist");
  chargeMisIDGraph->Divide(h2);

  chargeMisIDGraph->SetTitle("Electron Charge MisID Rate");

  chargeMisIDGraph->GetYaxis()->SetTitle("Charge MisID Rate");
  chargeMisIDGraph->GetXaxis()->SetTitle("Electron #eta");

  TCanvas c3;

  chargeMisIDGraph->Draw("ep");
  chargeMisIDGraph->GetYaxis()->SetLabelSize(0.02);
  c3.Print("plots/ElectronChargeMisID.pdf");
  c3.Print("plots/ElectronChargeMisID.png");

  //outfile->Append(chargeMisIDGraph);
  //outfile->Write();
}


TH1F*
getPullPlot(TH1F* hData, THStack * h, Variable* var, TH1F* h_err){//Actually a residue plot for now

  string title = hData->GetTitle();
  title += " (Pull)";
  TH1F* hpull = (TH1F*)hData->Clone(title.c_str());
  
  int size = hData->GetNbinsX();
  //hpull->SetTitle(";;Residual");//#sigma(Data-MC)");
  hpull->SetTitle(";;#frac{(obs-bkg)}{#sigma}");
  //clint's edit to change title size
  hpull->GetYaxis()->SetTitleSize(0.12);
  hpull->GetYaxis()->SetTitleOffset(0.4);
  hpull->GetXaxis()->SetTitle((var->Xaxis).c_str());
  //hpull->GetXaxis()->SetTitle("L_{T}^{0e3#mu} #equiv #Sigma p_{T}^{#font[12]{l}} (GeV)");
  hpull->GetXaxis()->SetTitleSize(0.17);
  hpull->GetXaxis()->SetTitleOffset(1.02);
  hpull->GetXaxis()->CenterTitle();
  hpull->GetYaxis()->CenterTitle();
  //hpull->SetTitle(title.c_str());
  TH1F* hsum = (TH1F*) h->GetStack()->Last();
  for(int i=1; i<=size; ++i){

    float error;
    float diff;
    //diff = (hsum->GetBinContent(i) > 0) ? diff/hData->GetBinError(i) : 0.;
    //if(debug_) cout<<"diff for bin "<<i<<" is "<<diff<<endl;
    //cout<<"diff for bin "<<i<<" is "<<diff<<endl;
    if(hData->GetBinContent(i)>=1){
      int N = hData->GetBinContent(i);
      double L =  (N==0) ? 0  : (ROOT::Math::gamma_quantile((1.0-0.6827)/2,N,1.));
      double U = ROOT::Math::gamma_quantile_c((1.0-0.6827)/2.0,N+1,1);
      if(hData->GetBinContent(i)>h_err->GetBinContent(i)){
	error = pow( pow(h_err->GetBinError(i),2) + pow(N-L,2),0.5);
	diff = (hData->GetBinContent(i) - hsum->GetBinContent(i))/error;
      }
      else{
	error = pow( pow(h_err->GetBinError(i),2) + pow(U-N,2),0.5);
	diff = (hData->GetBinContent(i) - hsum->GetBinContent(i))/error;
      }
      hpull->SetBinContent(i,diff);
      hpull->SetBinError(i,0);//Cory: include mc error
    }
    else{
      double U = ROOT::Math::gamma_quantile_c((1.0-0.6827)/2.0,1,1);
      error=pow( pow(h_err->GetBinError(i),2) + pow(U,2),0.5);
      diff=((-1.0)*hsum->GetBinContent(i))/error;
      hpull->SetBinContent(i,diff);
      hpull->SetBinError(i,0);//Cory: include mc error
    }
  }
  hpull->SetAxisRange( -3, 3, "Y");
  //hpull->GetYaxis()->SetRangeUser(-2.5,2.5);
  hpull->GetYaxis()->SetNdivisions(203);
  hpull->GetYaxis()->SetTickLength(0.02);
  hpull->GetYaxis()->SetLabelSize(0.13);
  hpull->GetXaxis()->SetLabelSize(0.35);
  hpull->SetLineColor(kBlack);
  hpull->SetFillColor(kRed);
  return hpull;
}

