#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

bool EventFilterFromFile_MuonEG(int r, int l, int e){

  std::ifstream file; file.open("eventlist_MuonEG_csc2015.txt");
  std::string line;
  std::stringstream streamline;
  std::string info;
  int i=0;
  bool badEvent =false;

  int run=-1;
  int lumi=-1;
  int event=-1;
  
  while(std::getline(file,line)){
    streamline<<line;
    i=0;
    while(std::getline(streamline,info,':')){
      i++;
      if(i==1) run = std::stoi(info);
      if(i==2) lumi = std::stoi(info);
      if(i==3) event = std::stoi(info);
    }
    std::cout<<"checking run: "<<run<<" lumi: "<<lumi<<" event: "<<event<<std::endl;
    std::cout<<"current run: "<<r<<" lumi: "<<l<<" event: "<<e<<std::endl;
    if(run==r && lumi==l && event==e){
      badEvent=true;
      break;
    }
    streamline.str( std::string() );
    streamline.clear();

  }

  return badEvent;

}

