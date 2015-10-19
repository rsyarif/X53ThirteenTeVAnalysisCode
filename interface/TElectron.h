#ifndef TElectron_h
#define TElectron_h

#include "TLepton.h"

class TElectron : public TLepton{
public:
  //constructor
  TElectron(double ptTemp,double etatemp,double phitemp, double energytemp, int chargetemp, int gsfCharget, int ctfCharget, int scpixCharget, double dEtatemp, double dPhitemp, double dZtemp,double d0temp,double hOverEtemp, double mHitstemp, double ooEmooPtemp, double sigmaIetaIetatemp, double chIsotemp,double puIsotemp, double neuIsotemp, double photIsotemp,double rhoIsotemp,double AEfftemp, int passConv,int chargeconsitencytemp, double mvatemp, double miniIsotemp);
  //varibles for charge
  int gsfCharge;
  int ctfCharge;
  int scpixCharge;
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
  double chIso;
  double puIso;
  double neutIso;
  double photIso;
  double rhoIso;
  double AEff;
  double relIsoDB;
  double relIsoEA;
  //passed conversion cuts
  int passConversion;
  //charge consistency
  int    chargeConsistency;

  // mvaID value and ID flags
  double mvaValue;
  double miniIso;

  bool mvaTight();
  bool mvaLoose();
  bool mvaTightIso();
  bool mvaLooseIso();

  bool mvaTightCC();
  bool mvaLooseCC();
  bool mvaTightCCIso();
  bool mvaLooseCCIso();
  bool mvaTightRCIso();
  bool mvaLooseRCIso();


  bool cutBasedTight50ns();
  bool cutBasedLoose50ns();
  bool cutBasedTight25nsSpring15MC();
  bool cutBasedLoose25nsSpring15MC();
  bool cutBasedTight25nsSpring15MCRC();
  bool cutBasedLoose25nsSpring15MCRC();
  bool cutBasedTightMay2015();
  bool cutBasedLooseMay2015();
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
    
    relIsoEA = 100;
    sigmaIetaIeta = -100;
    
    chargeConsistency = 0;

  }

};

#endif
