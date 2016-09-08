#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

bool EventFilterFromVector(int r, int l, long long e, std::vector<int> runs, std::vector<int> lumis, std::vector<unsigned long long> events){

  bool badEvent=false;


  for(unsigned int i=0; i<runs.size(); i++){
    //std::cout<<"checking run: "<<run<<" lumi: "<<lumi<<" event: "<<event<<std::endl;
    //std::cout<<"current run: "<<r<<" lumi: "<<l<<" event: "<<e<<std::endl;

    //    std::cout<<"run: "<<run<<" lumi: "<<lumi<<" event: "<<event<<std::endl;

    int run = runs.at(i);
    int lumi = lumis.at(i);
    unsigned long long event = events.at(i);

    //check if we have already passed it in terms of run number, which means it is a good event and we can stop checking
    if(run>r){ badEvent=false; break;}
    //another speedup in case of runs with many lumi sections to check
    else if( run==r && lumi>l){ badEvent=false; break;}
    if(run==r && lumi==l && event==e){
      badEvent=true;
      break;
    }
  }
  

  return badEvent;

}

