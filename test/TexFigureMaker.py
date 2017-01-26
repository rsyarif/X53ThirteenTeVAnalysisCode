#!/usr/bin/python

import os

def printHeader(figName,f):
#clearpage if staring channels anew
    if not figName.find("All")==-1:
        #write header
        f.write("""\\begin{figure}
\\centering
\\includegraphics[width=0.45\\textwidth]{plots/""")
        f.write(figName)
        f.write("}\n")

def printFigure(figName,f):
        f.write("\\includegraphics[width=0.45\\textwidth]{plots/")
        f.write(figName)
        f.write("}\n")

def printFooter(figName,f):
#first print figure:
    printFigure(figName,f)
#make label
    label="\\label{fig:"
    name=figName.split("_")
    label+=name[0]
    #write caption
    caption="\\caption{"
    capVar = name[0]
    capVar = capVar.replace('clean','')
    capVar = capVar.replace('Clean','')
    capVar = capVar.replace('Jet1', " Leading Jet ")
    capVar = capVar.replace('Jet2', " sub-Leading Jet ")
    capVar = capVar.replace('Lep1',' Leading Lepton ')
    capVar = capVar.replace('Lep2',' sub-Leading Lepton ')
    capVar = capVar.replace('Pt',' \\pt')
    capVar = capVar.replace('Eta',' $\\eta$')
    capVar = capVar.replace('Phi',' $\\phi$')
    caption= caption+capVar+' for eras '
    if figName.find('2016B-D')!=-1:
        era = '2016B-D'
    elif figName.find('2016E-H')!=-1:
        era='2016E-H'
    else:
        era='2016B-H'
    caption= caption+era+'}\n'
    f.write(caption)
    label=label+'-'+era+"}\n"
    f.write(label)
#end figure
    f.write("\\end{figure}")
#pad with some whitespace
    f.write("\n\n")

#make outfile
outfile=open("Figures.tex","w+")

#get list of figures
plots = os.listdir("plots_forPAS")
plots.sort(key=lambda x:(not x.islower(), x))

plotsFull=[]
plotsBD = []
plotsEH = []

for plot in plots:
    if plot.find('2016B-D')!=-1:
        plotsBD.append(plot)
    elif plot.find('2016E-H')!=-1:
        plotsEH.append(plot)
    else:
        plotsFull.append(plot)

for plot in plotsFull:
#skip non pdfs
    if plot.find(".pdf")==-1:
        continue
    if plot.find("new")!=-1 or plot.find('New')!=-1 or plot.find('NW')!=-1 or plot.find('NTop')!=-1 or plot.find('X53Mass')!=-1:
        continue
    if not plot.find("All")==-1:
        printHeader(plot,outfile)
    elif plot.find("MuMu")==-1:
        printFigure(plot,outfile)
    else:
        printFooter(plot,outfile)

for plot in plotsBD:
#skip non pdfs
    if plot.find(".pdf")==-1:
        continue
    if plot.find("new")!=-1 or plot.find('New')!=-1 or plot.find('NW')!=-1 or plot.find('NTop')!=-1 or plot.find('X53Mass')!=-1:
        continue
    if not plot.find("All")==-1:
        printHeader(plot,outfile)
    elif plot.find("MuMu")==-1:
        printFigure(plot,outfile)
    else:
        printFooter(plot,outfile)

for plot in plotsEH:
#skip non pdfs
    if plot.find(".pdf")==-1:
        continue
    if plot.find("new")!=-1 or plot.find('New')!=-1 or plot.find('NW')!=-1 or plot.find('NTop')!=-1 or plot.find('X53Mass')!=-1:
        continue
    if not plot.find("All")==-1:
        printHeader(plot,outfile)
    elif plot.find("MuMu")==-1:
        printFigure(plot,outfile)
    else:
        printFooter(plot,outfile)


outfile.close()

