#ifndef CUTCLASS
#define CUTCLASS

#include <iostream>
#include <vector>
#include <string>


class CutClass {

public:
  CutClass(std::string sample, std::vector<std::string > cut, std::vector<float> n, std::vector<float> err, float xs);
  ~CutClass();

  std::string samplename;
  std::vector<std::string> cutname;
  std::vector<float> nEvents;
  std::vector<float> vErr;
  float xsec; //this is for ease later

};

CutClass::~CutClass(){};

CutClass::CutClass(std::string sample, std::vector<std::string> cut, std::vector<float> n,std::vector<float>err, float xs):
  samplename(sample),cutname(cut),nEvents(n),vErr(err),xsec(xs)
{
};

#endif
