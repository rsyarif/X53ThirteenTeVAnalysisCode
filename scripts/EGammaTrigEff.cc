#include <iostream>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TMath.h"
#include "Math/ProbFunc.h"

using namespace std;

TGraphAsymmErrors* getGraph(TFile* f){

  TCanvas* c = (TCanvas*) f->Get("GsfElectronToTrigger/EfficiencyBinningSpecification/fit_eff_plots/probe_Ele_pt_PLOT_probe_sc_abseta_bin0");
    
  TGraphAsymmErrors* g = (TGraphAsymmErrors*)c->GetPrimitive("probe_Ele_pt_PLOT_probe_sc_abseta_bin0");

  return g;
}

Double_t erf2(Double_t* x, Double_t* par){

  //return par[0]* (ROOT::Math::normal_cdf(x[0]+par[1],par[3]) - ROOT::Math::normal_cdf(x[0]+par[1],par[3]) ) + par[2];
  return par[0]* (ROOT::Math::normal_cdf(x[0]-par[1],par[2]));

}

Double_t erf( Double_t *x, Double_t *par){   //<===========
  return par[0]*TMath::Erf(x[0]+par[1]) + par[2]; //<===========
}

void printGraph(TGraphAsymmErrors* g,std::string eta, std::string title, std::string pdfname){
  TCanvas* c = new TCanvas();

  //set up error function
  TF1 *fitfcn = new TF1("fitfcn",erf,20.0,100.0,3); //<============
  TF1 *fitfcn2 = new TF1("fitfcn2",erf2,20.0,100.0,3); //<============
  fitfcn->SetParameter(0,0.45); //<=============
  fitfcn->SetParameter(1,-33);  
  fitfcn->SetParameter(2,0.5);
  fitfcn2->SetParameter(0,0.95); //<=============
  fitfcn2->SetParameter(1,33);  
  fitfcn2->SetParameter(2,1.5);
  //fitfcn2->SetParameter(3,1.5);
  //some prettifying
  g->SetTitle(title.c_str());
  g->GetXaxis()->SetTitle("p_{T} (GeV)");
  g->GetYaxis()->SetTitle("Efficiency");
  //c->SetLogx();
  g->Draw("ap");   
  g->GetXaxis()->SetRangeUser(0,100);
  //g->Draw("ap");
  
  //fit graph
  g->Fit("fitfcn2","M");

  //write plateau efficiency:
  float eff = 100.0*(fitfcn2->GetParameter(0));//+fitfcn->GetParameter(2));
  std::stringstream texstring;
  texstring<<"#splitline{Plateau Efficiency for}{ "<<eta<<" : "<<eff<<"%}";
  TLatex* tex = new TLatex();
  tex->DrawLatex(45,.6, (texstring.str()).c_str());
  std::cout<<texstring.str()<<std::endl;
  //get turn on pT
  std::stringstream ptstring;
  ptstring<<"p_{T}^{TO}: "<<fitfcn2->GetParameter(1);
  TLatex* pttex = new TLatex();
  pttex->DrawLatex(45,0.4,(ptstring.str()).c_str());
  //get resolution
  std::stringstream sigmastring;
  sigmastring<<"#sigma_{p_{T}}: "<<fitfcn2->GetParameter(2);
  TLatex* sigmatex = new TLatex();
  sigmatex->DrawLatex(45,0.3,(sigmastring.str()).c_str());

  for(int i=0;i<g->GetN();i++){
    std::cout<<"bin: "<<i<<" eff: "<<g->GetY()[i]<<std::endl;
  }
  //save plot
  c->Print(pdfname.c_str());
  
}

void EGammaTrigEff(){

  
  TFile* fbin0 = new TFile("efficiency-data-passingHLTEle33_MVATightMiniIso_probeAbsEta0p0-0p8.root");
  TFile* fbin1 = new TFile("efficiency-data-passingHLTEle33_MVATightMiniIso_probeAbsEta0p8-1p4.root");
  TFile* fbin2 = new TFile("efficiency-data-passingHLTEle33_MVATightMiniIso_probeAbsEta1p5-2p4.root");

  TFile* fele27bin0 = new TFile("efficiency-data-passingHLTEle27_MVATightMiniIso_probeAbsEta0p0-0p8.root");
  TFile* fele27bin2 = new TFile("efficiency-data-passingHLTEle27_MVATightMiniIso_probeAbsEta1p5-2p4.root");

  TFile* fele37bin0 = new TFile("efficiency-data-passingHLTEle37_MVATightMiniIso_probeAbsEta0p0-0p8.root");
  TFile* fele37bin1 = new TFile("efficiency-data-passingHLTEle37_MVATightMiniIso_probeAbsEta0p8-1p4.root");
  TFile* fele37bin2 = new TFile("efficiency-data-passingHLTEle37_MVATightMiniIso_probeAbsEta1p5-2p4.root");


  TGraphAsymmErrors* gbin0 = getGraph(fbin0);
  TGraphAsymmErrors* gbin1 = getGraph(fbin1);
  TGraphAsymmErrors* gbin2 = getGraph(fbin2);

  TGraphAsymmErrors* gele27bin0 = getGraph(fele27bin0);
  TGraphAsymmErrors* gele27bin2 = getGraph(fele27bin2);

  TGraphAsymmErrors* gele37bin0 = getGraph(fele37bin0);
  TGraphAsymmErrors* gele37bin1 = getGraph(fele37bin1);
  TGraphAsymmErrors* gele37bin2 = getGraph(fele37bin2);

  TCanvas* can = new TCanvas();

  printGraph(gbin0,"0 < #eta < 0.8","Efficiency for passing single leg of HLT_DoubleEle33","Ele33_Efficiency-vs-pT_0p0-0p8.pdf");
  printGraph(gbin1,"0.8 < #eta < 1.442","Efficiency for passing single leg of HLT_DoubleEle33","Ele33_Efficiency-vs-pT_0p8-1p4.pdf");
  printGraph(gbin2,"1.556 < #eta < 2.4","Efficiency for passing single leg of HLT_DoubleEle33","Ele33_Efficiency-vs-pT_1p5-2p4.pdf");

  printGraph(gele27bin0,"0.0 < #eta < 0.8","Efficiency for passing single leg of HLT_Ele27","Ele27_Efficiency-vs-pT_0p0-0p8.pdf");
  printGraph(gele27bin2,"1.556 < #eta < 2.4","Efficiency for passing single leg of HLT_Ele27","Ele27_Efficiency-vs-pT_1p5-2p4.pdf");
  
  printGraph(gele37bin0,"0.0 < #eta < 0.8","Efficiency for passing single leg of HLT_Ele37","Ele37_Efficiency-vs-pT_0p0-0p8.pdf");
  printGraph(gele37bin1,"0.8 < #eta < 1.4442","Efficiency for passing single leg of HLT_Ele37","Ele37_Efficiency-vs-pT_0p8-1p4.pdf");
  printGraph(gele37bin2,"1.556 < #eta < 2.4","Efficiency for passing single leg of HLT_Ele37","Ele37_Efficiency-vs-pT_1p5-2p4.pdf");

  //gbin0->SetLineColor(kBlue);
  //gbin1->SetLineColor(kRed);
  //gbin2->SetLineColor(kBlack);
  //TCanvas* can = new TCanvas();
  //can->SetLogx();
  //gbin0->Draw("ap");
  //gbin0->Fit("fitfcn");
  //gbin1->Draw("plsame");
  //gbin2->Draw("plsame");

  //can->Print("Ele33_Efficiency-vs-pT.pdf");
  

}
