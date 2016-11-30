#!/usr/bin/python

import os

#make list of card files

allfiles = os.listdir('.')


def makeCfgs(ch):
    cardfiles = []
    for file in allfiles:
    #skip if not a card file, and if not a theta card file
#    if file.find("theta.root")==-1:
        if file.find("thetamuMiniIso.root")==-1:
            continue
        if file.find("Limits_M")==-1:
            continue
        if file.find("Ch_"+ch)==-1:
            continue

        cardfiles.append(file)
        
    for card in cardfiles:
    #open template file
        #print card,"theta_template_"+ch+".py"
        template = open("theta_template_"+ch+".py",'r')
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
        filename += (card.split("_thetamuMiniIso.root")[0]).split("Limits_")[1]
        filename += "_muMiniIso"
        exptxt = filename+"_expected.txt"
        obstxt = filename+"_observed.txt"
        htmlout = filename+"_html"
        jsonname=filename
        filename+=".py"
        #print filename
        outfile= open(filename,'w')
        for line in template:
            line = line.replace('ROOTFILE',card)
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

