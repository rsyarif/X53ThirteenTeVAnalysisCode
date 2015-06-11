#include <iostream>
#include <vector>
#include <string>


class CutClass {

public:
  CutClass(std::string sample, std::vector<std::string >cut, std::vecot<float> n);
  ~CutClass();

  std::string samplename;
  std::vecotr<std::string> cutname;
  std::vector<float> nEvents;


};

CutClass::~CutClass(){};

CutClass::CutClass(std::string sample, std::vector<std::string> cut, std::vector<float> n):
  samplename(sample),cutname(cut),nEvents(n)
{
};
