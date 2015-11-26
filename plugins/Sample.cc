#ifndef SAMPLE
#define SAMPLE

#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <string>
#include "TH1.h"
#include "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_3_0/src/AnalysisCode/ThirteenTeVX53/plugins/Variable.cc"
#include <assert.h>

class Sample {

public:
  Sample(std::string n, TFile* f, float w, float xs,std::string cut,int c, int ls=0);
  ~Sample();

  std::string name;
  TFile* file;
  TTree* tree;
  float weight;
  float xsec;
  std::string cutname;
  int color;
  int linestyle;

  //histograms for ntxy by channel
  std::vector<TH1F*> hists_all;
  std::vector<TH1F*> hists_elel;
  std::vector<TH1F*> hists_elmu;
  std::vector<TH1F*> hists_mumu;

  TH1F* hist;

  //final histograms for np background (useful for drawing since will have error correct)
  TH1F* NPCombinedHist_all;
  TH1F* NPCombinedHist_elel;
  TH1F* NPCombinedHist_elmu;
  TH1F* NPCombinedHist_mumu;

  void setHist(Variable* var,std::string cut);

  void setNPHistos(TFile*);
  TH1F* SetNPCombinedHisto(std::vector<TH1F*> hists,std::vector<float> weights);
};
  
Sample::~Sample(){
  delete hist;
  delete tree;
  delete file;
};

Sample::Sample(std::string n, TFile* f, float w, float xs, std::string cut, int c, int ls):
  name(n),file(f),weight(w), xsec(xs),cutname(cut), color(c), linestyle(ls)
  
{
  std::string tname = "tEvts_"+cutname;
  tree = (TTree*) file->Get(tname.c_str());

  hist = new TH1F();

  setNPHistos(file);

  

};


void Sample::setHist(Variable* var, std::string cut){

  //reset the hist
  hist->Reset("ICESM");
  //make new bins
  hist ->SetBins(var->nbins, var->xmin, var->xmax);
  //set name
  std::string histname = "h_"+var->name+"_"+name;
  //std::cout<<"setting histname to: "<<histname<<std::endl;
  hist->SetName(histname.c_str());
  hist->SetFillColor(color);
  //now draw variable into it
  //std::cout<<"about to project ttree for sample name "<<name<<std::endl;
  tree->Project(histname.c_str(),(var->name).c_str(),cut.c_str());
  //std::cout<<"finished projecting ttree for sample "<<name<<" and mean is now: "<<hist->GetMean()<<std::endl;  
  //now scale by weight
  //hist->Scale( weight);
  //std::cout<<"scaled weight for sample name "<<name<<std::endl;
  //now set axis labels
  hist->Sumw2();
  hist->GetXaxis()->SetTitle(var->Xaxis.c_str());
  hist->GetYaxis()->SetTitle(var->Yaxis.c_str());
  hist->SetLineWidth(linestyle);

}


void Sample::setNPHistos(TFile* f){


  hists_all.push_back( (TH1F*) f->Get("All_HT_nConstCut_NT00"));
  hists_all.push_back( (TH1F*) f->Get("All_HT_nConstCut_NT01"));
  hists_all.push_back( (TH1F*) f->Get("All_HT_nConstCut_NT10"));
  hists_all.push_back( (TH1F*) f->Get("All_HT_nConstCut_NT11"));

  hists_elel.push_back( (TH1F*) f->Get("ElEl_HT_nConstCut_NT00"));
  hists_elel.push_back( (TH1F*) f->Get("ElEl_HT_nConstCut_NT01"));
  hists_elel.push_back( (TH1F*) f->Get("ElEl_HT_nConstCut_NT10"));
  hists_elel.push_back( (TH1F*) f->Get("ElEl_HT_nConstCut_NT11"));

  hists_elmu.push_back( (TH1F*) f->Get("ElMu_HT_nConstCut_NT00"));
  hists_elmu.push_back( (TH1F*) f->Get("ElMu_HT_nConstCut_NT01"));
  hists_elmu.push_back( (TH1F*) f->Get("ElMu_HT_nConstCut_NT10"));
  hists_elmu.push_back( (TH1F*) f->Get("ElMu_HT_nConstCut_NT11"));

  hists_mumu.push_back( (TH1F*) f->Get("MuMu_HT_nConstCut_NT00"));
  hists_mumu.push_back( (TH1F*) f->Get("MuMu_HT_nConstCut_NT01"));
  hists_mumu.push_back( (TH1F*) f->Get("MuMu_HT_nConstCut_NT10"));
  hists_mumu.push_back( (TH1F*) f->Get("MuMu_HT_nConstCut_NT11"));


}

TH1F* Sample::SetNPCombinedHisto(std::vector<TH1F*> hists,std::vector<float> weights){

  TH1F* hist = (TH1F*) hists.at(0)->Clone();

  hist->Sumw2();
  hist->Scale(weights.at(0) );

  TH1F* ht01 = (TH1F*) hists.at(1)->Clone();
  ht01->Sumw2();
  ht01->Scale( weights.at(1));
  hist->Add(ht01);

  TH1F* ht10 = (TH1F*) hists.at(2)->Clone();
  ht10->Sumw2();
  ht10->Scale(weights.at(2));
  hist->Add(ht10);

  TH1F* ht11 = (TH1F*) hists.at(3)->Clone();
  ht11->Sumw2();
  ht11->Scale( weights.at(3));
  hist->Add(ht11);

  //std::cout<<"Nt00 weight: "<<weights.at(0)<<std::endl;
  //std::cout<<"Nt01 weight: "<<weights.at(1)<<std::endl;
  //std::cout<<"Nt10 weight: "<<weights.at(2)<<std::endl;
  //std::cout<<"Nt11 weight: "<<weights.at(3)<<std::endl;

  return hist;
  

}



#endif
