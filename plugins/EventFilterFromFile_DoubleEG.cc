#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

bool EventFilterFromFile_DoubleEG(int r, int l, long long e){

  std::ifstream file; file.open("eventlist_DoubleEG_csc2015.txt");
  std::string line;
  std::stringstream streamline;
  std::string info;
  int i=0;
  bool badEvent=false;


  int run=-1;
  int lumi =-1;
  long long event =-1;
  
  while(std::getline(file,line)){
    //std::cout<<line<<std::endl;
    streamline<<line;
    i=0;
    while(std::getline(streamline,info,':')){
      i++;
      if(i==1) run = std::stoi(info);
      if(i==2) lumi = std::stoi(info);
      if(i==3) event = std::stoi(info);
    }
    //std::cout<<"checking run: "<<run<<" lumi: "<<lumi<<" event: "<<event<<std::endl;
    //std::cout<<"current run: "<<r<<" lumi: "<<l<<" event: "<<e<<std::endl;

    //    std::cout<<"run: "<<run<<" lumi: "<<lumi<<" event: "<<event<<std::endl;

    //check if we have already passed it in terms of run number, which means it is a good event and we can stop checking
    if(run>r){ badEvent=false; break;}

    if(run==r && lumi==l && event==e){
      badEvent=true;
      break;
    }
    streamline.str( std::string() );
    streamline.clear();
  }


  return badEvent;

}

