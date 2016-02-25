#include <memory>
#include <vector>
#include <sstream>
#include <string>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/JetReco/interface/Jet.h"
#include "AnalysisDataFormats/TopObjects/interface/CATopJetTagInfo.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/JetReco/interface/BasicJet.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/JetCollection.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "PhysicsTools/CandUtils/interface/AddFourMomenta.h"
#include "DataFormats/Candidate/interface/CandMatchMap.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include <Math/VectorUtil.h>
#include "TH1F.h"
#include <TH2.h>
#include <TTree.h>



/* this module should store quantities for performing trigger studies. the idea here
   is to get all needed information and use a custom hltTreeReader later to analyze.
   the first thing of interest are electron kinematic variables for dielectron trigger*/


using namespace std;

//plugin declaration
class hltTreeMaker : public edm::EDProducer {
  
public:

  hltTreeMaker(const edm::ParameterSet& Pset);
  virtual ~hltTreeMaker(){}

  
private:
  virtual void BeginJob();
  virtual void produce(edm::Event & event, const edm::EventSetup & EventSetup);
  virtual void EndJob(){};

  //ttree
  TTree* tree;

  //needed electron inputs
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> eleOnlineToken;
  edm::InputTag eleOnlineTag;

  edm::EDGetTokenT<std::vector<pat::Electron> > eleRecoToken;
  edm::InputTag eleRecoTag;

  //kinematic quantities -- will only be saving electrons that pass offline ID and also trigger quality cuts so really just need these
  std::vector<double> patElePt;
  std::vector<double> hltElePt;
  std::vector<double> patEleEt;
  std::vector<double> hltEleEt;
  std::vector<double> patEleEta;
  std::vector<double> hltEleEta;
  std::vector<double> patElePhi;
  std::vector<double> hltElePhi;

  

};

hltTreeMaker(const edm::ParameterSet& iConfig):
  eleOnlineTag = iConfig.getParameter<edm::InputTag>("eleOnlineCollection"),
  eleOnlineToken = consumes<trigger::TriggerFilterObjectWithRefs>(eleOnlineTag),
  eleOfflineTag = iConfig.getParameter<edm::InputTag>("eleOfflineCollection"),
  eleOfflineToken = consumes<std::vector<pat::Electron> >(eleOfflineTag)

{

  //set branch aliases
  edm::Service<TFileService> fs;
  tree = fs->make<TTree>("electronVariables", "electronVariables");

  tree->Branch("patElePt",&patElePt);
  tree->Branch("hltElePt",&hltElePt);
  tree->Branch("patEleEt",&patEleEt);
  tree->Branch("hltEleEt",&hltEleEt);
  tree->Branch("patEleEta",&patEleEta);
  tree->Branch("hltEleEta",&hltEleEta);
  tree->Branch("patElePhi",&patElePhi);
  tree->Branch("hltElePhi",&hltElePhi);


}
//use input tags to fill tokens

void hltTreeMaker::BeginJob(){
}


void hltTreeMaker::produce(edm::Event& iEvent,const edm::EventSetup& iEventSetup){

  //get collections from tokens
  edm::Handle<trigger::TriggerfilterObjectWithRefs> hltElectrons;
  iEvent.getByToken(eleOnlineToken,hltElectrons);
  edm::Handle<std::vector<pat::Electron> > patElectrons;
  iEvent.getByToken(eleOfflineToken,patElectrons);
  

}


//define this as a plug-in
DEFINE_FWK_MODULE(hltTreeMaker);
