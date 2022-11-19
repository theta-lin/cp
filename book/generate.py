import glob
import os

with open('book.tex', 'w') as out:
    out.write('\\documentclass{article}\n')
    out.write('\\usepackage{fullpage}\n')
    out.write('\\usepackage{minted}\n')
    out.write('\\begin{document}\n')
    out.write('\\tableofcontents')

    file_names = glob.glob("../src/*")
    for file_name in file_names:
        out.write('\\section{')
        out.write(os.path.basename(file_name)[: -4].replace('_', ' ').capitalize())
        out.write('}\n')

        out.write('\\inputminted[breaklines=true]{cpp}{')
        out.write(file_name)
        out.write('}\n')

    out.write('\\end{document}\n')
