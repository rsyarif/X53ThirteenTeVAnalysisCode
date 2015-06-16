#!/usr/bin/python

import os

#get list of figures
plots = os.listdir("plots")

def printFigure(figName,f):
#clearpage if staring channels anew
    if not figName.find("All")==-1:
        f.write("\\clearpage\n")
#write header
    f.write("""\\begin{figure}
\\centering
\\includegraphics[width=0.45\\textwidth]{plots/""")
    f.write(figName)
    f.write("}\n")
#make caption
    caption="\\caption{"
#make label
    label="\\label{fig:"
    name=figName.split("_")
    label+=name[0]
    channel=name[2].split(".")
    label+=channel[0]
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
    printFigure(plot,outfile)


outfile.close()

