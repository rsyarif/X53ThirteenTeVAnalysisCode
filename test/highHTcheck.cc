void highHTcheck(){


  TFile* f = new TFile("Data_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016B-D.root");

  TTree* t = (TTree*) f->Get("tEvts_sZVeto");
  int nEvents = t->GetEntries();
  long long event;
  int nJets,channel,run,lumi,lep1flavor,lep2flavor,nTL;
  float ht,lep1pt,lep1miniIso,lep2miniIso,DilepMass,lep1eta,lep1phi,lep2pt,lep2eta,lep2phi;

  t->SetBranchAddress("Lep1Pt",&lep1pt);
  t->SetBranchAddress("Run",&run);
  t->SetBranchAddress("Lumi",&lumi);
  t->SetBranchAddress("Event",&event);
  t->SetBranchAddress("cleanAK4HT",&ht);
  t->SetBranchAddress("nCleanAK4Jets",&nJets);
  t->SetBranchAddress("DilepMass",&DilepMass);
  t->SetBranchAddress("Channel",&channel);
  t->SetBranchAddress("Lep1MiniIso",&lep1miniIso);
  t->SetBranchAddress("Lep2MiniIso",&lep2miniIso);
  t->SetBranchAddress("Lep1Eta",&lep1eta);
  t->SetBranchAddress("Lep1Phi",&lep1phi);
  t->SetBranchAddress("Lep1Flavor",&lep1flavor);
  t->SetBranchAddress("nTL",&nTL);
  for(int i=0; i<nEvents;i++){
    t->GetEntry(i);
    bool htwrong = !(ht<1320 && ht>1200);
    bool noJets = nJets<2;
    bool softLep = lep1pt<40;
    bool masscut = !(channel!=0 || (DilepMass<71 ||DilepMass>116));
    bool noIso = lep1miniIso>0.1 || lep2miniIso>0.1;
    //if(htwrong || noJets || softLep || masscut || noIso) continue;
    //std::cout<<run<<","<<lumi<<","<<event<<std::endl;
    //std::cout<<run<<":"<<event<<std::endl;
    //std::cout<<"run="<<run<<" lumi="<<lumi<<std::endl;
    if(run==276655 && lumi==460 && event==847874319) {
      //std::cout<<"triple counted event, lep1 flavor:"<<lep1flavor<<" lep 1 pt: "<<lep1pt<<" lep 1 eta: "<<lep1eta<<" lep1 phi: "<<lep1phi;
      std::cout<<"HTLep: "<<ht<<std::endl;
    }

  }

}
