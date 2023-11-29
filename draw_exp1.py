import os
from pygnuplot import gnuplot
import pandas as pd

g = gnuplot.Gnuplot()
g.set(terminal='postscript eps color "Times-Roman" 25 enhanced')
g.set(size='1,0.65')
g.set(style='data histogram')
g.set(style='histogram cluster gap 2')
g.set(style='fill solid border')
g.set(style='fill pattern')
g.set(boxwidth='1')
g.unset('mytics')
g.set(logscale='y')
g.set(format='y "10^{%L}"')
g.set(xtics='font "Times-Roman,25"')
g.set(key='autotitle columnheader')
g.set(key='top horizontal center')
g.set(key='height -0.3')


def getfile(method, dataset, k, l):
    for file_name in os.listdir('ExpResults/Exp_CW_generation/'):
        if method in file_name and dataset in file_name and \
           ('k'+str(k)+'_' in file_name or 'k'+str(k)+'.' in file_name) and \
           ('l'+str(l)+'_' in file_name or 'l'+str(l)+'.' in file_name):
            return 'ExpResults/Exp_CW_generation/' + file_name

ktics = [16, 32, 64, 128, 256]
ltics = [100, 1000, 10000, 100000]
# generation time vs k
g.set(x2label='offset -12.5 "Generation Time (s)" font "Times-Roman, 25"')
g.set(xlabel='"k"')
for dataset in 'openwebtext', 'PAN11', 'pile':
    for l in ltics:
        data = []
        for k in ktics:
            tmp = [k]
            file_name = getfile('OPH', dataset, k, l)
            with open(file_name, 'r') as f:
                tmp.append(float(f.readline().strip()) / 100)
            file_name = getfile('KMINS', dataset, k, l)
            with open(file_name, 'r') as f:
                tmp.append(float(f.readline().strip()) / 100)
            data.append(tmp)
        g.set(output='"' + f'Figures/EXP1/{dataset}_t_vs_k_l{l}.eps' + '"')
        df = pd.DataFrame(data)
        # print(f'l={l}')
        # print(df)
        g.plot_data(df, 'using 3:xtic(2) title "OPH" lt -1 fs pattern 8', 'using 4 title "KMINS" lt -1 fs pattern 4')

# number of compact windows vs k
g.set(x2label='offset -12.5 "Number of Compact Windows" font "Times-Roman, 25"')
g.set(xlabel='"k"')
for dataset in 'openwebtext', 'PAN11', 'pile':
    for l in ltics:
        data = []
        for k in ktics:
            tmp = [k]
            file_name = getfile('OPH', dataset, k, l)
            with open(file_name, 'r') as f:
                f.readline()
                tmp.append(int(f.readline().strip()) / 100)
            file_name = getfile('KMINS', dataset, k, l)
            with open(file_name, 'r') as f:
                f.readline()
                tmp.append(int(f.readline().strip()) / 100)
            data.append(tmp)
        g.set(output='"' + f'Figures/EXP1/{dataset}_ncws_vs_k_l{l}.eps' + '"')
        df = pd.DataFrame(data)
        # print(f'l={l}')
        # print(df)
        g.plot_data(df, 'using 3:xtic(2) title "OPH" lt -1 fs pattern 8', 'using 4 title "KMINS" lt -1 fs pattern 4')

# generation time vs l
g.set(x2label='offset -12.5 "Generation Time (s)" font "Times-Roman, 25"')
g.set(xlabel='"l"')
for dataset in 'openwebtext', 'PAN11', 'pile':
    for k in ktics:
        data = []
        for l in ltics:
            tmp = [l]
            file_name = getfile('OPH', dataset, k, l)
            with open(file_name, 'r') as f:
                tmp.append(float(f.readline().strip()) / 100)
            file_name = getfile('KMINS', dataset, k, l)
            with open(file_name, 'r') as f:
                tmp.append(float(f.readline().strip()) / 100)
            data.append(tmp)
        g.set(output='"' + f'Figures/EXP1/{dataset}_t_vs_l_k{k}.eps' + '"')
        df = pd.DataFrame(data)
        g.plot_data(df, 'using 3:xtic(2) title "OPH" lt -1 fs pattern 8', 'using 4 title "KMINS" lt -1 fs pattern 4')

# number of compact windows vs l
g.set(x2label='offset -12.5 "Number of Compact Windows" font "Times-Roman, 25"')
g.set(xlabel='"l"')
for dataset in 'openwebtext', 'PAN11', 'pile':
    for k in ktics:
        data = []
        for l in ltics:
            tmp = [l]
            file_name = getfile('OPH', dataset, k, l)
            with open(file_name, 'r') as f:
                f.readline()
                tmp.append(int(f.readline().strip()) / 100)
            file_name = getfile('KMINS', dataset, k, l)
            with open(file_name, 'r') as f:
                f.readline()
                tmp.append(int(f.readline().strip()) / 100)
            data.append(tmp)
        g.set(output='"' + f'Figures/EXP1/{dataset}_ncws_vs_l_k{k}.eps' + '"')
        df = pd.DataFrame(data)
        g.plot_data(df, 'using 3:xtic(2) title "OPH" lt -1 fs pattern 8', 'using 4 title "KMINS" lt -1 fs pattern 4')
