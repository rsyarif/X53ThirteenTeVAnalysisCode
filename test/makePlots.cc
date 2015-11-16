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
//root -b -q -l 'makePlots.cc("MVATightRC","CBTight")' 

void DrawAndSave(Variable* Var, std::vector<Sample*> vBkg, std::vector<Sample*> vSig, Sample* dataSample, TFile* outfile, std::string elID, std::string muID, int nMu=-1, int cutIndex=0);
void DrawTriggerEff(Sample* s, TFile* outfile);
void DrawChargeMisIDGraph(TFile* outfile, std::string elID);
TH1F* getPullPlot(TH1F* hData, THStack * h, Variable* var, TH1F* h_err);
      
void makePlots(std::string elID, std::string muID){

  //make output file
  TFile* fout = new TFile("plots.root","RECREATE");

  //set TDRStyle
  setTDRStyle();
  
 
  //desired lumi:
  float lumi = 1.28; //fb^-1  
  std::vector<Variable*> vVariables = getVariableVec();

  std::vector<Sample*> vBkgSamples = getBkgSampleVec("sZVeto", lumi, elID, muID);
  std::vector<Sample*> vSigSamples = getInclusiveSigSampleVecForTable("sZVeto", lumi, elID, muID);
  Sample* dataSample = getDataSample("sZVeto",elID,muID);

  for(int j=0; j <5; j++){
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

  THStack* tStack = new THStack("tStack","");
  TLegend* leg = new TLegend(0.65,0.6,0.9,0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  //histogram for weights
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
  for(std::vector<Sample*>::size_type nt=0;nt<vBkg.size();nt++){
    //load sample
    Sample* s= vBkg.at(nt);
    //skip if not non prompt
    if( (s->name).find("NonPrompt")==std::string::npos) continue;
    //get tree
    TTree* tdummy = s->tree;
    //fill histograms
    tdummy->Project("h_t00",(var->name).c_str(),nt00cut.c_str());
    tdummy->Project("h_t01",(var->name).c_str(),nt01cut.c_str());
    tdummy->Project("h_t10",(var->name).c_str(),nt10cut.c_str());
    tdummy->Project("h_t11",(var->name).c_str(),nt11cut.c_str());
  }

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

  //*******Now fill in THStack

  for(std::vector<Sample*>::size_type uk=0; uk<vBkg.size(); uk++){

    //vBkg.at(uk)->setHist(var);
    Sample* s = vBkg.at(uk);
    TH1F* h = new TH1F("h",(var->name).c_str(), var->nbins, var->xmin, var->xmax);
    TTree* t = s->tree;
    t->Project("h",(var->name).c_str(),(cutstring.str()).c_str());
    //scale by weight - don't scale for data
    //skip non prompt if using data non prompt
    if( ( (s->name).find("NonPrompt")!=std::string::npos) && ((s->name).find("TT")==std::string::npos) ) { }
    //skip charge misID
    else if( (s->name).find("ChargeMisID")!=std::string::npos) { h_err->Add(h);}
    else  {
      h->Scale(s->weight);
      h_err->Add(h);
    }

    //aesthetics
    h->SetFillColor(s->color);
    h->GetXaxis()->SetTitle(var->Xaxis.c_str());
    h->GetYaxis()->SetTitle(var->Yaxis.c_str());
    //add to legend
    leg->AddEntry(h,(vBkg.at(uk)->name).c_str(),"f");
    assert(h);
    tStack->Add(h);
    

  }
 

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
  std::cout<<"h_err bin 5: "<<h_err->GetBinContent(5)<<" and error: "<<h_err->GetBinError(5)<<std::endl;
  //draw signal:
  for(std::vector<Sample*>::size_type i1=0;i1<vSig.size();i1++){
 
    Sample* s = vSig.at(i1);
    if(s->name.find("700")==std::string::npos) continue;
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
  TGraphErrors* gData = new TGraphErrors(hData);
  gData->SetMarkerStyle(20);
  gData->Draw("pesame");
  //sethorizontal error bars to 0
  for(unsigned int ig = 0; ig < gData->GetN(); ig++){
    gData->SetPointError(ig,0,gData->GetEY()[ig]);
  }
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
  lumitex->DrawLatex(0.65,0.96,"1.28 fb^{-1} (13 TeV)");

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
  std::string pdfname = "./plots/"+(var->name)+"_"+(vBkg[0]->cutname)+"_"+channel+"_"+cutname+"_Mu"+muID+"_El"+elID+".pdf";
  std::string pngname = "./plots/"+(var->name)+"_"+(vBkg[0]->cutname)+"_"+channel+"_"+cutname+"_Mu"+muID+"_El"+elID+".png";

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

