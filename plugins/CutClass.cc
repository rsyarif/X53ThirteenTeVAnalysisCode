#ifndef CUTCLASS
#define CUTCLASS

#include <iostream>
#include <vector>
#include <string>


class CutClass {

public:
  CutClass(std::string sample, std::vector<std::string > cut, std::vector<float> n, float xs);
  ~CutClass();

  std::string samplename;
  std::vector<std::string> cutname;
  std::vector<float> nEvents;
  float xsec; //this is for ease later

};

CutClass::~CutClass(){};

CutClass::CutClass(std::string sample, std::vector<std::string> cut, std::vector<float> n, float xs):
  samplename(sample),cutname(cut),nEvents(n),xsec(xs)
{
};

#endif
