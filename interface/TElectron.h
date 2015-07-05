#ifndef TElectron_h
#define TElectron_h

#include "TLepton.h"

class TElectron : public TLepton{
public:
  //cosntructor
  TElectron(double ptTemp,double etatemp,double phitemp, double energytemp, int chargetemp, double dEtatemp, double dPhitemp, double dZtemp,double d0temp,double hOverEtemp, double mHitstemp, double ooEmooPtemp, double sigmaIetaIetatemp, double relIsotemp,bool passConv,int chargeconsitencytemp);
  //variables for tracking cuts
  double dEta; 
  double dPhi;
  //variables for primary vtx cuts
  double dZ;
  double d0;
  // Hadronic energy divided by the Electromagnetic
  double hOverE;
  //Minimum hits
  double mHits;
  double ooEmooP;
  //shower shape
  double sigmaIetaIeta;
  //Isolation
  double relIso;
  //passed conversion cuts
  bool passConversion;
  //charge consistency
  int    chargeConsistency;

  bool cutBasedTight();
  bool cutBasedLoose();
  bool cutBasedTightApr2015();
  bool cutBasedLooseApr2015();
  bool CMSDASTight();
  bool CMSDASLoose();

  void init(){
    pt   = -100;
    eta  = -100;
    phi  = -100;
    
    dEta = -100;
    dPhi = -100;

    dZ   = -100;
    d0   = -100;
    
    hOverE  = -100;
    
    mHits   =  100;
    ooEmooP = -100;
    
    relIso = 100;
    sigmaIetaIeta = -100;
    
    chargeConsistency = 0;

  }

};

#endif
