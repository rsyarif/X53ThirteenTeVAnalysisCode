#/usr/bin/python

import os

masses = [700,800,900,1000,1100,1200,1300,1400,1500]
chiralities = ['RH','LH']

theta=True

for mass in masses:
    for chi in chiralities:
        for i in range(0,6):
            ht=100*i

            command="./makeLimitRootFiles.o %i %s %i" % (mass,chi,ht)
            print command
            os.system(command)
            
