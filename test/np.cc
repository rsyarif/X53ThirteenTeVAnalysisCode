#include <iostream>
#include <sstream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TRandom.h"

#include <utility>

float getnff(float nt00, float nt01, float nt10, float nt11, int nMu){
  float f1,p1,f2,p2;

  if(nMu==0){
    f1=0.206;
    p1=0.839;
    f2=0.206;
    p2=0.839;
  }
  if(nMu==1){
    f1=0.206;
    p1=0.839;
    f2=0.427;
    p2=0.956;
  }
  if(nMu==2){
    f1=0.427;
    p1=0.956;
    f2=0.427;
    p2=0.956;
  }
  float denom =  (1 /(p1-f1))*( 1 / (p2-f2));
  float nff = f1*f2*denom* ( p1*p2*nt00 - (1-p1)*p2*nt10 - p1*(1-p2)*nt01 + (1-p1)*(1-p2)*nt11);
  return nff;
};

float getnfp(float nt00, float nt01, float nt10, float nt11, int nMu){
  float f1,p1,f2,p2;

  if(nMu==0){
    f1=0.206;
    p1=0.839;
    f2=0.206;
    p2=0.839;
  }
  if(nMu==1){
    f1=0.206;
    p1=0.839;
    f2=0.427;
    p2=0.956;
  }
  if(nMu==2){
    f1=0.427;
    p1=0.956;
    f2=0.427;
    p2=0.956;
  }
  float denom =  (1 /(p1-f1))*( 1 / (p2-f2));
  float nfp = f1*p2*denom* ( -p1*f2*nt00 + (1-p1)*f2*nt10 + p1*(1-f2)*nt01 - (1-p1)*(1-f2)*nt11);
  return nfp;
};

float getnpf(float nt00, float nt01, float nt10, float nt11, int nMu){
  float f1,p1,f2,p2;

  if(nMu==0){
    f1=0.206;
    p1=0.839;
    f2=0.206;
    p2=0.839;
  }
  if(nMu==1){
    f1=0.206;
    p1=0.839;
    f2=0.427;
    p2=0.956;
  }
  if(nMu==2){
    f1=0.427;
    p1=0.956;
    f2=0.427;
    p2=0.956;
  }
  float denom =  (1 /(p1-f1))*( 1 / (p2-f2));
  float npf = p1*f2*denom* ( -f1*p2*nt00 + (1-f1)*p2*nt10 + f1*(1-p2)*nt01 - (1-f1)*(1-p2)*nt11);
  return npf;
};

float getNEvents(TTree* t, int nMu, std::string cut, bool weight){
  
  std::stringstream channel;
  if(nMu>=0)  channel<<"&& (Channel =="<<nMu<<")";
  else  channel<<"";
  
  std::string cutstring;
  if(weight) cutstring = "NPWeight*( "+cut+channel.str()+")";
  else cutstring =  " ( "+cut+channel.str()+")";
  
  TH1F* hdummy = new TH1F("hdummy","dummy",100,0,10000);
  t->Project("hdummy","cleanAK4HT",cutstring.c_str());
  
  float nEvts = hdummy->Integral(1,hdummy->GetNbinsX()+1);
  double_t err;
  hdummy->IntegralAndError(1,hdummy->GetNbinsX()+1,err);
  
  return nEvts;
};

void np(std::string htCut="1200",TString elID="MVA2016TightRC",TString muID = "CBTightMiniIsoTight"){

  TFile* f = new TFile("NonPromptData_Mu"+muID+"_El"+elID+"_2016B-D.root");
  TTree* t = (TTree*) f->Get("tEvts_sZVeto");

  TFile* f2 = new TFile("NonPromptData_Mu"+muID+"_El"+elID+"_2016E-H.root");
  TTree* t2 = (TTree*) f2->Get("tEvts_sZVeto");
  

  std::string nt00cut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > "+htCut+" && nTL==0)";
  std::string nt01cut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > "+htCut+" && nTL==1)";
  std::string nt10cut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > "+htCut+" && nTL==2)";
  std::string nt11cut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > "+htCut+" && nTL==3)";
  std::string nbkgcut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nConst >= 5)&& cleanAK4HT > "+htCut+")";

  std::string nt00noHTcut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nCleanAK4Jets > 1) && nTL==0)";
  std::string nt01noHTcut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nCleanAK4Jets > 1) && nTL==1)";
  std::string nt10noHTcut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nCleanAK4Jets > 1) && nTL==2)";
  std::string nt11noHTcut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nCleanAK4Jets > 1) && nTL==3)";
  std::string nbkgnoHTcut = "((((((DilepMass>20) ) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )&& Lep1Pt > 40&& Lep2Pt > 30)&& nCleanAK4Jets > 1))";

  TH1F* h_nt00_ee = new TH1F("h_nt00_ee","H_{T}^{Lep} NonPrompt Check EE; H_{T}^{Lep} (GeV);Events",25,0,3000);
  TH1F* h_nt01_ee = new TH1F("h_nt01_ee","H_{T}^{Lep} NonPrompt Check EE; H_{T}^{Lep} (GeV);Events",25,0,3000);

  TH1F* hel_nt00_emu = new TH1F("hel_nt00_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (leading electron) (GeV);Events",25,0,3000);
  TH1F* hel_nt01_emu = new TH1F("hel_nt01_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (leading electron) (GeV);Events",25,0,3000);
  TH1F* hel_nt10_emu = new TH1F("hel_nt10_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (leading electron) (GeV);Events",25,0,3000);

  TH1F* h_nt00_emu = new TH1F("h_nt00_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (GeV);Events",25,0,3000);
  TH1F* h_nt01_emu = new TH1F("h_nt01_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (GeV);Events",25,0,3000);
  TH1F* h_nt10_emu = new TH1F("h_nt10_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (GeV);Events",25,0,3000);

  TH1F* hmu_nt00_emu = new TH1F("hmu_nt00_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (leading muon) (GeV);Events",25,0,3000);
  TH1F* hmu_nt01_emu = new TH1F("hmu_nt01_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (leading muon) (GeV);Events",25,0,3000);
  TH1F* hmu_nt10_emu = new TH1F("hmu_nt10_emu","H_{T}^{Lep} NonPrompt Check EMu; H_{T}^{Lep} (leading muon) (GeV);Events",25,0,3000);

  TH1F* h_nt00_mumu = new TH1F("h_nt00_mumu","H_{T}^{Lep} NonPrompt Check MuMu; H_{T}^{Lep} (GeV);Events",25,0,3000);
  TH1F* h_nt10_mumu = new TH1F("h_nt10_mumu","H_{T}^{Lep} NonPrompt Check MuMu; H_{T}^{Lep} (GeV);Events",25,0,3000);


  bool noweight=false;
  bool weight=true;
  for(int i=-1; i<3;i++){
    float nt00_1 = getNEvents(t,i,nt00cut,noweight);
    float nt01_1 = getNEvents(t,i,nt01cut,noweight);
    float nt10_1 = getNEvents(t,i,nt10cut,noweight);
    float nt11_1 = getNEvents(t,i,nt11cut,noweight);
    float nbkg_1 = getNEvents(t,i,nbkgcut,weight);

    float nt00_2 = getNEvents(t2,i,nt00cut,noweight);
    float nt01_2 = getNEvents(t2,i,nt01cut,noweight);
    float nt10_2 = getNEvents(t2,i,nt10cut,noweight);
    float nt11_2 = getNEvents(t2,i,nt11cut,noweight);
    float nbkg_2 = getNEvents(t2,i,nbkgcut,weight);

    std::cout<<"**************************"<<std::endl;
    std::cout<<"Channel: "<<i<<std::endl;
    std::cout<<"nt00: "<<nt00_1+nt00_2<<std::endl;
    std::cout<<"nt01: "<<nt01_1+nt01_2<<std::endl;
    std::cout<<"nt10: "<<nt10_1+nt10_2<<std::endl;
    std::cout<<"nt11: "<<nt11_1+nt00_2<<std::endl;// - BLINDED FOR NOW
    //std::cout<<"nt11: XX"<<std::endl;
    std::cout<<"total bkg: "<<nbkg_1+nbkg_2<<std::endl;
    TRandom* rand = new TRandom();
    TH1F* h_tot;
    TH1F* h_nozero;
    TH1F* h_tot_bd;
    TH1F* h_nozero_bd;
    TH1F* h_tot_eh;
    TH1F* h_nozero_eh;
    if(i==0){
      h_tot = new TH1F("h_tot","",25,-5,20);
      h_nozero= new TH1F("h_nozero","",25,-5,20);
      h_tot_bd = new TH1F("h_tot","",25,-5,20);
      h_nozero_bd= new TH1F("h_nozero","",25,-5,20);
      h_tot_eh = new TH1F("h_tot","",25,-5,20);
      h_nozero_eh= new TH1F("h_nozero","",25,-5,20);
    }
    else{
      h_tot = new TH1F("h_tot","",155,-5,150);
      h_nozero = new TH1F("h_nozero","",155,-5,150);
      h_tot_bd = new TH1F("h_tot","",155,-5,150);
      h_nozero_bd = new TH1F("h_nozero","",155,-5,150);
      h_tot_eh = new TH1F("h_tot","",155,-5,150);
      h_nozero_eh = new TH1F("h_nozero","",155,-5,150);
    }
    
    TLegend* leg = new TLegend(0.5,0.1,0.9,0.5);    
    TCanvas* c1 = new TCanvas();

    if(i==0){
      std::string chan_nt00cut = "("+nt00noHTcut+") && Channel==0";
      t->Project("h_nt00_ee","cleanAK4HT",chan_nt00cut.c_str());
      std::string chan_nt01cut = "("+nt01noHTcut+") && Channel==0";
      t->Project("h_nt01_ee","cleanAK4HT",chan_nt01cut.c_str());
      
      //run poisson distributions for backgroun
      for(int j=0; j<100000; j++){
	//first background
	int ntemp00_1  = rand->Poisson(nt00_1);
	int ntemp01_1  = rand->Poisson(nt01_1);
	int ntemp10_1  = 0;
	int ntemp11_1  = rand->Poisson(nt11_1);
	float nff_1 = getnff( ntemp00_1,ntemp01_1,ntemp10_1,ntemp11_1,1);
	float nfp_1 = getnfp( ntemp00_1,ntemp01_1,ntemp10_1,ntemp11_1,1);
	float npf_1 = getnpf( ntemp00_1,ntemp01_1,ntemp10_1,ntemp11_1,1);
	//second experiment
	int ntemp00_2  = rand->Poisson(nt00_2);
	int ntemp01_2  = rand->Poisson(nt01_2);
	int ntemp10_2  = 0;
	int ntemp11_2  = rand->Poisson(nt11_2);
	float nff_2 = getnff( ntemp00_2,ntemp01_2,ntemp10_2,ntemp11_2,1);
	float nfp_2 = getnfp( ntemp00_2,ntemp01_2,ntemp10_2,ntemp11_2,1);
	float npf_2 = getnpf( ntemp00_2,ntemp01_2,ntemp10_2,ntemp11_2,1);

	float nbkg =npf_1+nfp_1+nff_1+npf_2+nfp_2+nff_2;
	float nbkg_nozero = 0.;
	float nbkg_nozero_bd = 0.;
	float nbkg_nozero_eh = 0.;
	float nbkg_bd = npf_1+nfp_1+nff_1;
	h_tot_bd->Fill(nbkg_bd);
	float nbkg_eh = npf_2+nfp_2+nff_2;
	h_tot_eh->Fill(nbkg_eh);
	if(npf_1+nfp_1 >=0) nbkg_nozero_bd+=nfp_1+npf_1;
	if(nff_1>0) nbkg_nozero_bd+=nff_1;
	h_nozero_bd->Fill(nbkg_nozero_bd);
	if(npf_2+nfp_2 >=0) nbkg_nozero_eh+=nfp_2+npf_2;
	if(nff_2>0) nbkg_nozero_eh+=nff_2;
	h_nozero_eh->Fill(nbkg_nozero_eh);

	if( (npf_1 + nfp_1) >= 0) nbkg_nozero+=npf_1+nfp_1;
	if( (nff_1) >= 0) nbkg_nozero+=nff_1;
	if( (npf_2 + nfp_2) >= 0) nbkg_nozero+=npf_2+nfp_2;
	if( (nff_2) >= 0) nbkg_nozero+=nff_2;
	h_nozero->Fill(nbkg_nozero);
	//else if( (npf+nfp)<0 && nff>=0) h_nozero->Fill(nff);
	//std::cout<<"npf+nfp+nff: "<<npf+nfp+nff<<" and nbgk: "<<nbkg<<std::endl;
	//h_tot->Fill(nff+npf+nfp);
	h_tot->Fill(nbkg);
      }
      
      
      gStyle->SetOptStat(kFALSE);
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);
      h_nozero->SetLineColor(kRed);
      h_nozero->SetTitle("Distribution of NonPrompt - ee; N_{events}; Counts ");
      h_nozero->Draw();
      h_tot->Draw("same");
      std::string totstring = Form("Non-Truncated - Mean: %.2f; RMS: %.2f",h_tot->GetMean(),h_tot->GetRMS());
      std::string nozstring = Form("Truncated - Mean: %.2f; RMS: %.2f",h_nozero->GetMean(),h_nozero->GetRMS());
      leg->AddEntry(h_tot,totstring.c_str(),"l");
      leg->AddEntry(h_nozero,nozstring.c_str(), "l");
      leg->Draw("same");
      TString canname = "Check_ee_HT"+htCut+"_Overlay_Mu"+muID+"_El"+elID+".pdf";
      c1->Print(canname);
      //by era plotting
      TLegend* leg2 = new TLegend(0.5,0.5,0.9,0.9);
      //line styles
      h_nozero_bd->SetLineColor(kRed);
      h_nozero_bd->SetLineStyle(2);
      h_tot_bd->SetLineStyle(2);
      h_nozero_eh->SetLineColor(kRed);
      h_tot_eh->SetLineColor(kBlack);
      //title
      h_nozero_bd->SetTitle("Distribution of NonPrompt - ee; N_{events}; Counts ");
      //draw
      h_nozero_bd->Draw();
      h_tot_eh->Draw("same");
      h_nozero_eh->Draw("same");
      h_tot_bd->Draw("same");
      //add to legend
      TString totstring_bd = Form("2016BD Non-Truncated - Mean: %.2f; RMS: %.2f",h_tot_bd->GetMean(),h_tot_bd->GetRMS());
      TString nozstring_bd = Form("2016BD Truncated - Mean: %.2f; RMS: %.2f",h_nozero_bd->GetMean(),h_nozero_bd->GetRMS());
      TString totstring_eh = Form("2016EH Non-Truncated - Mean: %.2f; RMS: %.2f",h_tot_eh->GetMean(),h_tot_eh->GetRMS());
      TString nozstring_eh = Form("2016EH Truncated - Mean: %.2f; RMS: %.2f",h_nozero_eh->GetMean(),h_nozero_eh->GetRMS());
      leg2->AddEntry(h_tot_bd,totstring_bd,"l");
      leg2->AddEntry(h_nozero_bd,nozstring_bd,"l");
      leg2->AddEntry(h_tot_eh,totstring_eh,"l");
      leg2->AddEntry(h_nozero_eh,nozstring_eh,"l");
      leg2->Draw("same");
      TString canname_era = "Check_ee_HT"+htCut+"_OverlayByEra_Mu"+muID+"_El"+elID+".pdf";
      c1->Print(canname_era);
    }
    else if(i==1){
      std::string chan_nt00cut = "("+nt00noHTcut+") && Channel==1";
      t->Project("h_nt00_emu","cleanAK4HT",chan_nt00cut.c_str());
      std::string chan_nt01cut = "("+nt01noHTcut+") && Channel==1";
      t->Project("h_nt01_emu","cleanAK4HT",chan_nt01cut.c_str());
      std::string chan_nt10cut = "("+nt10noHTcut+") && Channel==1";
      t->Project("h_nt10_emu","cleanAK4HT",chan_nt10cut.c_str());
      
      std::string chan_nt00cut_el = "("+nt00noHTcut+") && Channel==1 && Lep1Flavor==0";
      t->Project("hel_nt00_emu","cleanAK4HT",chan_nt00cut_el.c_str());
      std::string chan_nt01cut_el = "("+nt01noHTcut+") && Channel==1 && Lep1Flavor==0";
      t->Project("hel_nt01_emu","cleanAK4HT",chan_nt01cut_el.c_str());
      std::string chan_nt10cut_el = "("+nt10noHTcut+") && Channel==1 && Lep1Flavor==0";
      t->Project("hel_nt10_emu","cleanAK4HT",chan_nt10cut_el.c_str());
      
      std::string chan_nt00cut_mu = "("+nt00noHTcut+") && Channel==1 && Lep1Flavor==1";
      t->Project("hmu_nt00_emu","cleanAK4HT",chan_nt00cut_mu.c_str());
      std::string chan_nt01cut_mu = "("+nt01noHTcut+") && Channel==1 && Lep1Flavor==1";
      t->Project("hmu_nt01_emu","cleanAK4HT",chan_nt01cut_mu.c_str());
      std::string chan_nt10cut_mu = "("+nt10noHTcut+") && Channel==1 && Lep1Flavor==1";
      t->Project("hmu_nt10_emu","cleanAK4HT",chan_nt10cut_mu.c_str());
      
      
      //run poisson distributions for backgroun
      for(int i=0; i<100000; i++){
	//first background
	int ntemp00_1  = rand->Poisson(nt00_1);
	int ntemp01_1  = rand->Poisson(nt01_1);
	int ntemp10_1  = rand->Poisson(nt10_1);
	int ntemp11_1  = rand->Poisson(nt11_1);
	float nff_1 = getnff( ntemp00_1,ntemp01_1,ntemp10_1,ntemp11_1,1);
	float nfp_1 = getnfp( ntemp00_1,ntemp01_1,ntemp10_1,ntemp11_1,1);
	float npf_1 = getnpf( ntemp00_1,ntemp01_1,ntemp10_1,ntemp11_1,1);
	//second experiment
	int ntemp00_2  = rand->Poisson(nt00_2);
	int ntemp01_2  = rand->Poisson(nt01_2);
	int ntemp10_2  = rand->Poisson(nt10_2);
	int ntemp11_2  = rand->Poisson(nt11_2);
	float nff_2 = getnff( ntemp00_2,ntemp01_2,ntemp10_2,ntemp11_2,1);
	float nfp_2 = getnfp( ntemp00_2,ntemp01_2,ntemp10_2,ntemp11_2,1);
	float npf_2 = getnpf( ntemp00_2,ntemp01_2,ntemp10_2,ntemp11_2,1);
	
	float nbkg =npf_1+nfp_1+nff_1+npf_2+nfp_2+nff_2;
	float nbkg_nozero = 0.;
	if( (npf_1 + nfp_1) > 0) nbkg_nozero+=npf_1+nfp_1;
	if( (nff_1) > 0) nbkg_nozero+=nff_1;
	if( (npf_2 + nfp_2) > 0) nbkg_nozero+=npf_2+nfp_2;
	if( (nff_2) > 0) nbkg_nozero+=nff_2;
	h_nozero->Fill(nbkg_nozero);
	float nbkg_nozero_bd = 0.;
	float nbkg_nozero_eh = 0.;
	float nbkg_bd = npf_1+nfp_1+nff_1;
	h_tot_bd->Fill(nbkg_bd);
	float nbkg_eh = npf_2+nfp_2+nff_2;
	h_tot_eh->Fill(nbkg_eh);
	if(npf_1+nfp_1 >=0) nbkg_nozero_bd+=nfp_1+npf_1;
	if(nff_1>0) nbkg_nozero_bd+=nff_1;
	h_nozero_bd->Fill(nbkg_nozero_bd);
	if(npf_2+nfp_2 >=0) nbkg_nozero_eh+=nfp_2+npf_2;
	if(nff_2>0) nbkg_nozero_eh+=nff_2;
	h_nozero_eh->Fill(nbkg_nozero_eh);

	/*if( ((npf_1+nfp_1) >=0 && nff_1>=0 && (npf_1+nfp_1+nff_1 >=0) )||( (npf_2+nfp_2) >=0 && nff_2>=0 && (npf_2+nfp_2+nff_2 >=0) )){
	  h_nozero->Fill(nbkg);	  
	}
	else if( (npf_1+nfp_1)>=0 && nff_1<0){
	  h_nozero->Fill(npf_1+nfp_1);
	}
	else if( (npf_2+nfp_2)>=0 && nff_2<0){
	  h_nozero->Fill(npf_2+nfp_2);
	  }*/
	//std::cout<<"npf+nfp+nff: "<<npf+nfp+nff<<" and nbgk: "<<nbkg<<std::endl;
	//h_tot->Fill(nff+npf+nfp);
	h_tot->Fill(nbkg);
      }

    
      gStyle->SetOptStat(kFALSE);
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);
      h_nozero->SetLineColor(kRed);
      h_nozero->SetTitle("Distribution of NonPrompt - emu; N_{events}; Counts ");
      h_nozero->Draw();
      h_tot->Draw("same");
      std::string totstring = Form("Non-Truncated - Mean: %.2f; RMS: %.2f",h_tot->GetMean(),h_tot->GetRMS());
      std::string nozstring = Form("Truncated - Mean: %.2f; RMS: %.2f",h_nozero->GetMean(),h_nozero->GetRMS());
      leg->AddEntry(h_tot,totstring.c_str(),"l");
      leg->AddEntry(h_nozero,nozstring.c_str(), "l");
      leg->Draw("same");
      TString canname = "Check_emu_HT"+htCut+"_Overlay_Mu"+muID+"_El"+elID+".pdf";
      c1->Print(canname);
      //by era plotting
      TLegend* leg2 = new TLegend(0.5,0.5,0.9,0.9);
      //line styles
      h_nozero_bd->SetLineColor(kRed);
      h_nozero_bd->SetLineStyle(2);
      h_tot_bd->SetLineStyle(2);
      h_nozero_eh->SetLineColor(kRed);
      h_tot_eh->SetLineColor(kBlack);
      //title
      h_nozero_bd->SetTitle("Distribution of NonPrompt - emu; N_{events}; Counts ");
      //draw
      h_nozero_bd->Draw();
      h_tot_eh->Draw("same");
      h_nozero_eh->Draw("same");
      h_tot_bd->Draw("same");
      //add to legend
      TString totstring_bd = Form("2016BD Non-Truncated - Mean: %.2f; RMS: %.2f",h_tot_bd->GetMean(),h_tot_bd->GetRMS());
      TString nozstring_bd = Form("2016BD Truncated - Mean: %.2f; RMS: %.2f",h_nozero_bd->GetMean(),h_nozero_bd->GetRMS());
      TString totstring_eh = Form("2016EH Non-Truncated - Mean: %.2f; RMS: %.2f",h_tot_eh->GetMean(),h_tot_eh->GetRMS());
      TString nozstring_eh = Form("2016EH Truncated - Mean: %.2f; RMS: %.2f",h_nozero_eh->GetMean(),h_nozero_eh->GetRMS());
      leg2->AddEntry(h_tot_bd,totstring_bd,"l");
      leg2->AddEntry(h_nozero_bd,nozstring_bd,"l");
      leg2->AddEntry(h_tot_eh,totstring_eh,"l");
      leg2->AddEntry(h_nozero_eh,nozstring_eh,"l");
      leg2->Draw("same");
      TString canname_era = "Check_emu_HT"+htCut+"_OverlayByEra_Mu"+muID+"_El"+elID+".pdf";
      c1->Print(canname_era);

    }
    else if(i==2){
      std::string chan_nt00cut = "("+nt00noHTcut+") && Channel==2";
      t->Project("h_nt00_mumu","cleanAK4HT",chan_nt00cut.c_str());
      std::string chan_nt10cut = "("+nt10noHTcut+") && Channel==2";
      t->Project("h_nt10_mumu","cleanAK4HT",chan_nt10cut.c_str());

    //run poisson distributions for backgroun
      for(int i=0; i<100000; i++){

	//first background
	int ntemp00_1  = rand->Poisson(nt00_1);
	int ntemp01_1  = 0;
	int ntemp10_1  = rand->Poisson(nt10_1);
	int ntemp11_1  = rand->Poisson(nt11_1);
	float nff_1 = getnff( ntemp00_1,ntemp01_1,ntemp10_1,ntemp11_1,1);
	float nfp_1 = getnfp( ntemp00_1,ntemp01_1,ntemp10_1,ntemp11_1,1);
	float npf_1 = getnpf( ntemp00_1,ntemp01_1,ntemp10_1,ntemp11_1,1);
	//second experiment
	int ntemp00_2  = rand->Poisson(nt00_2);
	int ntemp01_2  = 0;
	int ntemp10_2  = rand->Poisson(nt10_2);
	int ntemp11_2  = rand->Poisson(nt11_2);
	float nff_2 = getnff( ntemp00_2,ntemp01_2,ntemp10_2,ntemp11_2,1);
	float nfp_2 = getnfp( ntemp00_2,ntemp01_2,ntemp10_2,ntemp11_2,1);
	float npf_2 = getnpf( ntemp00_2,ntemp01_2,ntemp10_2,ntemp11_2,1);
	
	float nbkg =npf_1+nfp_1+nff_1+npf_2+nfp_2+nff_2;
	float nbkg_nozero = 0.;
	if( (npf_1 + nfp_1) > 0) nbkg_nozero+=npf_1+nfp_1;
	if( (nff_1) > 0) nbkg_nozero+=nff_1;
	if( (npf_2 + nfp_2) > 0) nbkg_nozero+=npf_2+nfp_2;
	if( (nff_2) > 0) nbkg_nozero+=nff_2;
	h_nozero->Fill(nbkg_nozero);
	float nbkg_nozero_bd = 0.;
	float nbkg_nozero_eh = 0.;
	float nbkg_bd = npf_1+nfp_1+nff_1;
	h_tot_bd->Fill(nbkg_bd);
	float nbkg_eh = npf_2+nfp_2+nff_2;
	h_tot_eh->Fill(nbkg_eh);
	if(npf_1+nfp_1 >=0) nbkg_nozero_bd+=nfp_1+npf_1;
	if(nff_1>0) nbkg_nozero_bd+=nff_1;
	h_nozero_bd->Fill(nbkg_nozero_bd);
	if(npf_2+nfp_2 >=0) nbkg_nozero_eh+=nfp_2+npf_2;
	if(nff_2>0) nbkg_nozero_eh+=nff_2;
	h_nozero_eh->Fill(nbkg_nozero_eh);

	/*if( ((npf_1+nfp_1) >=0 && nff_1>=0 && (npf_1+nfp_1+nff_1 >=0) )||( (npf_2+nfp_2) >=0 && nff_2>=0 && (npf_2+nfp_2+nff_2 >=0) )){
	  h_nozero->Fill(nbkg);	  
	}
	else if( (npf_1+nfp_1)>=0 && nff_1<0){
	  h_nozero->Fill(npf_1+nfp_1);
	}
	else if( (npf_2+nfp_2)>=0 && nff_2<0){
	  h_nozero->Fill(npf_2+nfp_2);
	  }*/
	//std::cout<<"npf+nfp+nff: "<<npf+nfp+nff<<" and nbgk: "<<nbkg<<std::endl;
	//h_tot->Fill(nff+npf+nfp);
	h_tot->Fill(nbkg);
      }


      gStyle->SetOptStat(kFALSE);
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);
      h_nozero->SetLineColor(kRed);
      h_nozero->SetTitle("Distribution of NonPrompt - mumu; N_{events}; Counts ");
      h_nozero->Draw();
      h_tot->Draw("same");
      std::string totstring = Form("Non-Truncated - Mean: %.2f; RMS: %.2f",h_tot->GetMean(),h_tot->GetRMS());
      std::string nozstring = Form("Truncated - Mean: %.2f; RMS: %.2f",h_nozero->GetMean(),h_nozero->GetRMS());
      leg->AddEntry(h_tot,totstring.c_str(),"l");
      leg->AddEntry(h_nozero,nozstring.c_str(), "l");
      leg->Draw("same");
      TString canname = "Check_mumu_HT"+htCut+"_Overlay_Mu"+muID+"_El"+elID+".pdf";
      c1->Print(canname);

      //by era plotting
      TLegend* leg2 = new TLegend(0.5,0.5,0.9,0.9);
      //line styles
      h_nozero_bd->SetLineColor(kRed);
      h_nozero_bd->SetLineStyle(2);
      h_tot_bd->SetLineStyle(2);
      h_nozero_eh->SetLineColor(kRed);
      h_tot_eh->SetLineColor(kBlack);
      //title
      h_nozero_bd->SetTitle("Distribution of NonPrompt - mumu; N_{events}; Counts ");
      //draw
      h_nozero_bd->Draw();
      h_tot_eh->Draw("same");
      h_nozero_eh->Draw("same");
      h_tot_bd->Draw("same");
      //add to legend
      TString totstring_bd = Form("2016BD Non-Truncated - Mean: %.2f; RMS: %.2f",h_tot_bd->GetMean(),h_tot_bd->GetRMS());
      TString nozstring_bd = Form("2016BD Truncated - Mean: %.2f; RMS: %.2f",h_nozero_bd->GetMean(),h_nozero_bd->GetRMS());
      TString totstring_eh = Form("2016EH Non-Truncated - Mean: %.2f; RMS: %.2f",h_tot_eh->GetMean(),h_tot_eh->GetRMS());
      TString nozstring_eh = Form("2016EH Truncated - Mean: %.2f; RMS: %.2f",h_nozero_eh->GetMean(),h_nozero_eh->GetRMS());
      leg2->AddEntry(h_tot_bd,totstring_bd,"l");
      leg2->AddEntry(h_nozero_bd,nozstring_bd,"l");
      leg2->AddEntry(h_tot_eh,totstring_eh,"l");
      leg2->AddEntry(h_nozero_eh,nozstring_eh,"l");
      leg2->Draw("same");
      TString canname_era = "Check_mumu_HT"+htCut+"_OverlayByEra_Mu"+muID+"_El"+elID+".pdf";
      c1->Print(canname_era);



    }
  }
  gStyle->SetOptStat(kFALSE);  
  TCanvas* c = new TCanvas();
  c->SetLogy();
  TLegend* leg_ee = new TLegend(0.5,0.5,0.9,0.9);
  leg_ee->SetFillStyle(0);
  leg_ee->SetBorderSize(0);
  h_nt00_ee->SetMarkerStyle(20);
  h_nt00_ee->SetMarkerColor(kBlue);
  h_nt00_ee->SetLineColor(kBlue);
  h_nt00_ee->GetYaxis()->SetRangeUser(0.01,10100);
  h_nt00_ee->Draw("phist");
  h_nt01_ee->Draw("hist same");
  leg_ee->AddEntry("h_nt00_ee","Loose-Loose","p");
  leg_ee->AddEntry("h_nt01_ee","Tight-Loose","l");
  leg_ee->Draw("same");
  c->Print("NPBackground_ee_Mu"+muID+"_El"+elID+".pdf");


  TLegend* leg_emu = new TLegend(0.5,0.5,0.9,0.9);
  leg_emu->SetFillStyle(0);
  leg_emu->SetBorderSize(0);
  h_nt00_emu->SetMarkerStyle(20);
  h_nt00_emu->SetMarkerColor(kBlue);
  h_nt00_emu->SetLineColor(kBlue);
  h_nt00_emu->GetYaxis()->SetRangeUser(0.01,10100);
  h_nt00_emu->Draw("phist");
  h_nt01_emu->Draw("hist same");
  h_nt10_emu->SetLineColor(kRed);
  h_nt10_emu->Draw("hist same");
  leg_emu->AddEntry("h_nt00_emu","Loose-Loose","p");
  leg_emu->AddEntry("h_nt01_emu","Tight El - Loose Mu","l");
  leg_emu->AddEntry("h_nt10_emu","Loose El - Tight Mu","l");
  leg_emu->Draw("same");
  c->Print("NPBackground_emu_Mu"+muID+"_El"+elID+".pdf");


  TLegend* legel_emu = new TLegend(0.5,0.5,0.9,0.9);
  legel_emu->SetFillStyle(0);
  legel_emu->SetBorderSize(0);
  hel_nt00_emu->SetMarkerStyle(20);
  hel_nt00_emu->SetMarkerColor(kBlue);
  hel_nt00_emu->SetLineColor(kBlue);
  hel_nt00_emu->GetYaxis()->SetRangeUser(0.01,10100);
  hel_nt00_emu->Draw("phist");
  hel_nt01_emu->Draw("hist same");
  hel_nt10_emu->SetLineColor(kRed);
  hel_nt10_emu->Draw("hist same");
  legel_emu->AddEntry("hel_nt00_emu","Loose-Loose","p");
  legel_emu->AddEntry("hel_nt01_emu","Tight El - Loose Mu","l");
  legel_emu->AddEntry("hel_nt10_emu","Loose El - Tight Mu","l");
  legel_emu->Draw("same");
  c->Print("NPBackground_emu_LeadingElectron_Mu"+muID+"_El"+elID+".pdf");


  TLegend* legmu_emu = new TLegend(0.5,0.5,0.9,0.9);
  legmu_emu->SetFillStyle(0);
  legmu_emu->SetBorderSize(0);
  hmu_nt00_emu->SetMarkerStyle(20);
  hmu_nt00_emu->SetMarkerColor(kBlue);
  hmu_nt00_emu->SetLineColor(kBlue);
  hmu_nt00_emu->GetYaxis()->SetRangeUser(0.01,10100);
  hmu_nt00_emu->Draw("phist");
  hmu_nt01_emu->Draw("hist same");
  hmu_nt10_emu->SetLineColor(kRed);
  hmu_nt10_emu->Draw("hist same");
  legmu_emu->AddEntry("hmu_nt00_emu","Loose-Loose","p");
  legmu_emu->AddEntry("hmu_nt01_emu","Tight El - Loose Mu","l");
  legmu_emu->AddEntry("hmu_nt10_emu","Loose El - Tight Mu","l");
  legmu_emu->Draw("same");
  c->Print("NPBackground_emu_LeadingMuon_Mu"+muID+"_El"+elID+".pdf");

  TLegend* leg_mumu = new TLegend(0.5,0.5,0.9,0.9);
  leg_mumu->SetFillStyle(0);
  leg_mumu->SetBorderSize(0);
  h_nt00_mumu->SetMarkerStyle(20);
  h_nt00_mumu->SetMarkerColor(kBlue);
  h_nt00_mumu->SetLineColor(kBlue);
  h_nt00_mumu->GetYaxis()->SetRangeUser(0.01,10100);
  h_nt00_mumu->Draw("phist");
  h_nt10_mumu->Draw("hist same");
  leg_mumu->AddEntry("h_nt00_mumu","Loose-Loose","p");
  leg_mumu->AddEntry("h_nt10_mumu","Tight-Loose","l");
  leg_mumu->Draw("same");
  c->Print("NPBackground_mumu_Mu"+muID+"_El"+elID+".pdf");

}
