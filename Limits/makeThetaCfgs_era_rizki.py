#!/usr/bin/python

import sys
sys.path.insert(0, '/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/X53ThirteenTeVAnalysisCode/scripts/Systematics/MC-Theory')
from unc_pdf_TT_bW0p5tZ0p25tH0p25 import *

import glob

#make list of card files

print pdfUp['TTM800']

# 
# 
# 
# def makeCfgs(ch):
#     allfiles = glob.glob('./*'+ch+'*2016B-D.root')
#     for card in allfiles:
#     #open template file
#         #print card,"theta_template_"+ch+".py"
#         template = open("theta_template_combo_"+ch+".py",'r')
#         mass = card.split("_M")[1].split("_")[0]
#         chi = card.split('_')[2]
#         if mass=="700":
#             if chi=='LH':
#                 sigpdf='1.036'
#             else:
#                 sigpdf='1.033'
#             xsec='0.442'
#         elif mass=='800':
#             if chi=='LH':
#                 sigpdf='1.031'
#             else:
#                 sigpdf='1.025'
#             xsec='0.190'
#         elif mass=='900':
#             if chi=='LH':
#                 sigpdf='1.025'
#             else:
#                 sigpdf='1.022'
#             xsec='0.0877'
#         elif mass=='1000':
#             if chi=='LH':
#                 sigpdf='1.022'
#             else:
#                 sigpdf='1.019'
#             xsec='0.0427'
#         elif mass=='1100':
#             if chi=='LH':
#                 sigpdf='1.018'
#             else:
#                 sigpdf='1.021'
#             xsec='0.0217'
#         elif mass=='1200':
#             if chi=='LH':
#                 sigpdf='1.018'
#             else:
#                 sigpdf='1.023'
#             xsec='0.0114'
#         elif mass=='1300':
#             if chi=='LH':
#                 sigpdf='1.020'
#             else:
#                 sigpdf='1.017'
#             xsec='0.00618'
#         elif mass=='1400':
#             if chi=='LH':
#                 sigpdf='1.015'
#             else:
#                 sigpdf='1.019'
#             xsec='0.00342'
#         elif mass=='1500':
#             if chi=='LH':
#                 sigpdf='1.021'
#             else:
#                 sigpdf='1.018'
#             xsec='0.00193'
#         else:
#             xsec='0.00111'
#             if chi=='LH':
#                 sigpdf='1.14'
#             else:
#                 sigpdf='1.14'
# 
#         filename = "X53X53_"
#         filename += (card.split("_2016B-D.root")[0]).split("Limits_")[1]
#         card2016EH = card.replace('2016B-D','2016E-H')
#         card2016EH = card2016EH.replace('SL35','SL30')
#         exptxt = filename+"_expected.txt"
#         obstxt = filename+"_observed.txt"
#         htmlout = filename+"_html"
#         jsonname=filename
#         postfitfile = filename+'_postfit'
#         histofile = filename+'_nuisanceHistos'
#         filename+=".py"
#         #print filename
#         outfile= open(filename,'w')
#         for line in template:
#             line = line.replace('SSDLROOTFILE2016BD',card)
#             line = line.replace('SSDLROOTFILE2016EH',card2016EH)
#             line = line.replace('EXPTXTFILE',exptxt)
#             line = line.replace('OBSTXTFILE',obstxt)
#             line = line.replace('HTMLOUT',htmlout)
#             line = line.replace('MASS',mass)
#             line = line.replace('XSEC',xsec)
#             line = line.replace('JSONNAME',jsonname)
#             line = line.replace('POSTFITFILE',postfitfile)
#             line = line.replace('NUISANCEHISTOS',histofile)
#             line = line.replace('SIGPDF',sigpdf)
#             outfile.write(line)
#         template.close()
#         outfile.close()
# 
# 
# chans = ['All','ee','emu','mumu']
# 
# for chan in chans:
#     makeCfgs(chan)

