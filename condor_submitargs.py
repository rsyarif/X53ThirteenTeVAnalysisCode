import os,sys
execfile("/uscms_data/d3/jmanagan/EOSSafeUtils.py")

print 'Getting proxy'
proxyPath=os.popen('voms-proxy-info -path')
proxyPath=proxyPath.readline().strip()

tprimelist = [
    'TprimeTprime_M-800',
    # 'TprimeTprime_M-900',
    # 'TprimeTprime_M-1000',
    # 'TprimeTprime_M-1100',
    # 'TprimeTprime_M-1200',
    # 'TprimeTprime_M-1300',
    # 'TprimeTprime_M-1400',
    # 'TprimeTprime_M-1500',
    # 'TprimeTprime_M-1600',
    # 'TprimeTprime_M-1700',
    # 'TprimeTprime_M-1800',
]

#tprimedecays = ['BWBW','TZTZ','THTH','THBW','TZBW','TZTH']
tprimedecays = ['THBW','TZBW']

bprimelist = [
    'BprimeBprime_M-800',
    'BprimeBprime_M-900',
    'BprimeBprime_M-1000',
    'BprimeBprime_M-1100',
    'BprimeBprime_M-1200',
    'BprimeBprime_M-1300',
    'BprimeBprime_M-1400',
    'BprimeBprime_M-1500',
    'BprimeBprime_M-1600',
    'BprimeBprime_M-1700',
    'BprimeBprime_M-1800',
]

#bprimedecays = ['TWTW','BZBZ','BHBH','BHTW','BZTW','BZBH']
bprimedecays = ['BHTW','BZTW']

eras = ['2016B-D','2016E-H']

bkgdatalist = [
    # 'TTH',
    # 'TTW',
    # 'TTZ',
    # 'TTTT',
    # 'WZ',
    # 'ZZ',
    # 'WWW',
    # 'WWZ',
    # 'WZZ',
    # 'ZZZ',
    # 'WpWp',
    # 'TTH',
    # 'TTW',
    # 'TTZ',
    # 'TTTT',
    # 'WZ',
    # 'ZZ',
    # 'WWW',
    # 'WWZ',
    # 'WZZ',
    # 'ZZZ',
    # 'WpWp',

	'TTGJets',
	'ZGTo2LG',
	'TGJets',
	'WGToLNuG',
	'TTZToLLM1to10',


    # 'DataElEl2016B',
    # 'DataElMu2016B',
    # 'DataMuMu2016B',
    # 'DataElEl2016C',
    # 'DataElMu2016C',
    # 'DataMuMu2016C',
    # 'DataElEl2016D',
    # 'DataElMu2016D',
    # 'DataMuMu2016D',
    # 'DataElEl2016E',
    # 'DataElMu2016E',
    # 'DataMuMu2016E',
    # 'DataElEl2016F',
    # 'DataElMu2016F',
    # 'DataMuMu2016F',
    # 'DataElEl2016G',
    # 'DataElMu2016G',
    # 'DataMuMu2016G',
    # 'DataElEl2016H2',
    # 'DataElMu2016H2',
    # 'DataMuMu2016H2',
    # 'DataElEl2016H3',
    # 'DataElMu2016H3',
    # 'DataMuMu2016H3',

    # 'ChargeMisIDElEl2016B',
    # 'ChargeMisIDElMu2016B',
    # 'ChargeMisIDElEl2016C',
    # 'ChargeMisIDElMu2016C',
    # 'ChargeMisIDElEl2016D',
    # 'ChargeMisIDElMu2016D',
    # 'ChargeMisIDElEl2016E',
    # 'ChargeMisIDElMu2016E',
    # 'ChargeMisIDElEl2016F',
    # 'ChargeMisIDElMu2016F',
    # 'ChargeMisIDElEl2016G',
    # 'ChargeMisIDElMu2016G',
    # 'ChargeMisIDElEl2016H2',
    # 'ChargeMisIDElMu2016H2',
    # 'ChargeMisIDElEl2016H3',
    # 'ChargeMisIDElMu2016H3',

#     'NonPromptDataElEl2016B',
#     'NonPromptDataElMu2016B',
#     'NonPromptDataMuMu2016B',
#     'NonPromptDataElEl2016C',
#     'NonPromptDataElMu2016C',
#     'NonPromptDataMuMu2016C',
#     'NonPromptDataElEl2016D',
#     'NonPromptDataElMu2016D',
#     'NonPromptDataMuMu2016D',
#     'NonPromptDataElEl2016E',
#     'NonPromptDataElMu2016E',
#     'NonPromptDataMuMu2016E',
#     'NonPromptDataElEl2016F',
#     'NonPromptDataElMu2016F',
#     'NonPromptDataMuMu2016F',
#     'NonPromptDataElEl2016G',
#     'NonPromptDataElMu2016G',
#     'NonPromptDataMuMu2016G',
#     'NonPromptDataElEl2016H2',
#     'NonPromptDataElMu2016H2',
#     'NonPromptDataMuMu2016H2',
#     'NonPromptDataElEl2016H3',
#     'NonPromptDataElMu2016H3',
#     'NonPromptDataMuMu2016H3',
]

relBase = os.environ['CMSSW_BASE']
print 'Relbase:',relBase

#condorDir = '/uscms_data/d3/jmanagan/SSDL_101817_logs/'
# condorDir = '/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/JulieEdit/SSDL_101917_logs/'
# condorDir = '/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/JulieEdit/SSDL_NonPromptWithTrilepFR_110517_logs/'
condorDir = '/uscms_data/d3/rsyarif/CERN2017/produceLjmetNtuples_TTSSdilep/CMSSW_8_0_26_patch1/src/PostLJMet/JulieEdit/SSDL_BkgMCGamma_112817_logs/'
if not os.path.exists(condorDir): os.system('mkdir -p '+condorDir)
#outputDir = '/store/user/lpctlbsm/jmanagan/SSDL_101817/'
# outputDir = '/store/user/lpcljm/SSDL_101917_rizki/'
# outputDir = '/store/user/lpcljm/SSDL_NonPromptWithTrilepFR_110517_rizki/'
outputDir = '/store/user/lpcljm/SSDL_BkgMCGamma_112817_rizki/'
if not EOSpathExists(outputDir): os.system('eos root://cmseos.fnal.gov/ mkdir -p '+outputDir)

#thisDir = relBase+'/src/X53ThirteenTeVAnalysisCode'
thisDir = relBase+'/src/PostLJMet/JulieEdit/X53ThirteenTeVAnalysisCode'
tarfile = thisDir+'.tar'
print 'Making tar:'

if os.path.exists(tarfile):
    print 'tar already exists! Will not re-tar!'
else:
    os.chdir(thisDir)
    os.chdir('../')
    print 'tar --exclude="X53ThirteenTeVAnalysisCode/.git" -zcf'+tarfile+' '+thisDir.split('/')[-1]+'/'
    os.system('tar --exclude="X53ThirteenTeVAnalysisCode/.git" -zcf '+tarfile+' '+thisDir.split('/')[-1])

count = 0
'''
for sample in tprimelist:
    for decay in tprimedecays:
        for era in eras:

            count+=1
            dict={'RUNDIR':thisDir, 'SAMPLE':sample, 'CONDORDIR':condorDir, 'PROXY':proxyPath, 'ERA':era, 'DECAY':decay, 'TARFILE':tarfile, 'OUTPUTDIR':outputDir}
            jdfName=condorDir+'/%(SAMPLE)s_%(DECAY)s_%(ERA)s.job'%dict
            print jdfName
            jdf=open(jdfName,'w')
            jdf.write(
                """x509userproxy = %(PROXY)s
universe = vanilla
Executable = %(RUNDIR)s/runX53analyzer.sh
Should_Transfer_Files = YES
WhenToTransferOutput = ON_EXIT
Transfer_Input_Files = %(TARFILE)s
Output = %(SAMPLE)s_%(DECAY)s_%(ERA)s.out
Error = %(SAMPLE)s_%(DECAY)s_%(ERA)s.err
Log = %(SAMPLE)s_%(DECAY)s_%(ERA)s.log
Notification = Never
Arguments = %(SAMPLE)s %(ERA)s %(DECAY)s %(OUTPUTDIR)s
Queue 1"""%dict)
            jdf.close()
            os.chdir('%s/'%(condorDir))
            os.system('condor_submit %(SAMPLE)s_%(DECAY)s_%(ERA)s.job'%dict)
            os.system('sleep 0.5')
            os.chdir('%s'%(thisDir))
            print count, "jobs submitted!!!"


for sample in bprimelist:
    for decay in bprimedecays:
        for era in eras:

            count+=1
            dict={'RUNDIR':thisDir, 'SAMPLE':sample, 'CONDORDIR':condorDir, 'PROXY':proxyPath, 'ERA':era, 'DECAY':decay, 'TARFILE':tarfile, 'OUTPUTDIR':outputDir}
            jdfName=condorDir+'/%(SAMPLE)s_%(DECAY)s_%(ERA)s.job'%dict
            print jdfName
            jdf=open(jdfName,'w')
            jdf.write(
                """x509userproxy = %(PROXY)s
universe = vanilla
Executable = %(RUNDIR)s/runX53analyzer.sh
Should_Transfer_Files = YES
WhenToTransferOutput = ON_EXIT
Transfer_Input_Files = %(TARFILE)s
Output = %(SAMPLE)s_%(DECAY)s_%(ERA)s.out
Error = %(SAMPLE)s_%(DECAY)s_%(ERA)s.err
Log = %(SAMPLE)s_%(DECAY)s_%(ERA)s.log
Notification = Never
Arguments = %(SAMPLE)s %(ERA)s %(DECAY)s %(OUTPUTDIR)s
Queue 1"""%dict)
            jdf.close()
            os.chdir('%s/'%(condorDir))
            os.system('condor_submit %(SAMPLE)s_%(DECAY)s_%(ERA)s.job'%dict)
            os.system('sleep 0.5')
            os.chdir('%s'%(thisDir))
            print count, "jobs submitted!!!"
'''
decay = ''
for sample in bkgdatalist:
    for era in eras:

        count+=1
        dict={'RUNDIR':thisDir, 'SAMPLE':sample, 'CONDORDIR':condorDir, 'PROXY':proxyPath, 'ERA':era, 'DECAY':decay, 'TARFILE':tarfile, 'OUTPUTDIR':outputDir}
        jdfName=condorDir+'/%(SAMPLE)s_%(ERA)s.job'%dict
        print jdfName
        jdf=open(jdfName,'w')
        jdf.write(
            """x509userproxy = %(PROXY)s
universe = vanilla
Executable = %(RUNDIR)s/runX53analyzer.sh
Should_Transfer_Files = YES
request_memory = 6000
WhenToTransferOutput = ON_EXIT
Transfer_Input_Files = %(TARFILE)s
Output = %(SAMPLE)s_%(ERA)s.out
Error = %(SAMPLE)s_%(ERA)s.err
Log = %(SAMPLE)s_%(ERA)s.log
Notification = Never
Arguments = %(SAMPLE)s %(ERA)s DUMMYARG %(OUTPUTDIR)s
Queue 1"""%dict)
        jdf.close()
        os.chdir('%s/'%(condorDir))
        os.system('condor_submit %(SAMPLE)s_%(ERA)s.job'%dict)
        os.system('sleep 0.5')
        os.chdir('%s'%(thisDir))
        print count, "jobs submitted!!!"

