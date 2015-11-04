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
#include <math.h>
#include <map>
#include <string>
#include <sstream> 
#include "../plugins/Macros.cc"
#include "../plugins/SetTDRStyle.cc"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

void DrawAndSave(Variable* Var, std::vector<Sample*> vSamples, TFile* outfile, std::string elID, std::string muID, int nMu=-1, int cutIndex=0);
TH1F* getNPErrorHisto(std::vector<Sample*> vS, Variable* var, int nMu, std::string elID, std::string muID, int cutIndex);

int main(int argc, char* argv[]){

  if(argc!=3) {
    std::cout<<"Need to specify electron and moun IDs! Exiting..."<<std::endl;
    return 0;
  }

  TFile* fout = new TFile("ClosureTest_Plots.root","RECREATE");
  setTDRStyle();

  std::string elID = argv[1];
  std::string muID = argv[2];
  float lumi = 2.0; //estimate for end of year

  std::vector<Sample*> vSamples = getSamplesForClosureTest("sZVeto",lumi,elID, muID);

  std::vector<Variable*> vVariables = getVariablesForClosureTest();

  for(unsigned int i=0; i< vVariables.size(); i++){
    for(unsigned int j =0; j<5; j++){
      DrawAndSave(vVariables.at(i),vSamples,fout,elID,muID,-1,j);
      DrawAndSave(vVariables.at(i),vSamples,fout,elID,muID,0,j);
      DrawAndSave(vVariables.at(i),vSamples,fout,elID,muID,1,j);
      DrawAndSave(vVariables.at(i),vSamples,fout,elID,muID,2,j);
      
    }
  }


  fout->Write();
  return 0;

}

void DrawAndSave(Variable* var, std::vector<Sample*> vSamples, TFile* outfile, std::string elID, std::string muID, int nMu, int cutIndex){

  TCanvas* c1 = new TCanvas("c1","c1");

  c1->SetLogy();

  std::stringstream cutstring;
  if(nMu>=0){
    if(cutIndex==0){cutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight * (Channel=="<<nMu<<") )";}
    else if(cutIndex==1){cutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel=="<<nMu<<" && DilepMass >20 &&  ((Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==2){cutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel=="<<nMu<<" && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==3){cutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel=="<<nMu<<" && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && nConst >=5 ) )";}
    else if(cutIndex==4){cutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel=="<<nMu<<" && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && nConst >=5  && Lep1Pt > 100) )";}
  }
  else {
    if(cutIndex==0){cutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight * (Channel>=0 && ((Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==1){cutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel>=0 && DilepMass >20 && ((Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==2){cutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel>=0 && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==3){cutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel>=0 && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && nConst >=5 ) )";}
    else if(cutIndex==4){cutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * NPWeight *(Channel>=0 && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && nConst >=5 && Lep1Pt > 100 ) )";}
  }

  TLegend* leg = new TLegend(0.65,0.6,0.9,0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  //histogram for weights
  TH1F* h_err = getNPErrorHisto(vSamples,var,nMu,elID,muID, cutIndex);
  for(unsigned int i=0; i< vSamples.size();i++){
    Sample* s = vSamples.at(i);
    TH1F* h = new TH1F("h",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
    
    TTree* t = s->tree;
    
    t->Project("h",(var->name).c_str(),(cutstring.str()).c_str());
    //scale by weight
    h->Scale(s->weight);
    //aesthetics
    h->SetFillStyle(0);
    h->SetLineColor(s->color);
    h->SetLineWidth(2);
    h->SetLineStyle(s->linestyle);
    h->GetXaxis()->SetTitle(var->Xaxis.c_str());
    h->GetYaxis()->SetTitle(var->Yaxis.c_str());
    std::cout<<"Sample: "<<s->name<<" and bin 3 content: "<<h->GetBinContent(3)<<" h_Err bin 3 content: "<<h_err->GetBinContent(3)<<std::endl;
    //add to legend
    leg->AddEntry(h,(s->name).c_str(),"l");
    if(i==0) h->Draw("hist");
    else h->Draw("hist same");
  }
    
    
  c1->RedrawAxis();
  c1->Update();
  //draw errors
  h_err->SetFillStyle(3344);
  h_err->SetFillColor(1);
  h_err->Draw("SAME E2");
  
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
  cmstex->DrawLatex(0.15,0.96,"CMS Simulation Preliminary");
  lumitex->DrawLatex(0.65,0.96,"2.0 fb^{-1} (13 TeV)");

  //draw latex for channels
  TLatex* chantex = new TLatex();
  chantex->SetNDC();
  chantex->SetTextSize(0.04);
  if(nMu==-1) chantex->DrawLatex(0.25,0.8,"All Channels");
  if(nMu==0) chantex->DrawLatex(0.25,0.8,"#bf{ee}");
  if(nMu==1) chantex->DrawLatex(0.25,0.8,"#bf{e#mu}");
  if(nMu==2) chantex->DrawLatex(0.25,0.8,"#bf{#mu#mu}");

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
  std::string pdfname = "./plots/ClosureTest_"+(var->name)+"_"+channel+"_"+cutname+"_Mu"+muID+"_El"+elID+".pdf";
  std::string pngname = "./plots/ClosureTest_"+(var->name)+"_"+channel+"_"+cutname+"_Mu"+muID+"_El"+elID+".png";

  c1->Print(pdfname.c_str());
  c1->Print(pngname.c_str());
  outfile->WriteTObject(c1);
  delete c1;
  delete cmstex;
  delete lumitex;
}

TH1F* getNPErrorHisto(std::vector<Sample*> vS, Variable* var, int nMu,std::string elID, std::string muID, int cutIndex){

  TH1F* h_err = new TH1F("h_err",(var->name).c_str(), var->nbins, var->xmin, var->xmax);

  
  //now go through pain of getting non-prompt background error correct;
  TH1F* h_t00 = new TH1F("h_t00",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
  TH1F* h_t01 = new TH1F("h_t01",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
  TH1F* h_t10 = new TH1F("h_t10",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
  TH1F* h_t11 = new TH1F("h_t11",(var->name).c_str(), var->nbins, var->xmin, var->xmax);

  //get version without npweight
  std::stringstream NTcutstring;
  if(nMu>=0){
    if(cutIndex==0){NTcutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * (Channel=="<<nMu<<") )";}
    else if(cutIndex==1){NTcutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * (Channel=="<<nMu<<" && DilepMass >20 &&  ((Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==2){NTcutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * (Channel=="<<nMu<<" && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==3){NTcutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * (Channel=="<<nMu<<" && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && nConst >=5) )";}
    else if(cutIndex==4){NTcutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * (Channel=="<<nMu<<" && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && nConst >=5 && Lep1Pt > 100) )";}
  }
  else {
    if(cutIndex==0){NTcutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * (Channel>=0 && ((Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==1){NTcutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * (Channel>=0 && DilepMass >20 && ((Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==2){NTcutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * (Channel>=0 && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) )) )";}
    else if(cutIndex==3){NTcutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * (Channel>=0 && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && nconst >=5) )";}
    else if(cutIndex==4){NTcutstring<<"( trigSF * IDSF * IsoSF * ChargeMisIDWeight * MCWeight * (Channel>=0 && DilepMass >20 && nCleanAK4Jets > 1 && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && nConst >=5 && Lep1Pt >100) )";}
  }
  //now add ntl requirement
  std::string nt00cut= "("+NTcutstring.str()+" && nTL==0)";;
  std::string nt01cut= "("+NTcutstring.str()+" && nTL==1)";;
  std::string nt10cut= "("+NTcutstring.str()+" && nTL==2)";;
  std::string nt11cut= "("+NTcutstring.str()+" && nTL==3)";;

  //now fill the needed histograms
  for(std::vector<Sample*>::size_type nt=0;nt<vS.size();nt++){
    //load sample
    Sample* s= vS.at(nt);
    //skip if not non prompt
    if( (s->name).find("NonPromptTTJets")==std::string::npos) continue;
    //get tree
    TTree* tdummy = s->tree;
    //fill histograms
    tdummy->Project("h_t00",(var->name).c_str(),nt00cut.c_str());
    tdummy->Project("h_t01",(var->name).c_str(),nt01cut.c_str());
    tdummy->Project("h_t10",(var->name).c_str(),nt10cut.c_str());
    tdummy->Project("h_t11",(var->name).c_str(),nt11cut.c_str());
  

    //now scale histograms and then add them to the total error but only do non-empty ones
    if(h_t00->Integral()!=0){ 
      if(nMu==0 || nMu==2) h_t00->Scale(WeightSF_T0(elID,muID,nMu));
      else h_t00->Scale(WeightOF_T00(elID,muID));
      h_err->Add(h_t00);
    }
    if(h_t01->Integral()!=0){ 
      if(nMu==0 || nMu==2) h_t01->Scale(WeightSF_T1(elID,muID,nMu));
      else h_t01->Scale(WeightOF_T01(elID,muID));
      h_err->Add(h_t01);
    }
    if(h_t10->Integral()!=0){ 
      if(nMu==0 || nMu==2) h_t10->Scale(WeightSF_T1(elID,muID,nMu));
      else h_t10->Scale(WeightOF_T10(elID,muID));
      h_err->Add(h_t10);
    }
    if(h_t11->Integral()!=0){ 
      if(nMu==0 || nMu==2) h_t11->Scale(WeightSF_T2(elID,muID,nMu));
      else h_t11->Scale(WeightOF_T11(elID,muID));
      h_err->Add(h_t11);
    }
    h_err->Scale(s->weight);
  }//end loop over samples

  return h_err;

}
