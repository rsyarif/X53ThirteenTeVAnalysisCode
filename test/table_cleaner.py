#!/usr/env/python

infile = open('table_miniIsoTight_ht1200.txt','r')
outfile = open('table_miniIsoTight_cleaned.tex','w')

for line in infile:
    line = line.replace('Sample & SSDL &  (DilepMass>20)  & EE-ZVeto &  Lep1Pt > 40 &  nConst >= 5 &  cleanAK4HT > 1200','Sample & Associated ZVeto &  (DilepMass$>$20)  & EE-ZVeto &  Lep1Pt$>$40 &  nConst $>=$ 5 & \\HTl$>$1200')
    line = line.replace('WpWp','W+W+')
    line = line.replace('_X53X53_','\\xft\\xft ')
    line = line.replace('\\begin{tabular}{|cccc|c|c|}','\\begin{tabular}{|c|cccc|c|c|}\\hline\\hline')
    outfile.write(line)

infile.close()
outfile.close()
