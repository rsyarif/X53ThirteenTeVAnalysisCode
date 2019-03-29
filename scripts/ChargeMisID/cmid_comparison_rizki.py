from ROOT import *

eras = ['2017B','2017C','2017D','2017E','2017F','All']
files=[]
hists=[]

gStyle.SetOptStat(0)

from setTDRStyle_cmid import *

def drawComparison(histname,elID):
    c = TCanvas()
    leg = TLegend(0.1,0.6,0.5,0.9)
    for era in eras:
        f = TFile('ChargeMisID_Data_'+era+'_Electrons_'+elID+'_corrected.root')
        h = f.Get(histname)
        #fix high pt title
        if histname=='hhpt_final':
            h.SetTitle("Charge MisID Rate - Electrons with p_{T} > 200 GeV")
        #keep objects accessible
        files.append(f)
        hists.append(h)
        if era=='2017B':
            h.SetMarkerColor(kBlack)
            if histname=='h_pt_final':
                h.GetYaxis().SetRangeUser(0.0001,1)
            h.Draw("pe")
        elif era=='2017C':
            h.SetMarkerColor(kBlue)
            h.Draw('pe same')
        elif era=='2017D':
            h.SetMarkerColor(kRed)
            h.Draw('pe same')
        elif era=='2017E':
            h.SetMarkerColor(kGreen)
            h.Draw('pe same')
        elif era=='2017F':
            h.SetMarkerColor(kViolet)
            h.Draw('pe same')
        leg.AddEntry(h,era,'lp')

    leg.Draw('same')
    if histname=='h_num_lpt':
        c.Print('ChargeMisID_pT-0to100_comparison_'+elID+'.pdf')
    elif histname=='hpt_final':
        c.Print('ChargeMisID_pT-100to200_comparison_'+elID+'.pdf')
    elif histname=='hhpt_final':
        c.Print('ChargeMisID_pT-200toInf_comparison_'+elID+'.pdf')
    elif histname=="h_pt_final":
        c.SetLogy()
        c.Print('ChargeMisID_vPT_comparison_'+elID+'.pdf')

def drawAllCombined(histname,elID):
    setTDRStyle()
    c = TCanvas()
    leg = TLegend(0.1,0.4,0.5,0.9)
    f = TFile('ChargeMisID_Data_All_Electrons_'+elID+'_corrected.root')
    print f
    h = f.Get(histname)
    print h
    h.SetMarkerStyle(20)
    h.SetTitle(';Electron |#eta|;Probability of charge misidentification')
    h.GetYaxis().SetTitleOffset(1.6);
    h.GetYaxis().SetTitleSize(0.04);
    h.GetYaxis().SetLabelSize(0.03);
    h.GetXaxis().SetLabelSize(0.03);
    h.GetYaxis().SetNoExponent(kFALSE);
    if histname=='h_num_lpt':
        h.GetYaxis().SetRangeUser(0,0.008)
    elif histname=='hpt_final':
        h.GetYaxis().SetRangeUser(0,0.09)
    elif histname=='hhpt_final':
        h.GetYaxis().SetRangeUser(0,0.2)
    elif histname=='h_pt_final':
        h.GetYaxis().SetRangeUser(0.0001,0.2)
    h.Draw('pe')

    #cms latex
    cmstex = TLatex(3.570061,23.08044,"CMS Preliminary")
    cmstex.SetNDC()
    cmstex.SetTextSizePixels(24)
    cmstex.SetY(0.918)
    cmstex.SetTextAlign(13)
    cmstex.SetTextFont(42)
    cmstex.SetX(0.354)
    cmstex.Draw()
    #lumi latex
    lumitex = TLatex(3.570061,23.08044,"41.6 fb^{-1} (13 TeV)")
    lumitex.SetNDC()
    lumitex.SetTextSizePixels(24)
    lumitex.SetY(0.87)
    lumitex.SetTextAlign(13)
    lumitex.SetTextFont(42)
    lumitex.SetX(0.354)
    lumitex.Draw()
    #print rate for table
    for i in range(1,h.GetNbinsX()+1):
        print "%.1f $<|\eta|<$ %.1f&  $%f \pm %f$" %(h.GetBinLowEdge(i),h.GetBinLowEdge(i+1), h.GetBinContent(i), h.GetBinError(i))

    if histname=='h_num_lpt':
        c.Print('ChargeMisID_pT-0to100_final_'+elID+'.pdf')
    elif histname=='hpt_final':
        c.Print('ChargeMisID_pT-100to200_final_'+elID+'.pdf')
    elif histname=='hhpt_final':
        c.Print('ChargeMisID_pT-200toInf_final_'+elID+'.pdf')
    elif histname=="h_pt_final":
        c.SetLogy()
        h.GetXaxis().SetTitle("p_{T}")
        c.Print('ChargeMisID_vPT_final_'+elID+'.pdf')


# drawComparison('h_num_lpt','MVATightRC')
# drawComparison('hpt_final','MVATightRC')
# drawComparison('hhpt_final','MVATightRC')
# drawComparison('h_pt_final','MVATightRC')
# drawComparison('h_num_lpt','MVA80XTightRC')
# drawComparison('hpt_final','MVA80XTightRC')
# drawComparison('hhpt_final','MVA80XTightRC')
# drawComparison('h_pt_final','MVA80XTightRC')
# drawComparison('h_num_lpt','MVAJulieTightRC')
# drawComparison('hpt_final','MVAJulieTightRC')
# drawComparison('hhpt_final','MVAJulieTightRC')
# drawComparison('h_pt_final','MVAJulieTightRC')
# drawComparison('h_num_lpt','MVAJulieNewTightRC')
# drawComparison('hpt_final','MVAJulieNewTightRC')
# drawComparison('hhpt_final','MVAJulieNewTightRC')
# drawComparison('h_pt_final','MVAJulieNewTightRC')
# drawComparison('h_num_lpt','MVA2016TightRC')
# drawComparison('hpt_final','MVA2016TightRC')
# drawComparison('hhpt_final','MVA2016TightRC')
# drawComparison('h_pt_final','MVA2016TightRC')
# 
# drawAllCombined('h_num_lpt','MVATightRC')
# drawAllCombined('hpt_final','MVATightRC')
# drawAllCombined('hhpt_final','MVATightRC')
# drawAllCombined('h_pt_final','MVATightRC')
# 
# 
# drawAllCombined('h_num_lpt','MVA80XTightRC')
# drawAllCombined('hpt_final','MVA80XTightRC')
# drawAllCombined('hhpt_final','MVA80XTightRC')
# drawAllCombined('h_pt_final','MVA80XTightRC')
# 
# 
# drawAllCombined('h_num_lpt','MVAJulieTightRC')
# drawAllCombined('hpt_final','MVAJulieTightRC')
# drawAllCombined('hhpt_final','MVAJulieTightRC')
# drawAllCombined('h_pt_final','MVAJulieTightRC')
# 
# 
# drawAllCombined('h_num_lpt','MVAJulieNewTightRC')
# drawAllCombined('hpt_final','MVAJulieNewTightRC')
# drawAllCombined('hhpt_final','MVAJulieNewTightRC')
# drawAllCombined('h_pt_final','MVAJulieNewTightRC')
# 
# 
# 
# drawAllCombined('h_num_lpt','MVA2016TightRC')
# drawAllCombined('hpt_final','MVA2016TightRC')
# drawAllCombined('hhpt_final','MVA2016TightRC')
# drawAllCombined('h_pt_final','MVA2016TightRC')

drawAllCombined('h_num_lpt','MVA2017TightIsoRC')
drawAllCombined('hpt_final','MVA2017TightIsoRC')
drawAllCombined('hhpt_final','MVA2017TightIsoRC')
drawAllCombined('h_pt_final','MVA2017TightIsoRC')
