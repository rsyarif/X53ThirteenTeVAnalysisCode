#include "../interface/TGenParticle.h"

TGenParticle::TGenParticle(){
}

TGenParticle::TGenParticle(double pttemp, double etatemp, double phitemp, double energytemp, int statustemp, int idtemp, int motherIdtemp) :
  pt(pttemp), eta(etatemp), phi(phitemp), energy(energytemp), status(statustemp), id(idtemp), motherId(motherIdtemp)
{

  if( (id==11) || (id==13) || (id==15)) charge =-1;
  else if( (id== -11) || (id == -13) || (id== -15) ) charge=1;
  else if( (id==1) || (id==3) || (id==5) ) charge = -0.333; 
  else if( (id==-1) || (id==-3) || (id==-5) ) charge = 0.333;
  else if( (id==2) || (id==4) || (id==6) ) charge= 0.667;
  else if( (id==-2) || (id==-4) || (id==-6) ) charge= -0.667;
  else charge=0;
  setLV();
}
