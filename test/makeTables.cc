#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "../plugins/Macros.cc"
#include "TFile.h"
#include "TTree.h"
#include "TGraphErrors.h"

std::string tableHeader(std::vector<std::string> vC, CutClass* c, std::string caption);
std::stringstream& printTable(std::stringstream& tablestring,std::vector<CutClass*> vCC, std::vector<std::string> vCS, int nmu,bool sig);
std::stringstream& printChargeMisIDTable(std::stringstream& chargeMisIDTable);

void makeTables(){

  //make output file
  std::ofstream outfile;
  outfile.open("table.txt");

  //set desired luminosity
  float lumi = 1.28; //fb^-1

  //get list of signal samples starting with ssdl cut
  std::vector<Sample*> vSig = getSigSampleVecForPlots("sZVeto",lumi,"MVATightRC","CBTight");

  //get vector of background samples
  std::vector<Sample*> vBkg = getBkgSampleVec("sZVeto",lumi,"MVATightRC","CBTight");

  //now get vector of cuts
  std::vector<string> vCutString = getCutString();

  for(size_t i =0; i<vCutString.size();i++){
    std::cout<<vCutString.at(i)<<std::endl;
  }

  bool Bkg=false;
  bool Sig=true;
  std::stringstream tables;
  for(int nmu=-1; nmu<3; nmu++){
    //now make a vector of cutClass for bkg
    std::vector<CutClass*> vCutBkg = getCutClassVector(vBkg,vCutString,nmu);
    //now make a vector of cutClass for sig
    std::vector<CutClass*> vCutSig = getCutClassVector(vSig,vCutString,nmu);
    //now print background table
    printTable(tables,vCutBkg,vCutString,nmu,Bkg);
    printTable(tables,vCutSig,vCutString,nmu,Sig);

  }
  
  //make charge misID table
  tables<<"\n";
  printChargeMisIDTable(tables);
  outfile<<tables.str();

  outfile.close();
}

std::string tableHeader(std::vector<std::string> vC, CutClass* cC, std::string caption){

  std::stringstream str;

  str<<"\\begin{table}\n"<<"\\centering\n"<<"\\topcaption{"<<caption<<"}\n"<<"\\begin{tabular}{|";
  for(size_t i =0; i< (vC.size()+1); i++){
    str<<"c|";
  }
  str<<"}\n\\hline\\hline\n";

  str<<"Sample";
  for(size_t i =0; i< (cC->cutname).size(); i++){
    str<<" & "<<(cC->cutname).at(i);
  }

  str<<"\\\\ \n";
  //std::cout<<str.str()<<std::endl;
  return str.str();
};

std::stringstream& printTable(std::stringstream& tablestring,std::vector<CutClass*> vCC, std::vector<std::string> vCS, int nmu,bool sig){



  //caption
  std::string caption;
  if(sig){
    if(nmu==-1) caption = "Expected Number of Signal Events vs. Analysis Cut for all channels combined";
    if(nmu==0) caption = "Expected Number of Signal Events vs. Analysis Cut for di-electron channel";
    if(nmu==1) caption = "Expected Number of Signal Events vs. Analysis Cut for electron-muon channel";
    if(nmu==2) caption = "Expected Number of Signal Events vs. Analysis Cut for di-muon channel";
  }
  else{
    if(nmu==-1) caption = "Expected Number of Background Events vs. Analysis Cut for all channels combined";
    if(nmu==0) caption = "Expected Number of Background Events vs. Analysis Cut for di-electron channel";
    if(nmu==1) caption = "Expected Number of Background Events vs. Analysis Cut for electron-muon channel";
    if(nmu==2) caption = "Expected Number of Background Events vs. Analysis Cut for di-muon channel";
  }


  //label
  std::string label;
  if(sig){
    if(nmu==-1) label = "\\label{tab:ExpSigEvtsAll}";
    if(nmu==0) label = "\\label{tab:ExpSigEvtsElEl}";
    if(nmu==1) label = "\\label{tab:ExpSigEvtsElMu}";
    if(nmu==2) label = "\\label{tab:ExpSigEvtsMuMu}";
  }
  else{
    if(nmu==-1) label = "\\label{tab:ExpBkgEvtsAll}";
    if(nmu==0) label = "\\label{tab:ExpBkgEvtsElEl}";
    if(nmu==1) label = "\\label{tab:ExpBkgEvtsElMu}";
    if(nmu==2) label = "\\label{tab:ExpBkgEvtsMuMu}";
  }

  tablestring<<tableHeader(vCS, vCC.at(0), caption); tablestring<<"\\hline \n";
  for(size_t i=0; i < vCC.size(); i++){
    tablestring<<vCC.at(i)->samplename;
    for(size_t j =0; j < (vCC.at(i)->nEvents).size(); j++){
      tablestring<<" & "<<(vCC.at(i)->nEvents).at(j);
    }
    tablestring<<" \\\\"<<std::endl;
  }
  tablestring<<"\\hline \n\\end{tabular} \n"<<label<<'\n'<<"\\end{table} \n\n";

  return tablestring;
 
}

std::stringstream& printChargeMisIDTable(std::stringstream& table){


  table<<"\\begin{table}\n\\centering\n";
  table<<"\\topcaption{Charge misID rate for electrons. Measured in DY MC requiring two tight electrons with \\pt greater than 30 GeV and an invariant mass within 20 GeV of the Z-boson mass.}";
  table<<"\\begin{tabular}{|";
  for(int i=0;i<2;i++){
    table<<"c|";
  }

  table<<"}\n\\hline\\hline\n";

  table<<"Electron $\\eta$ & Charge MisID Rate\\\\\n\\hline\n";

  TFile* weightfile = new TFile("ChargeMisID_Data_Run2015D_Electrons_MVATightRC.root");

  TH1F* h = (TH1F*) weightfile->Get("etaNumHist");
  TH1F* den = (TH1F*) weightfile->Get("etaDenHist");
  //h->Divide(den);
  TGraphErrors* g = new TGraphErrors(h);
  for(unsigned int j=0; j< g->GetN(); j++){
    std::cout<<"making point: "<<j<<" x bin: "<<g->GetX()[j]<<"+/-"<<g->GetErrorX(j)<<" and y value: "<<g->GetY()[j]<<std::endl;
    float xlow = g->GetX()[j] - g->GetErrorX(j);
    float xhigh = g->GetX()[j] + g->GetErrorX(j);
    std::string etabin = Form("%.1f $>\\eta>$ %.1f",xlow,xhigh);
    std::string misIDRate = Form("%1.5f",g->GetY()[j]);
    table<<etabin<<" & "<<misIDRate<<"\\\\\n";
  }

  table<<"\\hline\n\\end{tabular}\\end{table}";

  std::cout<<"made everything but table footer"<<std::endl;

  std::cout<<"made table footer"<<std::endl;

  return table;

}
