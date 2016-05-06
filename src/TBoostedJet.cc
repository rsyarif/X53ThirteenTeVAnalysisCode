#include "../interface/TBoostedJet.h"

TBoostedJet::TBoostedJet(double pttemp, double etatemp, double phitemp, double energytemp,double tM, double pM, double sdM, double fM, double t1, double t2, double t3, int nD) :
  pt(pttemp),eta(etatemp),phi(phitemp),energy(energytemp),trimmedMass(tM),prunedMass(pM),softDropMass(sdM),filteredMass(fM),tau1(t1),tau2(t2),tau3(t3),nSubjets(nD)
{
  setLV();
}

TBoostedJet::TBoostedJet(const TBoostedJet &jet){
  pt=jet.pt;
  eta=jet.eta;
  phi=jet.phi;
  energy=jet.energy;
  setLV();
}

TBoostedJet::~TBoostedJet(){}

void TBoostedJet::AddSubJet(TJet* j){

  subjetPt.push_back(j->pt);
  subjetEta.push_back(j->eta);
  subjetPhi.push_back(j->phi);
  subjetBDisc.push_back(j->bDisc);
  subjetBTag.push_back(j->bTag);
  subjetDeltaR.push_back(j->dR);
  subjetMass.push_back(j->mass);

}
