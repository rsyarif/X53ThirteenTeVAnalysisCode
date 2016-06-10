#include "../interface/THadronicGenJet.h"

THadronicGenJet::THadronicGenJet(double pttemp, double etatemp, double phitemp, double energytemp,int idt, int stat, double d0pt, double d0eta, double d0phi, double d0E, double d1pt, double d1eta, double d1phi, double d1E, double d2pt, double d2eta, double d2phi, double d2E) :
pt(pttemp),eta(etatemp),phi(phitemp),energy(energytemp),id(idt),status(stat),daughter0Pt(d0Pt),daughter0Eta(d0Eta),daughter0Phi(d0Phi),daughter0Energy(d0E),daughter1Pt(d1Pt),daughter1Eta(d1Eta),daughter1Phi(d1Phi),daughter1Energy(d1E),daughter2Pt(d2Pt),daughter2Eta(d2Eta),daughter2Phi(d2Phi),daughter2Energy(d2E)
{
  setLV();

}

THadronicGenJet::~THadronicGenJet(){}


