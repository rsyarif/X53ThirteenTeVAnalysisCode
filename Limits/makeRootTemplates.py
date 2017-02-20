#/usr/bin/python

import os


masses = [700,800,900,1000,1100,1200,1300,1400,1500]
chiralities = ['RH','LH']
eras = ['2016B-D','2016E-H']
#eras = ['2016E-H']
theta=True

for mass in masses:
    for chi in chiralities:
        for era in eras:
            for i in range(2,6):
                ht=100*i
                if era=='2016B-D':
                    lep2 = 5
                    lumi = 12.9
                else:
                    lep2 = 0
                    lumi = 23.9
                command="./makeThetaTemplates.o %i %s %i %i %.2f %s" % (mass,chi,ht,lep2,lumi,era)            
                print command
                os.system(command)
            
