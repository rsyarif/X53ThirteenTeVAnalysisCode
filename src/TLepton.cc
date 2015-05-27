#include "../interface/TLepton.h"

//Leptons
TLepton::TLepton(double pttemp, double etatemp,double phitemp, double energytemp, int chargetemp) :
  pt(pttemp),
  eta(etatemp),
  phi(phitemp),
  energy(energytemp),
  charge(chargetemp)
{
  setLV();
}

