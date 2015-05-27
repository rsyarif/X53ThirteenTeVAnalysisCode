#include <iostream>
#include <vector>
#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"

void printPlots(TH1F* hist1, TH1F* hist2, string label1, string label2, string Title, string xAxisLabel, string filename,float maxy=0.2);

void Gen_plots(){

  gStyle->SetOptStat(kFALSE);
  
  //load in files
  TFile* fl = new TFile("../../../LJMet/Com/python/ljmet_tree_T53T53_left_M-1000_JEC_hlttest_dummytoptag.root");
  TFile* fr = new TFile("../../../LJMet/Com/python/ljmet_tree_T53T53_right_M-1000_JEC_hlttest_dummytoptag.root");

  //grab trees
  TTree* tr = (TTree*) fr->Get("ljmet");
  TTree* tl = (TTree*) fl->Get("ljmet");


  //histograms for leptons - left handed
  TH1F* lep1Ptl = new TH1F("lep1Ptl", "p_{T} of lepton from top",100,0,400);
  //TH1F* lep1Etal = new TH1F("lep1Etal", "#eta of lepton from top",40,-4,4);
  //TH1F* lep1Phil = new TH1F("lep1Phil", "#phi of lepton from top",36,-3.6,3.6);

  TH1F* lep2Ptl = new TH1F("lep2Ptl", "p_{T} of lepton from top",100,0,400);
  //TH1F* lep2Etal = new TH1F("lep2Etal", "#eta of lepton from top",40,-4,4);
  //TH1F* lep2Phil = new TH1F("lep2Phil", "#phi of lepton from top",36,-3.6,3.6);


  //histograms for leptons - right handed
  TH1F* lep1Ptr = new TH1F("lep1Ptr", "p_{T} of lepton from top",100,0,400);
  //TH1F* lep1Etar = new TH1F("lep1Etar", "#eta of lepton from top",40,-4,4);
  //TH1F* lep1Phir = new TH1F("lep1Phir", "#phi of lepton from top",36,-3.6,3.6);

  TH1F* lep2Ptr = new TH1F("lep2Ptr", "p_{T} of lepton from top",100,0,400);
  //TH1F* lep2Etar = new TH1F("lep2Etar", "#eta of lepton from top",40,-4,4);
  //TH1F* lep2Phir = new TH1F("lep2Phir", "#phi of lepton from top",36,-3.6,3.6);

  //lepton pt vectors
  std::vector<double> * elPtsR;
  std::vector<double> * muPtsR;

  std::vector<double> * elPtsL;
  std::vector<double> * muPtsL;

  //jet kinematic variables
  std::vector<double> * genJetPtsR;
  std::vector<double> * genJetPtsL;

  std::vector<double> * genJetEtasR;
  std::vector<double> * genJetEtasL;

  std::vector<double> * genJetPhisR;
  std::vector<double> * genJetPhisL;


  tl->SetBranchAddress("elMatchedPt_DileptonCalc",&elPtsL);
  tl->SetBranchAddress("muMatchedPt_DileptonCalc",&muPtsL);

  tr->SetBranchAddress("elMatchedPt_DileptonCalc",&elPtsR);
  tr->SetBranchAddress("muMatchedPt_DileptonCalc",&muPtsR);

  tl->SetBranchAddress("genJetPt_DileptonCalc",&genJetPtsL);
  tl->SetBranchAddress("genJetEta_DileptonCalc",&genJetEtasL);
  tl->SetBranchAddress("genJetPhi_DileptonCalc",&genJetPhisL);

  tr->SetBranchAddress("genJetPt_DileptonCalc",&genJetPtsR);
  tr->SetBranchAddress("genJetEta_DileptonCalc",&genJetEtasR);
  tr->SetBranchAddress("genJetPhi_DileptonCalc",&genJetPhisR);


  int nL = tl->GetEntries();
  int nR = tr->GetEntries();

  for(int i = 0; i<nL;i++){
    tl->GetEntry(i);
    std::vector<double> ptsL;
    if(i%1000==0) std::cout<<"Completed "<<i<<" events out of "<<nL<<" of left handed sample"<<std::endl;
    for(unsigned int iel =0; iel< elPtsL->size();iel++){
      ptsL.push_back(elPtsL->at(iel)); 
    }

    for(unsigned int imu = 0; imu<muPtsL->size();imu++){
      ptsL.push_back(muPtsL->at(imu));
    }

    float maxpt = 0;

    for(unsigned int ilep =0; ilep<ptsL.size();ilep++){
      if(ptsL.at(ilep)>maxpt) maxpt=ptsL.at(ilep);
    }
    lep1Ptl->Fill(maxpt);

    float penpt = -1;
    for(unsigned int ilep =0; ilep<ptsL.size();ilep++){
      if(ptsL.at(ilep)>penpt && ptsL.at(ilep)!=maxpt) penpt=ptsL.at(ilep);
    }
    
    lep2Ptl->Fill(penpt);

  }


  for(int i = 0; i<nR;i++){
    tr->GetEntry(i);

    if(i%1000==0) std::cout<<"Completed "<<i<<" events out of "<<nR<<" of right handed sample"<<std::endl;
    std::vector<double> ptsR;
    for(unsigned int iel =0; iel< elPtsR->size();iel++){
      ptsR.push_back(elPtsR->at(iel)); 
    }

    for(unsigned int imu = 0; imu<muPtsR->size();imu++){
      ptsR.push_back(muPtsR->at(imu));
    }


    float maxpt = 0;

    for(unsigned int ilep =0; ilep<ptsR.size();ilep++){
      if(ptsR.at(ilep)>maxpt) maxpt=ptsR.at(ilep);
    }
    lep1Ptr->Fill(maxpt);

    float penpt = -1;
    for(unsigned int ilep =0; ilep<ptsR.size();ilep++){
      if(ptsR.at(ilep)>penpt && ptsR.at(ilep)!=maxpt) penpt=ptsR.at(ilep);
    }
    
    lep2Ptr->Fill(penpt);

  }
  
    
  /*
  //draw lepton pt info
  //first for electrons from X53
  tr->Draw("elMatchedPt_DileptonCalc>>lep1Ptr","abs(elMother_id_DileptonCalc)==8000003");
  tr->Draw("elMatchedEta_DileptonCalc>>lep1Etar","abs(elMother_id_DileptonCalc)==8000003");
  tr->Draw("elMatchedPhi_DileptonCalc>>lep1Phir","abs(elMother_id_DileptonCalc)==8000003");
  //then from muons from X53
  tr->Draw("muMatchedPt_DileptonCalc>>lep1Ptr","abs(muMother_id_DileptonCalc)==8000003");
  tr->Draw("muMatchedEta_DileptonCalc>>lep1Etar","abs(muMother_id_DileptonCalc)==8000003");
  tr->Draw("muMatchedPhi_DileptonCalc>>lep1Phir","abs(muMother_id_DileptonCalc)==8000003");

  //now electrons from top
  tr->Draw("elMatchedPt_DileptonCalc>>lep2Ptr","abs(elMother_id_DileptonCalc)==6");
  tr->Draw("elMatchedEta_DileptonCalc>>lep2Etar","abs(elMother_id_DileptonCalc)==6");
  tr->Draw("elMatchedPhi_DileptonCalc>>lep2Phir","abs(elMother_id_DileptonCalc)==6");
  //and finally muons from top
  tr->Draw("muMatchedPt_DileptonCalc>>lep2Ptr","abs(muMother_id_DileptonCalc)==6");
  tr->Draw("muMatchedEta_DileptonCalc>>lep2Etar","abs(muMother_id_DileptonCalc)==6");
  tr->Draw("muMatchedPhi_DileptonCalc>>lep2Phir","abs(muMother_id_DileptonCalc)==6");


  //draw lepton pt info
  //first for electrons from X53
  tl->Draw("elMatchedPt_DileptonCalc>>lep1Ptl","abs(elMother_id_DileptonCalc)==8000003");
  tl->Draw("elMatchedEta_DileptonCalc>>lep1Etal","abs(elMother_id_DileptonCalc)==8000003");
  tl->Draw("elMatchedPhi_DileptonCalc>>lep1Phil","abs(elMother_id_DileptonCalc)==8000003");
  //then from muons from X53
  tl->Draw("muMatchedPt_DileptonCalc>>lep1Ptl","abs(muMother_id_DileptonCalc)==8000003");
  tl->Draw("muMatchedEta_DileptonCalc>>lep1Etal","abs(muMother_id_DileptonCalc)==8000003");
  tl->Draw("muMatchedPhi_DileptonCalc>>lep1Phil","abs(muMother_id_DileptonCalc)==8000003");

  //now electlons from top
  tl->Draw("elMatchedPt_DileptonCalc>>lep2Ptl","abs(elMother_id_DileptonCalc)==6");
  tl->Draw("elMatchedEta_DileptonCalc>>lep2Etal","abs(elMother_id_DileptonCalc)==6");
  tl->Draw("elMatchedPhi_DileptonCalc>>lep2Phil","abs(elMother_id_DileptonCalc)==6");
  //and finally muons from top
  tl->Draw("muMatchedPt_DileptonCalc>>lep2Ptl","abs(muMother_id_DileptonCalc)==6");
  tl->Draw("muMatchedEta_DileptonCalc>>lep2Etal","abs(muMother_id_DileptonCalc)==6");
  tl->Draw("muMatchedPhi_DileptonCalc>>lep2Phil","abs(muMother_id_DileptonCalc)==6");
  */

  printPlots(lep1Ptl,lep1Ptr,"1 TeV LH X53","1 TeV RH X53","Gen Lepton p_{T} from X53","p_{T} GeV","GenLepton_LeadPt_pair.pdf",0.04);
  printPlots(lep2Ptl,lep2Ptr,"1 TeV LH X53","1 TeV RH X53","Gen Lepton p_{T} from Top quark","p_{T} GeV","GenLepton_SubPt_pair.pdf",0.06);

//   //printPlots(lep1Etal,lep1Etar,"1 TeV LH X53","1 TeV RH X53","Gen Lepton #eta from X53","#eta","LepEta_fromX53_pair.pdf");
//   //printPlots(lep2Etal,lep2Etar,"1 TeV LH X53","1 TeV RH X53","Gen Lepton #eta from top quark","#eta","LepEta_fromTop_pair.pdf");

//   //printPlots(lep1Phil,lep1Phir,"1 TeV LH X53","1 TeV RH X53","Gen Lepton #phi from X53","#phi","LepPhi_fromX53_pair.pdf");
//   //printPlots(lep2Phil,lep2Phir,"1 TeV LH X53","1 TeV RH X53","Gen Lepton #phi from top quark","#phi","LepPhi_fromTop_pair.pdf");


   //gen jet histograms
   TH1F* genJet1PtR = new TH1F("genJet1PtR","p_{T} of Leading Gen Jet",100,0,1000);
   TH1F* genJet1EtaR = new TH1F("genJet1EtaR","#eta of Leading Gen Jet",40,-4,4);
   TH1F* genJet1PhiR = new TH1F("genJet1PhiR","#phi of Leading Gen Jet",36,-3.6,3.6);


   //gen jet histograms
   TH1F* genJet2PtR = new TH1F("genJet2PtR","p_{T} of Leading Gen Jet",100,0,1000);
   TH1F* genJet2EtaR = new TH1F("genJet2EtaR","#eta of Leading Gen Jet",40,-4,4);
   TH1F* genJet2PhiR = new TH1F("genJet2PhiR","#phi of Leading Gen Jet",36,-3.6,3.6);
   
   //gen jet histograms
   TH1F* genJet1PtL = new TH1F("genJet1PtL","p_{T} of Leading Gen Jet",100,0,1000);
   TH1F* genJet1EtaL = new TH1F("genJet1EtaL","#eta of Leading Gen Jet",40,-4,4);
   TH1F* genJet1PhiL = new TH1F("genJet1PhiL","#phi of Leading Gen Jet",36,-3.6,3.6);
   
   
   //gen jet histograms
   TH1F* genJet2PtL = new TH1F("genJet2PtL","p_{T} of Leading Gen Jet",100,0,1000);
   TH1F* genJet2EtaL = new TH1F("genJet2EtaL","#eta of Leading Gen Jet",40,-4,4);
   TH1F* genJet2PhiL = new TH1F("genJet2PhiL","#phi of Leading Gen Jet",36,-3.6,3.6);


   TH1F* genJetHTL = new TH1F("genJetHTL","H_{T}",250,0,2500);
   TH1F* genJetHTR = new TH1F("genJetHTR","H_{T}",250,0,2500);

   //loop over gen jets
   for(int i=0;i<nL;i++){
     tl->GetEntry(i);
     
     float maxpt=0;
     double eta;
     double phi;
     float htl=0;
     for(unsigned int ijet=0;ijet<genJetPtsL->size();ijet++){
       if(genJetPtsL->at(ijet)>30) htl+=genJetPtsL->at(ijet);
       if(genJetPtsL->at(ijet)>maxpt){
	 maxpt = genJetPtsL->at(ijet);
	 eta = genJetEtasL->at(ijet);
	 phi = genJetPhisL->at(ijet);
       }
     }
     genJet1PtL->Fill(maxpt);
     genJet1EtaL->Fill(eta);
     genJet1PhiL->Fill(phi);
     genJetHTL->Fill(htl);
     float penpt=0;
     double eta2;
     double phi2;
     for(unsigned int ijet=0;ijet<genJetPtsL->size();ijet++){
       if(genJetPtsL->at(ijet)>penpt && genJetPtsL->at(ijet)!=maxpt){
	 penpt = genJetPtsL->at(ijet);
	 eta2 = genJetEtasL->at(ijet);
	 phi2 = genJetPhisL->at(ijet);
       }
     }
     
     genJet2PtL->Fill(penpt);
     genJet2EtaL->Fill(eta2);
     genJet2PhiL->Fill(phi2);
     
   }
   
   //loop over gen jets
   for(int i=0;i<nR;i++){
     tr->GetEntry(i);
     
     float maxpt=0;
     double eta;
     double phi;
     float htr=0;
     for(unsigned int ijet=0;ijet<genJetPtsR->size();ijet++){
       if(genJetPtsR->at(ijet)>30) htr+=genJetPtsR->at(ijet);
       if(genJetPtsR->at(ijet)>maxpt){
	 maxpt = genJetPtsR->at(ijet);
	 eta = genJetEtasR->at(ijet);
	 phi = genJetPhisR->at(ijet);
       }
     }
     genJet1PtR->Fill(maxpt);
     genJet1EtaR->Fill(eta);
     genJet1PhiR->Fill(phi);
     genJetHTR->Fill(htr);

     float penpt=0;
     double eta2;
     double phi2;
     for(unsigned int ijet=0;ijet<genJetPtsR->size();ijet++){
       if(genJetPtsR->at(ijet)>penpt && genJetPtsR->at(ijet)!=maxpt){
	 penpt = genJetPtsR->at(ijet);
	 eta2 = genJetEtasR->at(ijet);
	 phi2 = genJetPhisR->at(ijet);
       }
     }
   
    genJet2PtR->Fill(penpt);
    genJet2EtaR->Fill(eta2);
    genJet2PhiR->Fill(phi2);

   }


   printPlots(genJet1PtL,genJet1PtR,"1 TeV LH X53","1 TeV RH X53","Leading Gen Jet p_{T}","p_{T} GeV","GenJet_LeadingPt_pair.pdf",0.1);
   printPlots(genJet1EtaL,genJet1EtaR,"1 TeV LH X53","1 TeV RH X53","Leading Gen Jet #eta","#eta","GenJet_LeadingEta_pair.pdf");
   printPlots(genJet1PhiL,genJet1PhiR,"1 TeV LH X53","1 TeV RH X53","Leading Gen Jet #phi","#phi","GenJet_LeadingPhi_pair.pdf");

   printPlots(genJet2PtL,genJet2PtR,"1 TeV LH X53","1 TeV RH X53","Sub-Leading Gen Jet p_{T}","p_{T} GeV","GenJet_subLeadingPt_pair.pdf",0.1);
   printPlots(genJet2EtaL,genJet2EtaR,"1 TeV LH X53","1 TeV RH X53","Sub-Leading Gen Jet #eta","#eta","GenJet_subLeadingEta_pair.pdf");
   printPlots(genJet2PhiL,genJet2PhiR,"1 TeV LH X53","1 TeV RH X53","Sub-Leading Gen Jet #phi","#phi","GenJet_subLeadingPhi_pair.pdf");
   printPlots(genJetHTL,genJetHTR,"1 TeV LH X53","1 TeV RH X53","Gen H_{T}","H_{T} GeV","GenJet_HT_pair.pdf",0.1);


}

void printPlots(TH1F* hist1, TH1F* hist2, string label1, string label2, string Title, string xAxisLabel, string filename, float maxy){

  //set line style/color
  hist1->SetLineWidth(2);
  hist1->SetLineColor(kBlue);
  hist2->SetLineWidth(2);
  hist2->SetLineColor(kRed);

  //normalize
  hist1->Scale( 1. / hist1->Integral() );
  hist2->Scale( 1. / hist2->Integral() );

  hist1->GetXaxis()->SetTitle(xAxisLabel.c_str());
  hist1->GetYaxis()->SetRangeUser(0,maxy);
  hist1->GetYaxis()->SetTitle("a.u.");
  hist1->SetTitle(Title.c_str());

  TCanvas c1;
  
  hist1->Draw();
  hist2->Draw("same");

  //make legend
  TLegend leg(0.52,0.7,0.9,0.9,"Sample");

  leg.AddEntry(hist1,label1.c_str(),"l");
  leg.AddEntry(hist2,label2.c_str(),"l");

  leg.Draw("same");

  TLatex cmstex;
  cmstex.SetTextSize(0.03);
  cmstex.DrawLatexNDC(0.15,0.85,"CMS Preliminary - 13 TeV Simulation");

  c1.Print(filename.c_str());



}

