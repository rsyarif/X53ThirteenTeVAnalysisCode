#/usr/bin/python

import os,datetime

datetime_now = datetime.datetime.now()
today = '%i_%i_%i'%(datetime_now.year,datetime_now.month,datetime_now.day)

os.system("make makeLimitRootFiles")

#Check where files are taken in Analyzer/plugins/Macros.cc and adjust name accordingly!!
outDir = today+'_LJMet94x_2lepTT_2017datasets_2018_11_18_rizki_hadds_Analyzer'

# masses = [1000,1100,1200,1300,1400,1500,1600,1700]#,1800]
# masses = [1800]
masses = [1000,1100,1200,1300,1400,1500,1600,1700,1800]
# masses = [800,1300,1400,1500,1600,1700]#,1800]
# chiralities = ['RH','LH']
chiralities = ['LH']
eras = ['2017B-F']
theta=True

#added by rizki to scan BRs --> order needs to be in sync with list in Macro.cc
BRs={}
BRs['BW']=[0.50,0.0,0.0,0.0,0.0,0.0,0.0,0.2,0.2,0.2,0.2,0.2,0.4,0.4,0.4,0.4,0.6,0.6,0.6,0.8,0.8,1.0,0.0]
BRs['TH']=[0.25,0.0,0.2,0.4,0.6,0.8,1.0,0.0,0.2,0.4,0.6,0.8,0.0,0.2,0.4,0.6,0.0,0.2,0.4,0.0,0.2,0.0,0.5]
BRs['TZ']=[0.25,1.0,0.8,0.6,0.4,0.2,0.0,0.8,0.6,0.4,0.2,0.0,0.6,0.4,0.2,0.0,0.4,0.2,0.0,0.2,0.0,0.0,0.5]
BRs['TW']=[0.50,0.0,0.0,0.0,0.0,0.0,0.0,0.2,0.2,0.2,0.2,0.2,0.4,0.4,0.4,0.4,0.6,0.6,0.6,0.8,0.8,1.0,0.0]
BRs['BH']=[0.25,0.0,0.2,0.4,0.6,0.8,1.0,0.0,0.2,0.4,0.6,0.8,0.0,0.2,0.4,0.6,0.0,0.2,0.4,0.0,0.2,0.0,0.5]
BRs['BZ']=[0.25,1.0,0.8,0.6,0.4,0.2,0.0,0.8,0.6,0.4,0.2,0.0,0.6,0.4,0.2,0.0,0.4,0.2,0.0,0.2,0.0,0.0,0.5]

BRdict = {}
BRdict['singlet'] = [0]
BRdict['tZ=100%'] = [1]
BRdict['bW=100%'] = [21]
BRdict['tZ=tH=50%'] = [22]
BRdict['tZtZ,tZtH'] = [1,22]
BRdict['tHtH'] = [6]

for BR in xrange(len(BRs['BW'])): #edited by rizki
#for BR in BRdict['tHtH'] : #edited by rizki
	print 'BR:',BR
	outDirBR=outDir
	outDirBR=outDir+'_bW'+str(BRs['BW'][BR]).replace('.','p')+'_tZ'+str(BRs['TZ'][BR]).replace('.','p')+'_tH'+str(BRs['TH'][BR]).replace('.','p')
	if('BB' in outDir): outDirBR=outDir+'_tW'+str(BRs['TW'][BR]).replace('.','p')+'_bZ'+str(BRs['BZ'][BR]).replace('.','p')+'_bH'+str(BRs['BH'][BR]).replace('.','p')
	os.system('mkdir -v '+outDirBR)

	for mass in masses:
		for chi in chiralities:
			for era in eras:
	# 			for i in range(0,4): #edited by rizki
	# 				ht=100*i
					ht=200
					if era=='2017B-F':
						lep2 = 5
						lumi = 41.557
					else:
						lep2 = 0
						lumi = 0
					command="./makeLimitRootFiles.o %i %s %i %i %.2f %s %i" % (mass,chi,ht,lep2,lumi,era,BR)
					print command
					os.system(command)

	os.system('mv -v *root '+outDirBR+'/')
