#include "TFile.h"
#include "TH1.h"
#include <vector>
#include "../../../plugins/Macros.cc" //added by rizki

float roundME(float num){
	rounded = roundf(num * 1000) / 1000;
	return rounded;
}


void printSys(TFile* f,std::string name,std::stringstream& filecontent){

  TH1F* h1 = (TH1F*)f->Get("hist_scaleHT_1002");
  TH1F* h2 = (TH1F*)f->Get("hist_scaleHT_1003");
  TH1F* h3 = (TH1F*)f->Get("hist_scaleHT_1004");
  TH1F* h4 = (TH1F*)f->Get("hist_scaleHT_1005");
  TH1F* h5 = (TH1F*)f->Get("hist_scaleHT_1007");
  TH1F* h6 = (TH1F*)f->Get("hist_scaleHT_1009");

  TH1F* h_nom = (TH1F*) f->Get("hist_scaleHT_nom");
  float nom = h_nom->Integral(1,h_nom->GetNbinsX()+1);
  //std::cout<<"nominal number is: "<<nom<<std::endl;

for(unsigned int j=0; j<h1->GetNbinsX();j++){
  //std::cout<<"bin: "<<j+1<<" lower edge is: "<<h1->GetXaxis()->GetBinLowEdge(j+1)<<std::endl;
  }

  TH1F* h1_ssdl = (TH1F*)f->Get("hist_scaleHT_ssdl_1002");
  TH1F* h2_ssdl = (TH1F*)f->Get("hist_scaleHT_ssdl_1003");
  TH1F* h3_ssdl = (TH1F*)f->Get("hist_scaleHT_ssdl_1004");
  TH1F* h4_ssdl = (TH1F*)f->Get("hist_scaleHT_ssdl_1005");
  TH1F* h5_ssdl = (TH1F*)f->Get("hist_scaleHT_ssdl_1007");
  TH1F* h6_ssdl = (TH1F*)f->Get("hist_scaleHT_ssdl_1009");

  TH1F* h_nom_ssdl = (TH1F*) f->Get("hist_scaleHT_ssdl_nom");
  float nom_ssdl = h_nom_ssdl->Integral(1,h_nom_ssdl->GetNbinsX()+1);
  //std::cout<<"nominal ssdl number is: "<<nom_ssdl<<std::endl;
  

  std::vector<TH1F*> hists; hists.push_back(h1);hists.push_back(h2);hists.push_back(h3);hists.push_back(h4);hists.push_back(h5);hists.push_back(h6);
  std::vector<TH1F*> hists_ssdl; hists_ssdl.push_back(h1_ssdl);hists_ssdl.push_back(h2_ssdl);hists_ssdl.push_back(h3_ssdl);hists_ssdl.push_back(h4_ssdl);hists_ssdl.push_back(h5_ssdl);hists_ssdl.push_back(h6_ssdl);

//SF Julie derived if using Clints method
  float scaleSFsUp = 1.0;
  if(name=="TTM800") scaleSFsUp = 0.749925;
  if(name=="TTM900") scaleSFsUp = 0.749763;
  if(name=="TTM1000") scaleSFsUp = 0.749456;
  if(name=="TTM1100") scaleSFsUp = 0.748919;
  if(name=="TTM1200") scaleSFsUp = 0.748155;
  if(name=="TTM1300") scaleSFsUp = 0.747285;
  if(name=="TTM1400") scaleSFsUp = 0.746257;
  if(name=="TTM1500") scaleSFsUp = 0.745124;
  if(name=="TTM1600") scaleSFsUp = 0.743910;
  if(name=="TTM1700") scaleSFsUp = 0.742651;
  if(name=="TTM1800") scaleSFsUp = 0.741467;
  float scaleSFsDn = 1.0;
  if(name=="TTM800") scaleSFsDn = 1.302659;
  if(name=="TTM900") scaleSFsDn = 1.303236;
  if(name=="TTM1000") scaleSFsDn = 1.304089;
  if(name=="TTM1100") scaleSFsDn = 1.305306;
  if(name=="TTM1200") scaleSFsDn = 1.306860;
  if(name=="TTM1300") scaleSFsDn = 1.308596;
  if(name=="TTM1400") scaleSFsDn = 1.310591;
  if(name=="TTM1500") scaleSFsDn = 1.312745;
  if(name=="TTM1600") scaleSFsDn = 1.315014;
  if(name=="TTM1700") scaleSFsDn = 1.317327;
  if(name=="TTM1800") scaleSFsDn = 1.319497;

//SF Julie derived if using Clints method
  if(name=="BBM800") scaleSFsUp = 0.749985;
  if(name=="BBM900") scaleSFsUp = 0.749807;
  if(name=="BBM1000") scaleSFsUp = 0.749466;
  if(name=="BBM1100") scaleSFsUp = 0.748883;
  if(name=="BBM1200") scaleSFsUp = 0.748188;
  if(name=="BBM1300") scaleSFsUp = 0.747302;
  if(name=="BBM1400") scaleSFsUp = 0.746291;
  if(name=="BBM1500") scaleSFsUp = 0.745112;
  if(name=="BBM1600") scaleSFsUp = 0.743952;
  if(name=="BBM1700") scaleSFsUp = 0.742689;
  if(name=="BBM1800") scaleSFsUp = 0.741456;

  if(name=="BBM800") scaleSFsDn = 1.302567;
  if(name=="BBM900") scaleSFsDn = 1.303173;
  if(name=="BBM1000") scaleSFsDn = 1.304071;
  if(name=="BBM1100") scaleSFsDn = 1.305358;
  if(name=="BBM1200") scaleSFsDn = 1.306815;
  if(name=="BBM1300") scaleSFsDn = 1.308569;
  if(name=="BBM1400") scaleSFsDn = 1.310540;
  if(name=="BBM1500") scaleSFsDn = 1.312759;
  if(name=="BBM1600") scaleSFsDn = 1.314953;
  if(name=="BBM1700") scaleSFsDn = 1.317273;
  if(name=="BBM1800") scaleSFsDn = 1.319518;

  float nom_full = h_nom->Integral(13,h_nom->GetNbinsX()+1);
  //std::cout<< "nom_full : " << nom_full <<std::endl;
  float maxdiff=0;
  float mindiff=0;
  for(unsigned int i=0; i<hists.size();i++){
    float tot = hists.at(i)->Integral(13,hists.at(i)->GetNbinsX()+1);
  	//std::cout<< "tot : " << tot <<std::endl;
    float percentdiff = 1*( (tot-nom_full) / nom_full);
    if( percentdiff > maxdiff) maxdiff=percentdiff;
    if( percentdiff < mindiff) mindiff=percentdiff;
    //std::cout<<percentdiff<<std::endl;
  }
//   std::cout<<"**************Running uncertainty for: ****************"<<name<<std::endl;
//   std::cout<<"for full analysis cut: "<<maxdiff<<std::endl;
//   std::cout<< name <<" | "<< maxdiff <<" | " << mindiff << std::endl;
//   std::cout.precision(3);
//   std::cout<< name <<" | "<<  roundME(1+maxdiff) <<" | " << roundME(1+mindiff)  << std::endl;

  float scaleUp = (1+maxdiff)*scaleSFsUp;
  float scaleDn = (1+mindiff)*scaleSFsDn;

  std::cout<< name <<" | "<<  roundME( scaleUp ) <<" | " << roundME( scaleDn )  << " ----> "<< fabs(1-scaleUp) << " | "<< fabs(1-scaleDn)  << std::endl;

  //swap Up-Dn if necessary
//   float temp;
//   if(scaleUp < scaleDn){
//   	temp = scaleUp;
//   	scaleUp = scaleDn;
//   	scaleDn = temp;
//   }
  filecontent<<"scaleUp['"<< name << "']="<<scaleUp<< "\n";
  filecontent<<"scaleDn['"<< name << "']="<<scaleDn<< "\n";
	

  maxdiff=0;

  for(unsigned int i=0; i<hists.size();i++){
    float tot = hists.at(i)->Integral(1,hists.at(i)->GetNbinsX()+1);
    float percentdiff = 100*( (tot-nom) / nom);
    if(fabs(percentdiff) > maxdiff) maxdiff=percentdiff;
  }
  //std::cout<<"for nconst  cut: "<<maxdiff<<std::endl;  

  maxdiff=0;
  for(unsigned int i=0; i<hists_ssdl.size();i++){
    float tot = hists_ssdl.at(i)->Integral(1,hists_ssdl.at(i)->GetNbinsX()+1);
    float percentdiff = 100*( (tot-nom_ssdl) / nom_ssdl);
    if(fabs(percentdiff) > maxdiff) maxdiff=percentdiff;
  }
  //std::cout<<"Now for just ssdl cut: "<<maxdiff<<"\n";  
  //std::cout<<"\n\n";  

}


void scale_sys_rizki(){


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
	  outfile.open("unc_scale_TT_"+decay+".py");

	  std::stringstream filecontent;
	  filecontent<<std::fixed<<std::setprecision(3);
	  
// 	  filecontent<< "scaleUp = {} \n";
// 	  filecontent<< "scaleDn = {} \n";

  
	  TFile* TTM800 = new TFile(folder+"/TprimeTprime_M-800_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* TTM900 = new TFile(folder+"/TprimeTprime_M-900_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* TTM1000 = new TFile(folder+"/TprimeTprime_M-1000_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* TTM1100 = new TFile(folder+"/TprimeTprime_M-1100_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* TTM1200 = new TFile(folder+"/TprimeTprime_M-1200_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* TTM1300 = new TFile(folder+"/TprimeTprime_M-1300_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* TTM1400 = new TFile(folder+"/TprimeTprime_M-1400_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* TTM1500 = new TFile(folder+"/TprimeTprime_M-1500_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* TTM1600 = new TFile(folder+"/TprimeTprime_M-1600_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* TTM1700 = new TFile(folder+"/TprimeTprime_M-1700_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");

	  std::cout<<" =========="+decay+"==========="<<std::endl;
	  std::cout<<" Sample | up | down "<<std::endl;

	  printSys(TTM800,"TTM800",filecontent);
	  printSys(TTM900,"TTM900",filecontent);
	  printSys(TTM1000,"TTM1000",filecontent);
	  printSys(TTM1100,"TTM1100",filecontent);
	  printSys(TTM1200,"TTM1200",filecontent);
	  printSys(TTM1300,"TTM1300",filecontent);
	  printSys(TTM1400,"TTM1400",filecontent);
	  printSys(TTM1500,"TTM1500",filecontent);
	  printSys(TTM1600,"TTM1600",filecontent);
	  printSys(TTM1700,"TTM1700",filecontent);

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
	  outfile.open("unc_scale_BB_"+decay+".py");

	  std::stringstream filecontent;
	  filecontent<<std::fixed<<std::setprecision(3);
	  
// 	  filecontent<< "scaleUp = {} \n";
// 	  filecontent<< "scaleDn = {} \n";


	  TFile* BBM800 = new TFile(folder+"/BprimeBprime_M-800_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* BBM900 = new TFile(folder+"/BprimeBprime_M-900_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* BBM1000 = new TFile(folder+"/BprimeBprime_M-1000_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* BBM1100 = new TFile(folder+"/BprimeBprime_M-1100_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* BBM1200 = new TFile(folder+"/BprimeBprime_M-1200_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* BBM1300 = new TFile(folder+"/BprimeBprime_M-1300_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* BBM1400 = new TFile(folder+"/BprimeBprime_M-1400_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* BBM1500 = new TFile(folder+"/BprimeBprime_M-1500_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* BBM1600 = new TFile(folder+"/BprimeBprime_M-1600_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
	  TFile* BBM1700 = new TFile(folder+"/BprimeBprime_M-1700_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");

	  std::cout<<" =========="+decay+"==========="<<std::endl;
	  std::cout<<" Sample | up | down "<<std::endl;

	  printSys(BBM800,"BBM800",filecontent);
	  printSys(BBM900,"BBM900",filecontent);
	  printSys(BBM1000,"BBM1000",filecontent);
	  printSys(BBM1100,"BBM1100",filecontent);
	  printSys(BBM1200,"BBM1200",filecontent);
	  printSys(BBM1300,"BBM1300",filecontent);
	  printSys(BBM1400,"BBM1400",filecontent);
	  printSys(BBM1500,"BBM1500",filecontent);
	  printSys(BBM1600,"BBM1600",filecontent);
	  printSys(BBM1700,"BBM1700",filecontent);

	  outfile<<filecontent.str();
	  outfile.close();

  }
  

  ///----------MC Bkg-------

  TString MCfolder ="/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/X53ThirteenTeVAnalysisCode/test/ProcessedByJulie_Oct18-2017/test/";

  std::ofstream outfile;
  outfile.open("unc_scale_MCBkg.py");

  std::stringstream filecontent;
  filecontent<<std::fixed<<std::setprecision(3);
  
  filecontent<< "scaleUp = {} \n";
  filecontent<< "scaleDn = {} \n";

  TFile* TTZ = new TFile(MCfolder+"/TTZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* TTW = new TFile(MCfolder+"/TTW_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* TTH = new TFile(MCfolder+"/TTH_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* TTTT = new TFile(MCfolder+"/TTTT_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* WZ = new TFile(MCfolder+"/WZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* ZZ = new TFile(MCfolder+"/ZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* WpWp = new TFile(MCfolder+"/WpWp_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* WWZ = new TFile(MCfolder+"/WWZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* WZZ = new TFile(MCfolder+"/WZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* ZZZ = new TFile(MCfolder+"/ZZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");

  std::cout<<" ==========MC Bkg==========="<<std::endl;
// 	  std::cout<<" Sample | RMSup*SF | RMSdown*SF "<<std::endl;
  std::cout<<" Sample | up | down "<<std::endl;
  
  printSys(TTZ,"TTZ",filecontent);
  printSys(TTW,"TTW",filecontent);
  printSys(TTH,"TTH",filecontent);
  printSys(TTTT,"TTTT",filecontent);
  printSys(WZ,"WZ",filecontent);
  printSys(ZZ,"ZZ",filecontent);
  printSys(WpWp,"WpWp",filecontent);
  printSys(WWZ,"WWZ",filecontent);
  printSys(WZZ,"WZZ",filecontent);
  printSys(ZZZ,"ZZZ",filecontent);

  outfile<<filecontent.str();
  outfile.close();

  ///----------MC Bkg------- done
  
  system("cat unc_scale_MCBkg.py unc_scale_TT_bW0p5tZ0p25tH0p25.py > unc_scale_MCBkg_TT_bW0p5tZ0p25tH0p25.py");
  system("cat unc_scale_MCBkg.py unc_scale_TT_bW0p0tZ0p5tH0p5.py > unc_scale_MCBkg_TT_bW0p0tZ0p5tH0p5.py");
  system("cat unc_scale_MCBkg.py unc_scale_TT_bW0p0tZ1p0tH0p0.py > unc_scale_MCBkg_TT_bW0p0tZ1p0tH0p0.py");

	
  gApplication->Terminate();

}
