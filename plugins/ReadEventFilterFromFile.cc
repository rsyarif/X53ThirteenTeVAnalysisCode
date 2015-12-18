#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


  //open file based on run numbers
/* if(r<256676)  file.open("csc2015_Dec01.txt");
  else if(r>=256676 && r<256677)  file.open("csc2015_Dec01_run256676.txt");
  else if(r>=256677 && r<256734)  file.open("csc2015_Dec01_run256677.txt");
  else if(r>=256734 && r<256844)  file.open("csc2015_Dec01_run256734.txt");
  else if(r>=256844 && r<257490)  file.open("csc2015_Dec01_run256866.txt");
  else if(r>=257490 && r<257751)  file.open("csc2015_Dec01_run257490.txt");
  else if(r>=257751 && r<258136)  file.open("csc2015_Dec01_run257751.txt");
  else if(r>=258136 && r<258211)  file.open("csc2015_Dec01_run258136.txt");
  else if(r>=258211 && r<258444)  file.open("csc2015_Dec01_run258211.txt");
  else if(r>=258444 && r<258713)  file.open("csc2015_Dec01_run258444.txt");
  else if(r>=258713 && r<259686)  file.open("csc2015_Dec01_run258713.txt");
  else if(r>=259686 && r<259891)  file.open("csc2015_Dec01_run259686.txt");
  else if(r>=259891 && r<260536)  file.open("csc2015_Dec01_run259891.txt");
  else if(r>=260536)  file.open("csc2015_Dec01_run260536.txt");*/


std::vector<int> getRunListFilterFromFile(std::string filename){
  std::ifstream file; 
  file.open(filename);
  
  std::string line;
  std::stringstream streamline;
  std::string info;
  int i=0;

  std::vector<int> runs;
  int run =-1;
  int lumi =-1;
  unsigned long long event =0;
  
  while(std::getline(file,line)){
    //std::cout<<line<<std::endl;
    streamline<<line;
    i=0;

    while(std::getline(streamline,info,':')){
      i++;
      if(i==1) run = std::stoi(info);
      if(i==2) lumi = std::stoi(info);
      if(i==3) event = std::stoull(info);
    }
    runs.push_back(run);
   
    streamline.str( std::string() );
    streamline.clear();
  }


  return runs;

}


std::vector<int> getLumiListFilterFromFile(std::string filename){
  std::ifstream file; 
  file.open(filename);
  
  std::string line;
  std::stringstream streamline;
  std::string info;
  int i=0;

  std::vector<int> lumis;
  int run =-1;
  int lumi =-1;
  unsigned long long event =0;
  
  while(std::getline(file,line)){
    //std::cout<<line<<std::endl;
    streamline<<line;
    i=0;
    while(std::getline(streamline,info,':')){
      i++;
      if(i==1) run = std::stoi(info);
      if(i==2) lumi = std::stoi(info);
      if(i==3) event = std::stoull(info);
    }
    lumis.push_back(lumi);
   
    streamline.str( std::string() );
    streamline.clear();
  }


  return lumis;

}

std::vector<unsigned long long> getEventListFilterFromFile(std::string filename){
  std::ifstream file; 
  file.open(filename);
  
  std::string line;
  std::stringstream streamline;
  std::string info;
  int i=0;

  std::vector<unsigned long long> events;
  int run =-1;
  int lumi =-1;
  unsigned long long event =0;
  
  while(std::getline(file,line)){
    //std::cout<<line<<std::endl;
    streamline<<line;
    i=0;
    while(std::getline(streamline,info,':')){
      i++;
      if(i==1) run = std::stoi(info);
      if(i==2) lumi = std::stoi(info);
      if(i==3) event = std::stoull(info);
    }
    events.push_back(event);
   
    streamline.str( std::string() );
    streamline.clear();
  }


  return events;

}

