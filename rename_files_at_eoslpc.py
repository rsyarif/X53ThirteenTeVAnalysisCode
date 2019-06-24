
import os

xrd = 'eos root://cmseos.fnal.gov/'

myDir = '/store/user/lpcljm/LJMet94x_2lepTT_2017datasets_2019_3_15_rizki_hadds_Analyzer_elIDv2_nonIsoHTtrig/'

def striplist(alist):
        #takes a list of strings, returns a version of the list with
        #whitespace stripped from all entries.
        ret = []
        for item in alist:
                ret.append(item.strip())
        return ret


def EOSlistdir(Dir):
        #ls Dir, only eos safe.
        #does not check that this is a directory
        #returns a list of the contents of ls
        items = os.popen(xrd+' ls '+Dir).readlines() #they have a \n at the end
        return striplist(items)

if __name__ == '__main__':
        for f in EOSlistdir(myDir):
		if '2017B-F' not in f: continue
		os.system(xrd+' file rename '+myDir+f+' '+myDir+f.replace('2017B-F','2017C-F'))






