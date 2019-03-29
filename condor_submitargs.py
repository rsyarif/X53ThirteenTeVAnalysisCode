import os,sys
execfile("/uscms_data/d3/rsyarif/EOSSafeUtils.py")

print 'Getting proxy'
proxyPath=os.popen('voms-proxy-info -path')
proxyPath=proxyPath.readline().strip()

tprimelist = [
    'TprimeTprime_M-800',
    'TprimeTprime_M-900',
    'TprimeTprime_M-1000',
    'TprimeTprime_M-1100',
    'TprimeTprime_M-1200',
    'TprimeTprime_M-1300',
    'TprimeTprime_M-1400',
    'TprimeTprime_M-1500',
    'TprimeTprime_M-1600',
    'TprimeTprime_M-1700',
    'TprimeTprime_M-1800',
]

tprimedecays = ['BWBW','TZTZ','THTH','THBW','TZBW','TZTH']
# tprimedecays = ['THBW','TZBW']

bprimelist = [
    'BprimeBprime_M-800',
    'BprimeBprime_M-900',
    'BprimeBprime_M-1000',
    'BprimeBprime_M-1100',
#    'BprimeBprime_M-1200',
    'BprimeBprime_M-1300',
    'BprimeBprime_M-1400',
    'BprimeBprime_M-1500',
    'BprimeBprime_M-1600',
#    'BprimeBprime_M-1700',
    'BprimeBprime_M-1800',
]

bprimedecays = ['TWTW','BZBZ','BHBH','BHTW','BZTW','BZBH']

# eras = ['2016B-D','2016E-H']
#eras = ['2017B-F']
eras = ['2017C-F']

bkgdatalist = [
    'TTH',
    'TTW',
    'TTZ',
    'TTTT',
    'WZ',
    'ZZ',
    'ZZ_part1',
    'ZZ_part2_1',
    'ZZ_part2_2',
    'ZZ_part2_3',
    'ZZ_part2_4',
    'ZZ_part2_5',
    'ZZ_part2_6',
    'ZZ_part2_7',
    'ZZ_part2_8',
    'ZZ_part2_9',
    'ZZ_part2_10',
    'ZZ_part2_11',
    'ZZ_part2_12',
    'ZZ_part2_13',
    'ZZ_part2_14',
    'ZZ_part2_15',
    'WWW',
    'WWZ',
    'WZZ',
    'ZZZ',
    'WpWp',

# 	'TTGJets',
# 	'ZGTo2LG',
# 	'TGJets',
# 	'WGToLNuG',
# 	'TTZToLLM1to10',


    'DataElEl2017B',
    'DataElMu2017B',
    'DataMuMu2017B',
    'DataElEl2017C',
    'DataElMu2017C',
    'DataMuMu2017C',
    'DataElEl2017D',
    'DataElMu2017D',
    'DataMuMu2017D',
    'DataElEl2017E',
    'DataElMu2017E',
    'DataMuMu2017E',
    'DataElEl2017F',
    'DataElMu2017F',
#     'DataMuMu2017F',
    'DataMuMu2017F_1',
    'DataMuMu2017F_2_1',
    'DataMuMu2017F_2_2',
    'DataMuMu2017F_2_3',
    'DataMuMu2017F_2_4',
    'DataMuMu2017F_2_5',


    'ChargeMisIDElEl2017B',
    'ChargeMisIDElMu2017B',
    'ChargeMisIDElEl2017C',
    'ChargeMisIDElMu2017C',
    'ChargeMisIDElEl2017D',
    'ChargeMisIDElMu2017D',
    'ChargeMisIDElEl2017E',
    'ChargeMisIDElMu2017E',
    'ChargeMisIDElEl2017F',
    'ChargeMisIDElMu2017F',

    'NonPromptDataElEl2017B',
    'NonPromptDataElMu2017B',
    'NonPromptDataMuMu2017B',
    'NonPromptDataElEl2017C',
    'NonPromptDataElMu2017C',
    'NonPromptDataMuMu2017C',
    'NonPromptDataElEl2017D',
    'NonPromptDataElMu2017D',
    'NonPromptDataMuMu2017D',
    'NonPromptDataElEl2017E',
    'NonPromptDataElMu2017E',
    'NonPromptDataMuMu2017E',
    'NonPromptDataElEl2017F',
    'NonPromptDataElMu2017F',
#     'NonPromptDataMuMu2017F',
    'NonPromptDataMuMu2017F_1',
    'NonPromptDataMuMu2017F_2_1',
    'NonPromptDataMuMu2017F_2_2',
    'NonPromptDataMuMu2017F_2_3',
    'NonPromptDataMuMu2017F_2_4',
    'NonPromptDataMuMu2017F_2_5',
]

relBase = os.environ['CMSSW_BASE']
print 'Relbase:',relBase


# saveDir = 'LJMet94x_2lepTT_2017datasets_2018_11_18_rizki_hadds_Analyzer'
# saveDir = 'LJMet94x_2lepTT_2017datasets_2018_11_18_rizki_hadds_Analyzer_v2_elID2017'
# saveDir = 'LJMet94x_2lepTT_2017datasets_2019_1_13_rizki_hadds_Analyzer_elID2017_IsoTrig' #CHECK isoTrig in X53Analyzer.cc and compile!!
# saveDir = 'LJMet94x_2lepTT_2017datasets_2019_1_13_rizki_hadds_Analyzer_elID2017_NonIsoTrig' #CHECK isoTrig in X53Analyzer.cc and compile!!
# saveDir = 'LJMet94x_2lepTT_2017datasets_2019_2_18_rizki_hadds_Analyzer_elID2017_nonIsoHTtrig' #CHECK nonIso_HTtrig and inputFolder in X53Analyzer.cc and compile!!
saveDir = 'LJMet94x_2lepTT_2017datasets_2019_3_15_rizki_hadds_Analyzer_elIDv2_nonIsoHTtrig' #CHECK nonIso_HTtrig and inputFolder in X53Analyzer.cc and compile!!

condorDir = '/uscms_data/d3/rsyarif/Brown2018/TT_BB_SSDL_Analyzer_2017data/'+saveDir+'_logs/'
if not os.path.exists(condorDir): os.system('mkdir -p '+condorDir)
outputDir = '/store/user/lpcljm/'+saveDir
if not EOSpathExists(outputDir): os.system('eos root://cmseos.fnal.gov/ mkdir -p '+outputDir)

thisDir = relBase+'/src/Analyzer'
tarfile = thisDir+'.tar'
print 'Making tar:'

os.system('rm -vi '+relBase+'/src/Analyzer.tar')
if os.path.exists(tarfile):
    print 'tar already exists! Will not re-tar!'
else:
    os.chdir(thisDir)
    os.chdir('../')
    print 'tar --exclude="Analyzer/.git" --exclude="Analyzer/test/PromptRate*" --exclude="Analyzer/test/ChargeMisID*" --exclude="Analyzer/test/FakeRate*" --exclude="Analyzer/test/plot*" --exclude="Analyzer/Limits*" --exclude="Analyzer/test/csc2015*" -zvcf '+tarfile+' '+thisDir.split('/')[-1]+'/'
    os.system('tar --exclude="Analyzer/.git" --exclude="Analyzer/test/PromptRate*" --exclude="Analyzer/test/ChargeMisID*" --exclude="Analyzer/test/FakeRate*" --exclude="Analyzer/test/plot*" --exclude="Analyzer/Limits*" --exclude="Analyzer/test/csc2015*" -zvcf '+tarfile+' '+thisDir.split('/')[-1])

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
request_memory = 12000
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

