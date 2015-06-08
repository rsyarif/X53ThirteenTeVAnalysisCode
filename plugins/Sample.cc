#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <string>
#include "TH1.h"

class Sample {

public:
  Sample(std::string n, TFile* f, float w, int c,std::string cut);
  ~Sample();

  std::string name;
  TFile* file;
  TTree* tree;
  float weight;
  int color;
  std::string cutname;
};
  
Sample::~Sample(){};

Sample::Sample(std::string n, TFile* f, float w, int c, std::string cut):
  name(n),file(f),weight(w), color(c), cutname(cut)
  
{
  std::string tname = "tEvts_"+cutname;
  tree = (TTree*) file->Get(tname.c_str());
}    
