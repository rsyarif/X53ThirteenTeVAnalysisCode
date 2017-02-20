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

  TGraph* grhminT = new TGraph(9);
  TGraph* grhmin = new TGraph(9);
  TGraph* grhrel = new TGraph(9);
  TGraph* glhminT = new TGraph(9);
  TGraph* glhmin = new TGraph(9);
  TGraph* glhrel = new TGraph(9);


  for(int i=0; i<9; i++){
    float mass = 700+i*100;
    
    TH1F* hrhmin = (TH1F*)(rhFiles.at(i))->Get("h_MuCutFlow_MiniIso");
    TH1F* hrhrel = (TH1F*)(rhFiles.at(i))->Get("h_MuCutFlow");
    TH1F* hlhmin = (TH1F*)(lhFiles.at(i))->Get("h_MuCutFlow_MiniIso");
    TH1F* hlhrel = (TH1F*)(lhFiles.at(i))->Get("h_MuCutFlow");

    //get relative isolation with medium cut
    /* TH1F* hrhrel_num = (TH1F*)(rhFiles.at(i))->Get("hPtNum_Mu");
    TH1F* hrhrel_den = (TH1F*)(rhFiles.at(i))->Get("hPtDen_Mu");
    float nPassRel_rh = hrhrel_num->Integral(4,61);
    float nTotRel_rh = hrhrel_den->Integral(4,61);
    float rhEff_rel = nPassRel_rh / nTotRel_rh;

    TH1F* hlhrel_num = (TH1F*)(lhFiles.at(i))->Get("hPtNum_Mu");
    TH1F* hlhrel_den = (TH1F*)(lhFiles.at(i))->Get("hPtDen_Mu");
    float nPassRel_lh = hlhrel_num->Integral(4,61);
    float nTotRel_lh = hlhrel_den->Integral(4,61);
    float lhEff_m = nPassRel_lh / nTotRel_lh;
    */
    //get minisolation with medium cut
    TH1F* hrhmed_num = (TH1F*)(rhFiles.at(i))->Get("hPtNumMedIso_Mu");
    TH1F* hrhmed_den = (TH1F*)(rhFiles.at(i))->Get("hPtDen_Mu");
    float nPassMed_rh = hrhmed_num->Integral(4,61);
    float nTotMed_rh = hrhmed_den->Integral(4,61);
    float rhEff_m = nPassMed_rh / nTotMed_rh;

    TH1F* hlhmed_num = (TH1F*)(lhFiles.at(i))->Get("hPtNumMedIso_Mu");
    TH1F* hlhmed_den = (TH1F*)(lhFiles.at(i))->Get("hPtDen_Mu");
    float nPassMed_lh = hlhmed_num->Integral(4,61);
    float nTotMed_lh = hlhmed_den->Integral(4,61);
    float lhEff_m = nPassMed_lh / nTotMed_lh;

    //get minisolation with tightium cut
    TH1F* hrhtight_num = (TH1F*)(rhFiles.at(i))->Get("hPtNumTightIso_Mu");
    TH1F* hrhtight_den = (TH1F*)(rhFiles.at(i))->Get("hPtDen_Mu");
    float nPass_rh = hrhtight_num->Integral(4,61);
    float nTot_rh = hrhtight_den->Integral(4,61);
    float rhEff = nPass_rh / nTot_rh;

    TH1F* hlhtight_num = (TH1F*)(lhFiles.at(i))->Get("hPtNumTightIso_Mu");
    TH1F* hlhtight_den = (TH1F*)(lhFiles.at(i))->Get("hPtDen_Mu");
    float nPass_lh = hlhtight_num->Integral(4,61);
    float nTot_lh = hlhtight_den->Integral(4,61);
    float lhEff = nPass_lh / nTot_lh;


    grhminT->SetPoint(i,mass,rhEff);
    grhmin->SetPoint(i,mass, rhEff_m);
    grhrel->SetPoint(i,mass, hrhrel->GetBinContent(12));
    glhminT->SetPoint(i,mass,lhEff);
    glhmin->SetPoint(i,mass, lhEff_m);
    glhrel->SetPoint(i,mass, hlhrel->GetBinContent(12));
    
  }

  TCanvas* c = new TCanvas();
  grhmin->SetLineColor(kBlue);
  grhrel->SetLineColor(kBlack);
  grhminT->SetLineColor(kRed);
  glhmin->GetYaxis()->SetRangeUser(0.0,1.1);
  grhmin->GetYaxis()->SetTitle("Efficiency");
  grhmin->GetXaxis()->SetTitle("M_{X53} GeV");
  glhmin->SetLineColor(kBlue);
  glhminT->SetLineColor(kRed);
  glhmin->SetLineStyle(2);
  glhminT->SetLineStyle(2);
  glhrel->SetLineColor(kBlack);
  glhrel->SetLineStyle(2);
  glhrel->GetYaxis()->SetRangeUser(0.0,1.1);
  glhmin->SetTitle("");
  glhmin->GetYaxis()->SetTitle("Efficiency");
  glhmin->GetXaxis()->SetTitle("M_{X53} GeV");

  TLegend* leg = new TLegend(0.3,0.1,0.9,0.5);
  leg->SetNColumns(2);
  leg->AddEntry(glhrel,"Rel Iso < 0.2 LH","l");
  leg->AddEntry(glhmin,"Mini Iso < 0.2 LH","l");
  leg->AddEntry(glhminT,"Mini Iso < 0.1 LH","l");
  leg->AddEntry(grhrel,"Rel Iso < 0.2 RH","l");
  leg->AddEntry(grhmin,"Mini Iso < 0.2 RH","l");
  leg->AddEntry(grhminT,"Mini Iso < 0.1 RH","l");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  glhmin->Draw("al");
  glhrel->Draw("lsame");
  grhmin->Draw("lsame");
  grhrel->Draw("lsame");
  grhminT->Draw("lsame");
  glhminT->Draw("lsame");
  leg->Draw("same");
  c->Print("IsoEfficiency_v_Mass.pdf");
    
}

void MuonIsoCheck(){

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

    string lhFilename ="../../test/LeptonEfficiency_Signal_MC_"+lhSamples.at(i)+".root";
    string rhFilename ="../../test/LeptonEfficiency_Signal_MC_"+rhSamples.at(i)+".root";
    lhFiles.push_back(new TFile(lhFilename.c_str()));
    rhFiles.push_back(new TFile(rhFilename.c_str()));
  }

  for(unsigned int i=0; i<lhFiles.size(); i++){
    makeIsoComparisonPlot(lhFiles.at(i),rhFiles.at(i),lhSamples.at(i),rhSamples.at(i));
  }

  makeEfficiencyComparisonPlot(lhFiles,rhFiles);
 

}


