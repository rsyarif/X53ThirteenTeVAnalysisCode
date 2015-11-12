#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <map>
#include <string>
#include <sstream> 
#include <algorithm>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TChain.h"

#include "../interface/TreeReader.h"
#include "JetAnalyzer.cc"
#include "GenAnalyzer.cc"
#include "../interface/TreeMaker.h"
#include "../plugins/Macros.cc"


int main(int argc, char* argv[]){

  TFile* outfile = new TFile("nPV_hists.root", "RECREATE");

  TH1F* data_hist = new TH1F("data_hist","data npv",50,0,50);
  TH1F* mc_hist = new TH1F("mc_hist","mc npv",50,0,50);

  bool mc = true;
  TreeReader* trd = new TreeReader("/eos/uscms/store/user/lpctlbsm/clint/Run2015D/PreApproval/ljmet_trees/ljmet_Data_All.root",!mc);
  TreeReader* trzz = new TreeReader("/eos/uscms/store/user/lpctlbsm/clint/Spring15/25ns/PreApproval/ljmet_trees/ljmet_ZZ.root",mc);

  int nEntriesd = trd->tree->GetEntries();

  for(int ient=0; ient<nEntriesd; ient++){

    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntriesd<<" events"<<std::endl;
    
    trd->GetEntry(ient);
    data_hist->Fill(trd->nPrimaryVert);
    
  }

  int nEntriesmc = trzz->tree->GetEntries();

  for(int ient=0; ient<nEntriesmc; ient++){

    if(ient % 100000 ==0) std::cout<<"Completed "<<ient<<" out of "<<nEntriesmc<<" events"<<std::endl;
    
    trzz->GetEntry(ient);
    mc_hist->Fill(trzz->nPrimaryVert);
    
  }

  //normalize
  data_hist->Scale( 1 / data_hist->Integral());
  mc_hist->Scale( 1 / mc_hist->Integral() );

  outfile->WriteTObject(data_hist);
  outfile->WriteTObject(mc_hist);

  outfile->Write();
  outfile->Close();

}
