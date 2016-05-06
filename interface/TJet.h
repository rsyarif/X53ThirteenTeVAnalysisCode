#ifndef TJet_h
#define TJet_h

#include <TLorentzVector.h>
#include <cmath>
#include <iostream>

class TJet{
 public:
  TJet(double pttemp, double etatemp, double phitemp, double energytemp);
  TJet(double pttemp, double etatemp, double phitemp, double bd, double drtemp, double mtemp,int bt);
  //kinematics
  double pt;
  double eta;
  double phi;
  double energy;
  //below are primarily used for subjets, so won't be meaningful for ak4 jets
  double mass;
  double dR;
  double bDisc;
  int bTag;

  TJet(const TJet& jet);
  ~TJet();
  TLorentzVector lv;

  void setLV(){
    lv.SetPxPyPzE(pt*cos(phi), pt*sin(phi), pt*TMath::SinH(eta), energy);
  }

  void SetSubJetInfo(double m, double DR, double bd, int bt);

};
#endif
