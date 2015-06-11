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
  TH1F* hist;
  void setHist(Variable* var);
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


};

void Sample::setHist(Variable* var){

  //reset the hist
  hist->Reset();
  //set name
  std::string histname = "h_"+var->name+"_"+name;
  std::cout<<"setting histname to: "<<histname<<std::endl;
  hist->SetName(histname.c_str());
  hist->SetFillColor(color);
  //now draw variable into it
  std::cout<<"about to project ttree for sample name "<<name<<std::endl;
  tree->Project(histname.c_str(),(var->name).c_str());
  std::cout<<"finished projecting ttree for sample "<<name<<" and mean is now: "<<hist->GetMean()<<std::endl;  
  //now scale by weight
  hist->Scale( weight);
  std::cout<<"scaled weight for sample name "<<name<<std::endl;
  //now set axis labels
  hist->GetXaxis()->SetTitle(var->Xaxis.c_str());
  hist->GetYaxis()->SetTitle(var->Yaxis.c_str());
  hist->SetLineWidth(linestyle);

}

