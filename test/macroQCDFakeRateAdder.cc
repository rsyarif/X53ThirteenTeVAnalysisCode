#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include <vector>


void macroQCDFakeRateAdder(){


  typedef std::map<std::string,float> sfmap;
  
  sfmap xsec;

  xsec["QCD_Pt-20to30_MuEnrichedPt5"] = 558528000;
  xsec["QCD_Pt-30to50_MuEnrichedPt5"] = 139803000;
  xsec["QCD_Pt-50to80_MuEnrichedPt5"] = 19222500;
  xsec["QCD_Pt-80to120_MuEnrichedPt5"] = 2758420;
  xsec["QCD_Pt-120to170_MuEnrichedPt5"] = 469797;
  xsec["QCD_Pt-170to300_MuEnrichedPt5"] = 117989;
  xsec["QCD_Pt-300to470_MuEnrichedPt5"] = 7820.25;
  xsec["QCD_Pt-470to600_MuEnrichedPt5"] = 645.528;
  xsec["QCD_Pt-600to800_MuEnrichedPt5"] = 187.109;
  xsec["QCD_Pt-800to1000_MuEnrichedPt5"] = 32.3486;
  xsec["QCD_Pt-1000toInf_MuEnrichedPt5"] = 10.4305;

  xsec["QCD_Pt-20to30_EMEnriched"] = 557600000;
  xsec["QCD_Pt-30to50_EMEnriched"] = 136000000;
  xsec["QCD_Pt-50to80_EMEnriched"] = 19800000;
  xsec["QCD_Pt-80to120_EMEnriched"] = 2800000;
  xsec["QCD_Pt-120to170_EMEnriched"] = 477000;
  xsec["QCD_Pt-170to300_EMEnriched"] = 114000;
  xsec["QCD_Pt-300toInf_EMEnriched"] = 9000;

  TFile* fout = new TFile("FakeRate_QCD_Combined.root","RECREATE");

  //final histograms
  TH1F* elNumHist_all = new TH1F("elNumHist_all","el fake rate",6,0,6);
  TH1F* elNumHist_lpt = new TH1F("elNumHist_lpt","el fake rate",6,0,6);
  TH1F* elNumHist_hpt = new TH1F("elNumHist_hpt","el fake rate",6,0,6);

  //final histograms
  TH1F* muNumHist_all = new TH1F("muNumHist_all","mu fake rate",6,0,6);
  TH1F* muNumHist_lpt = new TH1F("muNumHist_lpt","mu fake rate",6,0,6);
  TH1F* muNumHist_hpt = new TH1F("muNumHist_hpt","mu fake rate",6,0,6);

  float norm = 0.0;

  for(sfmap::iterator imap = xsec.begin(); imap!=xsec.end(); imap++){
    std::string filename = "FakeRate_"+imap->first+".root";
    TFile* f = new TFile(filename.c_str());
    std::cout<<"running filename: "<<filename<<std::endl;
    TH1F* tempEl_all = (TH1F*) f->Get("elNumHist_all");
    TH1F* tempEl_lpt = (TH1F*) f->Get("elNumHist_lpt");
    TH1F* tempEl_hpt = (TH1F*) f->Get("elNumHist_hpt");

    //get weight
    float scale = xsec.find("QCD_Pt-20to30_MuEnrichedPt5")->second;
    float weight = imap->second / scale;
    norm = norm + weight;
    tempEl_all->Sumw2();
    //normalize to first entry
    tempEl_all->Scale( weight);
    elNumHist_all->Add(tempEl_all);

    tempEl_lpt->Sumw2();
    //normalize to first entry
    tempEl_lpt->Scale( weight);
    elNumHist_lpt->Add(tempEl_lpt);

    tempEl_hpt->Sumw2();
    //normalize to first entry
    tempEl_hpt->Scale( weight);
    elNumHist_hpt->Add(tempEl_hpt);

    TH1F* tempMu_all = (TH1F*) f->Get("muNumHist_all");
    TH1F* tempMu_lpt = (TH1F*) f->Get("muNumHist_lpt");
    TH1F* tempMu_hpt = (TH1F*) f->Get("muNumHist_hpt");

    tempMu_all->Sumw2();
    //normalize to first entry
    tempMu_all->Scale( weight);
    muNumHist_all->Add(tempMu_all);

    tempMu_lpt->Sumw2();
    //normalize to first entry
    tempMu_lpt->Scale( weight);
    muNumHist_lpt->Add(tempMu_lpt);

    tempMu_hpt->Sumw2();
    //normalize to first entry
    tempMu_hpt->Scale( weight);
    std::cout<<"weight is: "<<weight<<std::endl;
    muNumHist_hpt->Add(tempMu_hpt);
    std::cout<<"ran file: "<<filename<<std::endl;
    delete tempMu_all; delete tempMu_lpt; delete tempMu_hpt;
    delete tempEl_all; delete tempEl_lpt; delete tempEl_hpt;
    delete f;
    
  }


  //now normalize
  elNumHist_all->Scale( 1.0 / norm);
  elNumHist_lpt->Scale( 1.0 / norm);
  elNumHist_hpt->Scale( 1.0 / norm);
  
  muNumHist_all->Scale( 1.0 / norm);
  muNumHist_lpt->Scale( 1.0 / norm);
  muNumHist_hpt->Scale( 1.0 / norm);
  

  /* fout->Append(elNumHist_all);
  fout->Append(elNumHist_lpt);
  fout->Append(elNumHist_hpt);

  fout->Append(muNumHist_all);
  fout->Append(muNumHist_lpt);
  fout->Append(muNumHist_hpt);
  */

  fout->Write();


}
