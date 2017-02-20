#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TH1.h"
#include <vector>

void ElectronStudy(){
  gStyle->SetOptStat(kFALSE);
  std::vector<TString> masses;
  masses.push_back("700");
  masses.push_back("800");
  masses.push_back("900");
  masses.push_back("1000");
  masses.push_back("1100");
  masses.push_back("1200");
  masses.push_back("1300");
  masses.push_back("1400");
  masses.push_back("1500");


  std::vector<TString> chirals;
  chirals.push_back("LH");
  chirals.push_back("RH");

  //vectors to save overall efficiencies
  std::vector<float>  mvaEffs;
  std::vector<float>  mva80XEffs;
  std::vector<float>  mvaJulieEffs;
  std::vector<float>  mvaJulieNewEffs;
  std::vector<float>  mvaCustomEffs;


  for(unsigned int i=0; i < chirals.size();i++){
    TString chi = chirals.at(i);
    for(unsigned int j=0; j< masses.size(); j++){
      TString mass = masses.at(j);
      TFile* f = new TFile("../../test/LeptonEfficiency_Signal_MC_"+mass+"_"+chi+".root");
      TTree* t = (TTree*) f->Get("ElectronVariables");
      std::vector<float>* mvas=0;
      std::vector<float>* mvas80X=0;
      std::vector<float>* pts=0;
      std::vector<float>* etas=0;
      std::vector<float>* phis=0;
      std::vector<float>* miniIsos=0;      
      t->SetBranchAddress("mva",&mvas);
      t->SetBranchAddress("mva80X",&mvas80X);
      t->SetBranchAddress("pT",&pts);
      t->SetBranchAddress("eta",&etas);
      t->SetBranchAddress("phi",&phis);
      t->SetBranchAddress("miniIso",&miniIsos);
      TH2F* h_mvaComp = new TH2F("h_mvaComp","MVA Comparison",40,-1,1,40,-1,1);
      TH1F* h_num_mva = new TH1F("h_num_mva","74X MVA Eff",100,0,500);
      TH1F* h_num_mva80X = new TH1F("h_num_80X","80X Nominal WP MVA Eff",100,0,500);
      TH1F* h_num_mvaJulie = new TH1F("h_num_mvaJulie","80X Julie WP MVA Eff",100,0,500);
      TH1F* h_num_mvaJulieNew = new TH1F("h_num_mvaJulieNew","80X JulieNew WP MVA Eff",100,0,500);
      TH1F* h_num_mvaCustom = new TH1F("h_num_mvaCustom","80X Custom WP MVA Eff",100,0,500);

      TH1F* h_den_mva = new TH1F("h_den_mva","74X MVA Eff",100,0,500);
      TH1F* h_den_mva80X = new TH1F("h_den_80X","80X Nominal WP MVA Eff",100,0,500);
      TH1F* h_den_mvaJulie = new TH1F("h_den_mvaJulie","80X Julie WP MVA Eff",100,0,500);
      TH1F* h_den_mvaJulieNew = new TH1F("h_den_mvaJulieNew","80X JulieNew WP MVA Eff",100,0,500);
      TH1F* h_den_mvaCustom = new TH1F("h_den_mvaCustom","80X Custom WP MVA Eff",100,0,500);

      h_mvaComp->SetTitle("MVA Comparison; 80X MVA Value; 74X MVA Value");
      for(unsigned int entry=0; entry< t->GetEntries(); entry++){
	t->GetEntry(entry);
	for(unsigned int k=0;k<(*mvas).size();k++){
	  float pt = (*pts)[k];
	  float eta = (*etas)[k];
	  float miniIso = (*miniIsos)[k];
	  float mva = (*mvas)[k];
	  float mva80X = (*mvas80X)[k];
	  //skip leptons with pT less than 30
	  if(pt<30) continue;
	  h_mvaComp->Fill(mva80X,mva);
	  //fill denominators
	  h_den_mva->Fill(pt);
	  h_den_mva80X->Fill(pt);
	  h_den_mvaJulie->Fill(pt);
	  h_den_mvaJulieNew->Fill(pt);
	  h_den_mvaCustom->Fill(pt);
	  if(fabs(eta) < 0.8){
	    if(mva>0.967803) h_num_mva->Fill(pt);
	    if(mva80X>0.941) h_num_mva80X->Fill(pt);
	    if(mva80X>0.674) h_num_mvaJulie->Fill(pt);
	    if(mva80X>0.788) h_num_mvaJulieNew->Fill(pt);
	    if(mva80X>0.674) h_num_mvaCustom->Fill(pt);
	    
	  }
	  else if(fabs(eta) < 1.4442){
	    if(mva>0.929117) h_num_mva->Fill(pt);
	    if(mva80X>0.899) h_num_mva80X->Fill(pt);
	    if(mva80X>0.795) h_num_mvaJulie->Fill(pt);
	    if(mva80X>0.744) h_num_mvaJulieNew->Fill(pt);
	    if(mva80X>0.744) h_num_mvaCustom->Fill(pt);
	  }
	  else{
	    if(mva>0.726311) h_num_mva->Fill(pt);
	    if(mva80X>0.758) h_num_mva80X->Fill(pt);
	    if(mva80X>0.17) h_num_mvaJulie->Fill(pt);
	    if(mva80X>0.508) h_num_mvaJulieNew->Fill(pt);
	    if(mva80X>0.17) h_num_mvaCustom->Fill(pt);
	  }

	}//end loop on electrons
      }//end loop on entries
      TCanvas* c = new TCanvas();
      h_mvaComp->Draw("colz");
      c->SetLogz();
      c->Print("MVAComparison_"+chi+"_M"+mass+".pdf");

      //make TGraph for efficiency and draw
      TLegend* leg = new TLegend(0.4,0.1,0.9,0.5);
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);
      TGraphAsymmErrors* g_mva = new TGraphAsymmErrors(h_num_mva,h_den_mva);
      g_mva->SetTitle("Electron ID Efficiency vs. p_{T};p_{T} (GeV);Efficiency");
      g_mva->Draw("apl");
      leg->AddEntry(g_mva,"74X MVA","l");
      TGraphAsymmErrors* g_mva80X = new TGraphAsymmErrors(h_num_mva80X,h_den_mva80X);
      g_mva80X->SetLineColor(kBlue);
      g_mva80X->Draw("pl same");
      leg->AddEntry(g_mva80X,"80X MVA Nominal WP","l");

      TGraphAsymmErrors* g_mvaJulie = new TGraphAsymmErrors(h_num_mvaJulie,h_den_mvaJulie);
      g_mvaJulie->SetLineColor(kRed);
      //g_mvaJulie->Draw("pl same");
      //leg->AddEntry(g_mvaJulie,"80X MVA Julie WP","l");

      TGraphAsymmErrors* g_mvaJulieNew = new TGraphAsymmErrors(h_num_mvaJulieNew,h_den_mvaJulieNew);
      g_mvaJulieNew->SetLineColor(kGreen);
      //g_mvaJulieNew->Draw("pl same");
      //leg->AddEntry(g_mvaJulieNew,"80X MVA JulieNew WP","l");

      TGraphAsymmErrors* g_mvaCustom = new TGraphAsymmErrors(h_num_mvaCustom,h_den_mvaCustom);
      g_mvaCustom->SetLineColor(kGreen);
      g_mvaCustom->Draw("pl same");
      leg->AddEntry(g_mvaCustom,"80X MVA Custom WP","l");

      leg->Draw("same");
      c->Print("Eff_vPt_"+chi+"_M"+mass+".pdf");
      //now save  overall efficiencies
      mvaEffs.push_back( h_num_mva->GetEntries() / h_den_mva->GetEntries());
      mva80XEffs.push_back( h_num_mva80X->GetEntries() / h_den_mva80X->GetEntries());
      mvaJulieEffs.push_back( h_num_mvaJulie->GetEntries() / h_den_mvaJulie->GetEntries());
      mvaJulieNewEffs.push_back( h_num_mvaJulieNew->GetEntries() / h_den_mvaJulieNew->GetEntries());
      mvaCustomEffs.push_back( h_num_mvaCustom->GetEntries() / h_den_mvaCustom->GetEntries());
    }//end loop on masses
  }//end loop on chiralities

  //now plot eff vs mass
  TGraph* g_mva_rh = new TGraph(9);
  for(unsigned int i =9; i< mvaEffs.size();i++){
    int j = i-9;
    float mass = (j+7)*100.;
    g_mva_rh->SetPoint(j,mass,mvaEffs.at(i));
  }
  TGraph* g_mva80X_rh = new TGraph(9);
  for(unsigned int i =9; i< mva80XEffs.size();i++){
    int j = i-9;
    float mass = (j+7)*100.;
    g_mva80X_rh->SetPoint(j,mass,mva80XEffs.at(i));
  }
  TGraph* g_mvaJulie_rh = new TGraph(9);
  for(unsigned int i =9; i< mvaJulieEffs.size();i++){
    int j = i-9;
    float mass = (j+7)*100.;
    g_mvaJulie_rh->SetPoint(j,mass,mvaJulieEffs.at(i));
  }

  TGraph* g_mvaJulieNew_rh = new TGraph(9);
  for(unsigned int i =9; i< mvaJulieNewEffs.size();i++){
    int j = i-9;
    float mass = (j+7)*100.;
    g_mvaJulieNew_rh->SetPoint(j,mass,mvaJulieNewEffs.at(i));
  }

  TGraph* g_mvaCustom_rh = new TGraph(9);
  for(unsigned int i =9; i< mvaCustomEffs.size();i++){
    int j = i-9;
    float mass = (j+7)*100.;
    g_mvaCustom_rh->SetPoint(j,mass,mvaCustomEffs.at(i));
  }

  TGraph* g_mva_lh = new TGraph(9);
  for(unsigned int i =0; i< 9;i++){
    float mass = (i+7)*100.;
    g_mva_lh->SetPoint(i,mass,mvaEffs.at(i));
  }
  TGraph* g_mva80X_lh = new TGraph(9);
  for(unsigned int i =0; i< 9;i++){
    float mass = (i+7)*100.;
    g_mva80X_lh->SetPoint(i,mass,mva80XEffs.at(i));
  }
  TGraph* g_mvaJulie_lh = new TGraph(9);
  for(unsigned int i =0; i< 9;i++){
    float mass = (i+7)*100.;
    g_mvaJulie_lh->SetPoint(i,mass,mvaJulieEffs.at(i));
  }

  TGraph* g_mvaJulieNew_lh = new TGraph(9);
  for(unsigned int i =0; i< 9;i++){
    float mass = (i+7)*100.;
    g_mvaJulieNew_lh->SetPoint(i,mass,mvaJulieNewEffs.at(i));
  }

  TGraph* g_mvaCustom_lh = new TGraph(9);
  for(unsigned int i =0; i< 9;i++){
    float mass = (i+7)*100.;
    g_mvaCustom_lh->SetPoint(i,mass,mvaCustomEffs.at(i));
  }

  TCanvas* c = new TCanvas();
  TLegend* leg = new TLegend(0.5,0.1,0.9,0.4);
  g_mva_lh->SetLineColor(kBlack);
  g_mva_lh->SetLineStyle(2);
  g_mva_lh->Draw("apl");
  g_mva_lh->GetYaxis()->SetRangeUser(0,1.1);
  g_mva_lh->SetTitle("Efficiency vs Mass;X_{5/3} Mass (GeV);Efficiency");
  g_mva80X_lh->SetLineColor(kBlue);
  g_mva80X_lh->SetLineStyle(2);
  g_mva80X_lh->Draw("plsame");
  //g_mvaJulie_lh->SetLineColor(kBlue);
  //g_mvaJulie_lh->SetLineStyle(4);
  //g_mvaJulie_lh->Draw("plsame");
  g_mvaCustom_lh->SetLineColor(kGreen);
  g_mvaCustom_lh->SetLineStyle(2);
  g_mvaCustom_lh->Draw("plsame");


  g_mva_rh->SetLineColor(kBlack);
  g_mva_rh->Draw("plsame");
  g_mva80X_rh->SetLineColor(kBlue);
  g_mva80X_rh->Draw("plsame");
  g_mvaCustom_rh->SetLineColor(kGreen);
  g_mvaCustom_rh->Draw("plsame");


  leg->AddEntry(g_mva_lh,"LH - 74X MVA","l");
  leg->AddEntry(g_mva80X_lh,"LH - 80X MVA Nominal WP","l");
  leg->AddEntry(g_mvaCustom_lh,"LH - 80X MVA Custom WP","l");

  leg->AddEntry(g_mva_rh,"RH - 74X MVA","l");
  leg->AddEntry(g_mva80X_rh,"RH - 80X MVA Nominal WP","l");
  leg->AddEntry(g_mvaCustom_rh,"RH - 80X MVA Custom WP","l");
  leg->Draw("same");

  c->Print("Electron_MVAEff-vsMass.pdf");

}
