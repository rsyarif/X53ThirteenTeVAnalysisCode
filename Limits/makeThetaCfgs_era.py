#!/usr/bin/python

import glob

#make list of card files

allfiles = glob.glob('./*2016B-D.root')


def makeCfgs(ch):

    for card in allfiles:
    #open template file
        #print card,"theta_template_"+ch+".py"
        template = open("theta_template_combo_"+ch+".py",'r')
        mass = card.split("_M")[1].split("_")[0]
        if mass=="700":
            xsec='0.442'
        elif mass=='800':
            xsec='0.190'
        elif mass=='900':
            xsec='0.0877'
        elif mass=='1000':
            xsec='0.0427'
        elif mass=='1100':
            xsec='0.0217'
        elif mass=='1200':
            xsec='0.0114'
        elif mass=='1300':
            xsec='0.00618'
        elif mass=='1400':
            xsec='0.00342'
        elif mass=='1500':
            xsec='0.00193'
        else:
            xsec='0.00111'

        filename = "X53X53_"
        filename += (card.split("_2016B-D.root")[0]).split("Limits_")[1]
        card2016EH = card.replace('2016B-D','2016E-H')
        exptxt = filename+"_expected.txt"
        obstxt = filename+"_observed.txt"
        htmlout = filename+"_html"
        jsonname=filename
        filename+=".py"
        #print filename
        outfile= open(filename,'w')
        for line in template:
            line = line.replace('SSDLROOTFILE2016BD',card)
            line = line.replace('SSDLROOTFILE2016EH',card2016EH)
            line = line.replace('EXPTXTFILE',exptxt)
            line = line.replace('OBSTXTFILE',obstxt)
            line = line.replace('HTMLOUT',htmlout)
            line = line.replace('MASS',mass)
            line = line.replace('XSEC',xsec)
            line = line.replace('JSONNAME',jsonname)
            outfile.write(line)
        template.close()
        outfile.close()


chans = ['All','ee','emu','mumu']

for chan in chans:
    makeCfgs(chan)

