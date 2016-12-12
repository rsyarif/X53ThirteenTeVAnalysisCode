from ROOT import *

eras = ['2016B','2016C','2016D','2016E','2016F','2016G','2016H2','2016H3']

def drawComparison(histname):
    c = TCanvas()
    leg = TLegend(0.1,0.4,0.5,0.9)
    for era in eras:
        f = TFile('ChargeMisID_Data_'+era+'_Electrons_MVATightRC_corrected.root')
        h = f.Get(histname)
        if era=='2016B':
            h.SetLineColor(kBlack)
            h.Draw("hist")
        elif era=='2016C':
            h.SetLineColor(kBlue)
            h.Draw('hist same')
        elif era=='2016D':
            h.SetLineColor(kRed)
            h.Draw('hist same')
        elif era=='2016E':
            h.SetLineColor(kGreen)
            h.Draw('hist same')
        elif era=='2016F':
            h.SetLineColor(kViolet)
            h.Draw('hist same')
        elif era=='2016G':
            h.SetLineColor(kOrange)
            h.Draw('hist same')
        elif era=='2016H2':
            h.SetLineColor(kCyan)
            h.Draw('hist same')
        elif era=='2016H3':
            h.SetLineColor(kGray)
            h.Draw('hist same')
        leg.AddEntry(h,era,'l')

    leg.Draw('same')
    if histname=='h_num_lpt':
        c.Print('ChargeMisID_pT-0to100_comparison.pdf')
    elif histname=='hpt_final':
        c.Print('ChargeMisID_pT-100to200_comparison.pdf')
    elif histname=='hhpt_final':
        c.Print('ChargeMisID_pT-200toInf_comparison.pdf')


drawComparison('h_num_lpt')
drawComparison('hpt_final')
drawComparison('hhpt_final')
