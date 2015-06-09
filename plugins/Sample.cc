#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <string>
#include "TH1.h"

class Sample {

public:
  Sample(std::string n, TFile* f, float w, float xs,std::string cut,int c);
  ~Sample();

  std::string name;
  TFile* file;
  TTree* tree;
  float weight;
  float xsec;
  std::string cutname;
  int color;
};
  
Sample::~Sample(){};

Sample::Sample(std::string n, TFile* f, float w, float xs, std::string cut, int c):
  name(n),file(f),weight(w), xsec(xs),cutname(cut), color(c)
  
{
  std::string tname = "tEvts_"+cutname;
  tree = (TTree*) file->Get(tname.c_str());
}    
