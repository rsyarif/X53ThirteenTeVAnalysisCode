#ifndef TGenParticle_h
#define TGenParticle_h

#include <TLorentzVector.h>
#include <cmath>
#include <iostream>

class TGenParticle {
public:
  TGenParticle();
  TGenParticle(double pttemp, double etatemp, double phitemp,double energytemp, int statustemp, int idtemp, int motherIdtemp);
  //Kinematics
  double pt;
  double eta;
  double phi;
  double energy;

  int status;
  int id;
  int motherId;
  float charge;
  
  TLorentzVector lv;
  void setLV(){
    lv.SetPxPyPzE( pt*cos(phi), pt*sin(phi), pt*TMath::SinH(eta), energy);
  }

};

#endif

