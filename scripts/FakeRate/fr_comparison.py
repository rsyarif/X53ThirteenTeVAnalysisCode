from ROOT import *

eras = ['2016B','2016C','2016D','2016E','2016F','2016G','2016H2','2016H3']
files=[]
hists=[]

gStyle.SetOptStat(0)

#from setTDRStyle_cmid import *

def drawComparison(histname):
    c = TCanvas()
    leg = TLegend(0.5,0.1,0.9,0.6)
    for era in eras:
        f = TFile('FakeRate_Graph_'+era+'.root')
        h = f.Get(histname)
        #keep objects accessible
        files.append(f)
        hists.append(h)
        if era=='2016B':
            h.SetMarkerColor(kBlack)
            h.Draw("ape")
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

    #print out values:



    leg.Draw('same')
    if histname=='MuonFakeRate':
        c.Print('FakeRate_Muons_comparison.pdf')
    elif histname=='ElectronFakeRate':
        c.Print('FakeRate_Electrons_comparison.pdf')

def drawAllCombined(histname):
#    setTDRStyle()
    c = TCanvas()
    leg = TLegend(0.1,0.4,0.5,0.9)
    f = TFile('FakeRate_Graph_All.root')
    h = f.Get(histname)
    h.SetMarkerStyle(20)
    h.SetTitle(';I_{mini} Requirement;Fake rate')
    h.GetYaxis().SetTitleOffset(1.5);
    h.GetYaxis().SetLabelSize(0.03);
    h.GetXaxis().SetLabelSize(0.03);
    h.GetYaxis().SetNoExponent(kFALSE);
    h.Draw('ape')

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
    lumitex.SetY(0.95)
    lumitex.SetTextAlign(13)
    lumitex.SetTextFont(42)
    lumitex.SetX(0.8)
    lumitex.Draw()

    if histname=='MuonFakeRate':
        c.Print('FakeRate_Muons_All.pdf')
    elif histname=='ElectronFakeRate':
        c.Print('FakeRate_Electrons_All.pdf')

    for i in range(0,h.GetN()):
        miniIso = 0.01*i
        print "Fake Rate for miniIso cut %.2f : %.3f" %(miniIso,h.GetY()[i])


def drawIDComparison():
    c = TCanvas()
    leg = TLegend(0.5,0.1,0.9,0.4)
    f1 = TFile('FakeRate_Graph_All_MVATightRC.root')
    h1 = f1.Get('ElectronFakeRate')
    f2 = TFile('FakeRate_Graph_All_MVA80XTightRC.root')
    h2 = f2.Get('ElectronFakeRate')
    f3 = TFile('FakeRate_Graph_All_MVA2016TightRC.root')
    h3 = f3.Get('ElectronFakeRate')
    
    h1.SetLineColor(kRed)
    h2.SetLineColor(kBlue)
    h3.SetLineColor(kGreen)

    h1.SetMarkerColor(kRed)
    h2.SetMarkerColor(kBlue)
    h3.SetMarkerColor(kGreen)

    h1.Draw('apl')
    h2.Draw('pl same')
    h3.Draw('pl same')
    leg.AddEntry(h1,'74X MVA','lp')
    leg.AddEntry(h2,'80X MVA Nominal WP','lp')
    leg.AddEntry(h3,'80X MVA Custom WP','lp')
    leg.Draw('same')
    c.Print('Electron_FakeRate_IDComparison.pdf')

def drawFakeRateVEtaComparison():    
    c = TCanvas()
    leg = TLegend(0.3,0.6,0.7,0.9)
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    f1 = TFile('FakeRate_Graph_All_MVATightRC.root')
    h1 = f1.Get('ElectronEtaFakeRate')
    f2 = TFile('FakeRate_Graph_All_MVA80XTightRC.root')
    h2 = f2.Get('ElectronEtaFakeRate')
    f3 = TFile('FakeRate_Graph_All_MVA2016TightRC.root')
    h3 = f3.Get('ElectronEtaFakeRate')
#    f4 = TFile('FakeRate_Graph_All_MVAJulieNewTightRC.root')
#    h4 = f4.Get('ElectronEtaFakeRate')
    
    h1.SetLineColor(kRed)
    h2.SetLineColor(kBlue)
    h3.SetLineColor(kBlack)
#    h4.SetLineColor(kBlack)

    h1.SetMarkerColor(kRed)
    h2.SetMarkerColor(kBlue)
    h3.SetMarkerColor(kBlack)
#    h4.SetMarkerColor(kBlack)
    #remove points fromEE-EB overlap
    h3.RemovePoint(8)
    h3.RemovePoint(1)

    h3.Draw('ap')
    h3.GetYaxis().SetRangeUser(0,0.5)
    h3.SetTitle("Electron Fake Rate vs. #eta;#eta;Fake Rate")
    h3.GetYaxis().SetTitleOffset(1.25)
    #h2.Draw('pl same')
    #h3.Draw('pl same')
#    h4.Draw('pl same')
    leg.AddEntry(h1,'74X MVA','lp')
    leg.AddEntry(h2,'80X MVA Nominal WP','lp')
    leg.AddEntry(h3,'80X MVA Custom WP','lp')
#    leg.AddEntry(h4,'80X MVA Julie New WP','lp')
    #leg.Draw('same')

    #Draw CMS tex
    latex2 = TLatex()
    latex2.SetNDC()
    latex2.SetTextSize(0.05)
    latex2.SetTextAlign(11) # align right
    latex2.DrawLatex(0.58, 0.93, "CMS Preliminary")


    c.Print('Electron_FakeRate_vEta_Twiki.pdf')

    for i in range(0,h3.GetN()):
        print "electron fake rate for eta %.1f is: %.3f" %(h3.GetX()[i],h3.GetY()[i])


def drawMuonFakeRateVEta():
    c = TCanvas()
    leg = TLegend(0.5,0.1,0.9,0.5)
    f1 = TFile('FakeRate_Graph_All_MVA2016TightRC.root')
    h1 = f1.Get('MuonEtaFakeRate')
    h1.SetLineColor(kBlack)
    h1.SetMarkerColor(kBlack)
    h1.Draw("ap")
    h1.GetYaxis().SetRangeUser(0,0.5)    
    h1.SetTitle("Muon Fake Rate vs. #eta;#eta;Fake Rate")
    h1.GetYaxis().SetTitleOffset(1.25)
    #Draw CMS tex
    latex2 = TLatex()
    latex2.SetNDC()
    latex2.SetTextSize(0.05)
    latex2.SetTextAlign(11) # align right
    latex2.DrawLatex(0.58, 0.93, "CMS Preliminary")

    c.Print("Muon_FakeRate_vEta_Twiki.pdf")

    for i in range(0,h1.GetN()):
        print "muon fake rate for eta %.1f is: %.3f" %(h1.GetX()[i],h1.GetY()[i])


#drawComparison('MuonFakeRate')
#drawComparison('ElectronFakeRate')
#drawAllCombined('MuonFakeRate')
#drawAllCombined('ElectronFakeRate')

drawIDComparison()
drawFakeRateVEtaComparison()
drawMuonFakeRateVEta()
