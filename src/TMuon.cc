#include "../interface/TMuon.h"


TMuon::TMuon(double pttemp,double etatemp,double phitemp, double energytemp, int chargetemp, int isLtemp, int isTtemp,bool globaltemp,bool pftemp, bool trackertemp, double chi2temp, int nMuHtemp, int nMatchStattemp, double dxytemp, double dztemp, int ValPixtemp,int nTracktemp, double relIsotemp):
  TLepton(pttemp,etatemp,phitemp,energytemp,chargetemp),isLoose(isLtemp),isTight(isTtemp),Global(globaltemp),PFMuon(pftemp),Tracker(trackertemp),chi2(chi2temp),
  nValMuHits(nMuHtemp), nMatchedStations(nMatchStattemp),dxy(dxytemp),dz(dztemp),nValPixelHits(ValPixtemp),nTrackerLayers(nTracktemp),relIso(relIsotemp)
{
  setLV();
}
bool TMuon::cutBasedLoose(){
  //  if (pt < 20)              return false;
  if (dxy > 2.0)            return false; //Cut relaxed from 0.2 to 2.0
  if(!(Tracker || Global))   return false;
  return true;
}

bool TMuon::cutBasedTight(){
  if(!Global)               return false;
  if(!PFMuon)               return false;
  //  if (pt < 30)              return false;
  //  if (global < 5)           return false; //Global muon and tracker muon
  if (chi2 > 10)            return false;
  if (dz > 0.5)             return false;
  if (dxy > 0.2)            return false;
  if (nValMuHits < 1)       return false;
  if (nMatchedStations < 2) return false;
  if (nValPixelHits < 1)    return false;
  if (nTrackerLayers < 6)   return false;
  if (relIso > 0.06)        return false;
  
  return true;
}
