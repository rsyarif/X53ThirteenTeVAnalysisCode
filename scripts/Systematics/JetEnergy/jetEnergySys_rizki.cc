#include <iostream>
#include <iomanip> 
#include <vector>
#include <string>
#include "TString.h"

bool DEBUG = true;

float maxJesShift = 0.;
float maxJerShift = 0.;

float meanJesShift = 0.;
float meanJerShift = 0.;


float getEvents(TTree* t,TString cut){
  float nEvents = t->Draw("Lep1Pt",cut);
  return nEvents;
}


void printLineMCBkg(std::string sample, TString filename,std::stringstream& filecontent){


//   TString nomcut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
//   TString jesUpcut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleUp > 1200)";
//   TString jesDowncut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleDown > 1200)";
//   TString jerUpcut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearUp > 1200)";
//   TString jerDowncut = "MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearDown > 1200)";

  TString nomcut = "MCWeight * (Lep1Pt>40 && nConst >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
  TString jesUpcut = "MCWeight * (Lep1Pt>40 && nConstJESup >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleUp > 1200)";
  TString jesDowncut = "MCWeight * (Lep1Pt>40 && nConstJESdn >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTScaleDown > 1200)";
  TString jerUpcut = "MCWeight * (Lep1Pt>40 && nConstJERup >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearUp > 1200)";
  TString jerDowncut = "MCWeight * (Lep1Pt>40 && nConstJERdn >=4 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HTSmearDown > 1200)";


  TFile* f = new TFile(filename);
  TTree* t = (TTree*) f->Get("tEvts_sZVeto");

  float nom = getEvents(t,nomcut);
  std::cout<< "nom : " << nom <<std::endl;

  float jesup = getEvents(t,jesUpcut);
  std::cout<< "jesup : " << jesup <<std::endl;
  float jesupPct = 1*(jesup-nom)/nom;

  float jesdown = getEvents(t,jesDowncut);
  std::cout<< "jesdown : " << jesdown <<std::endl;
  float jesdownPct = 1*(jesdown-nom)/nom;

  float jerup = getEvents(t,jerUpcut);
  std::cout<< "jerup : " << jerup <<std::endl;
  float jerupPct = 1*(jerup-nom)/nom;

  float jerdown = getEvents(t,jerDowncut);
  std::cout<< "jerdown : " << jerdown <<std::endl;
  float jerdownPct = 1*(jerdown-nom)/nom;

  std::cout<<setprecision(3);
  std::cout<<sample<<" |  "<<1+jesupPct<<" |  "<<1+jesdownPct<<" |  "<<1+jerupPct<<" |  "<<1+jerdownPct << " ----> "<< fabs(jesupPct) << " | "<< fabs(jesdownPct)<< " | "<< fabs(jerupPct) << " | "<< fabs(jerdownPct) <<std::endl;
  
  //check in NaN = 0 
  if(jesupPct!=jesupPct)jesupPct=0.;
  if(jesdownPct!=jesdownPct)jesdownPct=0.;
  if(jerupPct!=jerupPct)jerupPct=0.;
  if(jerdownPct!=jerdownPct)jerdownPct=0.;

  filecontent<<"jecUp['"<< sample << "']="<<1+jesupPct<< "\n";
  filecontent<<"jecDn['"<< sample << "']="<<1+jesdownPct<< "\n";
  filecontent<<"jerUp['"<< sample << "']="<<1+jerupPct<< "\n";
  filecontent<<"jerDn['"<< sample << "']="<<1+jerdownPct<< "\n";

  delete t; delete f;

}


void printLine(std::string sample, TString filename,std::stringstream& filecontent){


  TFile* f = new TFile(filename);
  if(DEBUG)std::cout << "Opening :"<< filename<< std::endl;

  TH1D* hnom = (TH1D*)f->Get("hist_nom");
  float nom = hnom->Integral();
  if(DEBUG) std::cout<< "nom : " << nom <<std::endl;
 
  TH1D* hjesup = (TH1D*)f->Get("hist_jesup");
  float jesup = hjesup->Integral();
  if(DEBUG) std::cout<< "jesup : " << jesup <<std::endl;
  float jesupPct = 1*(jesup-nom)/nom;
 
  TH1D* hjesdown = (TH1D*)f->Get("hist_jesdown");
  float jesdown = hjesdown->Integral();
  if(DEBUG) std::cout<< "jesdown : " << jesdown <<std::endl;
  float jesdownPct = 1*(jesdown-nom)/nom;
 
  TH1D* hjerup = (TH1D*)f->Get("hist_jerup");
  float jerup = hjerup->Integral();
  if(DEBUG) std::cout<< "jerup : " << jerup <<std::endl;
  float jerupPct = 1*(jerup-nom)/nom;
 
  TH1D* hjerdown = (TH1D*)f->Get("hist_jerdown");
  float jerdown = hjerdown->Integral();
  if(DEBUG) std::cout<< "jerdown : " << jerdown <<std::endl;
  float jerdownPct = 1*(jerdown-nom)/nom;
  std::cout<<setprecision(3);
//   std::cout<<sample<<" |  "<<jesupPct<<" |  "<<jesdownPct<<" |  "<<jerupPct<<" |  "<<jerdownPct<<std::endl;
  std::cout<<sample<<" |  "<<1+jesupPct<<" |  "<<1+jesdownPct<<" |  "<<1+jerupPct<<" |  "<<1+jerdownPct<<std::endl;
  filecontent<<"jecUp['"<< sample << "']="<<1+jesupPct<< "\n";
  filecontent<<"jecDn['"<< sample << "']="<<1+jesdownPct<< "\n";
  filecontent<<"jerUp['"<< sample << "']="<<1+jerupPct<< "\n";
  filecontent<<"jerDn['"<< sample << "']="<<1+jerdownPct<< "\n";

  if(maxJesShift < 1+fabs(jesupPct) ) maxJesShift = 1+fabs(jesupPct);
  if(maxJesShift < 1+fabs(jesdownPct) ) maxJesShift = 1+fabs(jesdownPct);
  if(maxJerShift < 1+fabs(jesupPct) ) maxJerShift = 1+fabs(jerupPct);
  if(maxJerShift < 1+fabs(jerdownPct) ) maxJerShift = 1+fabs(jerdownPct);
  
  meanJesShift = meanJesShift+ (1+fabs(jesupPct));
  meanJesShift = meanJesShift+ (1+fabs(jesdownPct));
  meanJerShift = meanJerShift+ (1+fabs(jerupPct));
  meanJerShift = meanJerShift+ (1+fabs(jerdownPct));

  delete hnom;
  delete hjesup;
  delete hjesdown;
  delete hjerup;
  delete hjerdown;
  f->Close();
  delete f;

}


void jetEnergySys_rizki(){

  TString folder ="/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/X53ThirteenTeVAnalysisCode/scripts/Systematics/CombineTTsig";

  TString decay;
  
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

	  std::ofstream outfile;
	  outfile.open("unc_jec_jer_TT_"+decay+".py");

	  std::stringstream filecontent;
	  filecontent<<std::fixed<<std::setprecision(3);
	  
// 	  filecontent<< "jecUp = {} \n";
// 	  filecontent<< "jecDn = {} \n";
// 	  filecontent<< "jerUp = {} \n";
// 	  filecontent<< "jerDn = {} \n";

	  //print top line
	  std::cout<<" =========="+decay+"==========="<<std::endl;
	  std::cout<<" Sample | JES Up | JES Down | JER Up | JER Down"<<std::endl;
  
	  printLine("TTM800",folder+"/TprimeTprime_M-800_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("TTM900",folder+"/TprimeTprime_M-900_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("TTM1000",folder+"/TprimeTprime_M-1000_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("TTM1100",folder+"/TprimeTprime_M-1100_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("TTM1200",folder+"/TprimeTprime_M-1200_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("TTM1300",folder+"/TprimeTprime_M-1300_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("TTM1400",folder+"/TprimeTprime_M-1400_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("TTM1500",folder+"/TprimeTprime_M-1500_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("TTM1600",folder+"/TprimeTprime_M-1600_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("TTM1700",folder+"/TprimeTprime_M-1700_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);

	  outfile<<filecontent.str();
	  outfile.close();
  
  }

  for(int BRtype=0;BRtype<23;BRtype++){

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

	  std::ofstream outfile;
	  outfile.open("unc_jec_jer_BB_"+decay+".py");

	  std::stringstream filecontent;
	  filecontent<<std::fixed<<std::setprecision(3);
	  
// 	  filecontent<< "jecUp = {} \n";
// 	  filecontent<< "jecDn = {} \n";
// 	  filecontent<< "jerUp = {} \n";
// 	  filecontent<< "jerDn = {} \n";

	  //print top line
	  std::cout<<" =========="+decay+"==========="<<std::endl;
	  std::cout<<" Sample | JES Up | JES Down | JER Up | JER Down"<<std::endl;
  
	  printLine("BBM800",folder+"/BprimeBprime_M-800_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("BBM900",folder+"/BprimeBprime_M-900_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("BBM1000",folder+"/BprimeBprime_M-1000_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("BBM1100",folder+"/BprimeBprime_M-1100_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("BBM1200",folder+"/BprimeBprime_M-1200_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("BBM1300",folder+"/BprimeBprime_M-1300_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("BBM1400",folder+"/BprimeBprime_M-1400_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("BBM1500",folder+"/BprimeBprime_M-1500_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("BBM1600",folder+"/BprimeBprime_M-1600_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
	  printLine("BBM1700",folder+"/BprimeBprime_M-1700_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root",filecontent);
  
	  outfile<<filecontent.str();
	  outfile.close();

  }
  

  std::cout<<"\n"<<std::endl;

  std::cout<<" ====================="<<std::endl;
  std::cout<<" max JES  | max JER "<<std::endl;
  std::cout<< maxJesShift <<" | " << maxJerShift<<std::endl;
  
  float totalShifts = (10 * 23 + 10 * 23) * 2 ;// (TT*BR + BB*BR) * up/down
  std::cout<<" ====================="<<std::endl;
  std::cout<<" mean JES  | mean JER "<<std::endl;
  std::cout<< meanJesShift / totalShifts <<" | " << meanJerShift / totalShifts <<std::endl;
  
  
  ///----------MC Bkg-------

  TString MCfolder ="/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/X53ThirteenTeVAnalysisCode/test/ProcessedByJulie_Oct18-2017/test/";

  std::ofstream outfile;
  outfile.open("unc_jec_jer_MCBkg.py");

  std::stringstream filecontent;
  filecontent<<std::fixed<<std::setprecision(3);
  
  filecontent<< "jecUp = {} \n";
  filecontent<< "jecDn = {} \n";
  filecontent<< "jerUp = {} \n";
  filecontent<< "jerDn = {} \n";

  std::cout<<" ==========MC Bkg==========="<<std::endl;
  std::cout<<" Sample | JES Up | JES Down | JER Up | JER Down"<<std::endl;
  
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

  ///----------MC Bkg------- done
  
  system("cat unc_jec_jer_MCBkg.py unc_jec_jer_TT_bW0p5tZ0p25tH0p25.py > unc_jec_jer_MCBkg_TT_bW0p5tZ0p25tH0p25.py");
  system("cat unc_jec_jer_MCBkg.py unc_jec_jer_TT_bW0p0tZ0p5tH0p5.py > unc_jec_jer_MCBkg_TT_bW0p0tZ0p5tH0p5.py");
  system("cat unc_jec_jer_MCBkg.py unc_jec_jer_TT_bW0p0tZ1p0tH0p0.py > unc_jec_jer_MCBkg_TT_bW0p0tZ1p0tH0p0.py");

  
  gApplication->Terminate();

}
