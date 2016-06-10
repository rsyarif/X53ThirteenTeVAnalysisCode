#ifndef THadronicGenJet_h
#define THadronicGenJet_h

#include <TLorentzVector.h>
#include <cmath>
#include <iostream>

class THadronicGenJet{
 public:
  THadronicGenJet(double pttemp, double etatemp, double phitemp, double energytemp,int idt, int stat, double d0pt, double d0eta, double d0phi, double d0E, double d1pt, double d1eta, double d1phi, double d1E, double d2pt, double d2eta, double d2phi, double d2E);
  //kinematics
  double pt;
  double eta;
  double phi;
  double energy;

  int id;
  int status;
  
  double daughter0Pt;
  double daughter0Eta;
  double daughter0Phi;
  double daughter0Energy;

  double daughter1Pt;
  double daughter1Eta;
  double daughter1Phi;
  double daughter1Energy;

  double daughter2Pt;
  double daughter2Eta;
  double daughter2Phi;
  double daughter2Energy;


  THadronicGenJet(const THadronicGenJet& jet);
  ~THadronicGenJet();
  TLorentzVector lv;

  void setLV(){
    lv.SetPxPyPzE(pt*cos(phi), pt*sin(phi), pt*TMath::SinH(eta), energy);
  }


};
#endif
