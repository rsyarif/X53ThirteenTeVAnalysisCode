#/usr/bin/python

import os

outDir = 'Sep8_2017/'

masses = [800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800]
# chiralities = ['RH','LH']
chiralities = ['LH']
eras = ['2016B-D','2016E-H']
#eras = ['2016E-H']
theta=True

for mass in masses:
	for chi in chiralities:
		for era in eras:
			for i in range(0,5): #edited by rizki
				ht=100*i
				if era=='2016B-D':
					lep2 = 5
					lumi = 17.68
				else:
					lep2 = 0
					lumi = 18.19
				command="./makeLimitRootFiles.o %i %s %i %i %.2f %s" % (mass,chi,ht,lep2,lumi,era)
				print command
				os.system(command)


os.system('mkdir -v '+outDir)
os.system('mv -v *root '+outDir)