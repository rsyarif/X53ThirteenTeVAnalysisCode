void dupCheck(TString filename){

  set <long long> checkDuplicates;
  int nDup = 0;
  long long RUNPREF = 1000 * 1000;
  RUNPREF *= 1000 * 1000;
  
  TString eospath = "root://cmseos.fnal.gov:///store/group/lpcljm/LJMet94x_2lepTT_2017datasets_2018_11_18_rizki_hadds_Analyzer/";

  TFile* fd = TFile::Open(eospath+filename);

  TTree* t = (TTree*) fd->Get("tEvts_ssdl");
  
  std::cout << "\nChecking duplicates in : " << filename << std::endl;
  int run,lumi;
  long long event;
  t->SetBranchAddress("Run",&run);
  t->SetBranchAddress("Lumi",&lumi);
  t->SetBranchAddress("Event",&event);
  for(int i=0; i< t->GetEntries();i++){
    t->GetEntry(i);

    if(run ==279931 && event==466046051){ // what is this?? left over from Clint in 2016?? Nov27,2018.
      std::cout<<"run: "<<run<<" lumi: "<<lumi<<" event: "<<event<<std::endl;
    }
    long long dupCheck = run * RUNPREF + event;

    //std::cout<<"run: "<<run<<" lumi: "<<lumi<<" event: "<<event<< " dupCheck: " << dupCheck <<std::endl;

    if (checkDuplicates.find(dupCheck) != checkDuplicates.end()){
      nDup++;
      std::cout<<"run: "<<run<<" lumi: "<<lumi<<" event: "<<event<< " dupCheck: " << dupCheck <<" ------> DUPLICATE !! "<<std::endl;
      continue;
    }    
    else checkDuplicates.insert(dupCheck);
  }



  std::cout<<"number duplicates: "<<nDup<<std::endl;

}


void dupCheck(){

	std::vector<TString> filenames;
	filenames.push_back("ChargeMisID_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root");
	filenames.push_back("NonPromptData_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root");
	filenames.push_back("Data_MuCBTightMiniIsoTight_ElMVA2016TightRC_2017B-F.root");
	
	for(int i=0; i<filenames.size(); i++){dupCheck(filenames.at(i));}

}