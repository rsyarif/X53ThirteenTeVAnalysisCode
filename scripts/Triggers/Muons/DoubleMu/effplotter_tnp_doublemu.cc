#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFile.h"
/*TH1F* getRatio(TGraphAsymmErrors* g1, TGraphAsymmErrors* g2){

  float* xbins[10]= {30,35,40,50,60,100,150,200,300,500}

  TH1F* h = new TH1F("h","",g1->GetN(),xbins);
  

}
*/

TGraphAsymmErrors* getSFGraph(TGraphAsymmErrors* num, TGraphAsymmErrors* den){
  TGraphAsymmErrors* g = (TGraphAsymmErrors*)num->Clone();
  std::cout<<"number data points: "<<num->GetN()<<" number mc points: "<<den->GetN()<<std::endl;
  for(int i=0; i< g->GetN(); i++){
    std::cout<<" data eff: "<<num->GetY()[i]<<" mc eff: "<<den->GetY()[i];
    float ratio = num->GetY()[i]/den->GetY()[i];
    std::cout<<" sf: "<<ratio<<std::endl;
    g->SetPoint(i,num->GetX()[i],ratio);
    float err = pow( ratio * ratio * num->GetEYlow()[i]*num->GetEYlow()[i] + ratio*ratio*den->GetEYlow()[i]*den->GetEYlow()[i],0.5);
    g->SetPointEYhigh(i,err);
    g->SetPointEYlow(i,err);
  }
  return g;
  
}

void effplotter_tnp_doublemu(TString phi="WP"){

  gStyle->SetOptStat(kFALSE);
  

  //load in tnp
  TFile* fTnP = new TFile("TnP_MuonTrig_AbsEta_fitMuonTrig_Mu17_2016Full_"+phi+".root");
  TCanvas* c_eta1 = (TCanvas*) fTnP->Get("tpTree/Mu17Pass_eta/fit_eff_plots/pt_PLOT_abseta_bin0");
  TCanvas* c_eta2 = (TCanvas*) fTnP->Get("tpTree/Mu17Pass_eta/fit_eff_plots/pt_PLOT_abseta_bin1");
  TCanvas* c_eta3 = (TCanvas*) fTnP->Get("tpTree/Mu17Pass_eta/fit_eff_plots/pt_PLOT_abseta_bin2");
  TCanvas* c_eta4 = (TCanvas*) fTnP->Get("tpTree/Mu17Pass_eta/fit_eff_plots/pt_PLOT_abseta_bin3");
  TCanvas* c_eta5 = (TCanvas*) fTnP->Get("tpTree/Mu17Pass_eta/fit_eff_plots/pt_PLOT_abseta_bin4");

  TFile* fMCTnP = new TFile("TnP_MuonTrig_AbsEta_fitMuonTrig_Mu17_Moriond17MC_"+phi+".root");                                              
  TCanvas* cmc_eta1 = (TCanvas*) fMCTnP->Get("tpTree/Mu17Pass/fit_eff_plots/pt_PLOT_abseta_bin0");
  TCanvas* cmc_eta2 = (TCanvas*) fMCTnP->Get("tpTree/Mu17Pass/fit_eff_plots/pt_PLOT_abseta_bin1");
  TCanvas* cmc_eta3 = (TCanvas*) fMCTnP->Get("tpTree/Mu17Pass/fit_eff_plots/pt_PLOT_abseta_bin2");
  TCanvas* cmc_eta4 = (TCanvas*) fMCTnP->Get("tpTree/Mu17Pass/fit_eff_plots/pt_PLOT_abseta_bin3");
  TCanvas* cmc_eta5 = (TCanvas*) fMCTnP->Get("tpTree/Mu17Pass/fit_eff_plots/pt_PLOT_abseta_bin4");


  TGraphAsymmErrors* TnPGraph_eta1 = (TGraphAsymmErrors*) c_eta1->GetPrimitive("hxy_fit_eff");
  TGraphAsymmErrors* TnPGraph_eta2 = (TGraphAsymmErrors*) c_eta2->GetPrimitive("hxy_fit_eff");
  TGraphAsymmErrors* TnPGraph_eta3 = (TGraphAsymmErrors*) c_eta3->GetPrimitive("hxy_fit_eff");
  TGraphAsymmErrors* TnPGraph_eta4 = (TGraphAsymmErrors*) c_eta4->GetPrimitive("hxy_fit_eff");
  TGraphAsymmErrors* TnPGraph_eta5 = (TGraphAsymmErrors*) c_eta5->GetPrimitive("hxy_fit_eff");

  TGraphAsymmErrors* TnPGraphMC_eta1 = (TGraphAsymmErrors*) cmc_eta1->GetPrimitive("hxy_fit_eff");
  TGraphAsymmErrors* TnPGraphMC_eta2 = (TGraphAsymmErrors*) cmc_eta2->GetPrimitive("hxy_fit_eff");
  TGraphAsymmErrors* TnPGraphMC_eta3 = (TGraphAsymmErrors*) cmc_eta3->GetPrimitive("hxy_fit_eff");
  TGraphAsymmErrors* TnPGraphMC_eta4 = (TGraphAsymmErrors*) cmc_eta4->GetPrimitive("hxy_fit_eff");
  TGraphAsymmErrors* TnPGraphMC_eta5 = (TGraphAsymmErrors*) cmc_eta5->GetPrimitive("hxy_fit_eff");


  TCanvas* c_new = new TCanvas();  
  c_new->SetLogx();
  TLegend* leg = new TLegend(0.1,0.1,0.5,0.5);
  TnPGraph_eta1->Draw("ap");
  TnPGraph_eta1->GetYaxis()->SetRangeUser(0,1.1);
  TnPGraphMC_eta1->SetMarkerColor(kBlue);
  TnPGraphMC_eta1->SetLineColor(kBlue);
  TnPGraphMC_eta1->Draw("plsame");
  TGraphAsymmErrors* SFGraph_eta1 = getSFGraph(TnPGraph_eta1,TnPGraphMC_eta1);
  SFGraph_eta1->SetLineColor(kGreen+2);
  SFGraph_eta1->SetMarkerColor(kGreen+2);
  SFGraph_eta1->Draw("plsame");
  leg->AddEntry(TnPGraph_eta1, "Data2016B-D ReReco","pl");
  leg->AddEntry(TnPGraphMC_eta1,"DY Moriond17 MC","pl");
  leg->AddEntry(SFGraph_eta1,"Scale Factor","pl");
  leg->Draw("same");
  for(int i=0; i<TnPGraph_eta1->GetN();i++){
    std::cout<<"SF for 0<eta<0.4 pt bin "<<i<<" is: "<<TnPGraph_eta1->GetY()[i]/TnPGraphMC_eta1->GetY()[i]<<std::endl;
  }
  c_new->Print("Mu17_EffTnP_Eta0p0-0p4_"+phi+".pdf");

  TnPGraph_eta2->Draw("ap");
  TnPGraph_eta2->GetYaxis()->SetRangeUser(0,1.1);
  TnPGraphMC_eta2->SetMarkerColor(kBlue);
  TnPGraphMC_eta2->SetLineColor(kBlue);
  TnPGraphMC_eta2->Draw("plsame");
  TGraphAsymmErrors* SFGraph_eta2 = getSFGraph(TnPGraph_eta2,TnPGraphMC_eta2);
  SFGraph_eta2->SetLineColor(kGreen+2);
  SFGraph_eta2->SetMarkerColor(kGreen+2);
  SFGraph_eta2->Draw("plsame");
  leg->Draw("same");
  for(int i=0; i<TnPGraph_eta2->GetN();i++){
    std::cout<<"SF for 0.4<eta<0.9 pt bin "<<i<<" is: "<<TnPGraph_eta2->GetY()[i]/TnPGraphMC_eta2->GetY()[i]<<std::endl;
  }
  c_new->Print("Mu17_EffTnP_Eta0p4-0p9_"+phi+".pdf");

  TnPGraph_eta3->Draw("ap");
  TnPGraph_eta3->GetYaxis()->SetRangeUser(0,1.1);
  TnPGraphMC_eta3->SetMarkerColor(kBlue);
  TnPGraphMC_eta3->SetLineColor(kBlue);
  TnPGraphMC_eta3->Draw("plsame");
  TGraphAsymmErrors* SFGraph_eta3 = getSFGraph(TnPGraph_eta3,TnPGraphMC_eta3);
  SFGraph_eta3->SetLineColor(kGreen+2);
  SFGraph_eta3->SetMarkerColor(kGreen+2);
  SFGraph_eta3->Draw("plsame");
  leg->Draw("same");
  for(int i=0; i<TnPGraph_eta3->GetN();i++){
    std::cout<<"SF for 0.9<eta<01.2 pt bin "<<i<<" is: "<<TnPGraph_eta3->GetY()[i]/TnPGraphMC_eta3->GetY()[i]<<std::endl;
  }
  c_new->Print("Mu17_EffTnP_Eta0p9-1p2_"+phi+".pdf");

  TnPGraph_eta4->Draw("ap");
  TnPGraph_eta4->GetYaxis()->SetRangeUser(0,1.1);
  TnPGraphMC_eta4->SetMarkerColor(kBlue);
  TnPGraphMC_eta4->SetLineColor(kBlue);
  TnPGraphMC_eta4->Draw("plsame");
 TGraphAsymmErrors* SFGraph_eta4 = getSFGraph(TnPGraph_eta4,TnPGraphMC_eta4);
  SFGraph_eta4->SetLineColor(kGreen+2);
  SFGraph_eta4->SetMarkerColor(kGreen+2);
  SFGraph_eta4->Draw("plsame");
  leg->Draw("same");
  for(int i=0; i<TnPGraph_eta4->GetN();i++){
    std::cout<<"SF for 1.2<eta<2.1 pt bin "<<i<<" is: "<<TnPGraph_eta4->GetY()[i]/TnPGraphMC_eta4->GetY()[i]<<std::endl;
  }
  c_new->Print("Mu17_EffTnP_Eta1p2-2p1_"+phi+".pdf");

  TnPGraph_eta5->Draw("ap");
  TnPGraph_eta5->GetYaxis()->SetRangeUser(0,1.1);
  TnPGraphMC_eta5->SetMarkerColor(kBlue);
  TnPGraphMC_eta5->SetLineColor(kBlue);
  TnPGraphMC_eta5->Draw("plsame");
  TGraphAsymmErrors* SFGraph_eta5 = getSFGraph(TnPGraph_eta5,TnPGraphMC_eta5);
  SFGraph_eta5->SetLineColor(kGreen+2);
  SFGraph_eta5->SetMarkerColor(kGreen+2);
  SFGraph_eta5->Draw("plsame");
  leg->Draw("same");
  for(int i=0; i<TnPGraph_eta5->GetN();i++){
    std::cout<<"SF for 2.1<eta<2.4 pt bin "<<i<<" is: "<<TnPGraph_eta5->GetY()[i]/TnPGraphMC_eta5->GetY()[i]<<std::endl;
  }
  c_new->Print("Mu17_EffTnP_Eta2p1-2p4_"+phi+".pdf");




}
