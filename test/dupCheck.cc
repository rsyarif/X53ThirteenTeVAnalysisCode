void dupCheck(){

  set <long long> checkDuplicates;
  int nDup = 0;
  long long RUNPREF = 1000 * 1000;
  RUNPREF *= 1000 * 1000;

  TFile* fd = new TFile("Data_MuCBTightMiniIsoTight_ElMVA2016TightRC_2016Full.root");

  TTree* t = (TTree*) fd->Get("tEvts_ssdl");
  int run,lumi;
  long long event;
  t->SetBranchAddress("Run",&run);
  t->SetBranchAddress("Lumi",&lumi);
  t->SetBranchAddress("Event",&event);
  for(int i=0; i< t->GetEntries();i++){
    t->GetEntry(i);
    if(run ==279931 && event==466046051){
      std::cout<<"run: "<<run<<" lumi: "<<lumi<<" event: "<<event<<std::endl;
    }
    long long dupCheck = run * RUNPREF + event;
    if (checkDuplicates.find(dupCheck) != checkDuplicates.end()){
      nDup++;
      std::cout<<"run: "<<run<<" lumi: "<<lumi<<" event: "<<event<<std::endl;
      continue;
    }
    else checkDuplicates.insert(dupCheck);
  }



  std::cout<<"number duplicates: "<<nDup<<std::endl;

}
