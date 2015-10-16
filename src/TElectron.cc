#include "../interface/TElectron.h"


TElectron::TElectron(double pttemp,double etatemp,double phitemp, double energytemp, int chargetemp, double dEtatemp, double dPhitemp, double dZtemp,double d0temp,double hOverEtemp, double mHitstemp, double ooEmooPtemp, double sigmaIetaIetatemp,double chIsotemp,double puIsotemp, double neuIsotemp, double photIsotemp,double rhoIsotemp,double AEfftemp, int passConv, int chargeconsistencytemp, int gsftemp, int ctftemp, int scpixtemp, double mvatemp, double miniIsotemp):
  TLepton(pttemp,etatemp,phitemp,energytemp,chargetemp),  
  dEta(dEtatemp),
  dPhi(dPhitemp),
  dZ(dZtemp),
  d0(d0temp),
  hOverE(hOverEtemp),
  mHits(mHitstemp),
  ooEmooP(ooEmooPtemp),
  sigmaIetaIeta(sigmaIetaIetatemp),
  chIso(chIsotemp),
  puIso(puIsotemp),
  neutIso(neuIsotemp),
  photIso(photIsotemp),
  rhoIso(rhoIsotemp),
  AEff(AEfftemp),
  passConversion(passConv),
  chargeConsistency(chargeconsistencytemp),
  gsfCharge(gsftemp),
  ctfCharge(ctftemp),
  scpixCharge(scpixtemp),
  mvaValue(mvatemp),
  miniIso(miniIsotemp)
{
  setLV();

  //redo effective area
  if( fabs(eta)<1.0) AEff=0.1752;
  else if(fabs(eta)<1.479) AEff=0.1862;
  else if(fabs(eta)<2.0) AEff=0.1411;
  else if(fabs(eta)<2.2) AEff=0.1534;
  else if(fabs(eta)<2.3) AEff=0.1903;
  else if(fabs(eta)<2.4) AEff=0.2243;
  else if(fabs(eta)<2.5) AEff=0.2687;


  relIsoDB = (chIso + std::max(0.0, neutIso + photIso - 0.5*puIso) ) / pt;
  relIsoEA = (chIso + std::max(0.0, neutIso + photIso - AEff*rhoIso) ) / pt; 
}

bool TElectron::mvaLoose(){
  if(fabs(eta)<0.8){
    if(mvaValue>0.933) return true;
  }
  else if(fabs(eta)<1.479){
    if(mvaValue>0.825) return true;
  }
  else if(fabs(eta)<2.4){
    if(mvaValue>0.337) return true;
  }
  //if none of the above conditions is met return false
  return false;
}

bool TElectron::mvaTight(){

  if(fabs(eta)<0.8){
    if(mvaValue>0.965) return true;
  }
  else if(fabs(eta)<1.479){
    if(mvaValue>0.917) return true;
  }
  else if(fabs(eta)<2.4){
    if(mvaValue>0.683) return true;
  }
  //if none of the above conditions is met return false
  return false;
}

bool TElectron::mvaTightIso(){
  bool pass = mvaTight() && miniIso<0.1;
  return pass;
}

bool TElectron::mvaLooseIso(){
  bool pass = mvaLoose() && miniIso<0.1;
  return pass;
}

bool TElectron::cutBasedTight50ns(){
  //Barrel
  if(fabs(eta) <= 1.479){
    if(sigmaIetaIeta >= 0.0101) return false;
    if(fabs(dEta) >= 0.0095)    return false;
    if(fabs(dPhi) >= 0.0291)     return false;
    if(hOverE >= 0.0372)        return false;
    if(relIsoEA > 0.0468)        return false;
    if(ooEmooP >= 0.0174) return false;
    if(fabs(d0) >= 0.0144)      return false;
    if(fabs(dZ) >= 0.323)      return false;
    if(mHits > 2)              return false;
    if(chargeConsistency < 1)  return false;
    if(!passConversion)        return false;
    //    if(pt <30)                 return false;
  }
  //Endcap
  else{
    if(fabs(eta)>2.4)           return false;
    if(sigmaIetaIeta >= 0.0287) return false;
    if(fabs(dEta) >= 0.00762)    return false;
    if(fabs(dPhi) >= 0.0439)    return false;
    if(hOverE >= 0.0544)        return false;
    if(relIsoEA >= 0.0759)        return false; 
    if(ooEmooP >= 0.01) return false;
    if(fabs(d0) >= 0.0377)      return false;
    if(fabs(dZ) >= 0.571)      return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(!passConversion)        return false;
    //    if(pt <30)                 return false;
  }

  return true;
}

bool TElectron::cutBasedLoose50ns(){
  //Barrel
  if(fabs(eta) <= 1.479){
    if(sigmaIetaIeta >= 0.0105) return false;
    if(fabs(dEta) >= 0.00976)    return false;
    if(fabs(dPhi) >= 0.0929)    return false;
    if(hOverE >= 0.0765)         return false;
    if(relIsoEA >= 0.118)          return false;
    if(ooEmooP >= 0.184) return false;
    if(fabs(d0) >= 0.0227)      return false;
    if(fabs(dZ) >= 0.379)     return false;
    if(mHits > 2)              return false;
    if(chargeConsistency < 1)  return false;
    if(!passConversion)        return false;
    //   if(pt <20)                 return false;
  }
  
  //Endcap
  else{
    if(fabs(eta)>2.4)           return false;
    if(sigmaIetaIeta >= 0.0318)  return false;
    if(fabs(dEta) >= 0.00952)    return false;
    if(fabs(dPhi) >= 0.181)    return false;
    if(hOverE >= 0.0824)        return false;
    if(relIsoEA >= 0.118)        return false;
    if(ooEmooP >= 0.125) return false;
    if(fabs(d0) >= 0.242)       return false;
    if(fabs(dZ) >= 0.921)      return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(!passConversion)        return false;
    //    if(pt <20)                 return false;
  }
  return true;
}

bool TElectron::cutBasedTight25nsSpring15MC(){
  //Barrel
  if(fabs(eta) <= 1.479){
    if(sigmaIetaIeta >= 0.0101) return false;
    if(fabs(dEta) >= 0.00926)    return false;
    if(fabs(dPhi) >= 0.0336)     return false;
    if(hOverE >= 0.0597)        return false;
    if(relIsoEA > 0.0354)        return false;
    if(ooEmooP >= 0.012) return false;
    if(fabs(d0) >= 0.0111)      return false;
    if(fabs(dZ) >= 0.0466)      return false;
    if(mHits > 2)              return false;
    if(chargeConsistency < 1)  return false;
    if(!passConversion)        return false;
    //    if(pt <30)                 return false;
  }
  //Endcap
  else{
    if(fabs(eta)>2.4)           return false;
    if(sigmaIetaIeta >= 0.0279) return false;
    if(fabs(dEta) >= 0.00724)    return false;
    if(fabs(dPhi) >= 0.0918)    return false;
    if(hOverE >= 0.0615)        return false;
    if(relIsoEA >= 0.0646)        return false; 
    if(ooEmooP >= 0.00999) return false;
    if(fabs(d0) >= 0.0351)      return false;
    if(fabs(dZ) >= 0.417)      return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(!passConversion)        return false;
    //    if(pt <30)                 return false;
  }
  return true;
}

bool TElectron::cutBasedLoose25nsSpring15MC(){
  //Barrel
  if(fabs(eta) <= 1.479){
    if(sigmaIetaIeta >= 0.0103) return false;
    if(fabs(dEta) >= 0.0105)    return false;
    if(fabs(dPhi) >= 0.115)    return false;
    if(hOverE >= 0.104)         return false;
    if(relIsoEA >= 0.0893)          return false;
    if(ooEmooP >= 0.102) return false;
    if(fabs(d0) >= 0.0261)      return false;
    if(fabs(dZ) >= 0.41)     return false;
    if(mHits > 2)              return false;
    if(chargeConsistency < 1)  return false;
    if(!passConversion)        return false;
    //   if(pt <20)                 return false;
  }
  
  //Endcap
  else{
    if(fabs(eta)>2.4)           return false;
    if(sigmaIetaIeta >= 0.0301)  return false;
    if(fabs(dEta) >= 0.00814)    return false;
    if(fabs(dPhi) >= 0.182)    return false;
    if(hOverE >= 0.0897)        return false;
    if(relIsoEA >= 0.121)        return false;
    if(ooEmooP >= 0.126) return false;
    if(fabs(d0) >= 0.118)       return false;
    if(fabs(dZ) >= 0.822)      return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(!passConversion)        return false;
    //    if(pt <20)                 return false;
  }
  return true;
}

bool TElectron::cutBasedTightMay2015(){
  //Barrel
  if(fabs(eta) <= 1.479){
    if(fabs(dEta) >= 0.006046)    return false;
    if(fabs(dPhi) >= 0.028092)     return false;
    if(sigmaIetaIeta >= 0.009947) return false;
    if(hOverE >= 0.045772)        return false;
    if(fabs(d0) >= 0.008790)      return false;
    if(fabs(dZ) >= 0.021226)      return false;
    if(ooEmooP >= 0.020118) return false;
    if(relIsoEA > 0.069537)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(!passConversion)        return false;
    //    if(pt <30)                 return false;
  }
  //Endcap
  else{
    if(fabs(eta)>2.4)           return false;
    if(fabs(dEta) >= 0.007057)    return false;
    if(fabs(dPhi) >= 0.030159)    return false;
    if(sigmaIetaIeta >= 0.028237) return false;
    if(hOverE >= 0.067778)        return false;
    if(fabs(d0) >= 0.027984)      return false;
    if(fabs(dZ) >= 0.133431)      return false;
    if(ooEmooP >= 0.098919) return false;
    if(relIsoEA >= 0.078265)        return false; 
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(!passConversion)        return false;
    //    if(pt <30)                 return false;
  }
  return true;
}

bool TElectron::cutBasedLooseMay2015(){
  //Barrel
  if(fabs(eta) <= 1.479){
    if(fabs(dEta) >= 0.009277)    return false;
    if(fabs(dPhi) >= 0.094739)    return false;
    if(sigmaIetaIeta >= 0.010331) return false;
    if(hOverE >= 0.093068)         return false;
    if(fabs(d0) >= 0.035904)      return false;
    if(fabs(dZ) >= 0.075496)     return false;
    if(ooEmooP >= 0.189968) return false;
    if(relIsoEA >= 0.130136)          return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(!passConversion)        return false;
    //   if(pt <20)                 return false;
  }
  
  //Endcap
  else{
    if(fabs(eta)>2.4)           return false;
    if(fabs(dEta) >= 0.009833)    return false;
    if(fabs(dPhi) >= 0.149934)    return false;
    if(sigmaIetaIeta >= 0.031838)  return false;
    if(hOverE >= 0.115754)        return false;
    if(fabs(d0) >= 0.099266)       return false;
    if(fabs(dZ) >= 0.197897)      return false;
    if(ooEmooP >= 0.140662) return false;
    if(relIsoEA >= 0.163368)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    if(!passConversion)        return false;
    //    if(pt <20)                 return false;
  }
  return true;
}

bool TElectron::cutBasedTightApr2015(){
  //Barrel
  if(fabs(eta) <= 1.479){
    if(fabs(dEta) >= 0.006574)    return false;
    if(fabs(dPhi) >= 0.022868)     return false;
    if(sigmaIetaIeta >= 0.010181) return false;
    if(hOverE >= 0.037553)        return false;
    if(fabs(d0) >= 0.009924)      return false;
    if(fabs(dZ) >= 0.015310)      return false;
    if(ooEmooP >= 0.131191) return false;
    if(relIsoEA > 0.1649)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    //    if(pt <30)                 return false;
  }
  //Endcap
  else{
    if(fabs(eta)>2.4)           return false;
    if(fabs(dEta) >= 0.005681)    return false;
    if(fabs(dPhi) >= 0.032046)    return false;
    if(sigmaIetaIeta >= 0.028766) return false;
    if(hOverE >= 0.081902)        return false;
    if(fabs(d0) >= 0.0027261)      return false;
    if(fabs(dZ) >= 0.147154)      return false;
    if(ooEmooP >= 0.106055) return false;
    if(relIsoEA >= 0.090185)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    //    if(pt <30)                 return false;
  }
  return true;
}

bool TElectron::cutBasedLooseApr2015(){
  //Barrel
  if(fabs(eta) <= 1.479){
    if(fabs(dEta) >= 0.012442)    return false;
    if(fabs(dPhi) >= 0.072624)    return false;
    if(sigmaIetaIeta >= 0.010557) return false;
    if(hOverE >= 0.121476)         return false;
    if(fabs(d0) >= 0.022664)      return false;
    if(fabs(dZ) >= 0.173670)     return false;
    if(ooEmooP >= 0.221803) return false;
    if(relIsoEA >= 0.120026)          return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    //    if(pt <20)                 return false;
  }
  
  //Endcap
  else{
    if(fabs(eta)>2.4)           return false;
    if(fabs(dEta) >= 0.010654)    return false;
    if(fabs(dPhi) >= 0.145129)    return false;
    if(sigmaIetaIeta >= 0.032602)  return false;
    if(hOverE >= 0.131862)        return false;
    if(fabs(d0) >= 0.097358)       return false;
    if(fabs(dZ) >= 0.198444)      return false;
    if(ooEmooP >= 0.142283) return false;
    if(relIsoEA >= 0.162914)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    //    if(pt <20)                 return false;
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
    if(relIsoEA > 0.1649)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    //    if(pt <20)                 return false;
  }
  //Endcap
  else{
    if(fabs(eta)>2.4)           return false;
    if(fabs(dEta) > 0.0106)    return false;
    if(fabs(dPhi) > 0.0359)    return false;
    if(sigmaIetaIeta > 0.0305) return false;
    if(hOverE > 0.0835)        return false;
    if(fabs(d0) > 0.0163)      return false;
    if(fabs(dZ) > 0.5999)      return false;
    if(fabs(ooEmooP) > 0.1126) return false;
    if(relIsoEA > 0.2075)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    //    if(pt <20)                 return false;
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
    if(relIsoEA > 0.24)          return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    //    if(pt <20)                 return false;
  }

  //Endcap
  else{
    if(fabs(eta)>2.4)           return false;
    if(fabs(dEta) > 0.0124)    return false;
    if(fabs(dPhi) > 0.0642)    return false;
    if(sigmaIetaIeta > 0.035)  return false;
    if(hOverE > 0.1115)        return false;
    if(fabs(d0) > 0.098)       return false;
    if(fabs(dZ) > 0.9187)      return false;
    if(fabs(ooEmooP) > 0.1443) return false;
    if(relIsoEA > 0.3529)        return false;
    if(mHits > 1)              return false;
    if(chargeConsistency < 1)  return false;
    //    if(pt <20)                 return false;
  }
  return true;
}
