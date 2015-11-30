#/usr/bin/python

import os

masses = [700,800,900,1000,1100,1200,1300,1400,1500]
chiralities = ['RH','LH']

theta=True

for mass in masses:
    for chi in chiralities:
        for i in range(-1,3):
            for nc in range(5,6):
                for l2 in range(0,1):
                    lep2=l2*10
                    for l1 in range(l2+1,2):
                        lep1=l1*10
                        for ht in range(0,3):
                            htcut=100*ht
                            if theta:
                                command="./makeLimitCards.o %i %s %i %i %i %i %i theta" % (mass,chi,i,lep1,lep2,htcut,nc)
                                print command
                                os.system(command)
                            else:
                                command="./makeLimitCards.o %i %s %i %i %i %i %i higgs" % (mass,chi,i,lep1,lep2,htcut,nc)
                                os.system(command)
                                
