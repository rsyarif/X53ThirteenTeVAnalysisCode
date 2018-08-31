#include <iostream>
#include <iomanip> 
#include <vector>
#include <string>
#include "TString.h"

void test(){

  float Weights_BWBW = 0.12345;
  TString wStr_BWBW = std::to_string(Weights_BWBW);
  TString nomcut_BWBW = wStr_BWBW+" * MCWeight * (Lep1Pt>40 && nConst >=5 && (DilepMass>20) && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) && cleanAK4HT > 1200)";
  std::cout << nomcut_BWBW << std::endl;

}

