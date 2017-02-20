void printLine(TString channel){

  TFile* cm1 = new TFile("ChargeMisID_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016B-D.root");
  TFile* cm2 = new TFile("ChargeMisID_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");
  TFile* np1 = new TFile("NonPromptData_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016B-D.root");
  TFile* np2 = new TFile("NonPromptData_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");

  TFile* fttw1 = new TFile("TTW_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016B-D.root");
  TFile* fttw2 = new TFile("TTW_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");

  TFile* fttz1 = new TFile("TTZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016B-D.root");
  TFile* fttz2 = new TFile("TTZ_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");

  TFile* ftth1 = new TFile("TTH_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016B-D.root");
  TFile* ftth2 = new TFile("TTH_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016E-H.root");

  TFile* d = new TFile("Data_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016Full.root");

  TTree* tcm1 = (TTree*) cm1->Get("tEvts_sZVeto");
  TTree* tcm2 = (TTree*) cm2->Get("tEvts_sZVeto");
  TTree* tnp1 = (TTree*) np1->Get("tEvts_sZVeto");
  TTree* tnp2 = (TTree*) np2->Get("tEvts_sZVeto");

  TTree* ttw1 = (TTree*) fttw1->Get("tEvts_sZVeto");
  TTree* ttw2 = (TTree*) fttw2->Get("tEvts_sZVeto");
  TTree* ttz1 = (TTree*) fttz1->Get("tEvts_sZVeto");
  TTree* ttz2 = (TTree*) fttz2->Get("tEvts_sZVeto");
  TTree* tth1 = (TTree*) ftth1->Get("tEvts_sZVeto");
  TTree* tth2 = (TTree*) ftth2->Get("tEvts_sZVeto");


  TTree* td = (TTree*) d->Get("tEvts_sZVeto");
  TH1F* hcm1 = new TH1F("hcm1","h",1,0,100000);
  TH1F* hcm2 = new TH1F("hcm2","h",1,0,100000);
  TH1F* hnp1 = new TH1F("hnp1","h",1,0,100000);
  TH1F* hnp2 = new TH1F("hnp2","h",1,0,100000);
  TH1F* hd = new TH1F("hd","h",1,0,100000);
  //mc
  TH1F* httw1 = new TH1F("httw1","h",1,0,100000);
  TH1F* httw2 = new TH1F("httw2","h",1,0,100000);
  TH1F* httz1 = new TH1F("httz1","h",1,0,100000);
  TH1F* httz2 = new TH1F("httz2","h",1,0,100000);
  TH1F* htth1 = new TH1F("htth1","h",1,0,100000);
  TH1F* htth2 = new TH1F("htth2","h",1,0,100000);

  tcm1->Project("hcm1","Lep1Pt","ChargeMisIDWeight * NPWeight* (Lep1Pt>100 && Lep2Pt>120 && nCleanAK4Jets > 1 && cleanAK4HT < 900"+channel);
  tcm2->Project("hcm2","Lep1Pt","ChargeMisIDWeight * NPWeight* (Lep1Pt>100 && Lep2Pt>120 && nCleanAK4Jets > 1 && cleanAK4HT < 900"+channel);
  tnp1->Project("hnp1","Lep1Pt","ChargeMisIDWeight * NPWeight* (Lep1Pt>100 && Lep2Pt>120 && nCleanAK4Jets > 1 && cleanAK4HT < 900"+channel);
  tnp2->Project("hnp2","Lep1Pt","ChargeMisIDWeight * NPWeight* (Lep1Pt>100 && Lep2Pt>120 && nCleanAK4Jets > 1 && cleanAK4HT < 900"+channel);
  td->Project("hd","Lep1Pt","ChargeMisIDWeight * NPWeight* (Lep1Pt>100 && Lep2Pt>120 && nCleanAK4Jets > 1 && cleanAK4HT < 900"+channel);

  //do mc
  ttw1->Project("httw1","Lep1Pt","PUWeight * IDSF * IsoSF * trigSF * GsfSF * MCWeight *ChargeMisIDWeight * NPWeight* (Lep1Pt>100 && Lep2Pt>120 && nCleanAK4Jets > 1 && cleanAK4HT < 900"+channel);
  ttw2->Project("httw2","Lep1Pt","PUWeight * IDSF * IsoSF * trigSF * GsfSF * MCWeight *ChargeMisIDWeight * NPWeight* (Lep1Pt>100 && Lep2Pt>120 && nCleanAK4Jets > 1 && cleanAK4HT < 900"+channel);
  ttz1->Project("httz1","Lep1Pt","PUWeight * IDSF * IsoSF * trigSF * GsfSF * MCWeight *ChargeMisIDWeight * NPWeight* (Lep1Pt>100 && Lep2Pt>120 && nCleanAK4Jets > 1 && cleanAK4HT < 900"+channel);
  ttz2->Project("httz2","Lep1Pt","PUWeight * IDSF * IsoSF * trigSF * GsfSF * MCWeight *ChargeMisIDWeight * NPWeight* (Lep1Pt>100 && Lep2Pt>120 && nCleanAK4Jets > 1 && cleanAK4HT < 900"+channel);
  tth1->Project("htth1","Lep1Pt","PUWeight * IDSF * IsoSF * trigSF * GsfSF * MCWeight *ChargeMisIDWeight * NPWeight* (Lep1Pt>100 && Lep2Pt>120 && nCleanAK4Jets > 1 && cleanAK4HT < 900"+channel);
  tth2->Project("htth2","Lep1Pt","PUWeight * IDSF * IsoSF * trigSF * GsfSF * MCWeight *ChargeMisIDWeight * NPWeight* (Lep1Pt>100 && Lep2Pt>120 && nCleanAK4Jets > 1 && cleanAK4HT < 900"+channel);

  //scale mc by weights
  float weight_ttz1 = 12900 * 0.2529 / (1992438 * 0.465749);
  httz1->Scale(weight_ttz1);
  float weight_ttz2 = 23900 * 0.2529 / (1992438 * 0.465749);
  httz2->Scale(weight_ttz2);
  float weight_ttw1 = 12900 * 0.2043 / (2160168*0.515109);
  httw1->Scale(weight_ttw1);
  float weight_ttw2 = 23900 * 0.2043 / (2160168*0.515109);
  httw2->Scale(weight_ttw2);
  float weight_tth1 = 12900 * 0.215 / (3981250*0.981088);
  htth1->Scale(weight_tth1);
  float weight_tth2 = 23900 * 0.215 / (3981250*0.981088);
  htth2->Scale(weight_tth2);

  Double_t ev_cm1 = hcm1->Integral();
  Double_t ev_cm2 = hcm2->Integral();
  Double_t ev_np1 = hnp1->Integral();
  Double_t ev_np2 = hnp2->Integral();
  Double_t ev_d = hd->Integral();
  //mc
  Double_t ev_ttw1 = httw1->Integral();
  Double_t ev_ttw2 = httw2->Integral();
  Double_t ev_ttz1 = httz1->Integral();
  Double_t ev_ttz2 = httz2->Integral();
  Double_t ev_tth1 = htth1->Integral();
  Double_t ev_tth2 = htth2->Integral();
  std::cout<<ev_cm1+ev_cm2<<std::endl;
  float nbkg = ev_cm1+ev_cm2+ev_np1+ev_np2 + ev_ttw1 + ev_ttw2 + ev_ttz1 + ev_ttz2 + ev_tth1 + ev_tth2;
  float err = 0.3*0.3*(ev_cm1+ev_cm2)*(ev_cm1+ev_cm2);
  std::cout<<"Channel is: "<<channel<<std::endl;
  std::cout<<"err "<<err<<std::endl;
  err+=0.5*0.5*(ev_np1+ev_np2)*(ev_np1+ev_np2);
  std::cout<<"err "<<err<<std::endl;
  err = pow(err,0.5);
  std::cout<<" data: "<<ev_d<<" data-driven backgrounds: "<<nbkg<<" +/- "<<err<<std::endl;
  
}


void highptCheck(){

  printLine(" && Channel > -1)");
  printLine(" && Channel == 0)");
  printLine(" && Channel == 1)");
  printLine(" && Channel == 2)");

}
