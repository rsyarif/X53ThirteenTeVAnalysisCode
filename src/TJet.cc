#include "../interface/TJet.h"

TJet::TJet(double pttemp, double etatemp, double phitemp, double energytemp) :
  pt(pttemp),eta(etatemp),phi(phitemp),energy(energytemp)
{
  setLV();
  mass=-99;
  dR=-99;
  bDisc=-99;
  bTag=-99;   
}
TJet::TJet(double pttemp, double etatemp, double phitemp, double bd, double drtemp, double mtemp, int bt) :
  pt(pttemp),eta(etatemp),phi(phitemp)
{
  energy=-99;
  setLV();
  mass=mtemp;
  dR=drtemp;
  bDisc=bd;
  bTag=bt;   
}

TJet::TJet(const TJet &jet){
  pt=jet.pt;
  eta=jet.eta;
  phi=jet.phi;
  energy=jet.energy;
  setLV();
  mass=-99;
  dR=-99;
  bDisc=-99;
  bTag=-99;   
}

TJet::~TJet(){}

void TJet::SetSubJetInfo(double m, double DR, double bd, int bt){
  mass=m;
  dR=DR;
  bDisc=bd;
  bTag=bt;
}
