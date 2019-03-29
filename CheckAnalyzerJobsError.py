

import os, sys

#inputDir = '/uscms_data/d3/rsyarif/Brown2018/TT_BB_SSDL_Analyzer_2017data/LJMet94x_2lepTT_2017datasets_2019_1_13_rizki_hadds_Analyzer_elID2017_NonIsoTrig_logs/'

inputDir = sys.argv[1]

files =  [x for x in os.listdir(inputDir) if 'log' in x]
# files = [x for x in os.walk(inputDir).next()[2]]
print 'Checking :',inputDir

os.system('grep Error '+inputDir+'*')
os.system('grep error '+inputDir+'*')

for file_ in files:
    f = open(inputDir+file_,'r')
    lines = f.read()
    keyword = 'remove'
    if keyword in lines:
        print file_
        os.system('grep '+keyword+' '+inputDir+file_)

        #os.system('rm -vi '+inputDir+file_)

        #os.system('condor_submit '+inputDir+file_.replace('.log','.job'))

    f.close()


