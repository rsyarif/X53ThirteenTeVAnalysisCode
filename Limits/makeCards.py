#/usr/bin/python

import os

masses = [700,900,1000,1100,1300]
chiralities = ['RH','LH']

theta=True

for mass in masses:
    for chi in chiralities:
        for i in range(-1,0):
            for l1 in range(0,11):
                lep1=l1*10
                for l2 in range(0,11):
                    lep2=l2*10
                    for ht in range(0,11):
                        htcut=50*ht
                        if theta:
                            command="./makeLimitCards.o %i %s %i %i %i %i theta" % (mass,chi,i,lep1,lep2,htcut)
                            print command
#                            os.system(command)
                        else:
                            command="./makeLimitCards.o %i %s %i %i %i %i higgs" % (mass,chi,i,lep1,lep2,htcut)
                            os.system(command)
                        
