#include "TFile.h"
#include "TH1.h"
#include <iostream>
#include <string>

//the point of this script is to plot the differently scaled HT histograms in case the systematic value from scale_sys.cc seems odd. Basically a cross check

void plotHists(TFile* f, std::string pdfname){

  TCanvas c1;

  gStyle->SetOptStat(kFALSE);
  TH1F* hnom  = (TH1F*) f->Get("hist_scaleHT_nom");
  TH1F* h1002 = (TH1F*) f->Get("hist_scaleHT_1002");
  TH1F* h1003 = (TH1F*) f->Get("hist_scaleHT_1003");
  TH1F* h1004 = (TH1F*) f->Get("hist_scaleHT_1004");
  TH1F* h1005 = (TH1F*) f->Get("hist_scaleHT_1005");
  TH1F* h1007 = (TH1F*) f->Get("hist_scaleHT_1007");
  TH1F* h1009 = (TH1F*) f->Get("hist_scaleHT_1009");

  h1002->SetLineColor(kRed);
  hnom->SetLineColor(kBlack);
  h1003->SetLineColor(kBlue);
  h1004->SetLineColor(kGreen);
  h1005->SetLineColor(kViolet);
  h1007->SetLineColor(kYellow);
  h1009->SetLineColor(kOrange);
  hnom->Draw("ehist");
  h1002->Draw("ehist same");
  h1003->Draw("ehist same");
  h1004->Draw("ehist same");
  h1005->Draw("ehist same");
  h1007->Draw("ehist same");
  h1009->Draw("ehist same");


  TLegend* leg = new TLegend(0.5,0.5,0.9,0.9);
  leg->AddEntry(hnom,"Nominal","l");
  leg->AddEntry(h1002,"1002","l");
  leg->AddEntry(h1003,"1003","l");
  leg->AddEntry(h1004,"1004","l");
  leg->AddEntry(h1005,"1005","l");
  leg->AddEntry(h1007,"1007","l");
  leg->AddEntry(h1009,"1009","l");

  leg->Draw("same");

  c1.Print(pdfname.c_str());


}



void HT_plotter(){


  TFile* ttz = new TFile("TTZ_MuCBTight_ElMVATightRC.root");
  TFile* ttw = new TFile("TTW_MuCBTight_ElMVATightRC.root");
  TFile* tth = new TFile("TTH_MuCBTight_ElMVATightRC.root");
  TFile* ttb = new TFile("TTbar_ext2_MuCBTight_ElMVATightRC.root");

  plotHists(ttz,"scaleSys_HT_nConstCut_TTZ.pdf");
  plotHists(ttw,"scaleSys_HT_nConstCut_TTW.pdf");
  plotHists(tth,"scaleSys_HT_nConstCut_TTH.pdf");
  plotHists(ttb,"scaleSys_HT_nConstCut_TTbar.pdf");

}
