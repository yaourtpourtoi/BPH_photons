#ifndef _JPsiphi_h
#define _JPsiphi_h

// system include files
#include <memory>

// user include files

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/Handle.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "RecoVertex/KinematicFit/interface/KinematicParticleVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleFitter.h"
#include "RecoVertex/KinematicFit/interface/MassKinematicConstraint.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/TransientTrackKinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticleFactoryFromTransientTrack.h"
#include "RecoVertex/AdaptiveVertexFit/interface/AdaptiveVertexFitter.h"


#include "TrackingTools/TransientTrack/interface/TransientTrackFromFTSFactory.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/PatternTools/interface/ClosestApproachInRPhi.h"

#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
#include "DataFormats/V0Candidate/interface/V0Candidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"

#include "DataFormats/PatCandidates/interface/PackedCandidate.h" // muy importante para MiniAOD


#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"

#include "RecoVertex/VertexPrimitives/interface/BasicSingleVertexState.h"
#include "RecoVertex/VertexPrimitives/interface/VertexState.h"

#include "TFile.h"
#include "TTree.h"


//
// class decleration
//

class JPsiphi : public edm::EDAnalyzer {
public:
  explicit JPsiphi(const edm::ParameterSet&);
  ~JPsiphi();
  void fillPsi(const reco::Candidate& genpsi);
  void fillV0(const reco::Candidate& genv0);
  int const getMuCat(reco::Muon const& muon) const;
  bool IsTheSame(const pat::GenericParticle& tk, const pat::Muon& mu);


private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  void printout(const RefCountedKinematicVertex& myVertex) const;
  void printout(const RefCountedKinematicParticle& myParticle) const;
  void printout(const RefCountedKinematicTree& myTree) const;

    // ----------member data ---------------------------
  edm::EDGetTokenT<edm::View<pat::Muon>> dimuon_token;
  edm::EDGetTokenT<edm::View<pat::PackedCandidate>> trackCollection_token;
  edm::EDGetTokenT<reco::VertexCollection> primaryVertices_token;
  // edm::EDGetTokenT<reco::BeamSpot> BSLabel_;
  edm::EDGetTokenT<edm::TriggerResults> triggerResults_token;
  edm::EDGetTokenT<edm::View<pat::CompositeCandidate>> conv_photons_token;


  // bool OnlyBest_;
  bool isMC_;
  // bool OnlyGen_;
  // bool doMC_;
  // std::string genParticles_;





  TTree*      tree_;

  // *************************************

  int  run, event;
  int  lumiblock;

  unsigned int             nB;
  unsigned int             nMu;
  unsigned int             nVtx;

  // *************************************

  std::vector<float>       *mumC2;
  std::vector<int>         *mumNHits, *mumNPHits;
  std::vector<float>       *mupC2;
  std::vector<int>         *mupNHits, *mupNPHits;
  std::vector<float>       *mumdxy, *mupdxy, *mumdz, *mupdz;

  std::vector<bool>        *mu1soft, *mu2soft, *mu1tight, *mu2tight;
  std::vector<bool>        *mu1PF, *mu2PF, *mu1loose, *mu2loose;
  std::vector<float>       *mu1_mvaValue, *mu2_mvaValue;

  std::vector<int>         *tri_Dim25, *tri_JpsiTk, *tri_JpsiTkTk;


  // *************************************

  std::vector<float>       *photon_mass, *photon_px, *photon_py, *photon_pz;
  std::vector<int>         *photon_flags;

  // *************************************

  std::vector<float>       *photon_pt1, *photon_px1, *photon_py1, *photon_pz1;
  std::vector<float>       *photon_pt2, *photon_px2, *photon_py2, *photon_pz2;

  std::vector<float>       *photon_px1_track, *photon_py1_track, *photon_pz1_track;
  std::vector<float>       *photon_px2_track, *photon_py2_track, *photon_pz2_track;

  // std::vector<float>       *e1dxy, *e2dxy, *e1dz, *e2dz;
  // std::vector<float>       *e1dxy_e, *e2dxy_e, *e1dz_e, *e2dz_e;
  std::vector<int>         *photon_charge1, *photon_charge2;

  std::vector<float>       *photon1_track_normchi2;
  std::vector<int>         *photon1_Hits,  *photon1_PHits;
  std::vector<int>         *photon1_NTrackerLayers,  *photon1_NPixelLayers;

  std::vector<float>       *photon2_track_normchi2;
  std::vector<int>         *photon2_Hits,  *photon2_PHits;
  std::vector<int>         *photon2_NTrackerLayers,  *photon2_NPixelLayers;

  // *************************************

  std::vector<float>       *B_mass, *B_px, *B_py, *B_pz;

  // *************************************

  std::vector<float>       *B_J_mass, *B_J_px, *B_J_py, *B_J_pz;
  std::vector<float>       *B_J_pt1, *B_J_px1, *B_J_py1, *B_J_pz1;
  std::vector<float>       *B_J_pt2, *B_J_px2, *B_J_py2, *B_J_pz2;
  std::vector<int>         *B_J_charge1, *B_J_charge2;

  // *************************************

  std::vector<float>       *photon_chi2, *J_chi2, *B_chi2;
  std::vector<float>       *B_Prob, *J_Prob, *photon_Prob;

  // ********************************** ************************************************************************

  std::vector<float>       *bDecayVtxX, *bDecayVtxY, *bDecayVtxZ;
  std::vector<double>      *bDecayVtxXE, *bDecayVtxYE, *bDecayVtxZE;
  std::vector<double>      *bDecayVtxXYE, *bDecayVtxXZE, *bDecayVtxYZE;

  std::vector<float>       *psiDecayVtxX, *psiDecayVtxY, *psiDecayVtxZ;
  std::vector<double>      *psiDecayVtxXE, *psiDecayVtxYE, *psiDecayVtxZE;
  std::vector<double>      *psiDecayVtxXYE, *psiDecayVtxXZE, *psiDecayVtxYZE;

  std::vector<float>       *PhotonDecayVtxX, *PhotonDecayVtxY, *PhotonDecayVtxZ;
  std::vector<float>       *PhotonDecayVtxXE, *PhotonDecayVtxYE, *PhotonDecayVtxZE;
  std::vector<float>       *PhotonDecayVtxXYE, *PhotonDecayVtxXZE, *PhotonDecayVtxYZE;

  std::vector<float>       *PV_bestBang_RF_X   , *PV_bestBang_RF_Y , *PV_bestBang_RF_Z;
  std::vector<float>       *PV_bestBang_RF_XE  , *PV_bestBang_RF_YE, *PV_bestBang_RF_ZE;
  std::vector<float>       *PV_bestBang_RF_XYE , *PV_bestBang_RF_XZE , *PV_bestBang_RF_YZE;
  std::vector<float>       *PV_bestBang_RF_CL;



///////////////////////////////

  std::vector<float>       *B_phi_mass;
  std::vector<float>       *B_phi_px1, *B_phi_py1, *B_phi_pz1;
  std::vector<float>       *B_phi_px2, *B_phi_py2, *B_phi_pz2;

  std::vector<float>       *B_phi_px1_track, *B_phi_py1_track, *B_phi_pz1_track;
  std::vector<float>       *B_phi_px2_track, *B_phi_py2_track, *B_phi_pz2_track;

  std::vector<int>         *B_phi_charge1, *B_phi_charge2;
  std::vector<float>       *k1dxy, *k2dxy, *k1dz, *k2dz;
  std::vector<float>       *k1dxy_e, *k2dxy_e, *k1dz_e, *k2dz_e;
  std::vector<float>       *k1InnerHits, *k2InnerHits;

  float                    priVtxX, priVtxY, priVtxZ, priVtxXE, priVtxYE, priVtxZE, priVtxCL;
  float                    priVtxXYE, priVtxXZE, priVtxYZE;

  // ********************************** ************************************************************************


};
#endif
