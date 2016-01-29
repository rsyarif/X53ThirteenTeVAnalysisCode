#!/usr/bin/python


import os


allfiles = os.listdir('.')
cfgs = []

for file in allfiles:
    if file.find(".py")==-1 or file.find("X53X53_M")==-1 or file.find("HT1100")==-1 or file.find("All")==-1:
#    if file.find(".py")==-1 or file.find("X53X53_M")==-1 or file.find("Combined")==-1:
        continue
    cfgs.append(file)

for cfg in cfgs:
    os.system("../../utils2/theta-auto.py %s" % cfg)
    command = "../../utils2/theta-auto.py %s" % cfg
    print command
