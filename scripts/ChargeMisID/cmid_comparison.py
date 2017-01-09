from ROOT import *

eras = ['2016B','2016C','2016D','2016E','2016F','2016G','2016H2','2016H3']
files=[]
hists=[]

gStyle.SetOptStat(0)

from setTDRStyle_cmid import *

def drawComparison(histname):
    c = TCanvas()
    leg = TLegend(0.1,0.6,0.5,0.9)
    for era in eras:
        f = TFile('ChargeMisID_Data_'+era+'_Electrons_MVATightRC_corrected.root')
        h = f.Get(histname)
        #fix high pt title
        if histname=='hhpt_final':
            h.SetTitle("Charge MisID Rate - Electrons with p_{T} > 200 GeV")
        #keep objects accessible
        files.append(f)
        hists.append(h)
        if era=='2016B':
            h.SetMarkerColor(kBlack)
            if histname=='h_pt_final':
                h.GetYaxis().SetRangeUser(0.0001,1)
            h.Draw("pe")
        elif era=='2016C':
            h.SetMarkerColor(kBlue)
            h.Draw('pe same')
        elif era=='2016D':
            h.SetMarkerColor(kRed)
            h.Draw('pe same')
        elif era=='2016E':
            h.SetMarkerColor(kGreen)
            h.Draw('pe same')
        elif era=='2016F':
            h.SetMarkerColor(kViolet)
            h.Draw('pe same')
        elif era=='2016G':
            h.SetMarkerColor(kOrange)
            h.Draw('pe same')
        elif era=='2016H2':
            h.SetMarkerColor(kCyan)
            h.Draw('pe same')
        elif era=='2016H3':
            h.SetMarkerColor(kGray)
            h.Draw('pe same')
        leg.AddEntry(h,era,'lp')

    leg.Draw('same')
    if histname=='h_num_lpt':
        c.Print('ChargeMisID_pT-0to100_comparison.pdf')
    elif histname=='hpt_final':
        c.Print('ChargeMisID_pT-100to200_comparison.pdf')
    elif histname=='hhpt_final':
        c.Print('ChargeMisID_pT-200toInf_comparison.pdf')
    elif histname=="h_pt_final":
        c.SetLogy()
        c.Print('ChargeMisID_vPT_comparison.pdf')

def drawAllCombined(histname):
    setTDRStyle()
    c = TCanvas()
    leg = TLegend(0.1,0.4,0.5,0.9)
    f = TFile('ChargeMisID_Data_All_Electrons_MVATightRC_corrected.root')
    h = f.Get(histname)
    h.SetMarkerStyle(20)
    h.SetTitle(';Electron |#eta|;Probability of charge misidentification')
    h.GetYaxis().SetTitleOffset(1.5);
    h.GetYaxis().SetLabelSize(0.03);
    h.GetXaxis().SetLabelSize(0.03);
    h.GetYaxis().SetNoExponent(kFALSE);
    if histname=='h_num_lpt':
        h.GetYaxis().SetRangeUser(0,0.012)
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
    lumitex = TLatex(3.570061,23.08044,"36.4 fb^{-1} (13 TeV)")
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
        c.Print('ChargeMisID_pT-0to100_final.pdf')
    elif histname=='hpt_final':
        c.Print('ChargeMisID_pT-100to200_final.pdf')
    elif histname=='hhpt_final':
        c.Print('ChargeMisID_pT-200toInf_final.pdf')
    elif histname=="h_pt_final":
        c.SetLogy()
        h.GetXaxis().SetTitle("p_{T}")
        c.Print('ChargeMisID_vPT_final.pdf')


drawComparison('h_num_lpt')
drawComparison('hpt_final')
drawComparison('hhpt_final')
drawComparison('h_pt_final')

drawAllCombined('h_num_lpt')
drawAllCombined('hpt_final')
drawAllCombined('hhpt_final')
drawAllCombined('h_pt_final')
