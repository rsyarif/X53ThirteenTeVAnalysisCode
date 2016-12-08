void EGammaTnPPlotDumper(){

  TFile* fdata = new TFile("efficiency-data-passingMVATight-MVATight_Data.root");

  for( int i =0; i< 8; i++){
    for( int j =0; j<7; j++){
      std::string canname = Form("GsfElectronToEleID/passingMVATight/probe_Ele_eta_bin%i__probe_Ele_pt_bin%i__pdfSignalPlusBackground/fit_canvas",i,j);
      TCanvas* c = (TCanvas*) fdata->Get(canname.c_str());
      std::string pngname = Form("FitResults_Data_etabin%i_ptbin%i.png",i,j);
      c->Print(pngname.c_str());
    }
  }

  TFile * fmc = new TFile("efficiency-mc-passingMVATight-MVATight_MC.root");

  for( int i =0; i< 8; i++){
    for( int j =0; j<7; j++){
      std::string canname = Form("GsfElectronToEleID/MCtruth_passingMVATight/probe_Ele_eta_bin%i__probe_Ele_pt_bin%i__pdfSignalPlusBackground/fit_canvas",i,j);
      TCanvas* c = (TCanvas*) fmc->Get(canname.c_str());
      std::string pngname = Form("FitResults_MC_etabin%i_ptbin%i.png",i,j);
      c->Print(pngname.c_str());
    }
  }
  
}
