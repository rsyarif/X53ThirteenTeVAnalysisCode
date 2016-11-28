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
std::stringstream& printFinalTable(std::stringstream& tablestring,std::vector<Sample*> vBkg, std::vector<Sample*> vSig, Sample* dataSample, std::vector<std::string> vCutString);
std::stringstream& printEffTable(std::stringstream& tablestring,std::vector<CutClass*> vCC, std::vector<std::string> vCS, int nmu,bool sig);
std::stringstream& printChargeMisIDTable_lpt(std::stringstream& chargeMisIDTable);
std::stringstream& printChargeMisIDTable_hpt(std::stringstream& chargeMisIDTable);
std::stringstream& printChargeMisIDTable_hhpt(std::stringstream& chargeMisIDTable);

void makeTables(){

  //make output file
  std::ofstream outfile;
  outfile.open("table_miniIso.txt");
  //set precision

  //set desired luminosity
  float lumi1 = 12.9; //fb^-1
  float lumi2 = 23.3; //fb^-1
  //get list of signal samples starting with ssdl cut
  std::vector<Sample*> vSig2016BD = getInclusiveSigSampleVecForTable("sZVeto",lumi1,"MVATightRC","CBTightMiniIso");
  std::vector<Sample*> vSig2016EH = getInclusiveSigSampleVecForTable("sZVeto",lumi2,"MVATightRC","CBTightMiniIso");

  //get vector of background samples
  std::vector<Sample*> vMCBkg2016BD = getMCBkgSampleVec("sZVeto",lumi1,"MVATightRC","CBTightMiniIso","");
  std::vector<Sample*> vMCBkg2016EH = getMCBkgSampleVec("sZVeto",lumi2,"MVATightRC","CBTightMiniIso","");
  std::vector<Sample*> vDDBkg =  getDDBkgSampleVec("sZVeto",lumi1,"MVATightRC","CBTightMiniIso","");
  //get vector of data
  Sample* dataSample = getDataSample("sZVeto","MVATightRC","CBTightMiniIso");

  //now get vector of cuts
  std::vector<std::string> vCutString = getCutString();

  for(size_t i =0; i<vCutString.size();i++){
    std::cout<<vCutString.at(i)<<std::endl;
  }

  bool Bkg=false;
  bool Sig=true;
  std::stringstream tables;
  //set precision
  tables<<std::fixed<<std::setprecision(2);
  for(int nmu=-1; nmu<3; nmu++){
    //now make a vector of cutClass for bkg
    std::vector<CutClass*> vCutMCBkg2016BD = getCutClassVector(vMCBkg2016BD,vCutString,nmu);
    std::vector<CutClass*> vCutMCBkg2016EH = getCutClassVector(vMCBkg2016EH,vCutString,nmu);
    std::vector<CutClass*> vCutMCBkg = addCutClassVectors(vCutMCBkg2016BD,vCutMCBkg2016EH);
    std::vector<CutClass*> vCutDDBkg = getCutClassVector(vDDBkg,vCutString,nmu);
    std::vector<CutClass*> vCutBkg = appendCutClassVectors(vCutMCBkg,vCutDDBkg);
    //now make a vector of cutClass for sig
    std::vector<CutClass*> vCutSig2016BD = getCutClassVector(vSig2016BD,vCutString,nmu);
    std::vector<CutClass*> vCutSig2016EH = getCutClassVector(vSig2016EH,vCutString,nmu);
    std::vector<CutClass*> vCutSig = addCutClassVectors(vCutSig2016BD,vCutSig2016EH);
    //now print background table
    tables<<std::fixed<<std::setprecision(2);
    printTable(tables,vCutBkg,vCutString,nmu,Bkg);
    printTable(tables,vCutSig,vCutString,nmu,Sig);
    tables<<std::fixed<<std::setprecision(4);
    printEffTable(tables,vCutBkg,vCutString,nmu,Bkg);
    printEffTable(tables,vCutSig,vCutString,nmu,Sig);
  }
  
  tables<<std::fixed<<std::setprecision(2);
  printFinalTable(tables,vBkg,vSig,dataSample,vCutString);

  //make charge misID table
  tables<<"\n";
  printChargeMisIDTable_lpt(tables);
  printChargeMisIDTable_hpt(tables);
  printChargeMisIDTable_hhpt(tables);
  outfile<<tables.str();

  outfile.close();
}

std::string tableHeader(std::vector<std::string> vC, CutClass* cC, std::string caption){

  std::stringstream str;

  str<<"\\begin{table}\n"<<"\\centering\n\\scriptsize\n"<<"\\topcaption{"<<caption<<"}\n"<<"\\begin{tabular}{|";
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
    float sys=0;
    if(vCC.at(i)->samplename=="NonPrompt") sys= pow(0.5, 2);
    else if(vCC.at(i)->samplename=="ChargeMisID") sys= pow(0.3, 2);
    else if(vCC.at(i)->samplename=="TTW") sys= pow(0.18, 2) + pow(0.04,2) + pow(0.06,2) + pow(0.02,2); //mc,jes,jer,pu
    else if(vCC.at(i)->samplename=="TTZ") sys= pow(0.11, 2) + pow(0.02,2)+ pow(0.06,2) + pow(0.02,2);
    else if(vCC.at(i)->samplename=="TTH") sys= pow(0.12, 2) + pow(0.04,2)+ pow(0.06,2) + pow(0.02,2);
    else if(vCC.at(i)->samplename=="TTTT") sys= pow(0.5, 2) + pow(0.03,2)+ pow(0.06,2) + pow(0.02,2);
    else if(vCC.at(i)->samplename=="WZ") sys= pow(0.12, 2) + pow(0.08,2)+ pow(0.06,2) + pow(0.02,2);
    else if(vCC.at(i)->samplename=="ZZ") sys= pow(0.12, 2) + pow(0.05,2)+ pow(0.06,2) + pow(0.02,2);
    else if(vCC.at(i)->samplename=="WpWp") sys= pow(0.5, 2) + pow(0.05,2)+ pow(0.06,2) + pow(0.02,2);
    else if(vCC.at(i)->samplename=="WWZ") sys= pow(0.5, 2) + pow(0.07,2)+ pow(0.06,2) + pow(0.02,2);
    else if(vCC.at(i)->samplename=="WZZ") sys= pow(0.5, 2) + pow(0.06,2)+ pow(0.06,2) + pow(0.02,2);
    else if(vCC.at(i)->samplename=="ZZZ") sys= pow(0.5, 2) + pow(0.06,2)+ pow(0.06,2) + pow(0.02,2);
    else if(vCC.at(i)->samplename.find("X53X53")!=std::string::npos) sys = pow(0.03,2)+ pow(0.01,2) + pow(0.01,2); //jes, jer, pu
    else sys = pow(0.5,2);
    if(! (vCC.at(i)->samplename=="NonPrompt" || vCC.at(i)->samplename=="ChargeMisID")){
      sys = sys + 2*pow(0.02,2) + pow(0.03,2) + pow(.046,2); //id iso and trigger  plus lumi 
    }
    tablestring<<vCC.at(i)->samplename;
    for(size_t j =0; j < (vCC.at(i)->nEvents).size(); j++){
      float errsys = sys*pow((vCC.at(i)->nEvents).at(j),2);
      float staterr = vCC.at(i)->vErr.at(j);
      float err = pow((vCC.at(i)->vErr).at(j),2) + errsys;
      if(vCC.at(i)->samplename=="NonPrompt" && nmu==0)std::cout<<vCC.at(i)->samplename<<" sys: "<<sys<<" systematic errors"<<pow(errsys,0.5)<<" stat errors: "<<staterr<<" total errors "<<err<<" nEvents: "<<vCC.at(i)->nEvents.at(j)<<std::endl;
      err = pow(err,0.5);
      tablestring<<" & "<<(vCC.at(i)->nEvents).at(j)<<" $\\pm$ "<<err;
    }
    tablestring<<" \\\\"<<std::endl;
  }
  tablestring<<"\\hline \n\\end{tabular} \n"<<label<<'\n'<<"\\end{table} \n\n";

  return tablestring;
 
}


std::stringstream& printEffTable(std::stringstream& tablestring,std::vector<CutClass*> vCC, std::vector<std::string> vCS, int nmu,bool sig){



  //caption
  std::string caption;
  if(sig){
    if(nmu==-1) caption = "Signal Efficiency Post Associated Z Veto vs. Analysis Cut for all channels combined";
    if(nmu==0) caption = "Signal Efficiency Post Associated Z Veto vs. Analysis Cut for di-electron channel";
    if(nmu==1) caption = "Signal Efficiency Post Associated Z Veto vs. Analysis Cut for electron-muon channel";
    if(nmu==2) caption = "Signal Efficiency Post Associated Z Veto vs. Analysis Cut for di-muon channel";
  }
  else{
    if(nmu==-1) caption = "Background Rejection Post Associated Z Veto vs. Analysis Cut for all channels combined";
    if(nmu==0) caption = "Background Rejection Post Associated Z Veto vs. Analysis Cut for di-electron channel";
    if(nmu==1) caption = "Background Rejection Post Associated Z Veto vs. Analysis Cut for electron-muon channel";
    if(nmu==2) caption = "Background Rejection Post Associated Z Veto vs. Analysis Cut for di-muon channel";
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
      float eff = vCC.at(i)->nEvents.at(j)/vCC.at(i)->nEvents.at(0);
      if(sig) tablestring<<" & "<<eff;
      else tablestring<<" & "<<(1-eff);
    }
    tablestring<<" \\\\"<<std::endl;
  }
  tablestring<<"\\hline \n\\end{tabular} \n"<<label<<'\n'<<"\\end{table} \n\n";

  return tablestring;
 
}



std::stringstream& printChargeMisIDTable_lpt(std::stringstream& table){


  table<<"\\begin{table}\n\\centering\n";
  table<<"\\topcaption{Charge misID rate for electrons where both electrons have a \\pt less than 100 GeV. Measured in data requiring two tight electrons with \\pt greater than 30 GeV and an invariant mass within 10 GeV of the Z-boson mass.}";
  table<<"\\begin{tabular}{|";
  for(int i=0;i<2;i++){
    table<<"c|";
  }

  table<<"}\n\\hline\\hline\n";

  table<<"Electron $\\eta$ & Charge MisID Rate\\\\\n\\hline\n";

  TFile* weightfile = new TFile("ChargeMisID_Data_Run2016_Electrons_MVATightRC_corrected.root");

  TH1F* h = (TH1F*) weightfile->Get("h_num_lpt");
  //TH1F* den = (TH1F*) weightfile->Get("etaDenHist_lpt");
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

std::stringstream& printChargeMisIDTable_hpt(std::stringstream& table){


  table<<"\\begin{table}\n\\centering\n";
  table<<"\\topcaption{Charge misID rate for electrons where either of the electron pair has \\pt above 100 GeV. Measured in data requiring two tight electrons with \\pt greater than 30 GeV and an invariant mass within 10 GeV of the Z-boson mass.}";
  table<<"\\begin{tabular}{|";
  for(int i=0;i<2;i++){
    table<<"c|";
  }

  table<<"}\n\\hline\\hline\n";

  table<<"Electron $\\eta$ & Charge MisID Rate\\\\\n\\hline\n";

  TFile* weightfile = new TFile("ChargeMisID_Data_Run2016_Electrons_MVATightRC_corrected.root");


  TH1F* h = (TH1F*) weightfile->Get("hpt_final");
  //TH1F* den = (TH1F*) weightfile->Get("etaDenHist_hpt");
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


std::stringstream& printChargeMisIDTable_hhpt(std::stringstream& table){


  table<<"\\begin{table}\n\\centering\n";
  table<<"\\topcaption{Charge misID rate for electrons where both electrons have \\pt above 100 GeV. Measured in data requiring two tight electrons with \\pt greater than 30 GeV and an invariant mass within 10 GeV of the Z-boson mass.}";
  table<<"\\begin{tabular}{|";
  for(int i=0;i<2;i++){
    table<<"c|";
  }

  table<<"}\n\\hline\\hline\n";

  table<<"Electron $\\eta$ & Charge MisID Rate\\\\\n\\hline\n";

  TFile* weightfile = new TFile("ChargeMisID_Data_Run2016_Electrons_MVATightRC_corrected.root");


  TH1F* h = (TH1F*) weightfile->Get("hhpt_final");
  //TH1F* den = (TH1F*) weightfile->Get("etaDenHist_hpt");
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

std::stringstream& printFinalTable(std::stringstream& tablestring,std::vector<Sample*> vBkg, std::vector<Sample*> vSig, Sample* dataSample, std::vector<std::string> vCutString){

  tablestring<<"\\begin{table}\n\\centering\n\\scriptsize\n\\begin{tabular}{|c|cccc|c|c|}\\hline\\hline\n";
  //caption
  std::string caption;
  caption = "Summary of expected and observed events for all channels. We show also the representative yields for an 1000 \\GeV \\xft. All systematic uncertainties are included.";
  tablestring<<"PSS MC&NonPrompt&ChargeMisID& Total Background & 1000 \\GeV \\xft&Observed\\\\\n";
  std::string label;
  //label
  label = "\\label{tab:FinalYields}";


  for(int nmu=-1; nmu<3; nmu++){
    //now make a vector of cutClass for bkg
    std::vector<CutClass*> vCutBkg = getCutClassVector(vBkg,vCutString,nmu);
    //now make a vector of cutClass for sig
    std::vector<CutClass*> vCutSig = getCutClassVector(vSig,vCutString,nmu);
    CutClass* cutSig = 0;
    for(unsigned int j=0; j<vCutSig.size();j++){
      if(vCutSig.at(j)->samplename.find("1000")!=std::string::npos && vCutSig.at(j)->samplename.find("RH")!=std::string::npos) cutSig = vCutSig.at(j);
    }

    //now get cutcalss fordata
    CutClass* cutData = makeCutClass(dataSample, vCutString, nmu);

    //first machinery to get events in nice format
    float events_mctot=0;
    float errors_mctot=0;
    float events_nptot=0;
    float errors_nptot=0;
    float events_cmtot=0;
    float errors_cmtot=0;
    float events_tot = 0;
    float errors_tot = 0;

    //get background events
    for(size_t i=0; i < vCutBkg.size(); i++){
      float sys=0;

      if(vCutBkg.at(i)->samplename=="NonPrompt") sys= pow(0.5, 2);
      else if(vCutBkg.at(i)->samplename=="ChargeMisID") sys= pow(0.3, 2);
      else if(vCutBkg.at(i)->samplename=="TTW") sys= pow(0.18, 2) + pow(0.04,2)+ pow(0.06,2) + pow(0.02,2); //mc,jes,pu,jer
      else if(vCutBkg.at(i)->samplename=="TTZ") sys= pow(0.11, 2) + pow(0.02,2)+ pow(0.06,2) + pow(0.02,2);
      else if(vCutBkg.at(i)->samplename=="TTH") sys= pow(0.12, 2) + pow(0.04,2)+ pow(0.06,2) + pow(0.02,2);
      else if(vCutBkg.at(i)->samplename=="TTTT") sys= pow(0.5, 2) + pow(0.03,2)+ pow(0.06,2) + pow(0.02,2);
      else if(vCutBkg.at(i)->samplename=="WZ") sys= pow(0.12, 2) + pow(0.08,2)+ pow(0.06,2) + pow(0.02,2);
      else if(vCutBkg.at(i)->samplename=="ZZ") sys= pow(0.12, 2) + pow(0.05,2)+ pow(0.06,2) + pow(0.02,2);
      else if(vCutBkg.at(i)->samplename=="WpWp") sys= pow(0.5, 2) + pow(0.05,2)+ pow(0.06,2) + pow(0.02,2);
      else if(vCutBkg.at(i)->samplename=="WWZ") sys= pow(0.5, 2) + pow(0.07,2)+ pow(0.06,2) + pow(0.02,2);
      else if(vCutBkg.at(i)->samplename=="WZZ") sys= pow(0.5, 2) + pow(0.06,2)+ pow(0.06,2) + pow(0.02,2);
      else if(vCutBkg.at(i)->samplename=="ZZZ") sys= pow(0.5, 2) + pow(0.06,2)+ pow(0.06,2) + pow(0.02,2);
      else if(vCutBkg.at(i)->samplename.find("X53X53")!=std::string::npos) sys = pow(0.03,2) + pow(0.01,2) + pow(0.01,2); //jes, jer, pu
      else sys = pow(0.5,2);
      if(! (vCutBkg.at(i)->samplename=="NonPrompt" || vCutBkg.at(i)->samplename=="ChargeMisID")){
	sys = sys + 2*pow(0.02,2) + pow(0.03,2) + pow(.046,2) + pow(0.05,2) + pow(0.05,2); //id iso and trigger  plus lumi  plus pileup plus dummy jer
      }
      //std::cout<<"sample: "<<vCutBkg.at(i)->samplename<<" and total systematic: "<<pow(sys,0.5)<<std::endl;

      for(size_t j =0; j < (vCutBkg.at(i)->nEvents).size(); j++){
	if(j < (vCutBkg.at(i)->nEvents).size() -1) continue; //only get the last yields
	float errsys = sys*pow((vCutBkg.at(i)->nEvents).at(j),2);
	float err = pow((vCutBkg.at(i)->vErr).at(j),2) + errsys;
	if(! (vCutBkg.at(i)->samplename=="NonPrompt" || vCutBkg.at(i)->samplename=="ChargeMisID")){ //only add together if MC background
	  events_mctot = events_mctot + (vCutBkg.at(i)->nEvents).at(j);
	  errors_mctot = errors_mctot + err;

	  events_tot = events_tot + (vCutBkg.at(i)->nEvents).at(j);
	  errors_tot = errors_tot + err;
	}      
	else if(vCutBkg.at(i)->samplename!="NonPrompt" && vCutBkg.at(i)->samplename=="ChargeMisID"){ //only add together if MC background
	  events_tot = events_tot + (vCutBkg.at(i)->nEvents).at(j);
	  errors_tot = errors_tot + err;
	  events_cmtot = (vCutBkg.at(i)->nEvents).at(j);
	  errors_cmtot = err;	  
	}
	else if(vCutBkg.at(i)->samplename=="NonPrompt" && vCutBkg.at(i)->samplename!="ChargeMisID"){ //only add together if MC background
	  events_tot = events_tot + (vCutBkg.at(i)->nEvents).at(j);
	  errors_tot = errors_tot + err;
	  events_nptot = (vCutBkg.at(i)->nEvents).at(j);
	  errors_nptot = err;	  
	}

      }


      
    }
  
    //now signal
    float sig = (cutSig->nEvents).at( (cutSig->nEvents).size()-1);
    
    //ok now I have all background, so get observed with no errors
   float obs =  (cutData->nEvents).at( (cutData->nEvents).size()-1);

   //write channel
   if(nmu==0) tablestring<<"Di-electron&";
   else if(nmu==1) tablestring<<"Electron-Muon&";
   else if(nmu==2) tablestring<<"Di-muon&";
   else tablestring<<"All&";
    //now write table line -- BLIND FOR NOW
   //tablestring<<"$"<<events_mctot<<"\\pm"<<pow(errors_mctot,0.5)<<"$&$"<<events_nptot<<"\\pm"<<pow(errors_nptot,0.5)<<"$&$"<<events_cmtot<<"\\pm"<<pow(errors_cmtot,0.5)<<"$ &$ "<<events_tot<<"\\pm"<<pow(errors_tot,0.5)<<"$&"<<sig<<" & "<<obs<<"\\\\\n"; 
   tablestring<<"$"<<events_mctot<<"\\pm"<<pow(errors_mctot,0.5)<<"$&$"<<events_nptot<<"\\pm"<<pow(errors_nptot,0.5)<<"$&$"<<events_cmtot<<"\\pm"<<pow(errors_cmtot,0.5)<<"$ &$ "<<events_tot<<"\\pm"<<pow(errors_tot,0.5)<<"$&"<<sig<<" & XXX\\\\\n"; 
  }//end loop over channels

  tablestring<<"\\hline \n\\end{tabular} \n"<<label<<'\n'<<"\\end{table} \n\n";

  return tablestring;


    
}
