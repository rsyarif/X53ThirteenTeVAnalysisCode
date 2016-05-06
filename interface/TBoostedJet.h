#ifndef TBoostedJet_h
#define TBoostedJet_h

#include <TLorentzVector.h>
#include <cmath>
#include <iostream>
#include "TJet.h"

class TBoostedJet{
 public:
  TBoostedJet(double pttemp, double etatemp, double phitemp, double energytemp,double tM, double pM, double sdM, double fM, double t1, double t2, double t3, int nD);
  //kinematics
  double pt;
  double eta;
  double phi;
  double energy;

  double trimmedMass;
  double prunedMass;
  double softDropMass;
  double filteredMass;

  double tau1;
  double tau2;
  double tau3;

  int nSubjets;

  std::vector<double> subjetPt;
  std::vector<double> subjetEta;
  std::vector<double> subjetPhi;
  std::vector<double> subjetBDisc;
  std::vector<int> subjetBTag;
  std::vector<double> subjetDeltaR;
  std::vector<double> subjetMass;

  TBoostedJet(const TBoostedJet& jet);
  ~TBoostedJet();
  TLorentzVector lv;

  void setLV(){
    lv.SetPxPyPzE(pt*cos(phi), pt*sin(phi), pt*TMath::SinH(eta), energy);
  }

  void AddSubJet(TJet* j);
  bool isTopTag();
  bool isWTag();
};
#endif
