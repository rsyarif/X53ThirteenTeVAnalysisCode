#include "TFile.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TLatex.h"

void MuonID_plotter(TString mcfile="TnP_MuonID_signal_mc_TightID_pt_abseta.root", TString datafile = "TnP_MuonID_data_all_TightID_pt_abseta_2016Full.root"){


  TFile* fmc = new TFile(mcfile);
  TFile* fdata = new TFile(datafile);

  TCanvas* cmc = (TCanvas*) fmc->Get("tpTree/TightID_pt_abseta/fit_eff_plots/abseta_pt_PLOT");
  TCanvas* cdata = (TCanvas*) fdata->Get("tpTree/TightID_pt_abseta/fit_eff_plots/abseta_pt_PLOT");

  TH2F* hmc = (TH2F*) cmc->GetPrimitive("abseta_pt_PLOT");
  TH2F* hdata = (TH2F*) cdata->GetPrimitive("abseta_pt_PLOT");

  TCanvas* c = new TCanvas();
  hmc->SetTitle("Muon Tight ID Efficiency MC;|#eta|;p_{T}");
  c->SetLogy();
  hmc->Draw("text e colz");
  TPaletteAxis *palettemc = (TPaletteAxis*)hmc->GetListOfFunctions()->FindObject("palette");
  // the following lines moe the paletter. Choose the values you need for the position.
  palettemc->SetX1NDC(0.91);
  palettemc->SetX2NDC(0.96);
  palettemc->SetY1NDC(0.1);
  palettemc->SetY2NDC(0.9);
  c->Modified();
  c->Update();
  c->Print("MuonTightID_Eff_MC.pdf");

  hdata->SetTitle("Muon Tight ID Efficiency Data;|#eta|;p_{T}");
  hdata->Draw("text e colz");
  TPaletteAxis *palettedata = (TPaletteAxis*)hdata->GetListOfFunctions()->FindObject("palette");
  // the following lines moe the paletter. Choose the values you need for the position.
  palettedata->SetX1NDC(0.91);
  palettedata->SetX2NDC(0.96);
  palettedata->SetY1NDC(0.1);
  palettedata->SetY2NDC(0.9);
  c->Modified();
  c->Update();
  c->Print("MuonTightID_Eff_Data.pdf");
  
  TCanvas* c2 = new TCanvas();
  c2->SetLogy();
  TH2F* hSF = (TH2F*) hdata->Clone("hSF");
  hSF->Divide(hmc);
  std::cout<<hSF->GetBinContent(1,1)<<std::endl;
  hSF->SetTitle("Muon Tight ID Data/MC Scale Factor;|#eta|;p_{T}");
  hSF->Draw("text e colz");
  TPaletteAxis *paletteSF = (TPaletteAxis*)hSF->GetListOfFunctions()->FindObject("palette");
  // the following lines moe the paletter. Choose the values you need for the position.
  paletteSF->SetX1NDC(0.91);
  paletteSF->SetX2NDC(0.96);
  paletteSF->SetY1NDC(0.1);
  paletteSF->SetY2NDC(0.9);
  c->Modified();
  c->Update();

  c2->Print("MuonTightID_SF.pdf");
		

}
