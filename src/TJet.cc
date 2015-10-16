#include "../interface/TJet.h"

TJet::TJet(double pttemp, double etatemp, double phitemp, double energytemp) :
  pt(pttemp),eta(etatemp),phi(phitemp),energy(energytemp)
{
  setLV();
}

TJet::TJet(const TJet &jet){
  pt=jet.pt;
  eta=jet.eta;
  phi=jet.phi;
  energy=jet.energy;
  setLV();
}

TJet::~TJet(){}
