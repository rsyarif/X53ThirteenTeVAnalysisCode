#ifndef TGenParticle_h
#define TGenParticle_h

#include <TLorentzVector.h>
#include <cmath>
#include <iostream>

class TGenParticle {
public:
  TGenParticle();
  TGenParticle(double pttemp, double etatemp, double phitemp,double energytemp, int statustemp, int idtemp, int motherIdtemp, bool prompt, bool tauInfo, bool fromC, bool fromB, int pmother);
  //Kinematics
  double pt;
  double eta;
  double phi;
  double energy;

  int status;
  int id;
  int motherId;
  float charge;
  bool isPrompt;
  bool isFromPromptTau;
  bool PromptMotherHasC;
  bool PromptMotherHasB;
  int PromptMotherId;

  TLorentzVector lv;
  void setLV(){
    lv.SetPxPyPzE( pt*cos(phi), pt*sin(phi), pt*TMath::SinH(eta), energy);
  }

};

#endif

