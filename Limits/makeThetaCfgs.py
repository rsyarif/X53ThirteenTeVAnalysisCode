#!/usr/bin/python

import os

#make list of card files

allfiles = os.listdir('.')
cardfiles = []

for file in allfiles:
    #skip if not a card file, and if not a theta card file
    if file.find("theta.txt")==-1:
        continue
    if file.find("card")==-1:
        continue

    cardfiles.append(file)

for card in cardfiles:
    #open template file
    template = open("theta_template.py",'r')
    filename = "X53X53_"
    filename += (card.split("_theta.txt")[0]).split("card_")[1]
    exptxt = filename+"_expected.txt"
    obstxt = filename+"_observed.txt"
    htmlout = filename+"_html"
    filename+=".py"
    outfile= open(filename,'w')
    for line in template:
        line = line.replace('CARDFILE',card)
        line = line.replace('EXPTXTFILE',exptxt)
        line = line.replace('OBSTXTFILE',obstxt)
        line = line.replace('HTMLOUT',htmlout)
        outfile.write(line)
    template.close()
    outfile.close()


