#include <iostream>



class CutClass {

public:
  CutClass(std::string sample, std::string cut, float n);
  ~CutClass();

  std::string samplename;
  std::string cutname;
  float nEvents;


};

CutClass::~CutClass(){};

CutClass::CutClass(std::string sample, std::string cut, float n):
  samplename(sample),cutname(cut),nEvents(n)
{
};
