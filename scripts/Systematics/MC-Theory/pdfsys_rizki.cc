#include "TFile.h"
#include "TH2F.h"
#include "TH1.h"

bool useOriginalRange = false; //default is false

void getPDFUnc(TFile* f, TString name, TString decay,std::stringstream& filecontent){

  TH2F* h2 = (TH2F*) f->Get("hist_pdfHT");
  TH1D* h1 = new TH1D("h1","pdf",500,0,5);
  h2->ProjectionX("h1",11,30);

  float pdfSFsUp=1.0;
  float pdfSFsDn=1.0;

  if(useOriginalRange){
	//SF Julie derived if using Clints method  --- PDF RMS in 0, 5 --- 
	  if(name=="TTM800") pdfSFsUp = 0.798069;
	  if(name=="TTM900") pdfSFsUp = 0.786429;
	  if(name=="TTM1000") pdfSFsUp = 0.774264;
	  if(name=="TTM1100") pdfSFsUp = 0.761961;
	  if(name=="TTM1200") pdfSFsUp = 0.748426;
	  if(name=="TTM1300") pdfSFsUp = 0.734362;
	  if(name=="TTM1400") pdfSFsUp = 0.720017;
	  if(name=="TTM1500") pdfSFsUp = 0.704827;
	  if(name=="TTM1600") pdfSFsUp = 0.689221;
	  if(name=="TTM1700") pdfSFsUp = 0.672887;
	  if(name=="TTM1800") pdfSFsUp = 0.656809;

	  if(name=="TTM800") pdfSFsDn = 1.338733;
	  if(name=="TTM900") pdfSFsDn = 1.372817;
	  if(name=="TTM1000") pdfSFsDn = 1.411532;
	  if(name=="TTM1100") pdfSFsDn = 1.454339;
	  if(name=="TTM1200") pdfSFsDn = 1.506336;
	  if(name=="TTM1300") pdfSFsDn = 1.566725;
	  if(name=="TTM1400") pdfSFsDn = 1.636275;
	  if(name=="TTM1500") pdfSFsDn = 1.720541;
	  if(name=="TTM1600") pdfSFsDn = 1.821209;
	  if(name=="TTM1700") pdfSFsDn = 1.946031;
	  if(name=="TTM1800") pdfSFsDn = 2.094295;

	//SF Julie derived if using Clints method  --- PDF RMS in 0, 5 ---  
	  if(name=="BBM800") pdfSFsUp = 0.798745;
	  if(name=="BBM900") pdfSFsUp = 0.786365;
	  if(name=="BBM1000") pdfSFsUp = 0.773535;
	  if(name=="BBM1100") pdfSFsUp = 0.761371;
	  if(name=="BBM1200") pdfSFsUp = 0.748495;
	  if(name=="BBM1300") pdfSFsUp = 0.734677;
	  if(name=="BBM1400") pdfSFsUp = 0.720374;
	  if(name=="BBM1500") pdfSFsUp = 0.704064;
	  if(name=="BBM1600") pdfSFsUp = 0.688932;
	  if(name=="BBM1700") pdfSFsUp =  0.673248;
	  if(name=="BBM1800") pdfSFsUp = 0.656805;

	  if(name=="BBM800") pdfSFsDn = 1.336834;
	  if(name=="BBM900") pdfSFsDn = 1.373013;
	  if(name=="BBM1000") pdfSFsDn = 1.413961;
	  if(name=="BBM1100") pdfSFsDn = 1.456496;
	  if(name=="BBM1200") pdfSFsDn = 1.506057;
	  if(name=="BBM1300") pdfSFsDn = 1.565293;
	  if(name=="BBM1400") pdfSFsDn = 1.634435;
	  if(name=="BBM1500") pdfSFsDn = 1.725108;
	  if(name=="BBM1600") pdfSFsDn = 1.823229;
	  if(name=="BBM1700") pdfSFsDn = 1.943021;
	  if(name=="BBM1800") pdfSFsDn = 2.094334;
  }
  else{
	//SF Julie derived if using Clints method --- PDF RMS in 0.01, 2 --- 
	  if(name=="TTM800") pdfSFsUp = 0.842791;
	  if(name=="TTM900") pdfSFsUp = 0.836231;
	  if(name=="TTM1000") pdfSFsUp = 0.829966;
	  if(name=="TTM1100") pdfSFsUp = 0.824169;
	  if(name=="TTM1200") pdfSFsUp = 0.818264;
	  if(name=="TTM1300") pdfSFsUp = 0.812751;
	  if(name=="TTM1400") pdfSFsUp = 0.807161;
	  if(name=="TTM1500") pdfSFsUp = 0.801396;
	  if(name=="TTM1600") pdfSFsUp = 0.795429;
	  if(name=="TTM1700") pdfSFsUp = 0.788703;
	  if(name=="TTM1800") pdfSFsUp = 0.781770;

	  if(name=="TTM800") pdfSFsDn = 1.229307;
	  if(name=="TTM900") pdfSFsDn = 1.243537;
	  if(name=="TTM1000") pdfSFsDn = 1.257654;
	  if(name=="TTM1100") pdfSFsDn = 1.271203;
	  if(name=="TTM1200") pdfSFsDn = 1.285511;
	  if(name=="TTM1300") pdfSFsDn = 1.299359;
	  if(name=="TTM1400") pdfSFsDn = 1.313906;
	  if(name=="TTM1500") pdfSFsDn = 1.329473;
	  if(name=="TTM1600") pdfSFsDn = 1.346226;
	  if(name=="TTM1700") pdfSFsDn = 1.365941;
	  if(name=="TTM1800") pdfSFsDn = 1.387249;

	//SF Julie derived if using Clints method --- PDF RMS in 0.01, 2 --- 
	  if(name=="BBM800") pdfSFsUp = 0.842987;
	  if(name=="BBM900") pdfSFsUp = 0.836350;
	  if(name=="BBM1000") pdfSFsUp = 0.829989;
	  if(name=="BBM1100") pdfSFsUp = 0.823996;
	  if(name=="BBM1200") pdfSFsUp = 0.818278;
	  if(name=="BBM1300") pdfSFsUp = 0.812737;
	  if(name=="BBM1400") pdfSFsUp = 0.807308;
	  if(name=="BBM1500") pdfSFsUp = 0.801195;
	  if(name=="BBM1600") pdfSFsUp = 0.795491;
	  if(name=="BBM1700") pdfSFsUp = 0.788745;
	  if(name=="BBM1800") pdfSFsUp = 0.781682;

	  if(name=="BBM800") pdfSFsDn = 1.228891;
	  if(name=="BBM900") pdfSFsDn = 1.243274;
	  if(name=="BBM1000") pdfSFsDn = 1.257600;
	  if(name=="BBM1100") pdfSFsDn = 1.271614;
	  if(name=="BBM1200") pdfSFsDn = 1.285477;
	  if(name=="BBM1300") pdfSFsDn = 1.299394;
	  if(name=="BBM1400") pdfSFsDn = 1.313517;
	  if(name=="BBM1500") pdfSFsDn = 1.330028;
	  if(name=="BBM1600") pdfSFsDn = 1.346050;
	  if(name=="BBM1700") pdfSFsDn = 1.365815;
	  if(name=="BBM1800") pdfSFsDn = 1.387525;
  
	  h1->GetXaxis()->SetRange(2,200);
  }

  float RMSup   = ( 1+h1->GetRMS() ) * pdfSFsUp ;
  float RMSdown = ( 1-h1->GetRMS() ) * pdfSFsDn ;

//   float RMSup   = ( ( (1+h1->GetRMS() ) * pdfSFsUp) *100;
//   float RMSdown = ( ( (1-h1->GetRMS() ) * pdfSFsDn) *100;
//   float RMSup = (h1->GetRMS())*100;
//   float RMSdown = (h1->GetRMS())*100;


//   std::cout<<"PDF Uncertainty for: "<<name<<" is "<<h1->GetRMS()<<std::endl;
  std::cout<<setprecision(4);
  std::cout<<name<<" | "<< RMSup <<" |" << RMSdown << " "<<std::endl;
    
  //swap Up-Dn if necessary
  float temp;
  if(RMSup < RMSdown){
  	temp = RMSup;
  	RMSup = RMSdown;
  	RMSdown = temp;
  }
  filecontent<<"pdfUp['"<< name << "']="<<RMSup<< "\n";
  filecontent<<"pdfDn['"<< name << "']="<<RMSdown<< "\n";

  
//   TString fname = name+"_"+decay+"_PDFSys.pdf";
// 
//   TCanvas* c = new TCanvas();
//   h1->Draw();
//   c->Print(fname);

  delete h2;
  delete h1;
    

};

void getPDFUncYQM(TFile* f, TString name, TString decay,std::stringstream& filecontent){

  float pdfSFsUp=1.0;
  float pdfSFsDn=1.0;

// SF Julie uses (Yield Quantiles method SF) 
  if(name=="TTM800") pdfSFsUp = 0.908;
  if(name=="TTM900") pdfSFsUp = 0.902;
  if(name=="TTM1000") pdfSFsUp = 0.890;
  if(name=="TTM1100") pdfSFsUp = 0.889;
  if(name=="TTM1200") pdfSFsUp = 0.895;
  if(name=="TTM1300") pdfSFsUp = 0.895;
  if(name=="TTM1400") pdfSFsUp = 0.888;
  if(name=="TTM1500") pdfSFsUp = 0.897;
  if(name=="TTM1600") pdfSFsUp = 0.905;
  if(name=="TTM1700") pdfSFsUp = 0.885;
  if(name=="TTM1800") pdfSFsUp = 0.872;

  if(name=="TTM800") pdfSFsDn = 1.106;
  if(name=="TTM900") pdfSFsDn = 1.104;
  if(name=="TTM1000") pdfSFsDn = 1.099;
  if(name=="TTM1100") pdfSFsDn = 1.099;
  if(name=="TTM1200") pdfSFsDn = 1.093;
  if(name=="TTM1300") pdfSFsDn = 1.098;
  if(name=="TTM1400") pdfSFsDn = 1.102;
  if(name=="TTM1500") pdfSFsDn = 1.099;
  if(name=="TTM1600") pdfSFsDn = 1.122;
  if(name=="TTM1700") pdfSFsDn = 1.121;
  if(name=="TTM1800") pdfSFsDn = 1.133;

  if(name=="BBM800") pdfSFsUp = 0.908650;
  if(name=="BBM900") pdfSFsUp = 0.902838;
  if(name=="BBM1000") pdfSFsUp = 0.889160;
  if(name=="BBM1100") pdfSFsUp = 0.889035;
  if(name=="BBM1200") pdfSFsUp = 0.895234;
  if(name=="BBM1300") pdfSFsUp = 0.895267;
  if(name=="BBM1400") pdfSFsUp = 0.889021;
  if(name=="BBM1500") pdfSFsUp = 0.896896;
  if(name=="BBM1600") pdfSFsUp = 0.903131;
  if(name=="BBM1700") pdfSFsUp = 0.884259;
  if(name=="BBM1800") pdfSFsUp = 0.872146;

  if(name=="BBM800") pdfSFsDn = 1.105800;
  if(name=="BBM900") pdfSFsDn = 1.103726;
  if(name=="BBM1000") pdfSFsDn = 1.099539;
  if(name=="BBM1100") pdfSFsDn = 1.099161;
  if(name=="BBM1200") pdfSFsDn = 1.092635;
  if(name=="BBM1300") pdfSFsDn = 1.097083;
  if(name=="BBM1400") pdfSFsDn = 1.102208;
  if(name=="BBM1500") pdfSFsDn = 1.098160;
  if(name=="BBM1600") pdfSFsDn = 1.120596;
  if(name=="BBM1700") pdfSFsDn = 1.122464;
  if(name=="BBM1800") pdfSFsDn = 1.131872;


  TH2F* h2 = (TH2F*) f->Get("pdf_hist");
  TH1D* h1 = new TH1D("h1","pdf",101,0,101);
  h2->ProjectionX("h1",13,50);

  std::vector<double> pdfvar;

  for( int i = 0; i < 100; i++){
     pdfvar.push_back(h1->GetBinContent(i+1));
  }
  // if you need nominal from this hist:
  float nom = h1->GetBinContent(101);
//   std::cout << "	h1->GetBinContent(101):" << h1->GetBinContent(101) <<std::endl;
  
  std::sort(pdfvar.begin(),pdfvar.end());
  float yieldpdfup = pdfvar[83];
//   std::cout << "	pdfvar[83]:" << pdfvar[83] << std::endl;
  float yieldpdfdn = pdfvar[15];
//   std::cout << "	pdfvar[15]:" << pdfvar[15] <<std::endl;

//   float pctpdfup = 1*(yieldpdfup-nom)/nom;
//   float pctpdfdn = 1*(yieldpdfdn-nom)/nom;
//   float pdfup = (1+pctpdfup) *pdfSFsUp;
//   float pdfdn = (1+pctpdfdn) *pdfSFsDn;

  float pctpdfup = 1*((yieldpdfup*pdfSFsUp)-nom)/nom;
  float pctpdfdn = 1*((yieldpdfdn*pdfSFsDn)-nom)/nom;
  float pdfup = (1+pctpdfup) ;
  float pdfdn = (1+pctpdfdn) ;


//   std::cout<<"PDF Uncertainty for: "<<name<<" is "<<h1->GetRMS()<<std::endl;
  std::cout<<setprecision(4);
  std::cout<<name<<" | "<< pdfup <<" |" << pdfdn << " ----> "<< fabs(1-pdfup) << " | "<< fabs(1-pdfdn) << std::endl;
    
  //swap Up-Dn if necessary
//   float temp;
//   if(pdfup < pdfdn){
//   	temp = pdfup;
//   	pdfup = pdfdn;
//   	pdfdn = temp;
//   }
  filecontent<<"pdfUp['"<< name << "']="<<pdfup<< "\n";
  filecontent<<"pdfDn['"<< name << "']="<<pdfdn<< "\n";

  
//   TString fname = name+"_"+decay+"_PDFSys.pdf";
// 
//   TCanvas* c = new TCanvas();
//   h1->Draw();
//   c->Print(fname);

  delete h2;
  delete h1;
    

};

void pdfsys_rizki(){

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
	  outfile.open("unc_pdf_TT_"+decay+".py");

	  std::stringstream filecontent;
	  filecontent<<std::fixed<<std::setprecision(3);
	  
// 	  filecontent<< "pdfUp = {} \n";
// 	  filecontent<< "pdfDn = {} \n";

  
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
	  TFile* TTM1800 = new TFile(folder+"/TprimeTprime_M-1800_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");

	  std::cout<<" =========="+decay+"==========="<<std::endl;
// 	  std::cout<<" Sample | RMSup*SF | RMSdown*SF "<<std::endl;
	  std::cout<<" Sample | up | down "<<std::endl;
	  

	  getPDFUncYQM(TTM800,"TTM800",decay,filecontent);
	  getPDFUncYQM(TTM900,"TTM900",decay,filecontent);
	  getPDFUncYQM(TTM1000,"TTM1000",decay,filecontent);
	  getPDFUncYQM(TTM1100,"TTM1100",decay,filecontent);
	  getPDFUncYQM(TTM1200,"TTM1200",decay,filecontent);
	  getPDFUncYQM(TTM1300,"TTM1300",decay,filecontent);
	  getPDFUncYQM(TTM1400,"TTM1400",decay,filecontent);
	  getPDFUncYQM(TTM1500,"TTM1500",decay,filecontent);
	  getPDFUncYQM(TTM1600,"TTM1600",decay,filecontent);
	  getPDFUncYQM(TTM1700,"TTM1700",decay,filecontent);
	  getPDFUncYQM(TTM1800,"TTM1800",decay,filecontent);

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
	  outfile.open("unc_pdf_BB_"+decay+".py");

	  std::stringstream filecontent;
	  filecontent<<std::fixed<<std::setprecision(3);
	  
// 	  filecontent<< "pdfUp = {} \n";
// 	  filecontent<< "pdfDn = {} \n";
  
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
	  TFile* BBM1800 = new TFile(folder+"/BprimeBprime_M-1800_"+decay+"_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");

	  std::cout<<" =========="+decay+"==========="<<std::endl;
// 	  std::cout<<" Sample | RMSup*SF | RMSdown*SF "<<std::endl;
	  std::cout<<" Sample | up | down "<<std::endl;

	  getPDFUncYQM(BBM800,"BBM800",decay,filecontent);
	  getPDFUncYQM(BBM900,"BBM900",decay,filecontent);
	  getPDFUncYQM(BBM1000,"BBM1000",decay,filecontent);
	  getPDFUncYQM(BBM1100,"BBM1100",decay,filecontent);
	  getPDFUncYQM(BBM1200,"BBM1200",decay,filecontent);
	  getPDFUncYQM(BBM1300,"BBM1300",decay,filecontent);
	  getPDFUncYQM(BBM1400,"BBM1400",decay,filecontent);
	  getPDFUncYQM(BBM1500,"BBM1500",decay,filecontent);
	  getPDFUncYQM(BBM1600,"BBM1600",decay,filecontent);
	  getPDFUncYQM(BBM1700,"BBM1700",decay,filecontent);
	  getPDFUncYQM(BBM1800,"BBM1800",decay,filecontent);

	  outfile<<filecontent.str();
	  outfile.close();

  }

  ///----------MC Bkg-------

//   TString MCfolder ="/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/X53ThirteenTeVAnalysisCode/test/ProcessedByJulie_Oct18-2017/test/";
  TString MCfolder ="/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/X53ThirteenTeVAnalysisCode/test/ProcessedByJulie_Oct20-2017/test/";

  std::ofstream outfile;
  outfile.open("unc_pdf_MCBkg.py");

  std::stringstream filecontent;
  filecontent<<std::fixed<<std::setprecision(3);
  
  filecontent<< "pdfUp = {} \n";
  filecontent<< "pdfDn = {} \n";

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
  
  getPDFUncYQM(TTZ,"TTZ","",filecontent);
  getPDFUncYQM(TTW,"TTW","",filecontent);
  getPDFUncYQM(TTH,"TTH","",filecontent);
  getPDFUncYQM(TTTT,"TTTT","",filecontent);
  getPDFUncYQM(WZ,"WZ","",filecontent);
  getPDFUncYQM(ZZ,"ZZ","",filecontent);
  getPDFUncYQM(WpWp,"WpWp","",filecontent);
  getPDFUncYQM(WWZ,"WWZ","",filecontent);
  getPDFUncYQM(WZZ,"WZZ","",filecontent);
  getPDFUncYQM(ZZZ,"ZZZ","",filecontent);

  outfile<<filecontent.str();
  outfile.close();

  ///----------MC Bkg------- done

  
  system("cat unc_pdf_MCBkg.py unc_pdf_TT_bW0p5tZ0p25tH0p25.py > unc_pdf_MCBkg_TT_bW0p5tZ0p25tH0p25.py");
  system("cat unc_pdf_MCBkg.py unc_pdf_TT_bW0p0tZ0p5tH0p5.py > unc_pdf_MCBkg_TT_bW0p0tZ0p5tH0p5.py");
  system("cat unc_pdf_MCBkg.py unc_pdf_TT_bW0p0tZ1p0tH0p0.py > unc_pdf_MCBkg_TT_bW0p0tZ1p0tH0p0.py");
  
  gApplication->Terminate();


}
