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

bool TBoostedJet::isTopTag(){

  float maxBDisc=-99;
  for(unsigned int i=0; i< subjetBDisc.size();i++){
    if(maxBDisc<subjetBDisc.at(i)) maxBDisc = subjetBDisc.at(i);
  }

  bool tag = (softDropMass>110 && softDropMass<210) && ( (tau3/tau2) < 0.54) && (maxBDisc > 0.79);
  return tag;
}


bool TBoostedJet::isWTag(){

  bool tag = (prunedMass > 65 && prunedMass < 105) && (tau2/tau1 <0.6);
  return tag;

}
