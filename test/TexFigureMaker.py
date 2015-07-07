#!/usr/bin/python

import os

#get list of figures
plots = os.listdir("plots")

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
    label+="}\n"
    f.write(label)
#end figure
    f.write("\\end{figure}")
#pad with some whitespace
    f.write("\n\n")

#make outfile
outfile=open("Figures.tex","w+")

for plot in plots:
#skip non pdfs
    if plot.find(".pdf")==-1:
        continue
    if not plot.find("All")==-1:
        printHeader(plot,outfile)
    elif plot.find("MuMu")==-1:
        printFigure(plot,outfile)
    else:
        printFooter(plot,outfile)

outfile.close()

