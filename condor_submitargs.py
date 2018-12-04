import os,sys
execfile("/uscms_data/d3/rsyarif/EOSSafeUtils.py")

print 'Getting proxy'
proxyPath=os.popen('voms-proxy-info -path')
proxyPath=proxyPath.readline().strip()

tprimelist = [
#     'TprimeTprime_M-800',
    # 'TprimeTprime_M-900',
#     'TprimeTprime_M-1000',
#     'TprimeTprime_M-1100',
#     'TprimeTprime_M-1200',
#     'TprimeTprime_M-1300',
#     'TprimeTprime_M-1400',
#     'TprimeTprime_M-1500',
#     'TprimeTprime_M-1600',
#     'TprimeTprime_M-1700',
#     'TprimeTprime_M-1800',
]

tprimedecays = ['BWBW','TZTZ','THTH','THBW','TZBW','TZTH']
# tprimedecays = ['THBW','TZBW']

bprimelist = [
#     'BprimeBprime_M-800',
#     'BprimeBprime_M-900',
#     'BprimeBprime_M-1000',
#     'BprimeBprime_M-1100',
#     'BprimeBprime_M-1200',
#     'BprimeBprime_M-1300',
#     'BprimeBprime_M-1400',
#     'BprimeBprime_M-1500',
#     'BprimeBprime_M-1600',
#     'BprimeBprime_M-1700',
#     'BprimeBprime_M-1800',
]

bprimedecays = ['TWTW','BZBZ','BHBH','BHTW','BZTW','BZBH']

# eras = ['2016B-D','2016E-H']
eras = ['2018A-D']

bkgdatalist = [
#     'TTH',
#     'TTW',
#     'TTZ',
#     'TTZ_part1',
#     'TTZ_part2',
#     'TTZ_part3',
#     'TTTT',
#     'WZ',
#     'ZZ',
#     'WWW',
#     'WWZ',
#     'WZZ',
#     'ZZZ',
#     'WpWp',

# 	'TTGJets',
# 	'ZGTo2LG',
# 	'TGJets',
# 	'WGToLNuG',
# 	'TTZToLLM1to10',


#     'DataElEl2018A',
#     'DataElMu2018A',
#     'DataMuMu2018A',
#     'DataElEl2018B',
#     'DataElMu2018B',
#     'DataMuMu2018B',
#     'DataElEl2018C',
#     'DataElMu2018C',
#     'DataMuMu2018C',
#     'DataElEl2018D',
#     'DataElMu2018D',
    'DataMuMu2018D',
# 
#     'ChargeMisIDElEl2018A',
#     'ChargeMisIDElMu2018A',
#     'ChargeMisIDElEl2018B',
#     'ChargeMisIDElMu2018B',
#     'ChargeMisIDElEl2018C',
#     'ChargeMisIDElMu2018C',
#     'ChargeMisIDElEl2018D',
#     'ChargeMisIDElMu2018D',
# 
#     'NonPromptDataElEl2018A',
#     'NonPromptDataElMu2018A',
#     'NonPromptDataMuMu2018A',
#     'NonPromptDataElEl2018B',
#     'NonPromptDataElMu2018B',
#     'NonPromptDataMuMu2018B',
#     'NonPromptDataElEl2018C',
#     'NonPromptDataElMu2018C',
#     'NonPromptDataMuMu2018C',
#     'NonPromptDataElEl2018D',
#     'NonPromptDataElMu2018D',
    'NonPromptDataMuMu2018D',
]

relBase = os.environ['CMSSW_BASE']
print 'Relbase:',relBase

condorDir = '/uscms_data/d3/rsyarif/Brown2018/TT_BB_SSDL_Analyzer_2018data/LJMet102x_2lepTT_2018datasets_2018_11_29_rizki_hadds_Analyzer_logs/'
if not os.path.exists(condorDir): os.system('mkdir -p '+condorDir)
outputDir = '/store/user/lpcljm/LJMet102x_2lepTT_2018datasets_2018_11_29_rizki_hadds_Analyzer/'
if not EOSpathExists(outputDir): os.system('eos root://cmseos.fnal.gov/ mkdir -p '+outputDir)

thisDir = relBase+'/src/Analyzer'
tarfile = thisDir+'.tar'
print 'Making tar:'

if os.path.exists(tarfile):
    print 'tar already exists! Will not re-tar!'
else:
    os.chdir(thisDir)
    os.chdir('../')
    print 'tar --exclude="Analyzer/.git" -zcf'+tarfile+' '+thisDir.split('/')[-1]+'/'
    os.system('tar --exclude="Analyzer/.git" -zcf '+tarfile+' '+thisDir.split('/')[-1])

count = 0

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

'''
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
request_memory = 8000
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

