#include "TFile.h"
#include "TH2F.h"
#include "TH1.h"

void getPDFUnc(TFile* f, std::string name){

  TH2F* h2 = (TH2F*) f->Get("hist_pdfHT");
  TH1D* h1 = new TH1D("h1","pdf",500,0,5);
  h2->ProjectionX("h1",11,30);

  std::cout<<"PDF Uncertainty for: "<<name<<" is "<<h1->GetRMS()<<std::endl;

  std::string fname = name+"_PDFSys.pdf";

  TCanvas* c = new TCanvas();
  h1->Draw();
  c->Print(fname.c_str());
    

};

void pdfsys(){

  TString folder = "/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/X53ThirteenTeVAnalysisCode/test";

  TFile* fttz = new TFile(folder+"/TTZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* fttw = new TFile(folder+"/TTW_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* ftth = new TFile(folder+"/TTH_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* fwz = new TFile(folder+"/WZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* fzz = new TFile(folder+"/ZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");

  TH2F* httz = (TH2F*) fttz->Get("hist_pdfHT");
  TH2F* httw = (TH2F*) fttw->Get("hist_pdfHT");
  TH2F* htth = (TH2F*) ftth->Get("hist_pdfHT");
  TH2F* hwz = (TH2F*) fwz->Get("hist_pdfHT");
  TH2F* hzz = (TH2F*) fzz->Get("hist_pdfHT");
  
  TCanvas cttz;
  httz->Draw("colz");
  cttz.Print("ttz-2d.pdf");
  TCanvas cttw;
  httw->Draw("colz");
  cttw.Print("ttw-2D.pdf");

  TCanvas ctth;
  htth->Draw("colz");
  ctth.Print("tth-2D.pdf");
  
  /*

  TFile* lh700 = new TFile("X53X53m700LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* lh800 = new TFile("X53X53m800LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* lh900 = new TFile("X53X53m900LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* lh1000 = new TFile("X53X53m1000LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* lh1100 = new TFile("X53X53m1100LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* lh1200 = new TFile("X53X53m1200LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* lh1300 = new TFile("X53X53m1300LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* lh1400 = new TFile("X53X53m1400LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* lh1500 = new TFile("X53X53m1500LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* lh1600 = new TFile("X53X53m1600LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");


  getPDFUnc(lh700,"LH_700");
  getPDFUnc(lh800,"LH_800");
  getPDFUnc(lh900,"LH_900");
  getPDFUnc(lh1000,"LH_1000");
  getPDFUnc(lh1100,"LH_1100");
  getPDFUnc(lh1200,"LH_1200");
  getPDFUnc(lh1300,"LH_1300");
  getPDFUnc(lh1400,"LH_1400");
  getPDFUnc(lh1500,"LH_1500");
  getPDFUnc(lh1600,"LH_1600");

  TFile* rh700 = new TFile("X53X53m700RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* rh800 = new TFile("X53X53m800RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* rh900 = new TFile("X53X53m900RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* rh1000 = new TFile("X53X53m1000RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* rh1100 = new TFile("X53X53m1100RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* rh1200 = new TFile("X53X53m1200RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* rh1300 = new TFile("X53X53m1300RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* rh1400 = new TFile("X53X53m1400RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* rh1500 = new TFile("X53X53m1500RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");
  TFile* rh1600 = new TFile("X53X53m1600RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC.root");


   getPDFUnc(rh700,"RH_700");
  getPDFUnc(rh800,"RH_800");
  getPDFUnc(rh900,"RH_900");
  getPDFUnc(rh1000,"RH_1000");
  getPDFUnc(rh1100,"RH_1100");
  getPDFUnc(rh1200,"RH_1200");
  getPDFUnc(rh1300,"RH_1300");
  getPDFUnc(rh1400,"RH_1400");
  getPDFUnc(rh1500,"RH_1500");
  getPDFUnc(rh1600,"RH_1600");
  */


  TH1D* hsysttz = new TH1D("hsysttz","PDF Weights in Signal Region TTZ",500,0,5);
  httz->ProjectionX("hsysttz",11,30);
  TH1D* hsysttw = new TH1D("hsysttw","PDF Weights in Signal Region TTW",500,0,5);
  httw->ProjectionX("hsysttw",11,30);
  TH1D* hsystth = new TH1D("hsystth","PDF Weights in Signal Region TTH",500,0,5);
  htth->ProjectionX("hsystth",11,30);
  TH1D* hsyswz = new TH1D("hsyswz","PDF Weights in Signal Region WZ",500,0,5);
  hwz->ProjectionX("hsyswz",11,30);
  TH1D* hsyszz = new TH1D("hsyszz","PDF Weights in Signal Region ZZ",500,0,5);
  hzz->ProjectionX("hsyszz",11,30);


  std::cout<<"pdf uncert for ttz: "<<hsysttz->GetRMS()<<std::endl;
  std::cout<<"pdf uncert for ttw: "<<hsysttw->GetRMS()<<std::endl;
  std::cout<<"pdf uncert for tth: "<<hsystth->GetRMS()<<std::endl;
  std::cout<<"pdf uncert for wz: "<<hsyswz->GetRMS()<<std::endl;
  std::cout<<"pdf uncert for zz: "<<hsyszz->GetRMS()<<std::endl;

  TCanvas c;
  // hsysttz->SetLineColor(kRed);
  hsysttz->GetXaxis()->SetRangeUser(0,1.5);
  hsysttz->Draw();
 
  c.Print("pdfsys_ttz.pdf");
  hsysttw->GetXaxis()->SetRangeUser(0,1.5);  
  hsysttw->Draw();

  c.Print("pdfsys_ttw.pdf");

  hsystth->GetXaxis()->SetRangeUser(0,1.5);  
  hsystth->Draw();

  c.Print("pdfsys_tth.pdf");
  
  //added by rizki - start
  std::ofstream outfile;
  outfile.open("unc_pdf_MCBkg.py");
  std::stringstream filecontent;
  filecontent<<std::fixed<<std::setprecision(3);
  filecontent<< "pdfUp = {} \n";
  filecontent<< "pdfDn = {} \n";
  filecontent<<"pdfUp['TTZ']="<<hsysttz->GetRMS()<< "\n";
  filecontent<<"pdfDn['TTZ']="<<hsysttz->GetRMS()<< "\n";
  filecontent<<"pdfUp['TTW']="<<hsysttw->GetRMS()<< "\n";
  filecontent<<"pdfDn['TTW']="<<hsysttw->GetRMS()<< "\n";
  filecontent<<"pdfUp['TTH']="<<hsystth->GetRMS()<< "\n";
  filecontent<<"pdfDn['TTH']="<<hsystth->GetRMS()<< "\n";
  filecontent<<"pdfUp['WZ']="<<hsyswz->GetRMS()<< "\n";
  filecontent<<"pdfDn['WZ']="<<hsyswz->GetRMS()<< "\n";
  filecontent<<"pdfUp['ZZ']="<<hsyszz->GetRMS()<< "\n";
  filecontent<<"pdfDn['ZZ']="<<hsyszz->GetRMS()<< "\n";
  outfile<<filecontent.str();
  outfile.close();
  //added by rizki - end


  /*
  TH2F* httz = (TH2F*) fttz->Get("hist_pdfHT");
  TH2F* httw = (TH2F*) fttw->Get("hist_pdfHT");
  TH2F* htth = (TH2F*) fttw->Get("hist_pdfHT");
  
  TCanvas cttz;
  httz->Draw("colz");
  cttz.Print("ttz-2d.pdf");
  TCanvas cttw;
  httw->Draw("colz");
  cttw.Print("ttw-2D.pdf");

  TCanvas ctth;
  htth->Draw("colz");
  ctth.Print("tth-2D.pdf");

  delete httz; delete httw; delete hsysttz; delete hsysttw;

  TH2F* httz = (TH2F*) fttz->Get("hist_scaleHT");
  TH2F* httw = (TH2F*) fttw->Get("hist_scaleHT");
  

  TH1D* hsysttz = new TH1D("hsysttz","SCALE Weights in Signal Region TTZ",500,0,5);
  httz->ProjectionX("hsysttz",1,30);
  TH1D* hsysttw = new TH1D("hsysttw","SCALE Weights in Signal Region TTW",500,0,5);
  httw->ProjectionX("hsysttw",1,30);

  TCanvas c;

  std::cout<<"scale uncert for ttz: "<<hsysttz->GetRMS()<<std::endl;
  std::cout<<"scale uncert for ttw: "<<hsysttw->GetRMS()<<std::endl;

  // hsysttz->SetLineColor(kRed);
  hsysttz->GetXaxis()->SetRangeUser(0,1.5);
  hsysttz->Draw();
 
  c.Print("scalesys_ttz.pdf");
  hsysttw->GetXaxis()->SetRangeUser(0,1.5);  
  hsysttw->Draw();

  c.Print("scalesys_ttw.pdf");


  delete httz; delete httw; delete hsysttz; delete hsysttw;

  TH2F* httz = (TH2F*) fttz->Get("hist_scaleHT_1002");
  TH2F* httw = (TH2F*) fttw->Get("hist_scaleHT_1002");
  

  TH1D* hsysttz = new TH1D("hsysttz","SCALE Weights in Signal Region TTZ",500,0,5);
  httz->ProjectionX("hsysttz",1,30);
  TH1D* hsysttw = new TH1D("hsysttw","SCALE Weights in Signal Region TTW",500,0,5);
  httw->ProjectionX("hsysttw",1,30);

  TCanvas c;

  std::cout<<"scale uncert for ttz: "<<hsysttz->GetRMS()<<std::endl;
  std::cout<<"scale uncert for ttw: "<<hsysttw->GetRMS()<<std::endl;

  // hsysttz->SetLineColor(kRed);
  hsysttz->GetXaxis()->SetRangeUser(0,1.5);
  hsysttz->Draw();
 
  c.Print("scalesys_ttz_1002.pdf");
  hsysttw->GetXaxis()->SetRangeUser(0,1.5);  
  hsysttw->Draw();

  c.Print("scalesys_ttw_1002.pdf");

  delete hsysttz; delete hsysttw; delete hsysttz; delete hsysttw;

  TH2F* httz = (TH2F*) fttz->Get("hist_scaleHT_1003");
  TH2F* httw = (TH2F*) fttw->Get("hist_scaleHT_1003");
  

  TH1D* hsysttz = new TH1D("hsysttz","SCALE Weights in Signal Region TTZ",500,0,5);
  httz->ProjectionX("hsysttz",1,30);
  TH1D* hsysttw = new TH1D("hsysttw","SCALE Weights in Signal Region TTW",500,0,5);
  httw->ProjectionX("hsysttw",1,30);

  TCanvas c;

  std::cout<<"scale uncert for ttz: "<<hsysttz->GetRMS()<<std::endl;
  std::cout<<"scale uncert for ttw: "<<hsysttw->GetRMS()<<std::endl;

  // hsysttz->SetLineColor(kRed);
  hsysttz->GetXaxis()->SetRangeUser(0,1.5);
  hsysttz->Draw();
 
  c.Print("scalesys_ttz_1003.pdf");
  hsysttw->GetXaxis()->SetRangeUser(0,1.5);  
  hsysttw->Draw();

  c.Print("scalesys_ttw_1003.pdf");

  delete httz; delete httw; delete hsysttz; delete hsysttw;

  TH2F* httz = (TH2F*) fttz->Get("hist_scaleHT_1004");
  TH2F* httw = (TH2F*) fttw->Get("hist_scaleHT_1004");
  

  TH1D* hsysttz = new TH1D("hsysttz","SCALE Weights in Signal Region TTZ",500,0,5);
  httz->ProjectionX("hsysttz",1,30);
  TH1D* hsysttw = new TH1D("hsysttw","SCALE Weights in Signal Region TTW",500,0,5);
  httw->ProjectionX("hsysttw",1,30);

  TCanvas c;

  std::cout<<"scale uncert for ttz: "<<hsysttz->GetRMS()<<std::endl;
  std::cout<<"scale uncert for ttw: "<<hsysttw->GetRMS()<<std::endl;

  // hsysttz->SetLineColor(kRed);
  hsysttz->GetXaxis()->SetRangeUser(0,1.5);
  hsysttz->Draw();
 
  c.Print("scalesys_ttz_1004.pdf");
  hsysttw->GetXaxis()->SetRangeUser(0,1.5);  
  hsysttw->Draw();

  c.Print("scalesys_ttw_1004.pdf");

  delete httz; delete httw; delete hsysttz; delete hsysttw;

  TH2F* httz = (TH2F*) fttz->Get("hist_scaleHT_1005");
  TH2F* httw = (TH2F*) fttw->Get("hist_scaleHT_1005");
  

  TH1D* hsysttz = new TH1D("hsysttz","SCALE Weights in Signal Region TTZ",500,0,5);
  httz->ProjectionX("hsysttz",1,30);
  TH1D* hsysttw = new TH1D("hsysttw","SCALE Weights in Signal Region TTW",500,0,5);
  httw->ProjectionX("hsysttw",1,30);

  TCanvas c;

  std::cout<<"scale uncert for ttz: "<<hsysttz->GetRMS()<<std::endl;
  std::cout<<"scale uncert for ttw: "<<hsysttw->GetRMS()<<std::endl;

  // hsysttz->SetLineColor(kRed);
  hsysttz->GetXaxis()->SetRangeUser(0,1.5);
  hsysttz->Draw();
 
  c.Print("scalesys_ttz_1005.pdf");
  hsysttw->GetXaxis()->SetRangeUser(0,1.5);  
  hsysttw->Draw();

  c.Print("scalesys_ttw_1005.pdf");

  delete httz; delete httw; delete hsysttz; delete hsysttw;

  TH2F* httz = (TH2F*) fttz->Get("hist_scaleHT_1007");
  TH2F* httw = (TH2F*) fttw->Get("hist_scaleHT_1007");
  

  TH1D* hsysttz = new TH1D("hsysttz","SCALE Weights in Signal Region TTZ",500,0,5);
  httz->ProjectionX("hsysttz",1,30);
  TH1D* hsysttw = new TH1D("hsysttw","SCALE Weights in Signal Region TTW",500,0,5);
  httw->ProjectionX("hsysttw",1,30);

  TCanvas c;

  std::cout<<"scale uncert for ttz: "<<hsysttz->GetRMS()<<std::endl;
  std::cout<<"scale uncert for ttw: "<<hsysttw->GetRMS()<<std::endl;

  // hsysttz->SetLineColor(kRed);
  hsysttz->GetXaxis()->SetRangeUser(0,1.5);
  hsysttz->Draw();
 
  c.Print("scalesys_ttz_1007.pdf");
  hsysttw->GetXaxis()->SetRangeUser(0,1.5);  
  hsysttw->Draw();

  c.Print("scalesys_ttw_1007.pdf");

  delete httz; delete httw; delete hsysttz; delete hsysttw;

  TH2F* httz = (TH2F*) fttz->Get("hist_scaleHT_1009");
  TH2F* httw = (TH2F*) fttw->Get("hist_scaleHT_1009");
  

  TH1D* hsysttz = new TH1D("hsysttz","SCALE Weights in Signal Region TTZ",500,0,5);
  httz->ProjectionX("hsysttz",1,30);
  TH1D* hsysttw = new TH1D("hsysttw","SCALE Weights in Signal Region TTW",500,0,5);
  httw->ProjectionX("hsysttw",1,30);

  TCanvas c;

  std::cout<<"scale uncert for ttz: "<<hsysttz->GetRMS()<<std::endl;
  std::cout<<"scale uncert for ttw: "<<hsysttw->GetRMS()<<std::endl;

  // hsysttz->SetLineColor(kRed);
  hsysttz->GetXaxis()->SetRangeUser(0,1.5);
  hsysttz->Draw();
 
  c.Print("scalesys_ttz_1009.pdf");
  hsysttw->GetXaxis()->SetRangeUser(0,1.5);  
  hsysttw->Draw();

  c.Print("scalesys_ttw_1009.pdf");


  */
}
