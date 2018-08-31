#include <iostream>
#include <iomanip> 
#include <vector>
#include <string>
#include "TString.h"

float getEvents(TTree* t,TString cut){
  TH1F* h = new TH1F("h","h",1,0,1000000);
  t->Project("h","Lep1Pt",cut);  
  float nEvents = h->Integral();
  delete h;

  return nEvents;
}


void printLineMCBkg(std::string sample, TString filename,std::stringstream& filecontent){


//   TString nomcut =    "PUWeight * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
//   TString puUpcut =   "PUWeightUp * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT> 1200)";
//   TString puDowncut = "PUWeightDown * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";

  TString nomcut =    "PUWeight * MCWeight * (Lep1Pt>40 && nConst >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
  TString puUpcut =   "PUWeightUp * MCWeight * (Lep1Pt>40 && nConst >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT> 1200)";
  TString puDowncut = "PUWeightDown * MCWeight * (Lep1Pt>40 && nConst >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";


  TFile* f = new TFile(filename);
  TTree* t = (TTree*) f->Get("tEvts_sZVeto");
  float nom = getEvents(t,nomcut);
  float puup = getEvents(t,puUpcut);
  float puupPct = 1*(puup-nom)/nom;
  float pudown = getEvents(t,puDowncut);
  float pudownPct = 1*(pudown-nom)/nom;
  std::cout<<setprecision(3);
    
  //swap up-dn if necessary
//   float temp;
//   if(puupPct < pudownPct){
//   	temp = puupPct;
//   	puupPct = pudownPct;
//   	pudownPct = temp;
//   }
  std::cout<<sample<<" |  "<<1+puupPct<<" |  "<<1+pudownPct << " ----> "<< fabs(puupPct) << " | "<< fabs(pudownPct) <<std::endl;

  //check in NaN = 0 
  if(puupPct!=puupPct)puupPct=0.;
  if(pudownPct!=pudownPct)pudownPct=0.;

  filecontent<<"puUp['"<< sample << "']="<<1+puupPct<< "\n";
  filecontent<<"puDn['"<< sample << "']="<<1+pudownPct<< "\n";

  delete t; delete f;

}


void printLine(std::string sample, TString filename){


  TFile* f = new TFile(filename);
  TH1D* hnom = (TH1D*)f->Get("hist_punom");
  float nom = hnom->Integral();

  TH1D* hpuup = (TH1D*)f->Get("hist_puup");
  float puup = hpuup->Integral();
  float puupPct = 100*(puup-nom)/nom;

  TH1D* hpudown = (TH1D*)f->Get("hist_pudown");
  float pudown = hpudown->Integral();
  float pudownPct = 100*(pudown-nom)/nom;
  std::cout<<setprecision(2);
  std::cout<<sample<<" |  "<<puupPct<<" |  "<<pudownPct<<std::endl;
  
  f->Close();
  delete f;

}


void pileupSys_rizki(){
  TString folder ="/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/X53ThirteenTeVAnalysisCode/scripts/Systematics/CombineTTsig";

  TString decay;
  /*
  for(int BRtype=0;BRtype<23;BRtype++){

	  if(BRtype==0) decay = "bW0p5tZ0p25tH0p25";
	  if(BRtype==1) decay = "bW0p0tZ1p0tH0p0";
	  if(BRtype==2) decay = "bW0p0tZ0p8tH0p2";
	  if(BRtype==3) decay = "bW0p0tZ0p6tH0p4";
	  if(BRtype==4) decay = "bW0p0tZ0p4tH0p6";
	  if(BRtype==5) decay = "bW0p0tZ0p2tH0p8";
	  if(BRtype==6) decay = "bW0p0tZ0p0tH0p0";
	  if(BRtype==7) decay = "bW0p2tZ0p8tH0p0";
	  if(BRtype==8) decay = "bW0p2tZ0p6tH0p2";
	  if(BRtype==9) decay = "bW0p2tZ0p4tH0p4";
	  if(BRtype==10) decay = "bW0p2tZ0p2tH0p6";
	  if(BRtype==11) decay = "bW0p2tZ0p0tH0p8";
	  if(BRtype==12) decay = "bW0p4tZ0p6tH0p0";
	  if(BRtype==13) decay = "bW0p4tZ0p4tH0p2";
	  if(BRtype==14) decay = "bW0p4tZ0p2tH0p4";
	  if(BRtype==15) decay = "bW0p4tZ0p0tH0p6";
	  if(BRtype==16) decay = "bW0p6tZ0p4tH0p0";
	  if(BRtype==17) decay = "bW0p6tZ0p2tH0p2";
	  if(BRtype==18) decay = "bW0p6tZ0p0tH0p4";
	  if(BRtype==19) decay = "bW0p8tZ0p2tH0p0";
	  if(BRtype==20) decay = "bW0p8tZ0p0tH0p2";
	  if(BRtype==21) decay = "bW1p0tZ0p0tH0p0";
	  if(BRtype==22) decay = "bW0p0tZ0p5tH0p5";

	  //print top line
	  std::cout<<" Sample | PU Up | PU Down"<<std::endl;
	  printLine("800 ",folder+"/TprimeTprime_M-800_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  printLine("900 ",folder+"/TprimeTprime_M-900_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  printLine("1000 ",folder+"/TprimeTprime_M-1000_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  printLine("1100 ",folder+"/TprimeTprime_M-1100_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  printLine("1200 ",folder+"/TprimeTprime_M-1200_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  printLine("1300 ",folder+"/TprimeTprime_M-1300_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  printLine("1400 ",folder+"/TprimeTprime_M-1400_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  printLine("1500 ",folder+"/TprimeTprime_M-1500_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  printLine("1600 ",folder+"/TprimeTprime_M-1600_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  printLine("1700 ",folder+"/TprimeTprime_M-1700_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  
  }
  */

  ///----------MC Bkg-------

//   TString MCfolder ="/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/X53ThirteenTeVAnalysisCode/test/ProcessedByJulie_Oct18-2017/test/";
  TString MCfolder ="/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/X53ThirteenTeVAnalysisCode/test/ProcessedByJulie_Oct20-2017/test/";

  std::ofstream outfile;
  outfile.open("unc_pu_MCBkg.py");

  std::stringstream filecontent;
  filecontent<<std::fixed<<std::setprecision(3);
  
  filecontent<< "puUp = {} \n";
  filecontent<< "puDn = {} \n";

  std::cout<<" ==========MC Bkg==========="<<std::endl;
  std::cout<<" Sample | PU Up | PU Down "<<std::endl;
  
  printLineMCBkg("TTZ",MCfolder+"/TTZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
  printLineMCBkg("TTW",MCfolder+"/TTW_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
  printLineMCBkg("TTH",MCfolder+"/TTH_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
  printLineMCBkg("TTTT",MCfolder+"/TTTT_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
  printLineMCBkg("WZ",MCfolder+"/WZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
  printLineMCBkg("ZZ",MCfolder+"/ZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
  printLineMCBkg("WpWp",MCfolder+"/WpWp_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
  printLineMCBkg("WWZ",MCfolder+"/WWZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
  printLineMCBkg("WZZ",MCfolder+"/WZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
  printLineMCBkg("ZZZ",MCfolder+"/ZZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);

  outfile<<filecontent.str();
  outfile.close();


  gApplication->Terminate();
	  
}
