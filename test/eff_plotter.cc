#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include <vector>
#include <string>
#include "TLegend.h"
#include "TGraph.h"
#include "TCanvas.h"
using namespace std;

void makeIsoComparisonPlot(TFile* lhf, TFile* rhf, string lhname, string rhname){

  TH1F* lh_rel = (TH1F*) lhf->Get("hRelIso_Mu");
  TH1F* lh_min = (TH1F*) lhf->Get("hMiniIso_Mu");

  TH1F* rh_rel = (TH1F*) rhf->Get("hRelIso_Mu");
  TH1F* rh_min = (TH1F*) rhf->Get("hMiniIso_Mu");

  lh_rel->SetLineColor(kBlack);
  lh_min->SetLineColor(kBlue);
  rh_rel->SetLineColor(kBlack);
  rh_min->SetLineColor(kBlue);
  rh_rel->SetLineStyle(2);
  rh_min->SetLineStyle(2);

  string lhRelname = "RelIso"+lhname;
  string lhMinname = "MiniIso"+lhname;
  string rhRelname = "RelIso"+rhname;
  string rhMinname = "MiniIso"+rhname;

  TCanvas* c = new TCanvas();
  lh_rel->SetTitle(";;");
  lh_rel->Draw();
  lh_min->Draw("same");
  rh_rel->Draw("same");
  rh_min->Draw("same");

  TLegend* leg = new TLegend(0.6,0.5,0.9,0.9);
  leg->AddEntry(lh_rel,lhRelname.c_str(),"l");
  leg->AddEntry(lh_min,lhMinname.c_str(),"l");
  leg->AddEntry(rh_rel,rhRelname.c_str(),"l");
  leg->AddEntry(rh_min,rhMinname.c_str(),"l");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw("same");

  string pdfname="IsoComparison_"+lhname+".pdf";
  c->SetLogy();

  c->Print(pdfname.c_str());
}

void makeEfficiencyComparisonPlot(vector<TFile*> lhFiles,vector<TFile*> rhFiles){

  TGraph* grhmin = new TGraph(9);
  TGraph* grhrel = new TGraph(9);
  TGraph* glhmin = new TGraph(9);
  TGraph* glhrel = new TGraph(9);


  for(int i=0; i<9; i++){
    float mass = 700+i*100;
    
    TH1F* hrhmin = (TH1F*)(rhFiles.at(i))->Get("h_MuCutFlow_MiniIso");
    TH1F* hrhrel = (TH1F*)(rhFiles.at(i))->Get("h_MuCutFlow");
    TH1F* hlhmin = (TH1F*)(lhFiles.at(i))->Get("h_MuCutFlow_MiniIso");
    TH1F* hlhrel = (TH1F*)(lhFiles.at(i))->Get("h_MuCutFlow");

    grhmin->SetPoint(i,mass, hrhmin->GetBinContent(12));
    grhrel->SetPoint(i,mass, hrhrel->GetBinContent(12));
    glhmin->SetPoint(i,mass, hlhmin->GetBinContent(12));
    glhrel->SetPoint(i,mass, hlhrel->GetBinContent(12));
    
  }

  TCanvas* c = new TCanvas();
  grhmin->SetLineColor(kBlue);
  grhrel->SetLineColor(kBlack);
  grhrel->GetYaxis()->SetRangeUser(0,1.5);
  grhrel->GetYaxis()->SetTitle("Efficiency");
  grhrel->GetXaxis()->SetTitle("M_{X53} GeV");
  glhmin->SetLineColor(kBlue);
  glhmin->SetLineStyle(2);
  glhrel->SetLineColor(kBlack);
  glhrel->SetLineStyle(2);
  glhrel->GetYaxis()->SetRangeUser(0.5,1.1);
  glhrel->SetTitle("");
  glhrel->GetYaxis()->SetTitle("Efficiency");
  glhrel->GetXaxis()->SetTitle("M_{X53} GeV");

  TLegend* leg = new TLegend(0.6,0.1,0.9,0.5);
  leg->AddEntry(glhrel,"Rel Iso < 0.2 LH","l");
  leg->AddEntry(glhmin,"Mini Iso < 0.2 LH","l");
  leg->AddEntry(grhrel,"Rel Iso < 0.2 RH","l");
  leg->AddEntry(grhmin,"Mini Iso < 0.2 RH","l");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  glhrel->Draw("al");
  glhmin->Draw("lsame");
  grhmin->Draw("lsame");
  grhrel->Draw("lsame");
  leg->Draw("same");
  c->Print("IsoEfficiency_v_Mass.pdf");
    
}

void eff_plotter(){

  gStyle->SetOptStat(kFALSE);

  vector<string> lhSamples;
  lhSamples.push_back("700_LH");
  lhSamples.push_back("800_LH");
  lhSamples.push_back("900_LH");
  lhSamples.push_back("1000_LH");
  lhSamples.push_back("1100_LH");
  lhSamples.push_back("1200_LH");
  lhSamples.push_back("1300_LH");
  lhSamples.push_back("1400_LH");
  lhSamples.push_back("1500_LH");


  vector<string> rhSamples;
  rhSamples.push_back("700_RH");
  rhSamples.push_back("800_RH");
  rhSamples.push_back("900_RH");
  rhSamples.push_back("1000_RH");
  rhSamples.push_back("1100_RH");
  rhSamples.push_back("1200_RH");
  rhSamples.push_back("1300_RH");
  rhSamples.push_back("1400_RH");
  rhSamples.push_back("1500_RH");



  std::vector<TFile*> rhFiles;
  std::vector<TFile*> lhFiles;

  for(unsigned int i=0; i<lhSamples.size();i++){

    string lhFilename ="LeptonEfficiency_Signal_MC_"+lhSamples.at(i)+".root";
    string rhFilename ="LeptonEfficiency_Signal_MC_"+rhSamples.at(i)+".root";
    lhFiles.push_back(new TFile(lhFilename.c_str()));
    rhFiles.push_back(new TFile(rhFilename.c_str()));
  }

  for(unsigned int i=0; i<lhFiles.size(); i++){
    makeIsoComparisonPlot(lhFiles.at(i),rhFiles.at(i),lhSamples.at(i),rhSamples.at(i));
  }

  makeEfficiencyComparisonPlot(lhFiles,rhFiles);

}


