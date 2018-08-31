#/usr/bin/python

import os

os.system("make makeLimitRootFiles")

# outDir = 'Sep8_2017/'
# outDir = 'Oct6_2017/' #nConst4
# outDir = 'Oct9_2017_HT1200_nConst5/'

# outDir = 'Oct10_2017_HT1200_nConst4_no2LepRestriction' #BR0
# outDir = 'Oct10_2017_HT1200_nConst4_BB' #no2LepREstriction BR0

# outDir = 'Oct10_2017_HT1200_nConst5' #no2LepRestriction' #BR0
# outDir = 'Oct10_2017_HT1200_nConst5_BB' #no2LepREstriction BR0

# outDir = 'Oct11_2017_HT1200_nConst4' #BR0

# outDir = 'Oct19_2017_HT1200_nConst4_0NonSSLeps'
outDir = 'Oct19_2017_HT1200_nConst4_0NonSSLeps_BB'
# outDir = 'Oct20_2017_HT1200_nConst4_0NonSSLeps_1800'
# outDir = 'Oct20_2017_HT1200_nConst4_0NonSSLeps_1800_BB'

masses = [800,900,1000,1100,1200,1300,1400,1500,1600,1700]#,1800]
# masses = [1800]
# masses = [800,1300,1400,1500,1600,1700]#,1800]
# chiralities = ['RH','LH']
chiralities = ['LH']
eras = ['2016B-D','2016E-H']
#eras = ['2016E-H']
theta=True

#added by rizki to scan BRs --> order needs to be in sync with list in Macro.cc
BRs={}
BRs['BW']=[0.50,0.0,0.0,0.0,0.0,0.0,0.0,0.2,0.2,0.2,0.2,0.2,0.4,0.4,0.4,0.4,0.6,0.6,0.6,0.8,0.8,1.0,0.0]
BRs['TH']=[0.25,0.0,0.2,0.4,0.6,0.8,1.0,0.0,0.2,0.4,0.6,0.8,0.0,0.2,0.4,0.6,0.0,0.2,0.4,0.0,0.2,0.0,0.5]
BRs['TZ']=[0.25,1.0,0.8,0.6,0.4,0.2,0.0,0.8,0.6,0.4,0.2,0.0,0.6,0.4,0.2,0.0,0.4,0.2,0.0,0.2,0.0,0.0,0.5]
BRs['TW']=[0.50,0.0,0.0,0.0,0.0,0.0,0.0,0.2,0.2,0.2,0.2,0.2,0.4,0.4,0.4,0.4,0.6,0.6,0.6,0.8,0.8,1.0,0.0]
BRs['BH']=[0.25,0.0,0.2,0.4,0.6,0.8,1.0,0.0,0.2,0.4,0.6,0.8,0.0,0.2,0.4,0.6,0.0,0.2,0.4,0.0,0.2,0.0,0.5]
BRs['BZ']=[0.25,1.0,0.8,0.6,0.4,0.2,0.0,0.8,0.6,0.4,0.2,0.0,0.6,0.4,0.2,0.0,0.4,0.2,0.0,0.2,0.0,0.0,0.5]

for BR in range(0,1): #edited by rizki
	print 'BR:',BR
	outDirBR=outDir
# 	if(BR==1): outDirBR=outDir+"_BR1"
# 	if(BR==2): outDirBR=outDir+"_BR2"
	outDirBR=outDir+'_bW'+str(BRs['BW'][BR]).replace('.','p')+'_tZ'+str(BRs['TZ'][BR]).replace('.','p')+'_tH'+str(BRs['TH'][BR]).replace('.','p')
	if('BB' in outDir): outDirBR=outDir+'_tW'+str(BRs['TW'][BR]).replace('.','p')+'_bZ'+str(BRs['BZ'][BR]).replace('.','p')+'_bH'+str(BRs['BH'][BR]).replace('.','p')
	os.system('mkdir -v '+outDirBR)

	for mass in masses:
		for chi in chiralities:
			for era in eras:
	# 			for i in range(0,4): #edited by rizki
	# 				ht=100*i
					ht=200
					if era=='2016B-D':
						lep2 = 5
						lumi = 17.68
					else:
						lep2 = 0
						lumi = 18.19
					command="./makeLimitRootFiles.o %i %s %i %i %.2f %s %i" % (mass,chi,ht,lep2,lumi,era,BR)
					print command
					os.system(command)

	os.system('mv -v *root '+outDirBR+'/')