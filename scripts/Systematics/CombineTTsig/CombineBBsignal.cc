#include <iostream>
#include <iomanip> 
#include <vector>
#include <string>
#include "TString.h"

bool DEBUG = true;

float getEvents(TTree* t,TString cut){
  float nEvents = t->Draw("Lep1Pt",cut);
  return nEvents;
}


void combinedSignal(TString mass, int BRtype){

//   TString mass = "800";

//   TString workArea = "/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/X53ThirteenTeVAnalysisCode/test/";
//   TString workArea = "/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/X53ThirteenTeVAnalysisCode/test/ProcessedByJulie_Oct18-2017/test/";
  TString workArea = "/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/X53ThirteenTeVAnalysisCode/test/ProcessedByJulie_Oct20-2017/test/";
  TString fname = workArea+"BprimeBprime_M-"+mass;

  //--------------------open root files to combine : all the decays
  if(DEBUG)std::cout << "Opening Files ..." << std::endl;
  TFile* f_TWTW = TFile::Open(fname+"_TWTW_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* f_BZBZ = TFile::Open(fname+"_BZBZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* f_BHBH = TFile::Open(fname+"_BHBH_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* f_BHTW = TFile::Open(fname+"_BHTW_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* f_BZTW = TFile::Open(fname+"_BZTW_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* f_BZBH = TFile::Open(fname+"_BZBH_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  
  //--------------------create new root file
  TString decay;
  if(BRtype==0) decay = "tW0p5bZ0p25bH0p25";
  if(BRtype==1) decay = "tW0p0bZ1p0bH0p0";
  if(BRtype==2) decay = "tW0p0bZ0p8bH0p2";
  if(BRtype==3) decay = "tW0p0bZ0p6bH0p4";
  if(BRtype==4) decay = "tW0p0bZ0p4bH0p6";
  if(BRtype==5) decay = "tW0p0bZ0p2bH0p8";
  if(BRtype==6) decay = "tW0p0bZ0p0bH0p0";
  if(BRtype==7) decay = "tW0p2bZ0p8bH0p0";
  if(BRtype==8) decay = "tW0p2bZ0p6bH0p2";
  if(BRtype==9) decay = "tW0p2bZ0p4bH0p4";
  if(BRtype==10) decay = "tW0p2bZ0p2bH0p6";
  if(BRtype==11) decay = "tW0p2bZ0p0bH0p8";
  if(BRtype==12) decay = "tW0p4bZ0p6bH0p0";
  if(BRtype==13) decay = "tW0p4bZ0p4bH0p2";
  if(BRtype==14) decay = "tW0p4bZ0p2bH0p4";
  if(BRtype==15) decay = "tW0p4bZ0p0bH0p6";
  if(BRtype==16) decay = "tW0p6bZ0p4bH0p0";
  if(BRtype==17) decay = "tW0p6bZ0p2bH0p2";
  if(BRtype==18) decay = "tW0p6bZ0p0bH0p4";
  if(BRtype==19) decay = "tW0p8bZ0p2bH0p0";
  if(BRtype==20) decay = "tW0p8bZ0p0bH0p2";
  if(BRtype==21) decay = "tW1p0bZ0p0bH0p0";
  if(BRtype==22) decay = "tW0p0bZ0p5bH0p5";
  std::cout << "Creating new file: " << "BprimeBprime_M-"+mass+"_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root" <<std::endl;
  TFile* fsig = new TFile("BprimeBprime_M-"+mass+"_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root","RECREATE");

  //--------------------which BR
  float BR=0.;
  float BR_tW=0.;
  float BR_bZ=0.;
  float BR_bH=0.;  
  float BR_TWTW = 0;
  float BR_BZBZ = 0;
  float BR_BHBH = 0;
  float BR_BHTW = 0;
  float BR_BZTW = 0;
  float BR_BZBH = 0;

  if(BRtype==0){BR_tW=0.5	;BR_bZ=0.25	;BR_bH=0.25	;} //nominal 
  if(BRtype==1){BR_tW=0.	;BR_bZ=1.0	;BR_bH=0.0	;} // 
  if(BRtype==2){BR_tW=0.	;BR_bZ=0.8	;BR_bH=0.2	;} // 
  if(BRtype==3){BR_tW=0.	;BR_bZ=0.6	;BR_bH=0.4	;} // 
  if(BRtype==4){BR_tW=0.	;BR_bZ=0.4	;BR_bH=0.6	;} // 
  if(BRtype==5){BR_tW=0.	;BR_bZ=0.2	;BR_bH=0.8	;} // 
  if(BRtype==6){BR_tW=0.	;BR_bZ=0.0	;BR_bH=1.0	;} // 
  if(BRtype==7){BR_tW=0.2	;BR_bZ=0.8	;BR_bH=0.0	;} // 
  if(BRtype==8){BR_tW=0.2	;BR_bZ=0.6	;BR_bH=0.2	;} // 
  if(BRtype==9){BR_tW=0.2	;BR_bZ=0.4	;BR_bH=0.4	;} // 
  if(BRtype==10){BR_tW=0.2	;BR_bZ=0.2	;BR_bH=0.6	;} // 
  if(BRtype==11){BR_tW=0.2	;BR_bZ=0.0	;BR_bH=0.8	;} // 
  if(BRtype==12){BR_tW=0.4	;BR_bZ=0.6	;BR_bH=0.0	;} // 
  if(BRtype==13){BR_tW=0.4	;BR_bZ=0.4	;BR_bH=0.2	;} // 
  if(BRtype==14){BR_tW=0.4	;BR_bZ=0.2	;BR_bH=0.4	;} // 
  if(BRtype==15){BR_tW=0.4	;BR_bZ=0.0	;BR_bH=0.6	;} // 
  if(BRtype==16){BR_tW=0.6	;BR_bZ=0.4	;BR_bH=0.0	;} // 
  if(BRtype==17){BR_tW=0.6	;BR_bZ=0.2	;BR_bH=0.2	;} // 
  if(BRtype==18){BR_tW=0.6	;BR_bZ=0.0	;BR_bH=0.4	;} // 
  if(BRtype==19){BR_tW=0.8	;BR_bZ=0.2	;BR_bH=0.0	;} // 
  if(BRtype==20){BR_tW=0.8	;BR_bZ=0.0	;BR_bH=0.2	;} // 
  if(BRtype==21){BR_tW=1.0	;BR_bZ=0.0	;BR_bH=0.0	;} // 
  if(BRtype==22){BR_tW=0.0	;BR_bZ=0.5	;BR_bH=0.5	;} // 
  BR_TWTW = BR_tW*BR_tW;
  BR_BZBZ = BR_bZ*BR_bZ;
  BR_BHBH = BR_bH*BR_bH;
  BR_BHTW = 2*BR_bH*BR_tW;
  BR_BZTW = 2*BR_bZ*BR_tW;
  BR_BZBH = 2*BR_bZ*BR_bH;
    
  std::cout << "Processing signal with BR : tW=" << BR_tW <<" bZ=" << BR_bZ <<" bH=" << BR_bH <<std::endl;


  float initBR; //MC sample initially has equal BR's for T -> tW, bZ,bH
  //BB
  float initBR_TWTW=0.333*0.333;
  float initBR_BZBZ=0.333*0.333;
  float initBR_BHBH=0.333*0.333;
  float initBR_BHTW=0.333*0.333*2;
  float initBR_BZTW=0.333*0.333*2;
  float initBR_BZBH=0.333*0.333*2;
  
  float Xsec = 0.;
  float nEvnts = 0.;

  int NEvts;
  if (mass=="800"){ Xsec = 0.196; NEvts = 795000.;}
  if (mass=="900"){ Xsec = 0.0903; NEvts = 831200.;}
  if (mass=="1000"){ Xsec = 0.0440; NEvts = 829600.;}
  if (mass=="1100"){ Xsec = 0.0224; NEvts = 832800.;}
  if (mass=="1200"){ Xsec = 0.0118; NEvts = 832600.;}
  if (mass=="1300"){ Xsec = 0.00639; NEvts = 831000.;}
  if (mass=="1400"){ Xsec = 0.00354; NEvts = 832600.;}
  if (mass=="1500"){ Xsec = 0.00200; NEvts = 832800.;}
  if (mass=="1600"){ Xsec = 0.001148; NEvts = 832600.;}
  if (mass=="1700"){ Xsec = 0.000666; NEvts = 797000.;}
  if (mass=="1800"){ Xsec = 0.000391; NEvts= 833000.;}
  
  //float lumi = 17.68; //fb^-1  
  float lumi = 18.19; //fb^-1  

  //vector to hold weights
  float Weights_TWTW;
  float Weights_BZBZ;
  float Weights_BHBH;
  float Weights_BHTW;
  float Weights_BZTW;
  float Weights_BZBH;
  Weights_TWTW = lumi * 1000 * ( (Xsec*BR_TWTW) / (NEvts * initBR_TWTW) ) ; //factor of 1000 to convert lumi to pb^-1
  Weights_BZBZ = lumi * 1000 * ( (Xsec*BR_BZBZ) / (NEvts * initBR_BZBZ) ) ; //factor of 1000 to convert lumi to pb^-1
  Weights_BHBH = lumi * 1000 * ( (Xsec*BR_BHBH) / (NEvts * initBR_BHBH) ) ; //factor of 1000 to convert lumi to pb^-1
  Weights_BHTW = lumi * 1000 * ( (Xsec*BR_BHTW) / (NEvts * initBR_BHTW) ) ; //factor of 1000 to convert lumi to pb^-1
  Weights_BZTW = lumi * 1000 * ( (Xsec*BR_BZTW) / (NEvts * initBR_BZTW) ) ; //factor of 1000 to convert lumi to pb^-1
  Weights_BZBH = lumi * 1000 * ( (Xsec*BR_BZBH) / (NEvts * initBR_BZBH) ) ; //factor of 1000 to convert lumi to pb^-1

  //--------------------create new combined histograms
  if(DEBUG)std::cout << "create new combined histograms ..." << std::endl;

  //histogram for pdf uncertainties
  TH2F* hist_pdfHT = new TH2F("hist_pdfHT","PDF Weights",500,0,5,30,0,3000);
  TH2F* pdf_hist = new TH2F("pdf_hist","PDFnew Weights",100,0,100,50,0,5000); //julie added this in Analyzer
  //histogram for scale uncertainties - one for all and then separate ones
  TH2F* hist_scaleHT = new TH2F("hist_scaleHT","MC Scale Uncertainties Combined",500,0,5,30,0,3000);//total
  TH1F* hist_scaleHT_nom = new TH1F("hist_scaleHT_nom","MC Scale Uncertainties ID:Nominal",30,0,3000);//1002
  TH1F* hist_scaleHT_1002 = new TH1F("hist_scaleHT_1002","MC Scale Uncertainties ID:1002",30,0,3000);//1002
  TH1F* hist_scaleHT_1003 = new TH1F("hist_scaleHT_1003","MC Scale Uncertainties ID:1003",30,0,3000);//1003
  TH1F* hist_scaleHT_1004 = new TH1F("hist_scaleHT_1004","MC Scale Uncertainties ID:1004",30,0,3000);//1004
  TH1F* hist_scaleHT_1005 = new TH1F("hist_scaleHT_1005","MC Scale Uncertainties ID:1005",30,0,3000);//1005
  TH1F* hist_scaleHT_1007 = new TH1F("hist_scaleHT_1007","MC Scale Uncertainties ID:1007",30,0,3000);//1007
  TH1F* hist_scaleHT_1009 = new TH1F("hist_scaleHT_1009","MC Scale Uncertainties ID:1009",30,0,3000);//1009
  TH1F* hist_scaleHT_ssdl_nom = new TH1F("hist_scaleHT_ssdl_nom","MC Scale Uncertainties ID:Nominal",30,0,3000);//1002
  TH1F* hist_scaleHT_ssdl_1002 = new TH1F("hist_scaleHT_ssdl_1002","MC Scale Uncertainties ID:1002",30,0,3000);//1002
  TH1F* hist_scaleHT_ssdl_1003 = new TH1F("hist_scaleHT_ssdl_1003","MC Scale Uncertainties ID:1003",30,0,3000);//1003
  TH1F* hist_scaleHT_ssdl_1004 = new TH1F("hist_scaleHT_ssdl_1004","MC Scale Uncertainties ID:1004",30,0,3000);//1004
  TH1F* hist_scaleHT_ssdl_1005 = new TH1F("hist_scaleHT_ssdl_1005","MC Scale Uncertainties ID:1005",30,0,3000);//1005
  TH1F* hist_scaleHT_ssdl_1007 = new TH1F("hist_scaleHT_ssdl_1007","MC Scale Uncertainties ID:1007",30,0,3000);//1007
  TH1F* hist_scaleHT_ssdl_1009 = new TH1F("hist_scaleHT_ssdl_1009","MC Scale Uncertainties ID:1009",30,0,3000);//1009
  //jes JER
  TH1F* hist_nom = new TH1F("hist_nom","nom Uncertainties",1,0,1);
  TH1F* hist_jesup = new TH1F("hist_jesup","jes up Uncertainties",1,0,1);
  TH1F* hist_jesdown = new TH1F("hist_jesdown","jes down Uncertainties",1,0,1);
  TH1F* hist_jerup = new TH1F("hist_jerup","JER up Uncertainties",1,0,1);
  TH1F* hist_jerdown = new TH1F("hist_jerdown","JER down Uncertainties",1,0,1);
  //pileup
  TH1F* hist_punom = new TH1F("hist_punom","PU nom Uncertainties",1,0,1);
  TH1F* hist_puup = new TH1F("hist_puup","PU up Uncertainties",1,0,1);
  TH1F* hist_pudown = new TH1F("hist_pudown","PU down Uncertainties",1,0,1);
  
  //--------------------fetch histograms/trees from individual decay root files, get event numbers maybe create a vector
  if(DEBUG)std::cout << "fetch histograms/trees from individual decay root files ..." << std::endl;
  
  //TWTW
  TH2F* hist_pdfHT_TWTW = (TH2F*) f_TWTW->Get("hist_pdfHT");
  TH2F* pdf_hist_TWTW = (TH2F*) f_TWTW->Get("pdf_hist");
  TH1F* hist_scaleHT_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT");
  TH1F* hist_scaleHT_nom_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_nom");
  TH1F* hist_scaleHT_1002_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_1002");
  TH1F* hist_scaleHT_1003_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_1003");
  TH1F* hist_scaleHT_1004_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_1004");
  TH1F* hist_scaleHT_1005_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_1005");
  TH1F* hist_scaleHT_1007_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_1007");
  TH1F* hist_scaleHT_1009_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_1009");
  TH1F* hist_scaleHT_ssdl_nom_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_ssdl_nom");
  TH1F* hist_scaleHT_ssdl_1002_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_ssdl_1002");
  TH1F* hist_scaleHT_ssdl_1003_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_ssdl_1003");
  TH1F* hist_scaleHT_ssdl_1004_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_ssdl_1004");
  TH1F* hist_scaleHT_ssdl_1005_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_ssdl_1005");
  TH1F* hist_scaleHT_ssdl_1007_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_ssdl_1007");
  TH1F* hist_scaleHT_ssdl_1009_TWTW = (TH1F*)f_TWTW->Get("hist_scaleHT_ssdl_1009");
  TTree* t_TWTW = (TTree*) f_TWTW->Get("tEvts_sZVeto");

  //BZBZ
  TH2F* hist_pdfHT_BZBZ = (TH2F*) f_BZBZ->Get("hist_pdfHT");
  TH2F* pdf_hist_BZBZ = (TH2F*) f_BZBZ->Get("pdf_hist");
  TH1F* hist_scaleHT_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT");
  TH1F* hist_scaleHT_nom_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_nom");
  TH1F* hist_scaleHT_1002_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_1002");
  TH1F* hist_scaleHT_1003_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_1003");
  TH1F* hist_scaleHT_1004_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_1004");
  TH1F* hist_scaleHT_1005_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_1005");
  TH1F* hist_scaleHT_1007_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_1007");
  TH1F* hist_scaleHT_1009_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_1009");
  TH1F* hist_scaleHT_ssdl_nom_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_ssdl_nom");
  TH1F* hist_scaleHT_ssdl_1002_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_ssdl_1002");
  TH1F* hist_scaleHT_ssdl_1003_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_ssdl_1003");
  TH1F* hist_scaleHT_ssdl_1004_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_ssdl_1004");
  TH1F* hist_scaleHT_ssdl_1005_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_ssdl_1005");
  TH1F* hist_scaleHT_ssdl_1007_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_ssdl_1007");
  TH1F* hist_scaleHT_ssdl_1009_BZBZ = (TH1F*)f_BZBZ->Get("hist_scaleHT_ssdl_1009");
  TTree* t_BZBZ = (TTree*) f_BZBZ->Get("tEvts_sZVeto");


  //BHBH
  TH2F* hist_pdfHT_BHBH = (TH2F*) f_BHBH->Get("hist_pdfHT");
  TH2F* pdf_hist_BHBH = (TH2F*) f_BHBH->Get("pdf_hist");
  TH1F* hist_scaleHT_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT");
  TH1F* hist_scaleHT_nom_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_nom");
  TH1F* hist_scaleHT_1002_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_1002");
  TH1F* hist_scaleHT_1003_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_1003");
  TH1F* hist_scaleHT_1004_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_1004");
  TH1F* hist_scaleHT_1005_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_1005");
  TH1F* hist_scaleHT_1007_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_1007");
  TH1F* hist_scaleHT_1009_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_1009");
  TH1F* hist_scaleHT_ssdl_nom_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_ssdl_nom");
  TH1F* hist_scaleHT_ssdl_1002_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_ssdl_1002");
  TH1F* hist_scaleHT_ssdl_1003_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_ssdl_1003");
  TH1F* hist_scaleHT_ssdl_1004_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_ssdl_1004");
  TH1F* hist_scaleHT_ssdl_1005_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_ssdl_1005");
  TH1F* hist_scaleHT_ssdl_1007_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_ssdl_1007");
  TH1F* hist_scaleHT_ssdl_1009_BHBH = (TH1F*)f_BHBH->Get("hist_scaleHT_ssdl_1009");
  TTree* t_BHBH = (TTree*) f_BHBH->Get("tEvts_sZVeto");

  //BHTW
  TH2F* hist_pdfHT_BHTW = (TH2F*) f_BHTW->Get("hist_pdfHT");
  TH2F* pdf_hist_BHTW = (TH2F*) f_BHTW->Get("pdf_hist");
  TH1F* hist_scaleHT_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT");
  TH1F* hist_scaleHT_nom_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_nom");
  TH1F* hist_scaleHT_1002_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_1002");
  TH1F* hist_scaleHT_1003_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_1003");
  TH1F* hist_scaleHT_1004_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_1004");
  TH1F* hist_scaleHT_1005_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_1005");
  TH1F* hist_scaleHT_1007_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_1007");
  TH1F* hist_scaleHT_1009_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_1009");
  TH1F* hist_scaleHT_ssdl_nom_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_ssdl_nom");
  TH1F* hist_scaleHT_ssdl_1002_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_ssdl_1002");
  TH1F* hist_scaleHT_ssdl_1003_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_ssdl_1003");
  TH1F* hist_scaleHT_ssdl_1004_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_ssdl_1004");
  TH1F* hist_scaleHT_ssdl_1005_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_ssdl_1005");
  TH1F* hist_scaleHT_ssdl_1007_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_ssdl_1007");
  TH1F* hist_scaleHT_ssdl_1009_BHTW = (TH1F*)f_BHTW->Get("hist_scaleHT_ssdl_1009");
  TTree* t_BHTW = (TTree*) f_BHTW->Get("tEvts_sZVeto");

  //BZTW
  TH2F* hist_pdfHT_BZTW = (TH2F*) f_BZTW->Get("hist_pdfHT");
  TH2F* pdf_hist_BZTW = (TH2F*) f_BZTW->Get("pdf_hist");
  TH1F* hist_scaleHT_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT");
  TH1F* hist_scaleHT_nom_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_nom");
  TH1F* hist_scaleHT_1002_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_1002");
  TH1F* hist_scaleHT_1003_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_1003");
  TH1F* hist_scaleHT_1004_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_1004");
  TH1F* hist_scaleHT_1005_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_1005");
  TH1F* hist_scaleHT_1007_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_1007");
  TH1F* hist_scaleHT_1009_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_1009");
  TH1F* hist_scaleHT_ssdl_nom_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_ssdl_nom");
  TH1F* hist_scaleHT_ssdl_1002_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_ssdl_1002");
  TH1F* hist_scaleHT_ssdl_1003_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_ssdl_1003");
  TH1F* hist_scaleHT_ssdl_1004_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_ssdl_1004");
  TH1F* hist_scaleHT_ssdl_1005_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_ssdl_1005");
  TH1F* hist_scaleHT_ssdl_1007_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_ssdl_1007");
  TH1F* hist_scaleHT_ssdl_1009_BZTW = (TH1F*)f_BZTW->Get("hist_scaleHT_ssdl_1009");
  TTree* t_BZTW = (TTree*) f_BZTW->Get("tEvts_sZVeto");


  //BZBH
  TH2F* hist_pdfHT_BZBH = (TH2F*) f_BZBH->Get("hist_pdfHT");
  TH2F* pdf_hist_BZBH = (TH2F*) f_BZBH->Get("pdf_hist");
  TH1F* hist_scaleHT_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT");
  TH1F* hist_scaleHT_nom_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_nom");
  TH1F* hist_scaleHT_1002_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_1002");
  TH1F* hist_scaleHT_1003_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_1003");
  TH1F* hist_scaleHT_1004_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_1004");
  TH1F* hist_scaleHT_1005_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_1005");
  TH1F* hist_scaleHT_1007_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_1007");
  TH1F* hist_scaleHT_1009_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_1009");
  TH1F* hist_scaleHT_ssdl_nom_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_ssdl_nom");
  TH1F* hist_scaleHT_ssdl_1002_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_ssdl_1002");
  TH1F* hist_scaleHT_ssdl_1003_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_ssdl_1003");
  TH1F* hist_scaleHT_ssdl_1004_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_ssdl_1004");
  TH1F* hist_scaleHT_ssdl_1005_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_ssdl_1005");
  TH1F* hist_scaleHT_ssdl_1007_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_ssdl_1007");
  TH1F* hist_scaleHT_ssdl_1009_BZBH = (TH1F*)f_BZBH->Get("hist_scaleHT_ssdl_1009");    
  TTree* t_BZBH = (TTree*) f_BZBH->Get("tEvts_sZVeto");


  //--------------------scale histograms
  if(DEBUG)std::cout << "scale histograms ..." << std::endl;
  
  //for jes,jer
//   TString nomcut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
//   TString jesUpcut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleUp > 1200)";
//   TString jesDowncut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleDown > 1200)";
//   TString jerUpcut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearUp > 1200)";
//   TString jerDowncut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearDown > 1200)";

//   TString nomcut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
//   TString jesUpcut = "MCWeight * (Lep1Pt>40 && nConstJESup >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleUp > 1200)";
//   TString jesDowncut = "MCWeight * (Lep1Pt>40 && nConstJESdn >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleDown > 1200)";
//   TString jerUpcut = "MCWeight * (Lep1Pt>40 && nConstJERup >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearUp > 1200)";
//   TString jerDowncut = "MCWeight * (Lep1Pt>40 && nConstJERdn >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearDown > 1200)";

  TString nomcut = "MCWeight * (Lep1Pt>40 && nConst >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
  TString jesUpcut = "MCWeight * (Lep1Pt>40 && nConstJESup >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleUp > 1200)";
  TString jesDowncut = "MCWeight * (Lep1Pt>40 && nConstJESdn >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleDown > 1200)";
  TString jerUpcut = "MCWeight * (Lep1Pt>40 && nConstJERup >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearUp > 1200)";
  TString jerDowncut = "MCWeight * (Lep1Pt>40 && nConstJERdn >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearDown > 1200)";
  
  //for pu
//   TString punomcut =    "PUWeight * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
//   TString puUpcut =   "PUWeightUp * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT> 1200)";
//   TString puDowncut = "PUWeightDown * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";

  TString punomcut =    "PUWeight * MCWeight * (Lep1Pt>40 && nConst >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
  TString puUpcut =   "PUWeightUp * MCWeight * (Lep1Pt>40 && nConst >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT> 1200)";
  TString puDowncut = "PUWeightDown * MCWeight * (Lep1Pt>40 && nConst >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";

  //TWTW
  hist_pdfHT_TWTW->Scale(Weights_TWTW);
  pdf_hist_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_nom_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_1002_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_1003_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_1004_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_1005_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_1007_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_1009_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_ssdl_nom_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_ssdl_1002_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_ssdl_1003_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_ssdl_1004_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_ssdl_1005_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_ssdl_1007_TWTW->Scale(Weights_TWTW);
  hist_scaleHT_ssdl_1009_TWTW->Scale(Weights_TWTW);
  TString wStr_TWTW = std::to_string(Weights_TWTW);
  if(DEBUG)std::cout << "wStr_TWTW: "<< wStr_TWTW <<std::endl;
//   TString nomcut_TWTW = wStr_TWTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
//   TString jesUpcut_TWTW = wStr_TWTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleUp > 1200)";
//   TString jesDowncut_TWTW = wStr_TWTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleDown > 1200)";
//   TString jerUpcut_TWTW = wStr_TWTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearUp > 1200)";
//   TString jerDowncut_TWTW = wStr_TWTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearDown > 1200)";
  float nom_TWTW = getEvents(t_TWTW,nomcut)*Weights_TWTW;
  float jesup_TWTW = getEvents(t_TWTW,jesUpcut)*Weights_TWTW;
  float jesdown_TWTW = getEvents(t_TWTW,jesDowncut)*Weights_TWTW;
  float jerup_TWTW = getEvents(t_TWTW,jerUpcut)*Weights_TWTW;
  float jerdown_TWTW = getEvents(t_TWTW,jerDowncut)*Weights_TWTW;
  if(DEBUG)std::cout << "	nom_TWTW: "<< nom_TWTW <<std::endl;
  if(DEBUG)std::cout << "		jesup_TWTW: "<< jesup_TWTW <<std::endl;
  if(DEBUG)std::cout << "		jesdown_TWTW: "<< jesdown_TWTW <<std::endl;
  if(DEBUG)std::cout << "		jerup_TWTW: "<< jerup_TWTW <<std::endl;
  if(DEBUG)std::cout << "		jerdown_TWTW: "<< jerdown_TWTW <<std::endl;
  float punom_TWTW = getEvents(t_TWTW,punomcut)*Weights_TWTW;
  float puup_TWTW = getEvents(t_TWTW,puUpcut)*Weights_TWTW;
  float pudown_TWTW = getEvents(t_TWTW,puDowncut)*Weights_TWTW;
  if(DEBUG)std::cout << "	punom_TWTW: "<< punom_TWTW <<std::endl;
  if(DEBUG)std::cout << "		puup_TWTW: "<< puup_TWTW <<std::endl;
  if(DEBUG)std::cout << "		pudown_TWTW: "<< pudown_TWTW <<std::endl;

  //BZBZ
  hist_pdfHT_BZBZ->Scale(Weights_BZBZ);
  pdf_hist_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_nom_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_1002_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_1003_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_1004_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_1005_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_1007_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_1009_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_ssdl_nom_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_ssdl_1002_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_ssdl_1003_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_ssdl_1004_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_ssdl_1005_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_ssdl_1007_BZBZ->Scale(Weights_BZBZ);
  hist_scaleHT_ssdl_1009_BZBZ->Scale(Weights_BZBZ);
  TString wStr_BZBZ = std::to_string(Weights_BZBZ);
  if(DEBUG)std::cout << "wStr_BZBZ: "<< wStr_BZBZ <<std::endl;
//   TString nomcut_BZBZ = wStr_BZBZ+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
//   TString jesUpcut_BZBZ = wStr_BZBZ+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleUp > 1200)";
//   TString jesDowncut_BZBZ = wStr_BZBZ+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleDown > 1200)";
//   TString jerUpcut_BZBZ = wStr_BZBZ+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearUp > 1200)";
//   TString jerDowncut_BZBZ = wStr_BZBZ+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearDown > 1200)";
  float nom_BZBZ = getEvents(t_BZBZ,nomcut)*Weights_BZBZ;
  float jesup_BZBZ = getEvents(t_BZBZ,jesUpcut)*Weights_BZBZ;
  float jesdown_BZBZ = getEvents(t_BZBZ,jesDowncut)*Weights_BZBZ;
  float jerup_BZBZ = getEvents(t_BZBZ,jerUpcut)*Weights_BZBZ;
  float jerdown_BZBZ = getEvents(t_BZBZ,jerDowncut)*Weights_BZBZ;
  if(DEBUG)std::cout << "	nom_BZBZ: "<< nom_BZBZ <<std::endl;
  if(DEBUG)std::cout << "		jesup_BZBZ: "<< jesup_BZBZ <<std::endl;
  if(DEBUG)std::cout << "		jesdown_BZBZ: "<< jesdown_BZBZ <<std::endl;
  if(DEBUG)std::cout << "		jerup_BZBZ: "<< jerup_BZBZ <<std::endl;
  if(DEBUG)std::cout << "		jerdown_BZBZ: "<< jerdown_BZBZ <<std::endl;
  float punom_BZBZ = getEvents(t_BZBZ,punomcut)*Weights_BZBZ;
  float puup_BZBZ = getEvents(t_BZBZ,puUpcut)*Weights_BZBZ;
  float pudown_BZBZ = getEvents(t_BZBZ,puDowncut)*Weights_BZBZ;
  if(DEBUG)std::cout << "	punom_BZBZ: "<< punom_BZBZ <<std::endl;
  if(DEBUG)std::cout << "		puup_BZBZ: "<< puup_BZBZ <<std::endl;
  if(DEBUG)std::cout << "		pudown_BZBZ: "<< pudown_BZBZ <<std::endl;

  //BHBH
  hist_pdfHT_BHBH->Scale(Weights_BHBH);
  pdf_hist_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_nom_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_1002_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_1003_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_1004_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_1005_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_1007_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_1009_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_ssdl_nom_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_ssdl_1002_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_ssdl_1003_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_ssdl_1004_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_ssdl_1005_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_ssdl_1007_BHBH->Scale(Weights_BHBH);
  hist_scaleHT_ssdl_1009_BHBH->Scale(Weights_BHBH);
  TString wStr_BHBH = std::to_string(Weights_BHBH);
  if(DEBUG)std::cout << "wStr_BHBH: "<< wStr_BHBH <<std::endl;
//   TString nomcut_BHBH = wStr_BHBH+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
//   TString jesUpcut_BHBH = wStr_BHBH+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleUp > 1200)";
//   TString jesDowncut_BHBH = wStr_BHBH+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleDown > 1200)";
//   TString jerUpcut_BHBH = wStr_BHBH+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearUp > 1200)";
//   TString jerDowncut_BHBH = wStr_BHBH+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearDown > 1200)";
  float nom_BHBH = getEvents(t_BHBH,nomcut)*Weights_BHBH;
  float jesup_BHBH = getEvents(t_BHBH,jesUpcut)*Weights_BHBH;
  float jesdown_BHBH = getEvents(t_BHBH,jesDowncut)*Weights_BHBH;
  float jerup_BHBH = getEvents(t_BHBH,jerUpcut)*Weights_BHBH;
  float jerdown_BHBH = getEvents(t_BHBH,jerDowncut)*Weights_BHBH;
  if(DEBUG)std::cout << "	nom_BHBH: "<< nom_BHBH <<std::endl;
  if(DEBUG)std::cout << "		jesup_BHBH: "<< jesup_BHBH <<std::endl;
  if(DEBUG)std::cout << "		jesdown_BHBH: "<< jesdown_BHBH <<std::endl;
  if(DEBUG)std::cout << "		jerup_BHBH: "<< jerup_BHBH <<std::endl;
  if(DEBUG)std::cout << "		jerdown_BHBH: "<< jerdown_BHBH <<std::endl;
  float punom_BHBH = getEvents(t_BHBH,punomcut)*Weights_BHBH;
  float puup_BHBH = getEvents(t_BHBH,puUpcut)*Weights_BHBH;
  float pudown_BHBH = getEvents(t_BHBH,puDowncut)*Weights_BHBH;
  if(DEBUG)std::cout << "	punom_BHBH: "<< punom_BHBH <<std::endl;
  if(DEBUG)std::cout << "		puup_BHBH: "<< puup_BHBH <<std::endl;
  if(DEBUG)std::cout << "		pudown_BHBH: "<< pudown_BHBH <<std::endl;

  //BHTW
  hist_pdfHT_BHTW->Scale(Weights_BHTW);
  pdf_hist_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_nom_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_1002_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_1003_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_1004_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_1005_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_1007_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_1009_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_ssdl_nom_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_ssdl_1002_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_ssdl_1003_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_ssdl_1004_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_ssdl_1005_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_ssdl_1007_BHTW->Scale(Weights_BHTW);
  hist_scaleHT_ssdl_1009_BHTW->Scale(Weights_BHTW);
  TString wStr_BHTW = std::to_string(Weights_BHTW);
  if(DEBUG)std::cout << "wStr_BHTW: "<< wStr_BHTW <<std::endl;
//   TString nomcut_BHTW = wStr_BHTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
//   TString jesUpcut_BHTW = wStr_BHTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleUp > 1200)";
//   TString jesDowncut_BHTW = wStr_BHTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleDown > 1200)";
//   TString jerUpcut_BHTW = wStr_BHTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearUp > 1200)";
//   TString jerDowncut_BHTW = wStr_BHTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearDown > 1200)";
  float nom_BHTW = getEvents(t_BHTW,nomcut)*Weights_BHTW;
  float jesup_BHTW = getEvents(t_BHTW,jesUpcut)*Weights_BHTW;
  float jesdown_BHTW = getEvents(t_BHTW,jesDowncut)*Weights_BHTW;
  float jerup_BHTW = getEvents(t_BHTW,jerUpcut)*Weights_BHTW;
  float jerdown_BHTW = getEvents(t_BHTW,jerDowncut)*Weights_BHTW;
  if(DEBUG)std::cout << "	nom_BHTW: "<< nom_BHTW <<std::endl;
  if(DEBUG)std::cout << "		jesup_BHTW: "<< jesup_BHTW <<std::endl;
  if(DEBUG)std::cout << "		jesdown_BHTW: "<< jesdown_BHTW <<std::endl;
  if(DEBUG)std::cout << "		jerup_BHTW: "<< jerup_BHTW <<std::endl;
  if(DEBUG)std::cout << "		jerdown_BHTW: "<< jerdown_BHTW <<std::endl;
  float punom_BHTW = getEvents(t_BHTW,punomcut)*Weights_BHTW;
  float puup_BHTW = getEvents(t_BHTW,puUpcut)*Weights_BHTW;
  float pudown_BHTW = getEvents(t_BHTW,puDowncut)*Weights_BHTW;
  if(DEBUG)std::cout << "	punom_BHTW: "<< punom_BHTW <<std::endl;
  if(DEBUG)std::cout << "		puup_BHTW: "<< puup_BHTW <<std::endl;
  if(DEBUG)std::cout << "		pudown_BHTW: "<< pudown_BHTW <<std::endl;

  //BZTW
  hist_pdfHT_BZTW->Scale(Weights_BZTW);
  pdf_hist_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_nom_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_1002_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_1003_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_1004_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_1005_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_1007_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_1009_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_ssdl_nom_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_ssdl_1002_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_ssdl_1003_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_ssdl_1004_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_ssdl_1005_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_ssdl_1007_BZTW->Scale(Weights_BZTW);
  hist_scaleHT_ssdl_1009_BZTW->Scale(Weights_BZTW);
  TString wStr_BZTW = std::to_string(Weights_BZTW);
  if(DEBUG)std::cout << "wStr_BZTW: "<< wStr_BZTW <<std::endl;
//   TString nomcut_BZTW = wStr_BZTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
//   TString jesUpcut_BZTW = wStr_BZTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleUp > 1200)";
//   TString jesDowncut_BZTW = wStr_BZTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleDown > 1200)";
//   TString jerUpcut_BZTW = wStr_BZTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearUp > 1200)";
//   TString jerDowncut_BZTW = wStr_BZTW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearDown > 1200)";
  float nom_BZTW = getEvents(t_BZTW,nomcut)*Weights_BZTW;
  float jesup_BZTW = getEvents(t_BZTW,jesUpcut)*Weights_BZTW;
  float jesdown_BZTW = getEvents(t_BZTW,jesDowncut)*Weights_BZTW;
  float jerup_BZTW = getEvents(t_BZTW,jerUpcut)*Weights_BZTW;
  float jerdown_BZTW = getEvents(t_BZTW,jerDowncut)*Weights_BZTW;
  if(DEBUG)std::cout << "	nom_BZTW: "<< nom_BZTW <<std::endl;
  if(DEBUG)std::cout << "		jesup_BZTW: "<< jesup_BZTW <<std::endl;
  if(DEBUG)std::cout << "		jesdown_BZTW: "<< jesdown_BZTW <<std::endl;
  if(DEBUG)std::cout << "		jerup_BZTW: "<< jerup_BZTW <<std::endl;
  if(DEBUG)std::cout << "		jerdown_BZTW: "<< jerdown_BZTW <<std::endl;
  float punom_BZTW = getEvents(t_BZTW,punomcut)*Weights_BZTW;
  float puup_BZTW = getEvents(t_BZTW,puUpcut)*Weights_BZTW;
  float pudown_BZTW = getEvents(t_BZTW,puDowncut)*Weights_BZTW;
  if(DEBUG)std::cout << "	punom_BZTW: "<< punom_BZTW <<std::endl;
  if(DEBUG)std::cout << "		puup_BZTW: "<< puup_BZTW <<std::endl;
  if(DEBUG)std::cout << "		pudown_BZTW: "<< pudown_BZTW <<std::endl;

  //BZBH
  hist_pdfHT_BZBH->Scale(Weights_BZBH);
  pdf_hist_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_nom_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_1002_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_1003_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_1004_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_1005_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_1007_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_1009_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_ssdl_nom_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_ssdl_1002_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_ssdl_1003_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_ssdl_1004_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_ssdl_1005_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_ssdl_1007_BZBH->Scale(Weights_BZBH);
  hist_scaleHT_ssdl_1009_BZBH->Scale(Weights_BZBH);
  TString wStr_BZBH = std::to_string(Weights_BZBH);
  if(DEBUG)std::cout << "wStr_BZBH: "<< wStr_BZBH <<std::endl;
//   TString nomcut_BZBH = wStr_BZBH+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
//   TString jesUpcut_BZBH = wStr_BZBH+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleUp > 1200)";
//   TString jesDowncut_BZBH = wStr_BZBH+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleDown > 1200)";
//   TString jerUpcut_BZBH = wStr_BZBH+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearUp > 1200)";
//   TString jerDowncut_BZBH = wStr_BZBH+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearDown > 1200)";
  float nom_BZBH = getEvents(t_BZBH,nomcut)*Weights_BZBH;
  float jesup_BZBH = getEvents(t_BZBH,jesUpcut)*Weights_BZBH;
  float jesdown_BZBH = getEvents(t_BZBH,jesDowncut)*Weights_BZBH;
  float jerup_BZBH = getEvents(t_BZBH,jerUpcut)*Weights_BZBH;
  float jerdown_BZBH = getEvents(t_BZBH,jerDowncut)*Weights_BZBH;
  if(DEBUG)std::cout << "	nom_BZBH: "<< nom_BZBH <<std::endl;
  if(DEBUG)std::cout << "		jesup_BZBH: "<< jesup_BZBH <<std::endl;
  if(DEBUG)std::cout << "		jesdown_BZBH: "<< jesdown_BZBH <<std::endl;
  if(DEBUG)std::cout << "		jerup_BZBH: "<< jerup_BZBH <<std::endl;
  if(DEBUG)std::cout << "		jerdown_BZBH: "<< jerdown_BZBH <<std::endl;
  float punom_BZBH = getEvents(t_BZBH,punomcut)*Weights_BZBH;
  float puup_BZBH = getEvents(t_BZBH,puUpcut)*Weights_BZBH;
  float pudown_BZBH = getEvents(t_BZBH,puDowncut)*Weights_BZBH;
  if(DEBUG)std::cout << "	punom_BZBH: "<< punom_BZBH <<std::endl;
  if(DEBUG)std::cout << "		puup_BZBH: "<< puup_BZBH <<std::endl;
  if(DEBUG)std::cout << "		pudown_BZBH: "<< pudown_BZBH <<std::endl;

  //--------------------combine and save
  if(DEBUG)std::cout << "combine and save ..." << std::endl;

  //TWTW
  hist_pdfHT->Add(hist_pdfHT_TWTW);
  pdf_hist->Add(pdf_hist_TWTW);
  hist_scaleHT->Add(hist_scaleHT_TWTW);
  hist_scaleHT_nom->Add(hist_scaleHT_nom_TWTW);
  hist_scaleHT_1002->Add(hist_scaleHT_1002_TWTW);
  hist_scaleHT_1003->Add(hist_scaleHT_1003_TWTW);
  hist_scaleHT_1004->Add(hist_scaleHT_1004_TWTW);
  hist_scaleHT_1005->Add(hist_scaleHT_1005_TWTW);
  hist_scaleHT_1007->Add(hist_scaleHT_1007_TWTW);
  hist_scaleHT_1009->Add(hist_scaleHT_1009_TWTW);
  hist_scaleHT_ssdl_nom->Add(hist_scaleHT_ssdl_nom_TWTW);
  hist_scaleHT_ssdl_1002->Add(hist_scaleHT_ssdl_1002_TWTW);
  hist_scaleHT_ssdl_1003->Add(hist_scaleHT_ssdl_1003_TWTW);
  hist_scaleHT_ssdl_1004->Add(hist_scaleHT_ssdl_1004_TWTW);
  hist_scaleHT_ssdl_1005->Add(hist_scaleHT_ssdl_1005_TWTW);
  hist_scaleHT_ssdl_1007->Add(hist_scaleHT_ssdl_1007_TWTW);
  hist_scaleHT_ssdl_1009->Add(hist_scaleHT_ssdl_1009_TWTW);
  hist_nom->SetBinContent(1,hist_nom->GetBinContent(1)+nom_TWTW);
  hist_jesup->SetBinContent(1,hist_jesup->GetBinContent(1)+jesup_TWTW);
  hist_jesdown->SetBinContent(1,hist_jesdown->GetBinContent(1)+jesdown_TWTW);
  hist_jerup->SetBinContent(1,hist_jerup->GetBinContent(1)+jerup_TWTW);
  hist_jerdown->SetBinContent(1,hist_jerdown->GetBinContent(1)+jerdown_TWTW);
  hist_punom->SetBinContent(1,hist_punom->GetBinContent(1)+punom_TWTW);
  hist_puup->SetBinContent(1,hist_puup->GetBinContent(1)+pudown_TWTW);
  hist_pudown->SetBinContent(1,hist_pudown->GetBinContent(1)+pudown_TWTW);

  //BZBZ
  hist_pdfHT->Add(hist_pdfHT_BZBZ);
  pdf_hist->Add(pdf_hist_BZBZ);
  hist_scaleHT->Add(hist_scaleHT_BZBZ);
  hist_scaleHT_nom->Add(hist_scaleHT_nom_BZBZ);
  hist_scaleHT_1002->Add(hist_scaleHT_1002_BZBZ);
  hist_scaleHT_1003->Add(hist_scaleHT_1003_BZBZ);
  hist_scaleHT_1004->Add(hist_scaleHT_1004_BZBZ);
  hist_scaleHT_1005->Add(hist_scaleHT_1005_BZBZ);
  hist_scaleHT_1007->Add(hist_scaleHT_1007_BZBZ);
  hist_scaleHT_1009->Add(hist_scaleHT_1009_BZBZ);
  hist_scaleHT_ssdl_nom->Add(hist_scaleHT_ssdl_nom_BZBZ);
  hist_scaleHT_ssdl_1002->Add(hist_scaleHT_ssdl_1002_BZBZ);
  hist_scaleHT_ssdl_1003->Add(hist_scaleHT_ssdl_1003_BZBZ);
  hist_scaleHT_ssdl_1004->Add(hist_scaleHT_ssdl_1004_BZBZ);
  hist_scaleHT_ssdl_1005->Add(hist_scaleHT_ssdl_1005_BZBZ);
  hist_scaleHT_ssdl_1007->Add(hist_scaleHT_ssdl_1007_BZBZ);
  hist_scaleHT_ssdl_1009->Add(hist_scaleHT_ssdl_1009_BZBZ);
  hist_nom->SetBinContent(1,hist_nom->GetBinContent(1)+nom_BZBZ);
  hist_jesup->SetBinContent(1,hist_jesup->GetBinContent(1)+jesup_BZBZ);
  hist_jesdown->SetBinContent(1,hist_jesdown->GetBinContent(1)+jesdown_BZBZ);
  hist_jerup->SetBinContent(1,hist_jerup->GetBinContent(1)+jerup_BZBZ);
  hist_jerdown->SetBinContent(1,hist_jerdown->GetBinContent(1)+jerdown_BZBZ);
  hist_punom->SetBinContent(1,hist_punom->GetBinContent(1)+punom_BZBZ);
  hist_puup->SetBinContent(1,hist_puup->GetBinContent(1)+pudown_BZBZ);
  hist_pudown->SetBinContent(1,hist_pudown->GetBinContent(1)+pudown_BZBZ);

  //BHBH
  hist_pdfHT->Add(hist_pdfHT_BHBH);
  pdf_hist->Add(pdf_hist_BHBH);
  hist_scaleHT->Add(hist_scaleHT_BHBH);
  hist_scaleHT_nom->Add(hist_scaleHT_nom_BHBH);
  hist_scaleHT_1002->Add(hist_scaleHT_1002_BHBH);
  hist_scaleHT_1003->Add(hist_scaleHT_1003_BHBH);
  hist_scaleHT_1004->Add(hist_scaleHT_1004_BHBH);
  hist_scaleHT_1005->Add(hist_scaleHT_1005_BHBH);
  hist_scaleHT_1007->Add(hist_scaleHT_1007_BHBH);
  hist_scaleHT_1009->Add(hist_scaleHT_1009_BHBH);
  hist_scaleHT_ssdl_nom->Add(hist_scaleHT_ssdl_nom_BHBH);
  hist_scaleHT_ssdl_1002->Add(hist_scaleHT_ssdl_1002_BHBH);
  hist_scaleHT_ssdl_1003->Add(hist_scaleHT_ssdl_1003_BHBH);
  hist_scaleHT_ssdl_1004->Add(hist_scaleHT_ssdl_1004_BHBH);
  hist_scaleHT_ssdl_1005->Add(hist_scaleHT_ssdl_1005_BHBH);
  hist_scaleHT_ssdl_1007->Add(hist_scaleHT_ssdl_1007_BHBH);
  hist_scaleHT_ssdl_1009->Add(hist_scaleHT_ssdl_1009_BHBH);
  hist_nom->SetBinContent(1,hist_nom->GetBinContent(1)+nom_BHBH);
  hist_jesup->SetBinContent(1,hist_jesup->GetBinContent(1)+jesup_BHBH);
  hist_jesdown->SetBinContent(1,hist_jesdown->GetBinContent(1)+jesdown_BHBH);
  hist_jerup->SetBinContent(1,hist_jerup->GetBinContent(1)+jerup_BHBH);
  hist_jerdown->SetBinContent(1,hist_jerdown->GetBinContent(1)+jerdown_BHBH);
  hist_punom->SetBinContent(1,hist_punom->GetBinContent(1)+punom_BHBH);
  hist_puup->SetBinContent(1,hist_puup->GetBinContent(1)+pudown_BHBH);
  hist_pudown->SetBinContent(1,hist_pudown->GetBinContent(1)+pudown_BHBH);

  //BHTW
  hist_pdfHT->Add(hist_pdfHT_BHTW);
  pdf_hist->Add(pdf_hist_BHTW);
  hist_scaleHT->Add(hist_scaleHT_BHTW);
  hist_scaleHT_nom->Add(hist_scaleHT_nom_BHTW);
  hist_scaleHT_1002->Add(hist_scaleHT_1002_BHTW);
  hist_scaleHT_1003->Add(hist_scaleHT_1003_BHTW);
  hist_scaleHT_1004->Add(hist_scaleHT_1004_BHTW);
  hist_scaleHT_1005->Add(hist_scaleHT_1005_BHTW);
  hist_scaleHT_1007->Add(hist_scaleHT_1007_BHTW);
  hist_scaleHT_1009->Add(hist_scaleHT_1009_BHTW);
  hist_scaleHT_ssdl_nom->Add(hist_scaleHT_ssdl_nom_BHTW);
  hist_scaleHT_ssdl_1002->Add(hist_scaleHT_ssdl_1002_BHTW);
  hist_scaleHT_ssdl_1003->Add(hist_scaleHT_ssdl_1003_BHTW);
  hist_scaleHT_ssdl_1004->Add(hist_scaleHT_ssdl_1004_BHTW);
  hist_scaleHT_ssdl_1005->Add(hist_scaleHT_ssdl_1005_BHTW);
  hist_scaleHT_ssdl_1007->Add(hist_scaleHT_ssdl_1007_BHTW);
  hist_scaleHT_ssdl_1009->Add(hist_scaleHT_ssdl_1009_BHTW);
  hist_nom->SetBinContent(1,hist_nom->GetBinContent(1)+nom_BHTW);
  hist_jesup->SetBinContent(1,hist_jesup->GetBinContent(1)+jesup_BHTW);
  hist_jesdown->SetBinContent(1,hist_jesdown->GetBinContent(1)+jesdown_BHTW);
  hist_jerup->SetBinContent(1,hist_jerup->GetBinContent(1)+jerup_BHTW);
  hist_jerdown->SetBinContent(1,hist_jerdown->GetBinContent(1)+jerdown_BHTW);
  hist_punom->SetBinContent(1,hist_punom->GetBinContent(1)+punom_BHTW);
  hist_puup->SetBinContent(1,hist_puup->GetBinContent(1)+pudown_BHTW);
  hist_pudown->SetBinContent(1,hist_pudown->GetBinContent(1)+pudown_BHTW);

  //BZTW
  hist_pdfHT->Add(hist_pdfHT_BZTW);
  pdf_hist->Add(pdf_hist_BZTW);
  hist_scaleHT->Add(hist_scaleHT_BZTW);
  hist_scaleHT_nom->Add(hist_scaleHT_nom_BZTW);
  hist_scaleHT_1002->Add(hist_scaleHT_1002_BZTW);
  hist_scaleHT_1003->Add(hist_scaleHT_1003_BZTW);
  hist_scaleHT_1004->Add(hist_scaleHT_1004_BZTW);
  hist_scaleHT_1005->Add(hist_scaleHT_1005_BZTW);
  hist_scaleHT_1007->Add(hist_scaleHT_1007_BZTW);
  hist_scaleHT_1009->Add(hist_scaleHT_1009_BZTW);
  hist_scaleHT_ssdl_nom->Add(hist_scaleHT_ssdl_nom_BZTW);
  hist_scaleHT_ssdl_1002->Add(hist_scaleHT_ssdl_1002_BZTW);
  hist_scaleHT_ssdl_1003->Add(hist_scaleHT_ssdl_1003_BZTW);
  hist_scaleHT_ssdl_1004->Add(hist_scaleHT_ssdl_1004_BZTW);
  hist_scaleHT_ssdl_1005->Add(hist_scaleHT_ssdl_1005_BZTW);
  hist_scaleHT_ssdl_1007->Add(hist_scaleHT_ssdl_1007_BZTW);
  hist_scaleHT_ssdl_1009->Add(hist_scaleHT_ssdl_1009_BZTW);
  hist_nom->SetBinContent(1,hist_nom->GetBinContent(1)+nom_BZTW);
  hist_jesup->SetBinContent(1,hist_jesup->GetBinContent(1)+jesup_BZTW);
  hist_jesdown->SetBinContent(1,hist_jesdown->GetBinContent(1)+jesdown_BZTW);
  hist_jerup->SetBinContent(1,hist_jerup->GetBinContent(1)+jerup_BZTW);
  hist_jerdown->SetBinContent(1,hist_jerdown->GetBinContent(1)+jerdown_BZTW);
  hist_punom->SetBinContent(1,hist_punom->GetBinContent(1)+punom_BZTW);
  hist_puup->SetBinContent(1,hist_puup->GetBinContent(1)+pudown_BZTW);
  hist_pudown->SetBinContent(1,hist_pudown->GetBinContent(1)+pudown_BZTW);

  //BZBH
  hist_pdfHT->Add(hist_pdfHT_BZBH);
  pdf_hist->Add(pdf_hist_BZBH);
  hist_scaleHT->Add(hist_scaleHT_BZBH);
  hist_scaleHT_nom->Add(hist_scaleHT_nom_BZBH);
  hist_scaleHT_1002->Add(hist_scaleHT_1002_BZBH);
  hist_scaleHT_1003->Add(hist_scaleHT_1003_BZBH);
  hist_scaleHT_1004->Add(hist_scaleHT_1004_BZBH);
  hist_scaleHT_1005->Add(hist_scaleHT_1005_BZBH);
  hist_scaleHT_1007->Add(hist_scaleHT_1007_BZBH);
  hist_scaleHT_1009->Add(hist_scaleHT_1009_BZBH);
  hist_scaleHT_ssdl_nom->Add(hist_scaleHT_ssdl_nom_BZBH);
  hist_scaleHT_ssdl_1002->Add(hist_scaleHT_ssdl_1002_BZBH);
  hist_scaleHT_ssdl_1003->Add(hist_scaleHT_ssdl_1003_BZBH);
  hist_scaleHT_ssdl_1004->Add(hist_scaleHT_ssdl_1004_BZBH);
  hist_scaleHT_ssdl_1005->Add(hist_scaleHT_ssdl_1005_BZBH);
  hist_scaleHT_ssdl_1007->Add(hist_scaleHT_ssdl_1007_BZBH);
  hist_scaleHT_ssdl_1009->Add(hist_scaleHT_ssdl_1009_BZBH);
  hist_nom->SetBinContent(1,hist_nom->GetBinContent(1)+nom_BZBH);
  hist_jesup->SetBinContent(1,hist_jesup->GetBinContent(1)+jesup_BZBH);
  hist_jesdown->SetBinContent(1,hist_jesdown->GetBinContent(1)+jesdown_BZBH);
  hist_jerup->SetBinContent(1,hist_jerup->GetBinContent(1)+jerup_BZBH);
  hist_jerdown->SetBinContent(1,hist_jerdown->GetBinContent(1)+jerdown_BZBH);
  hist_punom->SetBinContent(1,hist_punom->GetBinContent(1)+punom_BZBH);
  hist_puup->SetBinContent(1,hist_puup->GetBinContent(1)+pudown_BZBH);
  hist_pudown->SetBinContent(1,hist_pudown->GetBinContent(1)+pudown_BZBH);

  if(DEBUG)std::cout << "==================================="<< std::endl;

  if(DEBUG)std::cout << "nom: "<< hist_nom->GetBinContent(1) <<std::endl;
  if(DEBUG)std::cout << "	jesup: "<< hist_jesup->GetBinContent(1) <<std::endl;
  if(DEBUG)std::cout << "	jesdown: "<< hist_jesdown->GetBinContent(1) <<std::endl;
  if(DEBUG)std::cout << "	jerup: "<< hist_jerup->GetBinContent(1) <<std::endl;
  if(DEBUG)std::cout << "	jerdown: "<< hist_jerdown->GetBinContent(1) <<std::endl;
  if(DEBUG)std::cout << "punom: "<< hist_punom->GetBinContent(1) <<std::endl;
  if(DEBUG)std::cout << "	puup: "<< hist_puup->GetBinContent(1) <<std::endl;
  if(DEBUG)std::cout << "	pudown: "<< hist_pudown->GetBinContent(1) <<std::endl;

  
  fsig->Write();
  fsig->Close();
  
  f_TWTW->Close();
  f_BZBZ->Close();
  f_BHBH->Close();
  f_BHTW->Close();
  f_BZTW->Close();
  f_BZBH->Close();

}

void CombineBBsignal(){
	for(int i=0;i<23;i++){
		combinedSignal("800",i);
		combinedSignal("900",i);
		combinedSignal("1000",i);
		combinedSignal("1100",i);
		combinedSignal("1200",i);
		combinedSignal("1300",i);
		combinedSignal("1400",i);
		combinedSignal("1500",i);
		combinedSignal("1600",i);
		combinedSignal("1700",i);
		combinedSignal("1800",i);
	}
	gApplication->Terminate();
}
