#include "TFile.h"
#include "TH1.h"
#include <vector>

void printSys(TFile* f,std::string name){

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


  float nom_full = h_nom->Integral(11,h_nom->GetNbinsX()+1);
  float maxdiff=0;
  for(unsigned int i=0; i<hists.size();i++){
    float tot = hists.at(i)->Integral(11,hists.at(i)->GetNbinsX()+1);
    float percentdiff = 100*( (tot-nom_full) / nom_full);
    if(fabs(percentdiff) > maxdiff) maxdiff=percentdiff;
    //std::cout<<percentdiff<<std::endl;
  }
  std::cout<<"**************Running uncertainty for: ****************"<<name<<std::endl;
  std::cout<<"for full analysis cut: "<<maxdiff<<std::endl;
  maxdiff=0;

  for(unsigned int i=0; i<hists.size();i++){
    float tot = hists.at(i)->Integral(1,hists.at(i)->GetNbinsX()+1);
    float percentdiff = 100*( (tot-nom) / nom);
    if(fabs(percentdiff) > maxdiff) maxdiff=percentdiff;
  }
  std::cout<<"for nconst  cut: "<<maxdiff<<std::endl;  

  maxdiff=0;
  for(unsigned int i=0; i<hists_ssdl.size();i++){
    float tot = hists_ssdl.at(i)->Integral(1,hists_ssdl.at(i)->GetNbinsX()+1);
    float percentdiff = 100*( (tot-nom_ssdl) / nom_ssdl);
    if(fabs(percentdiff) > maxdiff) maxdiff=percentdiff;
  }
  std::cout<<"Now for just ssdl cut"<<maxdiff<<"\n";  
  std::cout<<"\n\n";  

}


void scale_sys(){

  TFile* ttz = new TFile("../../../test/TTZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* ttw = new TFile("../../../test/TTW_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* tth = new TFile("../../../test/TTH_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  //TFile* ttb = new TFile("../../../test/TTbar_ext2_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* wz = new TFile("../../../test/WZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* zz = new TFile("../../../test/ZZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* lh700 = new TFile("../../../test/X53X53m700LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* lh800 = new TFile("../../../test/X53X53m800LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* lh900 = new TFile("../../../test/X53X53m900LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* lh1000 = new TFile("../../../test/X53X53m1000LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* lh1100 = new TFile("../../../test/X53X53m1100LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* lh1200 = new TFile("../../../test/X53X53m1200LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* lh1300 = new TFile("../../../test/X53X53m1300LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* lh1400 = new TFile("../../../test/X53X53m1400LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* lh1500 = new TFile("../../../test/X53X53m1500LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  //TFile* lh1600 = new TFile("../../../test/X53X53m1600LH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");

  TFile* rh700 = new TFile("../../../test/X53X53m700RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* rh800 = new TFile("../../../test/X53X53m800RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* rh900 = new TFile("../../../test/X53X53m900RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* rh1000 = new TFile("../../../test/X53X53m1000RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* rh1100 = new TFile("../../../test/X53X53m1100RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* rh1200 = new TFile("../../../test/X53X53m1200RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* rh1300 = new TFile("../../../test/X53X53m1300RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* rh1400 = new TFile("../../../test/X53X53m1400RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* rh1500 = new TFile("../../../test/X53X53m1500RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  //TFile* rh1600 = new TFile("../../../test/X53X53m1600RH_Inc_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");


  printSys(ttz,"TTZ");
  printSys(ttw,"TTW");
  printSys(tth,"TTH");
  //printSys(ttb,);
  printSys(wz,"WZ");
  printSys(zz,"ZZ");

  /* printSys(lh700,"X53 M700 LH");
  printSys(lh800,"X53 M800 LH");
  printSys(lh900,"X53 M900 LH");
  printSys(lh1000,"X53 M1000 LH");
  printSys(lh1100,"X53 M1100 LH");
  printSys(lh1200,"X53 M1200 LH");
  printSys(lh1300,"X53 M1300 LH");
  printSys(lh1400,"X53 M1400 LH");
  printSys(lh1500,"X53 M1500 LH");
  printSys(lh1600,"X53 M1600 LH");


  printSys(rh700,"X53 M700 RH");
  printSys(rh800,"X53 M800 RH");
  printSys(rh900,"X53 M900 RH");
  printSys(rh1000,"X53 M1000 RH");
  printSys(rh1100,"X53 M1100 RH");
  printSys(rh1200,"X53 M1200 RH");
  printSys(rh1300,"X53 M1300 RH");
  printSys(rh1400,"X53 M1400 RH");
  printSys(rh1500,"X53 M1500 RH");
  printSys(rh1600,"X53 M1600 RH");
  */

}
