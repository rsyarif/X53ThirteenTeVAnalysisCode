#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include "../plugins/Sample.cc"
#include "../plugins/CutClass.cc"
#include "../interface/TreeReader.h"
#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "Math/ProbFunc.h"


std::string eosDirector = "root://cmseos.fnal.gov:/";
std::string samplesDir = "/store/group/lpcljm/LJMet102x_2lepTT_2018datasets_2018_11_29_rizki_hadds_Analyzer/";

std::vector<Variable*> getVariableVec(){

  std::vector<Variable*> vVar;
// 
//   //Variable* lep1ptEl = new Variable("Lep1PtEl",30,0,600,"Leading Lepton (electron) p_{T} (GeV)","N_{Events} / 20 GeV");
//   //vVar.push_back(lep1ptEl);
//   //Variable* lep1ptMu = new Variable("Lep1PtMu",30,0,600,"Leading Lepton (muon) p_{T} (GeV)","N_{Events} / 20 GeV");
//   //vVar.push_back(lep1ptMu);
// 
  Variable* lep1pt = new Variable("Lep1Pt",30,0,600,"Leading Lepton p_{T} (GeV)","N_{Events} / 20 GeV");
  vVar.push_back(lep1pt);
  Variable* lep1eta = new Variable("Lep1Eta",25,-5,5,"Leading Lepton #eta","N_{Events}");
  vVar.push_back(lep1eta);
//   Variable* lep1phi = new Variable("Lep1Phi",20,-3.5,3.5,"Leading Lepton #phi","N_{Events}");
//   vVar.push_back(lep1phi);
//   //Variable* lep1RelIso = new Variable("Lep1RelIso",40,0,1,"Leading Lepton Relative Isolation","N_{Events}");
//   //vVar.push_back(lep1RelIso);
//   Variable* lep1MiniIso = new Variable("Lep1MiniIso",40,0,1,"Leading Lepton MiniIsolation","N_{Events}");
//   vVar.push_back(lep1MiniIso);
//   //Variable* lep1SusyIso = new Variable("Lep1SusyIso",40,0,1,"Leading Lepton Susy Isolation","N_{Events}");
//   //vVar.push_back(lep1SusyIso);
// 
  Variable* lep2pt = new Variable("Lep2Pt",30,0,600,"subLeading Lepton p_{T} (GeV)","N_{Events} / 20 GeV");
  vVar.push_back(lep2pt);
  Variable* lep2eta = new Variable("Lep2Eta",25,-5,5,"subLeading Lepton #eta","N_{Events}");
  vVar.push_back(lep2eta);
//   Variable* lep2phi = new Variable("Lep2Phi",20,-3.5,3.5,"subLeading Lepton #phi","N_{Events}");
//   vVar.push_back(lep2phi);
//   //Variable* lep2RelIso = new Variable("Lep2RelIso",40,0,1,"Leading Lepton Relative Isolation","N_{Events}");
//   //vVar.push_back(lep2RelIso);
//   Variable* lep2MiniIso = new Variable("Lep2MiniIso",40,0,1,"Leading Lepton MiniIsolation","N_{Events}");
//   vVar.push_back(lep2MiniIso);
//   //Variable* lep2SusyIso = new Variable("Lep2SusyIso",40,0,1,"Leading Lepton Susy Isolation","N_{Events}");
//   //vVar.push_back(lep2SusyIso);
// 
// 
//   /*Variable* ak4jet1pt = new Variable("AK4Jet1Pt",15,0,600,"Leading Jet p_{T} (GeV)","N_{Events}");
//   vVar.push_back(ak4jet1pt);
//   Variable* ak4jet1eta = new Variable("AK4Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
//   vVar.push_back(ak4jet1eta);
//   Variable* ak4jet1phi = new Variable("AK4Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
//   vVar.push_back(ak4jet1phi);
// 
//   Variable* ak4jet2pt = new Variable("AK4Jet2Pt",15,0,600,"subLeading Jet p_{T} (GeV)","N_{Events}");
//   vVar.push_back(ak4jet2pt);
//   Variable* ak4jet2eta = new Variable("AK4Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
//   vVar.push_back(ak4jet2eta);
//   Variable* ak4jet2phi = new Variable("AK4Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
//   vVar.push_back(ak4jet2phi);
// 
// 
//   Variable* ak4ht = new Variable("AK4HT",20,0,3000,"AK4 H_{T} (GeV)","N_{Events}");
//   vVar.push_back(ak4ht);
//   Variable* nak4jets = new Variable("nAK4Jets",17,0,17,"N_{AK4 Jets}","N_{Events}");
//   vVar.push_back(nak4jets);*/
// 
//   //cleaned jet variables
  Variable* cleanak4jet1pt = new Variable("cleanAK4Jet1Pt",30,0,600,"Leading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(cleanak4jet1pt);
  Variable* cleanak4jet1eta = new Variable("cleanAK4Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
  vVar.push_back(cleanak4jet1eta);
//   Variable* cleanak4jet1phi = new Variable("cleanAK4Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
//   vVar.push_back(cleanak4jet1phi);
// 
  Variable* cleanak4jet2pt = new Variable("cleanAK4Jet2Pt",30,0,600,"subLeading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(cleanak4jet2pt);
  Variable* cleanak4jet2eta = new Variable("cleanAK4Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
  vVar.push_back(cleanak4jet2eta);
//   Variable* cleanak4jet2phi = new Variable("cleanAK4Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
//   vVar.push_back(cleanak4jet2phi);
// 
//   Variable* cleanak4htEl = new Variable("cleanAK4HTEl",25,0,3000,"H_{T}^{lep} (leading electron) (GeV)","N_{Events} / 120 GeV"); 
//   vVar.push_back(cleanak4htEl);
//   Variable* cleanak4htMu = new Variable("cleanAK4HTMu",25,0,3000,"H_{T}^{lep}(leading muon) (GeV)","N_{Events} / 120 GeV");
//   vVar.push_back(cleanak4htMu);
  Variable* cleanak4ht = new Variable("cleanAK4HT",25,0,3000,"H_{T}^{lep} (GeV)","Events / 120 GeV");
  vVar.push_back(cleanak4ht);
//   Variable* ncleanak4jets = new Variable("nCleanAK4Jets",17,0,17,"N_{AK4 Jets}","N_{Events}");
//   vVar.push_back(ncleanak4jets);
// 
//   /*
//   //new ak4 jets
//   Variable* newCleanak4jet1pt = new Variable("newCleanAK4Jet1Pt",30,0,600,"Leading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
//   vVar.push_back(newCleanak4jet1pt);
//   Variable* newCleanak4jet1eta = new Variable("newCleanAK4Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
//   vVar.push_back(newCleanak4jet1eta);
//   Variable* newCleanak4jet1phi = new Variable("newCleanAK4Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
//   vVar.push_back(newCleanak4jet1phi);
// 
//   Variable* newCleanak4jet2pt = new Variable("newCleanAK4Jet2Pt",30,0,600,"subLeading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
//   vVar.push_back(newCleanak4jet2pt);
//   Variable* newCleanak4jet2eta = new Variable("newCleanAK4Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
//   vVar.push_back(newCleanak4jet2eta);
//   Variable* newCleanak4jet2phi = new Variable("newCleanAK4Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
//   vVar.push_back(newCleanak4jet2phi);
// 
//   Variable* newCleanak4ht = new Variable("newCleanAK4HT",25,0,3000,"H_{T}^{lep} (GeV)","N_{Events} / 120 GeV");
//   vVar.push_back(newCleanak4ht);
//   Variable* nnewCleanak4jets = new Variable("nNewCleanAK4Jets",17,0,17,"N_{AK4 Jets}","N_{Events}");
//   vVar.push_back(nnewCleanak4jets);
// 
// 
//   //ak8jets
//   Variable* ak8jet1pt = new Variable("AK8Jet1Pt",30,0,600,"Leading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
//   vVar.push_back(ak8jet1pt);
//   Variable* ak8jet1eta = new Variable("AK8Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
//   vVar.push_back(ak8jet1eta);
//   Variable* ak8jet1phi = new Variable("AK8Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
//   vVar.push_back(ak8jet1phi);
// 
//   Variable* ak8jet1tau1 = new Variable("AK8Jet1Tau1",50,0,1,"#tau_{1}","N_{Events}");
//   vVar.push_back(ak8jet1tau1);
//   Variable* ak8jet1tau2 = new Variable("AK8Jet1Tau2",50,0,1,"#tau_{2}","N_{Events}");
//   vVar.push_back(ak8jet1tau2);
//   Variable* ak8jet1tau3 = new Variable("AK8Jet1Tau3",50,0,1,"#tau_{3}","N_{Events}");
//   vVar.push_back(ak8jet1tau3);
//   Variable* ak8jet1tau21 = new Variable("AK8Jet1Tau21",50,0,1,"#tau_{21}","N_{Events}");
//   vVar.push_back(ak8jet1tau21);
//   Variable* ak8jet1tau31 = new Variable("AK8Jet1Tau31",50,0,1,"#tau_{31}","N_{Events}");
//   vVar.push_back(ak8jet1tau31);
//   Variable* ak8jet1tau32 = new Variable("AK8Jet1Tau32",50,0,1,"#tau_{32}","N_{Events}");
//   vVar.push_back(ak8jet1tau32);
// 
// 
//   Variable* ak8jet1bdisc = new Variable("AK8Jet1SubjetMaxBDisc",50,0,1,"Max Subjet CSV Score","N_{Events}");
//   vVar.push_back(ak8jet1bdisc);
// 
//   Variable* ak8jet1trimmass = new Variable("AK8Jet1TrimMass",100,0,250,"Trimmed Mass","N_{Events}");
//   vVar.push_back(ak8jet1trimmass);
//   Variable* ak8jet1prunemass = new Variable("AK8Jet1PruneMass",100,0,250,"Pruned Mass","N_{Events}");
//   vVar.push_back(ak8jet1prunemass);
//   Variable* ak8jet1filtmass = new Variable("AK8Jet1FiltMass",100,0,250,"Filtered Mass","N_{Events}");
//   vVar.push_back(ak8jet1filtmass);
//   Variable* ak8jet1sdmass = new Variable("AK8Jet1SDMass",100,0,250,"SoftDrop Mass","N_{Events}");
//   vVar.push_back(ak8jet1sdmass);
// 
// 
//   Variable* ak8jet2pt = new Variable("AK8Jet2Pt",30,0,600,"subLeading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
//   vVar.push_back(ak8jet2pt);
//   Variable* ak8jet2eta = new Variable("AK8Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
//   vVar.push_back(ak8jet2eta);
//   Variable* ak8jet2phi = new Variable("AK8Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
//   vVar.push_back(ak8jet2phi);
// 
//   Variable* ak8jet2tau1 = new Variable("AK8Jet2Tau1",50,0,1,"#tau_{1}","N_{Events}");
//   vVar.push_back(ak8jet2tau1);
//   Variable* ak8jet2tau2 = new Variable("AK8Jet2Tau2",50,0,1,"#tau_{2}","N_{Events}");
//   vVar.push_back(ak8jet2tau2);
//   Variable* ak8jet2tau3 = new Variable("AK8Jet2Tau3",50,0,1,"#tau_{3}","N_{Events}");
//   vVar.push_back(ak8jet2tau3);
//   Variable* ak8jet2tau21 = new Variable("AK8Jet2Tau21",50,0,1,"#tau_{21}","N_{Events}");
//   vVar.push_back(ak8jet2tau21);
//   Variable* ak8jet2tau31 = new Variable("AK8Jet2Tau31",50,0,1,"#tau_{31}","N_{Events}");
//   vVar.push_back(ak8jet2tau31);
//   Variable* ak8jet2tau32 = new Variable("AK8Jet2Tau32",50,0,1,"#tau_{32}","N_{Events}");
//   vVar.push_back(ak8jet2tau32);
// 
// 
//   Variable* ak8jet2bdisc = new Variable("AK8Jet2SubjetMaxBDisc",50,0,1,"Max Subjet CSV Score","N_{Events}");
//   vVar.push_back(ak8jet2bdisc);
// 
//   Variable* ak8jet2trimmass = new Variable("AK8Jet2TrimMass",100,0,250,"Trimmed Mass","N_{Events}");
//   vVar.push_back(ak8jet2trimmass);
//   Variable* ak8jet2prunemass = new Variable("AK8Jet2PruneMass",100,0,250,"Pruned Mass","N_{Events}");
//   vVar.push_back(ak8jet2prunemass);
//   Variable* ak8jet2filtmass = new Variable("AK8Jet2FiltMass",100,0,250,"Filtered Mass","N_{Events}");
//   vVar.push_back(ak8jet2filtmass);
//   Variable* ak8jet2sdmass = new Variable("AK8Jet2SDMass",100,0,250,"SoftDrop Mass","N_{Events}");
//   vVar.push_back(ak8jet2sdmass);
//   */
// 
//   Variable* nnonssleps = new Variable("nNonSSLeps",17,0,17,"N_{Non-SS Leps}","N_{Events}");
//   vVar.push_back(nnonssleps);
// 
//   //simple cleaned jet variables
//   /*Variable* simpleCleanak4jet1pt = new Variable("simpleCleanAK4Jet1Pt",30,0,600,"Leading Jet p_{T} (GeV)","N_{Events}");
//   vVar.push_back(simpleCleanak4jet1pt);
//   Variable* simpleCleanak4jet1eta = new Variable("simpleCleanAK4Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
//   vVar.push_back(simpleCleanak4jet1eta);
//   Variable* simpleCleanak4jet1phi = new Variable("simpleCleanAK4Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
//   vVar.push_back(simpleCleanak4jet1phi);
// 
//   Variable* simpleCleanak4jet2pt = new Variable("simpleCleanAK4Jet2Pt",30,0,600,"subLeading Jet p_{T} (GeV)","N_{Events}");
//   vVar.push_back(simpleCleanak4jet2pt);
//   Variable* simpleCleanak4jet2eta = new Variable("simpleCleanAK4Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
//   vVar.push_back(simpleCleanak4jet2eta);
//   Variable* simpleCleanak4jet2phi = new Variable("simpleCleanAK4Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
//   vVar.push_back(simpleCleanak4jet2phi);
// 
// 
//   Variable* simpleCleanak4ht = new Variable("simpleCleanAK4HT",20,0,3000,"simpleCleanAK4 H_{T} (GeV)","N_{Events}");
//   vVar.push_back(simpleCleanak4ht);
//   Variable* nsimpleCleanak4jets = new Variable("nSimpleCleanAK4Jets",17,0,17,"N_{simpleCleanAK4 Jets}","N_{Events}");
//   vVar.push_back(nsimpleCleanak4jets);*/
// 
  Variable* nConst = new Variable("nConst",17,0,17,"N_{Const}","N_{Events}");
  vVar.push_back(nConst);
// 
//   //Variable* nNewConst = new Variable("nNewConst",17,0,17,"N_{Boosted Const}","N_{Events}");
//   //vVar.push_back(nNewConst);
// 
//   //Variable* nConstDiff = new Variable("nNewConst - nConst",10,-5,5,"N_{Boosted Const} - N_{Const}","N_{Events}");
//   //vVar.push_back(nConstDiff);
// 
//   //Variable* NTopTags = new Variable("NTopTags",5,0,5,"N_{Top Tagged Jets}","N_{Events}");
//   //vVar.push_back(NTopTags);
// 
//   //Variable* NWTags = new Variable("NWTags",5,0,5,"N_{W Tagged Jets}","N_{Events}");
//   //vVar.push_back(NWTags);
// 
//   //Variable* X53Mass = new Variable("X53Mass",50,100,2000,"M_{X53}","N_{Events}");
//   //vVar.push_back(X53Mass);
// 
//   Variable* met = new Variable("MET",60,0,600,"MET (GeV)", "N_{Events}");
//   vVar.push_back(met);
//   Variable* dilepMass = new Variable("DilepMass",20,0,600,"Dilepton Mass (GeV)", "N_{Events} / 30 GeV");
//   vVar.push_back(dilepMass);
//   
// 
//   Variable* nPV = new Variable("nPV",60,0,60,"N_{PV}","N_{Events}/bin");
//   vVar.push_back(nPV);
// 
//   Variable* lep1MinDR = new Variable("Lep1MinDR",70,0,7,"Min(#Delta_{R} (Lep1,jet))","N_{Events} / bin");
//   vVar.push_back(lep1MinDR);
// 
//   Variable* lep2MinDR = new Variable("Lep2MinDR",70,0,7,"Min(#Delta_{R} (Lep2,jet))","N_{Events} / bin");
//   vVar.push_back(lep2MinDR);
// 
  return vVar;
}

std::vector<Variable*> getVariableVecForBoosted(){

  std::vector<Variable*> vVar;

  Variable* lep1pt = new Variable("Lep1Pt",30,0,600,"Leading Lepton p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(lep1pt);
  Variable* lep1eta = new Variable("Lep1Eta",25,-5,5,"Leading Lepton #eta","N_{Events}");
  vVar.push_back(lep1eta);
  Variable* lep1phi = new Variable("Lep1Phi",20,-3.5,3.5,"Leading Lepton #phi","N_{Events}");
  vVar.push_back(lep1phi);

  Variable* lep2pt = new Variable("Lep2Pt",30,0,600,"subLeading Lepton p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(lep2pt);
  Variable* lep2eta = new Variable("Lep2Eta",25,-5,5,"subLeading Lepton #eta","N_{Events}");
  vVar.push_back(lep2eta);
  Variable* lep2phi = new Variable("Lep2Phi",20,-3.5,3.5,"subLeading Lepton #phi","N_{Events}");
  vVar.push_back(lep2phi);
  /*
  //cleaned jet variables
  Variable* cleanak4jet1pt = new Variable("cleanAK4Jet1Pt",30,0,600,"Leading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(cleanak4jet1pt);
  Variable* cleanak4jet1eta = new Variable("cleanAK4Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
  vVar.push_back(cleanak4jet1eta);
  Variable* cleanak4jet1phi = new Variable("cleanAK4Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
  vVar.push_back(cleanak4jet1phi);

  Variable* cleanak4jet2pt = new Variable("cleanAK4Jet2Pt",30,0,600,"subLeading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(cleanak4jet2pt);
  Variable* cleanak4jet2eta = new Variable("cleanAK4Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
  vVar.push_back(cleanak4jet2eta);
  Variable* cleanak4jet2phi = new Variable("cleanAK4Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
  vVar.push_back(cleanak4jet2phi);

  Variable* cleanak4ht = new Variable("cleanAK4HT",25,0,3000,"H_{T}^{lep} (GeV)","N_{Events} / 120 GeV");
  vVar.push_back(cleanak4ht);
  Variable* ncleanak4jets = new Variable("nCleanAK4Jets",17,0,17,"N_{AK4 Jets}","N_{Events}");
  vVar.push_back(ncleanak4jets);
*/

  //new ak4 jets
  Variable* newCleanak4jet1pt = new Variable("newCleanAK4Jet1Pt",30,0,600,"Leading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(newCleanak4jet1pt);
  Variable* newCleanak4jet1eta = new Variable("newCleanAK4Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
  vVar.push_back(newCleanak4jet1eta);
  Variable* newCleanak4jet1phi = new Variable("newCleanAK4Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
  vVar.push_back(newCleanak4jet1phi);

  Variable* newCleanak4jet2pt = new Variable("newCleanAK4Jet2Pt",30,0,600,"subLeading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(newCleanak4jet2pt);
  Variable* newCleanak4jet2eta = new Variable("newCleanAK4Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
  vVar.push_back(newCleanak4jet2eta);
  Variable* newCleanak4jet2phi = new Variable("newCleanAK4Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
  vVar.push_back(newCleanak4jet2phi);

  Variable* newCleanak4ht = new Variable("newCleanAK4HT",25,0,3000,"H_{T}^{lep} (GeV)","N_{Events} / 120 GeV");
  vVar.push_back(newCleanak4ht);
  Variable* nnewCleanak4jets = new Variable("nNewCleanAK4Jets",17,0,17,"N_{AK4 Jets}","N_{Events}");
  vVar.push_back(nnewCleanak4jets);


  //ak8jets
  Variable* ak8jet1pt = new Variable("AK8Jet1Pt",30,0,600,"Leading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(ak8jet1pt);
  Variable* ak8jet1eta = new Variable("AK8Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
  vVar.push_back(ak8jet1eta);
  Variable* ak8jet1phi = new Variable("AK8Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
  vVar.push_back(ak8jet1phi);

  Variable* ak8jet1tau1 = new Variable("AK8Jet1Tau1",50,0,1,"#tau_{1}","N_{Events}");
  vVar.push_back(ak8jet1tau1);
  Variable* ak8jet1tau2 = new Variable("AK8Jet1Tau2",50,0,1,"#tau_{2}","N_{Events}");
  vVar.push_back(ak8jet1tau2);
  Variable* ak8jet1tau3 = new Variable("AK8Jet1Tau3",50,0,1,"#tau_{3}","N_{Events}");
  vVar.push_back(ak8jet1tau3);
  Variable* ak8jet1tau21 = new Variable("AK8Jet1Tau21",50,0,1,"#tau_{21}","N_{Events}");
  vVar.push_back(ak8jet1tau21);
  Variable* ak8jet1tau31 = new Variable("AK8Jet1Tau31",50,0,1,"#tau_{31}","N_{Events}");
  vVar.push_back(ak8jet1tau31);
  Variable* ak8jet1tau32 = new Variable("AK8Jet1Tau32",50,0,1,"#tau_{32}","N_{Events}");
  vVar.push_back(ak8jet1tau32);


  Variable* ak8jet1bdisc = new Variable("AK8Jet1SubjetMaxBDisc",50,0,1,"Max Subjet CSV Score","N_{Events}");
  vVar.push_back(ak8jet1bdisc);

  Variable* ak8jet1trimmass = new Variable("AK8Jet1TrimMass",100,0,250,"Trimmed Mass","N_{Events}");
  vVar.push_back(ak8jet1trimmass);
  Variable* ak8jet1prunemass = new Variable("AK8Jet1PruneMass",100,0,250,"Pruned Mass","N_{Events}");
  vVar.push_back(ak8jet1prunemass);
  Variable* ak8jet1filtmass = new Variable("AK8Jet1FiltMass",100,0,250,"Filtered Mass","N_{Events}");
  vVar.push_back(ak8jet1filtmass);
  Variable* ak8jet1sdmass = new Variable("AK8Jet1SDMass",100,0,250,"SoftDrop Mass","N_{Events}");
  vVar.push_back(ak8jet1sdmass);


  Variable* ak8jet2pt = new Variable("AK8Jet2Pt",30,0,600,"subLeading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(ak8jet2pt);
  Variable* ak8jet2eta = new Variable("AK8Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
  vVar.push_back(ak8jet2eta);
  Variable* ak8jet2phi = new Variable("AK8Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
  vVar.push_back(ak8jet2phi);

  Variable* ak8jet2tau1 = new Variable("AK8Jet2Tau1",50,0,1,"#tau_{1}","N_{Events}");
  vVar.push_back(ak8jet2tau1);
  Variable* ak8jet2tau2 = new Variable("AK8Jet2Tau2",50,0,1,"#tau_{2}","N_{Events}");
  vVar.push_back(ak8jet2tau2);
  Variable* ak8jet2tau3 = new Variable("AK8Jet2Tau3",50,0,1,"#tau_{3}","N_{Events}");
  vVar.push_back(ak8jet2tau3);
  Variable* ak8jet2tau21 = new Variable("AK8Jet2Tau21",50,0,1,"#tau_{21}","N_{Events}");
  vVar.push_back(ak8jet2tau21);
  Variable* ak8jet2tau31 = new Variable("AK8Jet2Tau31",50,0,1,"#tau_{31}","N_{Events}");
  vVar.push_back(ak8jet2tau31);
  Variable* ak8jet2tau32 = new Variable("AK8Jet2Tau32",50,0,1,"#tau_{32}","N_{Events}");
  vVar.push_back(ak8jet2tau32);


  Variable* ak8jet2bdisc = new Variable("AK8Jet2SubjetMaxBDisc",50,0,1,"Max Subjet CSV Score","N_{Events}");
  vVar.push_back(ak8jet2bdisc);

  Variable* ak8jet2trimmass = new Variable("AK8Jet2TrimMass",100,0,250,"Trimmed Mass","N_{Events}");
  vVar.push_back(ak8jet2trimmass);
  Variable* ak8jet2prunemass = new Variable("AK8Jet2PruneMass",100,0,250,"Pruned Mass","N_{Events}");
  vVar.push_back(ak8jet2prunemass);
  Variable* ak8jet2filtmass = new Variable("AK8Jet2FiltMass",100,0,250,"Filtered Mass","N_{Events}");
  vVar.push_back(ak8jet2filtmass);
  Variable* ak8jet2sdmass = new Variable("AK8Jet2SDMass",100,0,250,"SoftDrop Mass","N_{Events}");
  vVar.push_back(ak8jet2sdmass);


  //topJetjets
  Variable* topjet1pt = new Variable("TopJet1Pt",30,0,600,"Leading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(topjet1pt);
  Variable* topjet1eta = new Variable("TopJet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
  vVar.push_back(topjet1eta);
  Variable* topjet1phi = new Variable("TopJet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
  vVar.push_back(topjet1phi);

  Variable* topjet1tau1 = new Variable("TopJet1Tau1",50,0,1,"#tau_{1}","N_{Events}");
  vVar.push_back(topjet1tau1);
  Variable* topjet1tau2 = new Variable("TopJet1Tau2",50,0,1,"#tau_{2}","N_{Events}");
  vVar.push_back(topjet1tau2);
  Variable* topjet1tau3 = new Variable("TopJet1Tau3",50,0,1,"#tau_{3}","N_{Events}");
  vVar.push_back(topjet1tau3);
  Variable* topjet1tau21 = new Variable("TopJet1Tau21",50,0,1,"#tau_{21}","N_{Events}");
  vVar.push_back(topjet1tau21);
  Variable* topjet1tau31 = new Variable("TopJet1Tau31",50,0,1,"#tau_{31}","N_{Events}");
  vVar.push_back(topjet1tau31);
  Variable* topjet1tau32 = new Variable("TopJet1Tau32",50,0,1,"#tau_{32}","N_{Events}");
  vVar.push_back(topjet1tau32);


  Variable* topjet1bdisc = new Variable("TopJet1SubjetMaxBDisc",50,0,1,"Max Subjet CSV Score","N_{Events}");
  vVar.push_back(topjet1bdisc);

  Variable* topjet1trimmass = new Variable("TopJet1TrimMass",100,0,250,"Trimmed Mass","N_{Events}");
  vVar.push_back(topjet1trimmass);
  Variable* topjet1prunemass = new Variable("TopJet1PruneMass",100,0,250,"Pruned Mass","N_{Events}");
  vVar.push_back(topjet1prunemass);
  Variable* topjet1filtmass = new Variable("TopJet1FiltMass",100,0,250,"Filtered Mass","N_{Events}");
  vVar.push_back(topjet1filtmass);
  Variable* topjet1sdmass = new Variable("TopJet1SDMass",100,0,250,"SoftDrop Mass","N_{Events}");
  vVar.push_back(topjet1sdmass);


  Variable* topjet2pt = new Variable("TopJet2Pt",30,0,600,"subLeading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(topjet2pt);
  Variable* topjet2eta = new Variable("TopJet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
  vVar.push_back(topjet2eta);
  Variable* topjet2phi = new Variable("TopJet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
  vVar.push_back(topjet2phi);

  Variable* topjet2tau1 = new Variable("TopJet2Tau1",50,0,1,"#tau_{1}","N_{Events}");
  vVar.push_back(topjet2tau1);
  Variable* topjet2tau2 = new Variable("TopJet2Tau2",50,0,1,"#tau_{2}","N_{Events}");
  vVar.push_back(topjet2tau2);
  Variable* topjet2tau3 = new Variable("TopJet2Tau3",50,0,1,"#tau_{3}","N_{Events}");
  vVar.push_back(topjet2tau3);
  Variable* topjet2tau21 = new Variable("TopJet2Tau21",50,0,1,"#tau_{21}","N_{Events}");
  vVar.push_back(topjet2tau21);
  Variable* topjet2tau31 = new Variable("TopJet2Tau31",50,0,1,"#tau_{31}","N_{Events}");
  vVar.push_back(topjet2tau31);
  Variable* topjet2tau32 = new Variable("TopJet2Tau32",50,0,1,"#tau_{32}","N_{Events}");
  vVar.push_back(topjet2tau32);


  Variable* topjet2bdisc = new Variable("TopJet2SubjetMaxBDisc",50,0,1,"Max Subjet CSV Score","N_{Events}");
  vVar.push_back(topjet2bdisc);

  Variable* topjet2trimmass = new Variable("TopJet2TrimMass",100,0,250,"Trimmed Mass","N_{Events}");
  vVar.push_back(topjet2trimmass);
  Variable* topjet2prunemass = new Variable("TopJet2PruneMass",100,0,250,"Pruned Mass","N_{Events}");
  vVar.push_back(topjet2prunemass);
  Variable* topjet2filtmass = new Variable("TopJet2FiltMass",100,0,250,"Filtered Mass","N_{Events}");
  vVar.push_back(topjet2filtmass);
  Variable* topjet2sdmass = new Variable("TopJet2SDMass",100,0,250,"SoftDrop Mass","N_{Events}");
  vVar.push_back(topjet2sdmass);

  //wjets
  Variable* wjet1pt = new Variable("WJet1Pt",30,0,600,"Leading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(wjet1pt);
  Variable* wjet1eta = new Variable("WJet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
  vVar.push_back(wjet1eta);
  Variable* wjet1phi = new Variable("WJet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
  vVar.push_back(wjet1phi);

  Variable* wjet1tau1 = new Variable("WJet1Tau1",50,0,1,"#tau_{1}","N_{Events}");
  vVar.push_back(wjet1tau1);
  Variable* wjet1tau2 = new Variable("WJet1Tau2",50,0,1,"#tau_{2}","N_{Events}");
  vVar.push_back(wjet1tau2);
  Variable* wjet1tau3 = new Variable("WJet1Tau3",50,0,1,"#tau_{3}","N_{Events}");
  vVar.push_back(wjet1tau3);
  Variable* wjet1tau21 = new Variable("WJet1Tau21",50,0,1,"#tau_{21}","N_{Events}");
  vVar.push_back(wjet1tau21);
  Variable* wjet1tau31 = new Variable("WJet1Tau31",50,0,1,"#tau_{31}","N_{Events}");
  vVar.push_back(wjet1tau31);
  Variable* wjet1tau32 = new Variable("WJet1Tau32",50,0,1,"#tau_{32}","N_{Events}");
  vVar.push_back(wjet1tau32);


  Variable* wjet1bdisc = new Variable("WJet1SubjetMaxBDisc",50,0,1,"Max Subjet CSV Score","N_{Events}");
  vVar.push_back(wjet1bdisc);

  Variable* wjet1trimmass = new Variable("WJet1TrimMass",100,0,250,"Trimmed Mass","N_{Events}");
  vVar.push_back(wjet1trimmass);
  Variable* wjet1prunemass = new Variable("WJet1PruneMass",100,0,250,"Pruned Mass","N_{Events}");
  vVar.push_back(wjet1prunemass);
  Variable* wjet1filtmass = new Variable("WJet1FiltMass",100,0,250,"Filtered Mass","N_{Events}");
  vVar.push_back(wjet1filtmass);
  Variable* wjet1sdmass = new Variable("WJet1SDMass",100,0,250,"SoftDrop Mass","N_{Events}");
  vVar.push_back(wjet1sdmass);


  Variable* wjet2pt = new Variable("WJet2Pt",30,0,600,"subLeading Jet p_{T} (GeV)","N_{Events} / 100 GeV");
  vVar.push_back(wjet2pt);
  Variable* wjet2eta = new Variable("WJet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
  vVar.push_back(wjet2eta);
  Variable* wjet2phi = new Variable("WJet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
  vVar.push_back(wjet2phi);

  Variable* wjet2tau1 = new Variable("WJet2Tau1",50,0,1,"#tau_{1}","N_{Events}");
  vVar.push_back(wjet2tau1);
  Variable* wjet2tau2 = new Variable("WJet2Tau2",50,0,1,"#tau_{2}","N_{Events}");
  vVar.push_back(wjet2tau2);
  Variable* wjet2tau3 = new Variable("WJet2Tau3",50,0,1,"#tau_{3}","N_{Events}");
  vVar.push_back(wjet2tau3);
  Variable* wjet2tau21 = new Variable("WJet2Tau21",50,0,1,"#tau_{21}","N_{Events}");
  vVar.push_back(wjet2tau21);
  Variable* wjet2tau31 = new Variable("WJet2Tau31",50,0,1,"#tau_{31}","N_{Events}");
  vVar.push_back(wjet2tau31);
  Variable* wjet2tau32 = new Variable("WJet2Tau32",50,0,1,"#tau_{32}","N_{Events}");
  vVar.push_back(wjet2tau32);


  Variable* wjet2bdisc = new Variable("WJet2SubjetMaxBDisc",50,0,1,"Max Subjet CSV Score","N_{Events}");
  vVar.push_back(wjet2bdisc);

  Variable* wjet2trimmass = new Variable("WJet2TrimMass",100,0,250,"Trimmed Mass","N_{Events}");
  vVar.push_back(wjet2trimmass);
  Variable* wjet2prunemass = new Variable("WJet2PruneMass",100,0,250,"Pruned Mass","N_{Events}");
  vVar.push_back(wjet2prunemass);
  Variable* wjet2filtmass = new Variable("WJet2FiltMass",100,0,250,"Filtered Mass","N_{Events}");
  vVar.push_back(wjet2filtmass);
  Variable* wjet2sdmass = new Variable("WJet2SDMass",100,0,250,"SoftDrop Mass","N_{Events}");
  vVar.push_back(wjet2sdmass);
  Variable* nConst = new Variable("nConst",17,0,17,"N_{Const}","N_{Events}");
  vVar.push_back(nConst);

  Variable* nNewConst = new Variable("nNewConst",17,0,17,"N_{Boosted Const}","N_{Events}");
  vVar.push_back(nNewConst);

  Variable* nConstDiff = new Variable("nNewConst - nConst",10,-5,5,"N_{Boosted Const} - N_{Const}","N_{Events}");
  vVar.push_back(nConstDiff);

  Variable* HTDiff = new Variable("newCleanAK4HT - cleanAK4HT",100,-200,800,"H^{l}_{T}(Boosted) - H^{l}_{T}","N_{Events}");
  vVar.push_back(HTDiff);

  Variable* NTopTags = new Variable("NTopTags",5,0,5,"N_{Top Tagged Jets}","N_{Events}");
  vVar.push_back(NTopTags);

  Variable* NWTags = new Variable("NWTags",5,0,5,"N_{W Tagged Jets}","N_{Events}");
  vVar.push_back(NWTags);

  Variable* X53Mass = new Variable("X53Mass",50,100,2000,"M_{X53}","N_{Events}");
  vVar.push_back(X53Mass);

  Variable* met = new Variable("MET",60,0,600,"MET (GeV)", "N_{Events}");
  vVar.push_back(met);
  Variable* dilepMass = new Variable("DilepMass",20,0,600,"Dilepton Mass (GeV)", "N_{Events} / 30 GeV");
  vVar.push_back(dilepMass);
  return vVar;

}

std::vector<Variable*> getVariablesForClosureTest(){

  std::vector<Variable*> vVar;

  Variable* lep1pt = new Variable("Lep1Pt",30,0,600,"Leading Lepton p_{T} (GeV)","N_{Events}");
  vVar.push_back(lep1pt);
  /*Variable* lep1eta = new Variable("Lep1Eta",25,-5,5,"Leading Lepton #eta","N_{Events}");
  vVar.push_back(lep1eta);
  Variable* lep1phi = new Variable("Lep1Phi",20,-3.5,3.5,"Leading Lepton #phi","N_{Events}");
  vVar.push_back(lep1phi);*/

  Variable* lep2pt = new Variable("Lep2Pt",30,0,600,"subLeading Lepton p_{T} (GeV)","N_{Events}");
  vVar.push_back(lep2pt);
  /*Variable* lep2eta = new Variable("Lep2Eta",25,-5,5,"subLeading Lepton #eta","N_{Events}");
  vVar.push_back(lep2eta);
  Variable* lep2phi = new Variable("Lep2Phi",20,-3.5,3.5,"subLeading Lepton #phi","N_{Events}");
  vVar.push_back(lep2phi);*/

  //cleaned jet variables
  Variable* cleanak4jet1pt = new Variable("cleanAK4Jet1Pt",30,0,600,"Leading Jet p_{T} (GeV)","N_{Events}");
  vVar.push_back(cleanak4jet1pt);
  /*Variable* cleanak4jet1eta = new Variable("cleanAK4Jet1Eta",25,-5,5,"Leading Jet #eta","N_{Events}");
  vVar.push_back(cleanak4jet1eta);
  Variable* cleanak4jet1phi = new Variable("cleanAK4Jet1Phi",20,-3.5,3.5,"Leading Jet #phi","N_{Events}");
  vVar.push_back(cleanak4jet1phi);*/

  Variable* cleanak4jet2pt = new Variable("cleanAK4Jet2Pt",30,0,600,"subLeading Jet p_{T} (GeV)","N_{Events}");
  vVar.push_back(cleanak4jet2pt);
  /*Variable* cleanak4jet2eta = new Variable("cleanAK4Jet2Eta",25,-5,5,"subLeading Jet #eta","N_{Events}");
  vVar.push_back(cleanak4jet2eta);
  Variable* cleanak4jet2phi = new Variable("cleanAK4Jet2Phi",20,-3.5,3.5,"subLeading Jet #phi","N_{Events}");
  vVar.push_back(cleanak4jet2phi);*/


  Variable* cleanak4ht = new Variable("cleanAK4HT",20,0,3000,"H_{T} (GeV)","N_{Events}");
  vVar.push_back(cleanak4ht);
  Variable* ncleanak4jets = new Variable("nCleanAK4Jets",17,0,17,"N_{AK4 Jets}","N_{Events}");
  vVar.push_back(ncleanak4jets);

  //Variable* nConst = new Variable("nConst",17,0,17,"N_{Const}","N_{Events}");
  //vVar.push_back(nConst);

  //Variable* met = new Variable("MET",60,0,600,"MET (GeV)", "N_{Events}");
  //vVar.push_back(met);
  Variable* dilepMass = new Variable("DilepMass",60,0,600,"Dilepton Mass (GeV)", "N_{Events}");
  vVar.push_back(dilepMass);
  return vVar;

}


std::vector<TH1F*> getNPHistos(int nMu){

  std::vector<TH1F*> hists;
  std::string channel;
  if(nMu==-1) channel="All";
  if(nMu==0) channel="ElEl";
  if(nMu==1) channel="ElMu";
  if(nMu==2) channel="MuMu";

  std::string nt00 = channel+"_HT_nConstCut_NT00";
  std::string nt01 = channel+"_HT_nConstCut_NT01";
  std::string nt10 = channel+"_HT_nConstCut_NT10";
  std::string nt11 = channel+"_HT_nConstCut_NT11";

  //10 gev bins sot hat later I can use bin number ask cut
  hists.push_back(new TH1F(nt00.c_str(),nt00.c_str(),1000,0,10000) );
  hists.push_back(new TH1F(nt01.c_str(),nt01.c_str(),1000,0,10000) );
  hists.push_back(new TH1F(nt10.c_str(),nt10.c_str(),1000,0,10000) );
  hists.push_back(new TH1F(nt11.c_str(),nt11.c_str(),1000,0,10000) );

  return hists;
}


Sample* getDataSample(std::string cut,std::string elID, std::string muID,std::string era){

  std::string filename = eosDirector+samplesDir+"/Data_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* tfile = TFile::Open(filename.c_str());
  Sample* dataSample = new Sample("Data",tfile,1,1,cut,kBlack,1);
  return dataSample;
}


std::vector<Sample*> getSigSampleVecForPlots(std::string cut, float lumi, std::string elID, std::string muID,std::string era){

  //br is OR of either side decaying to ssdl. BR(ssdl) for one side = BR(W->enu) OR BR(W->munu) OR BR(W->taunu) **2 where the square comes from AND requiring both to decay leptonically
  float BRssdl= 2*( pow((.1063 + .1071 + .1138),2));
  //make names vector
  //make x-sec vector - NEED TO FIX THESE VALUES************************************************
  //make vector for number of events ran to get weight
  std::vector<float> vNEvts;
  std::vector<std::string> vSigNames;  std::vector<float> vXsec;
  vSigNames.push_back("LH_X53X53_M-700");   vXsec.push_back(0.442*BRssdl);  vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-700"); vXsec.push_back(0.442*BRssdl);vNEvts.push_back(20000.);
  //vSigNames.push_back("LH_X53X53_M-1000"); vXsec.push_back(0.0427*BRssdl);vNEvts.push_back(20000.);
  //vSigNames.push_back("RH_X53X53_M-1000"); vXsec.push_back(0.0427*BRssdl);vNEvts.push_back(19400.);

  //FOR RUNNING ON INCLUSIVE DON'T APPLY BR TO SSDL!!
  //vXsec.push_back(0.442);vXsec.push_back(0.442);vXsec.push_back(0.0427);vXsec.push_back(0.0427);vXsec.push_back(0.00618);vXsec.push_back(0.00618);


  

  //vector to hold weights
  std::vector<float> vWeights;
  for(std::vector<float>::size_type i=0; i<vXsec.size();i++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(i) / vNEvts.at(i) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  std::vector<Sample*> vSigSamples;
  
  std::string lh700name =samplesDir+"test/X53X53m700LH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53700Lfile = TFile::Open(lh700name.c_str());
  Sample* x53x53m700L = new Sample(vSigNames.at(0),x53x53700Lfile,vWeights.at(0),vXsec.at(0),cut,kGreen,2);
  vSigSamples.push_back(x53x53m700L);

  std::string rh700name = samplesDir+"test/X53X53m700RH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53700Rfile = TFile::Open(rh700name.c_str());
  Sample* x53x53m700R = new Sample(vSigNames.at(1),x53x53700Rfile,vWeights.at(1),vXsec.at(1),cut,kGreen,1);
  vSigSamples.push_back(x53x53m700R);
  
  /* std::string lh1000name = samplesDir+"test/X53X53m1000LH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531000Lfile = TFile::Open(lh1000name.c_str());
  Sample* x53x53m1000L = new Sample(vSigNames.at(2),x53x531000Lfile,vWeights.at(2),vXsec.at(2),cut,kCyan,2);
  vSigSamples.push_back(x53x53m1000L);
  
  std::string rh1000name = samplesDir+"test/X53X53m1000RH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531000Rfile = TFile::Open(rh1000name.c_str());
  Sample* x53x53m1000R = new Sample(vSigNames.at(3),x53x531000Rfile,vWeights.at(3),vXsec.at(3),cut,kCyan,1);
  vSigSamples.push_back(x53x53m1000R);*/

  /*  TFile* x53x531300Lfile = TFile::Open(samplesDir+"test/X53X53m1300LH_"+era+".root");
  Sample* x53x53m1300L = new Sample(vSigNames.at(4),x53x531300Lfile,vWeights.at(4),vXsec.at(4),cut,kBlue,2);
  TFile* x53x531300Rfile = TFile::Open(samplesDir+"test/X53X53m1300RH_"+era+".root");
  Sample* x53x53m1300R = new Sample(vSigNames.at(5),x53x531300Rfile,vWeights.at(5),vXsec.at(5),cut,kBlue,1);
  */
  return vSigSamples;

}


std::vector<Sample*> getSigSampleVecForTable(std::string cut, float lumi, std::string elID, std::string muID,std::string era){
  //make names vector
  std::vector<std::string> vSigNames;
  std::vector<float> vXsec;
  //br is OR of either side decaying to ssdl. BR(ssdl) for one side = BR(W->enu) OR BR(W->munu) **2 where the square comes from AND requiring both to decay leptonically
  float BRssdl= 2*( pow((.1063 + .1071 + .1138),2));
  std::vector<int> vNEvts;
  vSigNames.push_back("LH_X53X53_M-700"); vXsec.push_back(0.442*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-700"); vXsec.push_back(0.442*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("LH_X53X53_M-800"); vXsec.push_back(.190*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-800"); vXsec.push_back(.190*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("LH_X53X53_M-900"); vXsec.push_back(.0877*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-900"); vXsec.push_back(.0877*BRssdl); vNEvts.push_back(19800.);
  vSigNames.push_back("LH_X53X53_M-1000"); vXsec.push_back(0.0427*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-1000"); vXsec.push_back(0.0427*BRssdl); vNEvts.push_back(19400.);
  vSigNames.push_back("LH_X53X53_M-1100"); vXsec.push_back(0.0217*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-1100"); vXsec.push_back(0.0217*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("LH_X53X53_M-1300"); vXsec.push_back(0.00618*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-1300"); vXsec.push_back(0.00618*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("LH_X53X53_M-1400"); vXsec.push_back(0.00342*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-1400"); vXsec.push_back(0.00342*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("LH_X53X53_M-1500"); vXsec.push_back(0.00193*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-1500"); vXsec.push_back(0.00193*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("LH_X53X53_M-1600"); vXsec.push_back(0.00111*BRssdl); vNEvts.push_back(20000.);
  vSigNames.push_back("RH_X53X53_M-1600"); vXsec.push_back(0.00111*BRssdl); vNEvts.push_back(20000.);

 

  //vector to hold weights
  std::vector<float> vWeights;
  for(std::vector<float>::size_type i=0; i<vXsec.size();i++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(i) / vNEvts.at(i) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  std::vector<Sample*> vSigSamples;
  std::string lh700 = samplesDir+"test/X53X53m700LH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53700Lfile = TFile::Open(lh700.c_str());
  Sample* x53x53m700L = new Sample(vSigNames.at(0),x53x53700Lfile,vWeights.at(0),vXsec.at(0),cut,kGreen,2);
  vSigSamples.push_back(x53x53m700L);
  std::string rh700 = samplesDir+"test/X53X53m700RH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53700Rfile = TFile::Open(rh700.c_str());
  Sample* x53x53m700R = new Sample(vSigNames.at(1),x53x53700Rfile,vWeights.at(1),vXsec.at(1),cut,kGreen,1);
  vSigSamples.push_back(x53x53m700R);

  std::string lh800 = samplesDir+"test/X53X53m800LH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53800Lfile = TFile::Open(lh800.c_str());
  Sample* x53x53m800L = new Sample(vSigNames.at(2),x53x53800Lfile,vWeights.at(2),vXsec.at(2),cut,kBlue,2);
  vSigSamples.push_back(x53x53m800L);
  std::string rh800 = samplesDir+"test/X53X53m800RH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53800Rfile = TFile::Open(rh800.c_str());
  Sample* x53x53m800R = new Sample(vSigNames.at(3),x53x53800Rfile,vWeights.at(3),vXsec.at(3),cut,kBlue,1);
  vSigSamples.push_back(x53x53m800R);

  std::string lh900 = samplesDir+"test/X53X53m900LH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53900Lfile = TFile::Open(lh900.c_str());
  Sample* x53x53m900L = new Sample(vSigNames.at(4),x53x53900Lfile,vWeights.at(4),vXsec.at(4),cut,kGreen,2);
  //vSigSamples.push_back(x53x53m900L);
  std::string rh900 = samplesDir+"test/X53X53m900RH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53900Rfile = TFile::Open(rh900.c_str());
  Sample* x53x53m900R = new Sample(vSigNames.at(5),x53x53900Rfile,vWeights.at(5),vXsec.at(5),cut,kGreen,1);
  vSigSamples.push_back(x53x53m900R);

  std::string lh1000 = samplesDir+"test/X53X53m1000LH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531000Lfile = TFile::Open(lh1000.c_str());
  Sample* x53x53m1000L = new Sample(vSigNames.at(6),x53x531000Lfile,vWeights.at(6),vXsec.at(6),cut,kCyan,2);
  //vSigSamples.push_back(x53x53m1000L);
  std::string rh1000 = samplesDir+"test/X53X53m1000RH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531000Rfile = TFile::Open(rh1000.c_str());
  Sample* x53x53m1000R = new Sample(vSigNames.at(7),x53x531000Rfile,vWeights.at(7),vXsec.at(7),cut,kCyan,1);
  vSigSamples.push_back(x53x53m1000R);

  std::string lh1100 = samplesDir+"test/X53X53m1100LH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531100Lfile = TFile::Open(lh1100.c_str());
  Sample* x53x53m1100L = new Sample(vSigNames.at(8),x53x531100Lfile,vWeights.at(8),vXsec.at(8),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1100L);
  std::string rh1100 = samplesDir+"test/X53X53m1100RH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531100Rfile = TFile::Open(rh1100.c_str());
  Sample* x53x53m1100R = new Sample(vSigNames.at(9),x53x531100Rfile,vWeights.at(9),vXsec.at(9),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1100R);

  std::string lh1300 = samplesDir+"test/X53X53m1300LH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531300Lfile = TFile::Open(lh1300.c_str());
  Sample* x53x53m1300L = new Sample(vSigNames.at(10),x53x531300Lfile,vWeights.at(10),vXsec.at(10),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1300L);
  std::string rh1300 = samplesDir+"test/X53X53m1300RH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531300Rfile = TFile::Open(rh1300.c_str());
  Sample* x53x53m1300R = new Sample(vSigNames.at(11),x53x531300Rfile,vWeights.at(11),vXsec.at(11),cut,kBlue,1);
  //vSigSamples.push_back(x53x53m1300R);

  std::string lh1400 = samplesDir+"test/X53X53m1400LH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531400Lfile = TFile::Open(lh1400.c_str());
  Sample* x53x53m1400L = new Sample(vSigNames.at(12),x53x531400Lfile,vWeights.at(12),vXsec.at(12),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1400L);
  std::string rh1400 = samplesDir+"test/X53X53m1400RH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531400Rfile = TFile::Open(rh1400.c_str());
  Sample* x53x53m1400R = new Sample(vSigNames.at(13),x53x531400Rfile,vWeights.at(13),vXsec.at(13),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1400R);

  std::string lh1500 = samplesDir+"test/X53X53m1500LH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531500Lfile = TFile::Open(lh1500.c_str());
  Sample* x53x53m1500L = new Sample(vSigNames.at(14),x53x531500Lfile,vWeights.at(14),vXsec.at(14),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1500L);
  std::string rh1500 = samplesDir+"test/X53X53m1500RH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531500Rfile = TFile::Open(rh1500.c_str());
  Sample* x53x53m1500R = new Sample(vSigNames.at(15),x53x531500Rfile,vWeights.at(15),vXsec.at(15),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1500R);

  /*  TFile* x53x531600Lfile = TFile::Open(samplesDir+"test/X53X53m1600LH_Mu"+muID+"_El"+elID+"_"+era+".root");
  Sample* x53x53m1600L = new Sample(vSigNames.at(16),x53x531600Lfile,vWeights.at(16),vXsec.at(16),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1600L);
  TFile* x53x531600Rfile = TFile::Open(samplesDir+"test/X53X53m1600RH_Mu"+muID+"_El"+elID+"_"+era+".root");
  Sample* x53x53m1600R = new Sample(vSigNames.at(17),x53x531600Rfile,vWeights.at(17),vXsec.at(17),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1600R);*/


  return vSigSamples;

}

std::vector<Sample*> getInclusiveSigSampleVecForTable(std::string cut, float lumi, std::string elID, std::string muID,std::string era){
  //make names vector
  std::vector<std::string> vSigNames;
  std::vector<float> vXsec;
  //br is OR of either side decaying to ssdl. BR(ssdl) for one side = BR(W->enu) OR BR(W->munu) **2 where the square comes from AND requiring both to decay leptonically
  //float BRssdl= 2*( pow((.1063 + .1071 + .1138),2)); INCLUSIVE SO NO BRANCHING RATIO
  std::vector<int> vNEvts;
  vSigNames.push_back("LH_X53X53_M-700"); vXsec.push_back(0.442); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-700"); vXsec.push_back(0.442); vNEvts.push_back(299800.);
  vSigNames.push_back("LH_X53X53_M-800"); vXsec.push_back(.190); vNEvts.push_back(279200.);
  vSigNames.push_back("RH_X53X53_M-800"); vXsec.push_back(.190); vNEvts.push_back(300000.);
  vSigNames.push_back("LH_X53X53_M-900"); vXsec.push_back(.0877); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-900"); vXsec.push_back(.0877); vNEvts.push_back(297756.);
  vSigNames.push_back("LH_X53X53_M-1000"); vXsec.push_back(0.0427); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-1000"); vXsec.push_back(0.0427); vNEvts.push_back(300000.);
  vSigNames.push_back("LH_X53X53_M-1100"); vXsec.push_back(0.0217); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-1100"); vXsec.push_back(0.0217); vNEvts.push_back(299457.);
  vSigNames.push_back("LH_X53X53_M-1200"); vXsec.push_back(0.0114); vNEvts.push_back(286278.);
  vSigNames.push_back("RH_X53X53_M-1200"); vXsec.push_back(0.0114); vNEvts.push_back(293410.);
  vSigNames.push_back("LH_X53X53_M-1300"); vXsec.push_back(0.00618); vNEvts.push_back(295800.);
  vSigNames.push_back("RH_X53X53_M-1300"); vXsec.push_back(0.00618); vNEvts.push_back(298000.);
  vSigNames.push_back("LH_X53X53_M-1400"); vXsec.push_back(0.00342); vNEvts.push_back(290311.);
  vSigNames.push_back("RH_X53X53_M-1400"); vXsec.push_back(0.00342); vNEvts.push_back(299600.);
  vSigNames.push_back("LH_X53X53_M-1500"); vXsec.push_back(0.00193); vNEvts.push_back(299200.);
  vSigNames.push_back("RH_X53X53_M-1500"); vXsec.push_back(0.00193); vNEvts.push_back(300000.);
  vSigNames.push_back("LH_X53X53_M-1600"); vXsec.push_back(0.00111); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-1600"); vXsec.push_back(0.00111); vNEvts.push_back(300000.);

 

  //vector to hold weights
  std::vector<float> vWeights;
  for(std::vector<float>::size_type i=0; i<vXsec.size();i++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(i) / vNEvts.at(i) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  std::vector<Sample*> vSigSamples;
  std::string lh700 = samplesDir+"test/X53X53m700LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53700Lfile = TFile::Open(lh700.c_str());
  Sample* x53x53m700L = new Sample(vSigNames.at(0),x53x53700Lfile,vWeights.at(0),vXsec.at(0),cut,kGreen,2);
  vSigSamples.push_back(x53x53m700L);
  std::string rh700 = samplesDir+"test/X53X53m700RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53700Rfile = TFile::Open(rh700.c_str());
  Sample* x53x53m700R = new Sample(vSigNames.at(1),x53x53700Rfile,vWeights.at(1),vXsec.at(1),cut,kGreen,1);
  vSigSamples.push_back(x53x53m700R);

  std::string lh800 = samplesDir+"test/X53X53m800LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53800Lfile = TFile::Open(lh800.c_str());
  Sample* x53x53m800L = new Sample(vSigNames.at(2),x53x53800Lfile,vWeights.at(2),vXsec.at(2),cut,kBlue,2);
  vSigSamples.push_back(x53x53m800L);
  std::string rh800 = samplesDir+"test/X53X53m800RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53800Rfile = TFile::Open(rh800.c_str());
  Sample* x53x53m800R = new Sample(vSigNames.at(3),x53x53800Rfile,vWeights.at(3),vXsec.at(3),cut,kBlue,1);
  vSigSamples.push_back(x53x53m800R);

  std::string lh900 = samplesDir+"test/X53X53m900LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53900Lfile = TFile::Open(lh900.c_str());
  Sample* x53x53m900L = new Sample(vSigNames.at(4),x53x53900Lfile,vWeights.at(4),vXsec.at(4),cut,kRed,2);
  vSigSamples.push_back(x53x53m900L);
  std::string rh900 = samplesDir+"test/X53X53m900RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53900Rfile = TFile::Open(rh900.c_str());
  Sample* x53x53m900R = new Sample(vSigNames.at(5),x53x53900Rfile,vWeights.at(5),vXsec.at(5),cut,kRed,1);
  vSigSamples.push_back(x53x53m900R);

  std::string lh1000 = samplesDir+"test/X53X53m1000LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531000Lfile = TFile::Open(lh1000.c_str());
  Sample* x53x53m1000L = new Sample(vSigNames.at(6),x53x531000Lfile,vWeights.at(6),vXsec.at(6),cut,kCyan,2);
  vSigSamples.push_back(x53x53m1000L);
  std::string rh1000 = samplesDir+"test/X53X53m1000RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531000Rfile = TFile::Open(rh1000.c_str());
  Sample* x53x53m1000R = new Sample(vSigNames.at(7),x53x531000Rfile,vWeights.at(7),vXsec.at(7),cut,kCyan,1);
  vSigSamples.push_back(x53x53m1000R);

  std::string lh1100 = samplesDir+"test/X53X53m1100LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531100Lfile = TFile::Open(lh1100.c_str());
  Sample* x53x53m1100L = new Sample(vSigNames.at(8),x53x531100Lfile,vWeights.at(8),vXsec.at(8),cut,kBlack,2);
  vSigSamples.push_back(x53x53m1100L);
  std::string rh1100 = samplesDir+"test/X53X53m1100RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531100Rfile = TFile::Open(rh1100.c_str());
  Sample* x53x53m1100R = new Sample(vSigNames.at(9),x53x531100Rfile,vWeights.at(9),vXsec.at(9),cut,kBlack,1);
  vSigSamples.push_back(x53x53m1100R);

  std::string lh1200 = samplesDir+"test/X53X53m1200LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531200Lfile = TFile::Open(lh1200.c_str());
  Sample* x53x53m1200L = new Sample(vSigNames.at(10),x53x531200Lfile,vWeights.at(10),vXsec.at(10),cut,kOrange,2);
  vSigSamples.push_back(x53x53m1200L);
  std::string rh1200 = samplesDir+"test/X53X53m1200RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531200Rfile = TFile::Open(rh1200.c_str());
  Sample* x53x53m1200R = new Sample(vSigNames.at(11),x53x531200Rfile,vWeights.at(11),vXsec.at(11),cut,kOrange,1);
  vSigSamples.push_back(x53x53m1200R);

  std::string lh1300 = samplesDir+"test/X53X53m1300LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531300Lfile = TFile::Open(lh1300.c_str());
  Sample* x53x53m1300L = new Sample(vSigNames.at(12),x53x531300Lfile,vWeights.at(12),vXsec.at(12),cut,kViolet,2);
  vSigSamples.push_back(x53x53m1300L);
  std::string rh1300 = samplesDir+"test/X53X53m1300RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531300Rfile = TFile::Open(rh1300.c_str());
  Sample* x53x53m1300R = new Sample(vSigNames.at(13),x53x531300Rfile,vWeights.at(13),vXsec.at(13),cut,kViolet,1);
  vSigSamples.push_back(x53x53m1300R);

  std::string lh1400 = samplesDir+"test/X53X53m1400LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531400Lfile = TFile::Open(lh1400.c_str());
  Sample* x53x53m1400L = new Sample(vSigNames.at(14),x53x531400Lfile,vWeights.at(14),vXsec.at(14),cut,kRed,2);
  vSigSamples.push_back(x53x53m1400L);
  std::string rh1400 = samplesDir+"test/X53X53m1400RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531400Rfile = TFile::Open(rh1400.c_str());
  Sample* x53x53m1400R = new Sample(vSigNames.at(15),x53x531400Rfile,vWeights.at(15),vXsec.at(15),cut,kRed,1);
  vSigSamples.push_back(x53x53m1400R);

  std::string lh1500 = samplesDir+"test/X53X53m1500LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531500Lfile = TFile::Open(lh1500.c_str());
  Sample* x53x53m1500L = new Sample(vSigNames.at(16),x53x531500Lfile,vWeights.at(16),vXsec.at(16),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1500L);
  std::string rh1500 = samplesDir+"test/X53X53m1500RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531500Rfile = TFile::Open(rh1500.c_str());
  Sample* x53x53m1500R = new Sample(vSigNames.at(17),x53x531500Rfile,vWeights.at(17),vXsec.at(17),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1500R);

  /*  TFile* x53x531600Lfile = TFile::Open(samplesDir+"test/X53X53m1600LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root");
  Sample* x53x53m1600L = new Sample(vSigNames.at(16),x53x531600Lfile,vWeights.at(16),vXsec.at(16),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1600L);
  TFile* x53x531600Rfile = TFile::Open(samplesDir+"test/X53X53m1600RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root");
  Sample* x53x53m1600R = new Sample(vSigNames.at(17),x53x531600Rfile,vWeights.at(17),vXsec.at(17),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1600R);*/


  return vSigSamples;

}

//added by rizki
std::vector<Sample*> getInclusiveSigTTSampleVecForTable(std::string cut, float lumi, std::string elID, std::string muID,std::string era){
  //make names vector
  std::vector<std::string> vSigNames;
  std::vector<float> vXsec;
  //RIZKI: EVENTUALLY NEED TO MODIFY BELO FOR TT BR
  //br is OR of either side decaying to ssdl. BR(ssdl) for one side = BR(W->enu) OR BR(W->munu) **2 where the square comes from AND requiring both to decay leptonically
  //float BRssdl= 2*( pow((.1063 + .1071 + .1138),2)); INCLUSIVE SO NO BRANCHING RATIO
  std::vector<int> vNEvts;
  vSigNames.push_back("TprimeTprime_M-800"); vXsec.push_back(0.196); vNEvts.push_back(795000.);
  vSigNames.push_back("TprimeTprime_M-900"); vXsec.push_back(0.0903); vNEvts.push_back(831200.);
  vSigNames.push_back("TprimeTprime_M-1000"); vXsec.push_back(0.0440); vNEvts.push_back(829600.);
  vSigNames.push_back("TprimeTprime_M-1100"); vXsec.push_back(0.0224); vNEvts.push_back(832800.);
  vSigNames.push_back("TprimeTprime_M-1200"); vXsec.push_back(0.0118); vNEvts.push_back(832600.);
  vSigNames.push_back("TprimeTprime_M-1300"); vXsec.push_back(0.00639); vNEvts.push_back(831000.);
  vSigNames.push_back("TprimeTprime_M-1400"); vXsec.push_back(0.00354); vNEvts.push_back(832600.);
  vSigNames.push_back("TprimeTprime_M-1500"); vXsec.push_back(0.00200); vNEvts.push_back(832800.);
  vSigNames.push_back("TprimeTprime_M-1600"); vXsec.push_back(0.001148); vNEvts.push_back(832600.);
  vSigNames.push_back("TprimeTprime_M-1700"); vXsec.push_back(0.000666); vNEvts.push_back(797000.);
  vSigNames.push_back("TprimeTprime_M-1800"); vXsec.push_back(0.000391); vNEvts.push_back(833000.);

 

  //vector to hold weights
  std::vector<float> vWeights;
  for(std::vector<float>::size_type i=0; i<vXsec.size();i++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(i) / vNEvts.at(i) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  std::vector<Sample*> vSigSamples;

//   std::string lh800 = samplesDir+"test/TprimeTprime_M-800_Mu"+muID+"_El"+elID+"_"+era+".root";
//   TFile* x53x53800Lfile = TFile::Open(lh800.c_str());
//   Sample* x53x53m800L = new Sample(vSigNames.at(0),x53x53800Lfile,vWeights.at(0),vXsec.at(0),cut,kBlue,2);
//   vSigSamples.push_back(x53x53m800L);
// 
//   std::string lh900 = samplesDir+"test/TprimeTprime_M-900_Mu"+muID+"_El"+elID+"_"+era+".root";
//   TFile* x53x53900Lfile = TFile::Open(lh900.c_str());
//   Sample* x53x53m900L = new Sample(vSigNames.at(1),x53x53900Lfile,vWeights.at(1),vXsec.at(1),cut,kRed,2);
//   vSigSamples.push_back(x53x53m900L);

  std::string lh1000 = samplesDir+"test/TprimeTprime_M-1000_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531000Lfile = TFile::Open(lh1000.c_str());
  Sample* x53x53m1000L = new Sample(vSigNames.at(2),x53x531000Lfile,vWeights.at(2),vXsec.at(2),cut,kCyan,2);
  vSigSamples.push_back(x53x53m1000L);

  std::string lh1100 = samplesDir+"test/TprimeTprime_M-1100_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531100Lfile = TFile::Open(lh1100.c_str());
  Sample* x53x53m1100L = new Sample(vSigNames.at(3),x53x531100Lfile,vWeights.at(3),vXsec.at(3),cut,kBlack,2);
  vSigSamples.push_back(x53x53m1100L);

  std::string lh1200 = samplesDir+"test/TprimeTprime_M-1200_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531200Lfile = TFile::Open(lh1200.c_str());
  Sample* x53x53m1200L = new Sample(vSigNames.at(4),x53x531200Lfile,vWeights.at(4),vXsec.at(4),cut,kOrange,2);
  vSigSamples.push_back(x53x53m1200L);

  std::string lh1300 = samplesDir+"test/TprimeTprime_M-1300_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531300Lfile = TFile::Open(lh1300.c_str());
  Sample* x53x53m1300L = new Sample(vSigNames.at(5),x53x531300Lfile,vWeights.at(5),vXsec.at(5),cut,kViolet,2);
  vSigSamples.push_back(x53x53m1300L);

  std::string lh1400 = samplesDir+"test/TprimeTprime_M-1400_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531400Lfile = TFile::Open(lh1400.c_str());
  Sample* x53x53m1400L = new Sample(vSigNames.at(6),x53x531400Lfile,vWeights.at(6),vXsec.at(6),cut,kRed,2);
  vSigSamples.push_back(x53x53m1400L);

  std::string lh1500 = samplesDir+"test/TprimeTprime_M-1500_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531500Lfile = TFile::Open(lh1500.c_str());
  Sample* x53x53m1500L = new Sample(vSigNames.at(7),x53x531500Lfile,vWeights.at(7),vXsec.at(7),cut,kBlue+2,2);
  vSigSamples.push_back(x53x53m1500L);

  std::string lh1600 = samplesDir+"test/TprimeTprime_M-1600_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531600Lfile = TFile::Open(lh1600.c_str());
  Sample* x53x53m1600L = new Sample(vSigNames.at(8),x53x531600Lfile,vWeights.at(8),vXsec.at(8),cut,kRed+2,2);
  vSigSamples.push_back(x53x53m1600L);



  return vSigSamples;

}

//added by rizki
std::vector<Sample*> getInclusiveSigTTSampleVecForTable(std::string cut, float lumi, std::string elID, std::string muID,std::string era,std::string sigDecay,int BRtype){
  //make names vector
  std::vector<std::string> vSigNames;
  std::vector<float> vXsec;

  float BR=0.;
    
  //Set TT
  float BR_bW=0.5;
  float BR_tZ=0.25;
  float BR_tH=0.25;
//   if(BRtype==0){BR_bW=0.5	;BR_tZ=0.25	;BR_tH=0.25	;} //nominal 
//   if(BRtype==1){BR_bW=0.	;BR_tZ=0.5	;BR_tH=0.5	;} // 
//   if(BRtype==2){BR_bW=0.	;BR_tZ=1.0	;BR_tH=0.	;} // 

  if(BRtype==0){BR_bW=0.5	;BR_tZ=0.25	;BR_tH=0.25	;} //nominal 
  if(BRtype==1){BR_bW=0.	;BR_tZ=1.0	;BR_tH=0.0	;} // 
  if(BRtype==2){BR_bW=0.	;BR_tZ=0.8	;BR_tH=0.2	;} // 
  if(BRtype==3){BR_bW=0.	;BR_tZ=0.6	;BR_tH=0.4	;} // 
  if(BRtype==4){BR_bW=0.	;BR_tZ=0.4	;BR_tH=0.6	;} // 
  if(BRtype==5){BR_bW=0.	;BR_tZ=0.2	;BR_tH=0.8	;} // 
  if(BRtype==6){BR_bW=0.	;BR_tZ=0.0	;BR_tH=1.0	;} // 
  if(BRtype==7){BR_bW=0.2	;BR_tZ=0.8	;BR_tH=0.0	;} // 
  if(BRtype==8){BR_bW=0.2	;BR_tZ=0.6	;BR_tH=0.2	;} // 
  if(BRtype==9){BR_bW=0.2	;BR_tZ=0.4	;BR_tH=0.4	;} // 
  if(BRtype==10){BR_bW=0.2	;BR_tZ=0.2	;BR_tH=0.6	;} // 
  if(BRtype==11){BR_bW=0.2	;BR_tZ=0.0	;BR_tH=0.8	;} // 
  if(BRtype==12){BR_bW=0.4	;BR_tZ=0.6	;BR_tH=0.0	;} // 
  if(BRtype==13){BR_bW=0.4	;BR_tZ=0.4	;BR_tH=0.2	;} // 
  if(BRtype==14){BR_bW=0.4	;BR_tZ=0.2	;BR_tH=0.4	;} // 
  if(BRtype==15){BR_bW=0.4	;BR_tZ=0.0	;BR_tH=0.6	;} // 
  if(BRtype==16){BR_bW=0.6	;BR_tZ=0.4	;BR_tH=0.0	;} // 
  if(BRtype==17){BR_bW=0.6	;BR_tZ=0.2	;BR_tH=0.2	;} // 
  if(BRtype==18){BR_bW=0.6	;BR_tZ=0.0	;BR_tH=0.4	;} // 
  if(BRtype==19){BR_bW=0.8	;BR_tZ=0.2	;BR_tH=0.0	;} // 
  if(BRtype==20){BR_bW=0.8	;BR_tZ=0.0	;BR_tH=0.2	;} // 
  if(BRtype==21){BR_bW=1.0	;BR_tZ=0.0	;BR_tH=0.0	;} // 
  if(BRtype==22){BR_bW=0.0	;BR_tZ=0.5	;BR_tH=0.5	;} // 
  if(sigDecay=="BWBW") BR = BR_bW*BR_bW;
  if(sigDecay=="TZTZ") BR = BR_tZ*BR_tZ;
  if(sigDecay=="THTH") BR = BR_tH*BR_tH;
  if(sigDecay=="THBW") BR = 2*BR_tH*BR_bW;
  if(sigDecay=="TZBW") BR = 2*BR_tZ*BR_bW;
  if(sigDecay=="TZTH") BR = 2*BR_tZ*BR_tH;
    
  std::cout << "Processing signal with BR : bW=" << BR_bW <<" tZ=" << BR_tZ <<" tH=" << BR_tH <<std::endl;


  float initBR; //MC sample initially has equal BR's for T -> bW, tZ,tH
  //TT
  if(sigDecay=="BWBW" || sigDecay=="TZTZ" || sigDecay=="THTH" ) initBR=0.333*0.333;
  if(sigDecay=="THBW" || sigDecay=="TZBW" || sigDecay=="TZTH" ) initBR=0.333*0.333*2;

  std::vector<int> vNEvts;
  vSigNames.push_back("TprimeTprime_M-800_"+sigDecay); vXsec.push_back(0.196); vNEvts.push_back(795000.); //2017
  vSigNames.push_back("TprimeTprime_M-900_"+sigDecay); vXsec.push_back(0.0903); vNEvts.push_back(831200.); //2017
  vSigNames.push_back("TprimeTprime_M-1000_"+sigDecay); vXsec.push_back(0.0440); vNEvts.push_back(812636.); //2017
  vSigNames.push_back("TprimeTprime_M-1100_"+sigDecay); vXsec.push_back(0.0224); vNEvts.push_back(706170.); //2017
  vSigNames.push_back("TprimeTprime_M-1200_"+sigDecay); vXsec.push_back(0.0118); vNEvts.push_back(767798.); //2017
  vSigNames.push_back("TprimeTprime_M-1300_"+sigDecay); vXsec.push_back(0.00639); vNEvts.push_back(757036.); //2017
  vSigNames.push_back("TprimeTprime_M-1400_"+sigDecay); vXsec.push_back(0.00354); vNEvts.push_back(693456.); //2017
  vSigNames.push_back("TprimeTprime_M-1500_"+sigDecay); vXsec.push_back(0.00200); vNEvts.push_back(661276.); //2017
  vSigNames.push_back("TprimeTprime_M-1600_"+sigDecay); vXsec.push_back(0.001148); vNEvts.push_back(622818.); //2017
  vSigNames.push_back("TprimeTprime_M-1700_"+sigDecay); vXsec.push_back(0.000666); vNEvts.push_back(542558.); //2017
  vSigNames.push_back("TprimeTprime_M-1800_"+sigDecay); vXsec.push_back(0.000391); vNEvts.push_back(455156.); //2017

 

  //vector to hold weights
  std::vector<float> vWeights;
  for(std::vector<float>::size_type i=0; i<vXsec.size();i++){
    vWeights.push_back( lumi * 1000 * ( (vXsec.at(i)*BR) / (vNEvts.at(i) * initBR) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  std::vector<Sample*> vSigSamples;
  
  std::string subfolder = "";
//   std::cout << "input signal subfolder:" << subfolder << std::endl;
//   std::cout << "checking input TT signal files:";
//   TString action = "eos "+eosDirector+" ls "+samplesDir+subfolder+"/Tprime*.root";
//   system(action);

  
//   std::string lh800 = samplesDir+subfolder+"/TprimeTprime_M-800_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
//   TFile* x53x53800Lfile = TFile::Open(lh800.c_str());
//   Sample* x53x53m800L = new Sample(vSigNames.at(0),x53x53800Lfile,vWeights.at(0),vXsec.at(0),cut,kBlue,2);
//   vSigSamples.push_back(x53x53m800L);
//   
//   std::string lh900 = samplesDir+subfolder+"/TprimeTprime_M-900_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
//   TFile* x53x53900Lfile = TFile::Open(lh900.c_str());
//   Sample* x53x53m900L = new Sample(vSigNames.at(1),x53x53900Lfile,vWeights.at(1),vXsec.at(1),cut,kRed,2);
//   vSigSamples.push_back(x53x53m900L);

  std::string lh1000 = eosDirector+samplesDir+subfolder+"/TprimeTprime_M-1000_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531000Lfile = TFile::Open(lh1000.c_str());
  Sample* x53x53m1000L = new Sample(vSigNames.at(2),x53x531000Lfile,vWeights.at(2),vXsec.at(2),cut,kCyan,2);
  vSigSamples.push_back(x53x53m1000L);

  std::string lh1100 = eosDirector+samplesDir+subfolder+"/TprimeTprime_M-1100_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531100Lfile = TFile::Open(lh1100.c_str());
  Sample* x53x53m1100L = new Sample(vSigNames.at(3),x53x531100Lfile,vWeights.at(3),vXsec.at(3),cut,kBlack,2);
  vSigSamples.push_back(x53x53m1100L);

  std::string lh1200 = eosDirector+samplesDir+subfolder+"/TprimeTprime_M-1200_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531200Lfile = TFile::Open(lh1200.c_str());
  Sample* x53x53m1200L = new Sample(vSigNames.at(4),x53x531200Lfile,vWeights.at(4),vXsec.at(4),cut,kOrange,2);
  vSigSamples.push_back(x53x53m1200L);

  std::string lh1300 = eosDirector+samplesDir+subfolder+"/TprimeTprime_M-1300_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531300Lfile = TFile::Open(lh1300.c_str());
  Sample* x53x53m1300L = new Sample(vSigNames.at(5),x53x531300Lfile,vWeights.at(5),vXsec.at(5),cut,kViolet,2);
  vSigSamples.push_back(x53x53m1300L);

  std::string lh1400 = eosDirector+samplesDir+subfolder+"/TprimeTprime_M-1400_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531400Lfile = TFile::Open(lh1400.c_str());
  Sample* x53x53m1400L = new Sample(vSigNames.at(6),x53x531400Lfile,vWeights.at(6),vXsec.at(6),cut,kRed,2);
  vSigSamples.push_back(x53x53m1400L);

  std::string lh1500 = eosDirector+samplesDir+subfolder+"/TprimeTprime_M-1500_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531500Lfile = TFile::Open(lh1500.c_str());
  Sample* x53x53m1500L = new Sample(vSigNames.at(7),x53x531500Lfile,vWeights.at(7),vXsec.at(7),cut,kBlue+2,2);
  vSigSamples.push_back(x53x53m1500L);

  std::string lh1600 = eosDirector+samplesDir+subfolder+"/TprimeTprime_M-1600_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531600Lfile = TFile::Open(lh1600.c_str());
  Sample* x53x53m1600L = new Sample(vSigNames.at(8),x53x531600Lfile,vWeights.at(8),vXsec.at(8),cut,kRed+2,2);
  vSigSamples.push_back(x53x53m1600L);

  std::string lh1700 = eosDirector+samplesDir+subfolder+"/TprimeTprime_M-1700_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531700Lfile = TFile::Open(lh1700.c_str());
  Sample* x53x53m1700L = new Sample(vSigNames.at(9),x53x531700Lfile,vWeights.at(9),vXsec.at(9),cut,kCyan+2,2);
  vSigSamples.push_back(x53x53m1700L);

  std::string lh1800 = eosDirector+samplesDir+subfolder+"/TprimeTprime_M-1800_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531800Lfile = TFile::Open(lh1800.c_str());
  Sample* x53x53m1800L = new Sample(vSigNames.at(10),x53x531800Lfile,vWeights.at(10),vXsec.at(10),cut,kOrange+2,2);
  vSigSamples.push_back(x53x53m1800L);



  return vSigSamples;

}

//added by rizki
std::vector<Sample*> getInclusiveSigBBSampleVecForTable(std::string cut, float lumi, std::string elID, std::string muID,std::string era,std::string sigDecay,int BRtype){
  //make names vector
  std::vector<std::string> vSigNames;
  std::vector<float> vXsec;

  float BR=0.;
      
  //again for BB
  float BR_tW=0.5;
  float BR_bZ=0.25;
  float BR_bH=0.25; 
//   if(BRtype==0){BR_tW=0.5;BR_bZ=0.25;BR_bH=0.25;} //nominal 
//   if(BRtype==1){BR_tW=0.;BR_bZ=0.5;BR_bH=0.5;} //
//   if(BRtype==2){BR_tW=1.0;BR_bZ=0.0;BR_bH=0.0;} //100% tW

  if(BRtype==0){BR_tW=0.5	;BR_bZ=0.25	;BR_bH=0.25	;} //nominal 
  if(BRtype==1){BR_tW=0.	;BR_bZ=1.0	;BR_bH=0.0	;} // 
  if(BRtype==2){BR_tW=0.	;BR_bZ=0.8	;BR_bH=0.2	;} // 
  if(BRtype==3){BR_tW=0.	;BR_bZ=0.6	;BR_bH=0.4	;} // 
  if(BRtype==4){BR_tW=0.	;BR_bZ=0.4	;BR_bH=0.6	;} // 
  if(BRtype==5){BR_tW=0.	;BR_bZ=0.2	;BR_bH=0.8	;} // 
  if(BRtype==6){BR_tW=0.	;BR_bZ=0.0	;BR_bH=1.0	;} // 
  if(BRtype==7){BR_tW=0.2	;BR_bZ=0.8	;BR_bH=0.0	;} // 
  if(BRtype==8){BR_tW=0.2	;BR_bZ=0.6	;BR_bH=0.2	;} // 
  if(BRtype==9){BR_tW=0.2	;BR_bZ=0.4	;BR_bH=0.4	;} // 
  if(BRtype==10){BR_tW=0.2	;BR_bZ=0.2	;BR_bH=0.6	;} // 
  if(BRtype==11){BR_tW=0.2	;BR_bZ=0.0	;BR_bH=0.8	;} // 
  if(BRtype==12){BR_tW=0.4	;BR_bZ=0.6	;BR_bH=0.0	;} // 
  if(BRtype==13){BR_tW=0.4	;BR_bZ=0.4	;BR_bH=0.2	;} // 
  if(BRtype==14){BR_tW=0.4	;BR_bZ=0.2	;BR_bH=0.4	;} // 
  if(BRtype==15){BR_tW=0.4	;BR_bZ=0.0	;BR_bH=0.6	;} // 
  if(BRtype==16){BR_tW=0.6	;BR_bZ=0.4	;BR_bH=0.0	;} // 
  if(BRtype==17){BR_tW=0.6	;BR_bZ=0.2	;BR_bH=0.2	;} // 
  if(BRtype==18){BR_tW=0.6	;BR_bZ=0.0	;BR_bH=0.4	;} // 
  if(BRtype==19){BR_tW=0.8	;BR_bZ=0.2	;BR_bH=0.0	;} // 
  if(BRtype==20){BR_tW=0.8	;BR_bZ=0.0	;BR_bH=0.2	;} // 
  if(BRtype==21){BR_tW=1.0	;BR_bZ=0.0	;BR_bH=0.0	;} // 
  if(BRtype==22){BR_tW=0.0	;BR_bZ=0.5	;BR_bH=0.5	;} // 

  if(sigDecay=="TWTW") BR = BR_tW*BR_tW;
  if(sigDecay=="BZBZ") BR = BR_bZ*BR_bZ;
  if(sigDecay=="BHBH") BR = BR_bH*BR_bH;
  if(sigDecay=="BHTW") BR = 2*BR_bH*BR_tW;
  if(sigDecay=="BZTW") BR = 2*BR_bZ*BR_tW;
  if(sigDecay=="BZBH") BR = 2*BR_bZ*BR_bH;


  
  std::cout << "Processing signal with BR : tW=" << BR_tW <<" bZ=" << BR_bZ <<" bH=" << BR_bH <<std::endl;


  float initBR; //MC sample initially has equal BR's for T -> bW, tZ,tH
  //BB
  if(sigDecay=="TWTW" || sigDecay=="BZBZ" || sigDecay=="BHBH" ) initBR=0.333*0.333;
  if(sigDecay=="BHTW" || sigDecay=="BZTW" || sigDecay=="BZBH" ) initBR=0.333*0.333*2;

  std::vector<int> vNEvts;
  vSigNames.push_back("BprimeBprime_M-800_"+sigDecay); vXsec.push_back(0.196); vNEvts.push_back(826200.);
  vSigNames.push_back("BprimeBprime_M-900_"+sigDecay); vXsec.push_back(0.0903); vNEvts.push_back(799800.);
  vSigNames.push_back("BprimeBprime_M-1000_"+sigDecay); vXsec.push_back(0.0440); vNEvts.push_back(825600.);
  vSigNames.push_back("BprimeBprime_M-1100_"+sigDecay); vXsec.push_back(0.0224); vNEvts.push_back(832000.);
  vSigNames.push_back("BprimeBprime_M-1200_"+sigDecay); vXsec.push_back(0.0118); vNEvts.push_back(832200.);
  vSigNames.push_back("BprimeBprime_M-1300_"+sigDecay); vXsec.push_back(0.00639); vNEvts.push_back(807200.);
  vSigNames.push_back("BprimeBprime_M-1400_"+sigDecay); vXsec.push_back(0.00354); vNEvts.push_back(816800.);
  vSigNames.push_back("BprimeBprime_M-1500_"+sigDecay); vXsec.push_back(0.00200); vNEvts.push_back(831000.);
  vSigNames.push_back("BprimeBprime_M-1600_"+sigDecay); vXsec.push_back(0.001148); vNEvts.push_back(696600.);
  vSigNames.push_back("BprimeBprime_M-1700_"+sigDecay); vXsec.push_back(0.000666); vNEvts.push_back(832600.);
  vSigNames.push_back("BprimeBprime_M-1800_"+sigDecay); vXsec.push_back(0.000391); vNEvts.push_back(795400.);

 

  //vector to hold weights
  std::vector<float> vWeights;
  for(std::vector<float>::size_type i=0; i<vXsec.size();i++){
    vWeights.push_back( lumi * 1000 * ( (vXsec.at(i)*BR) / (vNEvts.at(i) * initBR) ) ); //factor of 1000 to convert lumi to pb^-1
  }
  int i_weight = 0;

  std::vector<Sample*> vSigSamples;
  
  std::string subfolder = "";
  //std::string subfolder = "test/Bprime_postLJMet_exactly2goodLeptons_beforeSep26-2017";
  //std::cout << "checking input TT signal files:";
  //TString action = "ls "+eosDirector+samplesDir+subfolder+"/Bprime*.root";
  //system(action);

  std::string lh800 = eosDirector+samplesDir+subfolder+"/BprimeBprime_M-800_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53800Lfile = TFile::Open(lh800.c_str());
  Sample* x53x53m800L = new Sample(vSigNames.at(i_weight),x53x53800Lfile,vWeights.at(i_weight),vXsec.at(i_weight),cut,kBlue,2);
  vSigSamples.push_back(x53x53m800L);  
  i_weight=i_weight+1;

  std::string lh900 = eosDirector+samplesDir+subfolder+"/BprimeBprime_M-900_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53900Lfile = TFile::Open(lh900.c_str());
  Sample* x53x53m900L = new Sample(vSigNames.at(i_weight),x53x53900Lfile,vWeights.at(i_weight),vXsec.at(i_weight),cut,kRed,2);
  vSigSamples.push_back(x53x53m900L);
  i_weight=i_weight+1;

  std::string lh1000 = eosDirector+samplesDir+subfolder+"/BprimeBprime_M-1000_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531000Lfile = TFile::Open(lh1000.c_str());
  Sample* x53x53m1000L = new Sample(vSigNames.at(i_weight),x53x531000Lfile,vWeights.at(i_weight),vXsec.at(i_weight),cut,kCyan,2);
  vSigSamples.push_back(x53x53m1000L);
  i_weight=i_weight+1;

  std::string lh1100 = eosDirector+samplesDir+subfolder+"/BprimeBprime_M-1100_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531100Lfile = TFile::Open(lh1100.c_str());
  Sample* x53x53m1100L = new Sample(vSigNames.at(i_weight),x53x531100Lfile,vWeights.at(i_weight),vXsec.at(i_weight),cut,kBlack,2);
  vSigSamples.push_back(x53x53m1100L);
  i_weight=i_weight+1;

  std::string lh1200 = eosDirector+samplesDir+subfolder+"/BprimeBprime_M-1200_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531200Lfile = TFile::Open(lh1200.c_str());
  Sample* x53x53m1200L = new Sample(vSigNames.at(i_weight),x53x531200Lfile,vWeights.at(i_weight),vXsec.at(i_weight),cut,kOrange,2);
  vSigSamples.push_back(x53x53m1200L);
  i_weight=i_weight+1;

  std::string lh1300 = eosDirector+samplesDir+subfolder+"/BprimeBprime_M-1300_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531300Lfile = TFile::Open(lh1300.c_str());
  Sample* x53x53m1300L = new Sample(vSigNames.at(i_weight),x53x531300Lfile,vWeights.at(i_weight),vXsec.at(i_weight),cut,kViolet,2);
  vSigSamples.push_back(x53x53m1300L);
  i_weight=i_weight+1;

  std::string lh1400 = eosDirector+samplesDir+subfolder+"/BprimeBprime_M-1400_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531400Lfile = TFile::Open(lh1400.c_str());
  Sample* x53x53m1400L = new Sample(vSigNames.at(i_weight),x53x531400Lfile,vWeights.at(i_weight),vXsec.at(i_weight),cut,kRed,2);
  vSigSamples.push_back(x53x53m1400L);
  i_weight=i_weight+1;

  std::string lh1500 = eosDirector+samplesDir+subfolder+"/BprimeBprime_M-1500_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531500Lfile = TFile::Open(lh1500.c_str());
  Sample* x53x53m1500L = new Sample(vSigNames.at(i_weight),x53x531500Lfile,vWeights.at(i_weight),vXsec.at(i_weight),cut,kBlue+2,2);
  vSigSamples.push_back(x53x53m1500L);
  i_weight=i_weight+1;

  std::string lh1600 = eosDirector+samplesDir+subfolder+"/BprimeBprime_M-1600_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531600Lfile = TFile::Open(lh1600.c_str());
  Sample* x53x53m1600L = new Sample(vSigNames.at(i_weight),x53x531600Lfile,vWeights.at(i_weight),vXsec.at(i_weight),cut,kRed+2,2);
  vSigSamples.push_back(x53x53m1600L);
  i_weight=i_weight+1;

  std::string lh1700 = eosDirector+samplesDir+subfolder+"/BprimeBprime_M-1700_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531700Lfile = TFile::Open(lh1700.c_str());
  Sample* x53x53m1700L = new Sample(vSigNames.at(i_weight),x53x531700Lfile,vWeights.at(i_weight),vXsec.at(i_weight),cut,kCyan+2,2);
  vSigSamples.push_back(x53x53m1700L);
  i_weight=i_weight+1;

  std::string lh1800 = eosDirector+samplesDir+subfolder+"/BprimeBprime_M-1800_"+sigDecay+"_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531800Lfile = TFile::Open(lh1800.c_str());
  Sample* x53x53m1800L = new Sample(vSigNames.at(i_weight),x53x531800Lfile,vWeights.at(i_weight),vXsec.at(i_weight),cut,kOrange+2,2);
  vSigSamples.push_back(x53x53m1800L);



  return vSigSamples;

}

std::vector<Sample*> getSamplesForClosureTest(std::string cut, float lumi, std::string elID, std::string muID){  
  std::vector<std::string> vBkgNames;  std::vector<float> vXsec;  std::vector<float> vNEvts;
  vBkgNames.push_back("TTJets");  vXsec.push_back(831.76);  vNEvts.push_back(42730273 * 0.331582);
  vBkgNames.push_back("NonPromptTTJets");  vXsec.push_back(831.76);  vNEvts.push_back(42730273 * 0.331582);
  vBkgNames.push_back("TTbar");  vXsec.push_back(831.76);  vNEvts.push_back(115091972);
  vBkgNames.push_back("NonPromptTTbar");  vXsec.push_back(831.76);  vNEvts.push_back(115091972);

  //now make vector to hold weights;
  std::vector<float> vWeights;
  for(std::vector<float>::size_type ui=0; ui<vXsec.size(); ui++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(ui) / vNEvts.at(ui) ) ); //factor of 1000 to convert lumi to pb^-1
  }


  std::vector<Sample*> vSample;
  std::string tt = samplesDir+"test/TTJets_Mu"+muID+"_El"+elID+".root";
  TFile* ttfile = TFile::Open(tt.c_str());
  Sample* ttSample = new Sample(vBkgNames.at(0),ttfile, vWeights.at(0),vXsec.at(0),cut,kRed+2);
  vSample.push_back(ttSample);


  std::string nptt = samplesDir+"test/NonPromptTTJets_Mu"+muID+"_El"+elID+".root";
  TFile* npttfile = TFile::Open(nptt.c_str());
  Sample* npttSample = new Sample(vBkgNames.at(1),npttfile, vWeights.at(1),vXsec.at(1),cut,kBlue+2);
  vSample.push_back(npttSample);

  std::string ttb = samplesDir+"test/TTbar-powheg_Mu"+muID+"_El"+elID+".root";
  TFile* ttbfile = TFile::Open(ttb.c_str());
  Sample* ttbSample = new Sample(vBkgNames.at(2),ttbfile, vWeights.at(2),vXsec.at(2),cut,kGreen+2);
  vSample.push_back(ttbSample);

  std::string npttb = samplesDir+"test/NonPromptTTbar-powheg_Mu"+muID+"_El"+elID+".root";
  TFile* npttbfile = TFile::Open(npttb.c_str());
  Sample* npttbSample = new Sample(vBkgNames.at(3),npttbfile, vWeights.at(3),vXsec.at(3),cut,kBlack);
  vSample.push_back(npttbSample);

  return vSample;
}



std::vector<Sample*> getBkgSampleVec(std::string cut, float lumi, std::string elID, std::string muID, std::string era){  

   //setup info for list of samples, xsec and events run  //make vector of actual number of events run MULTIPLIED BY AMCATNLO WEIGHT
  std::vector<std::string> vBkgNames;  std::vector<float> vXsec;  std::vector<float> vNEvts;

  //************** MC *************
 //vBkgNames.push_back("TTbar");  vXsec.push_back(831.76);  vNEvts.push_back(42730273 * 0.331582);
  vBkgNames.push_back("TTZ");    vXsec.push_back(0.2529);  vNEvts.push_back(398600 * 0.464706);
  vBkgNames.push_back("TTW");    vXsec.push_back(0.2043);  vNEvts.push_back(252673*0.515587);
  vBkgNames.push_back("TTH");    vXsec.push_back(0.215);  vNEvts.push_back(9984160 *0.296787);
  vBkgNames.push_back("TTTT");    vXsec.push_back(0.009103);  vNEvts.push_back(989025 *0.417453);
  vBkgNames.push_back("WZ");     vXsec.push_back(4.42965); vNEvts.push_back(2000000 * 1);
  //vBkgNames.push_back("WJets");  vXsec.push_back(61526.7); vNEvts.push_back(24151270 * 0.683948);
  //vBkgNames.push_back("DYJets"); vXsec.push_back(6025.2);  vNEvts.push_back(28825132 * 0.6693);
  vBkgNames.push_back("ZZ");     vXsec.push_back(1.212);  vNEvts.push_back(6638328 * 1);
  vBkgNames.push_back("VH");     vXsec.push_back(0.952);  vNEvts.push_back(993464 * 1);
  vBkgNames.push_back("WpWp");   vXsec.push_back(0.03711); vNEvts.push_back( 118350* 1);
  vBkgNames.push_back("WW-mpi"); vXsec.push_back(1.64);   vNEvts.push_back( 843514* 1);  
  vBkgNames.push_back("WWZ");    vXsec.push_back(0.1651); vNEvts.push_back(249200*0.885963);
  vBkgNames.push_back("WZZ");    vXsec.push_back(0.05565); vNEvts.push_back(249800*0.876645);
  vBkgNames.push_back("ZZZ");    vXsec.push_back(0.01398); vNEvts.push_back(250000* 0.8554);
  
  //******* Non Prompt**********
  //vBkgNames.push_back("NonPromptMC");  vXsec.push_back(831.76);  vNEvts.push_back(42730273 * 0.331582);
  vBkgNames.push_back("NonPrompt"); vXsec.push_back(1); vNEvts.push_back(1);
  vBkgNames.push_back("ChargeMisID"); vXsec.push_back(1); vNEvts.push_back(1);
  //now make vector to hold weights;
  std::vector<float> vWeights;
  for(std::vector<float>::size_type ui=0; ui<vXsec.size(); ui++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(ui) / vNEvts.at(ui) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  //now make samples and add to vector
  std::vector<Sample*> vSample;
  //TFile* ttfile = TFile::Open(samplesDir+"test/TTbar.root");
  //Sample* ttSample = new Sample(vBkgNames.at(0),ttfile, vWeights.at(0),vXsec.at(0),cut,kRed+2);
  //vSample.push_back(ttSample);

  std::string ttZfilename = samplesDir+"test/TTZ_Mu"+muID+"_El"+elID+".root";
  TFile* ttZfile = TFile::Open(ttZfilename.c_str());
  Sample* ttZSample = new Sample(vBkgNames.at(0),ttZfile, vWeights.at(0),vXsec.at(0),cut,kRed);
  vSample.push_back(ttZSample);

  std::string ttWfilename = samplesDir+"test/TTW_Mu"+muID+"_El"+elID+".root";
  TFile* ttwfile = TFile::Open(ttWfilename.c_str());
  Sample* ttwSample = new Sample(vBkgNames.at(1),ttwfile, vWeights.at(1),vXsec.at(1),cut,kYellow-2);
  vSample.push_back(ttwSample);

  std::string tthfilename = samplesDir+"test/TTH_Mu"+muID+"_El"+elID+".root";
  TFile* tthfile = TFile::Open(tthfilename.c_str());
  Sample* tthSample = new Sample(vBkgNames.at(2),tthfile, vWeights.at(2),vXsec.at(2),cut,kYellow);
  vSample.push_back(tthSample);

  std::string ttttfilename = samplesDir+"test/TTTT_Mu"+muID+"_El"+elID+".root";
  TFile* ttttfile = TFile::Open(ttttfilename.c_str());
  Sample* ttttSample = new Sample(vBkgNames.at(3),ttttfile, vWeights.at(3),vXsec.at(3),cut,kRed+2);
  vSample.push_back(ttttSample);


  std::string wzfilename=samplesDir+"test/WZ_Mu"+muID+"_El"+elID+".root";
  TFile* wzfile = TFile::Open(wzfilename.c_str());
  Sample* wzSample = new Sample(vBkgNames.at(4),wzfile, vWeights.at(4),vXsec.at(4),cut,kBlue-3);
  vSample.push_back(wzSample);

  //TFile* wjfile = TFile::Open(samplesDir+"test/WJets_Mu"+muID+"_El"+elID+".root");
  //Sample* wjSample = new Sample(vBkgNames.at(4),wjfile, vWeights.at(4),vXsec.at(4),cut,kGreen+2);
  //vSample.push_back(wjSample);

  /*std::string dyfilename =  samplesDir+"test/DYJets_Mu"+muID+"_El"+elID+".root";
  TFile* dyjfile = TFile::Open(dyfilename.c_str());
  Sample* dyjSample = new Sample(vBkgNames.at(3),dyjfile, vWeights.at(3),vXsec.at(3),cut,kMagenta+2);
  vSample.push_back(dyjSample);*/
  
  std::string zzfilename = samplesDir+"test/ZZ_Mu"+muID+"_El"+elID+".root";
  TFile* zzjfile = TFile::Open(zzfilename.c_str());
  Sample* zzjSample = new Sample(vBkgNames.at(5),zzjfile, vWeights.at(5),vXsec.at(5),cut,kOrange+1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(zzjSample);

  //std::string vhfilename = samplesDir+"test/VH_Mu"+muID+"_El"+elID+".root";
  //TFile* vhjfile = TFile::Open(vhfilename.c_str());
  //Sample* vhjSample = new Sample(vBkgNames.at(6),vhjfile, vWeights.at(6),vXsec.at(6),cut,kBlue);
  //std::cout<<"weight for VH is: "<<vWeights.at(6)<<std::endl;
  //vSample.push_back(vhjSample);

  std::string wpwpfilename = samplesDir+"test/WpWp_Mu"+muID+"_El"+elID+".root";
  TFile* wpwpfile = TFile::Open(wpwpfilename.c_str());
  Sample* wpwpSample = new Sample(vBkgNames.at(7),wpwpfile, vWeights.at(7),vXsec.at(7),cut,kGreen+1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(wpwpSample);

  /*std::string wwmpifilename = samplesDir+"test/WW-mpi_Mu"+muID+"_El"+elID+".root";
  TFile* wwmpifile = TFile::Open(wwmpifilename.c_str());
  Sample* wwmpiSample = new Sample(vBkgNames.at(8),wwmpifile, vWeights.at(8),vXsec.at(8),cut,kGreen-1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(wwmpiSample);*/


  std::string wwzfilename = samplesDir+"test/WWZ_Mu"+muID+"_El"+elID+".root";
  TFile* wwzfile = TFile::Open(wwzfilename.c_str());
  Sample* wwzSample = new Sample(vBkgNames.at(9),wwzfile, vWeights.at(9),vXsec.at(9),cut,kViolet+1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(wwzSample);

  std::string wzzfilename = samplesDir+"test/WZZ_Mu"+muID+"_El"+elID+".root";
  TFile* wzzfile = TFile::Open(wzzfilename.c_str());
  Sample* wzzSample = new Sample(vBkgNames.at(10),wzzfile, vWeights.at(10),vXsec.at(10),cut,kViolet+3);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(wzzSample);

  std::string zzzfilename = samplesDir+"test/ZZZ_Mu"+muID+"_El"+elID+".root";
  TFile* zzzfile = TFile::Open(zzzfilename.c_str());
  Sample* zzzSample = new Sample(vBkgNames.at(11),zzzfile, vWeights.at(11),vXsec.at(11),cut,kViolet);
  std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(zzzSample);


  //********** Nonprompt ***************
  /*std::string npTTfilename = samplesDir+"test/NonPromptTTJets_Mu"+muID+"_El"+elID+".root";
  TFile* npttfile = TFile::Open(nptTfilename.c_str());
  Sample* npttSample = new Sample(vBkgNames.at(-1),npttfile,vWeights.at(-1),vXsec.at(01),cut,kBlue);
  vSample.push_back(npttSample)*/

  std::string npfilename = samplesDir+"test/NonPromptData_Mu"+muID+"_El"+elID+".root";
  TFile* npfile = TFile::Open(npfilename.c_str());
  Sample* npSample = new Sample(vBkgNames.at(12),npfile,vWeights.at(13),vXsec.at(13),cut,kGray);
  vSample.push_back(npSample);

  //********ChargeMisID**********
  std::string cmidfilename = samplesDir+"test/ChargeMisID_Mu"+muID+"_El"+elID+".root";
  TFile* cmidfile = TFile::Open(cmidfilename.c_str());
  Sample* cmidSample = new Sample(vBkgNames.at(13),cmidfile,vWeights.at(13),vXsec.at(13),cut,kGreen); //force charge misID to start here since only at this point do we filter events
  vSample.push_back(cmidSample);


  return vSample;

}

std::vector<Sample*> getMCBkgSampleVec(std::string cut, float lumi, std::string elID, std::string muID, std::string era){  

   //setup info for list of samples, xsec and events run  //make vector of actual number of events run MULTIPLIED BY AMCATNLO WEIGHT
  std::vector<std::string> vBkgNames;  std::vector<float> vXsec;  std::vector<float> vNEvts;

  //************** MC *************
 //vBkgNames.push_back("TTbar");  vXsec.push_back(831.76);  vNEvts.push_back(42730273 * 0.331582);
  vBkgNames.push_back("TTZ");    vXsec.push_back(0.2529);  vNEvts.push_back(10453148);
  vBkgNames.push_back("TTW");    vXsec.push_back(0.2043);  vNEvts.push_back(4718602);
  vBkgNames.push_back("TTH");    vXsec.push_back(0.215);  vNEvts.push_back( 7522972); //2017
  vBkgNames.push_back("TTTT");    vXsec.push_back(0.009103);  vNEvts.push_back(1104584);
  vBkgNames.push_back("WZ");     vXsec.push_back(4.42965); vNEvts.push_back(1262156);
  //vBkgNames.push_back("WJets");  vXsec.push_back(61526.7); vNEvts.push_back(24151270 * 0.683948);
  //vBkgNames.push_back("DYJets"); vXsec.push_back(6025.2);  vNEvts.push_back(28825132 * 0.6693);
  vBkgNames.push_back("ZZ");     vXsec.push_back(1.212);  vNEvts.push_back(813812);
  vBkgNames.push_back("VH");     vXsec.push_back(0.952);  vNEvts.push_back(6 * 1);
  vBkgNames.push_back("WpWp");   vXsec.push_back(0.03711); vNEvts.push_back(148394); //2017
  vBkgNames.push_back("WW-mpi"); vXsec.push_back(1.64);   vNEvts.push_back( 843514* 1);  // what is this?
  vBkgNames.push_back("WWZ");    vXsec.push_back(0.1651); vNEvts.push_back(215228); 
  vBkgNames.push_back("WZZ");    vXsec.push_back(0.05565); vNEvts.push_back(413104);
  vBkgNames.push_back("ZZZ");    vXsec.push_back(0.01398); vNEvts.push_back(407160);
  //vBkgNames.push_back("WWW");    vXsec.push_back(0.01398); vNEvts.push_back(240000* 0.8554);
  
  //ARC review request: dataset with Gamma conversions // added by rizki
  vBkgNames.push_back("TTGJets");    vXsec.push_back(3.697); vNEvts.push_back(4870911 * 0.325); //prelim estimate: ran 1204482 events, adjusted count 391002. Could assume adjusted = 0.325 * total, from Julie Nov29-2017
  vBkgNames.push_back("ZGTo2LG");    vXsec.push_back(123.9); vNEvts.push_back(1579452); //ZG: int 2307158, adjusted count 1579452 , from Julie Nov29-2017
  vBkgNames.push_back("TGJets");    vXsec.push_back(2.967); vNEvts.push_back(58120); //TGJets: integral 292508, adjusted count 58120 , from Julie Nov29-2017
  vBkgNames.push_back("WGToLNuG");    vXsec.push_back(405.271); vNEvts.push_back( 6103817* 1);
  vBkgNames.push_back("TTZToLLM1to10");    vXsec.push_back(0.0493); vNEvts.push_back(246792 * 1);
  
  //now make vector to hold weights;
  std::vector<float> vWeights;
  for(std::vector<float>::size_type ui=0; ui<vXsec.size(); ui++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(ui) / vNEvts.at(ui) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  //now make samples and add to vector
  std::vector<Sample*> vSample;
  //TFile* ttfile = TFile::Open(eosDirector+samplesDir+"/TTbar"+era+".root");
  //Sample* ttSample = new Sample(vBkgNames.at(0),ttfile, vWeights.at(0),vXsec.at(0),cut,kRed+2);
  //vSample.push_back(ttSample);

  std::string ttZfilename = eosDirector+samplesDir+"/TTZ_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* ttZfile = TFile::Open(ttZfilename.c_str());
  Sample* ttZSample = new Sample(vBkgNames.at(0),ttZfile, vWeights.at(0),vXsec.at(0),cut,kRed);
  std::cout<<"weight for TTZ is: "<<vWeights.at(0)<<std::endl;
  vSample.push_back(ttZSample);

  std::string ttWfilename = eosDirector+samplesDir+"/TTW_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* ttwfile = TFile::Open(ttWfilename.c_str());
  Sample* ttwSample = new Sample(vBkgNames.at(1),ttwfile, vWeights.at(1),vXsec.at(1),cut,kYellow-2);
  std::cout<<"weight for TTW is: "<<vWeights.at(1)<<std::endl;
  vSample.push_back(ttwSample);

  std::string tthfilename = eosDirector+samplesDir+"/TTH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* tthfile = TFile::Open(tthfilename.c_str());
  Sample* tthSample = new Sample(vBkgNames.at(2),tthfile, vWeights.at(2),vXsec.at(2),cut,kYellow);
  std::cout<<"weight for TTH is: "<<vWeights.at(2)<<std::endl;
  vSample.push_back(tthSample);

  std::string ttttfilename = eosDirector+samplesDir+"/TTTT_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* ttttfile = TFile::Open(ttttfilename.c_str());
  Sample* ttttSample = new Sample(vBkgNames.at(3),ttttfile, vWeights.at(3),vXsec.at(3),cut,kRed+2);
  std::cout<<"weight for TTTT is: "<<vWeights.at(3)<<std::endl;
  vSample.push_back(ttttSample);


  std::string wzfilename=eosDirector+samplesDir+"/WZ_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* wzfile = TFile::Open(wzfilename.c_str());
  Sample* wzSample = new Sample(vBkgNames.at(4),wzfile, vWeights.at(4),vXsec.at(4),cut,kBlue-3);
  std::cout<<"weight for WZ is: "<<vWeights.at(4)<<std::endl;
  vSample.push_back(wzSample);

  //TFile* wjfile = TFile::Open(eosDirector+samplesDir+"/WJets_Mu"+muID+"_El"+elID+"_"+era+".root");
  //Sample* wjSample = new Sample(vBkgNames.at(4),wjfile, vWeights.at(4),vXsec.at(4),cut,kGreen+2);
  //vSample.push_back(wjSample);

  /*std::string dyfilename =  eosDirector+samplesDir+"/DYJets_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* dyjfile = TFile::Open(dyfilename.c_str());
  Sample* dyjSample = new Sample(vBkgNames.at(3),dyjfile, vWeights.at(3),vXsec.at(3),cut,kMagenta+2);
  vSample.push_back(dyjSample);*/
  
  std::string zzfilename = eosDirector+samplesDir+"/ZZ_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* zzjfile = TFile::Open(zzfilename.c_str());
  Sample* zzjSample = new Sample(vBkgNames.at(5),zzjfile, vWeights.at(5),vXsec.at(5),cut,kOrange+1);
  std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(zzjSample);

  //std::string vhfilename = eosDirector+samplesDir+"/VH_Mu"+muID+"_El"+elID+"_"+era+".root";
  //TFile* vhjfile = TFile::Open(vhfilename.c_str());
  //Sample* vhjSample = new Sample(vBkgNames.at(6),vhjfile, vWeights.at(6),vXsec.at(6),cut,kBlue);
  //std::cout<<"weight for VH is: "<<vWeights.at(6)<<std::endl;
  //vSample.push_back(vhjSample);

  std::string wpwpfilename = eosDirector+samplesDir+"/WpWp_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* wpwpfile = TFile::Open(wpwpfilename.c_str());
  Sample* wpwpSample = new Sample(vBkgNames.at(7),wpwpfile, vWeights.at(7),vXsec.at(7),cut,kGreen+1);
  std::cout<<"weight for WpWp is: "<<vWeights.at(7)<<std::endl;
  vSample.push_back(wpwpSample);

  /*std::string wwmpifilename = eosDirector+samplesDir+"/WW-mpi_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* wwmpifile = TFile::Open(wwmpifilename.c_str());
  Sample* wwmpiSample = new Sample(vBkgNames.at(8),wwmpifile, vWeights.at(8),vXsec.at(8),cut,kGreen-1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(wwmpiSample);*/


  std::string wwzfilename = eosDirector+samplesDir+"/WWZ_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* wwzfile = TFile::Open(wwzfilename.c_str());
  Sample* wwzSample = new Sample(vBkgNames.at(9),wwzfile, vWeights.at(9),vXsec.at(9),cut,kViolet+1);
  std::cout<<"weight for WWZ is: "<<vWeights.at(9)<<std::endl;
  vSample.push_back(wwzSample);

  std::string wzzfilename = eosDirector+samplesDir+"/WZZ_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* wzzfile = TFile::Open(wzzfilename.c_str());
  Sample* wzzSample = new Sample(vBkgNames.at(10),wzzfile, vWeights.at(10),vXsec.at(10),cut,kViolet+3);
  std::cout<<"weight for WZZ is: "<<vWeights.at(10)<<std::endl;
  vSample.push_back(wzzSample);

  std::string zzzfilename = eosDirector+samplesDir+"/ZZZ_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* zzzfile = TFile::Open(zzzfilename.c_str());
  Sample* zzzSample = new Sample(vBkgNames.at(11),zzzfile, vWeights.at(11),vXsec.at(11),cut,kViolet);
  std::cout<<"weight for ZZZ is: "<<vWeights.at(11)<<std::endl;
  vSample.push_back(zzzSample);

  //ARC review request: dataset with Gamma conversions // added by rizki
//   std::string ttgjetsfilename = eosDirector+samplesDir+"/TTGJets_Mu"+muID+"_El"+elID+"_"+era+".root";
//   TFile* ttgjetsfile = TFile::Open(ttgjetsfilename.c_str());
//   Sample* ttgjetsSample = new Sample(vBkgNames.at(12),ttgjetsfile, vWeights.at(12),vXsec.at(12),cut,kViolet-1);
//   std::cout<<"weight for TTGJets is: "<<vWeights.at(12)<<std::endl;
//   vSample.push_back(ttgjetsSample);
// 
//   std::string zgto2lgfilename = eosDirector+samplesDir+"/ZGTo2LG_Mu"+muID+"_El"+elID+"_"+era+".root";
//   TFile* zgto2lgfile = TFile::Open(zgto2lgfilename.c_str());
//   Sample* zgto2lgSample = new Sample(vBkgNames.at(13),zgto2lgfile, vWeights.at(13),vXsec.at(13),cut,kViolet-2);
//   std::cout<<"weight for ZGTo2LG is: "<<vWeights.at(13)<<std::endl;
//   vSample.push_back(zgto2lgSample);
// 
//   std::string tgjetsfilename = eosDirector+samplesDir+"/TGJets_Mu"+muID+"_El"+elID+"_"+era+".root";
//   TFile* tgjetsfile = TFile::Open(tgjetsfilename.c_str());
//   Sample* tgjetsSample = new Sample(vBkgNames.at(14),tgjetsfile, vWeights.at(14),vXsec.at(14),cut,kViolet-3);
//   std::cout<<"weight for TGJets is: "<<vWeights.at(14)<<std::endl;
//   vSample.push_back(tgjetsSample);
// 
//   std::string wgtolnugfilename = eosDirector+samplesDir+"/WGToLNuG_Mu"+muID+"_El"+elID+"_"+era+".root";
//   TFile* wgtolnugfile = TFile::Open(wgtolnugfilename.c_str());
//   Sample* wgtolnugSample = new Sample(vBkgNames.at(15),wgtolnugfile, vWeights.at(15),vXsec.at(15),cut,kViolet-4);
//   std::cout<<"weight for WGToLNuG is: "<<vWeights.at(15)<<std::endl;
//   vSample.push_back(wgtolnugSample);
// 
//   std::string ttztollm1to10filename = eosDirector+samplesDir+"/TTZToLLM1to10_Mu"+muID+"_El"+elID+"_"+era+".root";
//   TFile* ttztollm1to10file = TFile::Open(ttztollm1to10filename.c_str());
//   Sample* ttztollm1to10Sample = new Sample(vBkgNames.at(16),ttztollm1to10file, vWeights.at(16),vXsec.at(16),cut,kViolet-6);
//   std::cout<<"weight for TTZToLLM1to10 is: "<<vWeights.at(16)<<std::endl;
//   vSample.push_back(ttztollm1to10Sample);

  return vSample;

}

std::vector<Sample*> getDDBkgSampleVec(std::string cut, float lumi, std::string elID, std::string muID, std::string era){  

   //setup info for list of samples, xsec and events run  //make vector of actual number of events run MULTIPLIED BY AMCATNLO WEIGHT
  std::vector<std::string> vBkgNames;  std::vector<float> vXsec;  std::vector<float> vNEvts;

  //******* Non Prompt**********
  vBkgNames.push_back("NonPrompt"); vXsec.push_back(1); vNEvts.push_back(1);
  vBkgNames.push_back("ChargeMisID"); vXsec.push_back(1); vNEvts.push_back(1);
  //now make vector to hold weights;
  std::vector<float> vWeights;
  for(std::vector<float>::size_type ui=0; ui<vXsec.size(); ui++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(ui) / vNEvts.at(ui) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  //now make samples and add to vector
  std::vector<Sample*> vSample;

  //********** Nonprompt ***************
  std::string npfilename = eosDirector+samplesDir+"/NonPromptData_Mu"+muID+"_El"+elID+"_"+era+".root";
//   std::string npfilename = RizkiNPArea+"NonPromptData_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* npfile = TFile::Open(npfilename.c_str());
  Sample* npSample = new Sample(vBkgNames.at(0),npfile,vWeights.at(0),vXsec.at(0),cut,kGray);
  vSample.push_back(npSample);

  //********ChargeMisID**********
  std::string cmidfilename = eosDirector+samplesDir+"/ChargeMisID_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* cmidfile = TFile::Open(cmidfilename.c_str());
  Sample* cmidSample = new Sample(vBkgNames.at(1),cmidfile,vWeights.at(1),vXsec.at(1),cut,kGreen); //force charge misID to start here since only at this point do we filter events
  vSample.push_back(cmidSample);


  return vSample;

}


std::vector<std::string> getCutString(){

  std::vector<std::string> vString;

  //quarkonia-veto
//   std::string null = "Lep1Pt>0";
//   std::string null = "(Lep1Pt>0 && nNonSSLeps==0)"; //added by rizki for orthogonality with trilepton
  std::string null = "nNonSSLeps==0"; //added by rizki for orthogonality with trilepton
  vString.push_back(null);
  std::string qv = "("+null+" && (DilepMass>20) )";
  vString.push_back(qv);
  //z mass veto for ee channel only
  std::string zv = "("+qv+" && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )";
  vString.push_back(zv);
  //Leading Lep pT
  std::string lep1pt = "("+zv+"&& Lep1Pt > 40)" ;
  vString.push_back(lep1pt);
  //SubLeadingLep pT
  //std::string lep2pt = "("+lep1pt+"&& Lep2Pt > 30)" ;
  //vString.push_back(lep2pt);
  //Leading nJetscut
//   std::string nConstCut = "("+lep1pt+"&& nConst >= 5)"; //commented by rizki
//   std::string nConstCut = "("+lep1pt+"&& nConst >= 2)"; //added by rizki
  std::string nConstCut = "("+lep1pt+"&& nConst >= 4)"; //added by rizki
//   std::string nConstCut = "("+lep1pt+"&& nConst >= 3)"; //added by rizki
  vString.push_back(nConstCut);
  //SubLeading Jet Pt
  //std::string jet2pt = "("+jet1pt+"&& cleanAK4Jet2Pt > 150)";
  //vString.push_back(jet2pt);
  //HT cut
  std::string htcut = "("+nConstCut+"&& cleanAK4HT > 1200)"; //commented by rizki
//   std::string htcut = "("+nConstCut+"&& cleanAK4HT > 1100)"; //added by rizki
  vString.push_back(htcut);

  //std::string centrallepcut =  "("+htcut+"&& TMath::Abs(Lep1Eta) < 0.9)";
  //vString.push_back(centrallepcut);
  return vString;
}

std::vector<std::string> getBoostedCutString(){

  std::vector<std::string> vString;

  //quarkonia-veto
  std::string null = "Lep1Pt>0";
  vString.push_back(null);
  std::string qv = "("+null+" && (DilepMass>20) )";
  vString.push_back(qv);
  //z mass veto for ee channel only
  std::string zv = "("+qv+" && ( (Channel!=0) ||(DilepMass<76.1 || DilepMass >106.1) ) )";
  vString.push_back(zv);
  //Leading Lep pT
  std::string lep1pt = "("+zv+"&& Lep1Pt > 40)" ;
  vString.push_back(lep1pt);
  //SubLeadingLep pT
  //std::string lep2pt = "("+lep1pt+"&& Lep2Pt > 30)" ;
  //vString.push_back(lep2pt);
  //Leading nJetscut
  std::string nConstCut = "("+lep1pt+"&& nNewConst >= 5)";
  vString.push_back(nConstCut);
  //SubLeading Jet Pt
  //std::string jet2pt = "("+jet1pt+"&& cleanAK4Jet2Pt > 150)";
  //vString.push_back(jet2pt);
  //HT cut
  std::string htcut = "("+nConstCut+"&& newCleanAK4HT > 900)";
  vString.push_back(htcut);
  return vString;
}


std::pair<float,float> getNEvtsAndError(Sample* s, std::string cut, int nMu, bool scale_){
  bool scale = scale_;
  TTree* t = s->tree;
  TH1F* hdummy = new TH1F("hdummy","hdummy",1,0,10000);
  hdummy->Sumw2();
  //make cut string based on channel, should always be outside of parantheses for other cuts so a simply && should work also apply chargeMisIDWeight
  std::stringstream channel;
  if(nMu>=0)  channel<<"&& (Channel =="<<nMu<<")";
  else  channel<<"";

  //std::string cutstring= " PUWeight* MCWeight*ChargeMisIDWeight * NPWeight* ( "+cut+channel.str()+")";
  std::string cutstring= " PUWeight * IDSF * IsoSF * trigSF * GsfSF * MCWeight * ChargeMisIDWeight * NPWeight* ( "+cut+channel.str()+")";


  //draw the last variable to cut on just to be safe though it shouldn't matter
  t->Project("hdummy","AK4HT",cutstring.c_str());
  
  //std::cout<<"Sample: "<<s->name<<" and cut: "<<cutstring<<" unweighted events: "<<nEvts<<" weight: "<<s->weight<<std::endl;
  //now weight properly - for Data don't apply
  if( ( (s->name).find("NonPrompt")!=std::string::npos) && ((s->name).find("TTJets")==std::string::npos) ) { scale=false; }
  else if( ( (s->name).find("ChargeMisID")!=std::string::npos) && ((s->name).find("MC")==std::string::npos) ) { scale=false; }
  if(scale){
    hdummy->Scale(s->weight);
    //std::cout<<"Weight for sample: "<<s->name<<" is: "<<s->weight<<std::endl;
  }
  
  float nEvts = hdummy->Integral(1,hdummy->GetNbinsX()+1);
  double_t err;
  hdummy->IntegralAndError(1,hdummy->GetNbinsX()+1,err);
  delete hdummy;
  std::pair<float,float> nEvtsAndError(nEvts,(float)err);
  return nEvtsAndError;
};



std::string getPrettyCutString(std::string cut){

  //find the positions of && in the cut string
  std::vector<size_t> positions; // holds all the positions that sub occurs within str

  size_t pos = cut.find("&&", 0);
  while(pos != std::string::npos)
    {
      positions.push_back(pos);
      pos = cut.find("&&",pos+1);
    }

  //now take the last of them since what we want is the cut applied to the right of the last &&
  if(positions.size()==0) return "SSDL";
  else if(positions.size()==2) return "EE-ZVeto";
  size_t last = positions.at(positions.size()-1);
  size_t length = cut.size() - last; //should give number of characters remaining in string
  length = length -3; //decrement by one to ignor final ')'
  
  std::string prettyString(cut, last+2, length);
  
  return prettyString;

};


CutClass* makeCutClass(Sample* s, std::vector<std::string> vCuts,int nMu)
{

  std::vector<float> vEvts,vErr;
  std::vector<std::string> vCutsPretty;

  for(size_t j=0; j < vCuts.size(); j++){
    
    //get number of events and save to vector - IMPORTANT TO DO THIS WITH THE FULL CUT STRING AND NOT A PRETTY VERSION
    bool scale = true; //helper function will set to false if need be
    std::pair<float,float> evtsAndErr = getNEvtsAndError(s, vCuts.at(j), nMu, scale);
    vEvts.push_back(evtsAndErr.first);
    vErr.push_back(evtsAndErr.second);
    //now trim the cuts string to write prettily
    
    std::string cutPretty = getPrettyCutString(vCuts.at(j));
    vCutsPretty.push_back(cutPretty);
  }

  CutClass* c = new CutClass(s->name,vCutsPretty,vEvts,vErr,s->xsec);
  return c;

};


std::vector<CutClass*> getCutClassVector(std::vector<Sample*> vS, std::vector<std::string> vCuts, int nMu){

  std::vector<CutClass*> vCC;

  for(size_t i =0; i < vS.size(); i++){
    CutClass* c = makeCutClass(vS.at(i),vCuts,nMu);
    vCC.push_back(c);
  }

  return vCC;

};

std::vector<CutClass*> appendCutClassVectors(std::vector<CutClass*> vCC1, std::vector<CutClass*> vCC2){
  std::vector<CutClass*> vCC;
  for(unsigned int i =0; i< vCC1.size();i++){
    vCC.push_back(vCC1.at(i));
    //std::cout<<"appending first vector, number "<<i<<" of "<<vCC1.size()<<std::endl;
  }
  for(unsigned int j=0;j<vCC2.size();j++){
    vCC.push_back(vCC2.at(j));
    //std::cout<<"appending second vector, number "<<j<<" of "<<vCC2.size()<<std::endl;
  }
  return vCC;
}

std::vector<CutClass*> addCutClassVectors(std::vector<CutClass*> vCC1, std::vector<CutClass*> vCC2){
  //NB: This is only good for MC!
  std::vector<CutClass*> vCC;
  //first check that the sizes match
  if(vCC1.size() != vCC2.size()){    
    throw std::invalid_argument( "Error! Trying to add CutClass vectors of different size!");
  }
  
  for(unsigned int i=0; i< vCC1.size() ; i++){
    //check sample names are the same
    if(vCC1.at(i)->samplename!=vCC2.at(i)->samplename){
      throw std::invalid_argument("Error! Sample names are not consistent");
    }
    std::vector<float> vEvtsNew, vErrNew;
    for(unsigned int j=0; j< vCC1.at(i)->nEvents.size();j++){
      //std::cout<<"adding events for sample number: "<<i<<" on cut number "<<j<<" of "<<vCC1.at(i)->nEvents.size()<<" cuts for "<<vCC1.size()<<" samples"<<std::endl;
      vEvtsNew.push_back( vCC1.at(i)->nEvents.at(j) + vCC2.at(i)->nEvents.at(j)); //add the number of events for each
      float errNew = pow( vCC1.at(i)->vErr.at(j)*vCC1.at(i)->vErr.at(j) + vCC2.at(i)->vErr.at(j)*vCC2.at(i)->vErr.at(j), 0.5);
      vErrNew.push_back(errNew);
    }
    CutClass* c = new CutClass(vCC1.at(i)->samplename,vCC1.at(i)->cutname,vEvtsNew,vErrNew,vCC1.at(i)->xsec);
    vCC.push_back(c);
  }    
  return vCC;
}

/*std::vector<float> getEtaWeights(TreeReader* tr, TTree* t, TFile* outfile){

  std::vector<float> etaWeights;

  //float xbins[9] = {-2.5,-2.1,-1.5,-0.9,0,0.9,1.5,2.1,2.5};

  TH1F* h_ss = new TH1F("h_ss","",15,-3,3);
  TH1F* h_all = new TH1F("h_all","",15,-3,3);
  TH1F* h_PairMass = new TH1F("h_PairMass","",50,50,150);
  int nEntries=t->GetEntries();



  for(int ient=0; ient<nEntries; ient++){

    float mindiff=9999;
    float pairmass=-9999;
    TElectron* El1;
    TElectron* El2;

    tr->GetEntry(ient);
    //run over good electrons and find pair closest to Z Mass
    for(size_t i=0; i< tr->goodElectrons.size(); i++){
      TElectron* el1 = tr->goodElectrons.at(i);
      for(size_t j=i+1; j<tr->goodElectrons.size(); j++){
	TElectron* el2 = tr->goodElectrons.at(j);
	float mass = (el1->lv + el2->lv).M();
	
	if( fabs( 91.1 - mass) < mindiff){
	  mindiff=fabs(91.1 - mass);
	  El1=el1;
	  El2=el2;
	  pairmass=mass;	  
	}

      }
      
    }

    bool inPeak=false;
    if(mindiff<20) inPeak=true; //also implies that a pair was found since requires min diff to be reset;
    //std::cout<<"size of goodEls: "<<tr->goodElectrons.size()<<"El 1 eta: "<<El1->eta<<" El2 eta: "<<El2->eta<<" mass: "<<pairmass<<" mindiff: "<<mindiff<<std::endl;
    
    h_PairMass->Fill(pairmass);
    if(!inPeak) continue;

    if(El1->charge == El2->charge){
      h_ss->Fill(El1->eta);
      h_ss->Fill(El2->eta);
    }

    h_all->Fill(El1->eta);
    h_all->Fill(El2->eta);


  }//end event loop

  outfile->WriteTObject(h_PairMass);
  outfile->WriteTObject(h_ss);
  outfile->WriteTObject(h_all);
  //scale by 1/2
  h_all->Sumw2();
  h_ss->Sumw2();
  h_ss->Scale(0.5);


  TGraphAsymmErrors* chargeMisIDgraph = new TGraphAsymmErrors(h_ss,h_all);

  outfile->WriteTObject(chargeMisIDgraph);

  for(size_t i=0; i< chargeMisIDgraph->GetN(); i++){
    etaWeights.push_back(chargeMisIDgraph->GetY()[i]);
    std::cout<<"Weight is: "<<chargeMisIDgraph->GetY()[i]<<std::endl;
  }

  std::cout<<"size of etaWeights: "<<etaWeights.size()<<std::endl;

  return etaWeights;

  }*/

std::vector<float> getEtaWeights_lpt(TFile* weightfile){
  
  //TGraphAsymmErrors* g = (TGraphAsymmErrors*) weightfile->Get("divide_etaNumHist_by_etaDenHist");
  TH1F* h = (TH1F*) weightfile->Get("h_num_lpt");
  //TH1F* den = (TH1F*) weightfile->Get("etaDenHist");
  //h->Divide(den);
  std::vector<float> etaWeights;

  for(int i=1; i<= h->GetNbinsX(); i++){
    etaWeights.push_back(h->GetBinContent(i));
    std::cout<<"lpt etaweight for bin: "<<i<<" is: "<<h->GetBinContent(i)<<std::endl;
  }
  
  return etaWeights;
  
};

std::vector<float> getEtaWeights_hpt(TFile* weightfile){
  
  //TGraphAsymmErrors* g = (TGraphAsymmErrors*) weightfile->Get("divide_etaNumHist_by_etaDenHist");
  TH1F* h = (TH1F*) weightfile->Get("hpt_final");
  //TH1F* den = (TH1F*) weightfile->Get("etaDenHist");
  //h->Divide(den);
  std::vector<float> etaWeights;

  for(int i=1; i<= h->GetNbinsX(); i++){
    etaWeights.push_back(h->GetBinContent(i));
    std::cout<<"hpt etaweight for bin: "<<i<<" is: "<<h->GetBinContent(i)<<std::endl;
  }
  
  return etaWeights;
  
};

std::vector<float> getEtaWeights_hhpt(TFile* weightfile){
  
  //TGraphAsymmErrors* g = (TGraphAsymmErrors*) weightfile->Get("divide_etaNumHist_by_etaDenHist");
  TH1F* h = (TH1F*) weightfile->Get("hhpt_final");
  //TH1F* den = (TH1F*) weightfile->Get("etaDenHist");
  //h->Divide(den);
  std::vector<float> etaWeights;

  for(int i=1; i<= h->GetNbinsX(); i++){
    etaWeights.push_back(h->GetBinContent(i));
    std::cout<<"hhpt etaweight for bin: "<<i<<" is: "<<h->GetBinContent(i)<<std::endl;
  }
  
  return etaWeights;
  
};



float getEtaWeight_hhpt(float abseta, std::vector<float> etaWeights){
  float weight=0.0;

  if(abseta>1.55) weight = etaWeights.at(3);
  else if(abseta>1.442) weight = 0.0;
  else if(abseta>0.8) weight = etaWeights.at(1);
  else weight = etaWeights.at(0);

  return weight;
}

float getEtaWeight_hpt(float abseta, std::vector<float> etaWeights){
  float weight=0.0;

  if(abseta>2.0) weight = etaWeights.at(5);
  else if(abseta>1.55) weight = etaWeights.at(4);
  else if(abseta>1.442) weight = 0.0;
  else if(abseta>0.8) weight = etaWeights.at(2);
  else if(abseta>0.4) weight = etaWeights.at(1);
  else weight = etaWeights.at(0);

  return weight;
}

float getEtaWeight_lpt(float abseta, std::vector<float> etaWeights){
  float weight=0.0;

  if(abseta>2.0) weight = etaWeights.at(5);
  else if(abseta>1.55) weight = etaWeights.at(4);
  else if(abseta>1.442) weight = 0.0;
  else if(abseta>0.8) weight = etaWeights.at(2);
  else if(abseta>0.4) weight = etaWeights.at(1);
  else weight = etaWeights.at(0);

  return weight;
}

float getEtaWeight(std::vector<float> etaWeights, std::vector<TLepton*> leptons){

  float weight1=1;
  float weight2=1;
  TLepton* Lep1=leptons.at(0);
  TLepton* Lep2=leptons.at(1);

  if(Lep1->isEl){
    if(Lep1->eta<-2.6) weight1 = 0;//no electrons greater than 2.6
    else if(Lep1->eta<-2.2) weight1 = weight1*etaWeights.at(0);
    else if(Lep1->eta<-1.8) weight1 = weight1*etaWeights.at(1);
    else if(Lep1->eta<-1.4) weight1 = weight1*etaWeights.at(2);
    else if(Lep1->eta< -1.0) weight1 = weight1*etaWeights.at(3);
    else if(Lep1->eta< -0.6) weight1 = weight1*etaWeights.at(4);
    else if(Lep1->eta< -0.2) weight1 = weight1*etaWeights.at(5);
    else if(Lep1->eta< 0.2) weight1 = weight1*etaWeights.at(6);
    else if(Lep1->eta< 0.6) weight1 = weight1*etaWeights.at(7);
    else if(Lep1->eta< 1.0) weight1 = weight1*etaWeights.at(8);
    else if(Lep1->eta< 1.4) weight1 = weight1*etaWeights.at(9);
    else if(Lep1->eta< 1.8) weight1 = weight1*etaWeights.at(10);
    else if(Lep1->eta< 2.2) weight1 = weight1*etaWeights.at(11);
    else if(Lep1->eta< 2.6) weight1 = weight1*etaWeights.at(12);
    else if(Lep1->eta< 3.0) weight1 = 0; //no electrons w/ eta greater than 2.6

  }

  if(Lep2->isEl){
    if(Lep2->eta<-2.6) weight2 = 0;//no electrons outside eta 2.6
    else if(Lep2->eta<-2.2) weight2 = weight2*etaWeights.at(0);
    else if(Lep2->eta<-1.8) weight2 = weight2*etaWeights.at(1);
    else if(Lep2->eta<-1.4) weight2 = weight2*etaWeights.at(2);
    else if(Lep2->eta< -1.0) weight2 = weight2*etaWeights.at(3);
    else if(Lep2->eta< -0.6) weight2 = weight2*etaWeights.at(4);
    else if(Lep2->eta< -0.2) weight2 = weight2*etaWeights.at(5);
    else if(Lep2->eta< 0.2) weight2 = weight2*etaWeights.at(6);
    else if(Lep2->eta< 0.6) weight2 = weight2*etaWeights.at(7);
    else if(Lep2->eta< 1.0) weight2 = weight2*etaWeights.at(8);
    else if(Lep2->eta< 1.4) weight2 = weight2*etaWeights.at(9);
    else if(Lep2->eta< 1.8) weight2 = weight2*etaWeights.at(10);
    else if(Lep2->eta< 2.2) weight2 = weight2*etaWeights.at(11);
    else if(Lep2->eta< 2.6) weight2 = weight2*etaWeights.at(12);
    else if(Lep2->eta< 3.0) weight2 = 0; //no electrons outside eta 2.6
  }


  float weight=1;
  if(Lep1->isEl && Lep2->isEl) weight = weight1 + weight2 - weight1*weight2;
  else if( (Lep1->isEl && !Lep2->isEl) || (!Lep1->isEl && Lep2->isEl) ){
    if(Lep1->isEl) weight = weight1;
    else weight = weight2;
  }


  return weight;

};

float getPairMass(TLepton* lep1, TLepton* lep2){

  float mass = (lep1->lv + lep2->lv).M();
  return mass;

}

float getPairMass(TLepton* lep1, TMuon* mu){
  float mass = (lep1->lv + mu->lv).M();
  return mass;
}

float getPairMass(TLepton* lep1, TElectron* el){
  float mass = (lep1->lv + el->lv).M();
  return mass;
}

float getPairMass(TMuon* mu1, TMuon* mu2){
  float mass = (mu1->lv + mu2->lv).M();
  return mass;
}

float getPairMass(TElectron* el1, TElectron* el2){
  float mass = (el1->lv + el2->lv).M();
  return mass;
}


float getPrate(TFile* f){

  TH1F* h1 = (TH1F*) f->Get("ptNumHist");
  TH1F* h2 = (TH1F*) f->Get("ptDenHist");
  
  float rate = (float) h1->GetEntries();
  rate = rate / h2->GetEntries();
  return rate;

}


//functions to get weights for tight/loose method
float getMuFakeRate(std::string ID){

  if(ID=="CBTight") return 0.371;
  else return 0.371;
}

float getMuPromptRate(std::string ID){

  if(ID=="CBTight") return 0.94;
  else return 0.94;
		      
}

float getElFakeRate(std::string ID){

  if(ID=="CBTight") return 0.43;
  else if(ID=="MVATightRC") return 0.298;
  else if(ID=="MVATightCC") return 0.298;
  else if(ID=="CBTightRC") return 0.43;
  else return 0.298;

}

float getElPromptRate(std::string ID){

  if(ID=="CBTight") return 0.7259;
  else if(ID=="MVATightRC") return 0.873;
  else if(ID=="MVATightCC") return 0.873;
  else if(ID=="CBTightRC") return 0.7259;
  else return 0.873;

}  

//method weights
//same flavor
float WeightSF_T0(float pr, float fr){
  float weight = (-1.0)*( pow( fr*pr,2)) / (pow( pr - fr, 2));
  return weight;
}

float WeightSF_T0(std::string elID, std::string muID, int nMu){
  float prate = nMu==2 ? getMuPromptRate(muID) : getElPromptRate(elID);
  float frate = nMu==2 ? getMuFakeRate(muID) : getElFakeRate(elID);
  float weight = WeightSF_T0(prate,frate);
  return weight;
}

float WeightSF_T1(float pr, float fr){
  float weight= (pr*pr * (fr - fr*fr) ) / (pow( (pr -fr),2) );
  return weight;
}

float WeightSF_T1(std::string elID, std::string muID, int nMu){
  float prate = nMu==2 ? getMuPromptRate(muID) : getElPromptRate(elID);
  float frate = nMu==2 ? getMuFakeRate(muID) : getElFakeRate(elID);
  float weight = WeightSF_T1(prate,frate);
  return weight;
}

float WeightSF_T2(float pr, float fr){
  float weight= ( (fr) / (pow( (pr -fr),2)) ) * ( fr*(pow(1.0-pr,2)) - 2.0*pr*(1.0-pr)*(1.0-fr) ) ;
  return weight;
}

float WeightSF_T2(std::string elID, std::string muID, int nMu){
  float prate = nMu==2 ? getMuPromptRate(muID) : getElPromptRate(elID);
  float frate = nMu==2 ? getMuFakeRate(muID) : getElFakeRate(elID);
  float weight = WeightSF_T2(prate,frate);
  return weight;
}


//opposite flavor
float WeightOF_T00(float elpr, float elfr, float mupr, float mufr){
  float weight = (-1.0 * elfr * elpr * mufr * mupr);
  weight = weight * ( 1.0 / ( (elpr - elfr)*(mupr-mufr)) );
  return weight;
}

float WeightOF_T00(std::string elID, std::string muID){

  float elpr = getElPromptRate(elID);
  float elfr = getElFakeRate(elID);
  float mupr = getMuPromptRate(muID);
  float mufr = getMuFakeRate(muID);

  float weight = WeightOF_T00(elpr,elfr,mupr,mufr);
  return weight;

}

float WeightOF_T10(float elpr, float elfr, float mupr, float mufr){
  float weight = elpr * ( 1.0 - elfr) * mupr * mufr;
  weight = weight * ( 1.0 / ( (elpr - elfr)*(mupr-mufr)) );
  return weight;

}

float WeightOF_T10(std::string elID, std::string muID){

  float elpr = getElPromptRate(elID);
  float elfr = getElFakeRate(elID);
  float mupr = getMuPromptRate(muID);
  float mufr = getMuFakeRate(muID);

  float weight = WeightOF_T10(elpr,elfr,mupr,mufr);
  return weight;

}

float WeightOF_T01(float elpr, float elfr, float mupr, float mufr){
  float weight = elpr * elfr * mupr * (1.0 - mufr);
  weight = weight * ( 1.0 / ( (elpr - elfr)*(mupr-mufr)) );
  return weight;
}

float WeightOF_T01(std::string elID, std::string muID){

  float elpr = getElPromptRate(elID);
  float elfr = getElFakeRate(elID);
  float mupr = getMuPromptRate(muID);
  float mufr = getMuFakeRate(muID);

  float weight = WeightOF_T01(elpr,elfr,mupr,mufr);
  return weight;

}


float WeightOF_T11(float elpr, float elfr, float mupr, float mufr){
  float weight = ( elfr*(1.0-elpr)*mufr*(1.0-mupr) ) - ( elfr*(1.0-elpr)*mupr*(1.0-mufr) )  - ( elpr*(1.0-elfr)*mufr*(1.0-mupr) ) ;
  weight = weight * ( 1.0 / ( (elpr - elfr)*(mupr-mufr)) );
  return weight;
}

float WeightOF_T11(std::string elID, std::string muID){

  float elpr = getElPromptRate(elID);
  float elfr = getElFakeRate(elID);
  float mupr = getMuPromptRate(muID);
  float mufr = getMuFakeRate(muID);

  float weight = WeightOF_T11(elpr,elfr,mupr,mufr);
  return weight;

}

float getGsfSF(TLepton* lep){

  float sf=0.0;
  float eta = lep->eta;
  if(eta<-2.3) sf       =1.00852;
  else if(eta<-2.2)   sf=1.01047;
  else if(eta<-2.0)   sf=1.00519;
  else if(eta<-1.8)   sf=0.997932;
  else if(eta<-1.63)  sf=0.991701;
  else if(eta<-1.556) sf=0.986486;
  else if(eta<-1.2)   sf=0.986667;
  else if(eta<-1.0)   sf=0.977505;
  else if(eta<-0.6)   sf=0.969388;
  else if(eta<-0.4)   sf=0.966361;
  else if(eta<-0.2)   sf=0.963303;
  else if(eta<0.0)    sf=0.96;
  else if(eta<0.2)    sf=0.966189;
  else if(eta<0.4)    sf=0.979633;
  else if(eta<0.6)    sf=0.976578;
  else if(eta<1.0)    sf=0.980652;
  else if(eta<1.2)    sf=0.986735;
  else if(eta<1.445)  sf=0.98668;
  else if(eta<1.63)   sf=0.989669;
  else if(eta<1.8)    sf=0.995872;
  else if(eta<2.0)    sf=0.989733;
  else if(eta<2.2)    sf=0.994861;
  else if(eta<2.3)    sf=0.992769;
  else                sf=0.966632;

  return sf;

}

float getMu17Eff(TLepton* mu){
  float pt = mu->pt;
  float abseta = fabs(mu->eta);
  float eff = 0.0;
  if(abseta < 0.4){
    if ( pt >=500) eff= 0.0;
    else if(pt>200) eff = 0.847649;
    else if(pt>100) eff = 0.902537;
    else if(pt>60) eff = 0.90607;
    else if(pt>40) eff = 0.916117;
    else if(pt>=35) eff = 0.916757;
  }
  else if(abseta < 0.9){
    if ( pt >=500) eff= 0.0;
    else if(pt>200) eff = 0.915741;
    else if(pt>100) eff = 0.930011;
    else if(pt>60) eff = 0.946423;
    else if(pt>40) eff = 0.948176;
    else if(pt>=35) eff = 0.951504;
  }
  else if(abseta < 1.2){
    if ( pt >=500) eff= 0.0;
    else if(pt>200) eff = 0.814732;
    else if(pt>100) eff = 0.890936;
    else if(pt>60) eff = 0.886419;
    else if(pt>40) eff = 0.883023;
    else if(pt>=35) eff = 0.889053;
  }
  else if(abseta < 2.1){
    if ( pt >=500) eff= 0.0;
    else if(pt>200) eff = 0.710069;
    else if(pt>100) eff = 0.86932;
    else if(pt>60) eff = 0.920066;
    else if(pt>40) eff = 0.929194;
    else if(pt>=35) eff = 0.934919;
  }
  else if(abseta <= 2.4){
    if ( pt >=500) eff= 0.0;
    else if(pt>200) eff = 0.0;
    else if(pt>100) eff = 0.922062;
    else if(pt>60) eff = 0.895586;
    else if(pt>40) eff = 0.874371;
    else if(pt>=35) eff = 0.862037;
  }

  return eff;

}

float getMu17EffNearbyPhi(TLepton* mu){
  float pt = mu->pt;
  float abseta = fabs(mu->eta);
  float eff = 0.0;
  if(abseta < 0.4){
    if ( pt >=500) eff= 0.0;
    else if(pt>200) eff = 0.942681;
    else if(pt>100) eff = 0.897462;
    else if(pt>60) eff = 0.942251;
    else if(pt>40) eff = 0.9456;
    else if(pt>=35) eff = 0.941429;
  }
  else if(abseta < 0.9){
    if ( pt >=500) eff= 0.0;
    else if(pt>200) eff = 0.86657;
    else if(pt>100) eff = 0.95912;
    else if(pt>60) eff = 0.914582;
    else if(pt>40) eff = 0.972233;
    else if(pt>=35) eff = 0.945942;
  }
  else if(abseta < 1.2){
    if ( pt >=500) eff= 0.0;
    else if(pt>200) eff = 1.000;
    else if(pt>100) eff = 0.872508;
    else if(pt>60) eff = 0.894153;
    else if(pt>40) eff = 0.884886;
    else if(pt>=35) eff = 0.753005;
  }
  else if(abseta < 2.1){
    if ( pt >=500) eff= 0.0;
    else if(pt>200) eff = 0.649847;
    else if(pt>100) eff = 0.783815;
    else if(pt>60) eff = 0.914594;
    else if(pt>40) eff = 0.886344;
    else if(pt>=35) eff = 0.918257;
  }
  else if(abseta <= 2.4){
    if ( pt >=500) eff= 0.0;
    else if(pt>200) eff = 0.0;
    else if(pt>100) eff = 0.798197;
    else if(pt>60) eff =  0.841652;
    else if(pt>40) eff = 0.729629;
    else if(pt>=35) eff = 0.782926;
  }

  return eff;

}

float getAvgMu17(TLepton* mu){

  float eta = fabs(mu->eta);
  float eff = 0.0;
  if(eta>2.1) eff = 0.902;
  else if(eta > 1.2) eff = 0.944;
  else if(eta > 0.9) eff = 0.871;
  else if(eta > 0.4) eff = 0.935;
  else eff = 0.897;

  return eff;
}

float getTrigSF(std::vector<TLepton*> vLep){

  float sf;
  float eta1 = fabs(vLep.at(0)->eta);
  float eta2 = fabs(vLep.at(1)->eta);

  if(vLep.at(0)->isMu && vLep.at(1)->isMu){ //dimuon channel    

    //get conditional efficiency
    float cond_eff = 0.0;
    float mu17_lep1 = 0.0;
    float mu17_lep2 = 0.0;
    if(fabs(vLep.at(0)->phi - vLep.at(1)->phi) > 1 ){
      mu17_lep1 = getMu17Eff(vLep.at(0));
      mu17_lep2 = getMu17Eff(vLep.at(1));
      cond_eff = 1.0 - (1.0 - getMu17Eff(vLep.at(0)))*(1.0 - getMu17Eff(vLep.at(1)));
    } 
    else {
      mu17_lep2 = getMu17Eff(vLep.at(1));
      mu17_lep1 = getMu17Eff(vLep.at(1))*getMu17EffNearbyPhi(vLep.at(0)) +  (1.0 - getMu17Eff(vLep.at(1))) * (getMu17Eff(vLep.at(0)));
      cond_eff = 1.0 - (1.0 - ( getMu17Eff(vLep.at(1)) * getMu17EffNearbyPhi(vLep.at(0)) + (1 - getMu17Eff(vLep.at(1)) )* getMu17Eff(vLep.at(0)) ) ) * (1.0 - getMu17Eff(vLep.at(1)) ) ;
    }
    //std::cout<<"eff1: "<<getMu17Eff(vLep.at(0))<<" eff2: "<<getMu17Eff(vLep.at(1))<<" eff3: "<<getMu17EffNearbyPhi(vLep.at(0))<<std::endl;
    //std::cout<<"cond_Eff: "<<cond_eff<<" and new condeff: "<< (1.0 - (1.0-mu17_lep1)*(1.0-mu17_lep2))<<std::endl;
    float soup_eff = 0.0;
    
    if(eta1 > 2.1){
      if(eta2>2.1) soup_eff=0.8745;
      else if(eta2>1.2) soup_eff=0.8961;
      else if(eta2>0.9) soup_eff=0.8891;
      else if(eta2>0.4) soup_eff=0.9711;
      else soup_eff=1.0;
    }
    else if(eta1 > 1.2){
      if(eta2>2.1) soup_eff=0.8955;
      else if(eta2>1.2) soup_eff=0.9376;
      else if(eta2>0.9) soup_eff=0.9330;
      else if(eta2>0.4) soup_eff=0.9565;
      else soup_eff=0.9446;
    }
    else if(eta1 > 0.9){
      if(eta2>2.1) soup_eff=0.9245;
      else if(eta2>1.2) soup_eff=0.9577;
      else if(eta2>0.9) soup_eff=0.9588;
      else if(eta2>0.4) soup_eff=0.9713;
      else soup_eff=0.9614;
    }
    else if(eta1 > 0.4){
      if(eta2>2.1) soup_eff=0.9411;
      else if(eta2>1.2) soup_eff=0.9593;
      else if(eta2>0.9) soup_eff=0.9558;
      else if(eta2>0.4) soup_eff=0.9665;
      else soup_eff=0.9483;
    }
    else{
      if(eta2>2.1) soup_eff=1.0;
      else if(eta2>1.2) soup_eff=0.9649;
      else if(eta2>0.9) soup_eff=0.9499;
      else if(eta2>0.4) soup_eff=0.9658;
      else soup_eff=0.9503;
    }
    sf = cond_eff*soup_eff;
    //std::cout<<"soup eff for leading lepton with eta: "<<eta1<<" and pt: "<<vLep.at(0)->pt<<"and  for subleading  with eta: "<<eta2<<" and pt: "<<vLep.at(1)->pt<<" is: "<<soup_eff<<" conditional eff is: "<<cond_eff<<"and total sf is: "<<sf<<std::endl;
  }

  else if(vLep.at(0)->isEl && vLep.at(1)->isEl){//dielectron channel
    float w1 = 0.0;
    float w2 = 0.0;
    //do weight for first electron
    if(eta1<0.8) w1 = 97.97/99.18; //divide by plateau efficiencies
    else if(eta1<1.5) w1  = 98.60/99.42; //divide by plateau efficiencies
    else{
      if(vLep.at(0)->pt<40) w1= 0.9955*( ROOT::Math::normal_cdf(vLep.at(0)->pt-34.157,1.62)); //take from fitted function, but MC is in plateau so divide by that
      else w1 = 0.996;
    }
    //weight for second electron
    if(eta2<0.8) w2 = 0.980;
    else if(eta2<1.5) w2  = 0.986;
    else{
      if(vLep.at(1)->pt<40) w2= 0.9955*( ROOT::Math::normal_cdf(vLep.at(1)->pt-34.157,1.62)); //take from fitted function
      else w2 = 0.996;
    }
    sf = w1*w2;
    //std::cout<<"weight for leading lepton with eta: "<<eta1<<" and pt: "<<vLep.at(0)->pt<<" is: "<<w1<<" weight for subleading  with eta: "<<eta2<<" and pt: "<<vLep.at(1)->pt<<" is: "<<w2<<" total sf = "<<sf<<std::endl;
  }
  else{ //cross channel

    float elEff = 0.0;
    float muEff = 0.0;
    //get efficiency - first check if leading lepton is electron
    if(vLep.at(0)->isEl){
      //first electron efficiency
      if(eta1<0.8) elEff = 0.980;
      else if(eta1<1.5) elEff  = 0.986;
      else{
	if(vLep.at(0)->pt<40) elEff= 0.9955*( ROOT::Math::normal_cdf(vLep.at(0)->pt-34.157,1.62)); //take from fitted function
	else elEff = 0.996;
      }
      //now muon efficiency
      if(eta2>2.1){
	if(vLep.at(1)->pt>500) muEff = 0.0;
	else if(vLep.at(1)->pt>300) muEff = 0.7778;
	else if(vLep.at(1)->pt>200) muEff = 0.7964;
	else if(vLep.at(1)->pt>150) muEff = 0.8071;
	else if(vLep.at(1)->pt>100) muEff = 0.7895;
	else if(vLep.at(1)->pt>60) muEff = 0.8113;
	else if(vLep.at(1)->pt>50) muEff = 0.7684;
	else if(vLep.at(1)->pt>40) muEff = 0.7692;
	else if(vLep.at(1)->pt>35) muEff = 0.7607;      
      }
      else if(eta2>1.2){
	if(vLep.at(1)->pt>500) muEff = 0.0;
	else if(vLep.at(1)->pt>300) muEff = 0.8848;
	else if(vLep.at(1)->pt>200) muEff = 0.8279;
	else if(vLep.at(1)->pt>150) muEff = 0.8300;
	else if(vLep.at(1)->pt>100) muEff = 0.8356;
	else if(vLep.at(1)->pt>60) muEff = 0.8573;
	else if(vLep.at(1)->pt>50) muEff = 0.8674;
	else if(vLep.at(1)->pt>40) muEff = 0.8735;
	else if(vLep.at(1)->pt>35) muEff = 0.8638;      
      }
      else if(eta2>0.9){
	if(vLep.at(1)->pt>500) muEff = 0.0;
	else if(vLep.at(1)->pt>300) muEff = 0.8627;
	else if(vLep.at(1)->pt>200) muEff = 0.8776;
	else if(vLep.at(1)->pt>150) muEff = 0.8986;
	else if(vLep.at(1)->pt>100) muEff = 0.8949;
	else if(vLep.at(1)->pt>60) muEff = 0.9025;
	else if(vLep.at(1)->pt>50) muEff = 0.9165;
	else if(vLep.at(1)->pt>40) muEff = 0.9097;
	else if(vLep.at(1)->pt>35) muEff = 0.9080;      
      }
      else if(eta2>0.4){
	if(vLep.at(1)->pt>500) muEff = 0.0;
	else if(vLep.at(1)->pt>300) muEff = 0.9341;
	else if(vLep.at(1)->pt>200) muEff = 0.9494;
	else if(vLep.at(1)->pt>150) muEff = 0.9376;
	else if(vLep.at(1)->pt>100) muEff = 0.9385;
	else if(vLep.at(1)->pt>60) muEff = 0.9431;
	else if(vLep.at(1)->pt>50) muEff = 0.9502;
	else if(vLep.at(1)->pt>40) muEff = 0.9465;
	else if(vLep.at(1)->pt>35) muEff = 0.9433;      
      }
      else if(eta2>=0.0){
	if(vLep.at(1)->pt>500) muEff = 0.0;
	else if(vLep.at(1)->pt>300) muEff = 0.9433;
	else if(vLep.at(1)->pt>200) muEff = 0.9076;
	else if(vLep.at(1)->pt>150) muEff = 0.9175;
	else if(vLep.at(1)->pt>100) muEff = 0.9106;
	else if(vLep.at(1)->pt>60) muEff = 0.9141;
	else if(vLep.at(1)->pt>50) muEff = 0.9156;
	else if(vLep.at(1)->pt>40) muEff = 0.9081;
	else if(vLep.at(1)->pt>35) muEff = 0.9111;      
      }
      //std::cout<<"weight for leading electron with eta: "<<eta1<<" and pt: "<<vLep.at(0)->pt<<" is: "<<elEff<<" weight for subleading muon with eta: "<<eta2<<" and pt: "<<vLep.at(1)->pt<<" is: "<<muEff<<" total sf = "<<sf<<std::endl;
    }
    else{ //elEff is for subleading
      if(eta2<0.8) elEff = 0.980;
      else if(eta2<1.5) elEff  = 0.986;
      else{
	if(vLep.at(1)->pt<40) elEff= 0.9955*( ROOT::Math::normal_cdf(vLep.at(1)->pt-34.157,1.62)); //take from fitted function
	else elEff = 0.996;
      }
      //now muon efficiency
      if(eta1>2.1){
	if(vLep.at(0)->pt>500) muEff = 0.0;
	else if(vLep.at(0)->pt>300) muEff = 0.7778;
	else if(vLep.at(0)->pt>200) muEff = 0.7964;
	else if(vLep.at(0)->pt>150) muEff = 0.8071;
	else if(vLep.at(0)->pt>100) muEff = 0.7895;
	else if(vLep.at(0)->pt>60) muEff = 0.8113;
	else if(vLep.at(0)->pt>50) muEff = 0.7684;
	else if(vLep.at(0)->pt>40) muEff = 0.7692;
	else if(vLep.at(0)->pt>35) muEff = 0.7607;      
      }
      else if(eta1>1.2){
	if(vLep.at(0)->pt>500) muEff = 0.0;
	else if(vLep.at(0)->pt>300) muEff = 0.8848;
	else if(vLep.at(0)->pt>200) muEff = 0.8279;
	else if(vLep.at(0)->pt>150) muEff = 0.8300;
	else if(vLep.at(0)->pt>100) muEff = 0.8356;
	else if(vLep.at(0)->pt>60) muEff = 0.8573;
	else if(vLep.at(0)->pt>50) muEff = 0.8674;
	else if(vLep.at(0)->pt>40) muEff = 0.8735;
	else if(vLep.at(0)->pt>35) muEff = 0.8638;      
      }
      else if(eta1>0.9){
	if(vLep.at(0)->pt>500) muEff = 0.0;
	else if(vLep.at(0)->pt>300) muEff = 0.8627;
	else if(vLep.at(0)->pt>200) muEff = 0.8776;
	else if(vLep.at(0)->pt>150) muEff = 0.8986;
	else if(vLep.at(0)->pt>100) muEff = 0.8949;
	else if(vLep.at(0)->pt>60) muEff = 0.9025;
	else if(vLep.at(0)->pt>50) muEff = 0.9165;
	else if(vLep.at(0)->pt>40) muEff = 0.9097;
	else if(vLep.at(0)->pt>35) muEff = 0.9080;      
      }
      else if(eta1>0.4){
	if(vLep.at(0)->pt>500) muEff = 0.0;
	else if(vLep.at(0)->pt>300) muEff = 0.9341;
	else if(vLep.at(0)->pt>200) muEff = 0.9494;
	else if(vLep.at(0)->pt>150) muEff = 0.9376;
	else if(vLep.at(0)->pt>100) muEff = 0.9385;
	else if(vLep.at(0)->pt>60) muEff = 0.9431;
	else if(vLep.at(0)->pt>50) muEff = 0.9502;
	else if(vLep.at(0)->pt>40) muEff = 0.9465;
	else if(vLep.at(0)->pt>35) muEff = 0.9433;      
      }
      else if(eta1>=0.0){
	if(vLep.at(0)->pt>500) muEff = 0.0;
	else if(vLep.at(0)->pt>300) muEff = 0.9433;
	else if(vLep.at(0)->pt>200) muEff = 0.9076;
	else if(vLep.at(0)->pt>150) muEff = 0.9175;
	else if(vLep.at(0)->pt>100) muEff = 0.9106;
	else if(vLep.at(0)->pt>60) muEff = 0.9141;
	else if(vLep.at(0)->pt>50) muEff = 0.9156;
	else if(vLep.at(0)->pt>40) muEff = 0.9081;
	else if(vLep.at(0)->pt>35) muEff = 0.9111;      
      }
      //std::cout<<"weight for leading muon with eta: "<<eta1<<" and pt: "<<vLep.at(0)->pt<<" is: "<<muEff<<" weight for subleading electron with eta: "<<eta2<<" and pt: "<<vLep.at(1)->pt<<" is: "<<elEff<<" total sf = "<<sf<<std::endl;

    }//end check on electron being subleading or leading    

    //scale factor is combined efficiency (AND of reco'ing both el and mu)
    sf = muEff*elEff;

  }//end cross channel
  //std::cout<<"scale factor at end of function: "<<sf<<std::endl;
  return sf;

}

float getLepIDSF(TLepton* lep){

  float sf;

  if(lep->isMu){

    if(lep->pt<40){
      if(fabs(lep->eta)>2.1) sf = 0.9778;
      else if(fabs(lep->eta)>1.2) sf = 0.9909;
      else if(fabs(lep->eta)>0.9) sf = 0.9714;
      else sf = 0.9794;
    }
    else if(lep->pt<50){
      if(fabs(lep->eta)>2.1) sf = 0.9783;
      else if(fabs(lep->eta)>1.2) sf = 0.993;
      else if(fabs(lep->eta)>0.9) sf = 0.9741;
      else sf = 0.9803;
    }
    else if(lep->pt<60){
      if(fabs(lep->eta)>2.1) sf = 0.9758;
      else if(fabs(lep->eta)>1.2) sf = 0.9918;
      else if(fabs(lep->eta)>0.9) sf = 0.9743;
      else sf = 0.9796;
    }
    else{
      if(fabs(lep->eta)>2.1) sf = 0.9753;
      else if(fabs(lep->eta)>1.2) sf = 0.9868;
      else if(fabs(lep->eta)>0.9) sf = 0.9718;
      else sf =0.9744;
    }    

  }
  else{//electron


    if(lep->eta>1.566){
      if(lep->pt>300) sf = 0.9971;
      else if(lep->pt>200) sf = 0.9916;
      else if(lep->pt>100) sf = 1.0159;
      else if(lep->pt>75)  sf = 0.9899;
      else if(lep->pt>50)  sf = 0.9716;
      else if(lep->pt>40)  sf = 0.9455;
      else if(lep->pt>30)  sf = 0.9569;
    }
    else if(lep->eta > 1.442) sf = 0; //should never happen but this is dummy to prevent electrons in gap
    else if(lep->eta>0.8){
      if(lep->pt>300) sf = 0.943;
      else if(lep->pt>200) sf = 0.9834;
      else if(lep->pt>100) sf = 0.9961;
      else if(lep->pt>75)  sf = 0.9970;
      else if(lep->pt>50)  sf = 0.9788;
      else if(lep->pt>40)  sf = 0.9668;
      else if(lep->pt>30)  sf = 0.9756;
    }
    else if(lep->eta>0.0){
      if(lep->pt>300) sf = 1.019;
      else if(lep->pt>200) sf = 0.9742;
      else if(lep->pt>100) sf = 0.9926;
      else if(lep->pt>75)  sf = 0.9360;
      else if(lep->pt>50)  sf = 0.9839;
      else if(lep->pt>40)  sf = 0.9691;
      else if(lep->pt>30)  sf = 0.9848;
    }
    else if(lep->eta> -0.8){
      if(lep->pt>300) sf = 1.0099;
      else if(lep->pt>200) sf = 0.9699;
      else if(lep->pt>100) sf = 0.9842;
      else if(lep->pt>75)  sf = 0.9810;
      else if(lep->pt>50)  sf = 0.9689;
      else if(lep->pt>40)  sf = 0.9613;
      else if(lep->pt>30)  sf = 0.9561;
    }
    else if(lep->eta > -1.442){
      if(lep->pt>300) sf = 0.9820;
      else if(lep->pt>200) sf = 0.9785;
      else if(lep->pt>100) sf = 0.9817;
      else if(lep->pt>75)  sf = 1.0024;
      else if(lep->pt>50)  sf = 0.9757;
      else if(lep->pt>40)  sf = 0.9668;
      else if(lep->pt>30)  sf = 0.9622;
    }
    else if(lep->eta > -1.566) sf = 0; //same dummy protection against gap as above
    else if(lep->eta > -2.4){
      if(lep->pt>300) sf = 0.883;
      else if(lep->pt>200) sf = 0.9810;
      else if(lep->pt>100) sf = 1.0028;
      else if(lep->pt>75)  sf = 0.9651;
      else if(lep->pt>50)  sf = 0.9615;
      else if(lep->pt>40)  sf = 0.9509;
      else if(lep->pt>30)  sf = 0.9523;
    }
    else sf=0; //lepton eta less than -2.4 shouldn't happen
  }

  return sf;
}

float getLepIDSF(std::vector<TLepton*> vLep){

  float sf1,sf2;
  sf1 = getLepIDSF(vLep.at(0));
  sf2 = getLepIDSF(vLep.at(1));
  float sf = sf1*sf2;
  return sf;

}

float getLepIsoSF(TLepton* lep){

  float sf;
  if(lep->isMu) sf = 1.0; //no scale factor for muon iso
  else{
    if(fabs(lep->eta) > 2.0){
      if(lep->pt>50) sf = 1.02;
      else if(lep->pt>40) sf = 1.033;
      else if (lep->pt>30) sf = 1.042;
    }
    else if(fabs(lep->eta) > 1.566){
      if(lep->pt>50) sf = 1.002;
      else if(lep->pt>40) sf = 1.006;
      else if (lep->pt>30) sf = 1.011;
    }
    else if(fabs(lep->eta) > 0.8){
      if(lep->pt>50) sf = 0.9982;
      else if(lep->pt>40) sf = 0.9914;
      else if (lep->pt>30) sf = 0.9904;
    }
    else if(fabs(lep->eta) >= 0.0){
      if(lep->pt>50) sf = 0.9848;
      else if(lep->pt>40) sf = 0.9791;
      else if (lep->pt>30) sf = 0.9794;
    }
  }

  return sf;

}

float getLepIsoSF(std::vector<TLepton*> leps){

  float sf1 = getLepIsoSF(leps.at(0));
  float sf2 = getLepIsoSF(leps.at(1));
  float sf = sf1* sf2;
  return sf;

}

std::pair<float,float> getFakeRateByFlavor (std::string flavor){

  float mufr;
  float elfr;

  if(flavor=="data"){
    mufr=0.347;
    elfr=0.288;
  }

  if(flavor=="light"){
    mufr = 0.120;
    elfr = 0.209;
  }

  if(flavor=="charm"){
    mufr=0.376;
    elfr=0.215;
  }

  if(flavor=="bottom"){
    mufr=0.283;
    elfr=0.180;
  }
  if(flavor=="fakes"){
    mufr=0.109;
    elfr=0.278;
  }
  if(flavor=="average"){
    mufr=0.281;
    elfr=0.203;
  }
  if(flavor=="light_qcd"){
    mufr=0.193;
    elfr=0.585;
  }
  if(flavor=="charm_qcd"){
    mufr=0.330;
    elfr=0.323;
  }
  if(flavor=="bottom_qcd"){
    mufr=0.390;
    elfr=0.211;
  }
  if(flavor=="fakes_qcd"){
    mufr=0.354;
    elfr=0.374;
  }
  if(flavor=="average_qcd"){
    mufr=0.392;
    elfr=0.371;
  }

  if(flavor=="light_ttb"){
    mufr=0.405;
    elfr=0.249;
  }
  if(flavor=="charm_ttb"){
    mufr=0.376;
    elfr=0.209;
  }
  if(flavor=="bottom_ttb"){
    mufr=0.297;
    elfr=0.185;
  }
  if(flavor=="fakes_ttb"){
    mufr=0.117;
    elfr=0.263;
  }
  if(flavor=="unmatched_ttb"){
    mufr=0.692;
    elfr=0.116;
  }
  if(flavor=="average_ttb"){
    mufr=0.294;
    elfr=0.202;
  }


  std::pair<float,float> fr(mufr,elfr);
  return fr;
}

std::vector<float> weights_elel(std::string flavor){

  std::vector<float> weights;
  float elfr = getFakeRateByFlavor(flavor).second;
  float elpr = getElPromptRate("MVATightRC");
  //dielectron channel so only same flavor weights, order is 0: nt00, 1: nt01, 2: nt10, 3: nt11
  weights.push_back(WeightSF_T0(elpr,elfr));
  weights.push_back(WeightSF_T1(elpr,elfr));
  weights.push_back(WeightSF_T1(elpr,elfr));
  weights.push_back(WeightSF_T2(elpr,elfr));
  return weights;
}

std::vector<float> weights_elmu(std::string flavor){

  std::vector<float> weights;
  float elfr = getFakeRateByFlavor(flavor).second;
  float elpr = getElPromptRate("MVATightRC");
  float mufr = getFakeRateByFlavor(flavor).first;
  float mupr = getMuPromptRate("CBTight");

  //cross channel, but order remains the same
  weights.push_back(WeightOF_T00(elpr,elfr,mupr,mufr));
  weights.push_back(WeightOF_T01(elpr,elfr,mupr,mufr));
  weights.push_back(WeightOF_T10(elpr,elfr,mupr,mufr));
  weights.push_back(WeightOF_T11(elpr,elfr,mupr,mufr));

  return weights;
}

std::vector<float> weights_mumu(std::string flavor){

  std::vector<float> weights;
  float mufr = getFakeRateByFlavor(flavor).first;
  float mupr = getMuPromptRate("MVATightRC");
  //dimuectron channel so only same flavor weights, order is 0: nt00, 1: nt01, 2: nt10, 3: nt11
  weights.push_back(WeightSF_T0(mupr,mufr));
  weights.push_back(WeightSF_T1(mupr,mufr));
  weights.push_back(WeightSF_T1(mupr,mufr));
  weights.push_back(WeightSF_T2(mupr,mufr));
  return weights;
}

float getPUWeight(TH1F* h, int nPU){

  float weight = -1;
  weight = h->GetBinContent(nPU+1); // plus one because 1st bin is 0-0.9999 so pilupe of 1 falls in bin 2
  //std::cout<<"nInteractions: "<<nPU<<" and weight: "<<weight<<std::endl;
  return weight;

};



std::vector<TH1F*> initHistos(std::vector<Variable*> vVar, int nMu, std::string cutname){

  //make vector
  std::vector<TH1F*> hists;
  std::string chan ="";
  if(nMu==-1) chan ="All";
  if(nMu==0) chan ="ElEl";
  if(nMu==1) chan ="ElMu";
  if(nMu==2) chan ="MuMu";  
  
  for(unsigned int i=0; i< vVar.size(); i++){
    Variable* var = vVar.at(i);
    std::string histname = chan+"_"+cutname+"_"+var->name;
    hists.push_back(new TH1F(histname.c_str(),(var->name).c_str(), var->nbins, var->xmin, var->xmax));
  }
  for(unsigned int i=0; i< hists.size();i++){
    //save weights
    hists.at(i)->Sumw2();
  }
  return hists;

};


void fillHistos(std::vector<TH1F*> hists,std::vector<TLepton*> vSSLep, std::vector<TLepton*> vNonSSLep, std::vector<TJet*> jets, float MET, float DilepMass, float weight){
  
  
  //make nConst and HT
  int nConst = vNonSSLep.size() + jets.size();
  float HT = vSSLep.at(0)->pt + vSSLep.at(1)->pt;
  for(unsigned int i=0; i< vNonSSLep.size(); i++){
    HT = HT + vNonSSLep.at(i)->pt;
  }
  for(unsigned int i=0; i< jets.size(); i++){
    HT = HT + jets.at(i)->pt;
  }
  
  //fill histograms
  for(unsigned int i=0; i<hists.size(); i++){
   
    std::string title = hists.at(i)->GetTitle();
    if(title=="Lep1Pt") hists.at(i)->Fill(vSSLep.at(0)->pt,weight);
    if(title=="Lep1Eta") hists.at(i)->Fill(vSSLep.at(0)->eta,weight);
    if(title=="Lep1Phi") hists.at(i)->Fill(vSSLep.at(0)->phi,weight);
    
    if(title=="Lep2Pt") hists.at(i)->Fill(vSSLep.at(1)->pt,weight);
    if(title=="Lep2Eta") hists.at(i)->Fill(vSSLep.at(1)->eta,weight);
    if(title=="Lep2Phi") hists.at(i)->Fill(vSSLep.at(1)->phi,weight);
    
    if(title=="cleanAK4Jet1Pt") {
      if(jets.size() >0) hists.at(i)->Fill(jets.at(0)->pt,weight);
      else hists.at(i)->Fill(-999,weight);
    }
    if(title=="cleanAK4Jet1Eta") {
      if(jets.size() >0) hists.at(i)->Fill(jets.at(0)->eta,weight);
      else hists.at(i)->Fill(-999,weight);
    }
    if(title=="cleanAK4Jet1Phi"){
      if(jets.size() >0) hists.at(i)->Fill(jets.at(0)->phi,weight);
      else hists.at(i)->Fill(-999,weight);
    }
    
    if(title=="cleanAK4Jet2Pt"){
      if(jets.size()>1) hists.at(i)->Fill(jets.at(1)->pt,weight);
      else hists.at(i)->Fill(-999,weight);
    }
    if(title=="cleanAK4Jet2Eta"){
      if(jets.size()>1) hists.at(i)->Fill(jets.at(1)->eta,weight);
      else hists.at(i)->Fill(-999,weight);
    }
    if(title=="cleanAK4Jet2Phi"){
      if(jets.size()>1) hists.at(i)->Fill(jets.at(1)->phi,weight);
      else hists.at(i)->Fill(-999,weight);
    }
    
    if(title=="cleanAK4HT") hists.at(i)->Fill(HT,weight);
    if(title=="nCleanAK4Jets") hists.at(i)->Fill(jets.size(),weight);
    if(title=="nNonSSLeps") hists.at(i)->Fill(vNonSSLep.size(),weight);
    if(title=="MET") hists.at(i)->Fill(MET,weight);
    if(title=="DilepMass") hists.at(i)->Fill(DilepMass,weight);
    if(title=="nConst") hists.at(i)->Fill(nConst,weight);
    
    
  }
  
  
};
		      
void writeHistos(TFile* f, std::vector<TH1F*> hists){

  for(unsigned int i=0; i< hists.size();i++){
    f->WriteTObject(hists.at(i));
  }
};

std::vector<Sample*> appendSampleVectors(std::vector<Sample*> vS1,std::vector<Sample*> vS2){
  std::vector<Sample*> vS;
  for(unsigned int i=0; i<vS1.size();i++){
    vS.push_back(vS1.at(i));
  }
  for(unsigned int i=0;i<vS2.size();i++){
    vS.push_back(vS2.at(i));
  }
  return vS;
}

//added by rizki
std::vector<Sample*> appendSampleVectors(std::vector<Sample*> vS1,std::vector<Sample*> vS2,
										 std::vector<Sample*> vS3,std::vector<Sample*> vS4,
										 std::vector<Sample*> vS5,std::vector<Sample*> vS6
										)
										{
  std::vector<Sample*> vS;
  for(unsigned int i=0; i<vS1.size();i++){
    vS.push_back(vS1.at(i));
  }
  for(unsigned int i=0;i<vS2.size();i++){
    vS.push_back(vS2.at(i));
  }
  for(unsigned int i=0;i<vS3.size();i++){
    vS.push_back(vS3.at(i));
  }
  for(unsigned int i=0;i<vS4.size();i++){
    vS.push_back(vS4.at(i));
  }
  for(unsigned int i=0;i<vS5.size();i++){
    vS.push_back(vS5.at(i));
  }
  for(unsigned int i=0;i<vS6.size();i++){
    vS.push_back(vS6.at(i));
  }
  return vS;
}


std::vector<Sample*> get74BkgSampleVec(std::string cut, float lumi, std::string elID, std::string muID, std::string era){  

   //setup info for list of samples, xsec and events run  //make vector of actual number of events run MULTIPLIED BY AMCATNLO WEIGHT
  std::vector<std::string> vBkgNames;  std::vector<float> vXsec;  std::vector<float> vNEvts;

  //************** MC *************

 //vBkgNames.push_back("TTbar");  vXsec.push_back(831.76);  vNEvts.push_back(42730273 * 0.331582);
  vBkgNames.push_back("TTZ");    vXsec.push_back(0.2529);  vNEvts.push_back(398000 * 0.464779);
  vBkgNames.push_back("TTW");    vXsec.push_back(0.2043);  vNEvts.push_back(252908 * 0.513428);
  vBkgNames.push_back("TTH");    vXsec.push_back(0.215);  vNEvts.push_back(17882125 *0.296995);
  vBkgNames.push_back("TTTT");    vXsec.push_back(0.009103);  vNEvts.push_back(1238145 *0.4177);
  vBkgNames.push_back("WZ");     vXsec.push_back(4.42965); vNEvts.push_back(1925000 * 1);
  //vBkgNames.push_back("WJets");  vXsec.push_back(61526.7); vNEvts.push_back(24151270 * 0.683948);
  //vBkgNames.push_back("DYJets"); vXsec.push_back(6025.2);  vNEvts.push_back(28825132 * 0.6693);
  vBkgNames.push_back("ZZ");     vXsec.push_back(1.212);  vNEvts.push_back(6652512 * 0.689851);
  vBkgNames.push_back("VH");     vXsec.push_back(0.952);  vNEvts.push_back(993464 * 0.45775);
  vBkgNames.push_back("WpWp");   vXsec.push_back(0.03711); vNEvts.push_back( 140224* 1);
  vBkgNames.push_back("WW-mpi"); vXsec.push_back(1.64);   vNEvts.push_back( 843514* 1);  
  vBkgNames.push_back("WWZ");    vXsec.push_back(0.1651); vNEvts.push_back(250000*0.885872);
  vBkgNames.push_back("WZZ");    vXsec.push_back(0.05565); vNEvts.push_back(250000*0.876672);
  vBkgNames.push_back("ZZZ");    vXsec.push_back(0.01398); vNEvts.push_back(250000*0.8554);

  //******* Non Prompt**********
  //vBkgNames.push_back("NonPromptMC");  vXsec.push_back(831.76);  vNEvts.push_back(42730273 * 0.331582);
  vBkgNames.push_back("NonPrompt"); vXsec.push_back(1); vNEvts.push_back(1);
  vBkgNames.push_back("ChargeMisID"); vXsec.push_back(1); vNEvts.push_back(1);
  //now make vector to hold weights;
  std::vector<float> vWeights;
  for(std::vector<float>::size_type ui=0; ui<vXsec.size(); ui++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(ui) / vNEvts.at(ui) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  //now make samples and add to vector
  std::vector<Sample*> vSample;
  //TFile* ttfile = TFile::Open("/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/TTbar.root");
  //Sample* ttSample = new Sample(vBkgNames.at(0),ttfile, vWeights.at(0),vXsec.at(0),cut,kRed+2);
  //vSample.push_back(ttSample);

  std::string ttZfilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/TTZ_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* ttZfile = TFile::Open(ttZfilename.c_str());
  Sample* ttZSample = new Sample(vBkgNames.at(0),ttZfile, vWeights.at(0),vXsec.at(0),cut,kRed);
  vSample.push_back(ttZSample);

  std::string ttWfilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/TTW_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* ttwfile = TFile::Open(ttWfilename.c_str());
  Sample* ttwSample = new Sample(vBkgNames.at(1),ttwfile, vWeights.at(1),vXsec.at(1),cut,kYellow-2);
  vSample.push_back(ttwSample);

  std::string tthfilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/TTH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* tthfile = TFile::Open(tthfilename.c_str());
  Sample* tthSample = new Sample(vBkgNames.at(2),tthfile, vWeights.at(2),vXsec.at(2),cut,kYellow);
  vSample.push_back(tthSample);

  std::string ttttfilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/TTTT_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* ttttfile = TFile::Open(ttttfilename.c_str());
  Sample* ttttSample = new Sample(vBkgNames.at(3),ttttfile, vWeights.at(3),vXsec.at(3),cut,kRed+2);
  vSample.push_back(ttttSample);


  std::string wzfilename="/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/WZ_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* wzfile = TFile::Open(wzfilename.c_str());
  Sample* wzSample = new Sample(vBkgNames.at(4),wzfile, vWeights.at(4),vXsec.at(4),cut,kBlue-3);
  vSample.push_back(wzSample);

  //TFile* wjfile = TFile::Open("/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/WJets_Mu"+muID+"_El"+elID+"_"+era+".root");
  //Sample* wjSample = new Sample(vBkgNames.at(4),wjfile, vWeights.at(4),vXsec.at(4),cut,kGreen+2);
  //vSample.push_back(wjSample);

  /*std::string dyfilename =  "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/DYJets_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* dyjfile = TFile::Open(dyfilename.c_str());
  Sample* dyjSample = new Sample(vBkgNames.at(3),dyjfile, vWeights.at(3),vXsec.at(3),cut,kMagenta+2);
  vSample.push_back(dyjSample);*/
  
  std::string zzfilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/ZZ_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* zzjfile = TFile::Open(zzfilename.c_str());
  Sample* zzjSample = new Sample(vBkgNames.at(5),zzjfile, vWeights.at(5),vXsec.at(5),cut,kOrange+1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(zzjSample);

  /*std::string vhfilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/VH_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* vhjfile = TFile::Open(vhfilename.c_str());
  Sample* vhjSample = new Sample(vBkgNames.at(6),vhjfile, vWeights.at(6),vXsec.at(6),cut,kBlue);
  //std::cout<<"weight for VH is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(vhjSample);*/

  std::string wpwpfilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/WpWp_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* wpwpfile = TFile::Open(wpwpfilename.c_str());
  Sample* wpwpSample = new Sample(vBkgNames.at(7),wpwpfile, vWeights.at(7),vXsec.at(7),cut,kGreen+1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(wpwpSample);

  /*std::string wwmpifilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/WW-mpi_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* wwmpifile = TFile::Open(wwmpifilename.c_str());
  Sample* wwmpiSample = new Sample(vBkgNames.at(8),wwmpifile, vWeights.at(8),vXsec.at(8),cut,kGreen-1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(wwmpiSample);*/


  std::string wwzfilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/WWZ_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* wwzfile = TFile::Open(wwzfilename.c_str());
  Sample* wwzSample = new Sample(vBkgNames.at(9),wwzfile, vWeights.at(9),vXsec.at(9),cut,kViolet+1);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(wwzSample);

  std::string wzzfilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/WZZ_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* wzzfile = TFile::Open(wzzfilename.c_str());
  Sample* wzzSample = new Sample(vBkgNames.at(10),wzzfile, vWeights.at(10),vXsec.at(10),cut,kViolet+3);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(wzzSample);

  std::string zzzfilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/ZZZ_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* zzzfile = TFile::Open(zzzfilename.c_str());
  Sample* zzzSample = new Sample(vBkgNames.at(11),zzzfile, vWeights.at(11),vXsec.at(11),cut,kViolet);
  //std::cout<<"weight for ZZ is: "<<vWeights.at(5)<<std::endl;
  vSample.push_back(zzzSample);


  //********** Nonprompt ***************
  /*std::string npTTfilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/NonPromptTTJets_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* npttfile = TFile::Open(nptTfilename.c_str());
  Sample* npttSample = new Sample(vBkgNames.at(-1),npttfile,vWeights.at(-1),vXsec.at(01),cut,kBlue);
  vSample.push_back(npttSample)*/

  std::string npfilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/NonPromptData_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* npfile = TFile::Open(npfilename.c_str());
  Sample* npSample = new Sample(vBkgNames.at(12),npfile,vWeights.at(13),vXsec.at(13),cut,kGray);
  vSample.push_back(npSample);

  //********ChargeMisID**********
  std::string cmidfilename = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/ChargeMisID_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* cmidfile = TFile::Open(cmidfilename.c_str());
  Sample* cmidSample = new Sample(vBkgNames.at(13),cmidfile,vWeights.at(13),vXsec.at(13),cut,kGreen); //force charge misID to start here since only at this point do we filter events
  vSample.push_back(cmidSample);


  return vSample;

}

std::vector<Sample*> get74InclusiveSigSampleVecForTable(std::string cut, float lumi, std::string elID, std::string muID, std::string era){
  //make names vector
  std::vector<std::string> vSigNames;
  std::vector<float> vXsec;
  //br is OR of either side decaying to ssdl. BR(ssdl) for one side = BR(W->enu) OR BR(W->munu) **2 where the square comes from AND requiring both to decay leptonically
  //float BRssdl= 2*( pow((.1063 + .1071 + .1138),2)); INCLUSIVE SO NO BRANCHING RATIO
  std::vector<int> vNEvts;
  vSigNames.push_back("LH_X53X53_M-700"); vXsec.push_back(0.442); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-700"); vXsec.push_back(0.442); vNEvts.push_back(297400.);
  vSigNames.push_back("LH_X53X53_M-800"); vXsec.push_back(.190); vNEvts.push_back(295600.);
  vSigNames.push_back("RH_X53X53_M-800"); vXsec.push_back(.190); vNEvts.push_back(299600.);
  vSigNames.push_back("LH_X53X53_M-900"); vXsec.push_back(.0877); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-900"); vXsec.push_back(.0877); vNEvts.push_back(299800.);
  vSigNames.push_back("LH_X53X53_M-1000"); vXsec.push_back(0.0427); vNEvts.push_back(293600.);
  vSigNames.push_back("RH_X53X53_M-1000"); vXsec.push_back(0.0427); vNEvts.push_back(299000.);
  vSigNames.push_back("LH_X53X53_M-1100"); vXsec.push_back(0.0217); vNEvts.push_back(299600.);
  vSigNames.push_back("RH_X53X53_M-1100"); vXsec.push_back(0.0217); vNEvts.push_back(299800.);
  vSigNames.push_back("LH_X53X53_M-1200"); vXsec.push_back(0.0114); vNEvts.push_back(295400.);
  vSigNames.push_back("RH_X53X53_M-1200"); vXsec.push_back(0.0114); vNEvts.push_back(300000.);
  vSigNames.push_back("LH_X53X53_M-1300"); vXsec.push_back(0.00618); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-1300"); vXsec.push_back(0.00618); vNEvts.push_back(293600.);
  vSigNames.push_back("LH_X53X53_M-1400"); vXsec.push_back(0.00342); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-1400"); vXsec.push_back(0.00342); vNEvts.push_back(298400.);
  vSigNames.push_back("LH_X53X53_M-1500"); vXsec.push_back(0.00193); vNEvts.push_back(298400.);
  vSigNames.push_back("RH_X53X53_M-1500"); vXsec.push_back(0.00193); vNEvts.push_back(300000.);
  vSigNames.push_back("LH_X53X53_M-1600"); vXsec.push_back(0.00111); vNEvts.push_back(300000.);
  vSigNames.push_back("RH_X53X53_M-1600"); vXsec.push_back(0.00111); vNEvts.push_back(300000.);

 

  //vector to hold weights
  std::vector<float> vWeights;
  for(std::vector<float>::size_type i=0; i<vXsec.size();i++){
    vWeights.push_back( lumi * 1000 * ( vXsec.at(i) / vNEvts.at(i) ) ); //factor of 1000 to convert lumi to pb^-1
  }

  std::vector<Sample*> vSigSamples;
  std::string lh700 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m700LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53700Lfile = TFile::Open(lh700.c_str());
  Sample* x53x53m700L = new Sample(vSigNames.at(0),x53x53700Lfile,vWeights.at(0),vXsec.at(0),cut,kGreen,2);
  vSigSamples.push_back(x53x53m700L);
  std::string rh700 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m700RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53700Rfile = TFile::Open(rh700.c_str());
  Sample* x53x53m700R = new Sample(vSigNames.at(1),x53x53700Rfile,vWeights.at(1),vXsec.at(1),cut,kGreen,1);
  vSigSamples.push_back(x53x53m700R);

  std::string lh800 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m800LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53800Lfile = TFile::Open(lh800.c_str());
  Sample* x53x53m800L = new Sample(vSigNames.at(2),x53x53800Lfile,vWeights.at(2),vXsec.at(2),cut,kBlue,2);
  vSigSamples.push_back(x53x53m800L);
  std::string rh800 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m800RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53800Rfile = TFile::Open(rh800.c_str());
  Sample* x53x53m800R = new Sample(vSigNames.at(3),x53x53800Rfile,vWeights.at(3),vXsec.at(3),cut,kBlue,1);
  vSigSamples.push_back(x53x53m800R);

  std::string lh900 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m900LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53900Lfile = TFile::Open(lh900.c_str());
  Sample* x53x53m900L = new Sample(vSigNames.at(4),x53x53900Lfile,vWeights.at(4),vXsec.at(4),cut,kGreen,2);
  vSigSamples.push_back(x53x53m900L);
  std::string rh900 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m900RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x53900Rfile = TFile::Open(rh900.c_str());
  Sample* x53x53m900R = new Sample(vSigNames.at(5),x53x53900Rfile,vWeights.at(5),vXsec.at(5),cut,kGreen,1);
  vSigSamples.push_back(x53x53m900R);

  std::string lh1000 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1000LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531000Lfile = TFile::Open(lh1000.c_str());
  Sample* x53x53m1000L = new Sample(vSigNames.at(6),x53x531000Lfile,vWeights.at(6),vXsec.at(6),cut,kCyan,2);
  vSigSamples.push_back(x53x53m1000L);
  std::string rh1000 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1000RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531000Rfile = TFile::Open(rh1000.c_str());
  Sample* x53x53m1000R = new Sample(vSigNames.at(7),x53x531000Rfile,vWeights.at(7),vXsec.at(7),cut,kCyan,1);
  vSigSamples.push_back(x53x53m1000R);

  std::string lh1100 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1100LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531100Lfile = TFile::Open(lh1100.c_str());
  Sample* x53x53m1100L = new Sample(vSigNames.at(8),x53x531100Lfile,vWeights.at(8),vXsec.at(8),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1100L);
  std::string rh1100 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1100RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531100Rfile = TFile::Open(rh1100.c_str());
  Sample* x53x53m1100R = new Sample(vSigNames.at(9),x53x531100Rfile,vWeights.at(9),vXsec.at(9),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1100R);

  std::string lh1200 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1200LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531200Lfile = TFile::Open(lh1200.c_str());
  Sample* x53x53m1200L = new Sample(vSigNames.at(10),x53x531200Lfile,vWeights.at(10),vXsec.at(10),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1200L);
  std::string rh1200 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1200RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531200Rfile = TFile::Open(rh1200.c_str());
  Sample* x53x53m1200R = new Sample(vSigNames.at(11),x53x531200Rfile,vWeights.at(11),vXsec.at(11),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1200R);

  std::string lh1300 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1300LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531300Lfile = TFile::Open(lh1300.c_str());
  Sample* x53x53m1300L = new Sample(vSigNames.at(12),x53x531300Lfile,vWeights.at(12),vXsec.at(12),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1300L);
  std::string rh1300 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1300RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531300Rfile = TFile::Open(rh1300.c_str());
  Sample* x53x53m1300R = new Sample(vSigNames.at(13),x53x531300Rfile,vWeights.at(13),vXsec.at(13),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1300R);

  std::string lh1400 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1400LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531400Lfile = TFile::Open(lh1400.c_str());
  Sample* x53x53m1400L = new Sample(vSigNames.at(14),x53x531400Lfile,vWeights.at(14),vXsec.at(14),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1400L);
  std::string rh1400 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1400RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531400Rfile = TFile::Open(rh1400.c_str());
  Sample* x53x53m1400R = new Sample(vSigNames.at(15),x53x531400Rfile,vWeights.at(15),vXsec.at(15),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1400R);

  std::string lh1500 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1500LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531500Lfile = TFile::Open(lh1500.c_str());
  Sample* x53x53m1500L = new Sample(vSigNames.at(16),x53x531500Lfile,vWeights.at(16),vXsec.at(16),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1500L);
  std::string rh1500 = "/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1500RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root";
  TFile* x53x531500Rfile = TFile::Open(rh1500.c_str());
  Sample* x53x53m1500R = new Sample(vSigNames.at(17),x53x531500Rfile,vWeights.at(17),vXsec.at(17),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1500R);

  /*  TFile* x53x531600Lfile = TFile::Open("/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1600LH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root");
  Sample* x53x53m1600L = new Sample(vSigNames.at(16),x53x531600Lfile,vWeights.at(16),vXsec.at(16),cut,kBlue,2);
  vSigSamples.push_back(x53x53m1600L);
  TFile* x53x531600Rfile = TFile::Open("/uscms_data/d3/clint/using_git/T53/ljmet/CMSSW_7_4_15_patch1/src/AnalysisCode/X53ThirteenTeVAnalysisCode/test/X53X53m1600RH_Inc_Mu"+muID+"_El"+elID+"_"+era+".root");
  Sample* x53x53m1600R = new Sample(vSigNames.at(17),x53x531600Rfile,vWeights.at(17),vXsec.at(17),cut,kBlue,1);
  vSigSamples.push_back(x53x53m1600R);*/


  return vSigSamples;

}

