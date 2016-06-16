#/usr/bin/python

import os

masses = [700,800,900,1000,1100,1200,1300,1400,1500]
chiralities = ['RH','LH']

theta=True

for mass in masses:
    for chi in chiralities:
        for i in range(0,1):
            ht=50*i
            for j in range(0,2):
                command="./makeLimitRootFiles_Boosted.o %i %s %i %i" % (mass,chi,ht,j)
                print command
                os.system(command)
            
