#include "TStyle.h"
void DrawAndSave(TString var, bool logy, TString pdfname, TTree* tPred, TTree* tObs,TString obsCut, TString PredCut){

  tPred->SetFillColor(kCyan+2);
  tObs->SetMarkerStyle(20);

  TCanvas* c = new TCanvas();
  //make tpads
  TPad* pad1 = new TPad("pad1","pad1",0.01,0.2,1,1);
  TPad* pad2 = new TPad("pad2","pad2",0.01,0.,1,0.2);

  pad1->SetTopMargin(0.1);
  pad1->SetLogy();
  pad2->SetTopMargin(0.0);
  pad1->SetBottomMargin(0.0);
  pad2->SetBottomMargin(0.3);
  pad1->Draw();
  pad2->Draw();
  //cd to top pad for drawing
  pad1->cd();


  float etabins[11] ={-2.4,-1.566,-1.4442,-0.8,-0.4,0.,0.4,0.8,1.4442,1.566,2.4};
  float massbins[12] = {80,82,84,86,88,90,92,94,96,98,100,102};
  float ptbins[26] = {30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,250,300,350,400,500};

  TH1F* h_pred;
  TH1F* h_obs;
  if(var=="Lep1Eta" || var =="Lep2Eta"){
    h_pred = new TH1F("h_pred","; #eta;N_{Events}",10,etabins);
    h_obs = new TH1F("h_obs","",10,etabins);
  }
  else if(var=="DilepMass"){
    h_pred = new TH1F("h_pred",";M_{ll} (GeV};N_{Events}",11,massbins);
    h_obs = new TH1F("h_obs","",11,massbins);
  }
  else{
    h_pred = new TH1F("h_pred",";p_{T} (GeV}; N_{Events}",25,ptbins);
    h_obs = new TH1F("h_obs","",25,ptbins);
  }


  tPred->Project("h_pred",var,PredCut);
  tObs->Project("h_obs",var,obsCut);
  h_pred->SetFillColor(kCyan+2);
  h_obs->SetMarkerStyle(20);
  h_pred->Draw("hist");
  h_obs->Draw("pe same");
  //tPred->Draw(var,PredCut,"hist");
  //tObs->Draw(var,obsCut,"pe same");
  TLegend* leg;
  if(var=="DilepMass") leg = new TLegend(.7,0.7,0.9,0.9);
  else leg = new TLegend(0.4,0.7,0.6,0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_pred,"Pred","f");
  leg->AddEntry(h_obs, "Obs","p");
  leg->Draw("same");
  //latex
  TLatex* cmstex = new TLatex();
  cmstex->SetNDC();
  cmstex->SetTextSize(0.06);
  //draw latex
  cmstex->DrawLatex(0.15,0.93,"CMS Preliminary");

  if(logy) c->SetLogy();


  //now go to pad2 and draw ratio
  pad2->cd();
  TH1F* h_ratio = (TH1F*) h_obs->Clone("h_ratio");
  h_ratio->Divide(h_pred);
  h_ratio->GetYaxis()->SetRangeUser(0.5,1.5);
  h_ratio->GetYaxis()->SetTitle("Obs/Pred");
  h_ratio->GetYaxis()->SetTitleOffset(0.4);
  h_ratio->GetYaxis()->SetTitleSize(0.12);
  h_ratio->GetYaxis()->CenterTitle();
  h_ratio->GetYaxis()->SetLabelSize(0.10);
  if(var=="Lep1Eta")  h_ratio->GetXaxis()->SetTitle("Leading Lepton #eta");
  else if(var=="Lep2Eta")  h_ratio->GetXaxis()->SetTitle("sub-Leading Lepton #eta");
  else if(var=="Lep1Pt")  h_ratio->GetXaxis()->SetTitle("Leading Lepton p_{T}");
  else if(var=="Lep2Pt")  h_ratio->GetXaxis()->SetTitle("sub-Leading Lepton p_{T}");
  else if(var=="DilepMass")  h_ratio->GetXaxis()->SetTitle("M_{ll}");

  h_ratio->GetXaxis()->SetTitleSize(0.12);
  h_ratio->GetXaxis()->CenterTitle();
  h_ratio->GetXaxis()->SetLabelSize(0.10);
  h_ratio->GetYaxis()->SetNdivisions(205);
  h_ratio->Draw("pe");
  TLine* baseline;
  if(var=="Lep1Pt" || var=="Lep2Pt") baseline= new TLine(30,1,500,1);
  else if(var=="Lep1Eta" || var=="Lep2Eta") baseline= new TLine(-2.5,1,2.5,1);
  else if(var=="DilepMass") baseline= new TLine(80,1,102,1);
  baseline->SetLineColor(kBlack);
  baseline->SetLineStyle(2);
  baseline->Draw();

  c->Update();

  
  c->Print(pdfname);
  delete h_pred;
  delete h_obs;
}

void ChargeMisID_Closure(){
  gStyle->SetOptStat(kFALSE);
  TFile* f = new TFile("../../../test/ChargeMisID_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TTree* t = (TTree*) f->Get("tEvts_ssdl");

  TFile* fd = new TFile("../../../test/Data_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TTree* td = (TTree*) fd->Get("tEvts_ssdl");
  
  float DilepMass,Lep1Pt,Lep1Eta,Lep1Phi,Lep2Pt,Lep2Eta,Lep2Phi,cmidWeight;

  DrawAndSave("DilepMass",false,"DilepMass_Comparison_Twiki.pdf",t,td,"Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101","ChargeMisIDWeight*(Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101)");
  DrawAndSave("Lep1Pt",true,"Lep1Pt_Comparison_Twiki.pdf",t,td,"Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101","ChargeMisIDWeight*(Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101)");
  DrawAndSave("Lep1Eta",false,"Lep1Eta_Comparison_Twiki.pdf",t,td,"Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101","ChargeMisIDWeight*(Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101)");
  DrawAndSave("Lep1Eta",false,"Lep1Eta_LLPt_Comparison_Twiki.pdf",t,td,"Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101 && Lep1Pt<100","ChargeMisIDWeight*(Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101 && Lep1Pt<100)");
  DrawAndSave("Lep1Eta",false,"Lep1Eta_HXPt_Comparison_Twiki.pdf",t,td,"Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101 && Lep1Pt>100","ChargeMisIDWeight*(Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101 && Lep1Pt>100)");
  DrawAndSave("Lep1Eta",false,"Lep1Eta_HHPt_Comparison_Twiki.pdf",t,td,"Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101 && Lep2Pt>100","ChargeMisIDWeight*(Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101 && Lep2Pt>100)");
  DrawAndSave("Lep2Pt",true,"Lep2Pt_Comparison_Twiki.pdf",t,td,"Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101","ChargeMisIDWeight*(Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101)");
  DrawAndSave("Lep2Eta",false,"Lep2Eta_Comparison_Twiki.pdf",t,td,"Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101","ChargeMisIDWeight*(Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101)");
  DrawAndSave("Lep1Eta",false,"Lep1Eta_excess_Twiki.pdf",t,td,"Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101 && Lep1Pt > 300 && Lep1Pt < 350","ChargeMisIDWeight*(Channel==0 && (TMath::Abs(Lep1Eta) < 1.4442 || TMath::Abs(Lep1Eta)>1.566) && (TMath::Abs(Lep2Eta) < 1.4442 || TMath::Abs(Lep2Eta)>1.566) && DilepMass>81 && DilepMass < 101 && Lep1Pt > 300 && Lep1Pt < 350)");
  td->SetBranchAddress("ChargeMisIDWeight",&cmidWeight);
  td->SetBranchAddress("Lep1Pt",&Lep1Pt);
  td->SetBranchAddress("Lep1Eta",&Lep1Eta);
  td->SetBranchAddress("Lep2Pt",&Lep2Pt);
  td->SetBranchAddress("Lep2Eta",&Lep2Eta);
  td->SetBranchAddress("DilepMass",&DilepMass);
  /* for(int i=0; i< td->GetEntries(); i++){
    td->GetEntry(i);
    //  if(i%10000==0){
    if(DilepMass>81 && DilepMass < 101 && Lep1Pt>200) std::cout<<"Lep1 eta: "<<Lep1Eta<<" Lep2 eta: "<<Lep2Eta<<" cmid weight: "<<cmidWeight<<std::endl;
    }*/
  

  /*
  t->Draw("DilepMass","ChargeMisIDWeight*(DilepMass>81 && DilepMass<101)","hist");
  t->SetFillColor(kCyan+2);
  td->Draw("DilepMass","DilepMass>81 && DilepMass < 101","pe same");
  
  c->Print("DilepMass_comparison_Twiki.pdf");

  t->Draw("Lep1Pt","ChargeMisIDWeight*(DilepMass>81 && DilepMass<101)");
  td->Draw("Lep1Pt","DilepMass>81 && DilepMass < 101","hist same");

  c->Print("Lep1Pt_comparison_Twiki.pdf");*/

}
