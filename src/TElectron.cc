#include "../interface/TElectron.h"


TElectron::TElectron(double pttemp,double etatemp,double phitemp, double energytemp, int chargetemp, double dEtatemp, double dPhitemp, double dZtemp,double d0temp,double hOverEtemp, double mHitstemp, double ooEmooPtemp, double sigmaIetaIetatemp, double relIsotemp,int chargeconsistencytemp):
  TLepton(pttemp,etatemp,phitemp,energytemp,chargetemp),  
  dEta(dEtatemp),
  dPhi(dPhitemp),
  dZ(dZtemp),
  d0(d0temp),
  hOverE(hOverEtemp),
  mHits(mHitstemp),
  ooEmooP(ooEmooPtemp),
  sigmaIetaIeta(sigmaIetaIetatemp),
  relIso(relIsotemp),
  chargeConsistency(chargeconsistencytemp)
{
  setLV();
}

bool TElectron::cutBasedTight(){
  //Barrel
  if(fabs(eta) <= 1.479){
    if(fabs(dEta) >= 0.006574)    return false;
    if(fabs(dPhi) >= 0.022868)     return false;
    if(sigmaIetaIeta >= 0.010181) return false;
    if(hOverE >= 0.037553)        return false;
    if(fabs(d0) >= 0.009924)      return false;
    if(fabs(dZ) >= 0.015310)      return false;
    if(ooEmooP >= 0.131191) return false;
    if(relIso > 0.1649)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(pt <30)                 return false;
  }
  //Endcap
  else{
    if(fabs(dEta) >= 0.005681)    return false;
    if(fabs(dPhi) >= 0.032046)    return false;
    if(sigmaIetaIeta >= 0.028766) return false;
    if(hOverE >= 0.081902)        return false;
    if(fabs(d0) >= 0.0027261)      return false;
    if(fabs(dZ) >= 0.147154)      return false;
    if(ooEmooP >= 0.106055) return false;
    if(relIso >= 0.090185)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(pt <30)                 return false;
  }
  return true;
}

bool TElectron::cutBasedLoose(){
  //Barrel
  if(fabs(eta) <= 1.479){
    if(fabs(dEta) >= 0.012442)    return false;
    if(fabs(dPhi) >= 0.072624)    return false;
    if(sigmaIetaIeta >= 0.010557) return false;
    if(hOverE >= 0.121476)         return false;
    if(fabs(d0) >= 0.022664)      return false;
    if(fabs(dZ) >= 0.173670)     return false;
    if(ooEmooP >= 0.221803) return false;
    if(relIso >= 0.120026)          return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(pt <20)                 return false;
  }
  
  //Endcap
  else{
    if(fabs(dEta) >= 0.010654)    return false;
    if(fabs(dPhi) >= 0.145129)    return false;
    if(sigmaIetaIeta >= 0.032602)  return false;
    if(hOverE >= 0.131862)        return false;
    if(fabs(d0) >= 0.097358)       return false;
    if(fabs(dZ) >= 0.198444)      return false;
    if(ooEmooP >= 0.142283) return false;
    if(relIso >= 0.162914)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(pt <20)                 return false;
  }
  return true;
}

bool TElectron::CMSDASTight(){
  //Barrel
  if(fabs(eta) <= 1.479){
    if(fabs(dEta) > 0.0091)    return false;
    if(fabs(dPhi) > 0.031)     return false;
    if(sigmaIetaIeta > 0.0106) return false;
    if(hOverE > 0.0532)        return false;
    if(fabs(d0) > 0.0126)      return false;
    if(fabs(dZ) > 0.0116)      return false;
    if(fabs(ooEmooP) > 0.0609) return false;
    if(relIso > 0.1649)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(pt <20)                 return false;
  }
  //Endcap
  else{
    if(fabs(dEta) > 0.0106)    return false;
    if(fabs(dPhi) > 0.0359)    return false;
    if(sigmaIetaIeta > 0.0305) return false;
    if(hOverE > 0.0835)        return false;
    if(fabs(d0) > 0.0163)      return false;
    if(fabs(dZ) > 0.5999)      return false;
    if(fabs(ooEmooP) > 0.1126) return false;
    if(relIso > 0.2075)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(pt <20)                 return false;
  }
  return true;
}

bool TElectron::CMSDASLoose(){
  //Barrel
  if(fabs(eta) <= 1.479){
    if(fabs(dEta) > 0.0181)    return false;
    if(fabs(dPhi) > 0.0936)    return false;
    if(sigmaIetaIeta > 0.0123) return false;
    if(hOverE > 0.141)         return false;
    if(fabs(d0) > 0.0166)      return false;
    if(fabs(dZ) > 0.54342)     return false;
    if(fabs(ooEmooP) > 0.1353) return false;
    if(relIso > 0.24)          return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(pt <20)                 return false;
  }

  //Endcap
  else{
    if(fabs(dEta) > 0.0124)    return false;
    if(fabs(dPhi) > 0.0642)    return false;
    if(sigmaIetaIeta > 0.035)  return false;
    if(hOverE > 0.1115)        return false;
    if(fabs(d0) > 0.098)       return false;
    if(fabs(dZ) > 0.9187)      return false;
    if(fabs(ooEmooP) > 0.1443) return false;
    if(relIso > 0.3529)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(pt <20)                 return false;
  }
  return true;
}
